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

using namespace std;

/*
Search in a row and column-wise sorted matrix

https://takeuforward.org/arrays/search-in-a-row-and-column-wise-sorted-matrix/
https://leetcode.com/problems/search-a-2d-matrix-ii/


Problem statement:
You have been given a 2-D array 'mat' of size 'N x M' where 'N' and 'M' denote the number of rows and columns, respectively. The elements of each row and each column are sorted in non-decreasing order.
But, the first element of a row is not necessarily greater than the last element of the previous row (if it exists).
You are given an integer ‘target’, and your task is to find if it exists in the given 'mat' or not.

Examples:

Example 1:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
target = 5
Output: true

Example 2:
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
target = 20
Output: false


INPUT::::::
2

5
5 5
1 4 7 11 15
2 5 8 12 19
3 6 9 16 22
10 13 14 17 24
18 21 23 26 30

20
5 5
1 4 7 11 15
2 5 8 12 19
3 6 9 16 22
10 13 14 17 24
18 21 23 26 30


OUTPUT::::::
true
false

 */
class Solution
{
public:
    // ---------------------------------------------------------------------
    // Optimal approach
    // we should start the matrix traversal from either the cell (0, n-1) or (m-1, 0)
    // Beacause starting from either of these index, we can element either a row or a column each time
    // Here in this approach, we have chosen the cell (0, m-1) to start with
    // If current element > target then col-- and if current element < target then row++
    // Time: O(m+n)
    // In the worst case, the pointer starts at the top-right and moves all the way to the bottom-left. 
    // It makes at most N moves down and M moves left.
    // Space: O(1)
    bool searchMatrix(vector<vector<int>> &mat, int target)
    {
        int m = mat.size();    // #Rows
        int n = mat[0].size(); // #Cols

        int rowIdx = 0;
        int colIdx = n - 1;

        while (rowIdx <= m - 1 && colIdx >= 0)
        {
            if (mat[rowIdx][colIdx] == target)
                return true;
            else if (mat[rowIdx][colIdx] > target)
                colIdx--;
            else if (mat[rowIdx][colIdx] < target)
                rowIdx++;
        }

        return false;
    }

    /*
        Why not start at the top-left (0,0)? If you start at (0,0), moving right increases the value, and moving down also increases the value. If the current element is smaller than the target, you don't know whether to move right or down to find the target.

        Where to start? You must start at a corner where moving in one direction increases the value, and moving in the other decreases it. There are two valid starting points:

        Top-Right Corner: Moving Left decreases the value; moving Down increases the value.

        Bottom-Left Corner: Moving Up decreases the value; moving Right increases the value.
    */
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int k;
        cin >> k;
        cin.ignore();

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
        cout << boolalpha;
        cout << ob.searchMatrix(matrix, k);
        cout << endl;
    }
    return 0;
}