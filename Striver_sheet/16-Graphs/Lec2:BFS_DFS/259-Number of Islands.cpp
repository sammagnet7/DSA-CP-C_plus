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

1. Title: Number of Islands


Links:
https://takeuforward.org/data-structure/number-of-islands/
https://www.youtube.com/watch?v=muncqlKJrH0
https://www.geeksforgeeks.org/problems/find-the-number-of-islands/1

Similar: https://leetcode.com/problems/number-of-islands/submissions/1747903811/


Problem statement:
Given a grid of size n*m (n is the number of rows and m is the number of columns in the grid) consisting of 'W's (Water) and 'L's (Land). Find the number of islands.
Note: An island is either surrounded by water or the boundary of a grid and is formed by connecting adjacent lands horizontally or vertically or diagonally i.e., in all 8 directions.

Examples:
    Input: grid[][] = [['L', 'L', 'W', 'W', 'W'], ['W', 'L', 'W', 'W', 'L'], ['L', 'W', 'W', 'L', 'L'], ['W', 'W', 'W', 'W', 'W'], ['L', 'W', 'L', 'L', 'W']]
    Output: 4
    Explanation:
    The image below shows all the 4 islands in the grid.

    Input: grid[][] = [['W', 'L', 'L', 'L', 'W', 'W', 'W'], ['W', 'W', 'L', 'L', 'W', 'L', 'W']]
    Output: 2
    Expanation:
    The image below shows 2 islands in the grid.

Constraints:
    1 ≤ n, m ≤ 500
    grid[i][j] = {'L', 'W'}


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Number of distinct islands


Links:
https://www.youtube.com/watch?v=7zmgQSJghpo&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=16
https://takeuforward.org/plus/dsa/problems/number-of-distinct-islands?tab=editorial
https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1



Problem statement:
Given a boolean 2D matrix grid of size n * m. You have to find the number of distinct islands where a group of connected 1s (horizontally or vertically) forms an island. Two islands are considered to be distinct if and only if one island is not equal to another (not rotated or reflected).

Example 1:
    Input:
    grid[][] = [[1, 1, 0, 0, 0],
                [1, 1, 0, 0, 0],
                [0, 0, 0, 1, 1],
                [0, 0, 0, 1, 1]]
    Output: 1
    Explanation:
    grid[][] = [[1, 1, 0, 0, 0],
                [1, 1, 0, 0, 0],
                [0, 0, 0, 1, 1],
                [0, 0, 0, 1, 1]]
    Same colored islands are equal. We have 2 equal islands, so we have only 1 distinct island.

Example 2:
    Input:
    grid[][] = [
                [1, 1, 0, 1, 1],
                [1, 0, 0, 0, 0],
                [0, 0, 0, 0, 1],
                [1, 1, 0, 1, 1]
                ]
    Output: 3
    Explanation:
    grid[][] = [
                [1, 1, 0, 1, 1],
                [1, 0, 0, 0, 0],
                [0, 0, 0, 0, 1],
                [1, 1, 0, 1, 1]
                ]
    Same colored islands are equal.
    We have 4 islands, but 2 of them
    are equal, So we have 3 distinct islands.


Constraints:
    1 ≤ n, m ≤ 500
    grid[i][j] == 0 or grid[i][j] == 1


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Number of Islands
    //-------------------------------------------------------------------------------

    // All 8 possible directions (horizontal, vertical, and diagonal)
    int dist[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // up, down, left, right
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1} // diagonals
    };

    /**
     * @brief Check if the given index (i, j) is within grid bounds
     *
     * @param i current row
     * @param j current column
     * @param m total rows
     * @param n total columns
     * @return true if within bounds, false otherwise
     */
    bool isValIdx(int i, int j, int m, int n)
    {
        return !(i < 0 || j < 0 || i >= m || j >= n);
    }

    /**
     * @brief Perform DFS to mark all connected 'L' (land) cells as visited
     *
     * @param i current row
     * @param j current column
     * @param grid input grid containing 'L' for land and 'W' for water
     * @param vis visited matrix
     * @param m total rows
     * @param n total columns
     *
     * This function recursively explores all 8 directions from the current cell
     * and marks connected land cells as visited.
     */
    void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<int>> &vis, int m, int n)
    {

        vis[i][j] = 1; // mark current cell as visited

        // Check all 8 possible directions
        for (int k = 0; k < 8; k++)
        {

            int r = i + dist[k][0];
            int c = j + dist[k][1];

            // Skip if out of bounds, already visited, or not land
            if (!isValIdx(r, c, m, n) || vis[r][c] || grid[r][c] != 'L')
                continue;

            dfs(r, c, grid, vis, m, n);
        }
    }

    /**
     * @brief Count number of islands in the given grid
     *
     * @param grid 2D grid where 'L' represents land and 'W' represents water
     * @return int total number of islands
     *
     * Approach:
     * - Use DFS to traverse connected land cells (8-directional).
     * - For every unvisited land cell, start a DFS and increment island count.
     *
     * Time Complexity: O(M * N) where M = rows, N = columns
     * - Each cell is visited at most once.
     *
     * Space Complexity: O(M * N)
     * - For visited matrix and recursion stack (in worst case, all cells are land).
     */
    int countIslands(vector<vector<char>> &grid)
    {

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n, 0)); // visited matrix

        int ans = 0; // island count

        // Traverse entire grid
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                // If current cell is land and not visited, start DFS
                if (grid[i][j] == 'L' && !vis[i][j])
                {
                    dfs(i, j, grid, vis, m, n);
                    ans++; // increment island count
                }
            }
        }

        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Number of distinct islands
    //-------------------------------------------------------------------------------

    // Four possible directions (up, down, left, right)
    int dist[4][2] = {
        {1, 0},  // down
        {-1, 0}, // up
        {0, 1},  // right
        {0, -1}  // left
    };

    /**
     * @brief Check if the given (i, j) is a valid index within grid bounds
     *
     * @param i current row index
     * @param j current column index
     * @param m total rows
     * @param n total columns
     * @return true if within bounds, false otherwise
     */
    bool isValIdx(int i, int j, int m, int n)
    {
        return !(i < 0 || j < 0 || i >= m || j >= n);
    }

    /**
     * @brief DFS to explore and store normalized coordinates of an island
     *
     * @param i current row
     * @param j current column
     * @param norm_coord vector storing relative coordinates of current island
     * @param grid input grid (1 = land, 0 = water)
     * @param vis visited matrix
     * @param m number of rows
     * @param n number of columns
     * @param base base coordinate (starting cell of island) for normalization
     *
     * Approach:
     * - Mark current cell as visited
     * - Normalize its position by subtracting base cell coordinates
     * - Push normalized position into norm_coord
     * - Explore all 4 adjacent cells recursively if they are valid and land
     */
    void dfs(int i, int j, vector<pair<int, int>> &norm_coord, vector<vector<int>> &grid, vector<vector<int>> &vis, int m, int n, pair<int, int> base)
    {

        vis[i][j] = 1; // mark current cell as visited

        // Normalize coordinates relative to base (starting point of the island)
        int norm_i = i - base.first;
        int norm_j = j - base.second;
        norm_coord.push_back({norm_i, norm_j});

        // Explore all 4 directions
        for (int k = 0; k < 4; k++)
        {
            int r = i + dist[k][0];
            int c = j + dist[k][1];

            // Skip if out of bounds, already visited, or not land
            if (!isValIdx(r, c, m, n) || vis[r][c] || grid[r][c] != 1)
                continue;

            dfs(r, c, norm_coord, grid, vis, m, n, base);
        }
    }

    /**
     * @brief Count number of distinct islands in a binary grid
     *
     * @param grid 2D grid where 1 = land and 0 = water
     * @return int number of distinct islands
     *
     * Approach:
     * - Traverse the entire grid
     * - For each unvisited land cell, perform DFS to extract all its coordinates
     * - Normalize the coordinates of the island relative to its starting point
     * - Store normalized coordinates in a set (to maintain uniqueness)
     * - The size of the set represents the number of distinct island shapes
     *
     * Why normalization?
     * - Two islands with the same shape but different positions should be counted as the same
     *
     * Time Complexity: O(M * N) where M = rows, N = columns
     * - Each cell is visited at most once, DFS explores all connected cells.
     * - Insertion into set is O(K log S) where K = island size, S = number of islands
     *
     * Space Complexity: O(M * N)
     * - For visited matrix and recursion stack (in worst case all land cells)
     * - Additional space for storing islands in a set
     */
    int countDistinctIslands(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n, 0)); // visited matrix
        set<vector<pair<int, int>>> dist_islands;      // set to store unique normalized islands

        // Traverse the entire grid
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                // If current cell is land and not visited, start DFS
                if (grid[i][j] == 1 && !vis[i][j])
                {
                    vector<pair<int, int>> norm_coord; // normalized coordinates

                    // Perform DFS and collect normalized coordinates
                    dfs(i, j, norm_coord, grid, vis, m, n, {i, j});

                    // Insert island shape into set
                    dist_islands.insert(norm_coord);
                }
            }
        }

        // Return the number of distinct islands
        return dist_islands.size();
    }
};

int main()
{
    return 0;
}
