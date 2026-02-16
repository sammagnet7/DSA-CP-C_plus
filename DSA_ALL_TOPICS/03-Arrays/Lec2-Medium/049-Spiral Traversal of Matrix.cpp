#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Rotate Matric by 1 element clockwise

https://takeuforward.org/data-structure/spiral-traversal-of-matrix/
https://leetcode.com/problems/spiral-matrix/description/

Problem Statement: Given a Matrix, print the given matrix in spiral order.


Examples:

Example 1:
Input:
Matrix[][] =
{
{ 1, 2, 3, 4 },
{ 5, 6, 7, 8 },
{ 9, 10, 11, 12 },
{ 13, 14, 15, 16 }
}
Output: 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10.

Example 2:
Input:
Matrix[][] =
{
{ 1, 2, 3 },
{ 4, 5, 6 },
{ 7, 8, 9 }
}
Output: 1, 2, 3, 6, 9, 8, 7, 4, 5.

INPUT::::::
5

4 4
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16

3 3
1 2 3
4 5 6
7 8 9

1 4
5 6 7 8

4 1
5
7
3
2

4 3
0 11 0
16 5 7
-4 17 6
11 16 18

OUTPUT::::::

5 1 2 3
9 10 6 4
13 11 7 8
14 15 16 12

4 1 2
7 5 3
8 9 6

5 6 7 8

5
7
3
2

16 0 11
-4 5 7
17 6 0
11 16 18

 */

class Solution
{
public:
    /*
       Return the elements of matrix `mat` in spiral (clockwise) order.

       Inputs:
         - mat : a non-empty 2D vector with dimensions n x m (n rows, m cols)
       Output:
         - a vector<int> containing all elements of mat visited in spiral order.

       Intuition and approach (high level):
         - Maintain four boundaries: top, bot, left, right that describe the
           current outer rectangle (inclusive).
         - Repeatedly traverse the outer boundary in 4 steps:
             1) left -> right along top row
             2) top+1 -> bot along right column
             3) right-1 -> left along bottom row (if still valid)
             4) bot-1 -> top+1 along left column (if still valid)
         - After visiting one ring, move the boundaries inward:
             top++, bot--, left++, right--
         - Stop when top > bot or left > right (no cells left).

       Correctness notes:
         - The checks for single row or single column (top == bot or left == right)
           before the backward traversals prevent double-visiting the same cells.
         - We use top+1 and bot-1 for vertical traversals to avoid corner duplicates.

       Complexity:
         - Time: O(n * m) because each matrix element is visited exactly once.
         - Space: O(1) extra (ignoring the output vector which holds n*m elements).
    */
    vector<int> spiralOrder(vector<vector<int>> &mat)
    {

        int n = mat.size();    /* number of rows */
        int m = mat[0].size(); /* number of columns (assume non-empty) */

        vector<int> ans;
        ans.reserve(n * m); /* optional: reserve space for performance */

        /* Boundaries for the current outer layer (inclusive indices) */
        int top = 0;
        int bot = n - 1;
        int left = 0;
        int right = m - 1;

        /*
           Loop until boundaries cross.
           At each iteration we walk the current outer ring in 4 steps.
        */
        while (top <= bot && left <= right)
        {

            /* 1) Traverse top row from left to right (columns left..right) */
            for (int col = left; col <= right; col++)
            {
                int temp = mat[top][col];
                ans.push_back(temp);
            }

            /* 2) Traverse right column from row (top+1) to bot.
               Start at top+1 to avoid re-visiting the top-right corner. */
            for (int row = top + 1; row <= bot; row++)
            {
                int temp = mat[row][right];
                ans.push_back(temp);
            }

            /*
               If remaining submatrix is a single row or a single column,
               the backward traversals (bottom row leftwards and left column upwards)
               would re-visit elements already added. Break in that case.
            */
            if (top == bot || left == right)
                break;

            /* 3) Traverse bottom row from right-1 down to left (inclusive).
               Start at right-1 to avoid the bottom-right corner (visited in step 2). */
            for (int col = right - 1; col >= left; col--)
            {
                int temp = mat[bot][col];
                ans.push_back(temp);
            }

            /* 4) Traverse left column from bot-1 up to top+1.
               Use row > top to avoid the top-left corner (visited in step 1). */
            for (int row = bot - 1; row > top; row--)
            {
                int temp = mat[row][left];
                ans.push_back(temp);
            }

            /* Move boundaries inward to process the next inner ring */
            top++;
            bot--;
            left++;
            right--;
        }

        return ans;
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
        vector<int> ans = ob.spiralOrder(matrix);

        // Print matrix in spiral order
        for (int val : ans)
        {
            cout << val << " ";
        }

        if (t > 0)
            cout << endl; // Print a blank line between test cases
    }
    return 0;
}