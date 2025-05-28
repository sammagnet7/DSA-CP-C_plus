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
Find Peak Element in 2D Matrix

https://www.youtube.com/watch?v=nGGp5XBzC4g&ab_channel=takeUforward
https://leetcode.com/problems/find-a-peak-element-ii/description/


Problem statement:
A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.


Examples:

Example 1:
Input: mat = [[1,4],[3,2]]
Output: [0,1]
Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.

Example 2:
Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
Output: [1,1]
Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable answers.


INPUT::::::
2

2 2
1 4
3 2

3 3
10 20 15
21 30 14
7 16 32


OUTPUT::::::
1 0
1 1

 */
class Solution
{
public:
    // ---------------------------------------------------------------------
    // Optimal approach : BS
    // Expand the idea of finding Peak element in 1D array to 2D array
    // Here we apply BS on the column range from 0 to (N-1)
    // In each iteration find the max of that column
    // Then check that max element is peak or not
    // If not then move the BS to right or left based on which direction gives greater element than the max element of this column
    // So we can remove the other half of the columns in each iteration of Binary search
    // Time: O(M * Log N)
    // Space: O(1)
    vector<int> findPeakGrid(vector<vector<int>> &mat)
    {
        int m = mat.size();    // #Rows
        int n = mat[0].size(); // #Columns

        int l = 0;
        int r = n - 1;

        while (l <= r)
        { // O(Log N)
            int midColIdx = l + (r - l) / 2;

            int maxColVal = INT_MIN;
            int maxColRowIdx = -1;

            for (int row = 0; row < m; row++)
            { // O(M)
                if (mat[row][midColIdx] > maxColVal)
                {
                    maxColVal = mat[row][midColIdx];
                    maxColRowIdx = row;
                }
            }

            int leftVal = (midColIdx == 0) ? -1 : mat[maxColRowIdx][midColIdx - 1];
            int rightVal = (midColIdx == n - 1) ? -1 : mat[maxColRowIdx][midColIdx + 1];

            if (maxColVal >= leftVal && maxColVal >= rightVal)
                return {maxColRowIdx, midColIdx};
            else if (maxColVal < leftVal)
            {
                r = midColIdx - 1;
            }
            else if (maxColVal < rightVal)
            {
                l = midColIdx + 1;
            }
        }

        return {-1, -1};
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        // int k;
        // cin >> k;
        // cin.ignore();

        int m, n;
        cin >> m >> n;

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
        for (auto e : ob.findPeakGrid(matrix))
        {
            cout << e << " ";
        }
        cout << endl;
    }
    return 0;
}