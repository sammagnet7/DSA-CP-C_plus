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

1. Title: G-35. Print Shortest Path - Dijkstra's Algorithm


Links:
https://takeuforward.org/data-structure/g-35-print-shortest-path-dijkstras-algorithm/?utm_source=chatgpt.com
https://www.youtube.com/watch?v=rp1SMw7HSO8&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=36
https://takeuforward.org/plus/dsa/problems/print-shortest-path-?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1?utm_source=chatgpt.com


Problem statement:
You are given a weighted undirected graph having n vertices numbered from 1 to n and m edges along with their weights. Find the shortest weight path between the vertex 1 and the vertex n,  if there exists a path, and return a list of integers whose first element is the weight of the path, and the rest consist of the nodes on that path. If no path exists, then return a list containing a single element -1.
The input list of edges is as follows - {a, b, w}, denoting there is an edge between a and b, and w is the weight of that edge.

Note: The driver code here will first check if the weight of the path returned is equal to the sum of the weights along the nodes on that path, if equal it will output the weight of the path, else -2. In case the list contains only a single element (-1) it will simply output -1.

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
    2 <= n <= 106
    0 <= m <= 106
    1 <= a, b <= n
    1 <= w <= 105




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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: G-35. Print Shortest Path - Dijkstra's Algorithm
    //-------------------------------------------------------------------------------

    /*
    Problem: Find the shortest path from node 1 to node n in an undirected weighted graph.
    Input:
        n → number of nodes
        m → number of edges
        edges → list of edges in the form [u, v, weight]
    Output:
        A vector containing:
            -1 if there is no path from node 1 to node n
            OR
            The sequence of nodes representing the shortest path from 1 → n,
            followed by the total distance at the end.

    Approach:
    - Use Dijkstra's algorithm with a set (balanced BST) for efficient decrease-key operation.
    - Maintain a `parent` array to reconstruct the path after shortest distances are computed.

    Complexity:
    - Time: O((V + E) * log V) due to set operations (insert, erase, extract-min)
    - Space: O(V + E) for adjacency list, O(V) for distance and parent arrays, O(V) for set
    */

    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {

        int V = n + 1; // +1 because nodes are 1-indexed
        int src = 1;   // Start node is 1
        int t = n;     // Target node is n

        // -----------------------------
        // Step 1: Build adjacency list
        // -----------------------------
        vector<vector<pair<int, int>>> adjL(V); // Each node stores {neighbor, weight}

        for (auto e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]}); // u → v
            adjL[e[1]].push_back({e[0], e[2]}); // v → u (because graph is undirected)
        }

        // -----------------------------------------
        // Step 2: Initialize distance and parent
        // -----------------------------------------
        vector<int> dist(V, 1e9); // Distance array initialized to infinity
        dist[src] = 0;            // Distance to source = 0

        vector<int> parent(V, -1); // To reconstruct path
        parent[src] = -1;          // Source has no parent

        // ------------------------------------------------
        // Step 3: Use Set to simulate a min-priority queue
        // ------------------------------------------------
        set<pair<int, int>> st; // Stores {distance, node}, sorted by distance
        st.insert({0, src});

        // --------------------------
        // Step 4: Dijkstra's Loop
        // --------------------------
        while (!st.empty())
        {
            // Extract node with smallest distance
            auto [curDist, curN] = *st.begin();
            st.erase(st.begin());

            // Relax all adjacent nodes
            for (auto adj : adjL[curN])
            {
                int adjN = adj.first;     // Neighbor node
                int adjDist = adj.second; // Edge weight

                int newDist = curDist + adjDist;

                // If a shorter path to adjN is found
                if (newDist < dist[adjN])
                {
                    // Remove the old entry from set (if exists)
                    if (dist[adjN] != 1e9)
                    {
                        st.erase({dist[adjN], adjN});
                    }

                    // Update distance and parent
                    dist[adjN] = newDist;
                    parent[adjN] = curN;

                    // Insert new distance into set
                    st.insert({newDist, adjN});
                }
            }
        }

        // -----------------------------
        // Step 5: Build the result path
        // -----------------------------
        vector<int> ans;

        if (dist[t] == 1e9)
        {
            // If target node is unreachable
            ans.push_back(-1);
        }
        else
        {
            // Reconstruct path from t to src using parent array
            int p = t;
            while (p != -1)
            {
                ans.push_back(p);
                p = parent[p];
            }

            // Append total distance at the end
            ans.push_back(dist[t]);

            // Reverse path to get correct order (src → t)
            reverse(ans.begin(), ans.end());
        }

        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
