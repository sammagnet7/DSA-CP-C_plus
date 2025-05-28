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
    // Returns the upper-bound index
    // Time: O(Log N)
    // Space: O(1)
    int findUpperBound(vector<int> &mat, int n, int target)
    {
        int l = 0;
        int r = n - 1;

        int ans = n;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (mat[mid] > target)
            {
                ans = min(ans, mid);
                r = mid - 1;
            }
            else if (mat[mid] <= target)
            {
                l = mid + 1;
            }
        }

        return ans;
    }

    // Returns total number of elements in the whole matrix  (i.e. m vectors of each n size)
    // which are less-than-or-equals-to the given target element
    // Time: O(M * Log N)
    // Space: O(1)
    int countOfLessThanEquals(vector<vector<int>> &mat, int m, int n, int target)
    {
        int count = 0;

        for (int i = 0; i < m; i++)
        {
            count += findUpperBound(mat[i], mat[i].size(), target);
        }

        return count;
    }

    // ---------------------------------------------------------------------
    // Optimal approach: Using BS on the range of (min element to max element)
    // Time: O(M) + O(Log(10^9) * M * LogN)
    // Space: O(1)
    // Note: Brute force approach [Time: O(M*N) + O(M*N Log(M*N))]; [Space: O(M*N)]
    int median(vector<vector<int>> &mat, int m, int n)
    {
        // Write your code here.

        int minEl = INT_MAX;
        int maxEl = INT_MIN;

        for (int i = 0; i < m; i++)
        { // O(M)
            minEl = min(minEl, mat[i][0]);
            maxEl = max(maxEl, mat[i][n - 1]);
        }

        int l = minEl;
        int r = maxEl;
        int ans = maxEl;
        int leftToMedian = (m * n) / 2; // #expected elements left to the median

        while (l <= r)
        { // O(Log (max-min)) where  int the worst case min=0, max=10^9 => O(Log (10^9))

            int mid = l + (r - l) / 2;

            int lessThanEqualsCount = countOfLessThanEquals(mat, m, n, mid);

            if (lessThanEqualsCount > leftToMedian)
            {   // To become the answer,
                // #elements less than equals to median must be
                //  greater than the #expected elements left to median
                // becase of median element also need to be counted as +1
                ans = min(ans, mid);
                r = mid - 1;
            }
            else if (lessThanEqualsCount <= leftToMedian)
            {
                l = mid + 1;
            }
        }

        return ans; // If ans fails for any test cases then try with 'l'
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