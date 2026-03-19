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

Similar:
    https://leetcode.com/problems/number-of-islands/


Problem statement:
Given a grid of size n * m (n is the number of rows and m is the number of columns in the grid) consisting of 'W's (Water) and 'L's (Land). Find the number of islands.
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
        grid[][] = [
                    [1, 1, 0, 0, 0],
                    [1, 1, 0, 0, 0],
                    [0, 0, 0, 1, 1],
                    [0, 0, 0, 1, 1]
                                    ]
    Output: 1
    Explanation:
        grid[][] = [
                    [1, 1, 0, 0, 0],
                    [1, 1, 0, 0, 0],
                    [0, 0, 0, 1, 1],
                    [0, 0, 0, 1, 1]
                                    ]
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
        Same colored islands are equal. We have 4 islands, but 2 of them are equal, So we have 3 distinct islands.


Constraints:
    1 ≤ n, m ≤ 500
    grid[i][j] == 0 or grid[i][j] == 1


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Number of Islands
//-------------------------------------------------------------------------------

//=========================================
// Approach: Connected components [OPTIMAL]
//=========================================
#include <vector>

using namespace std;

class Solution
{
private:
    int m, n;

    // Direction array for moving in all 8 directions:
    // Right, Down, Left, Up, Down-Right, Down-Left, Up-Right, Up-Left
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    /**
     * @brief Recursively explores an island and marks all its connected landmasses as visited.
     * * @idea
     * We use the Call Stack to plunge as deep as possible into the island. By marking
     * cells as visited the moment we step on them, we prevent infinite recursion loops.
     */
    void dfs(int i, int j, vector<vector<bool>> &vis, vector<vector<char>> &grid)
    {

        // Mark the current land cell as visited
        vis[i][j] = true;

        // Plunge outward in all 8 directions to find connected land
        for (int k = 0; k < 8; ++k)
        {

            int adi = i + dir[k][0];
            int adj = j + dir[k][1];

            // 1. Boundary Check: Ensure we don't step outside the grid
            if (adi < 0 || adj < 0 || adi >= m || adj >= n)
            {
                continue;
            }

            // 2. State Check: If it's already visited OR if it's Water ('W'), ignore it
            if (vis[adi][adj] || grid[adi][adj] == 'W')
            {
                continue;
            }

            // It's unvisited land! Recursively explore it.
            dfs(adi, adj, vis, grid);
        }
    }

public:
    /**
     * @brief Counts the total number of disconnected islands in a grid.
     * * @idea
     * This is a classic Connected Components problem. We sweep the entire grid.
     * Every time we find an unvisited piece of land, we have discovered a brand new
     * island. We increment our count, and then immediately use DFS to explore and
     * mark that entire island as visited so we don't double-count it later.
     * * @approach
     * 1. Initialize a boolean `vis` matrix to track visited cells without mutating the input.
     * 2. Iterate through every cell in the M x N grid.
     * 3. If a cell is unvisited and is Water ('W'), just mark it visited and move on.
     * 4. If a cell is unvisited and is Land, increment the `islands` counter and launch
     * a DFS to mark the entire 8-directional connected component as visited.
     * * @time O(M * N)
     * We scan the grid once. During the DFS, each cell is visited and processed a
     * constant number of times (at most 8 lookups from its neighbors).
     * * @space O(M * N)
     * We use O(M * N) auxiliary space for the `vis` matrix. The DFS call stack will
     * also take O(M * N) space in the absolute worst-case scenario (e.g., the entire
     * grid is one massive zigzagging island).
     */
    int countIslands(vector<vector<char>> &grid)
    {

        m = grid.size();
        n = grid[0].size();

        // Visited matrix to preserve the original grid data
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        int islands = 0;

        // --- SWEEP THE GRID ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                // If we've already processed this cell, skip it
                if (vis[i][j])
                {
                    continue;
                }
                else
                {
                    // If it's water, mark as visited so we don't check it again
                    if (grid[i][j] == 'W')
                    {
                        vis[i][j] = true;
                        continue;
                    }
                    // --- NEW ISLAND FOUND ---
                    else
                    {
                        ++islands;            // Increment our global island count
                        dfs(i, j, vis, grid); // Map out the rest of this new island
                    }
                }
            }
        }

        return islands;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Number of distinct islands
//-------------------------------------------------------------------------------

//=====================================================================================
// Approach: Connected components + structural hashing + consistent traversal [OPTIMAL]
//=====================================================================================

class Solution
{
private:
    int m, n;

    // Direction array: Right, Down, Left, Up
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    /**
     * @brief DFS to explore an island and record its exact relative shape.
     * * @idea
     * We map out the island by recording the coordinates of every connected piece
     * of land relative to the very first cell we touched (base_i, base_j).
     * * --- CONSISTENT TRAVERSAL ORDER ---
     * Notice how the `dir` array never changes. Because we always explore in a
     * strict, fixed order (Right, Down, Left, Up), our DFS is mathematically
     * guaranteed to visit the cells of identical islands in the exact same sequence.
     * If we randomized this order, identical islands would generate different
     * coordinate vectors and fail the equivalence check!
     */
    void dfs(int i, int j, int base_i, int base_j, vector<vector<int>> &grid,
             vector<vector<bool>> &vis, vector<pair<int, int>> &currentIsland)
    {

        // Mark as visited to prevent infinite loops
        vis[i][j] = true;

        // --- RECORD RELATIVE SHAPE ---
        // Subtract the base coordinates to get the relative position
        currentIsland.push_back({i - base_i, j - base_j});

        // Plunge outward in the strict 4-directional order
        for (int k = 0; k < 4; ++k)
        {

            int adi = i + dir[k][0];
            int adj = j + dir[k][1];

            // Boundary Check
            if (adi < 0 || adj < 0 || adi >= m || adj >= n)
            {
                continue;
            }

            // State Check: Skip water (0) and already visited land
            if (vis[adi][adj] || grid[adi][adj] == 0)
            {
                continue;
            }

            dfs(adi, adj, base_i, base_j, grid, vis, currentIsland);
        }
    }

public:
    /**
     * @brief Counts the number of distinct island shapes in a binary grid.
     * * @idea
     * We use a standard Connected Components sweep. When we find an unvisited piece
     * of land (1), we record its coordinates as our "Base". We run a DFS, subtracting
     * this Base from every connected cell to generate a "Relative Shape". We insert
     * this shape into a Hash Set. The set automatically filters out duplicate shapes!
     * * --- IMPLICIT STRUCTURAL HASHING ---
     * We use a `std::set<vector<pair<int, int>>>` to store our shapes. In C++,
     * the Set automatically performs a deep,
     * element-by-element lexicographical comparison. This brilliantly filters out
     * duplicate shapes without requiring us to write a complex custom hash function!
     * * @time O(N * M * log(U))
     * We visit each cell in the N x M grid at most once. U is the number of unique
     * islands. Inserting a vector of size K into a C++ `std::set` takes O(K * log(U)).
     * * @space O(N * M)
     * We use a visited matrix of size N x M. The `std::set` will store all land
     * coordinates in the worst case, and the DFS call stack takes O(N * M) if the
     * entire grid is one massive island.
     */
    int countDistinctIslands(vector<vector<int>> &grid)
    {

        m = grid.size();
        n = grid[0].size();

        vector<vector<bool>> vis(m, vector<bool>(n, false));

        // The Set natively handles deep-comparisons of our relative shape vectors
        set<vector<pair<int, int>>> uniqueIslands;

        // --- SWEEP THE GRID ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                // If we find an unvisited piece of land, map out its shape!
                if (grid[i][j] == 1 && !vis[i][j])
                {

                    vector<pair<int, int>> currentIsland;

                    // The very first piece of land acts as the Base Coordinate (i, j)
                    dfs(i, j, i, j, grid, vis, currentIsland);

                    // Insert the fully mapped relative shape into our Set
                    uniqueIslands.insert(currentIsland);
                }
            }
        }

        // The number of distinct shapes is exactly the number of unique items in the Set
        return uniqueIslands.size();
    }
};

int main()
{
    return 0;
}
