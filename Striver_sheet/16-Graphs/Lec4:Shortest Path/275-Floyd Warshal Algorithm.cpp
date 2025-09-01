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

1. Title: Floyd Warshall Algorithm: G-42

Links:
https://takeuforward.org/data-structure/floyd-warshall-algorithm-g-42/
https://www.youtube.com/watch?v=YbY8cVwWAvw
https://takeuforward.org/plus/dsa/problems/floyd-warshall-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1

Similar problems:
1] Find the city with the smallest number of neighbors in a threshold distance:
    https://takeuforward.org/data-structure/find-the-city-with-the-smallest-number-of-neighbours-at-a-threshold-distance-g-43/
    https://www.youtube.com/watch?v=PwMVNSJ5SLI&t=1s
    https://takeuforward.org/plus/dsa/problems/find-the-city-with-the-smallest-number-of-neighbors?tab=editorial
    https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/



Problem statement:
You are given an weighted directed graph, represented by an adjacency matrix, dist[][] of size n x n, where dist[i][j] represents the weight of the edge from node i to node j. If there is no direct edge, dist[i][j] is set to a large value (i.e., 108) to represent infinity.
The graph may contain negative edge weights, but it does not contain any negative weight cycles.
Your task is to find the shortest distance between every pair of nodes i and j in the graph.
Note: Modify the distances for every pair in place.

Examples :
    Input: dist[][] = [[0, 4, 108, 5, 108], [108, 0, 1, 108, 6], [2, 108, 0, 3, 108], [108, 108, 1, 0, 2], [1, 108, 108, 4, 0]]
    Output: [[0, 4, 5, 5, 7], [3, 0, 1, 4, 6], [2, 6, 0, 3, 5], [3, 7, 1, 0, 2], [1, 5, 5, 4, 0]]
    Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.

    Input: dist[][] = [[0, -1, 2], [1, 0, 108], [3, 1, 0]]
    Output: [[0, -1, 2], [1, 0, 3], [2, 1, 0]]
    Explanation: Each cell dist[i][j] in the output shows the shortest distance from node i to node j, computed by considering all possible intermediate nodes.
    From 2 to 0 shortest distance should be 2 by following path 2 -> 1 -> 0
    From 1 to 2 shortest distance should be 3 by following path 1 -> 0 -> 2

Constraints:
    1 ≤ dist.size() ≤ 100
    -1000 ≤ dist[i][j] ≤ 1000
    dist[i][j] can be 108 to represent infinity.



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
// 1. Title: Floyd Warshall Algorithm: G-42
//-------------------------------------------------------------------------------
//

/**
 * Floyd-Warshall Algorithm
 *
 * Intuition:
 * ----------
 * We want the shortest distance between every pair of vertices.
 * Dijkstra’s algorithm finds shortest paths from a single source,
 * but Floyd-Warshall computes shortest paths between ALL pairs
 * in O(V^3) time, and it can handle negative weights as well
 * (but not negative cycles).
 *
 * Approach:
 * ----------
 * 1. Represent the graph as an adjacency matrix "dist", where
 *    dist[i][j] = weight of edge (i->j), or INF (1e8) if no edge.
 * 2. For each intermediate vertex k:
 *      - Try to use k as a "via" node between i and j.
 *      - If dist[i][k] + dist[k][j] improves dist[i][j],
 *        update it.
 * 3. After the algorithm, dist[i][j] contains the shortest distance
 *    from i to j.
 * 4. Negative cycle detection: If dist[i][i] < 0 for any vertex i,
 *    it means there is a negative weight cycle reachable from i.
 *
 * Time Complexity:
 * ----------------
 * O(V^3)  -> three nested loops over vertices.
 *
 * Space Complexity:
 * -----------------
 * O(1) extra (in-place on the dist matrix).
 *
 * Suitable For:
 * -------------
 * - Dense graphs (many edges).
 * - When we need shortest paths between ALL pairs.
 * - Graphs with negative weights but no negative cycles.
 */

class Solution
{
public:
    void floydWarshall(vector<vector<int>> &dist)
    {
        int V = dist.size();

        // Try every vertex as an intermediate node
        for (int k = 0; k < V; k++)
        {
            // For every source vertex
            for (int i = 0; i < V; i++)
            {
                // For every destination vertex
                for (int j = 0; j < V; j++)
                {

                    int oldDist = dist[i][j];              // current distance i->j
                    int newDist = dist[i][k] + dist[k][j]; // distance i->k->j

                    // Relax only if both subpaths are valid (not INF)
                    if (dist[i][k] != 1e8 && dist[k][j] != 1e8 && newDist < oldDist)
                    {
                        dist[i][j] = newDist; // update with shorter path
                    }
                }
            }
        }

        // Detect negative weight cycle:
        // If distance from a vertex to itself becomes negative,
        // it means there exists a cycle with negative total weight.
        for (int i = 0; i < V; i++)
        {
            if (dist[i][i] < 0)
            {
                cout << "Graph contains a negative weight cycle" << endl;
            }
        }
    }
};

int main()
{

    return 0;
}