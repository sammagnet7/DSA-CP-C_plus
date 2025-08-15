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

1. Title: Minimum path sum in Grid

Links:
https://takeuforward.org/data-structure/minimum-path-sum-in-a-grid-dp-10/
https://leetcode.com/problems/minimum-path-sum/description/


Problem statement:
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.

Example 1:
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1,2,3],[4,5,6]]
Output: 12


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Minimum path sum in Triangular Grid

Links:
https://takeuforward.org/data-structure/minimum-path-sum-in-triangular-grid-dp-11/
https://takeuforward.org/plus/dsa/problems/triangle?tab=editorial
https://leetcode.com/problems/triangle/description/


Problem statement:
Given a triangle array, return the minimum path sum from top to bottom.
For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:
Input: triangle = [[-10]]
Output: -10

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Minimum path sum in Grid
  //-------------------------------------------------------------------------------

  /*
   * Function: minPath
   * -----------------
   * A helper recursive function with memoization to compute the minimum path sum
   * from the top-left (0, 0) to a given cell (m, n) in the grid.
   *
   * Parameters:
   * - grid: 2D grid of non-negative integers representing the cost at each cell.
   * - dp: 2D memoization table to store minimum path sum to each cell.
   * - m: Current row index.
   * - n: Current column index.
   *
   * Returns:
   * - Minimum path sum to reach cell (m, n).
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n) for the DP table and recursion stack.
   */
  int minPath(vector<vector<int>> &grid, vector<vector<int>> &dp, int m, int n)
  {
    // If already computed, return the cached value
    if (dp[m][n] != -1)
      return dp[m][n];

    // Base Case: Starting cell (0, 0)
    if (m == 0 && n == 0)
    {
      return dp[m][n] = grid[m][n];
    }

    // If on the first row, can only come from the left
    if (m == 0)
    {
      return dp[m][n] = minPath(grid, dp, m, n - 1) + grid[m][n];
    }

    // If on the first column, can only come from the top
    if (n == 0)
    {
      return dp[m][n] = minPath(grid, dp, m - 1, n) + grid[m][n];
    }

    // Recursive calls: one from top, one from left
    int up = minPath(grid, dp, m - 1, n);
    int left = minPath(grid, dp, m, n - 1);

    // Store and return the result
    return dp[m][n] = grid[m][n] + min(up, left);
  }

  /*
   * Function: minPathSum
   * --------------------
   * Computes the minimum path sum from the top-left to bottom-right of a grid.
   * Only moves allowed are right or down.
   *
   * Parameters:
   * - grid: 2D grid of non-negative integers.
   *
   * Returns:
   * - Minimum total path sum.
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int minPathSum(vector<vector<int>> &grid)
  {
    int M = grid.size();
    int N = grid[0].size();

    // DP table initialized with -1 for memoization
    vector<vector<int>> dp(M, vector<int>(N, -1));

    // Start recursion from bottom-right cell
    return minPath(grid, dp, M - 1, N - 1);
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Minimum path sum in Triangular Grid
  //-------------------------------------------------------------------------------

  /*
   * Function: minPath
   * -----------------
   * A top-down recursive approach with memoization (DP) to find the minimum path sum.
   * From each level, you can move to the index directly below or the one diagonally right.
   *
   * Parameters:
   * - triangle: The 2D vector representing the triangle.
   * - dp: 2D DP table storing results to avoid recomputation.
   * - N: Total number of rows in the triangle.
   * - lv: Current level (row).
   * - idx: Current index in the level.
   *
   * Returns:
   * - Minimum path sum starting from triangle[lv][idx] to the bottom.
   *
   * Time Complexity: O(N^2) - Each state (lv, idx) is computed only once.
   * Space Complexity: O(N^2) - For DP table + O(N) recursion stack.
   */
  int minPath(vector<vector<int>> &triangle, vector<vector<int>> &dp, int N, int lv, int idx)
  {
    if (dp[lv][idx] != -1)
      return dp[lv][idx];

    // Base case: last level
    if (lv == N - 1)
      return dp[lv][idx] = triangle[lv][idx];

    // Recursive calls for downward and diagonal moves
    int op1 = minPath(triangle, dp, N, lv + 1, idx);     // move straight down
    int op2 = minPath(triangle, dp, N, lv + 1, idx + 1); // move diagonally

    return dp[lv][idx] = triangle[lv][idx] + min(op1, op2);
  }

  /*
   * Function: minimumTotal
   * ----------------------
   * Entry point for Approach 1 (Top-Down Recursive DP)
   */
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int N = triangle.size();

    vector<vector<int>> dp(N, vector<int>(N, -1)); // DP table

    return minPath(triangle, dp, N, 0, 0); // Start from top
  }

  /*
   *   [OPTIMAL]
   * Function: minimumTotal
   * ----------------------
   * A bottom-up tabulation approach with space optimization.
   * Computes the minimum path sum from top to bottom, level by level.
   *
   * Time Complexity: O(N^2)
   * Space Complexity: O(N) - Using only one 1D vector to store DP state.
   *
   * At each level, compute the minimum cost to reach each position
   * by checking valid positions from the previous level.
   */
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int N = triangle.size();

    // Initialize DP for level 0
    vector<int> lvDP(1);
    lvDP[0] = triangle[0][0];

    // Build DP level by level
    for (int lv = 1; lv < N; lv++)
    {
      int lvSize = triangle[lv].size();

      vector<int> tmp(lvSize, -1); // temp storage for current level

      for (int j = 0; j < lvSize; j++)
      {
        int opt1 = (j == lvSize - 1) ? INT_MAX : lvDP[j]; // from above
        int opt2 = (j - 1 < 0) ? INT_MAX : lvDP[j - 1];   // from left-diagonal

        tmp[j] = triangle[lv][j] + min(opt1, opt2);
      }

      lvDP = tmp; // update for next level
    }

    return *min_element(lvDP.begin(), lvDP.end()); // find minimum path to bottom
  }
};

int main()
{
  return 0;
}
