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
    /*
     * Approach Idea: Binary Search on Columns (Dimensionality Reduction)
     * * 1. Strategy: Instead of traversing the whole 2D grid, we apply Binary Search on the COLUMNS (0 to n-1).
     * * 2. The "Max in Column" Insight:
     * - In the chosen 'mid' column, we find the maximum element (maxColVal).
     * - Why? The largest element in a column is guaranteed to be greater than its top and bottom neighbors.
     * - This effectively simplifies the 4-direction check to a 2-direction check (Left and Right only).
     * * 3. Elimination Logic (Hill Climbing):
     * - If maxColVal is greater than its Left and Right neighbors -> It is a Peak.
     * - If the Left neighbor is greater -> There is a rising slope to the left, so a peak must exist in the left half. (Eliminate Right).
     * - If the Right neighbor is greater -> There is a rising slope to the right. (Eliminate Left).
     * * Time Complexity: O(rows * log(columns))
     * Space Complexity: O(1)
     */
    vector<int> findPeakGrid(vector<vector<int>> &mat)
    {
        int m = mat.size();    // #Rows
        int n = mat[0].size(); // #Columns

        // BS on columns range
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

    /*
        Note:
        
        Qs: Instead of taking max of the middle coulmn can we take any local max (top and bottom is less)?

        No, picking a "local" vertical peak is not safe. You must pick the Global Maximum of that column.

        Here is the deep dive into why, using a "Wall vs. Fence" analogy.

        1. The "Wall" Logic (Global Max)
        The logic of this algorithm relies on creating a "separation barrier" (the mid column) that splits the matrix into two independent halves.

        When we pick the Global Max (let's call it 100), we know that every other element in this column is smaller than 100.

        If we move Left because the left neighbor is 101, we have crossed a "barrier".

        The path of rising numbers can never come back to the Right side through this column, because to cross back, it would have to pass through this column again. But 101 is already taller than the entire mid column (since 100 was the max).

        Therefore, the peak must be trapped in the Left half.

        2. The "Fence" Leak (Local Peak)
        If you only pick a Local Peak (an element greater than its top and bottom, but not the max of the column), you are building a "low fence" instead of a high wall. The path to the true peak can "jump" back over your column.
    */
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