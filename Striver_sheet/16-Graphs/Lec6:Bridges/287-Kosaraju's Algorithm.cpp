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

1. Title: Strongly Connected Components - Kosaraju's Algorithm: G-54

Links:
https://takeuforward.org/graph/strongly-connected-components-kosarajus-algorithm-g-54/
https://www.youtube.com/watch?v=R6uoSjZ2imo
https://takeuforward.org/plus/dsa/problems/kosaraju's-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1


Problem statement:
Given an adjacency list, adj of Directed Graph, Find the number of strongly connected components in the graph.


Examples :
    Input: adj[][] = [[2, 3], [0], [1], [4], []]
    Output: 3
    Explanation: We can clearly see that there are 3 Strongly Connected Components in the Graph.
    Input: adj[][] = [[1], [2], [0]]
    Output: 1
    Explanation: All of the nodes are connected to each other. So, there's only one SCC.

    Input: adj[][] = [[1], []]
    Output: 2

Constraints:
    2<=adj.size()<=106
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
// 1. Title: Strongly Connected Components - Kosaraju's Algorithm: G-54
//-------------------------------------------------------------------------------
//

// Position this line where user code will be pasted.
class Solution
{

    // --------------------------------------------------------------------------
    // DFS that records finishing times (1st pass) OR just visits (2nd pass)
    // - finishTimes is used only in the 1st pass to push nodes *after* exploring
    //   their descendants (i.e., in post-order). In the 2nd pass we can pass a
    //   dummy stack we ignore.
    // --------------------------------------------------------------------------
private:
    void dfs(int cur,
             vector<vector<int>> &adjL,
             vector<int> &vis,
             stack<int> &finishTimes)
    {
        vis[cur] = 1; // mark current node visited

        // explore all outgoing edges
        for (int adjN : adjL[cur])
        {
            if (!vis[adjN])
            {
                dfs(adjN, adjL, vis, finishTimes);
            }
        }

        // post-order push: records finishing time (used by 1st pass only)
        finishTimes.push(cur);
    }

public:
    // --------------------------------------------------------------------------
    // Kosaraju's Algorithm: Count Strongly Connected Components (SCCs)
    //
    // Intuition:
    // 1) Run DFS on the original graph to compute nodes' finishing times.
    //    (Nodes finishing later get pushed later; they should be processed first
    //     on the reversed graph.)
    // 2) Build the transpose (reverse) graph by reversing all edges.
    // 3) Pop nodes in decreasing finishing time order; for each unvisited node,
    //    run DFS on the transpose graph. Each DFS tree corresponds to one SCC.
    //
    // Complexity:
    // - Time:  O(V + E)  (two DFS traversals + O(E) edge reversal)
    // - Space: O(V + E)  (adjacency lists, visited array, stack)
    // --------------------------------------------------------------------------
    int kosaraju(vector<vector<int>> &adjL)
    {
        const int V = (int)adjL.size();

        // -------------------- 1) First pass: finishing times on original graph
        vector<int> vis(V, 0);
        stack<int> finishTimes; // stores nodes by finish order (top = latest)

        for (int i = 0; i < V; i++)
        {
            if (vis[i])
                continue;
            dfs(i, adjL, vis, finishTimes); // pushes nodes after full exploration
        }

        // -------------------- 2) Build transpose graph (reverse all edges)
        // Note: Reversing edges does not change SCCs, but in the transpose graph,
        // exploring in decreasing finish time isolates one SCC per DFS.
        vector<vector<int>> adjL_MOD(V);
        for (int u = 0; u < V; u++)
        {
            for (int v : adjL[u])
            {
                adjL_MOD[v].push_back(u); // reverse edge u->v to v->u
            }
        }

        // -------------------- 3) Second pass: DFS in finish-time order on transpose
        fill(vis.begin(), vis.end(), 0); // reset visited
        int componentCount = 0;

        // dummy stack for dfs call in 2nd pass (we don't need finishing times now)
        stack<int> dummy;

        while (!finishTimes.empty())
        {
            int cur = finishTimes.top();
            finishTimes.pop();

            if (vis[cur])
                continue;

            // Each DFS here visits exactly one SCC in the transpose graph.
            dfs(cur, adjL_MOD, vis, dummy);
            componentCount++;
        }

        return componentCount;
    }
};

int main()
{
    return 0;
}