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

1. Title: Bellman Ford Algorithm: G-41

Links:
https://takeuforward.org/data-structure/bellman-ford-algorithm-g-41/
https://www.youtube.com/watch?v=0vVofAhAYjc
https://takeuforward.org/plus/dsa/problems/bellman-ford-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1


Problem statement:
Given an weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], where edges[i] = [u, v, w] represents a direct edge from node u to v having w edge weight. You are also given a source vertex src.
Your task is to compute the shortest distances from the source to all other vertices. If a vertex is unreachable from the source, its distance should be marked as 108. Additionally, if the graph contains a negative weight cycle, return [-1] to indicate that shortest paths cannot be reliably computed.

Examples:
    Input: V = 5, edges[][] = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0
    Output: [0, 5, 6, 6, 7]
    Explanation: Shortest Paths:
    For 0 to 1 minimum distance will be 5. By following path 0 → 1
    For 0 to 2 minimum distance will be 6. By following path 0 → 1  → 2
    For 0 to 3 minimum distance will be 6. By following path 0 → 1  → 2 → 4 → 3
    For 0 to 4 minimum distance will be 7. By following path 0 → 1  → 2 → 4

    Input: V = 4, edges[][] = [[0, 1, 4], [1, 2, -6], [2, 3, 5], [3, 1, -2]], src = 0
    Output: [-1]
    Explanation: The graph contains a negative weight cycle formed by the path 1 → 2 → 3 → 1, where the total weight of the cycle is negative.

Constraints:
    1 ≤ V ≤ 100
    1 ≤ E = edges.size() ≤ V*(V-1)
    -1000 ≤ w ≤ 1000
    0 ≤ src < V




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
// 1. Title: Bellman Ford Algorithm: G-41
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /**
     * Bellman-Ford Algorithm
     *
     * Intuition:
     * ----------
     * Dijkstra's algorithm fails with negative weight cycles because it assumes
     * once a node is "popped", its distance is finalized.
     * Bellman-Ford does not assume this. Instead, it keeps relaxing edges up to (V-1) times,
     * ensuring correct shortest paths even with negative weights.
     * It can also detect negative weight cycles.
     *
     * Approach:
     * ----------
     * 1. Initialize all distances as "infinity" (large value), except dist[src] = 0.
     * 2. Perform (V-1) iterations:
     *      - For each edge (u -> v with weight w), if going through u improves
     *        dist[v], update it.
     *    This works because the longest possible simple path in a graph has (V-1) edges.
     * 3. After these iterations, check for negative weight cycles:
     *      - If any edge can still relax a node, then a negative cycle exists.
     *      - In that case, return {-1}.
     * 4. Otherwise, return the computed shortest distance array.
     *
     * Algorithm:
     * ----------
     * - Initialize dist[] = INF, dist[src] = 0
     * - Repeat (V-1) times:
     *       for each edge (u,v,wt):
     *           if dist[u] + wt < dist[v]:
     *               dist[v] = dist[u] + wt
     * - Check for negative cycles:
     *       for each edge (u,v,wt):
     *           if dist[u] + wt < dist[v]:
     *               return {-1}
     * - Return dist[]
     *
     * Time Complexity:
     * ----------------
     * O(V * E)
     *   - Each of the (V-1) iterations scans all E edges.
     *   - One more pass for negative cycle check = O(E).
     *
     * Space Complexity:
     * -----------------
     * O(V)
     *   - Distance array of size V.
     *
     * Suitable For:
     * -------------
     * - Graphs with negative weight edges.
     * - Detecting negative weight cycles.
     * - When graph is sparse/small, since O(V*E) is slower than Dijkstra.
     */

    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
    {
        // Step 1: Initialize distances with "infinity"
        vector<int> dist(V, 1e8);
        dist[src] = 0; // distance to source is always 0

        // Step 2: Relax all edges (V-1) times
        for (int i = 1; i <= V - 1; i++)
        {
            bool isModified = false; // track if any update happens

            for (auto &e : edges)
            {
                int u = e[0];  // source of edge
                int v = e[1];  // destination of edge
                int wt = e[2]; // edge weight

                // Relaxation step: only if u is reachable
                if (dist[u] != 1e8 && dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt; // update shortest distance
                    isModified = true;      // mark update happened
                }
            }

            // If no update in this pass, all shortest paths are finalized
            if (!isModified)
                break;
        }

        // Step 3: Check for negative weight cycle
        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            int wt = e[2];

            // If we can still relax => negative cycle exists
            if (dist[u] != 1e8 && dist[u] + wt < dist[v])
            {
                return {-1}; // return {-1} as per convention
            }
        }

        // Step 4: Return shortest distances
        return dist;
    }
};

int main()
{

    return 0;
}