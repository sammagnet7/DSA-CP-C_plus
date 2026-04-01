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

1. Title: Bridges in Graph - Using Tarjan's Algorithm of time in and low time

Links:
https://takeuforward.org/graph/bridges-in-graph-using-tarjans-algorithm-of-time-in-and-low-time-g-55/
https://www.youtube.com/watch?v=qrAub5z8FeA
https://takeuforward.org/plus/dsa/problems/bridges-in-graph?tab=editorial
https://leetcode.com/problems/critical-connections-in-a-network/description/


Problem statement:
There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
Return all critical connections in the network in any order.

Examples:
    Example 1:
    Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
    Output: [[1,3]]
    Explanation: [[3,1]] is also accepted.

    Example 2:
    Input: n = 2, connections = [[0,1]]
    Output: [[0,1]]


Constraints:
    2 <= n <= 10^5
    n - 1 <= connections.length <= 10^5
    0 <= ai, bi <= n - 1
    ai != bi
    There are no repeated connections.


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
// 1. Title: Bridges in Graph - Tarjan's Algorithm
//-------------------------------------------------------------------------------

/**
 * @class Solution
 * @brief Finds all Critical Connections (Bridges) using a highly optimized Tarjan's Algorithm.
 *
 * ============================================================================
 * 🧠 INTUITION & IDEA
 * ============================================================================
 * A "Bridge" or "Critical Connection" is an edge that, if removed, splits the
 * graph into multiple disconnected components.
 * We track two things for every node:
 * 1. `discoveryTime`: The exact timer tick when the node was first visited.
 * 2. `lowestReachTime`: The earliest `discoveryTime` this node (or its children) can reach.
 * * An edge connecting `curr` to `child` is a Bridge if the `child` CANNOT reach
 * ANY node discovered *before or at the same time* as `curr`.
 * Mathematically: `discoveryTime[curr] < lowestReachTime[child]`.
 * (Notice the strict '<'. If it was '<=', the child has a backdoor to `curr` itself,
 * meaning they are part of a cycle, so the edge between them isn't critical!)
 *
 * ============================================================================
 * ⚙️ APPROACH, LOGIC & TRAPS AVOIDED
 * ============================================================================
 * 1. The Forward Edge Trap (Why the Bridge check is INSIDE the Tree Edge block):
 * We ONLY evaluate the Bridge condition (`discoveryTime < lowestAdjReachTime`)
 * for actual, unvisited DFS children. If we evaluated this for already-visited
 * nodes, we might accidentally check a "Forward Edge" to a descendant. Since
 * descendants are discovered *after* the current node, the math would trivially
 * and falsely flag the edge as a Bridge.
 * * 2. The Data Leak Trap (Why Back Edges strictly use `discoveryTime`):
 * When hitting a Back Edge (an already visited ancestor), we update our reach
 * using `discoveryTime[adjN]`, NOT `lowestReachTime[adjN]`. If we used the
 * latter, we risk "leaking" a lower time from an unrelated subtree, which would
 * mask a valid Bridge.
 * * 3. No Root Node Exception:
 * Unlike Articulation Points, Bridges are just edges. We don't care if a node
 * is the root of the DFS tree or not. The math holds true universally.
 *
 * 4. Platform-Specific Fixes:
 * - `clear()` and `assign()` are called on global states in the main function
 * to prevent data leaking between multiple test cases run on the same object.
 *
 * ============================================================================
 * ⏱️ COMPLEXITY ANALYSIS
 * ============================================================================
 * - Time Complexity: O(V + E)
 * Standard DFS processes every vertex (V) once and every edge (E) twice.
 * - Space Complexity: O(V + E)
 * O(V + E) for the Adjacency List. O(V) for the tracking arrays (`vis`,
 * `discoveryTime`, `lowestReachTime`, `bridges`) and the recursion stack.
 */
class Solution
{
private:
    vector<bool> vis;
    vector<int> discoveryTime, lowestReachTime;
    vector<vector<int>> bridges;
    int timer = 0;

    void dfs(int curN, int parN, const vector<vector<int>> &adjL)
    {

        vis[curN] = true;
        discoveryTime[curN] = timer;
        lowestReachTime[curN] = timer;
        ++timer;

        for (int adjN : adjL[curN])
        {

            // Do not immediately walk backward to the parent
            if (adjN == parN)
            {
                continue;
            }

            // Tree edge (Unvisited Node)
            if (!vis[adjN])
            {

                dfs(adjN, curN, adjL);

                // 1. Get the child's lowest reach
                int lowestAdjReachTime = lowestReachTime[adjN];

                // 2. ONLY evaluate the Bridge condition for actual DFS children!
                // Strictly `<` implies absolutely NO backdoors exist.
                if (discoveryTime[curN] < lowestAdjReachTime)
                {
                    bridges.push_back({curN, adjN});
                }

                // 3. Update current node's reach
                lowestReachTime[curN] = min(lowestReachTime[curN], lowestAdjReachTime);
            }
            // Back edge / Forward edge (Already Visited Node)
            else
            {
                // Safely use discovery time to prevent data leak across unrelated subtrees.
                lowestReachTime[curN] = min(lowestReachTime[curN], discoveryTime[adjN]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {

        // Build Adjacency List
        vector<vector<int>> adjL(n);
        for (const auto &e : connections)
        {
            int u = e[0];
            int v = e[1];

            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }

        // CRITICAL: Reset states for multiple test cases on the same object
        vis.assign(n, false);
        discoveryTime.assign(n, INT_MAX);
        lowestReachTime.assign(n, INT_MAX);
        bridges.clear();
        timer = 0;

        // Run DFS
        // (LeetCode guarantees a connected graph for this specific problem,
        // but the loop safely handles disconnected graphs if constraints change).
        for (int i = 0; i < n; ++i)
        {
            if (!vis[i])
            {
                dfs(i, -1, adjL);
            }
        }

        return bridges;
    }
};

int main()
{
    return 0;
}