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
    /**
     * Spiral Matrix Traversal
     * -----------------------
     * Problem:
     *   - Given an m x n matrix, return all elements in spiral order.
     *
     * Approach:
     *   - Use four boundary pointers (top, bottom, left, right) to define
     *     the current layer of the matrix to traverse.
     *   - Traverse in 4 directions:
     *       1. Left → Right   (across top row)
     *       2. Top → Bottom   (along right column)
     *       3. Right → Left   (across bottom row, if still valid)
     *       4. Bottom → Top   (along left column, if still valid)
     *   - After each direction, move the corresponding boundary inward:
     *       * top++, right--, bottom--, left++
     *   - Continue until all elements are traversed (while top ≤ bottom and left ≤ right).
     *
     * Time Complexity:  O(m * n)  [each element is visited once]
     * Space Complexity: O(1) extra (apart from output vector)
     *
     * Works for:
     *   - Both square (m == n) and rectangular (m != n) matrices.
     */
    vector<int> spiralOrder(vector<vector<int>> &mat)
    {
        vector<int> ans; // stores elements in spiral order

        int n = mat.size();    // number of rows
        int m = mat[0].size(); // number of columns

        // Initialize boundaries
        int top = 0, left = 0, bottom = n - 1, right = m - 1;

        // Traverse until boundaries cross
        while (top <= bottom && left <= right)
        {
            // 1. Traverse top row (left → right)
            for (int i = left; i <= right; i++)
                ans.push_back(mat[top][i]);
            top++; // move top boundary down

            // 2. Traverse right column (top → bottom)
            for (int i = top; i <= bottom; i++)
                ans.push_back(mat[i][right]);
            right--; // move right boundary left

            // 3. Traverse bottom row (right → left), if still valid
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                    ans.push_back(mat[bottom][i]);
                bottom--; // move bottom boundary up
            }

            // 4. Traverse left column (bottom → top), if still valid
            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                    ans.push_back(mat[i][left]);
                left++; // move left boundary right
            }
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