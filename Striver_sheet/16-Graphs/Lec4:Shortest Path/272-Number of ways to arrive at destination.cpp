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

1. Title: G-40: Number of Ways to Arrive at Destination

Links:
https://takeuforward.org/data-structure/g-40-number-of-ways-to-arrive-at-destination/
https://www.youtube.com/watch?v=_-0mx0SmYxA
https://takeuforward.org/plus/dsa/problems/number-of-ways-to-arrive-at-destination?tab=editorial
https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/


Problem statement:
You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.

Examples:
    Example 1:
    Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
    Output: 4
    Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
    The four ways to get there in 7 minutes are:
    - 0 ➝ 6
    - 0 ➝ 4 ➝ 6
    - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
    - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

    Example 2:
    Input: n = 2, roads = [[1,0,10]]
    Output: 1
    Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.


Constraints:
    1 <= n <= 200
    n - 1 <= roads.length <= n * (n - 1) / 2
    roads[i].length == 3
    0 <= ui, vi <= n - 1
    1 <= timei <= 109
    ui != vi
    There is at most one road connecting any two intersections.
    You can reach any intersection from any other intersection.



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
// 1. Title: G-40: Number of Ways to Arrive at Destination
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /*
     * Method: countPaths
     * ------------------
     * This method finds the number of shortest paths from a source node (0) to a
     * destination node (n-1) in a weighted, undirected graph.
     *
     * **Intuition:**
     * A standard Dijkstra's algorithm finds the shortest distance, but here we need to count
     * all paths that have that same minimum distance. The core idea is to modify Dijkstra's
     * to keep track of two values for each node: the minimum distance found so far and the
     * number of ways to achieve that distance. We use a priority queue to always
     * process the node with the current shortest known distance, ensuring we explore
     * paths in an optimal order.
     *
     * **Algorithm:**
     * 1.  **Graph Representation**: An adjacency list `adj` stores the graph where
     * `adj[u]` contains pairs `{v, weight}` for all neighbors `v` of `u`.
     * 2.  **State Arrays**: Two arrays, `minDist` and `ways`, are used to track the
     * shortest distance and the number of ways to achieve it for each node.
     * They are initialized to infinity and zero, respectively.
     * 3.  **Priority Queue**: A min-priority queue stores pairs `{distance, node}` to
     * efficiently retrieve the node with the smallest distance.
     * 4.  **Dijkstra's Traversal**:
     * - The process starts by initializing the source node (0) with a distance of 0
     * and 1 way.
     * - The algorithm iterates, pulling the node with the minimum distance from the queue.
     * - For each neighbor `v` of the current node `u`, we check if a new path through `u`
     * is shorter than, or equal to, the current shortest path to `v`.
     * - If a shorter path is found, `minDist[v]` is updated, `ways[v]` is set to `ways[u]`,
     * and `v` is pushed onto the queue.
     * - If a path of equal length is found, `ways[v]` is incremented by `ways[u]`.
     * 5.  **Result**: The final count is the value stored in `ways[n-1]`.
     *
     * **Complexity:**
     * - **Time**: O((V + E) * logV), where V is the number of vertices and E is the number of edges.
     * This is the standard time complexity for Dijkstra's with a binary heap.
     * - **Space**: O(V + E) to store the graph, distances, ways, and the priority queue.
     */
    int countPaths(int n, vector<vector<int>> &roads)
    {
        long long mod = 1e9 + 7;

        // Adjacency list: node -> {adjN, dist}
        vector<vector<pair<int, long long>>> adj(n);
        for (const auto &road : roads)
        {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }

        // minDist[i] stores the minimum distance from source (0) to node i
        vector<long long> minDist(n, LLONG_MAX);
        // ways[i] stores the number of ways to reach node i with minDist[i]
        vector<long long> ways(n, 0);

        // Priority queue: {distance, node}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

        minDist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while (!pq.empty())
        {
            long long d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // Optimization to handle stale entries in the priority queue.
            // If we've found a shorter path to `u` since this entry was created, skip it.
            if (d > minDist[u])
            {
                continue;
            }

            for (const auto &neighbor : adj[u])
            {
                int v = neighbor.first;
                long long weight = neighbor.second;

                long long new_dist = d + weight;

                if (new_dist < minDist[v])
                {
                    // Found a shorter path to `v`.
                    minDist[v] = new_dist;
                    ways[v] = ways[u];
                    pq.push({new_dist, v});
                }
                else if (new_dist == minDist[v])
                {
                    // Found another path with the same minimum distance.
                    ways[v] = (ways[v] + ways[u]) % mod;
                }
            }
        }

        return ways[n - 1];
    }
};

int main()
{
    // Example 1:
    // n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
    int n1 = 7;
    vector<vector<int>> roads1 = {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}};
    Solution sol1;
    int result1 = sol1.countPaths(n1, roads1);
    cout << "Example 1 Output: " << result1 << endl; // Expected output: 4

    // Example 2:
    // n = 2, roads = [[1,0,10]]
    int n2 = 2;
    vector<vector<int>> roads2 = {{1, 0, 10}};
    Solution sol2;
    int result2 = sol2.countPaths(n2, roads2);
    cout << "Example 2 Output: " << result2 << endl; // Expected output: 1

    return 0;
}