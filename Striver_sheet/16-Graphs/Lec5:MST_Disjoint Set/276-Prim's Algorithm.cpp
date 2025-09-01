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

1. Title: Minimum Spanning Tree - Theory: G-44 | Prim's Algorithm - Minimum Spanning Tree

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

#define P pair<int, int>

/**
 * Function: spanningTree
 * ----------------------
 * Computes the Minimum Spanning Tree (MST) of a weighted undirected graph
 * using **Prim’s Algorithm** with a min-heap (priority_queue).
 *
 * Intuition:
 * ----------
 * - MST connects all vertices with minimum total edge weight, without cycles.
 * - Prim’s algorithm grows the MST one vertex at a time:
 *      1. Start from any node.
 *      2. Repeatedly pick the minimum weight edge that connects a vertex
 *         already in MST to a vertex not yet in MST.
 *      3. Continue until all vertices are included.
 *
 * Approach:
 * ---------
 * 1. Build adjacency list from the edge list.
 * 2. Use a min-heap to always pick the next minimum-weight edge.
 * 3. Keep track of:
 *      - `inMST[]`: whether a vertex is already in MST.
 *      - `parent[]`: the parent vertex through which we added a vertex.
 *      - `MST`: the list of edges in the MST.
 * 4. Return total weight of MST.
 *
 * Time Complexity: O(E log V)
 *   - Each edge may be pushed to the priority queue → O(E log V).
 * Space Complexity: O(V + E)
 *   - Adjacency list + auxiliary arrays.
 */

class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> &edges)
    {
        // Step 1: Build adjacency list
        vector<vector<P>> adjL(V, vector<P>());
        for (auto &e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]}); // undirected graph
        }

        // Min-heap: {edge_weight, node}
        priority_queue<P, vector<P>, greater<P>> pq;

        vector<int> parent(V, -1);    // Track parent of each node in MST
        vector<bool> inMST(V, false); // Track if a node is included in MST
        vector<P> MST;                // List of edges in MST
        int MST_wt = 0;               // Total MST weight

        // Step 2: Start with node 0
        pq.push({0, 0});

        // Step 3: Process until all nodes are included
        while (!pq.empty())
        {
            int d = pq.top().first;  // edge weight
            int u = pq.top().second; // node
            pq.pop();

            // Skip if already added to MST
            if (inMST[u])
                continue;

            // If not starting node, add edge to MST
            if (parent[u] != -1)
            {
                MST.push_back({parent[u], u});
                MST_wt += d; // add edge weight
            }

            inMST[u] = true; // mark node as included

            // Step 4: Relax all adjacent nodes
            for (auto &adj : adjL[u])
            {
                int v = adj.first;   // neighbor
                int wt = adj.second; // edge weight
                if (!inMST[v])
                {
                    pq.push({wt, v});
                    parent[v] = u; // record parent for MST edge
                }
            }
        }

        return MST_wt; // Step 5: return total weight of MST
    }
};

int main()
{

    return 0;
}