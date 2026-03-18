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

1. Title: Surrounded Regions [Connected components]


Links:
https://takeuforward.org/graph/surrounded-regions-replace-os-with-xs/
https://www.youtube.com/watch?v=BtdgAys4yMk
https://takeuforward.org/plus/dsa/problems/surrounded-regions?tab=editorial
https://leetcode.com/problems/surrounded-regions/

Similar:
    https://leetcode.com/problems/number-of-enclaves/description/


Problem statement:
Given a matrix mat of size N x M where every element is either ‘O’ or ‘X’. Replace all ‘O’ with ‘X’ that is surrounded by ‘X’.
An ‘O’ (or a set of ‘O’) is considered to be surrounded by ‘X’ if there are ‘X’ at locations just below, just above just left, and just right of it.

Examples:
    Example 1:
    Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
    Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
    Explanation:
    In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.

    Example 2:
    Input: board = [["X"]]
    Output: [["X"]]


Constraints:
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'.



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
// 1. Title: Surrounded Regions [Connected components]
//-------------------------------------------------------------------------------

//============================================================================
// Approach 1: BFS-based (Multi-source from boundary)
//============================================================================

class Solution
{
private:
    // Direction array for moving right, left, down, up
    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    /**
     * @brief Captures surrounded regions using Multi-Source BFS.
     * * @idea
     * Instead of looking for trapped 'O's, we use "Reverse Thinking" to find the
     * safe 'O's. Any 'O' connected to the boundary cannot be surrounded. We gather
     * all boundary 'O's and run a Multi-Source BFS to mark their entire connected
     * components as safe.
     * * @approach
     * 1. Scan only the borders of the matrix. If we find an 'O', change it to 'M'
     * (Marked/Safe) and push it into our BFS queue.
     * 2. Run the BFS. For every connected 'O', mark it as 'M' and queue it.
     * 3. Do one final sweep of the entire board. If a cell is 'M', it's safe—revert
     * it to 'O'. If a cell is 'O', it was trapped—flip it to 'X'.
     * * @time O(M * N)
     * The boundary scan takes O(M + N). The BFS visits each safe 'O' exactly once.
     * The final board sweep takes O(M * N).
     * * @space O(M * N)
     * We achieve O(1) auxiliary space for visited tracking by mutating the board
     * in-place. The only extra space is the BFS queue, which takes O(M * N) in the worst case.
     */
    void solve(vector<vector<char>> &board)
    {

        int m = board.size();
        int n = board[0].size();

        queue<tuple<int, int>> q;

        // --- STEP 1: GATHER BORDER SURVIVORS (Optimized Scan) ---

        // Check first and last column
        for (int i = 0; i < m; ++i)
        {
            if (board[i][0] == 'O')
            {
                board[i][0] = 'M';
                q.push({i, 0});
            }
            if (board[i][n - 1] == 'O')
            {
                board[i][n - 1] = 'M';
                q.push({i, n - 1});
            }
        }

        // Check first and last row
        for (int j = 0; j < n; ++j)
        {
            // Note: Corners might be checked twice, but the 'O' check prevents duplicate pushing
            if (board[0][j] == 'O')
            {
                board[0][j] = 'M';
                q.push({0, j});
            }
            if (board[m - 1][j] == 'O')
            {
                board[m - 1][j] = 'M';
                q.push({m - 1, j});
            }
        }

        // --- STEP 2: MULTI-SOURCE BFS (Mark all connected safe zones) ---
        while (!q.empty())
        {

            auto [i, j] = q.front();
            q.pop();

            // Plunge outward in all 4 directions
            for (int k = 0; k < 4; ++k)
            {

                int adi = i + dir[k][0];
                int adj = j + dir[k][1];

                // Boundary check
                if (adi < 0 || adj < 0 || adi >= m || adj >= n)
                {
                    continue;
                }

                // State check: Only spread to connected 'O's
                if (board[adi][adj] != 'O')
                {
                    continue;
                }

                // Mark as safe and push to queue
                board[adi][adj] = 'M';
                q.push({adi, adj});
            }
        }

        // --- STEP 3: THE GREAT FLIP ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // If it's 'M', it's safe ('O'). Otherwise, it's either an original 'X'
                // or a trapped 'O', both of which become 'X'.
                board[i][j] = (board[i][j] == 'M') ? 'O' : 'X';
            }
        }
    }
};

//============================================================================
// Approach 2: DFS-based (Multi-source from boundary)
//============================================================================

class Solution
{
private:
    int m, n;

    // Direction array for moving right, left, down, up
    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    /**
     * @brief Recursively explores and marks a contiguous region of 'O's as safe ('M').
     * * @idea
     * We use the Call Stack to plunge as deep as possible into connected 'O' cells.
     * By immediately marking a visited cell as 'M', we naturally prevent infinite
     * recursion loops without needing a separate boolean visited matrix.
     */
    void dfs(vector<vector<char>> &board, int i, int j)
    {

        // 1. Boundary Check: Ensure we don't step outside the board
        // 2. State Check: If we hit water ('X') or an already marked safe zone ('M'), stop.
        if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != 'O')
        {
            return;
        }

        // --- MARK AS SAFE ---
        board[i][j] = 'M';

        // Recursively plunge outward in all 4 adjacent directions
        for (int k = 0; k < 4; ++k)
        {
            dfs(board, i + dir[k][0], j + dir[k][1]);
        }
    }

public:
    /**
     * @brief Captures surrounded regions using Depth-First Search.
     * * @idea
     * "Reverse Thinking": Any 'O' connected to the boundary is safe and cannot be
     * surrounded. We scan the perimeter, and if we find an 'O', we trigger our DFS
     * to mark that entire connected component as safe ('M'). After exploring the
     * boundaries, any remaining 'O's in the middle of the board are guaranteed
     * to be trapped and can be safely flipped to 'X'.
     * * @time O(M * N)
     * Scanning the boundaries takes O(M + N). In the worst case, the DFS visits each
     * cell exactly once. The final grid sweep takes O(M * N).
     * * @space O(M * N)
     * We achieve O(1) auxiliary space by mutating the board directly. The only extra
     * memory is the DFS Recursion Call Stack, which takes O(M * N) in the absolute
     * worst case (e.g., the entire board is 'O's).
     */
    void solve(vector<vector<char>> &board)
    {

        m = board.size();
        n = board[0].size();

        // --- STEP 1: GATHER BORDER SURVIVORS (Optimized O(M+N) Scan) ---
        // For every boundary 'O', we trigger a DFS to mark its whole connected island as 'M'.

        // Scan the first and last column
        for (int i = 0; i < m; ++i)
        {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
            if (board[i][n - 1] == 'O')
                dfs(board, i, n - 1);
        }

        // Scan the first and last row
        for (int j = 0; j < n; ++j)
        {
            if (board[0][j] == 'O')
                dfs(board, 0, j);
            if (board[m - 1][j] == 'O')
                dfs(board, m - 1, j);
        }

        // --- STEP 2: THE GREAT FLIP ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                // If it's 'M', it's safe (revert to 'O').
                // Otherwise, it's either an original 'X' or a trapped 'O', both become 'X'.
                board[i][j] = (board[i][j] == 'M') ? 'O' : 'X';
            }
        }
    }
};

int main()
{
    return 0;
}
