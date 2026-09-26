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

  //------------------------
  // Approach 1: Recursive
  //------------------------

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

  //------------------------
  // Approach 2: Iterative
  //------------------------

  int minPathSum(vector<vector<int>> &grid)
  {

    int M = grid.size();
    int N = grid[0].size();

    vector<vector<int>> DP(M, vector<int>(N, 0));

    DP[0][0] = grid[0][0]; // init cell 0

    // init col 0
    for (int i = 1; i < M; i++)
    {
      DP[i][0] = grid[i][0] + DP[i - 1][0];
    }

    // init Row 0
    for (int j = 1; j < N; j++)
    {
      DP[0][j] = grid[0][j] + DP[0][j - 1];
    }

    // Build DP table bottom up
    for (int i = 1; i < M; i++)
    {
      for (int j = 1; j < N; j++)
      {

        DP[i][j] = grid[i][j] + min(DP[i - 1][j], DP[i][j - 1]);
      }
    }

    return DP[M - 1][N - 1];
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Minimum path sum in Triangular Grid
  //-------------------------------------------------------------------------------

  //----------------------------------------------------
  // Approach 1: Recursive [N*N DP table] [SUB-OPTIMAL]
  //----------------------------------------------------
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

  //----------------------------------------------------
  // Approach 2: Iterative [N*N DP table] [SUB-OPTIMAL]
  //----------------------------------------------------
  int minimumTotal(vector<vector<int>> &triangle)
  {

    int M = triangle.size();
    int N = M;

    vector<vector<int>> DP(M, vector<int>(N, 1e9)); // init with large number so that invalid cells gets ignored from MIN path sum calculation

    DP[0][0] = triangle[0][0]; // init top layer

    // init Col 0
    for (int i = 1; i < M; i++)
    {
      DP[i][0] = triangle[i][0] + DP[i - 1][0];
    }

    // Build DP table bottom-up
    for (int i = 1; i < M; i++)
    {
      for (int j = 1; j < (i + 1); j++)
      {

        DP[i][j] = triangle[i][j] + min(DP[i - 1][j], DP[i - 1][j - 1]);
      }
    }

    return *min_element(DP[M - 1].begin(), DP[M - 1].end());
  }

  //----------------------------------------------------
  // Approach 3: Iterative [N-length vector] [OPTIMAL]
  //----------------------------------------------------
  /*
   * Method: minimumTotal
   * --------------------
   * Finds the minimum path sum from top to bottom of a triangle.
   * * * Approach: Top-Down Dynamic Programming with Space Optimization
   * Instead of a full 2D DP matrix, we use two 1D arrays:
   * - 'prev': Stores path sums for the row directly above.
   * - 'cur':  Stores path sums we are currently calculating.
   * * * Logic:
   * For every element at triangle[i][j], the path comes from the minimum
   * of the two parents directly above it: (i-1, j) and (i-1, j-1).
   * Recurrence: cur[j] = triangle[i][j] + min(prev[j], prev[j-1])
   * * * Complexity:
   * - Time: O(N^2) (Total elements in triangle)
   * - Space: O(N) (Two rows of size N)
   */
  int minimumTotal(vector<vector<int>> &triangle)
  {

    int M = triangle.size();
    int N = M; // The last row has M elements, so max width is M.

    // Initialize with a large value (1e9) to represent Infinity.
    // This acts as a boundary guard for edges where a parent doesn't exist.
    vector<int> prev(N, 1e9);
    vector<int> cur(N, 1e9);

    // Base Case: The top of the triangle has only one path.
    prev[0] = triangle[0][0];

    // Iterate from the 2nd row (index 1) down to the bottom
    for (int i = 1; i < M; i++)
    {

      // 1. Handle Left Edge (j=0) separately
      // The first element of a row can ONLY come from the first element
      // of the previous row (directly above). No 'j-1' exists.
      cur[0] = triangle[i][0] + prev[0];

      // 2. Handle the rest of the row
      // Loop goes up to 'i' (inclusive), as row 'i' has 'i+1' elements.
      for (int j = 1; j < (i + 1); j++)
      {

        // Find the cheaper path from the two parents:
        // - prev[j]:   Directly above (conceptually up-right)
        // - prev[j-1]: Up-left
        // Note: For the Right Edge (j=i), prev[j] will be 1e9 (infinity)
        // because the parent row was shorter. This forces the logic to
        // correctly pick prev[j-1] (the only valid parent).
        cur[j] = triangle[i][j] + min(prev[j], prev[j - 1]);
      }

      // Move current row to previous for the next iteration
      prev = cur;
    }

    // The answer is the minimum value found in the last computed row
    return *min_element(prev.begin(), prev.end());
  }
};

int main()
{
  return 0;
}
