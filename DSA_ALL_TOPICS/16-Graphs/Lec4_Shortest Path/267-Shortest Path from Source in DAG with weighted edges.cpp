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

1. Title: Shortest Path from Source in Directed Acyclic Graph with weighted edges


Links:
https://takeuforward.org/data-structure/shortest-path-in-directed-acyclic-graph-topological-sort-g-27/
https://www.youtube.com/watch?v=ZUFQfFaU-8U&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=28
https://takeuforward.org/plus/dsa/problems/shortest-path-in-dag?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/0
https://www.naukri.com/code360/problems/shortest-path-in-dag_8381897?leftPanelTabValue=PROBLEM


Problem statement:
Given a Directed Acyclic Graph of V vertices from 0 to n-1 and a 2D Integer array(or vector) edges[ ][ ] of length E, where there is a directed edge from edge[i][0] to edge[i][1] with a distance of edge[i][2] for all i.
Find the shortest path from src(0) vertex to all the vertices and if it is impossible to reach any vertex, then return -1 for that vertex.

Examples :
    Input: V = 4, E = 2, edges = [[0,1,2], [0,2,1]]
    Output: [0, 2, 1, -1]
    Explanation: Shortest path from 0 to 1 is 0->1 with edge weight 2. Shortest path from 0 to 2 is 0->2 with edge weight 1. There is no way we can reach 3, so it's -1 for 3.

    Input: V = 6, E = 7, edges = [[0,1,2], [0,4,1], [4,5,4], [4,2,2], [1,2,3], [2,3,6], [5,3,1]]
    Output: [0, 2, 3, 6, 1, 5]
    Explanation: Shortest path from 0 to 1 is 0->1 with edge weight 2. Shortest path from 0 to 2 is 0->4->2 with edge weight 1+2=3. Shortest path from 0 to 3 is 0->4->5->3 with edge weight 1+4+1=6. Shortest path from 0 to 4 is 0->4 with edge weight 1.Shortest path from 0 to 5 is 0->4->5 with edge weight 1+4=5.

Constraint:
    1 <= V <= 100
    1 <= E <= min((V*(V-1))/2, 4000)
    0 <= edges[i][0], edges[i][1] < n
    0 <= edges[i][2] <=10^5



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

//----------------------------------------------------------------------------------
// 1. Title: Shortest Path from Source in Directed Acyclic Graph with weighted edges
//----------------------------------------------------------------------------------

/**
 * ============================================================================
 * 🏆 THE DAG EXPLOIT: DIJKSTRA VS. KAHN'S ALGORITHM
 * ============================================================================
 * * When finding the shortest path in a Directed Acyclic Graph (DAG), you have
 * two primary approaches. One is a general-purpose tool, and the other is a
 * highly optimized, specialized weapon.
 * | Feature            | Approach 1 (Dijkstra)     | Approach 2 (Kahn's Topo Sort) |
 * | -----------------  | --------------------      | ----------------------------  |
 * | Core Algorithm:    | Min-Heap Priority Queue   | Breadth-First Search (Queue)  |
 * | Time Complexity:   | O((V + E) log V)          | O(V + E) (Strictly Linear!)   |
 * | Space Complexity   | O(V + E)                  | O(V + E)                      |
 * | Negative Weights?  | ❌ Fails / Infinite Loops | ✅ Works perfectly!           |
 * | Cycle Handling?    | ✅ Works (positive only)  | ❌ Fails (But DAGs have none!)|
 * * 🔨 Approach 1: Dijkstra's Algorithm (The Sledgehammer)
 * - Uses a Priority Queue to always grab the node with the smallest tentative distance.
 * - Overkill for DAGs because paths never circle back. The O(log V) sorting overhead
 * is a massive waste of CPU cycles.
 * * 🗡️ Approach 2: Kahn's Topological Sort (The Scalpel)
 * - Uses a standard FIFO Queue based on In-Degrees.
 * - By processing nodes in Topological Order, we mathematically guarantee that before
 * we process node V, every possible path leading into V has already been evaluated.
 * - Drops the Priority Queue entirely, achieving strictly linear O(V + E) time.
 * - Because it doesn't rely on greedy weight sorting, it flawlessly handles Negative Weights!
 * ============================================================================
 */
class Solution
{
public:
    //============================================================================
    // Approach 1 — Dijkstra's Algorithm (General Purpose)
    //============================================================================

    /**
     * @brief Finds the shortest path using a Min-Heap.
     *
     * Intuition:
     * - Greedily explores the shortest available path. It guarantees the shortest
     * path is found upon first extraction from the Priority Queue.
     *
     * Time Complexity: O((V + E) log V)
     * Space Complexity: O(V + E)
     */
    vector<int> shortestPathInDAG_Dijkstra(int n, int m, vector<vector<int>> &edges)
    {

        vector<vector<pair<int, int>>> adjL(n);

        for (const auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            adjL[u].push_back({v, w});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(n, 1e9);

        pq.push({0, 0});
        dist[0] = 0;

        while (!pq.empty())
        {

            auto [curW, curN] = pq.top();
            pq.pop();

            // Lazy Deletion
            if (dist[curN] < curW)
            {
                continue;
            }

            for (const auto &[adjN, adjW] : adjL[curN])
            {

                int newW = curW + adjW;

                if (newW < dist[adjN])
                {
                    dist[adjN] = newW;
                    pq.push({newW, adjN});
                }
            }
        }

        // Post-Process Unreachable Nodes
        for (int i = 0; i < n; ++i)
        {
            if (dist[i] == 1e9)
            {
                dist[i] = -1;
            }
        }

        return dist;
    }

    //=================================================================================
    // Approach 2 — Kahn's Algorithm / Topological Sort [OPTIMAL for DAG] [RECOMMENDED]
    //=================================================================================

    /**
     * @brief Finds the shortest path from node 0 to all other nodes in a Directed Acyclic Graph (DAG) using Topological Sort.
     *
     * Idea & Intuition:
     * - Dijkstra's Algorithm uses an expensive Priority Queue (Min-Heap) because it
     * needs to dynamically figure out the "correct" order to process nodes. This
     * costs O((V+E) log V) time.
     * - However, because this is a DAG (Directed Acyclic Graph), a "correct" processing
     * order already natively exists: Topological Sort.
     * - If we process nodes strictly in Topological Order, we mathematically guarantee
     * that before we process node V, every possible path leading into V has already
     * been completely evaluated.
     * - This allows us to drop the Priority Queue entirely, use a standard Queue, and
     * achieve strictly linear O(V + E) time! Furthermore, because this doesn't rely
     * on greedy weight sorting, it flawlessly handles negative edge weights.
     *
     * Approach:
     * 1. Graph & In-Degree Construction:
     * - Build a directed Adjacency List `adjL` where `adjL[u]` stores `{v, weight}`.
     * - Simultaneously populate an `ins` array to track the in-degree (number of
     * incoming edges) for every node.
     * * 2. Initialize Kahn's BFS:
     * - Initialize a `dist` array to infinity (`1e9`). Set the source `dist[0] = 0`.
     * - Iterate through the `ins` array. Push ANY node with `ins[i] == 0` into a
     * standard FIFO queue. (These are our topological starting points).
     * * 3. Topological Edge Relaxation:
     * - Pop `curN` from the queue.
     * - Iterate through all its neighbors.
     * - SAFETY CHECK: We only attempt to relax the edge if `curN` has actually been
     * reached by the source (`dist[curN] != 1e9`). This prevents adding edge weights
     * to infinity and causing catastrophic integer overflow.
     * - If a shorter path is found to the neighbor, update `dist[adjN]`.
     * - Finally, decrement the neighbor's in-degree (`--ins[adjN]`). If it hits 0,
     * all of its prerequisites have been processed, so push it into the queue.
     * * 4. Post-Processing:
     * - Iterate through the `dist` array. Any node that remains at `1e9` is
     * unreachable from node 0. Convert its distance to `-1`.
     *
     * Time Complexity:
     * - O(V + E): We visit every vertex exactly once and traverse every edge exactly once.
     * There is zero sorting overhead.
     *
     * Space Complexity:
     * - O(V + E): The Adjacency List takes O(V + E) memory. The standard Queue, `ins`
     * array, and `dist` array each take O(V) auxiliary space.
     */
    vector<int> shortestPathInDAG_Kahn(int n, int m, vector<vector<int>> &edges)
    {

        // --- STEP 1: Build Adjacency List & In-Degrees ---
        vector<vector<pair<int, int>>> adjL(n);
        vector<int> ins(n, 0);

        for (const auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            adjL[u].push_back({v, w});
            ++ins[v];
        }

        queue<int> q;
        vector<int> dist(n, 1e9);

        // --- STEP 2: Queue all topological starting points ---
        for (int i = 0; i < n; ++i)
        {
            if (ins[i] == 0)
            {
                q.push(i);
            }
        }

        // The problem specifically asks for paths starting from node 0
        dist[0] = 0;

        // --- STEP 3: Process via Topological Sort ---
        while (!q.empty())
        {

            int curN = q.front();
            q.pop();

            for (const auto &[adjN, adjW] : adjL[curN])
            {

                // SAFETY CHECK: Only relax edges if curN is actually reachable from node 0!
                // Prevents adding weights to 1e9 and causing negative integer overflow.
                if (dist[curN] != 1e9)
                {

                    int newW = dist[curN] + adjW;

                    if (newW < dist[adjN])
                    {
                        dist[adjN] = newW;
                    }
                }

                // Standard Kahn's Algorithm dependency reduction
                --ins[adjN];
                if (ins[adjN] == 0)
                {
                    q.push(adjN);
                }
            }
        }

        // --- STEP 4: Format Unreachable Nodes ---
        for (int i = 0; i < n; ++i)
        {
            if (dist[i] == 1e9)
            {
                dist[i] = -1;
            }
        }

        return dist;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
