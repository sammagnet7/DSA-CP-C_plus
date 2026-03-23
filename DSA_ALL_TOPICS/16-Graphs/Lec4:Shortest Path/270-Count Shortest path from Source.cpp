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

1. Title: Number of Ways to Arrive at Destination

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
    1 <= timei <= 10^9
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
// 1. Title: Number of Ways to Arrive at Destination
//-------------------------------------------------------------------------------


class Solution
{
    const int MOD = 1e9 + 7;

public:
    //============================================================================
    // Approach 1 — Dijkstra's Algorithm + Combinatorics (Path Counting)
    //============================================================================

    /**
     * @brief Finds the number of distinct shortest paths from node 0 to node n-1.
     *
     * Idea & Intuition:
     * - Standard Dijkstra finds *what* the shortest distance is, but not *how many* * ways there are to achieve it.
     * - To count paths, we introduce a `counts` array.
     * - When relaxing edges, two scenarios can occur:
     * 1. We find a STRICTLY shorter path: We discard all old paths. The number of
     * ways to reach the neighbor is now exactly equal to the number of ways we
     * reached our current node.
     * 2. We find a path with the EXACT SAME shortest time: We found an alternative
     * route! We add the current node's path count to the neighbor's path count.
     *
     * Understanding (The Data Type Trap):
     * - The time constraints allow weights up to 10^9 and 200 nodes. The max total time
     * can reach 2 * 10^11. A standard 32-bit integer overflows at ~2 * 10^9.
     * - We MUST use `long long` for all time/distance calculations, and our "infinity"
     * must be upgraded to `1e18` to accommodate massive valid paths.
     *
     * Approach:
     * 1. Initialization:
     * - Build the adjacency list `adjL`.
     * - Initialize `times` array to `1e18` (long long infinity).
     * - Initialize `counts` array to `0`. Set `counts[0] = 1` (1 way to stay at start).
     * - Priority Queue stores `{time, node}`. Time MUST be `long long`.
     * 2. Modified Dijkstra's Loop:
     * - Extract `{curT, curN}`. Skip stale paths using Lazy Deletion.
     * - For each neighbor, calculate `newT`.
     * - If `newT < times[adjN]`: Update shortest time, OVERWRITE `counts[adjN]`, push to PQ.
     * - If `newT == times[adjN]`: Accumulate `counts[adjN] = (counts[adjN] + counts[curN]) % MOD`.
     * 3. Return `counts[n-1] % MOD`.
     *
     * Time Complexity:
     * - O(E log V): This is still a standard Dijkstra traversal. We visit every edge and
     * push to the heap only when we find a strictly shorter path.
     *
     * Space Complexity:
     * - O(V + E): Standard space for Adjacency List, Priority Queue, `times`, and `counts` arrays.
     */
    int countPaths(int n, vector<vector<int>> &roads)
    {

        // --- STEP 1: Build Adjacency List ---
        // Weight must be extracted as long long to prevent calculation overflows later
        vector<vector<pair<int, long long>>> adjL(n);

        for (const auto &e : roads)
        {
            int u = e[0];
            int v = e[1];
            long long w = e[2];

            adjL[u].push_back({v, w});
            adjL[v].push_back({u, w});
        }

        // --- STEP 2: Initialize 64-bit trackers ---
        // 1e18 safely acts as infinity for long long without overflowing addition
        vector<long long> times(n, 1e18);
        vector<long long> counts(n, 0);

        // PQ must store {long long time, int node}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

        // Initialize Start Node
        pq.push({0LL, 0});
        times[0] = 0;
        counts[0] = 1;

        // --- STEP 3: Dijkstra's Loop with Path Counting ---
        while (!pq.empty())
        {

            auto [curT, curN] = pq.top();
            pq.pop();

            // Lazy Deletion
            if (times[curN] < curT)
            {
                continue;
            }

            for (const auto &[adjN, adjW] : adjL[curN])
            {

                long long newT = curT + adjW;

                // Case 1: We found a strictly faster route. Overwrite everything!
                if (newT < times[adjN])
                {
                    times[adjN] = newT;

                    // The number of ways to get here is inherited from the parent
                    counts[adjN] = counts[curN];

                    pq.push({newT, adjN});
                }
                // Case 2: We found a parallel route taking the exact same minimum time.
                else if (newT == times[adjN])
                {
                    // Accumulate the paths (with modulo to prevent counting overflows)
                    counts[adjN] = (counts[adjN] + counts[curN]) % MOD;
                }
            }
        }

        return counts[n - 1] % MOD;
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