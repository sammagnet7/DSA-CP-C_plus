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

1. Title: Climbing Stairs

Links:
https://takeuforward.org/data-structure/dynamic-programming-climbing-stairs/
https://takeuforward.org/plus/dsa/problems/climbing-stairs?tab=editorial
https://leetcode.com/problems/climbing-stairs/description/


Problem statement:
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Examples:
  Example 1:
  Input: n = 2
  Output: 2
  Explanation: There are two ways to climb to the top.
  1. 1 step + 1 step
  2. 2 steps

  Example 2:
  Input: n = 3
  Output: 3
  Explanation: There are three ways to climb to the top.
  1. 1 step + 1 step + 1 step
  2. 1 step + 2 steps
  3. 2 steps + 1 step


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
  /**
   * Approach 1: Recursion with Memoization (Top-Down DP)
   * ----------------------------------------------------
   * We use a recursive function to calculate the number of ways to reach the nth step,
   * but cache intermediate results using a dp array to avoid redundant computation.
   *
   * Time Complexity: O(N) — Each state from 1 to N is computed once.
   * Space Complexity: O(N) — For the recursion stack + dp array.
   */

  int stairs(int n, vector<int> &dp)
  {
    // Base case already computed
    if (dp[n] == -1)
    {
      // Compute and memoize result
      dp[n] = stairs(n - 1, dp) + stairs(n - 2, dp);
    }
    return dp[n];
  }

  int climbStairs(int n)
  {
    if (n == 1 || n == 2)
      return n;

    vector<int> dp(n + 1, -1); // dp[i] stores number of ways to reach step i

    dp[1] = 1;
    dp[2] = 2;

    return stairs(n, dp); // Compute using memoized recursion
  }

  /**
   * Approach 2: Tabulation (Bottom-Up DP)
   * -------------------------------------
   *
   * Calculates the number of distinct ways to reach step 'n'.
   *
   * Approach: Dynamic Programming (Tabulation / Bottom-Up)
   * We build an array 'DP' where DP[i] represents the number of distinct ways
   * to reach the i-th step.
   *
   * Logic:
   * To arrive at step 'i', you could have only come from:
   * 1. Step 'i-1' (by taking a 1-step jump)
   * 2. Step 'i-2' (by taking a 2-step jump)
   * Therefore: DP[i] = DP[i-1] + DP[i-2]
   *
   * Complexity Analysis:
   * - Time Complexity: O(N)
   * We iterate from 2 to N exactly once.
   * - Space Complexity: O(N)
   * We use a vector of size (N+1) to store the history of results.
   */
  int climbStairs(int n)
  {

    // Create a DP array of size n+1 to store ways for steps 0 to n.
    // Initialized to 0.
    vector<int> DP(n + 1, 0);

    // Base Cases:
    // DP[0] = 1: Technically represents "doing nothing" to stay at the bottom.
    // It acts as the mathematical anchor so that DP[2] = DP[0] + DP[1] = 1 + 1 = 2.
    DP[0] = 1;

    // DP[1] = 1: There is only 1 way to reach step 1 (take 1 step).
    DP[1] = 1;

    // Iterate from step 2 up to n
    for (int i = 2; i <= n; i++)
    {

      // The ways to reach step 'i' is the sum of ways to reach the
      // two possible previous steps.
      DP[i] = DP[i - 2] + DP[i - 1];
    }

    // Return the stored result for the target step 'n'
    return DP[n];
  }

  /**
   * Approach 3: Space Optimized Solution [OPTIMAL: Time + Space]
   * -------------------------------------------------------------
   * The problem follows the Fibonacci pattern. So instead of storing all results,
   * we only keep track of the last two computed values.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(1) — Only uses constant space.
   */

  int climbStairs(int n)
  {
    if (n == 1 || n == 2)
      return n;

    int top = 1;      // Ways to climb from step n
    int belowTop = 2; // Ways to climb from step n-1
    int cur = 0;

    // Build answer from step n-2 down to 1
    for (int i = n - 2; i > 0; i--)
    {
      cur = top + belowTop;
      top = belowTop;
      belowTop = cur;
    }

    return cur; // Ways to reach the top from step 1
  }
};

int main()
{
  return 0;
}
