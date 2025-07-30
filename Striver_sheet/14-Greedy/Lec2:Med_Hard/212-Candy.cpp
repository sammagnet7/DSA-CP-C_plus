#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_set>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

/*
1. Title: Candy

Links:
https://www.youtube.com/watch?v=IIqVFvKE6RY
https://takeuforward.org/plus/dsa/problems/candy?tab=editorial
https://leetcode.com/problems/candy/description/


Problem statement:
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Examples:
  Example 1:
  Input: ratings = [1,0,2]
  Output: 5
  Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

  Example 2:
  Input: ratings = [1,2,2]
  Output: 4
  Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
  The third child gets 1 candy because it satisfies the above two conditions.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Candy
  //-------------------------------------------------------------------------------

  // Approach 1: Sub-optimal (Two-Pass with Two Arrays)
  // Time Complexity: O(N)
  // Space Complexity: O(N) + O(N) = O(N)
  // Logic: Use two arrays to track candies from both left and right passes,
  // then take the maximum at each index.
  // int candy(vector<int> &ratings)
  // {
  //   int N = ratings.size();

  //   vector<int> leftCandies(N);  // Tracks left-to-right constraints
  //   vector<int> rightCandies(N); // Tracks right-to-left constraints

  //   leftCandies[0] = 1;
  //   rightCandies[N - 1] = 1;

  //   // Left to Right Pass: ensure increasing rating gets more candy
  //   for (int i = 1; i < N; i++)
  //   {
  //     leftCandies[i] = (ratings[i] > ratings[i - 1]) ? leftCandies[i - 1] + 1 : 1;

  //     // Right to Left in same loop
  //     int revIdx = N - 1 - i;
  //     rightCandies[revIdx] = (ratings[revIdx] > ratings[revIdx + 1]) ? rightCandies[revIdx + 1] + 1 : 1;
  //   }

  //   // Final candies = max(left pass, right pass) at each index
  //   int ans = 0;
  //   for (int i = 0; i < N; i++)
  //   {
  //     ans += max(leftCandies[i], rightCandies[i]);
  //   }

  //   return ans;
  // }

  // Approach 2: Sub-optimal (Two-Pass but Space Optimized)
  // Time Complexity: O(N)
  // Space Complexity: O(N) for leftCandies only
  // Logic: Store left pass in array, right pass inline using a variable.
  // int candy(vector<int> &ratings)
  // {
  //   int N = ratings.size();

  //   vector<int> leftCandies(N);
  //   leftCandies[0] = 1;

  //   // Left-to-right pass
  //   for (int i = 1; i < N; i++)
  //   {
  //     leftCandies[i] = (ratings[i] > ratings[i - 1]) ? leftCandies[i - 1] + 1 : 1;
  //   }

  //   int ans = max(leftCandies[N - 1], 1); // Start with last element
  //   int rightCandiesPrev = 1;             // Tracks right-to-left candy

  //   // Right-to-left pass (using variable instead of array)
  //   for (int i = N - 2; i >= 0; i--)
  //   {
  //     int rightCandiesCur = (ratings[i] > ratings[i + 1]) ? rightCandiesPrev + 1 : 1;

  //     ans += max(leftCandies[i], rightCandiesCur);
  //     rightCandiesPrev = rightCandiesCur;
  //   }

  //   return ans;
  // }

  // Approach 3: Optimal One-Pass (Greedy) [Note: Skipped]
  // Time Complexity: O(N)
  // Space Complexity: O(1)
  // Logic: Traverse once while keeping track of increasing and decreasing trends.
  // Use greedy logic to adjust candies when decreasing slope exceeds peak.
  int candy(vector<int> &ratings)
  {
    int n = ratings.size();
    int i = 1;   // Current index
    int sum = 1; // Total candies (first child gets 1)

    while (i < n)
    {
      // Case 1: Equal ratings → give 1 candy
      if (ratings[i] == ratings[i - 1])
      {
        sum += 1;
        i++;
        continue;
      }

      // Case 2: Increasing slope
      int peak = 1;
      while (i < n && ratings[i] > ratings[i - 1])
      {
        peak += 1;
        sum += peak;
        i++;
      }

      // Case 3: Decreasing slope
      int down = 1;
      while (i < n && ratings[i] < ratings[i - 1])
      {
        sum += down;
        down++;
        i++;
      }

      // Adjustment: if down slope is longer than peak slope
      if (down > peak)
      {
        sum += (down - peak);
      }
    }

    return sum;
  }
};

int main()
{
  return 0;
}
