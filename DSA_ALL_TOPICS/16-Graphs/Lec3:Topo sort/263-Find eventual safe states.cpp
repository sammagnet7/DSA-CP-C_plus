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

1. Title: Find Eventual Safe States - DFS


Links:
https://takeuforward.org/data-structure/find-eventual-safe-states-dfs-g-20/
https://takeuforward.org/data-structure/find-eventual-safe-states-bfs-topological-sort-g-25/
https://www.youtube.com/watch?v=uRbJ1OF9aYM
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
    1 <= n <= 10^4
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 10^4].


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
// 1. Title: Find Eventual Safe States
//-------------------------------------------------------------------------------

class Solution
{
public:
    //============================================================================
    // Approach 1 — DFS + Cycle Detection (3-State Validation)
    //============================================================================

    /**
     * @brief Find all eventually safe nodes in a directed graph.
     *
     * Intuition:
     * - A node is "eventually safe" if every possible path starting from it eventually
     *   reaches a terminal node (a node with no outgoing edges).
     * - Conversely, any node that is part of a cycle, or has any path leading to a cycle,
     *   can never be safe because traversal could get trapped infinitely.
     *
     * Understanding:
     * - Example:
     *     During a Depth-First Search (DFS), we can track our current path. If we ever
     *     step on a node that is currently active in our path, we have found a "back-edge"
     *     (a directed cycle).
     *     To optimize and prevent Time Limit Exceeded (TLE), we use an `unsafe` array.
     *     If we hit a node that a previous DFS run already proved is unsafe, we can
     *     immediately conclude our current path is also unsafe without re-exploring it.
     *
     * Approach (DFS + Memoization):
     * 1. Initialize three boolean tracking arrays:
     *    - `vis[i]`: Marks if node i has been visited.
     *    - `pathVis[i]`: Marks if node i is currently in the active DFS recursion stack.
     *    - `unsafe[i]`: Memoizes if node i is confirmed to lead to a cycle (true = unsafe).
     *
     * 2. For each node (0 to n-1):
     *    - If it is not visited, trigger the DFS.
     *      a) Mark the current node as visited (`vis`), add it to the active path (`pathVis`),
     *         and pre-emptively mark it as `unsafe` (assume guilty until proven innocent).
     *      b) Iterate through all adjacent nodes:
     *         - Case 1: If unvisited, recursively call DFS. If it returns true, bubble up the cycle.
     *         - Case 2: If visited and in `pathVis` → Cycle detected! Return true.
     *         - Case 3: If visited, NOT in `pathVis`, but marked `unsafe` → Leads to a known cycle! Return true.
     *      c) If the loop finishes without returning true, the node survived all paths!
     *         - Mark `unsafe[curN] = false` (it is officially safe).
     *         - Revert `pathVis[curN] = false` so other branches can explore it normally.
     *         - Return false (no cycle found).
     *
     * 3. After sweeping the whole graph, any node where `unsafe[i] == false` is an eventual safe node.
     *
     * Time Complexity:
     * - O(V + E): Each vertex (V) and edge (E) is visited and processed exactly once.
     *
     * Space Complexity:
     * - O(V): For the recursion stack (DFS) + O(V) for `vis` + O(V) for `pathVis` + O(V) for `unsafe`.
     */
    bool dfs(int curN, vector<bool> &vis, vector<bool> &pathVis,
             vector<bool> &unsafe, const vector<vector<int>> &graph)
    {

        vis[curN] = true;
        pathVis[curN] = true;

        // Assume this node is unsafe (cyclic) until proven otherwise
        unsafe[curN] = true;

        for (int adjN : graph[curN])
        {

            // Case 1: The neighbor is unvisited. Plunge deeper!
            if (!vis[adjN])
            {
                if (dfs(adjN, vis, pathVis, unsafe, graph))
                {
                    // We don't even need to unmark pathVis here. We found a cycle, bubble it up!
                    return true;
                }
            }
            // Case 2: The neighbor is visited AND currently in our DFS path. CYCLE!
            else if (pathVis[adjN])
            {
                return true;
            }
            // Case 3: The neighbor is visited, NOT in our path, but is known to be UNSAFE!
            // This means our current node leads to a cycle.
            else if (unsafe[adjN])
            {
                return true;
            }
        }

        // --- SAFE NODE CONFIRMED ---
        // We survived all neighbors! This node does not lead to any cycles.
        unsafe[curN] = false;

        // Remove from the current path so other DFS branches can process it properly
        pathVis[curN] = false;

        // Return FALSE because NO cycle was detected on this path!
        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {

        int n = graph.size();

        vector<bool> vis(n, false);
        vector<bool> pathVis(n, false);

        // True means "leads to a cycle". We initialize all to false.
        vector<bool> unsafe(n, false);

        // Sweep all components of the graph
        for (int i = 0; i < n; ++i)
        {
            if (!vis[i])
            {
                dfs(i, vis, pathVis, unsafe, graph);
            }
        }

        vector<int> ans;

        // Any node that is NOT unsafe is an eventual safe node!
        for (int i = 0; i < n; ++i)
        {
            if (!unsafe[i])
            {
                ans.push_back(i);
            }
        }

        return ans;
    }

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
