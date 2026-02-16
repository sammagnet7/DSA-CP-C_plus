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
Median of Row Wise Sorted Matrix

https://takeuforward.org/data-structure/median-of-row-wise-sorted-matrix/
https://www.naukri.com/code360/problems/median-of-a-row-wise-sorted-matrix_1115473?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf


Problem statement:
Given a row-wise sorted matrix of size MXN, where M is no. of rows and N is no. of columns, find the median in the given matrix.
Note: MXN is odd.

Examples:

Sample Input 1 :
5 5
1 5 7 9 11
2 3 4 8 9
4 11 14 19 20
6 10 22 99 100
7 15 17 24 28

Sample Output 1 :
10

Explanation For Sample Input 1:
If we arrange the elements of the matrix in the sorted order in an array, they will be like this-
1 2 3 4 4 5 6 7 7 8 9 9 10 11 11 14 15 17 19 20 22 24 28 99 100

So the median is 10, which is at index 12, which is midway as the total elements are 25, so the 12th index is exactly midway. Therefore, the answer will be 10.


Sample Input 2 :
3 5
1 2 3 4 5
8 9 11 12 13
21 23 25 27 29

Sample Output 2 :
11

Explanation For Sample Input 2:
If we arrange the elements of the matrix in the sorted order in an array, they will be like this-
1 2 3 4 5 8 9 11 12 13 21 23 25 27 29

So the median is 11, which is at index 7, which is midway as the total elements are 15, so the 7th index is exactly midway. Therefore, the answer will be 11.


INPUT::::::
2

5 5
1 5 7 9 11
2 3 4 8 9
4 11 14 19 20
6 10 22 99 100
7 15 17 24 28

3 5
1 2 3 4 5
8 9 11 12 13
21 23 25 27 29

OUTPUT::::::
10
11

 */
class Solution
{
public:
    /**
     * Function to find the median of a row-wise sorted matrix.
     * * Time Complexity: O(32 * m * log(n))
     * - 32: Binary search range (approx log2(10^9)).
     * - m: Iterating through each row.
     * - log(n): upper_bound (binary search) on each row.
     * * Space Complexity: O(1)
     */
    int median(vector<vector<int>> &matrix, int m, int n)
    {

        // 1. Initialize Search Space
        // Instead of searching from 1 to 10^9 (global constraints),
        // we find the actual minimum and maximum elements currently in the matrix.
        // Since rows are sorted, min is in the first column, max is in the last column.
        int minEl = INT_MAX;
        int maxEl = INT_MIN;

        for (int i = 0; i < m; i++)
        {
            minEl = min(minEl, matrix[i][0]);
            maxEl = max(maxEl, matrix[i][n - 1]);
        }

        // 2. Define the Target Rank
        // The median is the element in the middle of the sorted sequence.
        // For a matrix of size 9 (3x3), median is the 5th smallest element.
        // Formula: (Total Elements / 2) + 1
        int desiredCount = (m * n) / 2 + 1;

        int ans = -1;  // Variable to store the potential median
        int l = minEl; // Low pointer of binary search
        int r = maxEl; // High pointer of binary search

        // 3. Binary Search on Answer
        while (l <= r)
        {
            // Pick a candidate value 'mid'
            int mid = l + (r - l) / 2;

            int actualCount = 0; // Will store count of elements <= mid

            // 4. Count elements <= mid
            // Since rows are sorted, we don't need to iterate linearly.
            // We use binary search (upper_bound) on each row.
            for (int i = 0; i < m; i++)
            {
                // upper_bound returns iterator to the first element GREATER than mid.
                // Subtracting .begin() gives the number of elements LESS THAN OR EQUAL to mid.
                actualCount += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            }

            // 5. Decision Logic
            // If actualCount >= desiredCount, it means 'mid' is large enough to cover the median rank.
            // However, 'mid' might be larger than the true median (or not even exist in the matrix).
            // So, we record 'mid' as a possible answer but try to find a SMALLER number
            // that still satisfies the condition (squeeze to the left).
            if (actualCount >= desiredCount)
            {
                ans = mid;   // Store potential answer
                r = mid - 1; // Try smaller values
            }
            // If actualCount < desiredCount, 'mid' is too small.
            // We need a larger number to reach the desired rank.
            else
            {
                l = mid + 1;
            }
        }

        // 6. Return final answer
        // 'ans' will hold the smallest number X such that count(<= X) >= desiredCount.
        return ans;
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
        cout << ob.median(matrix, m, n) << " ";
        cout << endl;
    }
    return 0;
}