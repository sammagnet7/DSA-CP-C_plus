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

1. Title: Shortest Path in Undirected Graph with weighted edges | Dijkstra's Algorithm

Links:
https://takeuforward.org/data-structure/dijkstras-algorithm-using-priority-queue-g-32/
https://takeuforward.org/data-structure/dijkstras-algorithm-using-set-g-33/
https://takeuforward.org/data-structure/g-34-dijkstras-algorithm-intuition-and-time-complexity-derivation/
https://www.youtube.com/watch?v=V6H1qAeB-l4&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=32
https://www.youtube.com/watch?v=PATgNiuTP20&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=33
https://www.youtube.com/watch?v=3dINsjyfooY&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=34
https://takeuforward.org/plus/dsa/problems/dijkstra's-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1

Similar problem:
    743. Network Delay Time: https://leetcode.com/problems/network-delay-time/description/ [with directed edges]



Problem statement:
Given an undirected, weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by 2d array edges[][], where edges[i]=[u, v, w] represents the edge between the nodes u and v having w edge weight.
You have to find the shortest distance of all the vertices from the source vertex src, and return an array of integers where the ith element denotes the shortest distance between ith node and source vertex src.

Note: The Graph is connected and doesn't contain any negative weight edge.

Examples:

    Input: V = 3, edges[][] = [[0, 1, 1], [1, 2, 3], [0, 2, 6]], src = 2
    Output: [4, 3, 0]

    Explanation:
    Shortest Paths:
    For 2 to 0 minimum distance will be 4. By following path 2 -> 1 -> 0
    For 2 to 1 minimum distance will be 3. By following path 2 -> 1
    For 2 to 2 minimum distance will be 0. By following path 2 -> 2
    Input: V = 5, edges[][] = [[0, 1, 4], [0, 2, 8], [1, 4, 6], [2, 3, 2], [3, 4, 10]], src = 0
    Output: [0, 4, 8, 10, 10]

    Explanation:
    Shortest Paths:
    For 0 to 1 minimum distance will be 4. By following path 0 -> 1
    For 0 to 2 minimum distance will be 8. By following path 0 -> 2
    For 0 to 3 minimum distance will be 10. By following path 0 -> 2 -> 3
    For 0 to 4 minimum distance will be 10. By following path 0 -> 1 -> 4

Constraints:
    1 ≤ V ≤ 105
    1 ≤ E = edges.size() ≤ 105
    0 ≤ edges[i][j] ≤ 104
    0 ≤ src < V



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
// 1. Title: Shortest Path in Undirected Graph with unit distance: G-28
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /**********************************************************************************************
    Approach 1: Using Simple Queue (BFS-like approach)

    🔹 How it works:
    - Initialize distance array with infinity (1e9) except source = 0.
    - Push the source node into a normal queue.
    - Pop from queue, relax adjacent nodes, if a better distance found, push that node back to queue.

    🔹 Why is this inefficient?
    - The queue does not prioritize the smallest distance node.
    - Even if a far-away node has a large distance, it may get processed before a node with a smaller distance.
    - This leads to **redundant relaxations** (similar to Bellman-Ford but without negative weights).

    🔹 Complexity:
    - Worst-case Time Complexity: O(V * E)
      (Because every time a distance improves, the node is re-pushed into the queue. In worst case,
       each edge can cause multiple updates)
    - Space Complexity: O(V) for distance array + O(V) for queue = O(V)

    🔹 Why does this still give correct results?
    - Eventually all shorter paths propagate, but in a brute-force way.

    🔹 Example graph where this is inefficient:
       V = 4, Edges:
           0 -> 1 (weight 1)
           0 -> 2 (weight 100)
           1 -> 2 (weight 1)
           2 -> 3 (weight 1)
       - If we use queue:
           0 processed → push (1) and (2 with 100)
           2 with 100 processed before updating it to 2 via node 1 → unnecessary work

    **********************************************************************************************/
    vector<int> dijkstraUsingQueue(int V, vector<vector<int>> &edges, int src)
    {

        // Build adjacency list
        vector<vector<pair<int, int>>> adjL(V);
        for (auto e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(V, 1e9);
        dist[src] = 0;

        queue<int> q;
        q.push(src);

        while (!q.empty())
        {
            int curN = q.front();
            int curDist = dist[curN];
            q.pop();

            for (auto adj : adjL[curN])
            {
                int adjN = adj.first;
                int adjDist = adj.second;

                int newDist = curDist + adjDist;
                if (newDist < dist[adjN])
                {
                    dist[adjN] = newDist;
                    q.push(adjN); // No prioritization → inefficient
                }
            }
        }

        for (int &d : dist)
            if (d == 1e9)
                d = -1;
        return dist;
    }

    /**********************************************************************************************
    Approach 2: Using Min-Heap (Priority Queue)

    🔹 Why Min-Heap is used?
    - Always picks the node with the **smallest tentative distance** first.
    - Avoids unnecessary exploration of far-away nodes early.

    🔹 How it works:
    - Use priority_queue with pairs {distance, node} (min-heap).
    - Pop the smallest distance node and relax its neighbors.
    - If a better distance is found, push it into the priority queue.

    🔹 Complexity:
    - Each insertion and extraction in PQ → O(log V)
    - For all V vertices and E edges:
      Time Complexity = O((V + E) * log V)
      - V times pop from PQ → O(V log V)
      - Each edge relaxation involves pushing into PQ → O(E log V)
    - Space Complexity: O(V) for distance array + O(V) for PQ = O(V)

    🔹 Why is this better than Queue?
    - Processes nodes in increasing order of distance → fewer relaxations.

    🔹 Example where this is much better than Queue:
       Same as previous example:
           0 -> 1 (1)
           0 -> 2 (100)
           1 -> 2 (1)
           2 -> 3 (1)
       - Min-Heap processes 1 before 2 (with 100), updates 2 to distance 2 early → efficient.

    **********************************************************************************************/
    vector<int> dijkstraUsingMinHeap(int V, vector<vector<int>> &edges, int src)
    {

        vector<vector<pair<int, int>>> adjL(V);
        for (auto e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(V, 1e9);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty())
        {
            auto [curDist, curN] = pq.top();
            pq.pop();

            if (curDist > dist[curN])
                continue; // Skip outdated entries

            for (auto adj : adjL[curN])
            {
                int adjN = adj.first;
                int adjDist = adj.second;

                int newDist = curDist + adjDist;
                if (newDist < dist[adjN])
                {
                    dist[adjN] = newDist;
                    pq.push({newDist, adjN});
                }
            }
        }

        for (int &d : dist)
            if (d == 1e9)
                d = -1;
        return dist;
    }

    /**********************************************************************************************
    Approach 3: Using Set [OPTIMAL]

    🔹 Why use a Set instead of Min-Heap?
    - In Min-Heap, you cannot efficiently remove an outdated node (old distance).
      → You keep multiple entries of the same node with different distances.
      → This wastes time popping unnecessary elements.
    - A set (ordered) allows erasing the old pair before inserting the new one.

    🔹 How it works:
    - Use set<pair<int,node>> where it remains sorted by distance.
    - When a better distance is found:
        If old distance exists, erase it before inserting new one.

    🔹 Complexity:
    - Each insertion, deletion, and smallest element retrieval in set → O(log V)
    - For all V vertices and E edges:
      Time Complexity = O((V + E) * log V)
      - Similar to Min-Heap, but fewer redundant operations because outdated entries are removed.
    - Space Complexity: O(V) for distance array + O(V) for set = O(V)

    🔹 Why is this better than Min-Heap?
    - Handles decrease-key operation properly by erasing old value.
    - Avoids processing outdated nodes.

    🔹 Example where Set is better than Min-Heap:
       Graph with many edges and multiple relaxations for the same node:
           0 -> 1 (1)
           0 -> 2 (10)
           1 -> 2 (1)
           1 -> 3 (50)
           2 -> 3 (1)
       - Min-Heap pushes old values of node 2 and 3 multiple times → extra pops.
       - Set erases old values → more efficient.

    **********************************************************************************************/
    vector<int> dijkstraUsingSet(int V, vector<vector<int>> &edges, int src)
    {

        vector<vector<pair<int, int>>> adjL(V);
        for (auto e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(V, 1e9);
        dist[src] = 0;

        set<pair<int, int>> st;
        st.insert({0, src});

        while (!st.empty())
        {
            auto [curDist, curN] = *st.begin();
            st.erase(st.begin());

            for (auto adj : adjL[curN])
            {
                int adjN = adj.first;
                int adjDist = adj.second;

                int newDist = curDist + adjDist;
                if (newDist < dist[adjN])
                {
                    if (dist[adjN] != 1e9)
                    {
                        st.erase({dist[adjN], adjN});
                    }
                    dist[adjN] = newDist;
                    st.insert({newDist, adjN});
                }
            }
        }

        for (int &d : dist)
            if (d == 1e9)
                d = -1;
        return dist;
    }
};

/**********************************************************************************************
Comparison Summary:

1️⃣ Queue-based:
    - Time: O(V * E)
    - Space: O(V)
    - Works but very inefficient (acts like brute force)

2️⃣ Min-Heap-based (Priority Queue):
    - Time: O((V + E) * log V)
    - Space: O(V)
    - Efficient, standard implementation of Dijkstra

3️⃣ Set-based:
    - Time: O((V + E) * log V)
    - Space: O(V)
    - Slightly better than Min-Heap in practice (fewer redundant extractions)

**********************************************************************************************/

int main()
{
    Solution sol;

    int V = 4;
    vector<vector<int>> edges = {
        {0, 1, 1}, {0, 2, 100}, {1, 2, 1}, {2, 3, 1}};

    int src = 0;

    cout << "Using Queue: ";
    for (int d : sol.dijkstraUsingQueue(V, edges, src))
        cout << d << " ";
    cout << "\n";

    cout << "Using Min-Heap: ";
    for (int d : sol.dijkstraUsingMinHeap(V, edges, src))
        cout << d << " ";
    cout << "\n";

    cout << "Using Set: ";
    for (int d : sol.dijkstraUsingSet(V, edges, src))
        cout << d << " ";
    cout << "\n";

    return 0;
}
