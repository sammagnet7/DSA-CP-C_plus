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

1. Title: Ninja’s Training

Links:
https://takeuforward.org/data-structure/dynamic-programming-ninjas-training-dp-7/
https://takeuforward.org/plus/dsa/problems/ninja's-training?tab=editorial
https://www.naukri.com/code360/problems/ninja-s-training_3621003?leftPanelTabValue=PROBLEM


Problem statement:
Ninja is planing this ‘N’ days-long training schedule. Each day, he can perform any one of these three activities. (Running, Fighting Practice or Learning New Moves). Each activity has some merit points on each day. As Ninja has to improve all his skills, he can’t do the same activity in two consecutive days. Can you help Ninja find out the maximum merit points Ninja can earn?

You are given a 2D array of size N*3 ‘POINTS’ with the points corresponding to each day and activity. Your task is to calculate the maximum number of merit points that Ninja can earn.

For Example
If the given ‘POINTS’ array is [[1,2,5], [3 ,1 ,1] ,[3,3,3] ],the answer will be 11 as 5 + 3 + 3.

Sample Input 1:
2
3
1 2 5
3 1 1
3 3 3
3
10 40 70
20 50 80
30 60 90
Sample Output 1:
11
210
Explanation of sample input 1:
For the first test case,
One of the answers can be:
On the first day, Ninja will learn new moves and earn 5 merit points.
On the second day, Ninja will do running and earn 3 merit points.
On the third day, Ninja will do fighting and earn 3 merit points.
The total merit point is 11 which is the maximum.
Hence, the answer is 11.

For the second test case:
One of the answers can be:
On the first day, Ninja will learn new moves and earn 70 merit points.
On the second day, Ninja will do fighting and earn 50 merit points.
On the third day, Ninja will learn new moves and earn 90 merit points.
The total merit point is 210 which is the maximum.
Hence, the answer is 210.
Sample Input 2:
2
3
18 11 19
4 13 7
1 8 13
2
10 50 1
5 100 11
Sample Output 2:
45
110


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
  // 1. Title: Ninja’s Training
  //-------------------------------------------------------------------------------

  /*
   * Function: maxPoints
   * -------------------
   * A recursive function with memoization to compute the maximum points a ninja can earn
   * by performing one of three daily activities (0, 1, or 2), ensuring no activity is repeated
   * on two consecutive days.
   *
   * Parameters:
   * - points: A 2D vector where points[i][j] represents the points earned on day `i` for activity `j`.
   * - dp: A memoization table storing results for subproblems.
   * - day: The current day for which we're computing the maximum points.
   * - lastact: The index of the activity performed on the previous day (0, 1, or 2).
   *
   * Returns:
   * - The maximum points that can be earned from day 0 to `day` without repeating `lastact`.
   *
   * Time Complexity: O(n * 3) = O(n), where n is the number of days (because we memoize each subproblem).
   * Space Complexity: O(n * 3) for the memoization table.
   */
  int maxPoints(vector<vector<int>> &points, vector<vector<int>> &dp, int day, int lastact) {
      if (day < 0) {
          return 0; // No days left, no points to earn
      }

      if (dp[day][lastact] != -1)
          return dp[day][lastact]; // Return memoized result

      int maxP = INT_MIN;

      // Try all activities except the one done last time
      for (int i = 0; i < 3; i++) {
          if (lastact == i) continue; // Skip same activity as previous day

          // Choose activity i and add its points
          maxP = max(maxP, points[day][i] + maxPoints(points, dp, day - 1, i));
      }

      dp[day][lastact] = maxP; // Memoize and return result
      return maxP;
  }

  /*
   * Function: ninjaTraining
   * -----------------------
   * Driver function to compute the maximum points a ninja can earn over `n` days
   * following the no-consecutive-same-activity constraint.
   *
   * Parameters:
   * - n: Number of days
   * - points: 2D vector representing the points for each activity on each day
   *
   * Returns:
   * - The maximum total points achievable under the given constraints.
   *
   * Time Complexity: O(n * 3) = O(n), due to memoized recursion.
   * Space Complexity: O(n * 3), for the DP table.
   */
  int ninjaTraining(int n, vector<vector<int>> &points)
  {
    if (n == 1)
      return *max_element(points[0].begin(), points[0].end()); // Only one day, take the best activity

    // Initialize DP table with -1 (uncomputed)
    vector<vector<int>> dp(n, vector<int>(3, -1));

    int ans = INT_MIN;

    // Try all possible activities on the last day (n-1) and compute max points
    for (int i = 0; i < 3; i++)
    {
      ans = max(ans, points[n - 1][i] + maxPoints(points, dp, n - 2, i));
    }

    return ans;
  }

  //-------------------------------------------------------------------------------
  // 1. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
