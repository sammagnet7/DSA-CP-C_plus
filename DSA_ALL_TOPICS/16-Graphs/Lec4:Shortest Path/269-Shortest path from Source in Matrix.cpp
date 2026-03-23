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

1. Title: Shortest Path in Binary Matrix


Links:
https://takeuforward.org/data-structure/g-36-shortest-distance-in-a-binary-maze/
https://www.youtube.com/watch?v=U5Mw4eyUmw4&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=37
https://takeuforward.org/plus/dsa/problems/shortest-path-with-minimum-effort?tab=editorial
https://leetcode.com/problems/shortest-path-in-binary-matrix/description/


Problem statement:
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
    - All the visited cells of the path are 0.
    - All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).

The length of a clear path is the number of visited cells of this path.


Examples:
    Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: 2

    Example 2:
    Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    Output: 4

    Example 3:
    Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    Output: -1


Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Path With Minimum Effort

Links:
https://takeuforward.org/data-structure/g-37-path-with-minimum-effort/
https://www.youtube.com/watch?v=0ytpZyiZFhA
https://takeuforward.org/plus/dsa/problems/path-with-minimum-effort?tab=editorial
https://leetcode.com/problems/path-with-minimum-effort/description/


Problem statement:
You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Examples:
    Example 1:
    Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
    Output: 2
    Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
    This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

    Example 2:
    Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
    Output: 1
    Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

    Example 3:
    Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
    Output: 0
    Explanation: This route does not require any effort.


Constraints:
    rows == heights.length
    columns == heights[i].length
    1 <= rows, columns <= 100
    1 <= heights[i][j] <= 10^6



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Shortest Path in Binary Matrix
//-------------------------------------------------------------------------------

class Solution
{
public:
    //============================================================================
    // Approach 1 — Breadth-First Search (Shortest Path in Unweighted Grid)
    //============================================================================

    /**
     * @brief Finds the length of the shortest clear path from top-left to bottom-right.
     *
     * Intuition:
     * - The grid represents an unweighted graph where every valid 8-directional move
     * costs exactly 1 unit of distance.
     * - Breadth-First Search (BFS) is the optimal algorithm for finding shortest paths
     * in unweighted graphs. It explores all nodes at the present "depth" (distance)
     * before moving on to nodes at the next depth level.
     *
     * Understanding (Why NOT Dijkstra?):
     * - Dijkstra's algorithm relies on a Min-Heap Priority Queue to constantly sort
     * and prioritize paths of varying weights.
     * - Since every step in this grid has an identical cost (1), a standard FIFO Queue
     * naturally processes the cells in strictly increasing order of distance.
     * - Using Dijkstra here would add an unnecessary O(log N) sorting overhead,
     * wasting CPU cycles on something the queue structure already guarantees.
     *
     * Approach:
     * 1. Edge Case Check: If the starting cell or ending cell is blocked (1), a
     * valid path is instantly impossible. Return -1.
     * 2. Initialization:
     * - Create a 2D `dist` array initialized to infinity (1e9) to track visited
     * states and shortest known distances.
     * - Push the starting coordinates `{0, 0}` into the queue and set `dist[0][0] = 1`.
     * 3. 8-Directional BFS:
     * - Pop the front cell `{i, j}`.
     * - Iterate through all 8 possible directions.
     * - If the neighbor `{i1, j1}` is within bounds, is a clear path (0), AND
     * the new calculated distance is strictly smaller than its currently known
     * distance, we update `dist[i1][j1]` and push it into the queue.
     * 4. Post-Processing:
     * - If `dist[n-1][n-1]` is still 1e9, the destination was unreachable. Return -1.
     *
     * Time Complexity:
     * - O(N^2): In the absolute worst-case (a completely open grid), we will visit
     * each of the N*N cells exactly once, and check their 8 neighbors. This gives
     * a linear scan relative to the total number of cells.
     *
     * Space Complexity:
     * - O(N^2): The `dist` matrix takes N*N memory. The queue can grow to hold at
     * most O(N^2) cells in a highly dense, open grid scenario.
     */
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {

        int n = grid.size();

        // --- STEP 1: Edge Case Check ---
        // If the start or end points are blocked, no path can exist
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
        {
            return -1;
        }

        // --- STEP 2: Initialization ---
        // dist matrix doubles as our visited tracker and shortest-path record
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        queue<pair<int, int>> q;

        // 8-Directional movement arrays (Right, Down, Left, Up, and all 4 diagonals)
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        q.push({0, 0});
        dist[0][0] = 1; // Problem specifies the path length includes the starting cell

        // --- STEP 3: BFS Traversal ---
        while (!q.empty())
        {

            auto [i, j] = q.front();
            q.pop();

            for (int k = 0; k < 8; ++k)
            {

                int i1 = i + dir[k][0];
                int j1 = j + dir[k][1];

                // Boundary checks
                if (i1 < 0 || j1 < 0 || i1 >= n || j1 >= n)
                {
                    continue;
                }

                int newDist = dist[i][j] + 1;

                // State checks: Is it a shorter path? Is it unblocked land?
                if (newDist < dist[i1][j1] && grid[i1][j1] == 0)
                {

                    dist[i1][j1] = newDist;
                    q.push({i1, j1});
                }
            }
        }

        // --- STEP 4: Check if destination was reached ---
        return dist[n - 1][n - 1] == 1e9 ? -1 : dist[n - 1][n - 1];
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Minimum Effort Path
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    //============================================================================
    // Approach 1 — Dijkstra's Algorithm (Min-Max Path Cost)
    //============================================================================

    /**
     * @brief Finds a path from top-left to bottom-right that minimizes the maximum height difference.
     *
     * Idea & Intuition:
     * - This is a weighted graph problem operating on a 2D matrix. The "weight" of moving
     * from cell A to cell B is `abs(height[A] - height[B])`.
     * - Because edge weights vary, a standard BFS will fail. We must use Dijkstra's Algorithm
     * with a Min-Heap Priority Queue to always explore the "cheapest" available path.
     * - MODIFIED DIJKSTRA: Instead of finding the sum of weights, we are looking for the
     * maximum single jump on a path. Therefore, the cost of a path reaching cell B from
     * cell A is `max(cost_to_reach_A, jump_from_A_to_B)`.
     *
     * Approach:
     * 1. Initialization:
     * - Create a 2D `cost` array initialized to infinity (`1e9`) to track the minimum
     * effort required to reach each cell.
     * - Initialize a Min-Heap storing `tuple<effort, row, col>`. Push `{0, 0, 0}`.
     * 2. Dijkstra's Traversal:
     * - Extract the cell with the smallest current effort from the Min-Heap.
     * - LAZY DELETION: If the popped effort is strictly greater than `cost[i][j]`, skip it.
     * (This is a stale entry from an earlier, worse path).
     * 3. Edge Relaxation:
     * - For all 4 valid orthogonal neighbors, calculate the jump cost: `adjCost`.
     * - The new effort to reach the neighbor is the maximum of the current path's effort
     * and the new jump: `newCost = max(cost[i][j], adjCost)`.
     * - If `newCost` is strictly less than the neighbor's known `cost[i1][j1]`, update it
     * and push the new state into the Priority Queue.
     * 4. Return:
     * - Because it is Dijkstra, the absolute first time we pop the destination cell,
     * we guarantee we have found its minimum effort. We can return `cost[m-1][n-1]`.
     *
     * Time Complexity:
     * - O(M * N * log(M * N)): In the worst case, we might push every cell into the Priority
     * Queue multiple times. There are V = M*N cells and E = 4*M*N edges. Extracting from
     * the heap takes O(log V), giving us standard Dijkstra time complexity.
     *
     * Space Complexity:
     * - O(M * N): The 2D `cost` matrix and the Priority Queue both take space proportional
     * to the total number of cells in the grid.
     */
    int minimumEffortPath(vector<vector<int>> &heights)
    {

        int m = heights.size();
        int n = heights[0].size();

        // 4-Directional movement (Right, Down, Left, Up)
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        // Tracks the minimum effort required to reach [i][j]
        vector<vector<int>> cost(m, vector<int>(n, 1e9));

        // Min-Heap stores {current_max_effort, row, col}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        pq.push({0, 0, 0});
        cost[0][0] = 0;

        while (!pq.empty())
        {

            // C++17 Structured Binding to cleanly unpack the tuple
            auto [c, i, j] = pq.top();
            pq.pop();

            // Lazy Deletion: Skip stale, outdated queue entries
            if (cost[i][j] < c)
            {
                continue;
            }

            // Early Exit Optimization: If we pop the target, we are done!
            if (i == m - 1 && j == n - 1)
            {
                return c;
            }

            for (int k = 0; k < 4; ++k)
            {

                int i1 = i + dir[k][0];
                int j1 = j + dir[k][1];

                // Boundary Check
                if (i1 < 0 || j1 < 0 || i1 >= m || j1 >= n)
                {
                    continue;
                }

                // Calculate the hurdle to move to the neighbor
                int adjCost = abs(heights[i][j] - heights[i1][j1]);

                // The effort of this path is the MAXIMUM of the path so far, and the new jump
                int newCost = max(cost[i][j], adjCost);

                // Edge Relaxation: If this path is better, record it and queue it
                if (newCost < cost[i1][j1])
                {
                    cost[i1][j1] = newCost;
                    pq.push({newCost, i1, j1});
                }
            }
        }

        return cost[m - 1][n - 1];
    }
};

int main()
{
    return 0;
}
