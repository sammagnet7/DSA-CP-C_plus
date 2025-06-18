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

using namespace std;

/*

N-Queens:

https://takeuforward.org/data-structure/n-queen-problem-return-all-distinct-solutions-to-the-n-queens-puzzle/
https://leetcode.com/problems/n-queens/description/


Problem statement:
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Examples:

Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:
Input: n = 1
Output: [["Q"]]


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // N-Queens (Approach1 with space N^2):

    // // O(3N)
    // bool checkCellEligible(vector<string> &board, int rowIdx, int colIdx, int N)
    // {
    //     // Check prev cells in same Col
    //     int tmpRow = rowIdx;
    //     int tmpCol = colIdx;
    //     while (tmpRow >= 0)
    //     {
    //         if (board[tmpRow--][tmpCol] == 'Q')
    //             return false;
    //     }

    //     // Check prev cells in Left Diagonal
    //     tmpRow = rowIdx;
    //     tmpCol = colIdx;
    //     while (tmpCol >= 0 && tmpRow >= 0)
    //     {
    //         if (board[tmpRow--][tmpCol--] == 'Q')
    //             return false;
    //     }

    //     // Check prev cells in Right Diagonal
    //     tmpRow = rowIdx;
    //     tmpCol = colIdx;
    //     while (tmpCol < N && tmpRow >= 0)
    //     {
    //         if (board[tmpRow--][tmpCol++] == 'Q')
    //             return false;
    //     }

    //     return true;
    // }

    // // O( [N! * (3N + N^2)] )
    // void recurseQueen(vector<vector<string>> &ans, vector<string> &board, int N, int rowIdx)
    // {
    //     if (rowIdx == N)
    //     {
    //         ans.push_back(board); // O(N^2)
    //         return;
    //     }

    //     // O(N!)
    //     for (int j = 0; j < N; j++)
    //     { // Iterate over each cols of the current row

    //         if (!checkCellEligible(board, rowIdx, j, N)) // O(3N)
    //             continue;

    //         board[rowIdx][j] = 'Q';

    //         recurseQueen(ans, board, N, (rowIdx + 1));

    //         board[rowIdx][j] = '.';
    //     }
    // }

    // // Approach 1: Where for each cell we chaeck all the prev row, col and diagonal for placement validity
    // // Time: O( [N! * (3N + N^2)] ): For each N rows check for N cols; Copy N^2 `board` to `ans`
    // // Space: O(N^2) because of the `board` data structure having n strings of length n
    // vector<vector<string>> solveNQueens(int n)
    // {
    //     vector<vector<string>> ans;
    //     vector<string> board(n, string(n, '.')); // As n rows and n cols in the board
    //                                              // we here populated the whole with '.'

    //     recurseQueen(ans, board, n, 0);

    //     return ans;
    // }

    // ---------------------------------------------
    // N-Queens (Approach2: Optimal with Hashing ):

    // O(3)
    bool checkCellEligible(vector<int> &prevColsHash, vector<int> &prevleftDiagHash, vector<int> &prevRightDiagHash, int rowIdx, int colIdx, int N)
    {
        if (prevColsHash[colIdx] == 1                             // Check prev cells in same Col
            || prevleftDiagHash[(N - 1) + (colIdx - rowIdx)] == 1 // Check prev cells in Left Diagonal
            || prevRightDiagHash[(rowIdx + colIdx)] == 1)         // Check prev cells in Right Diagonal
            return false;

        else
            return true;
    }

    // O( [N! * (N^2)] )
    void recurseQueen(vector<vector<string>> &ans, vector<string> &board, int N, vector<int> &prevColsHash, vector<int> &prevleftDiagHash, vector<int> &prevRightDiagHash, int rowIdx)
    {
        if (rowIdx == N)
        {
            ans.push_back(board); // O(N^2)
            return;
        }

        // O(N!)
        for (int j = 0; j < N; j++)
        { // Iterate over each cols of the current row

            if (!checkCellEligible(prevColsHash, prevleftDiagHash, prevRightDiagHash, rowIdx, j, N)) // O(1)
                continue;

            board[rowIdx][j] = 'Q';
            prevColsHash[j] = 1;
            prevleftDiagHash[(N - 1) + (j - rowIdx)] = 1; // formula: (N-1) + (col-row)
            prevRightDiagHash[(rowIdx + j)] = 1;          // formula: (row+col)

            recurseQueen(ans, board, N, prevColsHash, prevleftDiagHash, prevRightDiagHash, (rowIdx + 1));

            board[rowIdx][j] = '.';
            prevColsHash[j] = 0;
            prevleftDiagHash[(N - 1) + (j - rowIdx)] = 0;
            prevRightDiagHash[(rowIdx + j)] = 0;
        }
    }

    // Optimal Approach: Here we optimize the time by taking help from hashing.
    // In each iteration instead of traversing the prev row col or diagonal, get occupation information from hash
    // For row: No need to check as looping through row indexes one at a time
    // For column: Keep a vector of size `N` to store occupation by prev runs
    // For left-Upper-Diagonal: all cells ((N-1)+(colIdx-rowIdx)) values are same, so create hash of size (2N-1) on that
    // For right-upper-diagonal: all cells (rowIdx+colIdx) values are same, create hash of size (2N-1) on that
    //
    // Time: O( [N! * (1 + N^2)] ): For each N rows check for N cols; Copy N^2 `board` to `ans`
    // Space: O(N^2 + 5N) because of the `board` data structure having n strings of length n and hashes
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.')); // As n rows and n cols in the board
                                                 // we here populated the whole with '.'

        vector<int> prevColsHash(n);                // Stores if previously this column is occupied or not
        vector<int> prevleftDiagHash((2 * n - 1));  // Stores if left upper diagonal is occupied or not. Size=(2N-1)
        vector<int> prevRightDiagHash((2 * n - 1)); // Stores if right upper diagonal is occupied or not. Size=(2N-1)

        recurseQueen(ans, board, n, prevColsHash, prevleftDiagHash, prevRightDiagHash, 0);

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
