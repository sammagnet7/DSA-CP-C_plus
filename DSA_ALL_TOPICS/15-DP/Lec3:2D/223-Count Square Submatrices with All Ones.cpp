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

1. Title: Count Square Submatrices with All 1s | DP on Rectangles

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

//-------------------------------------------------------------------------------
// 1. Title: Count Square Submatrices with All 1s | DP on Rectangles
//-------------------------------------------------------------------------------


class Solution
{
public:
    /**
     * @brief Computes the total number of square submatrices containing only 1s.
     *
     * * * * * --- THE CORE IDEA: THE "TOP-LEFT" ANCHOR & BOTTLENECK ---
     * Instead of looking back at the top/left neighbors, we anchor our squares at
     * the TOP-LEFT corner and look FORWARD (down and right).
     * To form a square of size K starting at (i, j), the cells immediately below it,
     * to the right of it, and diagonally bottom-right MUST all be able to form
     * squares of size K-1. We are bottlenecked by the minimum of those three neighbors.
     *
     * * * * * --- THE TRICK: MATRIX PADDING ---
     * By creating a DP table slightly larger than the original matrix (m+2, n+2),
     * we surround our grid with an invisible wall of 0s. When our loop checks the
     * boundaries (the bottom row or rightmost column), it safely reads those 0s
     * instead of throwing an "Index Out of Bounds" error. This completely eliminates
     * the need for messy edge-case checks!
     *
     * * * * * --- 2D STATE DEFINITION & THE MAGIC AGGREGATION ---
     * dp[dpi][dpj]: The size of the LARGEST square whose top-left corner is at (i, j).
     * The Magic: If the largest square starting at (i, j) is size 3, it naturally implies
     * there is also a size 2 and a size 1 square starting at that exact same spot.
     * Therefore, the size of the maximum square directly equals the COUNT of valid squares!
     *
     * * * * * --- COMPLEXITY ---
     * Time Complexity  : O(M * N). We iterate through every cell of the matrix exactly once.
     * Space Complexity : O(M * N) auxiliary space for the padded DP table.
     */
    int countSquares(vector<vector<int>> &matrix)
    {

        int m = matrix.size();
        int n = matrix[0].size();

        // Create a padded DP table filled with 0s.
        // (Note: m+1 and n+1 is technically enough, but m+2 and n+2 is perfectly safe!)
        vector<vector<int>> dp(m + 2, vector<int>(n + 2, 0));

        // This will accumulate the total count of all valid squares
        int totSqrs = 0;

        // TOPOLOGICAL ORDER: Iterate backwards!
        // Because a cell relies on the cells below it and to its right, we must
        // calculate the bottom-right of the matrix first and build upwards.
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {

                // Shift our coordinates by +1 to map the 0-indexed original matrix
                // into our 1-indexed padded DP table.
                int dpi = i + 1;
                int dpj = j + 1;

                // If the original cell is a 0, it cannot act as the top-left corner
                // of ANY square. It remains 0 in the DP table.
                if (matrix[i][j] == 0)
                {
                    continue;
                }

                // --- THE TRANSITION (BOTTLENECK) ---
                // The current cell is a 1. It can form a square of size 1 PLUS the
                // minimum square size that its three forward-looking neighbors can form.
                // Because of our padded 0s, boundary cells naturally get a minimum of 0!
                dp[dpi][dpj] = 1 + min({
                                       dp[dpi + 1][dpj],    // Cell directly below
                                       dp[dpi][dpj + 1],    // Cell directly to the right
                                       dp[dpi + 1][dpj + 1] // Cell diagonally bottom-right
                                   });

                // Add the valid squares starting exactly at this cell to our global total
                totSqrs += dp[dpi][dpj];
            }
        }

        return totSqrs;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
