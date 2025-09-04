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

1. Title: Articulation Point in Graph: G-56

Links:
https://takeuforward.org/data-structure/articulation-point-in-graph-g-56/
https://www.youtube.com/watch?v=j1QDfU21iZk
https://takeuforward.org/plus/dsa/problems/articulation-point-in-graph?tab=editorial
https://www.geeksforgeeks.org/problems/articulation-point-1/1
https://www.geeksforgeeks.org/problems/articulation-point2616/1

Problem statement:
You are given an undirected graph with V vertices and E edges. The graph is represented as a 2D array edges[][], where each element edges[i] = [u, v] indicates an undirected edge between vertices u and v.
Your task is to return all the articulation points (or cut vertices) in the graph.
An articulation point is a vertex whose removal, along with all its connected edges, increases the number of connected components in the graph.

Note: The graph may be disconnected, i.e., it may consist of more than one connected component.
If no such point exists, return {-1}.

Examples :
    Input: V = 5, edges[][] = [[0, 1], [1, 4], [4, 3], [4, 2], [2, 3]]
    Output: [1, 4]
    Explanation: Removing the vertex 1 or 4 will disconnects the graph as-

    Input: V = 4, edges[][] = [[0, 1], [0, 2]]
    Output: [0]
    Explanation: Removing the vertex 0 will increase the number of disconnected components to 3.

Constraints:
    1 ≤ V, E ≤ 104


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
// 1. Title: Articulation Point in Graph: G-56
//-------------------------------------------------------------------------------
//

class Solution
{
    // ------------------------------------------------------------------------
    // Tarjan’s Algorithm for Articulation Points (Cut Vertices)
    // ------------------------------------------------------------------------
    // Intuition:
    // - A vertex u is an articulation point if removing u (and all its incident
    //   edges) increases the number of connected components.
    // - Using DFS, we track for every node:
    //     * visTime[u]  : discovery time (the time u is first seen)
    //     * minAdjTime[u] (low[u]) : the earliest discovery time reachable
    //       from u via any downward edges (tree edges) + at most one back edge.
    // - Key condition (for non-root u):
    //     If there exists a child v of u in the DFS tree such that
    //         low[v] >= disc[u]
    //       then u is an articulation point.
    // - Root special case:
    //     The DFS-root is an articulation point iff it has > 1 children.
    //
    // Approach:
    // 1) Build adjacency list.
    // 2) DFS each unvisited node:
    //     - Set disc[u] and low[u] to timer++
    //     - For each neighbor v:
    //         - If v == parent, skip
    //         - If v not visited:
    //               recurse on v, update low[u] = min(low[u], low[v])
    //               if (low[v] >= disc[u] and u is not root) → mark u
    //           Else (back edge):
    //               low[u] = min(low[u], disc[v])
    //     - After iterating neighbors:
    //         if (u is root and childCount > 1) → mark u
    //
    // Complexity:
    // - Time:  O(V + E) (single DFS over the graph)
    // - Space: O(V + E) for adjacency + O(V) for vis/disc/low/mark arrays
    // ------------------------------------------------------------------------

    int time = 0; // global DFS timer to assign discovery times (disc[])

    // DFS utility to find articulation points
    void artPointFindRec(int cur, int par,
                         vector<int> adj[],
                         vector<int> &vis,
                         vector<int> &visTime,     // disc[]
                         vector<int> &minAdjTime,  // low[]
                         vector<int> &cutVertices) // mark array: 1 if articulation
    {
        vis[cur] = 1;                            // mark current node visited
        visTime[cur] = minAdjTime[cur] = time++; // initialize disc & low

        int child = 0; // counts DFS-tree children of `cur` (needed for root rule)

        // Explore all neighbors
        for (int &adjN : adj[cur])
        {

            if (adjN == par)
            {
                // Skip the edge leading back to parent (not a back-edge)
                continue;
            }

            if (!vis[adjN])
            {
                // Tree-edge: go deeper
                child++;
                artPointFindRec(adjN, cur, adj, vis, visTime, minAdjTime, cutVertices);

                // After DFS on child, update low[cur] with low[child]
                minAdjTime[cur] = min(minAdjTime[cur], minAdjTime[adjN]);

                // ---------- Bridge-style check adapted for cut vertices ----------
                // If the earliest reachable ancestor from child adjN is NOT earlier
                // than cur's discovery, then removing `cur` disconnects child’s subtree.
                // This condition applies only if `cur` is NOT the DFS root.
                if (minAdjTime[adjN] >= visTime[cur] && par != -1)
                { // NOTE
                    cutVertices[cur] = 1;
                }
            }
            else
            {
                // Back-edge: adjN is visited and NOT parent → update low[cur]
                // Use neighbor's discovery time to potentially lower low[cur].
                minAdjTime[cur] = min(minAdjTime[cur], visTime[adjN]); // NOTE
            }
        }

        // ---------- Root special case ----------
        // If cur is root (par == -1) and has more than one DFS child,
        // removing cur will split the component.
        if (par == -1 && child > 1)
        { // NOTE
            cutVertices[cur] = 1;
        }
    }

public:
    vector<int> articulationPoints(int V, vector<vector<int>> &edges)
    {
        // Build adjacency list (undirected)
        vector<int> adj[V];
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Helper arrays:
        // vis[i]       : visited marker
        // visTime[i]   : discovery time (disc)
        // minAdjTime[i]: lowest reachable discovery time (low)
        // cutVertices[i]: mark array for articulation points
        vector<int> vis(V, 0);
        vector<int> visTime(V, -1);
        vector<int> minAdjTime(V, -1);
        vector<int> cutVertices(V, 0); // NOTE: use a mark array to avoid duplicates
        vector<int> ans;

        // Graph can be disconnected → run DFS from every unvisited node
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                artPointFindRec(i, -1, adj, vis, visTime, minAdjTime, cutVertices);
            }
        }

        // Collect all articulation points in ascending order
        for (int i = 0; i < V; i++)
        {
            if (cutVertices[i] == 1)
            {
                ans.push_back(i);
            }
        }

        // If none, return [-1] as per convention
        return ans.empty() ? vector<int>(1, -1) : ans;
    }
};

int main()
{
    return 0;
}