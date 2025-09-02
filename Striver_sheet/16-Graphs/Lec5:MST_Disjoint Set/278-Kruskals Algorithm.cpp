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

1. Title: Kruskal's Algorithm - Minimum Spanning Tree : G-47

Links:
https://takeuforward.org/data-structure/kruskals-algorithm-minimum-spanning-tree-g-47/
https://www.youtube.com/watch?v=DMnDM_sxVig
https://takeuforward.org/plus/dsa/problems/find-the-mst-weight?tab=editorial


Problem statement:
Given a weighted, undirected, and connected graph with V vertices and E edges, the task is to find the sum of the weights of the edges in the Minimum Spanning Tree (MST) of the graph using Kruskal's Algorithm. The graph is represented as an edge list edges[][], where edges[i] = [u, v, w] denotes an undirected edge between u and v with weight w.

Example:
    Input: V = 3, E = 3, edges[][] = [[0, 1, 5], [1, 2, 3], [0, 2, 1]]
    Output: 4
    Explanation:
    The Spanning Tree resulting in a weight of 4 is shown above.

    Input: V = 2, E = 1, edges = [[0, 1, 5]]
    Output: 5
    Explanation: Only one Spanning Tree is possible which has a weight of 5.

Constraints:
    2 ≤ V ≤ 1000
    V-1 ≤ E ≤ (V*(V-1))/2
    1 ≤ w ≤ 1000
    The graph is connected and doesn't contain self-loops & multiple edges.



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
// 1. Title: Kruskal's Algorithm - Minimum Spanning Tree : G-47
//-------------------------------------------------------------------------------
//

//----------------------------------------------------------------------------
//  Disjoint Set Union (Union-Find) with Union by Size + Path Compression
//----------------------------------------------------------------------------
// Intuition:
// - DSU (Disjoint Set Union) is a data structure used to keep track of
//   elements partitioned into disjoint (non-overlapping) sets.
// - It efficiently answers connectivity queries ("are two nodes in the same set?")
//   and supports merging sets.
//
// Optimizations used:
// 1. Path Compression → makes find() very fast (flattening the tree).
// 2. Union by Size → always attach smaller tree under bigger tree to keep tree shallow.
//
// Time Complexity: Amortized O(4α(N)) ≈ O(1) per operation (α = inverse Ackermann).
// Space Complexity: O(N) for parent[] and size[].
//----------------------------------------------------------------------------

class DisjointSet
{
private:
    vector<int> parent; // parent[i] = parent of node i
    vector<int> size;   // size[i] = number of nodes in the set rooted at i

    // ------------------------------------------------------------------------
    // Find with Path Compression
    // ------------------------------------------------------------------------
    // - Recursively finds the ultimate parent (root) of node u.
    // - While returning, compresses the path: directly connects u to root.
    // - This ensures very flat trees (near constant time queries).
    int findUltParent(int u)
    {
        if (parent[u] == u) // base case: u is the root of its set
            return u;
        // recursive step + path compression
        parent[u] = findUltParent(parent[u]);
        return parent[u];
    }

public:
    // ------------------------------------------------------------------------
    // Constructor: initialize DSU with n elements
    // ------------------------------------------------------------------------
    // Initially: each node is its own parent, and each set has size 1.
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i; // each node is root of itself initially
        }
    }

    // ------------------------------------------------------------------------
    // Check if two nodes are in the same set
    // ------------------------------------------------------------------------
    bool isSameSet(int u, int v)
    {
        return (findUltParent(u) == findUltParent(v));
    }

    // ------------------------------------------------------------------------
    // Union by Size
    // ------------------------------------------------------------------------
    // Algorithm:
    // 1. Find ultimate parents of u and v.
    // 2. If same parent → already in same set → no need to merge.
    // 3. Else, attach the smaller-sized tree under the bigger-sized tree.
    // 4. Update the size of the new root.
    void unionBySize(int u, int v)
    {
        int p_u = findUltParent(u);
        int p_v = findUltParent(v);

        if (p_u == p_v)
            return; // already in same set

        if (size[p_u] == size[p_v])
        {
            // attach p_u under p_v (arbitrary when sizes are equal)
            parent[p_u] = p_v;
            size[p_v] += size[p_u];
        }
        else if (size[p_u] < size[p_v])
        {
            // attach smaller set p_u under larger set p_v
            parent[p_u] = p_v;
            size[p_v] += size[p_u];
        }
        else
        {
            // attach smaller set p_v under larger set p_u
            parent[p_v] = p_u;
            size[p_u] += size[p_v];
        }
    }
};

//----------------------------------------------------------------------------
// Kruskal’s Algorithm for Minimum Spanning Tree (MST)
//----------------------------------------------------------------------------
// Intuition:
// - MST = spanning tree of graph with minimum total edge weight.
// - Kruskal’s Algorithm builds MST by:
//    1. Sorting all edges by weight.
//    2. Iterating over edges in increasing order.
//    3. Adding edge (u,v) if u and v are not already connected
//       (i.e., adding it won’t form a cycle).
//    4. Continue until MST has (V-1) edges.
//
// Implementation:
// - Uses DSU to efficiently check connectivity and merge components.
// - Returns total MST weight.
//
// Complexity:
// - Sorting edges: O(E log E)
// - Union-Find operations: O(E α(V)) ≈ O(E)
// - Overall: O(E log E)
//----------------------------------------------------------------------------

class Solution
{
public:
    int kruskalsMST(int V, vector<vector<int>> &edges)
    {
        vector<vector<int>> wt_edges; // will store edges as {weight, u, v}
        vector<pair<int, int>> MST;   // stores the chosen edges of MST
        int MST_wt = 0;               // total weight of MST
        DisjointSet DS(V);            // initialize DSU for V vertices

        // Step 1: Convert edges into {weight, u, v} format
        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            int wt = e[2];
            wt_edges.push_back({wt, u, v});
        }

        // Step 2: Sort edges by weight
        sort(wt_edges.begin(), wt_edges.end());

        // Step 3: Iterate over edges and build MST
        for (auto &e : wt_edges)
        {
            int wt = e[0];
            int u = e[1];
            int v = e[2];

            // If u and v are in different sets, add this edge to MST
            if (!DS.isSameSet(u, v))
            {
                DS.unionBySize(u, v);  // merge sets
                MST.push_back({u, v}); // include edge in MST
                MST_wt += wt;          // add weight
            }

            if (MST.size() == V - 1)
                break;
        }

        // Final: return weight of MST
        return MST_wt;
    }
};

// ============================================================================
//  Main Method (Driver)
// ============================================================================
int main()
{
    // Example graph: 4 vertices (0-based), 5 edges
    // Graph edges: {u, v, weight}
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}};

    int V = 4; // number of vertices
    Solution sol;

    cout << "Running Kruskal's MST Algorithm...\n\n";
    int mst_weight = sol.kruskalsMST(V, edges);

    cout << "\nTotal Weight of MST = " << mst_weight << "\n";

    return 0;
}