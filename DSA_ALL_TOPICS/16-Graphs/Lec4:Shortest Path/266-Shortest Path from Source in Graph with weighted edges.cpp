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

1. Title: Shortest Path in Undirected Graph with weighted edges

Links:
https://takeuforward.org/data-structure/dijkstras-algorithm-using-priority-queue-g-32/
https://takeuforward.org/data-structure/dijkstras-algorithm-using-set-g-33/
https://takeuforward.org/data-structure/g-34-dijkstras-algorithm-intuition-and-time-complexity-derivation/
https://www.youtube.com/watch?v=V6H1qAeB-l4&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=32
https://www.youtube.com/watch?v=PATgNiuTP20&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=33
https://www.youtube.com/watch?v=3dINsjyfooY&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=34
https://takeuforward.org/plus/dsa/problems/dijkstra's-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1



Problem statement:
Given an undirected, weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by 2D array edges[][], where edges[i]=[u, v, w] represents the edge between the nodes u and v having w edge weight.
You have to find the shortest distance of all the vertices from the source vertex `src`, and return an array of integers where the i-th element denotes the shortest distance between i-th node and source vertex `src`.

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

2. Title: Shortest Path in Directed Graph with weighted edges 


Links:
https://leetcode.com/problems/network-delay-time/description/


Similar problem:
    https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/



Problem statement:
You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.


Examples:
    Example 1:
    Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
    Output: 2

    Example 2:
    Input: times = [[1,2,1]], n = 2, k = 1
    Output: 1

    Example 3:
    Input: times = [[1,2,1]], n = 2, k = 2
    Output: -1


Constraints:
    1 <= k <= n <= 100
    1 <= times.length <= 6000
    times[i].length == 3
    1 <= ui, vi <= n
    ui != vi
    0 <= wi <= 100
    All the pairs (ui, vi) are unique. (i.e., no multiple edges.)


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Shortest Path in Undirected Graph with weighted edges
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    //=================================================
    // Approach 1: Shortest Path using simple BFS [TLE]
    //=================================================
    /**********************************************************************************************
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
    vector<int> dijkstra_BFS(int V, vector<vector<int>> &edges, int src)
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

    //============================================================================
    // Approach 2 — Dijkstra's Algorithm (Min-Heap / Priority Queue) [RECOMMENDED]
    //============================================================================

    /**
     * @brief Finds the shortest paths from a source node to all other vertices in a weighted graph.
     *
     * Intuition:
     * - In a weighted graph, BFS fails because the shortest path in terms of *edges*
     *   might not be the shortest path in terms of *weight*.
     * - Dijkstra's Algorithm acts like a BFS that expands based on "cost" rather than "steps".
     * - By always exploring the node with the smallest tentative distance first (using a Min-Heap),
     *   we guarantee that the first time we fully process a node, we have found the absolute
     *   cheapest path to it.
     *
     * Understanding (Min-Heap vs. Standard Queue):
     * - Example: We have paths 0 -> 1 (cost 1), 0 -> 2 (cost 100), and 1 -> 2 (cost 1).
     * - A standard Queue would process 0 -> 2, set node 2's distance to 100, and aggressively
     *   queue all of node 2's neighbors based on that terrible distance.
     * - A Min-Heap processes node 1 first (cost 1). It then evaluates 1 -> 2 (total cost 2),
     *   updates node 2 to a distance of 2, and pushes that better path to the heap. The terrible
     *   path (100) is gracefully skipped later. This prevents massive cascades of redundant work!
     *
     * Approach:
     * 1. Graph Construction:
     *    - Build an Adjacency List where `adjL[u]` stores pairs of `{neighbor, edge_weight}`.
     * 2. Initialization:
     *    - Create a `dist` array initialized to infinity (`1e9`), setting `dist[src] = 0`.
     *    - Initialize a Min-Heap (Priority Queue) storing pairs of `{current_distance, node}`.
     * 3. Relaxation Loop:
     *    - Pop the node with the absolute minimum distance from the PQ.
     *    - STALE NODE CHECK: If the popped distance is strictly greater than `dist[curN]`,
     *      it means we already found a faster route to this node earlier. Skip it immediately!
     *    - Iterate through all neighbors. If `curDist + edgeWeight < dist[adjN]`, update
     *      the `dist` array and push the new `{newDist, adjN}` into the PQ.
     * 4. Post-Processing:
     *    - Convert any remaining `1e9` distances to `-1` to indicate unreachable nodes.
     *
     * Time Complexity:
     * - O(E log V): In the worst case, every edge gets pushed into the PQ. Extracting from
     *   the PQ takes O(log V). Therefore, E insertions/extractions take O(E log V).
     *
     * Space Complexity:
     * - O(V + E) for the Adjacency List + O(V) for the `dist` array + O(E) for the Priority Queue
     *   in the absolute worst-case scenario (a highly dense graph).
     */
    vector<int> dijkstraUsingMinHeap(int V, vector<vector<int>> &edges, int src)
    {

        // --- STEP 1: Build the Adjacency List ---
        // Using const auto& prevents expensive memory copies of the edge vectors
        vector<vector<pair<int, int>>> adjL(V);
        for (const auto &e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]}); // Undirected graph
        }

        // Initialize distances to "infinity"
        vector<int> dist(V, 1e9);

        // Min-Heap stores {distance, node} to automatically sort by smallest distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, src});
        dist[src] = 0;

        // --- STEP 2: Dijkstra's Relaxation Loop ---
        while (!pq.empty())
        {

            // C++17 Structured Binding to unpack the tuple cleanly!
            auto [curDist, curN] = pq.top();
            pq.pop();

            // LAZY DELETION / STALE ENTRY OPTIMIZATION:
            // If we already found a shorter path to curN, this queue entry is obsolete.
            if (curDist > dist[curN])
            {
                continue;
            }

            // Structured binding applied to the neighbor loop as well!
            for (const auto &[adjN, adjDist] : adjL[curN])
            {

                int newDist = curDist + adjDist;

                // Edge Relaxation
                if (newDist < dist[adjN])
                {
                    dist[adjN] = newDist;
                    pq.push({newDist, adjN});
                }
            }
        }

        // --- STEP 3: Post-Process Unreachable Nodes ---
        for (int &d : dist)
        {
            if (d == 1e9)
            {
                d = -1;
            }
        }

        return dist;
    }

    //============================================================================
    // Approach 3 — Dijkstra's Algorithm (Set / Simulated Decrease-Key) [OPTIMAL]
    //============================================================================

    /**
     * @brief Finds the shortest paths from a source node using a Set for optimal memory usage.
     *
     * Intuition:
     * - A Min-Heap (`priority_queue`) cannot efficiently delete or update an element inside of it.
     *   When we find a better path to a node, a Min-Heap forces us to push a duplicate, better
     *   entry. This results in the queue holding multiple outdated "stale" paths for the same node.
     * - A `std::set` is an ordered Binary Search Tree. It inherently sorts elements (acting like
     *   a Min-Heap), but it ALSO allows us to find and erase specific elements in O(log V) time!
     *
     * Understanding (Set vs. Min-Heap):
     * - Example: We have path 0 -> 2 (cost 100). Node 2 is in the Min-Heap as {100, 2}.
     *   Later, we find a faster path 0 -> 1 -> 2 (cost 2).
     *   * Min-Heap approach: Pushes {2, 2}. Queue now holds BOTH {2, 2} and {100, 2}.
     *   * Set approach: Erases {100, 2} and inserts {2, 2}. The Set remains perfectly lean!
     * - This "erase and re-insert" technique perfectly simulates the theoretical `decrease-key()`
     *   operation of Dijkstra's algorithm.
     *
     * Approach:
     * 1. Graph Construction:
     *    - Build the Adjacency List `adjL`.
     * 2. Initialization:
     *    - Create a `dist` array initialized to 1e9.
     *    - Initialize a `set<pair<int, int>>` to maintain the ordered queue of nodes.
     * 3. Relaxation Loop:
     *    - Extract the minimum element using `*st.begin()` and immediately erase it.
     *    - Iterate through all neighbors. If `curDist + adjDist < dist[adjN]`:
     *      a) DECREASE-KEY: If the neighbor was already visited (`dist[adjN] != 1e9`),
     *         find its old, worse distance in the Set and erase it to save space.
     *      b) Update `dist[adjN]` and insert the newly optimized `{newDist, adjN}` into the Set.
     * 4. Post-Processing:
     *    - Convert any unreachable `1e9` distances to `-1`.
     *
     * Time Complexity:
     * - O((V + E) * log V): Erasing and inserting into a balanced BST (Set) takes O(log V).
     *   Because we aggressively prune stale entries, we do slightly fewer operations than
     *   the Min-Heap in dense graphs, though the asymptotic time bound remains the same.
     *
     * Space Complexity:
     * - O(V + E) for the Adjacency List + O(V) for the `dist` array + strictly bounded O(V)
     *   for the Set. (Unlike the Min-Heap which can grow to O(E) due to duplicate entries!)
     */
    vector<int> dijkstraUsingSet(int V, vector<vector<int>> &edges, int src)
    {

        // --- STEP 1: Build the Adjacency List ---
        vector<vector<pair<int, int>>> adjL(V);
        for (const auto &e : edges)
        {
            adjL[e[0]].push_back({e[1], e[2]});
            adjL[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(V, 1e9);
        dist[src] = 0;

        // The Set automatically orders pairs by the first element (distance)
        set<pair<int, int>> st;
        st.insert({0, src});

        // --- STEP 2: Dijkstra's Relaxation Loop ---
        while (!st.empty())
        {

            // Extract the minimum element from the front of the Set
            auto [curDist, curN] = *st.begin();
            st.erase(st.begin()); // Remove it so we don't process it again

            // Structured binding to directly unpack neighbors
            for (const auto &[adjN, adjDist] : adjL[curN])
            {

                int newDist = curDist + adjDist;

                // Edge Relaxation
                if (newDist < dist[adjN])
                {

                    // --- SIMULATED DECREASE-KEY ---
                    // If this node already had a valid, but worse distance,
                    // erase that stale entry from the Set before it clogs the queue!
                    if (dist[adjN] != 1e9)
                    {
                        st.erase({dist[adjN], adjN});
                    }

                    // Update and insert the newly optimized path
                    dist[adjN] = newDist;
                    st.insert({newDist, adjN});
                }
            }
        }

        // --- STEP 3: Post-Process Unreachable Nodes ---
        for (int &d : dist)
        {
            if (d == 1e9)
            {
                d = -1;
            }
        }

        return dist;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Shortest Path in Directed Graph with weighted edges
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    //===============================================================================
    // Approach 1 — Dijkstra's Algorithm (Min-Heap / Priority Queue) [SAME AS BEFORE]
    //===============================================================================

    /**
     * @brief Finds the minimum time required for all nodes to receive a network signal.
     *
     * Intuition:
     * - The network signal travels simultaneously along all paths starting from node K.
     * - The time a specific node receives the signal is exactly the shortest weighted path
     *   from K to that node.
     * - Therefore, the time it takes for *all* nodes to receive the signal is simply the
     *   maximum of all those shortest paths. If any node remains unreachable, it's impossible.
     *
     * Understanding:
     * - Example: K -> A (takes 2s), K -> B (takes 5s). Both signals fire at the same time.
     *   A receives it at 2s, but the network as a whole isn't finished until B receives it
     *   at 5s. The answer is max(2, 5) = 5.
     * - 1-Based Indexing: The nodes are numbered 1 to n. We size our arrays to `n + 1`
     *   and simply ignore index 0 to make the mapping perfectly clean.
     *
     * Approach:
     * 1. Graph Construction:
     *    - Build a 1-indexed directed Adjacency List `adjL`.
     * 2. Dijkstra's Initialization:
     *    - Initialize a `dist` array to infinity (`1e9`) and set `dist[k] = 0`.
     *    - Push `{0, k}` into a Min-Heap.
     * 3. Relaxation Loop:
     *    - Extract by VALUE (`auto [dist, node]`) from the PQ before popping to avoid UB.
     *    - Skip stale entries using lazy deletion (`if (dist[curN] < curDist) continue;`).
     *    - Relax all neighbors. If a faster time is found, update `dist` and push to PQ.
     * 4. Post-Processing:
     *    - Iterate through nodes 1 to n. If any node is still `1e9`, return -1.
     *    - Otherwise, track and return the maximum distance found.
     *
     * Time Complexity:
     * - O(E log V): Dijkstra's standard time complexity where E is the number of edges
     *   (`times.size()`) and V is the number of vertices (`n`).
     *
     * Space Complexity:
     * - O(V + E) for the Adjacency List + O(V) for the `dist` array + O(E) for the Priority Queue.
     */
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {

        // --- STEP 1: Build the Adjacency List (1-Indexed) ---
        vector<vector<pair<int, int>>> adjL(n + 1);

        for (const auto &t : times)
        {
            int u = t[0], v = t[1], w = t[2];
            adjL[u].push_back({v, w}); // Directed edge
        }

        // Initialize distances to "infinity"
        vector<int> dist(n + 1, 1e9);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // --- STEP 2: Initialize Start Node ---
        dist[k] = 0;
        pq.push({0, k});

        // --- STEP 3: Dijkstra's Relaxation Loop ---
        while (!pq.empty())
        {

            // CRITICAL FIX: Extract by value to avoid a dangling reference after pq.pop()!
            auto [curDist, curN] = pq.top();
            pq.pop();

            // Lazy Deletion: Skip stale, unoptimized paths
            if (dist[curN] < curDist)
            {
                continue;
            }

            // Extract neighbors by const reference (safe, because adjL isn't being modified)
            for (const auto &[adjN, adjDist] : adjL[curN])
            {

                int newDist = curDist + adjDist;

                if (newDist < dist[adjN])
                {
                    dist[adjN] = newDist;
                    pq.push({newDist, adjN});
                }
            }
        }

        // --- STEP 4: Calculate Final Network Time ---
        int timeTaken = 0;

        for (int i = 1; i <= n; ++i)
        {

            // If any node is unreachable, the whole network fails
            if (dist[i] == 1e9)
            {
                return -1;
            }

            // The total time is the time it takes the furthest node to receive the signal
            timeTaken = max(timeTaken, dist[i]);
        }

        return timeTaken;
    }
};

int main()
{
    Solution sol;

    int V = 4;
    vector<vector<int>> edges = {
        {0, 1, 1}, {0, 2, 100}, {1, 2, 1}, {2, 3, 1}};

    return 0;
}
