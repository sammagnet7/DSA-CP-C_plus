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

1. Title: Disjoint Set | Union by Rank | Union by Size | Path Compression: G-46

Links:
https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/
youtube.com/watch?v=aBxjDBC4M1U&feature=youtu.be
https://takeuforward.org/plus/dsa/problems/disjoint-set-?tab=editorial



Problem statement:
    Given two components of an undirected graph, determine if node 1 and node 5 belong to the same component.

Approach:
    To solve this problem, Depth-First Search (DFS) or Breadth-First Search (BFS) traversal techniques can be employed.
    By traversing the graph components, it is evident that node 1 and node 5 are in different components.
    This brute force approach has a time complexity of O(N+E) where N is the number of nodes and E is the number of edges.
    However, using a Disjoint Set data structure, this problem can be solved in constant time.

    The Disjoint Set data structure is particularly useful for dynamic graphs.
    Dynamic Graph: A dynamic graph refers to a graph that continuously changes its configuration.

Functionalities of Disjoint Set Data Structure:
    The Disjoint Set data structure provides two primary functionalities:
        Finding the parent(ultimate parent) of a particular node.
        Union operation (which adds an edge between two nodes):
            Union by Rank
            Union by Size
    Terminologies:
        Ultimate Parent: The parent of a node refers to the node right above that particular node.
        The ultimate parent refers to the topmost node or the root node of that component.
        Rank: The rank of a node refers to the distance (the number of nodes including the leaf node) between the furthest leaf node and the current node.
                Rank includes all nodes beneath the current node.




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
//--------------------------------------------------------------------------------
//  Title: Disjoint Set (Union-Find)
//  Variants: Union by Rank | Union by Size | Path Compression
//  Reference: G-46 (Striver’s Graph Series)
//--------------------------------------------------------------------------------
//
// Intuition:
// A Disjoint Set (DSU/Union-Find) is a data structure to efficiently handle
// dynamic connectivity queries: "Are two nodes in the same connected component?"
// It supports two main operations:
//   1. find(u): Find representative (ultimate parent) of the set containing u.
//   2. union(u, v): Merge the sets containing u and v.
//
// Optimizations:
// - Path Compression: Flattens the structure of the tree, so future queries
//   are faster (almost O(1)).
// - Union by Rank / Union by Size: Ensures the smaller tree is attached to
//   the larger tree to prevent height growth.
//
// Time Complexity: Nearly O(1) (amortized) per operation using α(n) inverse Ackermann.
// Space Complexity: O(N) for parent[], rank[], size[].
//
//--------------------------------------------------------------------------------

class DisjointSet
{
    vector<int> parent; // parent[i] = parent of node i
    vector<int> rank;   // rank[i] = approx. tree height of set i (used in union by rank)
    vector<int> size;   // size[i] = size of set rooted at i (used in union by size)

    // ----------------------------------------------------------------------
    // Find operation with path compression
    // ----------------------------------------------------------------------
    // Algorithm:
    // - If u is its own parent, return u (ultimate parent).
    // - Else, recursively find parent and compress the path by directly
    //   linking u to its ultimate parent.
    //
    // Effect: Flattens the tree, making future finds much faster.
    //
    int findUltimateParent(int u)
    {
        if (u == parent[u]) // Base case: u is root
            return u;

        // Recursive call + path compression
        return parent[u] = findUltimateParent(parent[u]);
    }

public:
    // ----------------------------------------------------------------------
    // Constructor: initialize DSU with n nodes
    // ----------------------------------------------------------------------
    // parent[i] = i initially (each node is its own set)
    // rank[i] = 0 (all trees are single nodes initially)
    // size[i] = 1 (each set has 1 element initially)
    //
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);

        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // ----------------------------------------------------------------------
    // Check if two nodes belong to the same set
    // ----------------------------------------------------------------------
    bool find(int u, int v)
    {
        return (findUltimateParent(u) == findUltimateParent(v));
    }

    // ----------------------------------------------------------------------
    // Union by Rank
    // ----------------------------------------------------------------------
    // Algorithm:
    // 1. Find ultimate parents of u and v.
    // 2. If same parent → already connected.
    // 3. Else attach smaller rank tree under larger rank tree.
    // 4. If ranks are equal, attach arbitrarily and increase rank by 1.
    //
    void unionByRank(int u, int v)
    {
        int p_u = findUltimateParent(u);
        int p_v = findUltimateParent(v);

        if (p_u == p_v) // Already in same set
            return;

        if (rank[p_u] == rank[p_v])
        {
            parent[p_u] = p_v; // Attach u’s tree under v
            rank[p_v]++;       // Increase rank as height grew
        }
        else if (rank[p_u] < rank[p_v])
        {
            parent[p_u] = p_v; // Attach smaller rank tree under bigger
        }
        else
        {
            parent[p_v] = p_u;
        }
    }

    // ----------------------------------------------------------------------
    // Union by Size
    // ----------------------------------------------------------------------
    // Algorithm:
    // 1. Find ultimate parents of u and v.
    // 2. If same parent → already connected.
    // 3. Else attach smaller sized tree under bigger sized tree.
    // 4. Update the size of new root accordingly.
    //
    void unionBySize(int u, int v)
    {
        int p_u = findUltimateParent(u);
        int p_v = findUltimateParent(v);

        if (p_u == p_v) // Already in same set
            return;

        if (size[p_u] == size[p_v])
        {
            parent[p_u] = p_v;      // Attach u under v
            size[p_v] += size[p_u]; // Update size of v’s set
        }
        else if (size[p_u] < size[p_v])
        {
            parent[p_u] = p_v;
            size[p_v] += size[p_u];
        }
        else
        {
            parent[p_v] = p_u;
            size[p_u] += size[p_v];
        }
    }
};

// ----------------------------------------------------------------------
// Example usage with Union by Rank
// ----------------------------------------------------------------------
// int main()
// {
//     DisjointSet ds(7);

//     ds.unionByRank(1, 2); // Connect 1-2
//     ds.unionByRank(2, 3); // Connect 2-3
//     ds.unionByRank(4, 5); // Connect 4-5
//     ds.unionByRank(6, 7); // Connect 6-7
//     ds.unionByRank(5, 6); // Connect 5-6

//     // Check connectivity between 3 and 7
//     if (ds.find(3, 7))
//         cout << "They belong to the same components.\n";
//     else
//         cout << "They do not belong to the same components.\n";

//     ds.unionByRank(3, 7); // Connect 3-7

//     if (ds.find(3, 7))
//         cout << "They belong to the same components.\n";
//     else
//         cout << "They do not belong to the same components.\n";

//     return 0;
// }

// ----------------------------------------------------------------------
// Example usage with Union by Size
// ----------------------------------------------------------------------
int main()
{
    DisjointSet ds(7);

    ds.unionBySize(1, 2); // Connect 1-2
    ds.unionBySize(2, 3); // Connect 2-3
    ds.unionBySize(4, 5); // Connect 4-5
    ds.unionBySize(6, 7); // Connect 6-7
    ds.unionBySize(5, 6); // Connect 5-6

    // Check connectivity between 3 and 7
    if (ds.find(3, 7))
        cout << "They belong to the same components.\n";
    else
        cout << "They do not belong to the same components.\n";

    ds.unionBySize(3, 7); // Connect 3-7

    if (ds.find(3, 7))
        cout << "They belong to the same components.\n";
    else
        cout << "They do not belong to the same components.\n";

    return 0;
}
