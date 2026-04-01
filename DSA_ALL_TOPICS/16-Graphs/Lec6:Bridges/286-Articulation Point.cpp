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

1. Title: Articulation Point in Graph

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
    1 ≤ V, E ≤ 10^4


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
// 1. Title: Articulation Point in Graph
//-------------------------------------------------------------------------------

/**
 * @class Solution
 * @brief Finds all Articulation Points (Cut Vertices) using a highly optimized Tarjan's Algorithm.
 *
 * ============================================================================
 * 🧠 INTUITION & IDEA
 * ============================================================================
 * An Articulation Point (AP) is a node that, if removed, splits the graph into
 * multiple disconnected components.
 * We use Tarjan's Algorithm to track two things for every node:
 * 1. `discoveryTime`: The exact timer tick when the node was first visited.
 * 2. `lowestReachTime`: The earliest `discoveryTime` this node (or its children) can reach.
 * * A node is an Articulation Point if it has a child that CANNOT reach any node
 * discovered *before* the current node. Mathematically: `discoveryTime[curr] <= lowestReachTime[child]`.
 *
 * ============================================================================
 * ⚙️ APPROACH, LOGIC & TRAPS AVOIDED
 * ============================================================================
 * 1. Duplicate Prevention (The Local Boolean):
 * Instead of using a global `isAP` boolean array or a Set, we use a local
 * `isArtPoint` boolean inside the DFS frame. If multiple independent children
 * flag the current node as an AP, it is still only pushed to the final array
 * EXACTLY ONCE at the very end of its DFS frame.
 * * 2. The Forward Edge Trap (Why the AP check is INSIDE the Tree Edge block):
 * We ONLY evaluate the AP condition (`discoveryTime <= lowestAdjReachTime`)
 * for actual, unvisited DFS children. If we evaluated this for already-visited
 * nodes, we might accidentally check a "Forward Edge" to a descendant. Since
 * descendants are discovered *after* the current node, the math would trivially
 * and falsely flag the current node as an AP.
 * * 3. The Data Leak Trap (Why Back Edges strictly use `discoveryTime`):
 * When hitting a Back Edge (an already visited ancestor), we update our reach
 * using `discoveryTime[adjN]`, NOT `lowestReachTime[adjN]`. If we used the
 * latter, we risk "leaking" a lower time from an unrelated subtree (e.g., the
 * other side of a Bowtie Graph), which would mask a valid Articulation Point.
 * * 4. The Root Node Exception:
 * The starting node of the DFS (`parN == -1`) has no ancestors, so the math
 * check is invalid. A root node is an AP *only* if it physically acts as a
 * bridge between 2 or more completely independent DFS subtrees (`IndpChildCount > 1`).
 *
 * 5. Platform-Specific Fixes:
 * - `clear()` and `assign()` are called on global states in the main function
 * to prevent data leaking between multiple test cases run on the same object.
 * - The output array is sorted at the end, as required by the platform.
 * - Returns `{-1}` if the array is empty.
 *
 * ============================================================================
 * ⏱️ COMPLEXITY ANALYSIS
 * ============================================================================
 * - Time Complexity: O(V + E) + O(A log A)
 * Standard DFS processes every vertex (V) once and every edge (E) twice.
 * Sorting the resulting AP array takes O(A log A) where A is the number of APs.
 * - Space Complexity: O(V + E)
 * O(V + E) for the Adjacency List. O(V) for the tracking arrays (`vis`,
 * `discoveryTime`, `lowestReachTime`) and the recursion stack.
 */
class Solution
{
private:
    vector<bool> vis;
    vector<int> discoveryTime, lowestReachTime;
    vector<int> artPoints;
    int timer = 0;

    void dfs(int curN, int parN, vector<vector<int>> &adjL)
    {

        vis[curN] = true;
        discoveryTime[curN] = timer;
        lowestReachTime[curN] = timer;
        ++timer;

        bool isArtPoint = false;
        int IndpChildCount = 0;

        for (int adjN : adjL[curN])
        {

            if (adjN == parN)
            {
                continue;
            }

            // Tree edge (Unvisited Node)
            if (!vis[adjN])
            {

                ++IndpChildCount;

                dfs(adjN, curN, adjL);

                // 1. Get the child's lowest reach
                int lowestAdjReachTime = lowestReachTime[adjN];

                // 2. ONLY evaluate the AP condition for actual DFS children!
                // This avoids the Forward Edge Trap.
                if (discoveryTime[curN] <= lowestAdjReachTime)
                {
                    isArtPoint = true;
                }

                // 3. Update current node's reach
                lowestReachTime[curN] = min(lowestReachTime[curN], lowestAdjReachTime);
            }
            // Back edge / Forward edge (Already Visited Node)
            else
            {
                // Safely use discovery time to prevent data leak across unrelated subtrees.
                // DO NOT check AP condition here!
                lowestReachTime[curN] = min(lowestReachTime[curN], discoveryTime[adjN]);
            }
        }

        // If it's a normal node and flagged as an AP, record it exactly once
        if (parN != -1 && isArtPoint)
        {
            artPoints.push_back(curN);
            return;
        }

        // Edge case handling for ROOT nodes
        if (parN == -1 && IndpChildCount > 1)
        {
            artPoints.push_back(curN);
            return;
        }
    }

public:
    vector<int> articulationPoints(int V, vector<vector<int>> &edges)
    {

        int n = V;
        vector<vector<int>> adjL(n);

        for (auto &e : edges)
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
        artPoints.clear();
        timer = 0;

        // Run DFS (Graph might be disconnected)
        for (int i = 0; i < n; ++i)
        {
            if (!vis[i])
            {
                dfs(i, -1, adjL);
            }
        }

        // Problem requires returning {-1} if empty
        if (artPoints.empty())
        {
            return {-1};
        }

        // Problem requires sorted output
        sort(artPoints.begin(), artPoints.end());

        return artPoints;
    }
};

int main()
{
    return 0;
}