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

  //-------------------------------------------------------------------------------
  // Approach 1: Sub-optimal (Two-Pass with Two Arrays)
  //-------------------------------------------------------------------------------

  /*
   * Method: candy
   * -------------
   * Calculates the minimum candies needed.
   * * Strategy: Two-Pass Greedy
   * 1. Initialize all children with 1 candy (Requirement 1).
   * 2. Left-to-Right Pass: Ensure children with higher ratings than their
   * LEFT neighbor get more candies.
   * 3. Right-to-Left Pass: Ensure children with higher ratings than their
   * RIGHT neighbor get more candies.
   * * Complexity Analysis:
   * Time Complexity: O(N)
   * - We traverse the array exactly 3 times (L->R, R->L, Sum).
   * Space Complexity: O(N)
   * - To store the 'candies' array.
   */
  int candy(vector<int> &ratings)
  {
    int n = ratings.size();

    // Step 1: Give everyone 1 candy initially
    // This satisfies the "Each child must have at least one candy" rule.
    vector<int> candies(n, 1);

    // Step 2: Left-to-Right Pass
    // Only look at the LEFT neighbor (i-1)
    for (int i = 1; i < n; i++)
    {
      if (ratings[i] > ratings[i - 1])
      {
        // If I have a higher rating than my left neighbor,
        // I must have 1 more candy than them.
        candies[i] = candies[i - 1] + 1;
      }
    }

    // Step 3: Right-to-Left Pass
    // Only look at the RIGHT neighbor (i+1)
    for (int i = n - 2; i >= 0; i--)
    {
      if (ratings[i] > ratings[i + 1])
      {
        // If I have a higher rating than my right neighbor,
        // I must have more candies than them.
        // CRITICAL: We take max() to ensure we don't break the condition
        // established in the Left-to-Right pass.
        candies[i] = max(candies[i], candies[i + 1] + 1);
      }
    }

    // Step 4: Sum up the candies
    // (accumulate is a standard library function to sum a vector)
    return accumulate(candies.begin(), candies.end(), 0);
  }

  //-------------------------------------------------------------------------------
  // Approach 2: Sub-optimal (Two-Pass but Space Optimized) [IGNORE]
  //-------------------------------------------------------------------------------

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

  //-------------------------------------------------------------------------------
  // Approach 3: Optimal One-Pass (Greedy) [Note: Skipped]
  //-------------------------------------------------------------------------------

  /*
   * Method: candy
   * -------------
   * Calculates the minimum total candies required under the given constraints.
   * * Approach: Slope (Peak & Valley) Strategy
   * We treat the ratings array as a mountain range and calculate candies on the fly
   * without using extra space.
   * * 1. Initialization: The first child always starts with 1 candy.
   * 2. Flat Surface (ratings[i] == ratings[i-1]):
   * - The current child gets 1 candy (reset). The sequence restarts.
   * 3. Increasing Slope (ratings[i] > ratings[i-1]):
   * - We are climbing a mountain. Each subsequent child gets 1 more candy than the last.
   * - We track the 'peak' height to compare with the valley later.
   * 4. Decreasing Slope (ratings[i] < ratings[i-1]):
   * - We are going down into a valley.
   * - MATHEMATICAL TRICK: Instead of assigning candies like 3, 2, 1, we add them to the sum
   * in reverse order (1, then 2, then 3...) as we descend.
   * - 'down' tracks the length of the descent.
   * - CONFLICT RESOLUTION: If the "Down" slope becomes longer than the "Up" slope (Peak),
   * the peak wasn't high enough. We retroactively increase the peak's value by the difference, to avoid -ve values.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * We iterate through the array exactly once. The inner while loops just advance the main pointer 'i'.
   * - Space Complexity: O(1)
   * We only use a few variables (sum, i, up, down, peak) instead of an O(N) array.
   */
  int candy(vector<int> &ratings)
  {
    int n = ratings.size();
    int i = 1;   // Pointer to traverse the array
    int sum = 1; // Total candies accumulated (First child gets 1 initially)

    while (i < n)
    {
      // Case 1: Flat Surface (Current rating equals previous)
      // Rule: "Each child must have at least one candy."
      // Since there is no slope requirement, we reset and give 1 candy.
      if (ratings[i] == ratings[i - 1])
      {
        sum += 1;
        i++;
        continue;
      }

      // Case 2: Increasing Slope (Current rating > previous)
      // We are climbing up.
      int up = 1;   // Tracks height of the climb relative to the start of this slope
      int peak = 1; // Tracks the max height reached (used later for adjustment)

      while (i < n && ratings[i] > ratings[i - 1])
      {
        up++;      // Increment candy count for the current child (2, 3, 4...)
                   // Note: // here increasing 'up' before summing
        peak = up; // Update the peak height
        sum += up; // Add these candies to total sum
        i++;
      }

      // Case 3: Decreasing Slope (Current rating < previous)
      // We are sliding down.
      int down = 1; // Tracks length of the descent
      while (i < n && ratings[i] < ratings[i - 1])
      {
        // LOGIC: When going down, the current child gets 1, the previous gets 2, etc.
        // We simulate this by adding 'down' to sum.
        // Step 1: Add 1 (for bottom-most child).
        // Step 2: Add 2 (boost previous child to 2, bottom remains 1).
        sum += down;
        down++; // Note: here increase 'down' after summing
        i++;
      }

      // CRITICAL ADJUSTMENT: Peak Correction
      // The 'peak' is shared by the Up slope and the Down slope.
      // It must be high enough to satisfy BOTH sides.
      // Example: Up slope height 2, Down slope length 3.
      // The peak must be at least 4 (3+1) to support the descent.
      // If down > peak, we add the difference to lift the peak retroactively.
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
