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

1. Title: Minimum Cost Path with Teleportations

Links:
https://leetcode.com/problems/minimum-cost-path-with-teleportations/description/?envType=daily-question&envId=2026-01-28


Problem statement:
You are given a m x n 2D integer array grid and an integer k. You start at the top-left cell (0, 0) and your goal is to reach the bottom‐right cell (m - 1, n - 1).

There are two types of moves available:

Normal move: You can move right or down from your current cell (i, j), i.e. you can move to (i, j + 1) (right) or (i + 1, j) (down). The cost is the value of the destination cell.

Teleportation: You can teleport from any cell (i, j), to any cell (x, y) such that grid[x][y] <= grid[i][j]; the cost of this move is 0. You may teleport at most k times.

Return the minimum total cost to reach cell (m - 1, n - 1) from (0, 0).



Example 1:
Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
Output: 7
Explanation:
Initially we are at (0, 0) and cost is 0.
Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 5 = 7
(1, 1)	Teleport to (2, 2)	(2, 2)	7 + 0 = 7
The minimum cost to reach bottom-right cell is 7.

Example 2:
Input: grid = [[1,2],[2,3],[3,4]], k = 1
Output: 9
Explanation:
Initially we are at (0, 0) and cost is 0.
Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 3 = 5
(1, 1)	Move Down	(2, 1)	5 + 4 = 9
The minimum cost to reach bottom-right cell is 9.



Constraints:
2 <= m, n <= 80
m == grid.length
n == grid[i].length
0 <= grid[i][j] <= 104
0 <= k <= 10



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:


Problem statement:


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Minimum Cost Path with Teleportations
//-------------------------------------------------------------------------------

//--------------------------------
// Approach 1: Brute force [TLE]
//--------------------------------
// (M*N)^2 ~ 10^8
class Solution
{
public:
  int rec(int i, int j, int k, vector<vector<int>> &grid, int M, int N, vector<vector<vector<int>>> &DP)
  {

    if (i == M - 1 && j == N - 1)
    {
      return 0;
    }

    if (DP[i][j][k] != -1)
    {
      return DP[i][j][k];
    }

    int minCost = 1e9;
    int right = 1e9;
    int down = 1e9;

    if (j + 1 < grid[0].size())
    {
      right = grid[i][j + 1] + rec(i, j + 1, k, grid, M, N, DP);
    }
    if (i + 1 < grid.size())
    {
      down = grid[i + 1][j] + rec(i + 1, j, k, grid, M, N, DP);
    }

    minCost = min(minCost, min(right, down));

    if (k > 0)
    {
      for (int x = 0; x < M; x++)
      {
        for (int y = 0; y < N; y++)
        {
          if ((x == i && y == j))
          {
            continue;
          }
          if (grid[x][y] <= grid[i][j])
          {
            minCost = min(minCost, rec(x, y, k - 1, grid, M, N, DP));
          }
        }
      }
    }

    return DP[i][j][k] = minCost;
  }

  int minCost(vector<vector<int>> &grid, int k)
  {

    int M = grid.size();
    int N = grid[0].size();

    vector<vector<vector<int>>> DP(M, vector<vector<int>>(N, vector<int>(k + 1, -1)));

    return rec(0, 0, k, grid, M, N, DP);
  }
};

//----------------------------------
// Approach 2: Iterative [OPTIMAL]
//----------------------------------

class Solution
{
public:
  /*
   * METHOD: minCost
   * ----------------
   * APPROACH: Layered Dynamic Programming + Bucket Optimization
   * * This problem is modeled as finding the shortest path in a graph with K layers (representing teleports).
   * * 1. Layered Iteration:
   * We perform K iterations. Each iteration represents allowing ONE additional teleport.
   * - 'dist[i][j]' tracks the minimum cost to reach cell (i, j).
   * * 2. Propagation (Walking):
   * Since we can only move Right and Down, the grid is a DAG (Directed Acyclic Graph) for normal moves.
   * We can propagate costs in a single linear pass from (0,0) to (m-1, n-1).
   * * 3. Teleport Optimization (Bucket Strategy):
   * A naive check for teleporting from ANY valid cell to ANY valid cell takes O((MN)^2), which causes TLE.
   * Instead, we use a "Bucket" array 'min_val_cost':
   * - Step A: Store the min cost to reach each specific grid value.
   * - Step B: Use Suffix Minimums. If we can reach a value 'X' cheaply, we can teleport to any value <= X.
   * So, the cost to teleport TO value 'v' is min(cost of any source >= v).
   * - Step C: Update all cells in O(1) using this precomputed array.
   * * COMPLEXITY:
   * Time: O(K * (M*N + V))
   * - K: Number of teleports (<= 10)
   * - M*N: Grid size (<= 6400)
   * - V: Value range (<= 10,000)
   * Total operations ~ 1.6 * 10^5, which is extremely fast.
   * * Space: O(M*N + V)
   * - O(M*N) for the distance grid.
   * - O(V) for the bucket array.
   */
  int minCost(vector<vector<int>> &grid, int k)
  {
    int m = grid.size();
    int n = grid[0].size();

    // DP grid to store min cost to reach each cell.
    // Initialize with infinity (1e9) to represent unreachability.
    vector<vector<int>> dist(m, vector<int>(n, 1e9));

    // Base Case: Starting point cost is 0
    dist[0][0] = 0;

    // --- Helper Lambda: Propagate Normal Moves ---
    // Since moves are only Right/Down, we can simply iterate top-left to bottom-right.
    auto propagate_moves = [&]()
    {
      for (int i = 0; i < m; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          // 1. Try moving from Top neighbor
          if (i > 0)
          {
            dist[i][j] = min(dist[i][j], dist[i - 1][j] + grid[i][j]);
          }
          // 2. Try moving from Left neighbor
          if (j > 0)
          {
            dist[i][j] = min(dist[i][j], dist[i][j - 1] + grid[i][j]);
          }
        }
      }
    };

    // 1. Initial Phase: Compute costs with 0 teleports (Only walking)
    propagate_moves();

    // 2. Iterative Phase: Add 1 teleport capability per loop, up to K
    for (int step = 0; step < k; ++step)
    {

      // --- OPTIMIZATION: BUCKET STRATEGY ---

      // Step A: Snapshot current costs by value
      // min_val_cost[v] will store the cheapest known cost to reach a cell with value 'v'
      vector<int> min_val_cost(10002, 1e9);

      for (int i = 0; i < m; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          int val = grid[i][j];
          min_val_cost[val] = min(min_val_cost[val], dist[i][j]);
        }
      }

      // Step B: Compute Suffix Minimums
      // Rule: You can teleport TO 'v' from any source with value >= 'v'.
      // Therefore, min_val_cost[v] should become min(min_val_cost[v], min_val_cost[v + 1]);
      for (int v = 10000; v >= 0; --v)
      {
        min_val_cost[v] = min(min_val_cost[v], min_val_cost[v + 1]);
      }

      // Step C: Apply Teleportation
      // For every cell (i, j), check if teleporting INTO it is cheaper than the current cost.
      // min_val_cost[grid[i][j]] now holds the min cost of any valid launchpad (value >= current).
      for (int i = 0; i < m; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          dist[i][j] = min(dist[i][j], min_val_cost[grid[i][j]]);
        }
      }

      // Step D: Propagate Moves again
      // After teleporting to random spots, we spread the savings to adjacent cells via walking.
      propagate_moves();
    }

    return dist[m - 1][n - 1];
  }
};

int main()
{
  return 0;
}
