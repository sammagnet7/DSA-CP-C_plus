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

1. Title: Minimum Falling Path Sum

Links:
https://takeuforward.org/data-structure/minimum-maximum-falling-path-sum-dp-12/
https://www.youtube.com/watch?v=N_aJ5qQbYA0
https://takeuforward.org/plus/dsa/problems/minimum-falling-path-sum?tab=editorial
https://leetcode.com/problems/minimum-falling-path-sum/description/


Problem statement:
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).


Example 1:
Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:
Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.


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
  // 1. Title: Minimum Falling Path Sum
  //-------------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Approach1:
  //----------------------------------------------------------------------------

  // Recursive helper function to calculate the minimum falling path sum to cell (m, n)
  // Parameters:
  // - matrix: the input grid
  // - dp: memoization table
  // - N: number of rows/columns in the square matrix
  // - m: current row
  // - n: current column
  //
  // Time Complexity: O(N^2) – each cell is computed once and cached
  // Space Complexity: O(N^2) for dp table + O(N) recursion stack (in worst case)

  int minFall(vector<vector<int>> &matrix, vector<vector<int>> &dp, int N, int m, int n)
  {

    // If out of bounds (column), return INT_MAX to ignore this path
    if (n < 0 || n >= N)
      return INT_MAX;

    // If reached top row, base case: return the cell value
    if (m == 0)
      return dp[m][n] = matrix[m][n];

    // If already computed, return memoized result
    if (dp[m][n] != -1)
      return dp[m][n];

    // Recursively compute min path sum from three directions
    int upLeft = minFall(matrix, dp, N, m - 1, n - 1);
    int up = minFall(matrix, dp, N, m - 1, n);
    int upRight = minFall(matrix, dp, N, m - 1, n + 1);

    // Store and return the minimum path sum to cell (m, n)
    return dp[m][n] = matrix[m][n] + min({upLeft, up, upRight});
  }

  // Main function using the recursive memoized helper
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int N = matrix.size();

    // Initialize memoization table
    vector<vector<int>> dp(N, vector<int>(N, -1));

    int minPath = INT_MAX;

    // Try starting from each cell in the last row
    for (int i = 0; i < N; i++)
    {
      minPath = min(minPath, minFall(matrix, dp, N, N - 1, i));
    }

    return minPath;
  }

  //----------------------------------------------------------------------------
  // Approach2:
  //----------------------------------------------------------------------------

  // Bottom-up approach with space optimization
  // Fills row-by-row from top to bottom, only maintaining the last computed row
  //
  // Time Complexity: O(N^2) – every cell is visited once
  // Space Complexity: O(N) – only two rows (current and previous) are stored
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int N = matrix.size();

    vector<int> prevRow;

    for (int i = 0; i < N; i++)
    {
      vector<int> curRow(N, INT_MAX); // current row for dp values

      for (int j = 0; j < N; j++)
      {
        // For the first row, base case is just the cell values
        if (i == 0)
        {
          curRow[j] = matrix[0][j];
          continue;
        }

        // For other rows, compute min path from the three possible directions
        for (int k = -1; k <= 1; k++)
        {
          int prevRowIdx = j + k;

          if (prevRowIdx < 0 || prevRowIdx >= N)
            continue;

          curRow[j] = min(curRow[j], matrix[i][j] + prevRow[prevRowIdx]);
        }
      }

      // Update prevRow to current for next iteration
      prevRow = curRow;
    }

    // The answer is the minimum value in the last computed row
    return *min_element(prevRow.begin(), prevRow.end());
  }

  //-------------------------------------------------------------------------------
  // 1. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
