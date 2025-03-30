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
Program to generate Pascal's Triangle

https://takeuforward.org/data-structure/program-to-generate-pascals-triangle/
https://leetcode.com/problems/pascals-triangle/description/
https://www.naukri.com/code360/problems/print-pascal-s-triangle_6917910?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_Arrayproblems


Problem Statement: This problem has 3 variations. They are stated below:
Variation 1: Given row number r and column number c. Print the element at position (r, c) in Pascal’s triangle.
Variation 2: Given the row number n. Print the n-th row of Pascal’s triangle.
Variation 3: Given the number of rows n. Print the first n rows of Pascal’s triangle.

Note: In Pascal's triangle, each number is the sum of the two numbers directly above it.

Examples:

    Example 1:

        Input Format:
        N = 5, r = 5, c = 3

        Result:

        6 (for variation 1)

        1 4 6 4 1 (for variation 2)

        1
        1 1
        1 2 1
        1 3 3 1
        1 4 6 4 1    (for variation 3)

    Explanation:
        There are 5 rows in the output matrix. Each row is formed using the logic of Pascal’s triangle.

    Example 2:

        Input Format:
        N = 1, r = 1, c = 1

        Result:

        1 (for variation 1)

            1 (for variation 2)

            1  (for variation 3)

    Explanation:
        The output matrix has only 1 row.

INPUT::::::
2
5 3
10 4

OUTPUT::::::

Variation 1
6
Variation 2
1 4 6 4 1
Variation 3
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1

Variation 1
84
Variation 2
1 9 36 84 126 126 84 36 9 1
Variation 3
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
1 7 21 35 35 21 7 1
1 8 28 56 70 56 28 8 1
1 9 36 84 126 126 84 36 9 1



 */

class Solution
{
public:
    // Required element = (rowNum-1)C(colNum-1)
    // Time: O(colNum)
    // Space: O(1)
    void generateElem(int rowNum, int colNum)
    {
        cout << calnCr(rowNum - 1, colNum - 1) << endl;
    }

    // current element = prevElement * (rowNumber - colIndex) / colIndex
    //  Time: O(rowNum)
    //  Space: O(1)
    void generateRow(int rowNum)
    {
        vector<int> row(rowNum);

        row[0] = 1; // default values for each row
        row[rowNum - 1] = -1;

        int numer = rowNum;
        int denom = 0;
        int elem = 1;

        for (int i = 1; i < rowNum; i++)
        {
            numer--;
            denom++;
            elem = elem * numer; // Must do it in 2 steps to avoid wrong fractional values
            elem = elem / denom;

            row[i] = elem;
        }

        for (int e : row)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    // Approach: Taken a 1 index based Matrix
    // Time: O(numRows^2)
    // Space: O(N) because here we are using the matrix for calculation
    // Optimal approach: Use generateRow() to generate each rows in O(1) space
    void generateMatrix(int numRows)
    {
        vector<vector<int>> matrix(numRows);

        // Creating empty matrix
        for (int i = 0; i < numRows; i++)
        {
            vector<int> n(i + 1);
            matrix[i] = n;
        }

        // Filling default values
        for (int i = 0; i < numRows; i++)
        {
            matrix[i][0] = 1;
            matrix[i][i] = 1;
        }

        for (int i = 2; i < numRows; i++)
        {
            for (int j = 1; j < i; j++)
            {
                matrix[i][j] = matrix[i - 1][j - 1] + matrix[i - 1][j];
            }
        }

        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    // Approach:
    // nCr= [ n!/ ((n-r)!*r!) ] = [ (n*(n-1)*(n-2)*.....*(n-r+1)) / (r*(r-1)*(r-2)*....1) ]
    //    = (n / 1)*((n-1) / 2)*.....*((n-r+1) / r)
    // time: O(r)
    // Space: O(1)
    int calnCr(int n, int r)
    {
        int m = min(r, (n - r));
        r = m;

        long long result = 1;

        for (int i = 1; i <= r; i++)
        {
            result *= (n - i + 1); // This 2 step split is necessary
                                   // so that numerators gets divided properly
                                   // in both the csases of n being even or odd
            result /= i;
        }
        return result;
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
        int row, col;
        cin >> row >> col;

        Solution ob;

        cout << "Variation 1  " << endl;
        ob.generateElem(row, col);
        cout << "Variation 2  " << endl;
        ob.generateRow(row);
        cout << "Variation 3  " << endl;
        ob.generateMatrix(row);

        cout << endl; // Print a blank line between test cases
    }
    return 0;
}