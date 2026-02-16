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

1. Title: Shortest Path in Undirected Graph with unit distance: G-28


Links:
https://takeuforward.org/data-structure/shortest-path-in-undirected-graph-with-unit-distance-g-28/
https://www.youtube.com/watch?v=C4gxoTaI71U&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=29
https://takeuforward.org/plus/dsa/problems/shortest-path-in-undirected-graph-with-unit-weights?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1


Problem statement:
You are given an adjacency list, adj of Undirected Graph having unit weight of the edges, find the shortest path from src to all the vertex and if it is unreachable to reach any vertex, then return -1 for that vertex.

Examples :
    Input: adj[][] = [[1, 3], [0, 2], [1, 6], [0, 4], [3, 5], [4, 6], [2, 5, 7, 8], [6, 8], [7, 6]], src=0
    Output: [0, 1, 2, 1, 2, 3, 3, 4, 4]

    Input: adj[][]= [[3], [3], [], [0, 1]], src=3
    Output: [1, 1, -1, 0]

    Input: adj[][]= [[], [], [], [4], [3], [], []], src=1
    Output: [-1, 0, -1, -1, -1, -1, -1]

Constraint:
    1<=adj.size()<=104
    0<=edges<=adj.size()-1



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
    // 1. Title: Shortest Path in Undirected Graph with unit distance: G-28
    //-------------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
