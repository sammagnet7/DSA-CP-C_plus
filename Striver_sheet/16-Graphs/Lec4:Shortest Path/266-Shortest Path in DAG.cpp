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

1. Title: Shortest Path in Directed Acyclic Graph Topological Sort: G-27


Links:
https://takeuforward.org/data-structure/shortest-path-in-directed-acyclic-graph-topological-sort-g-27/
https://www.youtube.com/watch?v=ZUFQfFaU-8U&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=28
https://takeuforward.org/plus/dsa/problems/shortest-path-in-dag?tab=editorial
https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/0
https://www.naukri.com/code360/problems/shortest-path-in-dag_8381897?leftPanelTabValue=PROBLEM


Problem statement:
Given a Directed Acyclic Graph of V vertices from 0 to n-1 and a 2D Integer array(or vector) edges[ ][ ] of length E, where there is a directed edge from edge[i][0] to edge[i][1] with a distance of edge[i][2] for all i.
Find the shortest path from src(0) vertex to all the vertices and if it is impossible to reach any vertex, then return -1 for that vertex.

Examples :
    Input: V = 4, E = 2, edges = [[0,1,2], [0,2,1]]
    Output: [0, 2, 1, -1]
    Explanation: Shortest path from 0 to 1 is 0->1 with edge weight 2. Shortest path from 0 to 2 is 0->2 with edge weight 1. There is no way we can reach 3, so it's -1 for 3.

    Input: V = 6, E = 7, edges = [[0,1,2], [0,4,1], [4,5,4], [4,2,2], [1,2,3], [2,3,6], [5,3,1]]
    Output: [0, 2, 3, 6, 1, 5]
    Explanation: Shortest path from 0 to 1 is 0->1 with edge weight 2. Shortest path from 0 to 2 is 0->4->2 with edge weight 1+2=3. Shortest path from 0 to 3 is 0->4->5->3 with edge weight 1+4+1=6. Shortest path from 0 to 4 is 0->4 with edge weight 1.Shortest path from 0 to 5 is 0->4->5 with edge weight 1+4=5.

Constraint:
    1 <= V <= 100
    1 <= E <= min((N*(N-1))/2,4000)
    0 <= edgesi,0, edgesi,1 < n
    0 <= edgei,2 <=105



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
    // 1. Title: Shortest Path in Directed Acyclic Graph Topological Sort: G-27
    //-------------------------------------------------------------------------------

    /**
     * @brief Compute the shortest path in a DAG using a BFS-like approach.
     *
     * Intuition:
     * - Start from the source node (0), traverse using a queue like BFS.
     * - Update the distances of adjacent nodes whenever we find a shorter path.
     *
     * Steps:
     * 1. Create an adjacency list where each node stores (neighbor, edge weight).
     * 2. Use a queue starting from node 0.
     * 3. For every node popped from the queue, relax its adjacent nodes (update distance if smaller).
     * 4. Push the neighbor back to the queue if its distance gets updated.
     *
     * Time Complexity: O(V + E) in best case, but can be **O(V * E)** in worst case.
     * - Because the same node can be added multiple times if distances keep updating.
     *
     * Space Complexity: O(V + E) for adjacency list + O(V) for queue + O(V) for distance array.
     *
     * **Why it's not efficient:**
     * - Nodes are revisited multiple times since we don?t guarantee that we process nodes after all their dependencies.
     * - This makes it similar to Bellman-Ford behavior in worst cases (though still better in DAG because no negative cycle).
     */

    // vector<int> shortestPath(int V, int m, vector<vector<int>> &edges)
    // {
    //     // Build adjacency list where each entry stores {neighbor, weight}
    //     vector<vector<pair<int, int>>> adjL(V);
    //     for (auto e : edges)
    //     {
    //         adjL[e[0]].push_back({e[1], e[2]});
    //     }

    //     // Distance array initialized with large value (1e9 means unreachable)
    //     vector<int> vist_dist(V, 1e9);

    //     // Start BFS from source node 0
    //     queue<int> q;
    //     q.push(0);
    //     vist_dist[0] = 0;

    //     // BFS-like processing
    //     while (!q.empty())
    //     {
    //         int cur = q.front();
    //         int curDist = vist_dist[cur];
    //         q.pop();

    //         // Relax all adjacent nodes
    //         for (auto adj : adjL[cur])
    //         {
    //             int adjN = adj.first;     // neighbor
    //             int adjDist = adj.second; // edge weight

    //             int newAdjDist = curDist + adjDist;

    //             // If we find a shorter path, update and push neighbor to queue
    //             if (newAdjDist < vist_dist[adjN])
    //             {
    //                 vist_dist[adjN] = newAdjDist;
    //                 q.push(adjN);
    //             }
    //         }
    //     }

    //     // Convert unreachable nodes to -1
    //     vector<int> ans;
    //     for (int i : vist_dist)
    //     {
    //         ans.push_back(i == 1e9 ? -1 : i);
    //     }

    //     return ans;
    // }

    /**
     * @brief Compute the shortest path in a DAG using Topological Sort (Efficient approach).
     *
     * Intuition:
     * - In a DAG, the shortest path problem can be solved in **linear time** using topological order.
     * - Once we have the topological order, we process nodes in that order and relax their adjacent edges.
     * - This guarantees that when we process a node, we have already computed the shortest path for all its predecessors.
     *
     * Steps:
     * 1. Build adjacency list and indegree array.
     * 2. Perform topological sort using Kahn?s algorithm.
     * 3. Initialize dist array with infinity except source node = 0.
     * 4. Traverse nodes in topological order, and relax edges.
     * 5. Convert unreachable nodes (still 1e9) to -1.
     *
     * Time Complexity: O(V + E)
     * - Topological sort = O(V + E)
     * - Relaxation = O(E)
     *
     * Space Complexity: O(V + E)
     *
     * **Why is this better than Approach 1?**
     * - Each edge is processed only once (in topological order).
     * - No repeated updates like in Approach 1 because DAG + topological sort ensures we handle dependencies first.
     * - Guaranteed linear time complexity.
     */

    vector<int> shortestPath(int V, int m, vector<vector<int>> &edges)
    {
        // Step 1: Build adjacency list and indegree array
        vector<vector<pair<int, int>>> adjL(V);
        vector<int> indegree(V, 0);
        for (auto e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            indegree[e[1]]++;
        }

        // Step 2: Perform topological sort using Kahn's Algorithm
        queue<int> q;
        vector<int> topo;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
                topo.push_back(i);
            }
        }

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (auto adj : adjL[cur])
            {
                indegree[adj.first]--;
                if (indegree[adj.first] == 0)
                {
                    q.push(adj.first);
                    topo.push_back(adj.first);
                }
            }
        }

        // Step 3: Initialize distance array with infinity, source node = 0
        vector<int> dist(V, 1e9);
        int sourceNode = 0;
        dist[sourceNode] = 0;

        // Step 4: Relax edges in topological order
        for (int i = 0; i < topo.size(); i++)
        {
            int curNode = topo[i];
            if (dist[curNode] == 1e9)
                continue; // If current node is unreachable, skip
            int curNodeDist = dist[curNode];
            for (auto adj : adjL[curNode])
            {
                int adjN = adj.first;
                int adjDist = adj.second;
                if (curNodeDist + adjDist < dist[adjN])
                {
                    dist[adjN] = curNodeDist + adjDist;
                }
            }
        }

        // Step 5: Convert unreachable nodes to -1
        for (int i = 0; i < V; i++)
        {
            if (dist[i] == 1e9)
                dist[i] = -1;
        }

        return dist;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
