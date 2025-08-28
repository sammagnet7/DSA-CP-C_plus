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

1. Title: G-36: Shortest Distance in a Binary Maze


Links:
https://takeuforward.org/data-structure/g-36-shortest-distance-in-a-binary-maze/
https://www.youtube.com/watch?v=U5Mw4eyUmw4&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=37
https://takeuforward.org/plus/dsa/problems/shortest-path-with-minimum-effort?tab=editorial


Problem statement:
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

Examples:
    Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: 2

    Example 2:
    Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    Output: 4

    Example 3:
    Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    Output: -1

Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1




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
    // 1. Title: G-36: Shortest Distance in a Binary Maze
    //-------------------------------------------------------------------------------

    // Utility function to check if a cell (i,j) is inside the grid boundaries
    bool isIdxValid(int i, int j, int n)
    {
        return !(i < 0 || i >= n || j < 0 || j >= n);
    }

    // -------------------------------
    // DFS + Memoization Approach (TLE)
    // -------------------------------
    // Intuition:
    // We try to find the shortest path recursively. At each cell, we explore
    // all 8 directions and compute the minimum path length to reach the destination.
    // pathVis ensures we do not enter cycles, and dp is intended to memoize results.
    // This approach fails on large grids due to TLE because memoization does not
    // guarantee shortest path in all cases for unweighted grids.
    int rec(int src_i, int src_j, vector<vector<int>> &grid, vector<vector<int>> &dp,
            vector<vector<int>> &delta, vector<vector<int>> &pathVis, int n)
    {

        // Base case: reached the destination
        if (src_i == n - 1 && src_j == n - 1)
        {
            return 1;
        }

        // We cannot use dp[src_i][src_j] here to early return,
        // because minimization can happen later along other paths
        // if(dp[src_i][src_j] != 1e9)
        //     return dp[src_i][src_j];

        int min_dist = 1e9; // Initialize the minimum distance from this cell

        pathVis[src_i][src_j] = 1; // Mark current cell as visited

        // Explore all 8 directions
        for (int k = 0; k < 8; k++)
        {
            int k_i = src_i + delta[k][0];
            int k_j = src_j + delta[k][1];

            if (isIdxValid(k_i, k_j, n) && grid[k_i][k_j] != 1)
            {
                if (pathVis[k_i][k_j] == 1)
                {
                    continue; // Skip already visited cells in current path
                }
                // Recursive call for neighbor cell
                int cur_dist = 1 + rec(k_i, k_j, grid, dp, delta, pathVis, n);
                min_dist = min(min_dist, cur_dist); // Keep track of minimum distance
            }
        }

        pathVis[src_i][src_j] = 0; // Unmark for other paths

        // Memoize the result
        return dp[src_i][src_j] = min_dist;
    }

    // This function uses DFS + Memoization (TLE version)
    // int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    //     int n = grid.size();

    //     // Edge case: blocked start or destination
    //     if(grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;

    //     vector<vector<int>> dp(n, vector<int>(n, 1e9));
    //     vector<vector<int>> pathVis(n, vector<int>(n, 0));

    //     // All 8 possible moves (orthogonal + diagonal)
    //     vector<vector<int>> delta = {
    //         {0,-1}, {0,1}, {-1,0}, {1,0},
    //         {1,1}, {-1,-1}, {-1,1}, {1,-1}
    //     };

    //     int ans = rec(0,0, grid, dp, delta, pathVis, n);

    //     // If no path is found, return -1
    //     if(ans == 1e9) return -1;
    //     else return ans;
    // }

    // -------------------------------
    // BFS Approach (Works Correctly)
    // -------------------------------
    // Intuition:
    // The problem includes finding the shortest path from the source to destination
    // which gives the idea of using a Dijsktra's Algorithm.
    // But since, all the edges are of unit weight, instead of using Dijsktra's algorithm,
    // a simple BFS traversal will get the job done.
    // Each level in BFS represents distance from the starting point.

    // Time Complexity Analysis:
    // DFS + Memoization: O(N*M*8) in worst case, but can TLE due to path exploration order
    // BFS: O(N*M), each cell visited once, 8 neighbors checked

    // Space Complexity Analysis:
    // Both DFS and BFS: O(N*M) for distance/memo array + O(N*M) for recursion stack (DFS) or queue (BFS)

    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {

        int n = grid.size();

        // Edge case: blocked start or destination
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;

        // 8 directions: up, down, left, right, and 4 diagonals
        vector<vector<int>> delta = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

        // Queue stores: {distance_so_far, {row, col}}
        queue<pair<int, pair<int, int>>> q;

        // Distance array to store shortest distance from destination
        vector<vector<int>> dist(n, vector<int>(n, 1e9));

        // Start BFS from the destination cell (can also start from source)
        q.push({0, {n - 1, n - 1}});
        dist[n - 1][n - 1] = 0;

        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();

            int curN_dist = cur.first;
            int curN_i = cur.second.first;
            int curN_j = cur.second.second;

            // Explore all neighbors
            for (int k = 0; k < 8; k++)
            {

                int newN_dist = curN_dist + 1;
                int adjN_i = curN_i + delta[k][0];
                int adjN_j = curN_j + delta[k][1];

                // If neighbor is valid, unblocked, and offers shorter path
                if (isIdxValid(adjN_i, adjN_j, n) && grid[adjN_i][adjN_j] != 1 && newN_dist < dist[adjN_i][adjN_j])
                {
                    dist[adjN_i][adjN_j] = newN_dist;
                    q.push({newN_dist, {adjN_i, adjN_j}});
                }
            }
        }

        // If source cell is unreachable, return -1
        if (dist[0][0] == 1e9)
            return -1;
        else
            return dist[0][0] + 1; // +1 to include the starting cell
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
