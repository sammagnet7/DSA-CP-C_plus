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

Sudoku Solver:

https://takeuforward.org/data-structure/sudoku-solver/
https://leetcode.com/problems/sudoku-solver/description/


Problem statement:
Write a program to solve a Sudoku puzzle by filling the empty cells.
A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

Examples:

Example 1:
Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:

Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Sudoku Solver:

    // O(N)
    bool isCurCellNumberValid(vector<vector<char>> &board, int N, int curRowIdx, int curColIdx, char curCellChar)
    {

        int matrixSize = N;
        int subMatrixSize = sqrt(matrixSize);

        for (int k = 0; k < N; k++)
        {
            // Iterates over the same row of curRow
            if (board[k][curColIdx] == curCellChar)
                return false;

            // Iterates over the same column as curCol
            if (board[curRowIdx][k] == curCellChar)
                return false;

            // Iterates over the same sub-matrix as curRow-curCol cell belongs to
            int subMatrixStartRow = subMatrixSize * (curRowIdx / subMatrixSize);
            int subMatrixStartCol = subMatrixSize * (curColIdx / subMatrixSize);

            int subMatrixRowIdx =  subMatrixStartRow + k / subMatrixSize;
            int subMatrixColIdx =  subMatrixStartCol + k % subMatrixSize;

            if (board[subMatrixRowIdx][subMatrixColIdx] == curCellChar)
                return false;
        }

        return true;
    }

    // O(9^(N∗N) ∗ N)
    bool recurseSudoku(vector<vector<char>> &board, int N, int curRowIdx, int curColIdx)
    {

        // If we've reached the end of the board
        if (curRowIdx == N)
            return true;

        // Compute next cell's indices for 2D matrix
        int nextRowIdx = (curColIdx == N - 1) ? (curRowIdx + 1) : curRowIdx;
        int nextColIdx = (curColIdx == N - 1) ? 0 : (curColIdx + 1);

        if (board[curRowIdx][curColIdx] != '.')
        {
            return recurseSudoku(board, N, nextRowIdx, nextColIdx); // Skip pre-filled cells
        }

        //
        for (int ch = '1'; ch <= '9'; ch++)
        {

            if (isCurCellNumberValid(board, N, curRowIdx, curColIdx, ch))
            {
                board[curRowIdx][curColIdx] = ch;

                if (recurseSudoku(board, N, nextRowIdx, nextColIdx))
                    return true;

                board[curRowIdx][curColIdx] = '.';
            }
        }

        return false;
    }

    // Optimal approach: Recursion for each cells in the matrix + Iteration for each number per cell
    // Time: O(9^(N∗N) ∗ N): per step 9 possible numbers to choose from;
    // For each number recurse stack can grow to length (N*N)
    // Each time check isvalid number for N cells
    // Space: O(1)
    void solveSudoku(vector<vector<char>> &board)
    {

        recurseSudoku(board, board.size(), 0, 0);
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
