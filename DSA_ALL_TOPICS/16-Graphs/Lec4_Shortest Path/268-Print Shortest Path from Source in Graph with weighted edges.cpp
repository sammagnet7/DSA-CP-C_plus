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

1. Title: Print Shortest Path from Source in Graph with weighted edges - Dijkstra's Algorithm


Links:
https://takeuforward.org/data-structure/g-35-print-shortest-path-dijkstras-algorithm/?utm_source=chatgpt.com
https://www.youtube.com/watch?v=rp1SMw7HSO8&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=36
https://takeuforward.org/plus/dsa/problems/print-shortest-path-?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1?utm_source=chatgpt.com


Problem statement:
You are given a weighted undirected graph having n vertices numbered from 1 to n and m edges along with their weights. Find the shortest weight path between the vertex 1 and the vertex n,  if there exists a path, and return a list of integers whose first element is the weight of the path, and the rest consist of the nodes on that path. If no path exists, then return a list containing a single element -1.
The input list of edges is as follows - {a, b, w}, denoting there is an edge between a and b, and w is the weight of that edge.


Examples :
    Input: n = 5, m= 6, edges = [[1, 2, 2], [2, 5, 5], [2, 3, 4], [1, 4, 1], [4, 3, 3], [3, 5, 1]]
    Output: 5
    Explanation: Shortest path from 1 to n is by the path 1 4 3 5 whose weight is 5.

    Input: n = 2, m= 1, edges = [[1, 2, 2]]
    Output: 2
    Explanation: Shortest path from 1 to 2 is by the path 1 2 whose weight is 2.

    Input: n = 2, m= 0, edges = [ ]
    Output: -1
    Explanation: Since there are no edges, so no answer is possible.

Expected Time Complexity: O(m* log(n))
Expected Space Complexity: O(n+m)

Constraint:
    2 <= n <= 10^6
    0 <= m <= 10^6
    1 <= a, b <= n
    1 <= w <= 10^5




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
// 1. Title: Print Shortest Path from Source to Destination node
//-------------------------------------------------------------------------------

class Solution
{
public:
    //============================================================================
    // Approach 1 — Dijkstra's Algorithm + Parent Tracking (Path Reconstruction)
    //============================================================================

    /**
     * @brief Finds the shortest path and its total cost from node 1 to node n.
     *
     * Intuition:
     * - Standard Dijkstra's algorithm finds the shortest *distance* to a node, but it
     *   doesn't remember *how* it got there.
     * - To reconstruct the path, we use a `par` (parent) array. Every time we find a
     *   shorter path to a neighbor `v` coming from node `u`, we record `par[v] = u`.
     * - Once we reach the destination `n`, we can just follow the parent pointers
     *   backwards all the way to the source!
     *
     * Understanding:
     * - Example: 1 -> 2 (cost 2), 2 -> 4 (cost 3).
     *   When relaxing node 2, `par[2] = 1`. When relaxing node 4, `par[4] = 2`.
     *   To rebuild the path from 4: `cur = 4`, then `cur = par[4] (2)`, then `cur = par[2] (1)`.
     *   The reversed path is [1, 2, 4].
     *
     * Approach:
     * 1. Graph Construction:
     *    - Build a 1-indexed undirected Adjacency List.
     * 2. Dijkstra's Setup:
     *    - `dist` array initialized to `1e9`. `dist[1] = 0`.
     *    - `par` array initialized to `-1`.
     *    - Push `{0, 1}` (distance 0, node 1) into the Min-Heap.
     * 3. Relaxation Loop:
     *    - Extract `{curW, curN}` from the priority queue.
     *    - Skip stale nodes (`if (dist[curN] < curW) continue;`).
     *    - Relax neighbors. If a faster path is found:
     *      a) Update `dist[adjN]`.
     *      b) Push the new path to the queue.
     *      c) RECORD PARENT: `par[adjN] = curN;`
     * 4. Path Backtracking:
     *    - If `dist[n] == 1e9`, it's unreachable, return `{-1}`.
     *    - Start at `n` and backtrack using the `par` array until you hit the source.
     *    - Append the total weight (`dist[n]`) to the end.
     *    - Reverse the entire array to get the required format: [weight, 1, ..., n].
     *
     * Time Complexity:
     * - O(E log V) for standard Dijkstra. Backtracking the path takes O(V) time.
     *   Overall Time: O(E log V).
     *
     * Space Complexity:
     * - O(V + E) for the Adjacency List + O(V) for the Min-Heap, `dist`, and `par` arrays.
     */
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {

        // --- STEP 1: Build the Adjacency List (1-Indexed) ---
        vector<vector<pair<int, int>>> adjL(n + 1);

        for (const auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            adjL[u].push_back({v, w});
            adjL[v].push_back({u, w}); // Added undirected edge
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(n + 1, 1e9);
        vector<int> par(n + 1, -1);

        // --- STEP 2: Initialize Start Node ---
        pq.push({0, 1});
        dist[1] = 0;

        // --- STEP 3: Dijkstra's Relaxation Loop ---
        while (!pq.empty())
        {

            auto [curW, curN] = pq.top();
            pq.pop();

            // Lazy Deletion
            if (dist[curN] < curW)
            {
                continue;
            }

            // FIX: Iterate over adjL[curN], not adjL[curW]!
            for (const auto &[adjN, adjW] : adjL[curN])
            {

                int newW = curW + adjW;

                if (newW < dist[adjN])
                {
                    dist[adjN] = newW;
                    pq.push({newW, adjN});

                    // Track the breadcrumb
                    par[adjN] = curN;
                }
            }
        }

        // --- STEP 4: Path Reconstruction ---
        // If the destination is unreachable
        if (dist[n] == 1e9)
        {
            return {-1};
        }

        vector<int> ans;
        int cur = n;

        // Backtrack from destination to source
        while (cur != -1)
        {
            ans.push_back(cur);
            cur = par[cur];
        }

        // The problem expects the total weight to be the first element
        // The total weight from 1 to n is exactly dist[n]
        ans.push_back(dist[n]);

        // Reverse to get [weight, 1, node_a, node_b, ..., n]
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main()
{
    return 0;
}