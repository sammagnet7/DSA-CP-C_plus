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
    // // Appraoch: Better. Works with negetive matrix elements as well
    // // Time: O(2(m*n))
    // // Space: O(m+n)
    // void setZeroes(vector<vector<int>>& matrix) {
    //     int m=matrix.size();
    //     int n=matrix[0].size();

    //     vector<int> rows(m,-1);
    //     vector<int> cols(n,-1);

    //     // O(m*n)
    //     for(int i=0; i<m; i++){
    //         for(int j=0; j<n; j++){
    //             if(matrix[i][j]==0){
    //                 rows[i]=0;
    //                 cols[j]=0;
    //             }
    //         }
    //     }

    //     // O(m*n)
    //     for(int i=0; i<m; i++){
    //         for(int j=0; j<n; j++){
    //             if(rows[i]==0 || cols[j]==0){
    //                 matrix[i][j]=0;
    //             }
    //         }
    //     }
    // }

    /* Appraoch: Optimal. Works with negetive matrix elements as well
    // using matrix row0 as cols[] and matrix column0 as rows[];
    // As matrix[0][0] is taken as cols[0] => var r0 will work as rows[0]
    // Time: O(2(m*n))
    // Space: O(1);
    */
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        int r0 = -1;

        // O(m*n)
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && matrix[i][j] == 0)
                    r0 = 0;
                else if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // O(m*n)
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }

        // Need to check matrix[0][0] first to modify column0
        // O(m)
        if (matrix[0][0] == 0)
        {
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
        }

        // Then check the outside variable to modify row0
        // O(n)
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