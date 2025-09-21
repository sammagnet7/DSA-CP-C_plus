#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Set Matrix Zero

https://takeuforward.org/data-structure/set-matrix-zero/
https://leetcode.com/problems/set-matrix-zeroes/description/
https://www.naukri.com/code360/problems/zero-matrix_1171153?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_Arrayproblems

Problem Statement: Given a matrix if an element in the matrix is 0 then you will have to set its entire column and row to 0 and then return the matrix.

Note:
-231 <= matrix[i][j] <= 231 - 1
You must do it in place.

Examples:

Examples 1:
Input:
 matrix=[[1,1,1],[1,0,1],[1,1,1]]
Output:
 [[1,0,1],[0,0,0],[1,0,1]]
Explanation:
 Since matrix[2][2]=0.Therfore the 2nd column and 2nd row wil be set to 0.

Input:
 matrix=[[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output:
[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
Explanation:
Since matrix[0][0]=0 and matrix[0][3]=0. Therefore 1st row, 1st column and 4th column will be set to 0

INPUT::::::
2

3 3
1 1 1
1 0 1
1 1 1

3 4
0 1 2 0
3 4 5 2
1 3 1 5

OUTPUT::::::

1 0 1
0 0 0
1 0 1

0 0 0 0
0 4 5 0
0 3 1 0
 */

class Solution
{
public:
    /**
     * Set Matrix Zeroes — Better Approach
     * -----------------------------------
     * Problem:
     *   - Given an m x n matrix, if an element is 0,
     *     set its entire row and column to 0 (in-place).
     *
     * Approach:
     *   - Use two auxiliary arrays:
     *       rows[i] = 0 if row i contains at least one 0
     *       cols[j] = 0 if column j contains at least one 0
     *   - Step 1: Scan the matrix and mark rows/cols that must be zeroed.
     *   - Step 2: Traverse matrix again and set cell (i,j) = 0
     *             if rows[i] == 0 or cols[j] == 0.
     *
     * Why this works with negatives:
     *   - We explicitly store row/col markers in separate arrays,
     *     instead of trying to modify the matrix in-place during scanning,
     *     so negative values don’t interfere with detection.
     *
     * Time Complexity:  O(m * n)   [two full traversals of matrix]
     * Space Complexity: O(m + n)   [two auxiliary arrays]
     *
     * Note:
     *   - This is not the most optimal solution (O(1) extra space exists using
     *     the first row/col as markers), but it is simpler and safer.
     */
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        // Marker arrays for rows and columns
        vector<int> rows(m, -1);
        vector<int> cols(n, -1);

        // Step 1: Identify rows and columns that need to be zeroed
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    rows[i] = 0; // mark row i
                    cols[j] = 0; // mark column j
                }
            }
        }

        // Step 2: Update the matrix based on row/col markers
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (rows[i] == 0 || cols[j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    /**
     * Set Matrix Zeroes — Optimal Approach (O(1) extra space)
     * -------------------------------------------------------
     * Problem:
     *   - Given an m x n matrix, if an element is 0, set its entire row and column to 0.
     *
     * Approach (using first row and first column as markers):
     *   1. Use matrix[0][j] to mark if column j needs to be zeroed.
     *   2. Use matrix[i][0] to mark if row i needs to be zeroed.
     *   3. Special care:
     *        - matrix[0][0] overlaps between row0 and col0 → need extra variable (r0).
     *        - r0 stores whether the first row must be zeroed.
     *   4. Steps:
     *        - Pass 1: Traverse the matrix. When a cell is 0:
     *            * If it's in row 0, set r0 = 0.
     *            * Otherwise, mark row and column by setting matrix[i][0] = 0 and matrix[0][j] = 0.
     *        - Pass 2: For all non-first rows and columns,
     *                 if row or column is marked, set the cell to 0.
     *        - Pass 3: If matrix[0][0] == 0, zero out column 0.
     *        - Pass 4: If r0 == 0, zero out row 0.
     *
     * Time Complexity:  O(m * n)
     * Space Complexity: O(1) (only one extra variable)
     *
     * Notes:
     *   - This is the most space-efficient solution.
     *   - Careful handling of the first row and column is the key.
     */
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        int r0 = -1; // flag to track whether the first row needs to be zeroed

        // Step 1: Mark rows and columns using first row/col
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && matrix[i][j] == 0)
                {
                    r0 = 0; // first row must be zeroed
                }
                else if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0; // mark row i
                    matrix[0][j] = 0; // mark column j
                }
            }
        }

        // Step 2: Zero out cells based on markers, skipping first row/col
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }

        // Step 3: Handle first column using matrix[0][0] as marker
        if (matrix[0][0] == 0)
        {
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
        }

        // Step 4: Handle first row using r0
        if (r0 == 0)
        {
            for (int j = 0; j < n; j++)
                matrix[0][j] = 0;
        }
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
        int m, n;
        cin >> m >> n;
        // cin.ignore();

        vector<vector<int>> matrix(m, vector<int>(n));

        // Read the matrix
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
            }
        }

        Solution ob;
        ob.setZeroes(matrix);

        // Print modified matrix
        for (const auto &row : matrix)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
        if (t > 0)
            cout << endl; // Print a blank line between test cases
    }
    return 0;
}