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

1. Title: Swim in rising water

Links:
https://takeuforward.org/plus/dsa/problems/swim-in-rising-water?tab=editorial
https://leetcode.com/problems/swim-in-rising-water/description/


Problem statement:
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).

Examples:
    Example 1:
    Input: grid = [[0,2],[1,3]]
    Output: 3
    Explanation:
    At time 0, you are in grid location (0, 0).
    You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
    You cannot reach point (1, 1) until time 3.
    When the depth of water is 3, we can swim anywhere inside the grid.

    Example 2:
    Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
    Output: 16
    Explanation: The final route is shown.
    We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 50
    0 <= grid[i][j] < n2
    Each value grid[i][j] is unique.


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
// 1. Title: Swim in rising water
//-------------------------------------------------------------------------------
//

#define P pair<int, pair<int, int>>

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Utility: Check if (x, y) lies inside the grid
    // ------------------------------------------------------------------------
    bool isidxVal(int x, int y, int m, int n)
    {
        if (x < 0 || x >= m || y < 0 || y >= n)
            return false;
        return true;
    }

    // ------------------------------------------------------------------------
    // Problem: Swim in Rising Water (LC 778)
    //
    // Intuition:
    // - Each cell has a value = elevation (time when it becomes swimmable).
    // - You can move to an adjacent cell only when both current time >= elevation
    //   of the target cell.
    // - Essentially, we want the minimum "time" to reach the bottom-right corner.
    //
    // Understanding:
    // - This is equivalent to finding the minimum "maximum elevation" along a path
    //   from (0,0) → (n-1,n-1).
    // - Can be solved by:
    //   - Dijkstra’s algorithm on a grid (minimize max elevation seen so far).
    //   - Or Binary Search + BFS (not used here).
    //
    // Approach (Dijkstra):
    // 1. Maintain a priority queue (min-heap) storing {time, {x,y}}.
    //    - "time" = max elevation seen so far on the path to (x,y).
    // 2. Initialize with {grid[0][0], {0,0}}.
    // 3. Pop the smallest-time cell:
    //    - If it’s the destination (n-1,n-1), return its time.
    //    - Otherwise, relax its neighbors:
    //      - New time = max(currentTime, grid[vx][vy])
    //      - If new time improves shortest known time → update & push to PQ.
    // 4. The first time we pop (n-1,n-1), we have the optimal answer.
    //
    // Complexity:
    // - Each of n^2 cells is pushed/popped at most once → O(n^2 log n^2).
    // - Simplified: O(n^2 log n).
    // - Space: O(n^2) for time[][] and PQ.
    // ------------------------------------------------------------------------
    int swimInWater(vector<vector<int>> &grid)
    {
        int n = grid.size();

        // time[i][j] = minimum time required to reach cell (i,j)
        vector<vector<int>> time(n, vector<int>(n, 1e9));

        // Min-heap: {time, {x,y}}
        priority_queue<P, vector<P>, greater<P>> pq;

        // 4 possible moves: right, left, up, down
        vector<vector<int>> delta = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        // Start from (0,0) with initial time = grid[0][0]
        pq.push({grid[0][0], {0, 0}});
        time[0][0] = grid[0][0];

        while (!pq.empty())
        {
            int ux = pq.top().second.first;  // current x
            int uy = pq.top().second.second; // current y
            int t = pq.top().first;          // current best time
            pq.pop();

            // If destination reached, answer found
            if (ux == n - 1 && uy == n - 1)
                break;

            // Skip if we already found a better path earlier
            if (time[ux][uy] < t)
                continue;

            // Explore all 4 neighbors
            for (int k = 0; k < 4; k++)
            {
                int vx = ux + delta[k][0];
                int vy = uy + delta[k][1];

                if (!isidxVal(vx, vy, n, n))
                    continue;

                // New time = max of current path time and target cell’s elevation
                int v_time = max(t, grid[vx][vy]);

                // Relaxation: update if better
                if (v_time < time[vx][vy])
                {
                    time[vx][vy] = v_time;
                    pq.push({v_time, {vx, vy}});
                }
            }
        }

        // Return minimum time required to reach bottom-right cell
        return time[n - 1][n - 1];
    }
};

int main()
{
    return 0;
}