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

1. Title: Number of Operations to Make Network Connected

Links:
https://takeuforward.org/data-structure/number-of-operations-to-make-network-connected-dsu-g-49/
https://www.youtube.com/watch?v=FYrl7iz9_ZU
https://takeuforward.org/plus/dsa/problems/number-of-operations-to-make-network-connected?tab=editorial
https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/


Problem statement:
There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.
You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.
Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1.

Examples:
    Example 1:
    Input: n = 4, connections = [[0,1],[0,2],[1,2]]
    Output: 1
    Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.

    Example 2:
    Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
    Output: 2

    Example 3:
    Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
    Output: -1
    Explanation: There are not enough cables.


Constraints:
    1 <= n <= 10^5
    1 <= connections.length <= min(n * (n - 1) / 2, 10^5)
    connections[i].length == 2
    0 <= ai, bi < n
    ai != bi
    There are no repeated connections.
    No two computers are connected by more than one cable.



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
// 1. Title: Number of Operations to Make Network Connected
//-------------------------------------------------------------------------------

//============================================================================
// Approach 1 — Disjoint Set Union (Optimal Space & Overhead) [RECOMMENDED]
//============================================================================

//============================================================================
// Helper Class — Disjoint Set Union (Union-Find)
//============================================================================
class DSU
{
    vector<int> parent, size;

public:
    // Dynamically tracks the number of isolated networks
    int components;

    DSU(int n)
    {
        components = n;
        parent.resize(n + 1);
        size.resize(n + 1, 1);

        for (int i = 0; i <= n; ++i)
        {
            parent[i] = i;
        }
    }

    int findP(int i)
    {
        int p = parent[i];
        if (p == i)
        {
            return p;
        }
        // Path Compression
        return parent[i] = findP(p);
    }

    void dunion(int u, int v)
    {
        int pu = findP(u);
        int pv = findP(v);

        // Already connected, no change to components
        if (pu == pv)
        {
            return;
        }

        int su = size[pu];
        int sv = size[pv];

        // Union by Size
        if (su <= sv)
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];
        }

        // A successful merge reduces the total number of isolated islands by 1
        components--;
    }
};

class Solution_DSU
{
public:
    /**
     * @brief Component counting using DSU.
     *
     * Why this is preferred:
     * - Space efficient: O(V) space because we do NOT build an Adjacency List.
     * - Fast execution: Avoids dynamic memory allocations required to build the graph.
     *
     * Time Complexity: O(V + E) — V to initialize DSU, E to process edges.
     * Space Complexity: O(V) — Only requires parent and size arrays.
     */
    int makeConnected(int n, vector<vector<int>> &connections)
    {

        // 1. Pigeonhole Principle: N nodes require strictly N - 1 edges to connect
        if (connections.size() < n - 1)
        {
            return -1;
        }

        DSU dsu(n);

        // 2. Build the networks and automatically track component count
        for (const auto &e : connections)
        {
            dsu.dunion(e[0], e[1]);
        }

        // 3. To connect C components together, we need exactly C - 1 bridges
        return dsu.components - 1;
    }
};

//============================================================================
// Approach 2 — Breadth-First Search (Classic Graph Traversal)
//============================================================================
class Solution_BFS
{
public:
    /**
     * @brief Component counting using Breadth-First Search.
     *
     * Why you should know this:
     * - If the problem was modified to ask for the ACTUAL PATHS between the
     * disconnected computers, DSU would be useless, and BFS/DFS would be required.
     *
     * Time Complexity: O(V + E) — Standard BFS traversal.
     * Space Complexity: O(V + E) — Required to store the Adjacency List.
     */
    int makeConnected(int n, vector<vector<int>> &connections)
    {

        // 1. Pigeonhole Principle: N nodes require strictly N - 1 edges to connect
        if (connections.size() < n - 1)
        {
            return -1;
        }

        // 2. Build Adjacency List
        vector<vector<int>> adjL(n);
        for (const auto &e : connections)
        {
            adjL[e[0]].push_back(e[1]);
            adjL[e[1]].push_back(e[0]);
        }

        // 3. BFS Traversal to map out and count disconnected islands
        vector<int> vis(n, 0);
        int countDisCon = 0;
        queue<int> q;

        for (int i = 0; i < n; i++)
        {

            // Skip nodes already claimed by a previously counted component
            if (vis[i] != 0)
            {
                continue;
            }

            // Unvisited node found! This is a brand new isolated component
            countDisCon++;
            q.push(i);
            vis[i] = 1;

            // Map out every node connected to this specific component
            while (!q.empty())
            {
                int curN = q.front();
                q.pop();

                for (const int &adjN : adjL[curN])
                {
                    if (vis[adjN] == 0)
                    {
                        vis[adjN] = 1;
                        q.push(adjN);
                    }
                }
            }
        }

        // 4. To connect C components together, we need exactly C - 1 bridges
        return countDisCon - 1;
    }
};

int main()
{
    return 0;
}