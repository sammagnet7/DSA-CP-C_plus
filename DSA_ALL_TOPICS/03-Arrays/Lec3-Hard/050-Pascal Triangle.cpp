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
https://www.geeksforgeeks.org/dsa/find-the-nth-row-in-pascals-triangle/
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
        1
        1 1
        1 2 1
        1 3 3 1
        1 4 6 4 1 (for variation 1)

        1 4 6 4 1 (for variation 2)

        6         (for variation 3)
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
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
Variation 2
1 4 6 4 1
Variation 3
6

Variation 1
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
Variation 2
1 9 36 84 126 126 84 36 9 1
Variation 3
84

 */

class Solution
{
public:
    // ----------------------------------------------------------------------
    // Variation 1: genrate whole matrix in O(N^2)
    // ----------------------------------------------------------------------

    /*
        generate: build Pascal's Triangle up to numRows rows.

        Input:
            - numRows : number of rows to generate (0 => empty triangle)

        Output:
            - a vector of vectors, where matrix[i] is the (i)-th row (0-indexed)
            of Pascal's triangle and contains i+1 integers.

        Intuition:
            - Each row k (0-based) has k+1 elements.
            - The first and last elements of every row are 1.
            - Every interior element matrix[i][j] (0 < j < i) equals
                matrix[i-1][j-1] + matrix[i-1][j]
            i.e., sum of the two entries above it from the previous row.

        Complexity:
            - Time:  O(numRows^2) because we fill about 1 + 2 + ... + numRows = O(numRows^2) entries.
            - Space: O(numRows^2) for storing the triangle.
    */
    vector<vector<int>> generateMatrix(int numRows)
    {
        /* Create the outer vector with numRows empty rows initially.
        If numRows == 0, this yields an empty triangle (early return behavior). */
        vector<vector<int>> matrix(numRows);

        /* Allocate each row with the correct length (row i has i+1 elements).
        This guarantees matrix[i][j] is valid for 0 <= j <= i. */
        for (int i = 0; i < numRows; i++)
        {
            vector<int> row(i + 1);
            matrix[i] = row;
        }

        /* Fill the boundary values (first and last element of each row) with 1.
        For row 0 this sets matrix[0][0] = 1 (single-element row). */
        for (int i = 0; i < numRows; i++)
        {
            matrix[i][0] = 1; /* left boundary */
            matrix[i][i] = 1; /* right boundary (same as left when i == 0) */
        }

        /* Fill interior values using the Pascal recurrence:
            matrix[i][j] = matrix[i-1][j-1] + matrix[i-1][j]
        We start from i = 2 because rows 0 and 1 contain only boundary elements. */
        for (int i = 2; i < numRows; i++)
        {
            for (int j = 1; j < i; j++)
            {
                matrix[i][j] = matrix[i - 1][j - 1] + matrix[i - 1][j];
            }
        }

        return matrix;
    }

    // ----------------------------------------------------------------------
    // Variation 2: genrate a Row in O(N)
    // ----------------------------------------------------------------------

    /*
  generateRow: compute and print one row of Pascal's triangle using an
  iterative multiplicative formula (updated/tweaked version).

  Intuition:
    - The k-th element (0-based) in the r-th row of Pascal's triangle is
      the binomial coefficient C(r-1, k) when rowNum = r (this function uses
      rowNum as the row length, so rowNum == r).
    - Consecutive elements in the same row satisfy:
        C(r-1, k) = C(r-1, k-1) * (r - k) / k
      where k runs from 1..r-1 (1-based denominator).
    - Using this multiplicative relation we can compute each element from the
      previous element using one multiplication and one division (division is
      exact in integer arithmetic for binomial ratios).
    - This implementation fills a temporary vector `row` of length rowNum and
      prints it. It assumes rowNum >= 1. Be careful with overflow for large rows.

  Parameters / conventions:
    - rowNum : number of elements in the row to generate (row length).
               Example: rowNum == 5 corresponds to the 5 elements of the row
               [C(4,0), C(4,1), C(4,2), C(4,3), C(4,4)].
    - The function prints the row to stdout (space separated), then a newline.

  Complexity:
    - Time : O(rowNum) — computes each element once.
    - Space: O(rowNum) — stores the row in a vector.

  Edge cases and notes:
    - If rowNum <= 0: behavior is undefined in this code. For safety, check and
      return early before calling this function.
    - For rowNum == 1: the loop body will not run; the vector contains a single 1.
    - For rowNum == 2: interior loop is skipped and both boundary 1s remain.
    - For large rowNum, intermediate values can overflow 32-bit int. Consider
      using long long if needed.
*/
    void generateRow(int rowNum)
    {
        /* allocate a vector of length rowNum to hold the row values */
        vector<int> row(rowNum);

        /* boundary values are always 1 in Pascal's triangle */
        row[0] = 1;          /* left boundary: C(r-1,0) = 1 */
        row[rowNum - 1] = 1; /* right boundary: C(r-1,r-1) = 1 */

        /*
          We will compute interior entries using the multiplicative relation:
            row[k] = row[k-1] * (r - k) / k
          where:
            - r   == rowNum
            - k   runs from 1 .. rowNum-2 (since row[rowNum-1] is boundary)
          The implementation below uses previous element stored in row[k-1].
        */
        int r = rowNum;

        /* Loop over interior positions and fill them.
           Note: loop upper bound is k < rowNum-1 so it does not overwrite the right boundary. */
        for (int k = 1; k < rowNum - 1; k++)
        {
            /* compute next element from previous using integer arithmetic.
               multiply first, then divide to avoid fractional truncation. */
            int temp = row[k - 1] * (r - k); /* numerator: previous * (r - k) */
            temp = temp / k;                 /* denominator: k (exact division) */

            row[k] = temp;
        }

        /* print the computed row to stdout (space separated) */
        for (int e : row)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    // ----------------------------------------------------------------------
    // Variation 3: genrate an element in particular row in O(N)
    // ----------------------------------------------------------------------

    /*
  calnCr: compute the binomial coefficient C(n, r) using an
  iterative multiplicative approach without computing full factorials.

  Formula intuition:
    C(n, r) = n! / (r! * (n-r)!)
            = (n * (n-1) * ... * (n-r+1)) / (r * (r-1) * ... * 1)
    We compute this as an iterative product:
      result = 1
      for i = 1..r:
        result = result * (n - i + 1) / i
    At each step the division is exact (no fractional remainder) because
    binomial coefficients are integers and the multiplicative sequence
    preserves exactness when done in this order (multiply then divide).

  Key optimizations / correctness points:
    - Use r = min(r, n-r). Because C(n, r) == C(n, n-r), this reduces the
      number of iterations to at most floor(n/2).
    - Do multiplication before division on each step to keep integers exact.
    - Use a 64-bit accumulator (long long) to reduce overflow risk for moderate n.
      For very large n or r, even 64-bit may overflow; use big-integer libraries
      if you need arbitrary precision.
    - If r == 0, the loop does zero iterations and result remains 1 (C(n,0)=1).

  Complexity:
    - Time:  O(r) where r is min(r, n-r).
    - Space: O(1) extra memory.

  Note about return type:
    - The function returns int in the original snippet. If n is large enough that
      C(n,r) exceeds 32-bit range, the returned value will overflow. Prefer
      returning long long (or a big-int type) if larger results are needed.

  Examples:
    - calnCr(5, 2) computes: result = 1
        i=1: result = 1 * 5 / 1 = 5
        i=2: result = 5 * 4 / 2 = 10
      returns 10 (C(5,2) = 10)
*/
    int calnCr(int n, int r)
    {
        /* symmetry reduction: compute the smaller of r and n-r */
        r = min(r, n - r);

        /* accumulator uses 64-bit to reduce overflow chances during intermediate steps */
        long long result = 1;

        /* multiply-then-divide loop: each step keeps the intermediate value integral */
        for (int i = 1; i <= r; i++)
        {
            /* multiply by the next numerator term (n - i + 1) */
            result *= (n - i + 1);

            /* divide by the denominator i (division is exact at this step) */
            result /= i;
        }

        /* note: casting/truncation may occur if caller expects int and result > INT_MAX */
        return (int)result;
    }

    /*
  generateElem: print the element at (rowNum, colNum) in Pascal's triangle.

  Explanation / Intuition:
    - The element at row index `rowNum` and column index `colNum` (1-based indices)
      in Pascal's triangle equals the binomial coefficient:
         C(rowNum-1, colNum-1)
      because rows and columns in Pascal's triangle are zero-based binomial indices.
    - This function delegates the computation to calnCr(n, r) which computes
      C(n, r) efficiently via an iterative multiplicative approach.

  Parameters:
    - rowNum : 1-based row number in Pascal's triangle (must be >= 1)
    - colNum : 1-based column number in that row (1 <= colNum <= rowNum)

  Behavior:
    - Prints the computed value followed by a newline.
    - Does not return a value (void). If you need the value for further use,
      modify the function to return the result of calnCr instead of printing.

  Complexity:
    - Time:  O(colNum) in the worst case, since calnCr uses r = min(r, n-r) and
      runs in O(r) where r = colNum-1 (or its symmetric counterpart).
    - Space: O(1) extra space.

  Notes / Edge cases:
    - Assumes valid 1-based inputs (1 <= colNum <= rowNum). If inputs may be invalid,
      add guards to handle or report errors.
    - For large rowNum/colNum, calnCr may overflow 32-bit int; ensure calnCr uses
      a sufficiently wide integer type or big-int if needed.
*/
    void generateElem(int rowNum, int colNum)
    {
        cout << calnCr(rowNum - 1, colNum - 1) << endl;
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
        ob.generateMatrix(row);
        cout << "Variation 2  " << endl;
        ob.generateRow(row);
        cout << "Variation 3  " << endl;
        ob.generateElem(row, col);

        cout << endl; // Print a blank line between test cases
    }
    return 0;
}