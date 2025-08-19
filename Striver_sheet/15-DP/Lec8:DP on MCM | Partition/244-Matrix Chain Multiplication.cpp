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

1. Title: Matrix Chain Multiplication | (DP-48)
          Matrix Chain Multiplication | Tabulation Method | (DP-49)

Links:
https://takeuforward.org/dynamic-programming/matrix-chain-multiplication-dp-48/
https://takeuforward.org/data-structure/matrix-chain-multiplication-tabulation-method-dp-49/
https://www.youtube.com/watch?v=vRVfmbCFW7Y
https://www.youtube.com/watch?v=pDCXsbAw5Cg
https://takeuforward.org/plus/dsa/problems/matrix-chain-multiplication?tab=editorial
https://www.naukri.com/code360/problems/matrix-chain-multiplication_975344?leftPanelTabValue=PROBLEM



Problem statement:
Given a chain of matrices A1, A2, A3,.....An. Your task is to find out the minimum cost to multiply these matrices. The cost of matrix multiplication is defined as the number of scalar multiplications. A Chain of matrices A1, A2, A3,.....An is represented by a sequence of numbers in an array ‘arr’ where the dimension of 1st matrix is equal to arr[0] * arr[1] , 2nd matrix is arr[1] * arr[2], and so on.

For example:
For arr[ ] = { 10, 20, 30, 40}, matrix A1 = [10 * 20], A2 = [20 * 30], A3 = [30 * 40]

Scalar multiplication of matrix with dimension 10 * 20 is equal to 200.



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
    // 1. Title: Matrix Chain Multiplication | (DP-48)
    //           Matrix Chain Multiplication | Tabulation Method | (DP-49)

    /*
     Problem: Matrix Chain Multiplication
     -----------------------------------
     Given an array 'arr' of size N where:
         - Matrix i has dimensions arr[i-1] x arr[i]
     Goal: Find the minimum number of scalar multiplications
           required to multiply the entire chain of matrices.

     Approach: Recursion + Memoization (Top-Down DP)
     -----------------------------------------------
     - Define recMatrix(i, j) as the minimum number of multiplications
       required to multiply matrices from index i to j.
     - Base case:
         If i == j, only one matrix ? No multiplication needed ? return 0
     - Transition:
         Try splitting the chain at every position k (i <= k < j):
             cost = cost of left chain (i..k)
                  + cost of right chain (k+1..j)
                  + cost of multiplying the resulting two matrices
                  = recMatrix(i, k) + recMatrix(k+1, j)
                    + arr[i-1] * arr[k] * arr[j]
         Take the minimum over all k.
     - Memoize results in dp[i][j] to avoid recomputation.

     Time Complexity: O(N^3)
         - For each pair (i, j), we try all splits (k)
     Space Complexity: O(N^2) for dp table + recursion stack
 */

    // Recursive helper with memoization
    int recMatrix(int i, int j, vector<int> &arr, int N, vector<vector<int>> &dp)
    {
        // Base case: Only one matrix left
        if (i == j)
            return dp[i][j] = 0;

        // Already computed ? return memoized value
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        int minOps = INT_MAX;

        // Try every possible split between i..j
        for (int k = i; k < j; k++)
        {
            // Cost = cost of left part + right part + multiplying the results
            int curops = (arr[i - 1] * arr[k] * arr[j]) + recMatrix(i, k, arr, N, dp) + recMatrix(k + 1, j, arr, N, dp);

            // Choose the minimum among all possible splits
            minOps = min(minOps, curops);
        }

        // Store result in dp and return
        return dp[i][j] = minOps;
    }

    // Main function to compute matrix chain multiplication
    int matrixMultiplication(vector<int> &arr, int N)
    {
        // dp[i][j] = minimum cost of multiplying matrices from i to j
        vector<vector<int>> dp(N, vector<int>(N, -1));

        // Start recursion from the full chain (1..N-1)
        // Note: Matrices are indexed from 1 to N-1
        // because arr[0]..arr[N-1] are dimensions
        return recMatrix(1, N - 1, arr, N, dp);
    }

    /*
        Problem: Matrix Chain Multiplication
        -----------------------------------
        Given an array 'arr' of size N where:
            - Matrix i has dimensions arr[i-1] x arr[i]
        Goal: Find the minimum number of scalar multiplications
              required to multiply the entire chain of matrices.

        Approach: Bottom-Up Dynamic Programming (Tabulation)
        ----------------------------------------------------
        - dp[i][j] = minimum number of multiplications required
                     to multiply matrices from index i to j.
        - Base case:
            If i == j, only one matrix ? No multiplication ? dp[i][j] = 0
        - Transition:
            For every possible split point k (i ? k < j):
                cost = dp[i][k] + dp[k+1][j] + (arr[i-1] * arr[k] * arr[j])
            Take the minimum among all splits.
        - Filling order:
            We fill the DP table diagonally (increasing chain length).
            That?s why the outer loop runs i backwards (N-1 ? 0)
            and inner loop runs j forward (i+1 ? N-1).
        - Answer is stored in dp[1][N-1].

        Time Complexity: O(N^3)
            - For each pair (i, j), we try all k in between
        Space Complexity: O(N^2)
    */

    // Iterative DP solution
    int matrixMultiplication(vector<int> &arr, int N)
    {
        // dp[i][j] = min cost to multiply matrices from i to j
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Fill table bottom-up
        for (int i = N - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < N; j++)
            {

                // Base case: single matrix ? no multiplication
                if (i == j)
                {
                    dp[i][j] = 0;
                    continue;
                }

                int minOps = INT_MAX;

                // Try splitting at every possible k
                for (int k = i; k < j; k++)
                {
                    int curops = (arr[i - 1] * arr[k] * arr[j]) + dp[i][k] // left subchain
                                 + dp[k + 1][j];                           // right subchain

                    minOps = min(minOps, curops);
                }

                dp[i][j] = minOps;
            }
        }

        // Final answer: cost of multiplying entire chain (1..N-1)
        return dp[1][N - 1];
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
