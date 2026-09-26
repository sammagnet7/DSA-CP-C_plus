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

1. Title: Cheapest Flights Within K Stops

Links:
https://takeuforward.org/data-structure/g-38-cheapest-flights-within-k-stops/
https://www.youtube.com/watch?v=9XybHVqTHcQ
https://takeuforward.org/plus/dsa/problems/cheapest-flight-within-k-stops?tab=editorial
https://leetcode.com/problems/cheapest-flights-within-k-stops/description/


Problem statement:
There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.

Examples:
    Example 1:
    Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
    Output: 700
    Explanation:
    The graph is shown above.
    The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
    Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.

    Example 2:
    Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
    Output: 200
    Explanation:
    The graph is shown above.
    The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.

    Example 3:
    Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
    Output: 500
    Explanation:
    The graph is shown above.
    The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.


Constraints:
    1 <= n <= 100
    0 <= flights.length <= (n * (n - 1) / 2)
    flights[i].length == 3
    0 <= fromi, toi < n
    fromi != toi
    1 <= pricei <= 10^4
    There will not be any multiple flights between two cities.
    0 <= src, dst, k < n
    src != dst



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
// 1. Title: Cheapest Flights Within K Stops
//-------------------------------------------------------------------------------

class Solution
{
public:
    //============================================================================
    // Approach 1 — Modified Bellman-Ford (Level-Isolated DP) [RECOMMENDED]
    //============================================================================

    /**
     * @brief Finds the cheapest price from src to dst with at most k stops.
     *
     * Idea & Intuition:
     * - The problem restricts our path to at most `k` stops, which mathematically
     * equates to at most `k + 1` flights (edges).
     * - Standard Bellman-Ford naturally finds shortest paths by expanding exactly one
     * edge length per iteration. If we strictly limit the algorithm to run exactly
     * `k + 1` times, it perfectly solves the problem without needing a BFS Queue or a
     * Min-Heap Priority Queue.
     *
     * Understanding (The "State Bleeding" Trap):
     * - Why do we need `tmpPrices`? Standard Bellman-Ford updates its distance array
     * IN-PLACE. If our array has edges `A -> B` and `B -> C`, and the loop processes
     * them in that exact order, `C` will update in the same iteration as `B`.
     * - This means we just traveled 2 edges, but the algorithm thinks it only took 1
     * iteration! This violates the `k` stops constraint.
     * - By reading from the finalized `prices` (previous level) and writing strictly
     * to `tmpPrices` (current level), we completely isolate the levels and prevent
     * intra-iteration state bleeding.
     *
     * Approach:
     * 1. Initialization:
     * - Define `V = k + 2`. Looping from 1 to `V - 1` ensures exactly `k + 1` iterations.
     * - Initialize `prices` and `tmpPrices` arrays to infinity (`1e9`). Set the
     * `src` node to 0 in both.
     * 2. Level-Restricted Edge Relaxation:
     * - Iterate `k + 1` times.
     * - For every edge `[u, v, w]`, check if the source node `u` was reachable in a
     * previous level (`prices[u] != 1e9`).
     * - Calculate the new cost: `newW = prices[u] + w`.
     * - If `newW` is cheaper than the currently known path to `v` at this level, update
     * `tmpPrices[v] = newW`.
     * 3. State Synchronization:
     * - At the end of every iteration, sync the arrays: `prices = tmpPrices`. This
     * locks in the results of the current edge depth before moving to the next.
     * 4. Return Result:
     * - If `prices[dst]` is still `1e9`, it's unreachable within `k` stops. Return -1.
     *
     * Time Complexity:
     * - O((K + 1) * E): We iterate exactly K + 1 times, and process every edge (E)
     * each time. Because K is often much smaller than V, this is frequently faster
     * than standard Bellman-Ford's O(V * E).
     *
     * Space Complexity:
     * - O(V): Extremely memory efficient. We only need two arrays of size V. We don't
     * even need to spend memory building an Adjacency List!
     */
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {

        // k  stops mean total (k+2) nodes in the graph
        // k stops means exactly k + 1 flights.
        // V = k + 2 allows a loop from 1 to V - 1 (which is exactly k + 1 iterations)
        int V = (k + 2);

        // prices tracks the finalized distances from the PREVIOUS level
        // tmpPrices tracks the newly discovered distances for the CURRENT level
        vector<int> prices(n, 1e9), tmpPrices(n, 1e9);

        prices[src] = 0;
        tmpPrices[src] = 0;

        // Run exactly k + 1 times
        for (int i = 1; i <= V - 1; ++i)
        {

            for (const auto &e : flights)
            {

                int u = e[0];
                int v = e[1];
                int w = e[2];

                // SAFETY CHECK: Only project paths from nodes we could reach in prior steps
                if (prices[u] == 1e9)
                {
                    continue;
                }

                int newW = prices[u] + w;

                // READ from `prices` (old state), WRITE to `tmpPrices` (new state)
                if (newW < tmpPrices[v]) // NOTE: here we are checking against `tmpPrices` (new state)
                {
                    tmpPrices[v] = newW;
                }
            }

            // Sync the states: the current level becomes the "previous" level for the next iteration
            prices = tmpPrices;
        }

        return prices[dst] == 1e9 ? -1 : prices[dst];
    }

    //============================================================================
    // Approach 2 — Level-Restricted BFS (Queue)
    //============================================================================

    /**
     * @brief Finds the cheapest price from src to dst with at most k stops.
     *
     * Idea & Intuition:
     * - Pure Dijkstra fails here because it prioritizes cost over the number of stops.
     * It might finalize a node via a very cheap path that has too many stops, ruining
     * our chances of finding a slightly more expensive but legally valid path.
     * - Because the primary constraint is the *number of steps* (stops), Breadth-First
     * Search (BFS) is the perfect tool. BFS inherently processes the graph in concentric
     * circles (levels), meaning all 0-stop flights are processed, then 1-stop, etc.
     *
     * Approach:
     * 1. Graph Construction:
     * - Build a directed Adjacency List `adjL`.
     * 2. Initialization:
     * - Create a `dist` array initialized to `1e9`. Set `dist[src] = 0`.
     * - Initialize a standard FIFO Queue storing `{node, current_cost}`.
     * 3. Level-By-Level BFS:
     * - Maintain a `stops` counter.
     * - Process the queue level-by-level using `int sz = q.size(); while(sz--)`.
     * - For each popped `{node, cost}`, look at its neighbors.
     * - If `cost + adjW < dist[adjN]`, update `dist[adjN]` and push `{adjN, newCost}`
     * into the queue.
     * - Crucial Detail: Notice the queue stores the `cost` it took to get there, NOT
     * just the node. This prevents level N from accidentally using an updated distance
     * from a different path in level N.
     * - Increment `stops`. If `stops > k`, terminate the loop!
     * 4. Return:
     * - Return `dist[dst]` (or -1 if it remains `1e9`).
     *
     * Time Complexity:
     * - O(E): In the worst case, we process every edge. Because we strictly stop after
     * k levels, we don't have the O(log V) sorting overhead of Dijkstra's Min-Heap.
     *
     * Space Complexity:
     * - O(V + E): The Adjacency List takes O(V + E). The Queue and `dist` array take
     * O(V) auxiliary space.
     */
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {

        // --- STEP 1: Build the Adjacency List ---
        vector<vector<pair<int, int>>> adjL(n);

        for (const auto &f : flights)
        {
            int u = f[0], v = f[1], w = f[2];
            adjL[u].push_back({v, w});
        }

        // --- STEP 2: Initialize BFS ---
        vector<int> dist(n, 1e9);
        dist[src] = 0;

        // Queue stores {current_node, total_cost_to_reach_node}
        queue<pair<int, int>> q;
        q.push({src, 0});

        int stops = 0;

        // --- STEP 3: Level-Restricted BFS Traversal ---
        // We are allowed up to 'k' intermediate stops.
        while (!q.empty() && stops <= k)
        {

            int sz = q.size();

            // Process the entire current level (all flights with 'stops' intermediate cities)
            while (sz--)
            {

                auto [curN, curCost] = q.front();
                q.pop();

                for (const auto &[adjN, adjW] : adjL[curN])
                {

                    int newCost = curCost + adjW;

                    // If we found a cheaper way to reach the neighbor within the stop limit
                    if (newCost < dist[adjN])
                    {
                        dist[adjN] = newCost;
                        q.push({adjN, newCost});
                    }
                }
            }

            // Move to the next depth level
            ++stops;
        }

        // --- STEP 4: Return Result ---
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};

int main()
{
    Solution sol;

    // Example 1
    int n1 = 3;
    std::vector<std::vector<int>> flights1 = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src1 = 0, dst1 = 2, k1 = 1;
    std::cout << "Cheapest price for Example 1: " << sol.findCheapestPrice(n1, flights1, src1, dst1, k1) << std::endl; // Expected output: 200

    // Example 2
    int n2 = 3;
    std::vector<std::vector<int>> flights2 = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src2 = 0, dst2 = 2, k2 = 0;
    std::cout << "Cheapest price for Example 2: " << sol.findCheapestPrice(n2, flights2, src2, dst2, k2) << std::endl; // Expected output: 500

    // Example 3
    int n3 = 4;
    std::vector<std::vector<int>> flights3 = {{0, 1, 1}, {0, 2, 5}, {1, 2, 1}, {2, 3, 1}};
    int src3 = 0, dst3 = 3, k3 = 1;
    std::cout << "Cheapest price for Example 3: " << sol.findCheapestPrice(n3, flights3, src3, dst3, k3) << std::endl; // Expected output: 6

    return 0;
}