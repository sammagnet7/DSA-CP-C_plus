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

1. Title: Unique Paths

Links:
https://www.youtube.com/watch?v=sdE0A2Oxofw
https://takeuforward.org/data-structure/grid-unique-paths-dp-on-grids-dp8/
https://takeuforward.org/plus/dsa/problems/grid-unique-paths?tab=editorial
https://leetcode.com/problems/unique-paths/description/


Problem statement:
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The test cases are generated so that the answer will be less than or equal to 2 * 109.

Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Unique Paths II

Links:
https://takeuforward.org/data-structure/grid-unique-paths-2-dp-9/
https://takeuforward.org/plus/dsa/problems/unique-paths-ii?tab=editorial
https://leetcode.com/problems/unique-paths-ii/description/


Problem statement:
You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.
Return the number of possible unique paths that the robot can take to reach the bottom-right corner.


Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Unique Paths
  //-------------------------------------------------------------------------------

  /*
   * Function: totalPaths
   * --------------------
   * A recursive helper function with memoization to calculate the number of unique paths
   * from the top-left corner (0, 0) to the bottom-right corner (m-1, n-1) in a grid,
   * moving only right or down.
   *
   * Parameters:
   * - dp: A memoization table where dp[i][j] stores the number of unique paths from cell (i, j) to bottom-right.
   * - m, n: Dimensions of the grid.
   * - p, q: Current position in the grid.
   *
   * Returns:
   * - The number of unique paths from (p, q) to (m-1, n-1).
   *
   * Time Complexity: O(m * n) — each cell is visited once due to memoization.
   * Space Complexity: O(m * n) — for the dp table and recursion stack.
   */
  int totalPaths(vector<vector<int>> &dp, int m, int n, int p, int q)
  {
    // Base case: reached bottom-right corner, one valid path found
    if (p == m - 1 && q == n - 1)
    {
      return dp[p][q] = 1;
    }
    // Out of bounds, invalid path
    else if (p >= m || q >= n)
    {
      return 0;
    }

    // Return cached result if already computed
    if (dp[p][q] != -1)
    {
      return dp[p][q];
    }

    // Explore both directions: right (p, q+1) and down (p+1, q)
    return dp[p][q] = totalPaths(dp, m, n, p + 1, q) + totalPaths(dp, m, n, p, q + 1);
  }

  /*
   * Function: uniquePaths (Recursive + Memoization)
   * -----------------------------------------------
   * Calculates the number of unique paths in an m x n grid using top-down DP.
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int uniquePaths(int m, int n)
  {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return totalPaths(dp, m, n, 0, 0); // Start from top-left cell
  }

  /*
   * Function: uniquePaths (Tabulation)
   * ----------------------------------
   * Uses bottom-up dynamic programming to count unique paths from (0,0) to (m-1,n-1),
   * moving only down or right.
   *
   * dp[i][j] = number of paths to reach cell (i, j)
   * The number of ways to reach any cell is the sum of ways to reach from top (i-1, j)
   * and from left (i, j-1).
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int uniquePaths(int m, int n)
  {
    if (m == 1 || n == 1)
      return 1;

    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Fill the rest of the table
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        // Base condition
        if (i == 0 || j == 0)
        {
          dp[i][j] = 1;
          /* Skip the rest of the loop and
          continue with the next iteration.*/
          continue;
        }

        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }

    return dp[m - 1][n - 1]; // Return paths to bottom-right
  }

  //-------------------------------------------------------------------------------
  // 1. Title: Unique Paths II
  //-------------------------------------------------------------------------------

  /*
   * Function: uniquePathsWithObstacles
   * ----------------------------------
   * Calculates the number of unique paths in a grid from the top-left to bottom-right,
   * while avoiding obstacles. Movement is allowed only right or down.
   *
   * Each cell in `obstacleGrid` can be:
   * - 0: Free cell
   * - 1: Obstacle (cannot be passed through)
   *
   * Parameters:
   * - obstacleGrid: 2D grid representing obstacles and free paths
   *
   * Returns:
   * - The number of unique paths from (0,0) to (m-1,n-1) while avoiding obstacles
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
  {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    // DP table to store the number of ways to reach each cell
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Initialize first column: only fill cells until obstacle is hit
    for (int i = 0; i < m; i++)
    {
      if (obstacleGrid[i][0] == 1)
        break;      // All cells below this are unreachable
      dp[i][0] = 1; // Only one way to reach (i,0): all down moves
    }

    // Initialize first row: only fill cells until obstacle is hit
    for (int j = 0; j < n; j++)
    {
      if (obstacleGrid[0][j] == 1)
        break;      // All cells to the right are unreachable
      dp[0][j] = 1; // Only one way to reach (0,j): all right moves
    }

    // Fill the rest of the DP table
    for (int i = 1; i < m; i++)
    {
      for (int j = 1; j < n; j++)
      {
        if (obstacleGrid[i][j] == 1)
        {
          dp[i][j] = 0; // If obstacle, no path through this cell
        }
        else
        {
          // Sum of paths from top and left cells
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }

    // Result is the number of ways to reach the bottom-right cell
    return dp[m - 1][n - 1];
  }
};

int main()
{
  return 0;
}
