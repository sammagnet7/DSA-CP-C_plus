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

1. Title: Surrounded Regions | Replace O’s with X’s


Links:
https://takeuforward.org/graph/surrounded-regions-replace-os-with-xs/
https://www.youtube.com/watch?v=BtdgAys4yMk
https://takeuforward.org/plus/dsa/problems/surrounded-regions?tab=editorial
https://leetcode.com/problems/surrounded-regions/submissions/1747411603/


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

2. Title: Number of Enclaves [flood fill implementation - multisource]

Links:
https://takeuforward.org/graph/number-of-enclaves/
https://www.youtube.com/watch?v=rxKcepXQgU4
https://takeuforward.org/plus/dsa/problems/number-of-enclaves?tab=editorial
https://leetcode.com/problems/number-of-enclaves/description/


Problem statement:
You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

Example:
    Example 1:
    Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
    Output: 3
    Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.

    Example 2:
    Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
    Output: 0
    Explanation: All 1s are either on the boundary or can reach the boundary.


Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 500
    grid[i][j] is either 0 or 1.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Surrounded Regions | Replace O’s with X’s
    //-------------------------------------------------------------------------------

    // Direction array for moving in 4 directions: Down, Up, Right, Left
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    /**
     * Helper function to check if (r, c) is a valid index within matrix bounds.
     * @param r: current row
     * @param c: current column
     * @param m: total rows
     * @param n: total columns
     * @return true if valid index, false otherwise
     */
    bool isIdxValid(int r, int c, int m, int n)
    {
        return !(r < 0 || r >= m || c < 0 || c >= n);
    }

    /**
     * DFS function to mark all connected 'O' cells starting from (i, j).
     * These represent boundary-connected regions which should NOT be flipped.
     * @param i, j: current cell coordinates
     * @param vis: visited matrix to track processed cells
     * @param board: input board of 'X' and 'O'
     * @param m, n: dimensions of the board
     */
    void markDFS(int i, int j, vector<vector<int>> &vis, vector<vector<char>> &board, int m, int n)
    {
        vis[i][j] = 1; // mark as visited

        // Explore all 4 directions
        for (int k = 0; k < 4; k++)
        {
            int r = i + dir[k][0];
            int c = j + dir[k][1];

            // Skip invalid or already visited or 'X' cells
            if (!isIdxValid(r, c, m, n))
                continue;
            if (vis[r][c] || board[r][c] == 'X')
                continue;

            // Recurse for valid 'O' cell
            markDFS(r, c, vis, board, m, n);
        }
    }

    /**
     * Main function to solve the "Surrounded Regions" problem.
     * Approach:
     * 1. Identify all 'O's connected to boundary and mark them as safe (cannot be flipped).
     * 2. For all other unvisited 'O's, flip them to 'X'.
     *
     * Time Complexity: O(M * N) - each cell visited at most once.
     * Space Complexity: O(M * N) for visited array + recursion stack.
     *
     * @param board: reference to the input 2D board
     */
    void solve(vector<vector<char>> &board)
    {
        int m = board.size();
        int n = board[0].size();

        // Visited matrix to keep track of processed cells
        vector<vector<int>> vis(m, vector<int>(n, 0));

        // Step 1: Traverse boundary cells and run DFS for each 'O'
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                // Only process boundary cells
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                {

                    // If it's already visited or 'X', skip
                    if (board[i][j] == 'X' || vis[i][j])
                        continue;

                    // Run DFS for boundary 'O'
                    markDFS(i, j, vis, board, m, n);
                }
            }
        }

        // Step 2: Flip all unvisited 'O's to 'X'
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j])
                {
                    board[i][j] = 'X';
                }
            }
        }
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Number of Enclaves [flood fill implementation - multisource]
    //-------------------------------------------------------------------------------

    //============================================================================
    // Approach 1: DFS-based Flood Fill (Multi-source from boundary)
    //============================================================================

    // Direction array for 4 possible moves: Down, Up, Right, Left
    int disDFS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    /**
     * Check if a given (i, j) lies within the grid boundaries.
     *
     * @param i, j: Current cell coordinates
     * @param m, n: Grid dimensions
     * @return true if (i, j) is a valid index within grid, false otherwise
     */
    bool isValidIdx(int i, int j, int m, int n)
    {
        return !(i < 0 || j < 0 || i >= m || j >= n);
    }

    /**
     * DFS function to mark all land cells (1) connected to (i, j) as visited.
     * These cells are connected to the boundary, so they cannot be enclaves.
     *
     * @param i, j: Current cell coordinates
     * @param grid: Input grid (1 = land, 0 = water)
     * @param vis: Visited matrix
     * @param m, n: Grid dimensions
     */
    void markDFS(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &vis, int m, int n)
    {
        vis[i][j] = 1; // Mark current cell as visited

        // Explore 4 directions
        for (int k = 0; k < 4; k++)
        {
            int r = i + disDFS[k][0];
            int c = j + disDFS[k][1];

            // Skip if out of bounds, already visited, or water
            if (!isValidIdx(r, c, m, n) || vis[r][c] || grid[r][c] != 1)
                continue;

            // Recursive DFS call
            markDFS(r, c, grid, vis, m, n);
        }
    }

    /**
     * Count number of land cells that cannot reach the boundary (enclaves).
     *
     * Steps:
     * 1. Traverse all boundary cells.
     * 2. For each unvisited land cell on the boundary, run DFS to mark all connected cells.
     * 3. Count remaining unvisited land cells in the grid.
     *
     * Time Complexity: O(M * N) - Each cell visited once
     * Space Complexity: O(M * N) - Visited matrix + DFS recursion stack
     *
     * @param grid: 2D grid representing land and water
     * @return number of enclaves
     */

    int numEnclaves(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));

        // Step 1: DFS from boundary land cells
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
                {
                    if (grid[i][j] == 1 && !vis[i][j])
                        markDFS(i, j, grid, vis, m, n);
                }
            }
        }

        // Step 2: Count unvisited land cells
        int count = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1 && !vis[i][j])
                    count++;
            }
        }
        return count;
    }

    //============================================================================
    // Approach 2: BFS-based Flood Fill (Multi-source from boundary)
    //============================================================================

    // Direction array for BFS: Down, Up, Right, Left
    int disBFS[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    /**
     * BFS function to mark all land cells connected to (i, j) as visited.
     *
     * Steps:
     * - Start BFS from boundary land cell
     * - For each cell, explore its 4 neighbors and enqueue valid land cells
     *
     * @param cur_i, cur_j: Starting cell coordinates
     * @param grid: Input grid
     * @param vis: Visited matrix
     * @param m, n: Grid dimensions
     *
     * Time Complexity: O(M * N)
     * Space Complexity: O(M * N) for queue and visited matrix
     */
    void markBFS(int cur_i, int cur_j, vector<vector<int>> &grid, vector<vector<int>> &vis, int m, int n)
    {
        queue<pair<int, int>> q;
        q.push({cur_i, cur_j});
        vis[cur_i][cur_j] = 1;

        while (!q.empty())
        {
            int i = q.front().first;
            int j = q.front().second;
            q.pop();

            // Explore 4 directions
            for (int k = 0; k < 4; k++)
            {
                int r = i + disBFS[k][0];
                int c = j + disBFS[k][1];

                if (!isValidIdx(r, c, m, n) || vis[r][c] || grid[r][c] != 1)
                    continue;

                vis[r][c] = 1;
                q.push({r, c});
            }
        }
    }

    /**
     * Count number of enclaves using BFS.
     *
     * Approach:
     * - Similar to DFS approach, but uses BFS for marking boundary-connected lands.
     *
     * Time Complexity: O(M * N)
     * Space Complexity: O(M * N)
     *
     * @param grid: 2D grid representing land and water
     * @return number of enclaves
     */

    int numEnclaves(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vis(m, vector<int>(n, 0));

        // BFS from boundary land cells
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
                {
                    if (grid[i][j] == 1 && !vis[i][j])
                        markBFS(i, j, grid, vis, m, n);
                }
            }
        }

        // Count unvisited land cells
        int count = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1 && !vis[i][j])
                    count++;
            }
        }
        return count;
    }
};

int main()
{
    return 0;
}
