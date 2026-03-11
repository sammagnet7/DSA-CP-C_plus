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
#include <map>
#include <unordered_set>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

/*

1. Title: Count Square Submatrices with All 1s | DP on Rectangles : DP 56

Links:
https://takeuforward.org/data-structure/count-square-submatrices-with-all-1s-dp-on-rectangles-dp-56/
https://www.youtube.com/watch?v=auS1fynpnjo
https://leetcode.com/problems/count-square-submatrices-with-all-ones/description/


Problem statement:
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

Examples:
    Example 1:
    Input: matrix =
    [
    [0,1,1,1],
    [1,1,1,1],
    [0,1,1,1]
    ]
    Output: 15
    Explanation:
    There are 10 squares of side 1.
    There are 4 squares of side 2.
    There is  1 square of side 3.
    Total number of squares = 10 + 4 + 1 = 15.

    Example 2:
    Input: matrix =
    [
    [1,0,1],
    [1,1,0],
    [1,1,0]
    ]
    Output: 7
    Explanation:
    There are 6 squares of side 1.
    There is 1 square of side 2.
    Total number of squares = 6 + 1 = 7.


Constraints:
    1 <= arr.length <= 300
    1 <= arr[0].length <= 300
    0 <= arr[i][j] <= 1



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Count Square Submatrices with All 1s | DP on Rectangles : DP 56
    //-------------------------------------------------------------------------------

    /*
        Function: countSquares
        --------------------------------------
        Problem:
        Given a binary matrix (containing 0s and 1s), count the total number of square submatrices
        that consist only of 1s.

        Approach:
        - Use **Dynamic Programming (DP)** to compute the size of the largest square ending at each cell.
        - Let dp[i][j] represent the size of the largest square submatrix with the bottom-right corner at (i, j).
        - Recurrence:
            - If matrix[i][j] == 0 → dp[i][j] = 0 (cannot form a square).
            - If matrix[i][j] == 1:
                - If i == 0 OR j == 0 → dp[i][j] = 1 (edge cells can only form 1x1 square).
                - Otherwise:
                    dp[i][j] = 1 + min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1])
                    (Take minimum of top, top-left diagonal, and left squares).
        - Why? Because a square can only expand if all three directions have at least that size.

        Counting:
        - Each dp[i][j] contributes to the total count since it represents how many squares end at that cell.
        - For example, if dp[i][j] = 3, it means:
            - One 1x1 square, one 2x2 square, and one 3x3 square ending at (i, j).

        Time Complexity:
        - O(m * n) → Fill DP table and sum up.
        Space Complexity:
        - O(m * n) for DP table (can be optimized to O(n) with 1D DP).
    */
    int countSquares(vector<vector<int>> &matrix)
    {

        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0)); // DP table to store max square size ending at (i,j)

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                // Base case: First row or first column → same as input
                if (i == 0 || j == 0)
                {
                    dp[i][j] = matrix[i][j];
                    continue;
                }

                // If current cell is 0 → no square can end here
                if (matrix[i][j] == 0)
                    continue;

                // Otherwise, compute size of square ending at (i,j)
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]});
            }
        }

        int ans = 0;
        // Sum all dp[i][j] values → total number of squares
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ans += dp[i][j];
            }
        }

        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
