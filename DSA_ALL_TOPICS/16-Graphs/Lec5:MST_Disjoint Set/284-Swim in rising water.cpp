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

1. Title: Swim in rising water

Links:
https://takeuforward.org/plus/dsa/problems/swim-in-rising-water?tab=editorial
https://leetcode.com/problems/swim-in-rising-water/description/


Problem statement:
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Examples:
    Example 1:
    Input: grid = [[0,2],[1,3]]
    Output: 3
    Explanation:
    At time 0, you are in grid location (0, 0).
    You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
    You cannot reach point (1, 1) until time 3.
    When the depth of water is 3, we can swim anywhere inside the grid.

    Example 2:
    Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
    Output: 16
    Explanation: The final route is shown.
    We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 50
    0 <= grid[i][j] < n^2
    Each value grid[i][j] is unique.


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
// 1. Title: Swim in rising water
//-------------------------------------------------------------------------------

//============================================================================
// Approach 1 — Modified Dijkstra's Algorithm (Minimax Path) [Slower]
//============================================================================

// Alias for cleaner Priority Queue syntax
using T = tuple<int, int, int>;

class Solution
{
public:
    /**
     * @brief Finds the minimum time to swim from top-left to bottom-right.
     *
     * Idea & Intuition:
     * - This is a "Bottleneck Shortest Path" problem. We want to find a path from
     * start to end where the MAXIMUM elevation along that path is minimized.
     * - We can modify Dijkstra's Algorithm to track the maximum peak encountered so far,
     * rather than summing up edge weights.
     * - The Priority Queue (Min-Heap) ensures we always expand the frontier by taking
     * the path with the lowest possible bottleneck.
     *
     * Time Complexity:
     * - O(N^2 log N): There are N^2 cells. In the worst case, we push all of them
     * into the Priority Queue. Extracting from the PQ takes O(log(N^2)) which
     * simplifies to O(log N).
     *
     * Space Complexity:
     * - O(N^2): The `minCost` matrix takes N x N space. The Priority Queue can hold
     * up to N^2 elements in the worst case.
     */
    int swimInWater(vector<vector<int>> &grid)
    {

        int n = grid.size();

        // Tracks the absolute lowest bottleneck required to reach cell (i, j)
        vector<vector<int>> minCost(n, vector<int>(n, INT_MAX));

        // 4-Directional movement (Right, Down, Up, Left)
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        // Min-Heap stores: {current_bottleneck_cost, row, col}
        priority_queue<T, vector<T>, greater<T>> pq;

        // Start at (0, 0)
        pq.push({grid[0][0], 0, 0});
        minCost[0][0] = grid[0][0];

        while (!pq.empty())
        {
            auto [cost, i, j] = pq.top();
            pq.pop();

            // Lazy Deletion: Skip stale entries that were pushed before a better path was found
            if (minCost[i][j] < cost)
            {
                continue;
            }

            // Early Exit: The first time we POP the destination, it is guaranteed optimal!
            if (i == n - 1 && j == n - 1)
            {
                break;
            }

            // Explore neighbors
            for (int k = 0; k < 4; ++k)
            {
                int ni = i + dir[k][0];
                int nj = j + dir[k][1];

                // Bounds check
                if (ni < 0 || nj < 0 || ni >= n || nj >= n)
                {
                    continue;
                }

                // The new bottleneck is whichever is higher: our current path's bottleneck,
                // or the elevation of the new cell we are stepping onto.
                int newCost = max(cost, grid[ni][nj]);

                // If this path offers a lower bottleneck to the neighbor, record it and queue it
                if (newCost < minCost[ni][nj])
                {
                    minCost[ni][nj] = newCost;
                    pq.push({newCost, ni, nj});
                }
            }
        }

        return minCost[n - 1][n - 1];
    }
};

//============================================================================
// Approach2 — Time Simulation with DSU [OPTIMAL] [RECOMMENDED]
//============================================================================

//============================================================================
// Helper Class — Disjoint Set Union (Union-Find)
//============================================================================
class DSU
{
private:
    vector<int> parent, size;

    int getPar(int i)
    {
        int p = parent[i];
        if (i == p)
        {
            return p;
        }
        // Path Compression: flattens the tree for near O(1) lookups
        return parent[i] = getPar(p);
    }

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    bool isConnected(int u, int v)
    {
        int pu = getPar(u);
        int pv = getPar(v);
        return pu == pv;
    }

    void dunion(int u, int v)
    {
        int pu = getPar(u);
        int pv = getPar(v);

        // Already in the same set
        if (pu == pv)
        {
            return;
        }

        int su = size[pu];
        int sv = size[pv];

        // Union by Size: attach the smaller tree under the larger tree
        if (su <= sv)
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

using P = pair<int, int>;

class Solution
{
public:
    /**
     * @brief Finds the minimum time required to swim from top-left to bottom-right.
     *
     * 🧠 Intuition (The "Ah-Ha!" Moment):
     * - The problem explicitly states that the grid contains UNIQUE integers from
     * 0 to (N^2 - 1). This is a massive hint! It implies that exactly ONE distinct
     * cell gets flooded every single minute.
     * - Instead of pathfinding from Start to End, we can "simulate the rain".
     * - As time ticks upward, new cells flood. When a cell floods, we look at its
     * neighbors. If a neighbor is already flooded, we merge them into a single
     * "lake" using our DSU.
     * - The exact minute that the Top-Left cell and the Bottom-Right cell end up
     * in the same DSU "lake", we have found our minimum time!
     *
     * ⚙️ Approach:
     * 1. Create an array `timeToCoords` to map Time -> (Row, Col). Because elevation
     * equals time, the cell with elevation 5 will flood exactly at time t = 5.
     * 2. Loop `time` from 0 to N^2 - 1.
     * 3. Fetch the exact cell that floods at the current `time`.
     * 4. Check its 4 neighbors. If a neighbor's elevation is <= current `time`, it
     * means the neighbor is ALREADY flooded.
     * 5. Use DSU to merge the newly flooded cell with its flooded neighbors.
     * 6. Check if cell 0 (Top-Left) and cell N^2 - 1 (Bottom-Right) are connected.
     * If they are, return the current time immediately.
     *
     * 🥊 Why this beats Dijkstra's Algorithm here:
     * - Standard Dijkstra uses a Priority Queue (Min-Heap), which takes O(log V)
     * time for every push/pop operation, resulting in O(N^2 log N) time complexity.
     * - Because we know the exact order of flooding (0 to N^2 - 1), we can completely
     * bypass the Priority Queue. Our DSU approach processes the grid linearly,
     * bringing the time complexity down to a blisteringly fast O(N^2)!
     *
     * ⏱️ Time Complexity:
     * - O(N^2 * α(N^2)): We iterate exactly N^2 times. In each iteration, checking
     * 4 neighbors and performing DSU operations takes amortized O(1) time.
     *
     * 💾 Space Complexity:
     * - O(N^2): We need O(N^2) space for the flattened DSU parent/size arrays,
     * and O(N^2) space for the `timeToCoords` lookup array.
     */
    int swimInWater(vector<vector<int>> &grid)
    {

        int n = grid.size();

        // Initialize 1D flattened DSU
        DSU dsu(n * n);

        vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Maps Elevation (which is also Time) to its exact 2D coordinates
        vector<P> timeToCoords(n * n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int elevation = grid[i][j];
                timeToCoords[elevation] = {i, j};
            }
        }

        // Simulate time ticking upwards
        for (int time = 0; time < n * n; ++time)
        {

            // Grab the exact cell that gets flooded at this specific minute
            auto [i, j] = timeToCoords[time];
            int pos = i * n + j; // 1D ID of the current cell

            // Look at 4 neighbors
            for (int k = 0; k < 4; ++k)
            {
                int ni = i + dir[k][0];
                int nj = j + dir[k][1];

                // Bounds Check
                if (ni < 0 || nj < 0 || ni >= n || nj >= n)
                {
                    continue;
                }

                // If the neighbor's elevation is strictly greater than the current time,
                // it is still dry land. We cannot swim to it yet.
                if (grid[ni][nj] > time)
                {
                    continue;
                }

                // If we reach here, the neighbor is already flooded. Merge them!
                int npos = ni * n + nj;
                dsu.dunion(pos, npos);
            }

            // At the end of every minute, check if the Start and End are in the same lake
            if (dsu.isConnected(0, (n * n - 1)))
            {
                return time;
            }
        }

        return -1;
    }
};

int main()
{
    return 0;
}