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

1. Title: Bipartite Graph | DFS Implementation


Links:
https://takeuforward.org/graph/bipartite-graph-dfs-implementation/
https://www.youtube.com/watch?v=KG5YFfR0j8A
https://takeuforward.org/plus/dsa/problems/bipartite-graph?tab=editorial
https://leetcode.com/problems/is-graph-bipartite/description/


Problem statement:
There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:

There are no self-edges (graph[u] does not contain u).
There are no parallel edges (graph[u] does not contain duplicate values).
If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.

Return true if and only if it is bipartite.

Examples:
    Example 1:
    Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
    Output: false
    Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.

    Example 2:
    Input: graph = [[1,3],[0,2],[1,3],[0,2]]
    Output: true
    Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.


Constraints:
    graph.length == n
    1 <= n <= 100
    0 <= graph[u].length < n
    0 <= graph[u][i] <= n - 1
    graph[u] does not contain u.
    All the values of graph[u] are unique.
    If graph[u] contains v, then graph[v] contains u.


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
// 1. Title: Bipartite Graph | BFS Implementation
//-------------------------------------------------------------------------------
class Solution
{
    //-----------------
    // Approach 1: DFS
    //-----------------
private:
    /**
     * @brief DFS helper to 2-color the graph and detect odd-length cycles.
     * * @idea
     * We attempt to color the current node with `nodeClr`. For every neighbor,
     * they MUST be painted with the opposite color. If we ever encounter a neighbor
     * that has already been painted with our exact same color, the graph contains
     * an odd-length cycle and cannot be bipartite.
     */
    bool dfs(int node, int nodeClr, const vector<vector<int>> &graph, vector<int> &colored)
    {

        // Bitwise XOR trick: 0 becomes 1, and 1 becomes 0.
        // (Alternatively, 1 - nodeClr works perfectly too!)
        int adjClr = nodeClr ^ 1;

        // Iterate through all explicit neighbors in the adjacency list
        for (int adjN : graph[node])
        {

            // STATE CHECK: Neighbor is colored AND it matches my color. CONFLICT!
            if (colored[adjN] == nodeClr)
            {
                return false;
            }

            // STATE CHECK: Neighbor is uncolored (-1).
            if (colored[adjN] == -1)
            {

                // Paint the neighbor with the opposite color
                colored[adjN] = adjClr;

                // Recursively color the neighbor's neighbors.
                // EARLY EXIT: If any deep recursion finds a conflict, bubble it up immediately!
                if (!dfs(adjN, adjClr, graph, colored))
                {
                    return false;
                }
            }
        }

        return true;
    }

public:
    /**
     * @brief Determines if an explicit graph is Bipartite.
     * * @idea
     * We use a standard graph coloring approach. We map an array `colored` initialized
     * to -1. We loop through all vertices to handle disconnected graph components.
     * If a component is uncolored, we seed it with color 0 and launch a DFS.
     * * @time O(V + E)
     * V is the number of vertices, E is the number of edges. We visit each vertex
     * exactly once, and iterate over its outgoing edges exactly once.
     * * @space O(V)
     * We allocate an array of size V to store the colors. The recursive DFS call
     * stack will take O(V) space in the worst-case scenario (e.g., a straight line graph).
     */
    bool isBipartite(vector<vector<int>> &graph)
    {

        int v = graph.size();

        // -1 represents uncolored, 0 and 1 are our two distinct colors
        vector<int> colored(v, -1);

        // --- SWEEP ALL COMPONENTS ---
        // A graph might be disconnected. We must ensure every component is checked.
        for (int i = 0; i < v; ++i)
        {

            if (colored[i] == -1)
            {

                // Seed the starting node of this component with color 0
                colored[i] = 0;

                // Launch the DFS coloring process
                if (!dfs(i, 0, graph, colored))
                {
                    return false; // Conflict found in this component!
                }
            }
        }

        return true; // Successfully 2-colored the entire graph
    }

    //-----------------
    // Approach 2: BFS
    //-----------------

    /**
     * @brief Check if an undirected graph is bipartite using BFS
     *
     * A graph is bipartite if we can color its vertices using two colors such that
     * no two adjacent vertices have the same color.
     *
     * Approach:
     * - Use BFS to traverse each connected component.
     * - Assign a color (0 or 1) to the starting node.
     * - For each adjacent node:
     *      - If uncolored, assign the opposite color and push into queue.
     *      - If already colored, check for color conflict.
     * - If any conflict occurs, return false.
     * - If all components satisfy bipartite conditions, return true.
     *
     * Time Complexity: O(V + E)
     * - Each vertex is visited once.
     * - Each edge is checked at most twice (once for each vertex).
     *
     * Space Complexity: O(V)
     * - For color array and BFS queue.
     */

    bool isBipartite(vector<vector<int>> &graph)
    {

        int n = graph.size(); // Number of nodes in the graph

        // Initialize color array with -1 (uncolored)
        // colored[i] = 0 or 1 when the node is colored
        vector<int> colored(n, -1);

        queue<int> q; // BFS queue

        // Check each component of the graph (handles disconnected graphs)
        for (int i = 0; i < n; i++)
        {

            // If node already colored, skip
            if (colored[i] != -1)
                continue;

            // Start BFS from this node
            q.push(i);
            colored[i] = 0; // Assign color 0 to start node

            while (!q.empty())
            {
                int cur = q.front();
                q.pop();

                // Color to be assigned to adjacent nodes (opposite color)
                int makeColor = !colored[cur];

                // Traverse all adjacent nodes
                for (auto adj : graph[cur])
                {

                    // If adjacent node is uncolored, assign opposite color and push into queue
                    if (colored[adj] == -1)
                    {
                        colored[adj] = makeColor;
                        q.push(adj);
                    }
                    else
                    {
                        // If already colored, check for color conflict
                        if (colored[adj] != makeColor)
                            return false; // Conflict found → Not bipartite
                    }
                }
            }
        }

        // No conflicts found, graph is bipartite
        return true;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
