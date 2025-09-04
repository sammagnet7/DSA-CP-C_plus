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

1. Title: Bridges in Graph - Using Tarjan's Algorithm of time in and low time: G-55

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
    2 <= n <= 105
    n - 1 <= connections.length <= 105
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
// 1. Title: Bridges in Graph - Using Tarjan's Algorithm of time in and low time: G-55
//-------------------------------------------------------------------------------
//

class Solution
{
    int time = 0; // Global timer to assign discovery times during DFS

    // ------------------------------------------------------------------------
    // DFS Recursive Function to Find Bridges
    //
    // Parameters:
    // - cur: current node being visited
    // - parent: parent node in DFS tree (to avoid trivial backtracking)
    // - adjL: adjacency list of graph
    // - bridges: stores all critical connections (bridges)
    // - vis: visited array to track visited nodes
    // - vis_time: discovery time (when a node was first visited)
    // - min_adj_time: lowest discovery time reachable from this node
    //
    // Core Idea (Tarjan’s Algorithm):
    // - discovery time (vis_time[u]) = order in which u was visited
    // - lowest time (min_adj_time[u]) = earliest discovered node reachable
    //   from u (including back edges)
    // - if low[v] > tin[u] → edge (u,v) is a bridge
    // ------------------------------------------------------------------------
    void findBridgeRec(int cur, int parent, vector<vector<int>> &adjL,
                       vector<vector<int>> &bridges, vector<int> &vis,
                       vector<int> &vis_time, vector<int> &min_adj_time)
    {

        vis[cur] = 1;
        vis_time[cur] = min_adj_time[cur] = time; // initialize discovery & low
        time++;

        // Explore all neighbors
        for (int adjN : adjL[cur])
        {

            if (adjN == parent)
                continue; // skip the edge back to parent

            if (!vis[adjN])
            {
                // If neighbor not visited, DFS deeper
                findBridgeRec(adjN, cur, adjL, bridges, vis, vis_time, min_adj_time);

                // After return, update current node's low value
                min_adj_time[cur] = min(min_adj_time[cur], min_adj_time[adjN]);

                // Bridge condition: If neighbor’s low > current’s discovery
                if (min_adj_time[adjN] > vis_time[cur])
                {
                    bridges.push_back({cur, adjN});
                }
            }
            else
            {
                // If neighbor already visited (back edge), update low
                min_adj_time[cur] = min(min_adj_time[cur], vis_time[adjN]);
            }
        }
    }

public:

    // ------------------------------------------------------------------------
    // Function: criticalConnections
    // Problem: Find all bridges in an undirected graph
    //
    // Intuition:
    // - A bridge is an edge that, if removed, increases the number of components.
    // - Use DFS + Tarjan’s algorithm with discovery & low arrays.
    //
    // Approach:
    // 1. Build adjacency list from edge list.
    // 2. Initialize:
    //    - vis[]: visited markers
    //    - vis_time[]: discovery times
    //    - min_adj_time[]: lowest reachable discovery times
    // 3. Perform DFS (Tarjan’s) starting from node 0 (or any unvisited node).
    // 4. Collect all edges (u,v) satisfying low[v] > disc[u].
    //
    // Complexity:
    // - Time: O(V + E) → standard DFS traversal
    // - Space: O(V + E) for adjacency list, O(V) for arrays
    // ------------------------------------------------------------------------
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {

        // Step 1: Build adjacency list
        vector<vector<int>> adjL(n);
        for (auto &e : connections)
        {
            adjL[e[0]].push_back(e[1]);
            adjL[e[1]].push_back(e[0]);
        }

        // Step 2: Initialize helper arrays
        vector<vector<int>> bridges;     // stores all found bridges
        vector<int> vis(n, 0);           // visited array
        vector<int> vis_time(n, -1);     // discovery times
        vector<int> min_adj_time(n, -1); // lowest reachable discovery times

        // Step 3: Run DFS (Tarjan’s)
        // Note: Graph may be disconnected, so loop over all nodes
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                findBridgeRec(i, -1, adjL, bridges, vis, vis_time, min_adj_time);
            }
        }

        return bridges;
    }
};

int main()
{
    return 0;
}