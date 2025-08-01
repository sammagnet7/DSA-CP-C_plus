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
  //-------------------------------------------------------------------------------
  // 1. Title: Climbing Stairs
  //-------------------------------------------------------------------------------

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
   * We build the solution from the base cases up to n using a dp table.
   * This avoids recursion and is more efficient in terms of call stack.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(N)
   */

  int climbStairs(int n)
  {
    if (n == 1)
      return 1;

    vector<int> dp(n + 1); // dp[i] = number of ways to reach step i

    dp[n] = 1;     // One way to stand on step n (base case)
    dp[n - 1] = 2; // Two ways to reach step n-1: either step 1 or step 2 at once

    // Build dp from n-2 down to 1
    for (int i = n - 2; i > 0; i--)
    {
      dp[i] = dp[i + 1] + dp[i + 2];
    }

    return dp[1]; // Start from step 1 to climb up
  }

  /**
   * Approach 3: Space Optimized Solution [OPTIMAL]
   * ------------------------------------
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
