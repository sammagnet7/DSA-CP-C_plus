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

1. Title: Find Eventual Safe States - DFS: G-20


Links:
https://takeuforward.org/data-structure/find-eventual-safe-states-dfs-g-20/
https://www.youtube.com/watch?v=uRbJ1OF9aYM
https://takeuforward.org/plus/dsa/problems/find-eventual-safe-states?tab=editorial
https://leetcode.com/problems/find-eventual-safe-states/description/


Problem statement:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].
A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

Examples:
    Example 1:
    Illustration of graph
    Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
    Output: [2,4,5,6]
    Explanation: The given graph is shown above.
    Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
    Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

    Example 2:
    Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
    Output: [4]
    Explanation:
    Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.


Constraints:
    n == graph.length
    1 <= n <= 104
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 104].


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Find Eventual Safe States - BFS - Topological Sort: G-25


Links:
https://takeuforward.org/data-structure/find-eventual-safe-states-bfs-topological-sort-g-25/
https://www.youtube.com/watch?v=2gtg3VsDGyc
https://takeuforward.org/plus/dsa/problems/find-eventual-safe-states?tab=editorial
https://leetcode.com/problems/find-eventual-safe-states/description/


Problem statement:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].
A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

Examples:
    Example 1:
    Illustration of graph
    Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
    Output: [2,4,5,6]
    Explanation: The given graph is shown above.
    Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
    Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

    Example 2:
    Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
    Output: [4]
    Explanation:
    Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.


Constraints:
    n == graph.length
    1 <= n <= 104
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 104].


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Find Eventual Safe States - DFS: G-20
    //-------------------------------------------------------------------------------

    //============================================================================
    // Approach 1 — DFS + Cycle Detection (mark & memoize)
    //============================================================================

    /**
     * @brief Find all eventually safe nodes in a directed graph.
     *
     * Intuition:
     * - A node is considered "eventually safe" if all possible paths starting from it lead to a terminal node
     *   (a node with no outgoing edges) and do NOT enter a cycle.
     * - Nodes that are either:
     *     1. Part of a cycle, or
     *     2. Lead to a cycle,
     *   are unsafe.
     *
     * Understanding:
     * - Example:
     *     If a node is part of a cycle or can reach a cycle, it's unsafe.
     *     Nodes that do not participate in cycles and cannot reach any cycle are safe.
     *
     * Approach (DFS + Cycle Detection):
     * 1. Use three arrays:
     *    - `vis[i]`: Marks if node i has been visited.
     *    - `pathVis[i]`: Marks if node i is in the current DFS path (used for cycle detection).
     *    - `safeCheck[i]`: Marks if node i is safe (true = safe, false = unsafe).
     *
     * 2. For each node (0 to V-1):
     *    - If not visited, perform DFS:
     *      a) Mark current node as visited and add it to path (`pathVis`).
     *      b) For every adjacent node:
     *         - If `pathVis[adj]` is true → cycle detected → return true.
     *         - If `adj` is not visited, recurse DFS on it.
     *         - If recursion returns true (cycle found), propagate `true` upwards.
     *    - After exploring all adjacents:
     *      - Remove current node from `pathVis` (as DFS for this node is done).
     *      - Mark `safeCheck[cur] = 1` (safe node) if no cycle found.
     *
     * 3. After processing all nodes, collect all nodes marked safe.
     *
     * Time Complexity:
     * - O(V + E): Each node and edge is visited once during DFS.
     *
     * Space Complexity:
     * - O(V) for recursion stack (DFS) + O(V) for `vis` + O(V) for `pathVis` + O(V) for `safeCheck` → O(V).
     *
     * This approach ensures we efficiently detect cycles and mark safe nodes.
     */

    bool dfsWithCycle(int cur, vector<vector<int>> &graph, vector<int> &vis, vector<int> &pathVis, vector<int> &safeCheck)
    {
        vis[cur] = 1;     // Mark current node as visited
        pathVis[cur] = 1; // Add current node to recursion stack (path)

        for (int adj : graph[cur])
        {
            // If adjacent node is already in the path → cycle detected
            if (pathVis[adj])
            {
                return true; // Cycle exists
            }

            // If adjacent node not visited → recurse
            if (!vis[adj])
            {
                bool ret = dfsWithCycle(adj, graph, vis, pathVis, safeCheck);

                if (ret) // If cycle detected in recursion → propagate true
                    return true;
            }
        }

        // Backtrack: remove from current path
        pathVis[cur] = 0;

        // Mark current node as safe (no cycle found from this node)
        safeCheck[cur] = 1;

        return false; // No cycle detected
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int V = graph.size();

        // Arrays to track visited nodes, nodes in current path, and safe nodes
        vector<int> vis(V, 0);
        vector<int> pathVis(V, 0);
        vector<int> safeCheck(V, 0);
        vector<int> ans;

        // Perform DFS for all nodes
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfsWithCycle(i, graph, vis, pathVis, safeCheck);
            }
        }

        // Collect nodes marked as safe
        for (int i = 0; i < V; i++)
        {
            if (safeCheck[i])
            {
                ans.push_back(i);
            }
        }

        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Find Eventual Safe States - BFS - Topological Sort: G-25
    //-------------------------------------------------------------------------------

    //============================================================================
    // Approach 2 — Reverse-Graph + Kahn’s Algorithm (BFS Topological Pruning)
    //============================================================================
    /**
     * Find all "eventually safe" nodes using reverse graph + Kahn’s algorithm.
     *
     * Idea:
     * - In the original graph, **terminal nodes** (outdegree = 0) are safe.
     * - Any node whose **every** outgoing edge leads to a safe node is also safe.
     * - Build the **reverse graph** (for each u→v, add v→u). Keep `indeg[u]` for original.
     * - Initialize a queue with all nodes having indeg = 0 (original terminals).
     * - Repeatedly pop a safe node cur. For each predecessor adj in reverse graph:
     *   decrement indeg[adj]; if it becomes 0, adj is now safe → push adj.
     * - All nodes popped are safe. (Everything left with indeg > 0 participates in/points to cycles.)
     *
     * Implementation detail here:
     * - We store reverse edges in `adjL[v].push_back(u)` and the array `indegree[u]`
     *   actually holds the **original outdegree(u)** (counted while reading original edges).
     *
     * Time:  O(V + E) — build reverse graph O(E), BFS processes each edge once.
     * Space: O(V + E) — reverse adjacency list + queue + arrays.
     */

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int V = graph.size();

        // Build reverse graph and count original outdegrees in `indeg`
        vector<vector<int>> rev(V);
        vector<int> indeg(V, 0);

        for (int u = 0; u < V; u++)
        {
            for (int v : graph[u])
            {
                rev[v].push_back(u); // reverse edge v -> u
                indeg[u]++;          // original outdegree of u
            }
        }

        // Start from all terminal nodes (indeg == 0) which are trivially safe
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indeg[i] == 0)
                q.push(i);
        }

        vector<int> safe;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            safe.push_back(cur);

            // "Remove" cur from the graph: it satisfies one outgoing edge of each predecessor p
            for (int adj : rev[cur])
            {
                if (--indeg[adj] == 0)
                    q.push(adj);
            }
        }

        // `safe` contains exactly the safe nodes; problem expects ascending order
        sort(safe.begin(), safe.end());
        return safe;
    }
};

int main()
{
    return 0;
}
