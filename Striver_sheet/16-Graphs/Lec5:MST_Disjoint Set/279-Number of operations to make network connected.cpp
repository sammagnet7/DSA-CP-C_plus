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

1. Title: Number of Operations to Make Network Connected - DSU: G-49.

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
    1 <= n <= 105
    1 <= connections.length <= min(n * (n - 1) / 2, 105)
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
// 1. Title: Number of Operations to Make Network Connected - DSU: G-49.
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    //----------------------------------------------------------------------------
    // Approach 1: Graph Traversal (BFS)
    //----------------------------------------------------------------------------
    // Intuition:
    // - A connected graph with n nodes requires at least (n-1) edges.
    // - If edges < n-1 → impossible, return -1.
    // - Otherwise, count the number of connected components via BFS/DFS.
    // - To connect k disconnected components, we need (k - 1) extra edges.
    //
    // Steps:
    // 1. Build adjacency list.
    // 2. Use BFS to count disconnected components.
    // 3. Return (components - 1).
    //
    // Complexity:
    // - Time  : O(N + E) → traverses all vertices and edges.
    // - Space : O(N + E) → adjacency list + visited[].
    //----------------------------------------------------------------------------

    // int makeConnected(int n, vector<vector<int>>& connections) {
    //     int eCount = connections.size();

    //     // Not enough cables
    //     if (n - 1 > eCount)
    //         return -1;

    //     // Step 1: Build adjacency list
    //     vector<vector<int>> adjL(n);
    //     for (auto &e : connections) {
    //         adjL[e[0]].push_back(e[1]);
    //         adjL[e[1]].push_back(e[0]);
    //     }

    //     // Step 2: BFS to count components
    //     vector<int> vis(n, 0);
    //     int countDisCon = 0;
    //     queue<int> q;

    //     for (int i = 0; i < n; i++) {
    //         if (vis[i] != 0) continue; // already visited in previous BFS

    //         countDisCon++;  // new component found
    //         q.push(i);
    //         vis[i] = 1;

    //         while (!q.empty()) {
    //             int curN = q.front(); q.pop();

    //             for (int &adjN : adjL[curN]) {
    //                 if (vis[adjN] == 0) {
    //                     vis[adjN] = 1;
    //                     q.push(adjN);
    //                 }
    //             }
    //         }
    //     }

    //     // Step 3: Need (components - 1) edges
    //     return (countDisCon - 1);
    // }

    //----------------------------------------------------------------------------
    // Approach 2: Disjoint Set Union (DSU / Union-Find)
    //----------------------------------------------------------------------------
    // Intuition:
    // - Use DSU to group computers into connected components.
    // - After unioning all given edges, count number of distinct parents.
    // - To connect k components, we need (k - 1) operations.
    //
    // Steps:
    // 1. Initialize DSU (each node in its own set).
    // 2. Union all edges.
    // 3. Count distinct ultimate parents.
    // 4. Return (components - 1).
    //
    // Complexity:
    // - Time  : O(E α(N)) ≈ O(E), since DSU ops are nearly O(1).
    // - Space : O(N) for parent[] and size[].
    //----------------------------------------------------------------------------
    class Disjoint
    {
    private:
        vector<int> p, size;

    public:
        Disjoint(int n)
        {
            p.resize(n);
            size.resize(n, 1);
            for (int i = 0; i < n; i++)
                p[i] = i;
        }

        int findUPar(int u)
        {
            if (u == p[u])
                return u;
            return p[u] = findUPar(p[u]); // path compression
        }

        void UbyS(int u, int v)
        {
            int u_p = findUPar(u);
            int v_p = findUPar(v);

            if (u_p == v_p)
                return;

            if (size[u_p] < size[v_p])
            {
                p[u_p] = v_p;
                size[v_p] += size[u_p];
            }
            else
            {
                p[v_p] = u_p;
                size[u_p] += size[v_p];
            }
        }
    };

    int makeConnected(int n, vector<vector<int>> &connections)
    {
        int eCount = connections.size();

        // Not enough cables
        if (eCount < n - 1)
            return -1;

        Disjoint DS(n);

        // Step 1: Union all edges
        for (auto &e : connections)
        {
            int u = e[0];
            int v = e[1];
            DS.UbyS(u, v);
        }

        // Step 2: Count distinct components
        int compCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (DS.findUPar(i) == i)
                compCount++;
        }

        // Step 3: Need (components - 1) edges
        return compCount - 1;
    }
};

int main()
{
    return 0;
}