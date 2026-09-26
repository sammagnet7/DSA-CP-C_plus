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

1. Title: Shortest Path in Undirected Graph with unit distance


Links:
https://takeuforward.org/data-structure/shortest-path-in-undirected-graph-with-unit-distance-g-28/
https://www.youtube.com/watch?v=C4gxoTaI71U&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=29
https://takeuforward.org/plus/dsa/problems/shortest-path-in-undirected-graph-with-unit-weights?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1


Problem statement:
You are given an undirected graph with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where each element edges[i] = [u, v] represents an undirected edge between vertices u and v.

Your task is to find the shortest path distance from a given source vertex src to all other vertices in the graph.
If a vertex is not reachable from the source, return -1 for that vertex.


Note: All edges have unit weight (1).

Examples :
Input: V = 9, E = 10,
edges[][] = [[0, 1], [0, 3], [1, 2], [3, 4], [4, 5], [2, 6], [5, 6], [6, 7], [6, 8], [7, 8]], src = 0
Output: [0, 1, 2, 1, 2, 3, 3, 4, 4]

Input: V = 4, E = 2,
edges[][]= [[0, 3], [1, 3]], src = 3
Output: [1, 1, -1, 0]

Constraints:
1 ≤ V ≤ 104
0 ≤ E ≤ V*(V-1)/2
0 ≤ edges[i][0], edges[i][1] <



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
// 1. Title: Shortest Path in Undirected Graph with unit distance
//-------------------------------------------------------------------------------
class Solution
{
public:
    //=========================
    // Approach 1: BFS
    //=========================
    /**
     * @brief Computes the shortest path distances from a source node in an unweighted graph using BFS.
     *
     * Intuition:
     * - The graph is unweighted, so the shortest path from the source to any node can be computed using Breadth-First Search (BFS).
     * - BFS explores nodes level by level. When we first visit a node, the distance at that time is guaranteed to be the shortest.
     *
     * Approach:
     * 1. Initialize a distance array with -1 (indicating unvisited nodes).
     * 2. Start BFS from the source node, setting its distance as 0.
     * 3. For each node, visit all its neighbors. If a neighbor is not visited yet, update its distance as current node's distance + 1, and push it into the queue.
     * 4. Continue until the queue is empty. The resulting distance array gives the shortest path length from the source to all nodes.
     *
     * Time Complexity:
     * - O(V + E), where V is the number of vertices and E is the number of edges.
     *   (Each node and edge is processed once in BFS.)
     *
     * Space Complexity:
     * - O(V) for the distance array + O(V) for the queue in the worst case.
     *
     * @param adj Adjacency list representing the graph.
     * @param src The source vertex from which shortest distances are calculated.
     * @return A vector<int> where the i-th element is the shortest distance from src to node i (or -1 if unreachable).
     */
    vector<int> shortestPath(vector<vector<int>> &adj, int src)
    {

        // Number of vertices in the graph
        int V = adj.size();

        // Queue for BFS traversal
        queue<int> q;

        // Distance array initialized with -1 (meaning: unvisited node)
        // vis_dist[i] = shortest distance from src to node i
        vector<int> vis_dist(V, -1);

        // Start BFS from the source
        q.push(src);

        // Distance from src to itself is 0
        vis_dist[src] = 0;

        // BFS traversal
        while (!q.empty())
        {

            // Get the current node from the queue
            int cur = q.front();

            // Get the current distance of this node from src
            int dist = vis_dist[cur];

            q.pop(); // Remove the node from queue

            // Traverse all adjacent nodes of current node
            for (int node : adj[cur])
            {

                // If this neighbor is already visited, skip it
                if (vis_dist[node] != -1)
                    continue;

                // Otherwise, set its distance (current distance + 1)
                vis_dist[node] = dist + 1;

                // Push the neighbor into the queue for BFS
                q.push(node);
            }
        }

        // Return the vector containing shortest distances from src to all nodes
        return vis_dist;
    }

    //==============================
    // Approach 2: BFS [RECOMMENDED]
    //==============================
    /**
     * @brief Calculates the shortest path from a source node to all other nodes in an unweighted graph.
     *
     * Intuition:
     * - In an unweighted graph, all edges have equal cost. Therefore, the first time we
     *   reach a node via a Breadth-First Search (BFS), we are mathematically guaranteed
     *   to have found the shortest possible path to it.
     * - We don't need Dijkstra's algorithm (Priority Queue) here; a standard FIFO Queue
     *   is perfectly sufficient and faster.
     *
     * Understanding:
     * - Example: We start at `src` with distance 0. Its immediate neighbors are at distance 0 + 1 = 1.
     *   Their unvisited neighbors are at distance 1 + 1 = 2.
     * - Optimization: Instead of allocating a separate `visited` array, we initialize our
     *   `ans` (distances) array to -1. A value of -1 means "unvisited". Any other value
     *   means we have already found the absolute shortest path to that node.
     *
     * Approach (Flattened BFS):
     * 1. Build the Adjacency List (`adjL`) from the given undirected `edges`.
     *
     * 2. Initialize the `ans` array with -1.
     *    - Set `ans[src] = 0` (distance from source to itself is 0).
     *    - Push `src` into the BFS queue.
     *
     * 3. Process the Queue:
     *    - Pop `curN`. We already know its shortest distance is `ans[curN]`.
     *    - Iterate through all its neighbors (`adjN`).
     *    - If `ans[adjN] == -1` (unvisited), the shortest distance to it is `ans[curN] + 1`.
     *    - Update `ans[adjN]` and push `adjN` into the queue to explore its neighbors later.
     *
     * 4. Once the queue is empty, any node still holding -1 is completely unreachable
     *    from the source node. Return the `ans` array.
     *
     * Time Complexity:
     * - O(V + E): Building the adjacency list takes O(E). The BFS visits each vertex (V)
     *   exactly once and evaluates every edge (E) exactly twice (undirected).
     *
     * Space Complexity:
     * - O(V + E): The adjacency list takes O(V + 2E) memory.
     *   The `ans` array takes O(V), and the BFS queue takes O(V) in the worst case.
     */
    vector<int> shortestPath(int V, vector<vector<int>> &edges, int src)
    {

        // Output array initialized to -1 (acts as both distance map and visited tracker)
        vector<int> ans(V, -1);

        // --- STEP 1: Build Adjacency List ---
        vector<vector<int>> adjL(V);
        for (const auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            adjL[u].push_back(v);
            adjL[v].push_back(u); // Undirected graph
        }

        // --- STEP 2: Initialize BFS ---
        queue<int> q;

        q.push(src);
        ans[src] = 0; // Distance to itself is 0

        // --- STEP 3: Flattened BFS Traversal ---
        while (!q.empty())
        {

            int curN = q.front();
            q.pop();

            for (int adjN : adjL[curN])
            {

                // If it's unvisited, we have found the shortest path to it!
                if (ans[adjN] == -1)
                {

                    // Distance is just the parent's distance + 1
                    ans[adjN] = ans[curN] + 1;

                    // Queue it up to process its neighbors later
                    q.push(adjN);
                }
            }
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
