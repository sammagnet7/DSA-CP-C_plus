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

1. Title: Topo Sort


Links:

https://www.geeksforgeeks.org/problems/topological-sort/1
https://www.youtube.com/watch?v=5lZ0iJMrUMk
https://takeuforward.org/data-structure/topological-sort-algorithm-dfs-g-21/
https://takeuforward.org/data-structure/kahns-algorithm-topological-sort-algorithm-bfs-g-22/
https://www.youtube.com/watch?v=iTBaI90lpDQ
https://takeuforward.org/plus/dsa/problems/topological-sort-or-kahns-algorithm?tab=editorial


Problem statement:
Given a Directed Acyclic Graph (DAG) of V (0 to V-1) vertices and E edges represented as a 2D list of edges[][], where each entry edges[i] = [u, v] denotes a directed edge u -> v. Return the topological sort for the given graph.

Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u -> v, vertex u comes before v in the ordering.
Note: As there are multiple Topological orders possible, you may return any of them. If your returned Topological sort is correct then the output will be true else false.

Examples:
    Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
    Output: true
    Explanation: The output true denotes that the order is valid. Few valid Topological orders for the given graph are:
    [3, 2, 1, 0]
    [1, 2, 3, 0]
    [2, 3, 1, 0]

    Input: V = 6, E = 6, edges[][] = [[1, 3], [2, 3], [4, 1], [4, 0], [5, 0], [5,2]]
    Output: true
    Explanation: The output true denotes that the order is valid. Few valid Topological orders for the graph are:
    [4, 5, 0, 1, 2, 3]
    [5, 2, 4, 0, 1, 3]

Constraints:
    2  ≤  V  ≤  5 x 103
    1  ≤  E = edges.size()  ≤  min[105, (V * (V - 1)) / 2]



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
    // 1. Title: Topo Sort
    //-------------------------------------------------------------------------------

    //============================================================================
    // Approach 1: Topological Sort using DFS (Post-order + Stack)
    //============================================================================

    /**
     * @brief Topological Sort using DFS
     *
     * Intuition:
     * Topological sorting of a Directed Acyclic Graph (DAG) is a linear ordering
     * of vertices such that for every directed edge u → v, vertex u appears before v.
     *
     * Why only for DAG?
     *  - If there is a cycle, no valid ordering exists because nodes in the cycle
     *    depend on each other.
     *
     * Why DFS works:
     *  - DFS ensures that before we finish a node, we completely process all
     *    its outgoing edges (dependencies).
     *  - After processing all neighbors of a node, we push it onto a stack.
     *    So, nodes with no dependencies are placed first in the stack.
     *  - Reversing this stack (or popping from it) gives the topological order.
     *
     * Time Complexity: O(V + E)
     *  - Each vertex and edge is visited exactly once.
     * Space Complexity: O(V + E)
     *  - O(V) for visited array
     *  - O(E) for adjacency list
     *  - O(V) for stack storing the result
     */

    /**
     * @brief DFS helper for topological sorting
     * @param cur Current node being processed
     * @param adjL Graph adjacency list
     * @param st Stack to store nodes in reverse topological order
     * @param vis Visited array
     */
    void dfsTopo(int cur, vector<vector<int>> &adjL, stack<int> &st, vector<int> &vis)
    {
        vis[cur] = 1; // Mark current node as visited

        // Explore all adjacent nodes
        for (int adj : adjL[cur])
        {
            if (!vis[adj])
            {
                dfsTopo(adj, adjL, st, vis);
            }
        }

        // Push current node after all its neighbors are processed
        st.push(cur);
    }

    /**
     * @brief Computes topological order using DFS
     * Steps:
     *  1. Convert edge list to adjacency list
     *  2. Run DFS for all unvisited nodes
     *  3. Push nodes to stack after processing (post-order)
     *  4. Pop from stack to get final topological order
     *
     * Handles disconnected components by initiating DFS from every unvisited node.
     *
     * @param V Number of vertices
     * @param edges Edge list of graph
     * @return vector<int> Topological order
     */

    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {

        // Step 1: Build adjacency list
        vector<vector<int>> adjL(V);
        for (auto &e : edges)
        {
            adjL[e[0]].push_back(e[1]);
        }

        vector<int> vis(V, 0); // Visited array
        stack<int> st;         // Stack to store nodes in reverse order
        vector<int> topo;       // Result vector

        // Step 2: Perform DFS for all unvisited nodes
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfsTopo(i, adjL, st, vis);
            }
        }

        // Step 3: Pop stack to get final ordering
        while (!st.empty())
        {
            topo.push_back(st.top());
            st.pop();
        }

        return topo;
    }

    //============================================================================
    // Approach 2: Topological Sort using BFS (Kahn's Algorithm)
    //============================================================================

    /**
     * @brief Topological Sort using BFS (Kahn's Algorithm)
     *
     * Intuition:
     *  - Count incoming edges (indegree) for all nodes.
     *  - Nodes with indegree 0 have no dependencies → start from them.
     *  - Remove these nodes from the graph, reducing indegree of their neighbors.
     *  - Continue this process until all nodes are processed.
     *
     * Time Complexity: O(V + E)
     *  - Each vertex is enqueued and dequeued exactly once.
     *  - Each edge is processed exactly once.
     * Space Complexity: O(V + E)
     *  - O(V) for indegree array
     *  - O(E) for adjacency list
     *  - O(V) for the queue
     *
     * If the number of nodes processed != V, the graph has a cycle.
     */

    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {

        // Step 1: Build adjacency list and indegree array
        vector<vector<int>> adjL(V);
        vector<int> indegree(V, 0);

        for (auto &e : edges)
        {
            adjL[e[0]].push_back(e[1]);
            indegree[e[1]]++;
        }

        queue<int> q;
        vector<int> topo;

        // Step 2: Push all nodes with indegree 0 into queue
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // Step 3: Process nodes
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Reduce indegree of neighbors
            for (int adj : adjL[node])
            {
                indegree[adj]--;
                if (indegree[adj] == 0)
                {
                    q.push(adj);
                }
            }
        }

        return topo; // If ans.size() < V → cycle exists
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
