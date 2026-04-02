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

1. Title: Strongly Connected Components - Kosaraju's Algorithm

Links:
https://takeuforward.org/graph/strongly-connected-components-kosarajus-algorithm-g-54/
https://www.youtube.com/watch?v=R6uoSjZ2imo
https://takeuforward.org/plus/dsa/problems/kosaraju's-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1


Problem statement:
Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges. The graph is represented as a 2D vector edges[][], where each entry edges[i] = [u, v] denotes a direct edge from vertex u to v. Find the number of strongly connected components in the graph.


Examples :
    Input: V = 5, E = 5, edges[][] = [[0, 2], [0, 3], [1, 0], [2, 1], [3, 4]]
    Output: 3
    Explanation: We can clearly see that there are 3 Strongly Connected Components in the Graph.

    Input: V = 3, E = 3, edges[][] = [[0, 1], [1, 2], [2, 0]]
    Output: 1
    Explanation: All of the nodes are connected to each other. So, there's only one SCC.

    Input: V = 2, E = 1, edges[][] = [[0, 1]]
    Output: 2


Constraints:
    2<=adj.size()<=10^6
    0<=edges<=adj.size()-1


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
// 1. Title: Strongly Connected Components - Kosaraju's Algorithm
//-------------------------------------------------------------------------------

#include <vector>
#include <stack>

using namespace std;

/**
 * @class Solution
 * @brief Finds the number of Strongly Connected Components (SCCs) using Kosaraju's Algorithm.
 *
 * ============================================================================
 * 🧠 INTUITION & IDEA (The "Bleeding" Problem)
 * ============================================================================
 * In a directed graph, finding SCCs with a normal DFS is dangerous because
 * the DFS can "bleed" from one component into another across one-way bridges.
 * Kosaraju's Algorithm prevents this "bleeding" using a brilliant 3-step trick:
 * * 1. The Finish Time Stack: We run a normal DFS. A node is pushed to a stack ONLY
 * after all its neighbors are fully explored. This naturally puts "sink" clusters
 * at the bottom of the stack and "source" clusters at the top.
 * 2. Reverse the World (Transpose): We reverse the direction of every single arrow
 * in the graph. This magically turns all the old "source" clusters into "sinks".
 * 3. Pop and Count (Trapped DFS): We pop nodes from our stack (starting with the
 * old sources, which are now sinks) and run a second DFS. Because the edges
 * are reversed, the DFS cannot cross the bridges and gets perfectly TRAPPED
 * inside its own SCC. Every trapped DFS equals one SCC!
 *
 * ============================================================================
 * ⏱️ COMPLEXITY ANALYSIS
 * ============================================================================
 * - Time Complexity: O(V + E)
 * We perform two DFS passes O(V + E) and one graph reversal O(E).
 * - Space Complexity: O(V + E)
 * For the Adjacency List, visited array, and the recursion/stack space. By
 * clearing and reusing the same Adjacency List, we save significant memory!
 */
class Solution
{

private:
    vector<bool> vis;
    vector<vector<int>> adjL;
    stack<int> finishStack;
    int sccCount;

    /**
     * @brief A unified DFS that handles both Step 1 (filling stack) and Step 3 (counting).
     * @param curN The current node being explored.
     * @param isFirstPass Boolean flag. If true, it pushes nodes to the stack upon finishing.
     */
    void dfs(int curN, bool isFirstPass)
    {

        vis[curN] = true;

        for (int adjN : adjL[curN])
        {
            if (!vis[adjN])
            {
                dfs(adjN, isFirstPass);
            }
        }

        // Step 1 logic: Push to stack ONLY after exploring all paths from this node
        if (isFirstPass)
        {
            finishStack.push(curN);
        }
    }

public:
    int kosaraju(int V, vector<vector<int>> &edges)
    {

        int n = V;

        // ====================================================================
        // STEP 1: The Finish Time Stack
        // Run DFS to order nodes by their finish times. Source nodes will
        // end up at the top of the stack, and Sink nodes at the bottom.
        // ====================================================================
        vis.assign(n, false);
        adjL.assign(n, {});
        finishStack = stack<int>(); // Clear stack to prevent multi-testcase leakage
        sccCount = 0;

        // Build original graph
        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            adjL[u].push_back(v); // Directed edge: u -> v
        }

        // Run first DFS pass
        for (int i = 0; i < n; ++i)
        {
            if (!vis[i])
            {
                dfs(i, true);
            }
        }

        // ====================================================================
        // STEP 2: Reverse the World (Transpose Graph)
        // Reverse all arrows so that Source SCCs become Sink SCCs.
        // We reuse the existing adjL to save O(V+E) memory!
        // ====================================================================
        adjL.assign(n, {}); // Clear the old graph

        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            adjL[v].push_back(u); // Reversed edge: v -> u
        }

        // ====================================================================
        // STEP 3: Pop and Count (Trapped DFS)
        // Pop nodes from the stack. Because the graph is reversed and we
        // process in this specific order, the DFS hits the walls of previously
        // visited SCCs and cannot bleed. It gets trapped inside exactly one SCC.
        // ====================================================================
        vis.assign(n, false); // Reset visited array for the second pass

        while (!finishStack.empty())
        {

            int curN = finishStack.top();
            finishStack.pop();

            // If unvisited, we found a new SCC head!
            if (!vis[curN])
            {
                ++sccCount;
                dfs(curN, false); // Trapped DFS (doesn't push to stack)
            }
        }

        return sccCount;
    }
};

int main()
{
    return 0;
}