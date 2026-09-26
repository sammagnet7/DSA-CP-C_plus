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

1. Title: Minimum Spanning Tree | Kruskal's Algorithm

Links:
https://takeuforward.org/data-structure/kruskals-algorithm-minimum-spanning-tree-g-47/
https://www.youtube.com/watch?v=DMnDM_sxVig
https://takeuforward.org/plus/dsa/problems/find-the-mst-weight?tab=editorial
https://www.geeksforgeeks.org/problems/minimum-spanning-tree-kruskals-algorithm/1


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
// 1. Title: Kruskal's Algorithm - Minimum Spanning Tree
//-------------------------------------------------------------------------------

//============================================================================
// Data Structure — Disjoint Set Union (Union-Find)
//============================================================================
class DSU
{
    vector<int> parent, size;

    /**
     * @brief Recursively finds the ultimate root of a node with Path Compression.
     * Path compression flattens the tree, ensuring future queries take O(1) time.
     */
    int findPar(int i)
    {
        int p = parent[i];

        // Base case: If the node is its own boss, it is the ultimate root
        if (p == i)
        {
            return p;
        }

        // Path Compression: Recursively find the root and attach the current node directly to it
        return parent[i] = findPar(p);
    }

public:
    // Initialize with n + 1 to safely handle both 0-indexed and 1-indexed graphs
    DSU(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);

        for (int i = 0; i <= n; ++i)
        {
            parent[i] = i;
        }
    }

    // Checks if two nodes belong to the same connected component
    // Time taken: O(1)
    bool dfind(int u, int v)
    {
        int pU = findPar(u);
        int pV = findPar(v);

        return pU == pV;
    }

    // Merges two components using Union by Size
    // Time taken: O(1)
    void dunion(int u, int v)
    {
        int pU = findPar(u);
        int pV = findPar(v);

        // If they share the same root, they are already connected
        if (pU == pV)
        {
            return;
        }

        int sU = size[pU];
        int sV = size[pV];

        // Attach the smaller tree under the larger tree to keep the overall height minimal
        if (sU <= sV)
        {
            parent[pU] = pV;
            size[pV] += size[pU];
        }
        else
        {
            parent[pV] = pU;
            size[pU] += size[pV];
        }
    }
};

class Solution
{
public:
    //============================================================================
    // Approach — Kruskal's Algorithm (Minimum Spanning Tree)
    //============================================================================

    /**
     * @brief Calculates the total weight of the Minimum Spanning Tree (MST).
     *
     * Idea & Intuition:
     * - Kruskal's Algorithm builds the MST using an "Edge-First" Greedy approach.
     * - We evaluate every possible road (edge) in the entire graph, strictly from
     * cheapest to most expensive.
     * - We pick the cheapest edge. If building this road connects two cities that
     * don't already have a path between them, we build it!
     * - If they ARE already connected (detected via our DSU), building this road
     * would create a redundant cycle, so we throw the edge away.
     *
     * Time Complexity:
     * - O(E log E): Sorting the edges dominates the execution time. The DSU `find`
     * and `union` operations take nearly O(1) amortized time.
     *
     * Space Complexity:
     * - O(V): The DSU strictly requires O(V) space for its `parent` and `size` arrays.
     */
    int kruskalsMST(int V, vector<vector<int>> &edges)
    {

        // --- STEP 1: Sort all edges ascending by weight ---
        sort(edges.begin(), edges.end(), [](const auto &a, const auto &b)
             { return a[2] < b[2]; });

        // --- STEP 2: Initialize DSU and Trackers ---
        DSU ds(V);
        int sum = 0;
        int edgesCount = 0;

        // --- STEP 3: Greedy Edge Selection ---
        for (auto &e : edges)
        {

            int u = e[0];
            int v = e[1];
            int w = e[2];

            // CYCLE CHECK: If u and v have the same ultimate boss, an edge already exists
            if (ds.dfind(u, v))
            {
                continue;
            }

            // Connect the two components and add the cost
            ds.dunion(u, v);
            sum += w;

            // --- STEP 4: Senior-Level Optimization (Early Exit) ---
            // A valid MST on V vertices mathematically ALWAYS has exactly V - 1 edges.
            // Once we hit that number, the tree is complete, and we can stop looping!
            ++edgesCount;
            if (edgesCount == V - 1)
            {
                break;
            }
        }

        return sum;
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