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

1. Title: Minimum Spanning Tree | Prim's Algorithm

Links:
https://takeuforward.org/data-structure/minimum-spanning-tree-theory-g-44/
https://www.youtube.com/watch?v=ZSPjZuZWCME&feature=youtu.be
https://takeuforward.org/plus/dsa/problems/mst-theory?tab=editorial

https://takeuforward.org/data-structure/prims-algorithm-minimum-spanning-tree-c-and-java-g-45/
https://www.youtube.com/watch?v=mJcZjjKzeqk
https://takeuforward.org/plus/dsa/problems/find-the-mst-weight?tab=editorial
https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1



Problem statement:
Given a weighted, undirected, and connected graph with V vertices and E edges, your task is to find the sum of the weights of the edges in the Minimum Spanning Tree (MST) of the graph. The graph is provided as a list of edges, where each edge is represented as [u, v, w], indicating an edge between vertex u and vertex v with edge weight w.

Examples:
    Input: V = 3, E = 3, Edges = [[0, 1, 5], [1, 2, 3], [0, 2, 1]]
    Output: 4
    Explanation:
    The Spanning Tree resulting in a weight
    of 4 is shown above.

    Input: V = 2, E = 1, Edges = [[0 1 5]]
    Output: 5
    Explanation: Only one Spanning Tree is possible which has a weight of 5.

Constraints:
    2 ≤ V ≤ 1000
    V-1 ≤ E ≤ (V*(V-1))/2
    1 ≤ w ≤ 1000
    The graph is connected and doesn't contain self-loops & multiple edges.



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
// 1. Title: Prim's Algorithm - Minimum Spanning Tree
//-------------------------------------------------------------------------------
//

using P = pair<int, int>;
using T = tuple<int, int, int>;

class Solution
{
public:
    //============================================================================
    // Approach 1 — Prim's Algorithm (Minimum Spanning Tree)
    //============================================================================

    /**
     * @brief Calculates the total weight of the Minimum Spanning Tree (MST) and
     * retrieves the edges used to form it.
     *
     * Idea & Intuition:
     * - The Minimum Spanning Tree (MST) problem asks us to connect EVERY node in a
     * graph together using the absolute minimum total edge weight, without forming any cycles.
     * - Prim's Algorithm solves this using a Greedy "Expanding Empire" approach.
     * - We start at any arbitrary node and mark it as our initial "empire". Then, we
     * look at all possible roads (edges) leading OUT of our empire to unconquered cities.
     * - We strictly pick the CHEAPEST road, conquer that city, and add its outgoing
     * roads to our list of options. We repeat this until all cities are conquered.
     * - By using a Priority Queue (Min-Heap), we can instantly access the cheapest
     * available edge in O(log E) time.
     *
     * Understanding (The Lazy Deletion Trap):
     * - Unlike standard BFS where nodes are marked 'visited' when PUSHED into the queue,
     * in Prim's, we MUST wait to mark them 'visited' until they are POPPED.
     * - Why? Because while a node is sitting in the queue waiting its turn, we might
     * discover a completely different, much cheaper edge that connects to it!
     * - When we pop a node, we check `if (visited[node])`. If it's already visited,
     * this edge is a stale, worse path that would create a cycle, so we just `continue`.
     *
     * Approach:
     * 1. Graph Construction:
     * - Convert the given `edges` array into a bidirectional Adjacency List `adj`.
     * 2. Initialization:
     * - Create a `visited` array of size V to prevent cycles.
     * - Initialize a Min-Heap Priority Queue storing: `{weight, current_node, parent_node}`.
     * 3. The Root Setup:
     * - Push the starting condition into the PQ: `{0, 0, -1}`. (Starting at node 0
     * costs 0, and it has no parent).
     * 4. The Greedy Expansion:
     * - While the PQ is not empty, pop the cheapest edge: `{wt, node, parent}`.
     * - CYCLE CHECK: If `visited[node]` is true, skip this edge.
     * - Mark `visited[node] = true`.
     * - Accumulate the cost (`sum += wt`).
     * - Bookkeeping: If `parent != -1`, we record `{parent, node}` as an official MST edge.
     * 5. Expand the Frontier:
     * - Iterate through all neighbors of `node`. If a neighbor is NOT visited, push
     * `{neighbor_weight, neighbor, node}` into the PQ.
     *
     * Time Complexity:
     * - O(E log E): Building the Adjacency List takes O(E). In the worst case, we push
     * every single edge into the Min-Heap, and extracting them takes O(log E) time.
     *
     * Space Complexity:
     * - O(V + E): The Adjacency List holds 2E elements. The Priority Queue can hold
     * up to E elements. The `visited` and `mstEdges` arrays take O(V) space.
     */
    int spanningTree(int V, vector<vector<int>> &edges)
    {

        // --- STEP 1: Build the Adjacency List ---
        // adj[u] will store pairs of {neighbor, weight}
        vector<vector<P>> adj(V);

        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            // Because an MST graph is undirected, we must add edges in both directions!
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // --- STEP 2: Initialize Prim's Data Structures ---
        // Min-Heap stores: {weight, current_node, parent_node}
        priority_queue<T, vector<T>, greater<T>> pq;

        vector<bool> visited(V, false);
        vector<P> mstEdges; // Bookkeeping
        int sum = 0;
        int nodesConquered = 0;

        // --- STEP 3: The Greedy Expansion ---
        // Push starting node (cost 0, parent -1)
        pq.push({0, 0, -1});

        while (!pq.empty())
        {

            auto [curWt, curNode, parent] = pq.top();
            pq.pop();

            // Cycle Prevention
            if (visited[curNode])
            {
                continue;
            }

            // Conquered!
            visited[curNode] = true;
            sum += curWt;

            // Record the architectural edge (ignoring the starting node)
            if (parent != -1)
            {
                mstEdges.push_back({parent, curNode});
            }

            // Optimization
            nodesConquered++;
            if (nodesConquered == V) {
                break;
            }

            // Expand Frontier using our custom Adjacency List
            for (const auto &[adjNode, edgeWeight] : adj[curNode])
            {

                if (!visited[adjNode])
                {
                    pq.push({edgeWeight, adjNode, curNode});
                }
            }
        }

        return sum;
    }
};

int main()
{

    return 0;
}