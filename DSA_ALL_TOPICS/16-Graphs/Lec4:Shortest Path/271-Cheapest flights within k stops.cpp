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

1. Title: G-38: Cheapest Flights Within K Stops | Bellmanford Algorithm

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
    1 <= pricei <= 104
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
// 1. Title: Cheapest Flights Within K Stops: G-46
//-------------------------------------------------------------------------------
//

// Define P as a shorthand for the priority queue element:
// {{number_of_stops, total_price}, node}
#define P pair<pair<int, int>, int>

class Solution
{
public:
    /**********************************************************************************************
    Approach 1: Dijkstra's Algorithm with a twist (using a priority queue)

    🔹 Why does this not work?
    - The primary issue with this implementation is that the priority queue sorts by price, but the relaxation `if(newN_dist < minDist[adjN])` doesn't consider the number of stops.
    - A path with fewer stops might have a higher cost to reach an intermediate node, but could lead to a cheaper final path.
    - For example, if we reach node B via a path with 2 stops and a cost of 100, and then later we find a path with 3 stops to B with a cost of 110, we will correctly ignore the second path. However, what if the 3-stop path is actually a sub-path of the optimal solution? The `minDist` array prevents us from exploring a path to a node that has already been "finalized" with a seemingly better price, even if a path with more stops could be a better sub-solution for the rest of the journey.
    - The correct approach requires a different state to be stored: `minDist[node][stops]` to store the minimum cost to reach a node with a certain number of stops. The provided code only uses `minDist[node]`, which loses the stop count information.

    🔹 Complexity:
    - Time Complexity: O(E * log V) in the best-case where there are no stops constraints. With the stops constraint, it's inefficient and potentially incorrect due to the `minDist` array not accounting for stops. The number of states can be up to `n * k`. So the time complexity would be roughly O(E * log(E*k)). This implementation is flawed for the reasons mentioned above.
    - Space Complexity: O(V + E) for the adjacency list + O(V*k) for the priority queue in the worst case (multiple paths to the same node).

    **********************************************************************************************/
    // int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

    //     // Adjacency list to represent the graph: adjL[node] = {{neighbor, price}, ...}
    //     vector<vector<pair<int,int>>> adjL(n, vector<pair<int,int>>());

    //     // Build the adjacency list from the flights data
    //     for(auto e: flights){
    //         adjL[e[0]].push_back({e[1], e[2]});
    //     }

    //     // Min-priority queue to store flight states: {{stops, price}, node}
    //     priority_queue<P,vector<P>,greater<P>> pq;
    //     // `minDist[i]` stores the minimum price to reach node `i`
    //     vector<int> minDist(n, 1e9);

    //     // Push the source node with 0 stops and 0 price
    //     pq.push({ {0, 0}, src });
    //     minDist[src] = 0;

    //     while(!pq.empty()){

    //         // Extract the state with the smallest price from the priority queue
    //         int curN_hops = pq.top().first.first;
    //         int curN_dist = pq.top().first.second;
    //         int curN = pq.top().second;

    //         pq.pop();

    //         // If we have exceeded the maximum allowed stops, skip this path
    //         if(curN_hops > k)
    //             continue;

    //         // Explore the neighbors of the current node
    //         for(auto adj : adjL[curN]){
    //             int adjN = adj.first;
    //             int adjN_dist = adj.second;

    //             // Calculate the new total price and number of hops
    //             int newN_dist = curN_dist + adjN_dist;
    //             int newN_hops = curN_hops + 1;

    //             // If the new path is cheaper, update the `minDist` and push to the queue
    //             // This is the flawed part: it doesn't consider the number of hops.
    //             // A path with more stops but a cheaper intermediate price is better,
    //             // but this logic only checks against the cheapest path found so far.
    //             if(newN_dist < minDist[adjN]){
    //                 minDist[adjN] = newN_dist;
    //                 pq.push({ { newN_hops ,newN_dist }, adjN });
    //             }
    //         }
    //     }

    //     // Return the cheapest price to the destination, or -1 if unreachable
    //     return minDist[dst]==1e9 ? -1 : minDist[dst];
    // }

    /**
     * @brief Finds the cheapest price from src to dst with at most k stops.
     *
     * This function uses a modified Bellman-Ford algorithm.
     * The core idea is to run the relaxation step k+1 times.
     *
     * Let costs[i] be the cheapest cost to reach city 'i'.
     * We run a loop from 1 to k+1 (representing the number of flights).
     * In each iteration 'i', we calculate the minimum cost to reach any node
     * using at most 'i' flights, based on the costs from iteration 'i-1'.
     *
     * "At most k stops" means "at most k+1 flights".
     *
     * @param n The number of cities.
     * @param flights A list of [from, to, price] for each flight.
     * @param src The source city.
     * @param dst The destination city.
     * @param k The maximum number of stops allowed.
     * @return The cheapest price, or -1 if no such route exists.
     */
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {

        // Use a large number to represent infinity.
        // We choose 1e9 because the max possible cost is around 100 * 10000 = 1e6,
        // so 1e9 is safe from both overflow and being a valid cost.
        const int INF = 1e9;

        // costs[i] = minimum cost to reach city 'i' from 'src'
        vector<int> costs(n, INF);
        costs[src] = 0;

        // We need k+1 iterations, as k stops mean k+1 flights.
        // i=0: 1 flight (0 stops)
        // i=1: 2 flights (1 stop)
        // ...
        // i=k: k+1 flights (k stops)
        for (int i = 1; i <= k + 1; ++i)
        {

            // Create a temporary copy of the costs from the *previous* iteration.
            // We must use the values from the previous step to calculate the
            // current step, otherwise we might inadvertently chain flights
            // together and exceed the 'i' flight limit within a single iteration.
            vector<int> temp_costs = costs;

            for (const auto &flight : flights)
            {
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];

                // If the 'from' city was reachable in the previous iteration...
                if (costs[from] != INF)
                {
                    // ...see if we can find a cheaper path to the 'to' city
                    // *in the current iteration*.
                    temp_costs[to] = min(temp_costs[to], costs[from] + price);
                }
            }

            // Update the main costs array with the results from this iteration.
            costs = temp_costs;
        }

        // After k+1 iterations, costs[dst] will hold the cheapest price
        // to reach 'dst' with at most k stops.
        if (costs[dst] == INF)
        {
            return -1; // Destination is not reachable within k stops.
        }
        else
        {
            return costs[dst];
        }
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