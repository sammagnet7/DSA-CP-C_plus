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

1. Title: House Robber

Links:
https://takeuforward.org/data-structure/maximum-sum-of-non-adjacent-elements-dp-5/
https://takeuforward.org/plus/dsa/problems/maximum-sum-of-non-adjacent-elements?tab=editorial
https://leetcode.com/problems/house-robber/description/


Problem statement:
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Examples:
  Example 1:
  Input: nums = [1,2,3,1]
  Output: 4
  Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
  Total amount you can rob = 1 + 3 = 4.

  Example 2:
  Input: nums = [2,7,9,3,1]
  Output: 12
  Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
  Total amount you can rob = 2 + 9 + 1 = 12.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: House Robber II

Links:
https://takeuforward.org/data-structure/dynamic-programming-house-robber-dp-6/
https://takeuforward.org/plus/dsa/problems/house-robber?tab=editorial
https://leetcode.com/problems/house-robber-ii/description/


Problem statement:
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Examples:
  Example 1:
  Input: nums = [2,3,2]
  Output: 3
  Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

  Example 2:
  Input: nums = [1,2,3,1]
  Output: 4
  Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
  Total amount you can rob = 1 + 3 = 4.

  Example 3:
  Input: nums = [1,2,3]
  Output: 3


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: House Robber
  //-------------------------------------------------------------------------------

  /**
   * Approach 1: Recursion with Memoization
   * --------------------------------------
   * For each house at index `idx`, we make two choices:
   * - Rob it: add nums[idx] + total from idx+2
   * - Skip it: take total from idx+1
   *
   * We use memoization to store results of subproblems to avoid recomputation.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(N) — due to recursion stack and memoization array
   */
  int totalRob(vector<int> &nums, int idx, vector<int> &dp)
  {
    if (idx >= nums.size())
      return 0;
    if (dp[idx] != -1)
      return dp[idx];

    // Choose to rob current house or skip
    int withRob = nums[idx] + totalRob(nums, idx + 2, dp);
    int withoutRob = totalRob(nums, idx + 1, dp);

    return dp[idx] = max(withRob, withoutRob);
  }

  int rob(vector<int> &nums)
  {
    vector<int> dp(nums.size(), -1);
    return totalRob(nums, 0, dp);
  }

  /**
   * Approach 2: Tabulation (Bottom-Up DP)
   * -------------------------------------
   * Build the solution iteratively using a DP array.
   *
   * dp[i] = max money we can rob from house 0 to i.
   * For each house, decide:
   * - Rob it: nums[i] + dp[i-2]
   * - Skip it: dp[i-1]
   *
   * Time Complexity: O(N)
   * Space Complexity: O(N)
   */
  int rob(vector<int> &nums)
  {
    int N = nums.size();
    if (N == 1)
      return nums[0];

    vector<int> dp(N);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < N; i++)
    {
      int withRob = nums[i] + dp[i - 2];
      int withoutRob = dp[i - 1];
      dp[i] = max(withRob, withoutRob);
    }

    return dp[N - 1];
  }

  /**
   * Approach 3: Space Optimized DP
   * ------------------------------
   * We only need the last two states at any time, so we can reduce space to O(1).
   *
   * Time Complexity: O(N)
   * Space Complexity: O(1)
   */
  int rob(vector<int> &nums)
  {
    int N = nums.size();
    if (N == 1)
      return nums[0];

    int first = nums[0];                // dp[i-2]
    int second = max(nums[0], nums[1]); // dp[i-1]

    for (int i = 2; i < N; i++)
    {
      int withRob = nums[i] + first;
      int withoutRob = second;

      first = second;
      second = max(withRob, withoutRob);
    }

    return second;
  }

  //-------------------------------------------------------------------------------
  // 1. Title: House Robber II
  //-------------------------------------------------------------------------------

  //---------------------------------
  // Approach 2: SUB-OPTIMAL [Space]
  //---------------------------------

  /*
   * Method: rob
   * -----------
   * Solves the Circular House Robber problem.
   * * * Approach: Decomposition into Linear Cases
   * Since the first and last houses are neighbors, we cannot rob both.
   * This breaks the problem into two mutually exclusive scenarios:
   * 1. Case A (DP1): Ignore the First House (Index 0). Rob from range [1 to N-1].
   * 2. Case B (DP2): Ignore the Last House (Index N-1). Rob from range [0 to N-2].
   * * The answer is simply max(Case A, Case B).
   * * * Complexity Analysis:
   * - Time Complexity: O(N)
   * We iterate through the array twice (once for each scenario).
   * - Space Complexity: O(N)
   * We use two DP arrays of size N.
   * (Note: This could be optimized to O(1) space by using variables instead of arrays).
   */
  int rob(vector<int> &nums)
  {

    int N = nums.size();

    // Edge Case: Only 1 house. The "circular" constraint doesn't exist yet.
    if (N == 1)
    {
      return nums[0];
    }
    // Edge Case: 2 houses. They are neighbors, so pick the max.
    if (N == 2)
    {
      return max(nums[0], nums[1]);
    }

    // DP Arrays for the two scenarios
    vector<int> DP1(N, 0); // Scenario 1: Range [1...N-1] (Include Last, Exclude First)
    vector<int> DP2(N, 0); // Scenario 2: Range [0...N-2] (Include First, Exclude Last)

    // -------------------------------------------------------
    // Scenario 1: Solve for Range [1 to N-1]
    // We implicitly skip nums[0] by initializing DP1[0] to 0
    // and treating index 1 as the effective start.
    // -------------------------------------------------------

    // Base case relative to this sub-problem:
    DP1[0] = 0;       // Dummy value (Skipping index 0)
    DP1[1] = nums[1]; // First house of this range

    // Standard House Robber logic for the rest
    for (int i = 2; i <= N - 1; i++)
    {
      // Option 1: Rob current 'i' + loot from 'i-2'
      // Note: DP1[i-2] is valid because we initialized DP1[0]=0
      int take = nums[i] + DP1[i - 2];

      // Option 2: Skip current 'i', take loot from 'i-1'
      int notTake = DP1[i - 1];

      DP1[i] = max(take, notTake);
    }

    // -------------------------------------------------------
    // Scenario 2: Solve for Range [0 to N-2]
    // We proceed normally but STOP before the last element (N-1).
    // -------------------------------------------------------

    // Base cases for standard House Robber starting at 0:
    DP2[0] = nums[0];
    DP2[1] = max(nums[0], nums[1]); // Standard logic: max of first two

    // Loop stops at N-2 (strictly excluding the last house)
    for (int i = 2; i <= N - 2; i++)
    {

      int take = nums[i] + DP2[i - 2];
      int notTake = DP2[i - 1];

      DP2[i] = max(take, notTake);
    }

    // -------------------------------------------------------
    // Final Result
    // Compare the best result from Scenario 1 (ending at N-1)
    // and Scenario 2 (ending at N-2).
    // -------------------------------------------------------
    return max(DP1[N - 1], DP2[N - 2]);
  }

  //-----------------------------
  // Approach 2: OPTIMAL [Space]
  //-----------------------------

  /**
   * Function: rob
   * Problem: Leetcode 213 - House Robber II
   *
   * Description:
   * In a circular arrangement of houses, determine the maximum amount of money
   * that can be robbed such that no two adjacent houses are robbed.
   *
   * Approach:
   * 1. Since the first and last houses are adjacent, we cannot rob both.
   * 2. So, we solve the problem twice:
   *    - Case 1: Rob from house 0 to n-2 (exclude last house)
   *    - Case 2: Rob from house 1 to n-1 (exclude first house)
   * 3. Use space-optimized dynamic programming for both cases.
   * 4. Return the maximum of the two cases.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(1)
   */

  int rob(vector<int> &nums)
  {
    int N = nums.size();

    // Base cases
    if (N == 1)
      return nums[0];
    if (N == 2)
      return max(nums[0], nums[1]);

    // Case 1: Rob houses from index 0 to N-2 (excluding the last house)
    int first = nums[0];                // dp[i-2]
    int second = max(nums[0], nums[1]); // dp[i-1]

    for (int i = 2; i < N - 1; i++)
    {
      int withRob = nums[i] + first; // Rob current + dp[i-2]
      int withoutRob = second;       // Skip current, take dp[i-1]
      first = second;
      second = max(withRob, withoutRob); // Update to max of both choices
    }

    int wFirst = second; // Max profit excluding last house

    // Case 2: Rob houses from index 1 to N-1 (excluding the first house)
    first = nums[1];
    second = max(nums[1], nums[2]);

    for (int i = 3; i < N; i++)
    {
      int withRob = nums[i] + first;
      int withoutRob = second;
      first = second;
      second = max(withRob, withoutRob);
    }

    int woFirst = second; // Max profit excluding first house

    // Return the best of both scenarios
    return max(wFirst, woFirst);
  }
};

int main()
{
  return 0;
}
