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

1. Title: Number of Ways to Paint N × 3 Grid

Links:
https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/description/?envType=daily-question&envId=2026-01-03


Problem statement:
You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).

Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.



Example 1:


Input: n = 1
Output: 12
Explanation: There are 12 possible way to paint the grid as shown.
Example 2:

Input: n = 5000
Output: 30228214


Constraints:

n == grid.length
1 <= n <= 5000



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Painting a Grid With Three Different Colors

Links:
https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description/


Problem statement:
You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.

Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.



Example 1:


Input: m = 1, n = 1
Output: 3
Explanation: The three possible colorings are shown in the image above.
Example 2:


Input: m = 1, n = 2
Output: 6
Explanation: The six possible colorings are shown in the image above.
Example 3:

Input: m = 5, n = 5
Output: 580986


Constraints:

1 <= m <= 5
1 <= n <= 1000


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Number of Ways to Paint N × 3 Grid
//-------------------------------------------------------------------------------

//---------------------------
// Approach: 1 [SUB-OPTIMAL]
//---------------------------

class Solution
{

  int MOD = 1e9 + 7;
  int CLR_COUNT = 3; // Red, Yellow, or Green

  // DP Table for Memoization.
  // Dimensions: [Row Index][Col 0 Color][Col 1 Color][Col 2 Color]
  // Stores the number of valid ways to complete the grid from 'rowIdx' onwards,
  // given the specific color configuration of the PREVIOUS row.
  // Size: 50001 rows * 27 color states per row.
  int DP[50001][3][3][3];

public:
  /**
   * Helper Function 1: Horizontal Recursion (Intra-Row)
   * * Approach:
   * This function attempts to color the 'curRow' one cell at a time (from col 0 to cols).
   * It ensures that the color chosen for the current cell does not conflict with:
   * 1. The cell directly above it (Vertical Constraint from prevRow).
   * 2. The cell directly to the left (Horizontal Constraint from curRow).
   * * @param rowIdx  Current row index.
   * @param colIdx  Current column index we are filling.
   * @param prevRow The colors of the previous completed row.
   * @param curRow  The row currently being built.
   */
  int recPerRow(int rowIdx, int colIdx, vector<int> &prevRow, vector<int> &curRow, int rows, int cols)
  {

    // Base Case: If we have filled all columns (0 to cols-1), the row is complete.
    // We now move to the next row using recInterRow.
    if (colIdx == cols)
    {
      return recInterRow(rowIdx + 1, curRow, rows, cols);
    }

    long long count = 0; // Use long long to prevent overflow during addition steps

    // Try all 3 colors (0: Red; 1: Yellow; 2: Green) for the current cell
    for (int clr = 0; clr < CLR_COUNT; clr++)
    {
      // Constraint Check:
      // 1. Vertical: prevRow[colIdx] == clr
      // 2. Horizontal: curRow[colIdx-1] == clr (only if colIdx > 0)
      if (prevRow[colIdx] == clr || (colIdx > 0 && curRow[colIdx - 1] == clr))
      {
        continue; // Skip invalid colors
      }
      else
      {
        // Assign valid color
        curRow[colIdx] = clr;

        // Recurse to fill the next cell in the SAME row
        int ret = recPerRow(rowIdx, colIdx + 1, prevRow, curRow, rows, cols);

        // Accumulate results modulo MOD
        count = (count + (ret % MOD)) % MOD;

        // Backtrack: Reset cell for next iteration
        curRow[colIdx] = -1;
      }
    }

    return count;
  }

  /**
   * Helper Function 2: Vertical Recursion (Inter-Row)
   * * Approach:
   * This function handles the transition from a completed row to the start of a new row.
   * It uses Memoization to store the result based on the state of the 'prevRow'.
   * * @param rowIdx   The index of the row we are about to start filling.
   * @param prevRow  The configuration of the row immediately above rowIdx.
   */
  int recInterRow(int rowIdx, vector<int> &prevRow, int rows, int cols)
  {

    // Base Case: If rowIdx reaches 'rows', we successfully painted the whole grid.
    if (rowIdx == rows)
    {
      return 1;
    }

    // Memoization Check:
    // If we have calculated this state (rowIdx + specific prevRow configuration), return it.
    // rowIdx > 0 check ensures we don't access DP with the dummy initial row.
    if (rowIdx > 0 && DP[rowIdx][prevRow[0]][prevRow[1]][prevRow[2]] != -1)
    {
      return DP[rowIdx][prevRow[0]][prevRow[1]][prevRow[2]];
    }

    // Create an empty vector for the current row to be filled
    vector<int> curRow(cols, -1);

    // Start filling the current row from column 0
    int ret = recPerRow(rowIdx, 0, prevRow, curRow, rows, cols);

    // Store the result in DP table
    // We index the DP state by the colors of 'prevRow' because they determine the constraints for 'rowIdx'.
    if (rowIdx > 0)
    {
      DP[rowIdx][prevRow[0]][prevRow[1]][prevRow[2]] = ret;
    }

    return ret;
  }

  /**
   * Main Function
   * * Algorithm: Profile Dynamic Programming (DP on Broken Profile)
   * We build the grid row by row, keeping track of the previous row's colors to enforce constraints.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * There are N rows. For each row, there are 3^3 = 27 possible states for the previous row.
   * For each state, we try to form a valid current row (constant number of ways, approx 12).
   * Total operations ~ N * 27 * 12.
   * * - Space Complexity: O(N)
   * The DP table size is 50001 * 27 integers (~5.4 MB), which fits in memory.
   */
  int numOfWays(int n)
  {
    int rows = n;
    int cols = 3;

    // Initialize DP table with -1
    memset(DP, -1, sizeof(DP));

    // Create a dummy previous row initialized with -1.
    // This ensures the first actual row (row 0) has no vertical conflicts.
    vector<int> row(cols, -1);

    return recInterRow(0, row, rows, cols);
  }
};

//------------------------
// Approach: 2 [OPTIMAL]
//------------------------

class Solution
{
public:
  /**
   * Calculates the number of ways to paint an N x 3 grid with 3 colors.
   * * Approach: Dynamic Programming with State Optimization
   * We classify row colorings into two types:
   * 1. ABA: Uses 2 colors (indices 0 and 2 are same). e.g., 121
   * 2. ABC: Uses 3 colors (all distinct). e.g., 123
   * * Transitions derived from combinatorics:
   * - A row of type ABA can be followed by: 3 ABA rows and 2 ABC rows.
   * - A row of type ABC can be followed by: 2 ABA rows and 2 ABC rows.
   * * Complexity:
   * Time: O(N) - Single loop from 1 to N.
   * Space: O(1) - We only store the counts for the current iteration.
   */
  int numOfWays(int n)
  {
    long long cur_aba = 6;
    long long cur_abc = 6;
    long long mod = 1e9 + 7;

    // Iterate from row 2 to n
    for (int i = 2; i <= n; i++)
    {
      long long next_aba = (3 * cur_aba + 2 * cur_abc) % mod;
      long long next_abc = (2 * cur_aba + 2 * cur_abc) % mod;

      cur_aba = next_aba;
      cur_abc = next_abc;
    }

    return (cur_aba + cur_abc) % mod;
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Painting a Grid With Three Different Colors
//-------------------------------------------------------------------------------

class Solution
{

  int MOD = 1e9 + 7;
  int CLR_COUNT = 3; // Red, Yellow, or Green

  // Max states for a column of height 5 using 3 colors is 3^5 = 243.
  // This constant defines the size of the DP table's second dimension.
  static const int maxDPindices = 243;

  // DP Table for Memoization.
  // Dimensions: [Column Index (0 to 1000)] [Compressed State of Previous Column (0 to 242)]
  // DP[col][mask] stores the number of ways to color the remaining grid (cols 'col' to 'n')
  // given that the previous column (col-1) had the color configuration represented by 'mask'.
  int DP[1001][maxDPindices];

public:
  /**
   * Helper Function: Intra-Column Recursion (DFS)
   * * Approach:
   * This function attempts to build the 'curCol' (current column) one cell (row) at a time.
   * It acts as a generator that produces valid column configurations that are compatible
   * with the 'prevCol'.
   * * Conflict Checks:
   * 1. Horizontal: The current cell must not match the neighbor to the left (prevCol[rowIdx]).
   * 2. Vertical: The current cell must not match the neighbor above (curCol[rowIdx-1]).
   * * @param rowIdx  Current row index within the column we are filling.
   * @param colIdx  The index of the column we are currently filling.
   * @param prevCol The configuration of the fully completed column to the left.
   * @param curCol  The current column we are building.
   * @param rows    Total number of rows (m).
   * @param cols    Total number of columns (n).
   * @return        Count of valid ways to complete the rest of the grid given the current partial column.
   */
  int recPerCol(int rowIdx, int colIdx, vector<int> &prevCol, vector<int> &curCol, int rows, int cols)
  {

    // Base Case: If we have filled all rows (0 to rows-1) for the current column,
    // the column is complete and valid. We then transition to the next column.
    if (rowIdx == rows)
    {
      return recInterCol(colIdx + 1, curCol, rows, cols);
    }

    long long count = 0;

    // Try assigning each of the 3 colors (0: Red, 1: Yellow, 2: Green) to the current cell
    for (int clr = 0; clr < CLR_COUNT; clr++)
    {

      // Check for conflicts:
      // 1. prevCol[rowIdx] == clr: Checks collision with the Left neighbor.
      // 2. (rowIdx>0 && curCol[rowIdx-1]==clr): Checks collision with the Upper neighbor.
      if (prevCol[rowIdx] == clr || (rowIdx > 0 && curCol[rowIdx - 1] == clr))
      {
        continue; // Skip invalid color
      }
      else
      {
        // Assign valid color
        curCol[rowIdx] = clr;

        // Recurse to fill the next row in the SAME column
        int ret = recPerCol(rowIdx + 1, colIdx, prevCol, curCol, rows, cols);

        // Add valid paths found to local count, applying Modulo
        count = (count + (ret % MOD)) % MOD;

        // Backtrack: Reset cell for the next iteration
        curCol[rowIdx] = -1;
      }
    }

    return count;
  }

  /**
   * Main DP Function: Inter-Column Recursion
   * * Approach:
   * This function handles the transition from one completed column to the start of the next.
   * It uses State Compression (Base-3 integer) to memoize the results based on the
   * configuration of the 'prevCol'.
   * * Complexity Analysis:
   * - Time Complexity: O(N * 3^M)
   * There are N columns. For each column, there are 3^M possible states for 'prevCol'.
   * The transition (recPerCol) takes constant time relative to N (since M <= 5).
   * - Space Complexity: O(N * 3^M)
   * For the DP table size (1000 * 243 integers).
   * * @param colIdx  The index of the column we are about to start filling.
   * @param prevCol The color configuration of the column immediately to the left.
   */
  int recInterCol(int colIdx, vector<int> &prevCol, int rows, int cols)
  {

    // Base Case: If we have processed all columns (0 to cols-1),
    // we have found 1 valid full grid coloring.
    if (colIdx == cols)
    {
      return 1;
    }

    // --- State Compression ---
    // Convert the 'prevCol' vector (size M) into a unique integer hash (Base-3).
    // Example: prevCol = {0, 1, 2} -> 0*3^0 + 1*3^1 + 2*3^2
    int DPindex = 0;
    int powerOf3 = 1;

    // Only calculate index if we aren't at the very first column (which has no prevCol)
    if (colIdx > 0)
    {
      for (int i = 0; i < rows; i++)
      {
        // prevCol values are 0, 1, 2. This creates a unique hash.
        DPindex += (prevCol[i] * powerOf3);
        powerOf3 *= 3;
      }
    }

    // --- Memoization Check ---
    // If we have already computed the result for this column index and previous pattern, return it.
    if (colIdx > 0 && DP[colIdx][DPindex] != -1)
    {
      return DP[colIdx][DPindex];
    }

    // Prepare a new empty column to be filled
    vector<int> curCol(rows, -1);

    // Start the intra-column recursion (DFS) to fill 'curCol' from row 0
    int ret = recPerCol(0, colIdx, prevCol, curCol, rows, cols);

    // --- Store Result ---
    // Save the result in the DP table for future lookups
    if (colIdx > 0)
    {
      DP[colIdx][DPindex] = ret;
    }

    return ret;
  }

  int colorTheGrid(int m, int n)
  {

    int rows = m;
    int cols = n;

    // Initialize DP table with -1 (indicating uncomputed states)
    memset(DP, -1, sizeof(DP));

    // Create a dummy "previous column" for the first column.
    // Initialized to -1 so it won't conflict with any color in the first column.
    vector<int> col(rows, -1);

    // Start recursion from Column 0
    return recInterCol(0, col, rows, cols);
  }
};

/*
  Summary:
  For M <=3: You can memorize the math formulas (ABA/ABC).
  For M > 3: Use the Profile DP code. It essentially "auto-discovers" the math formulas for you.
*/

int main()
{
  return 0;
}
