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

1. Title: G-37: Path With Minimum Effort | Djisktra's Algorithm

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
    1 <= heights[i][j] <= 106



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
// 1. Title: Minimum Effort Path: G-45
//-------------------------------------------------------------------------------
//
#define P pair<int, pair<int, int>>

class Solution
{
public:
    /**********************************************************************************************
    Method: isIdxVal

    🔹 Description:
    - This helper function checks if a given row and column index `(i, j)` is within the bounds of a 2D grid of size `m x n`.
    - It's a standard utility for grid traversal problems to prevent out-of-bounds access.

    🔹 Parameters:
    - `i`: The row index to check.
    - `j`: The column index to check.
    - `m`: The total number of rows in the grid.
    - `n`: The total number of columns in the grid.

    🔹 Returns:
    - `true` if `(i, j)` is a valid index.
    - `false` otherwise.

    **********************************************************************************************/
    bool isIdxVal(int i, int j, int m, int n)
    {
        if (i < 0 || i >= m || j < 0 || j >= n) // Check if indices are within the grid dimensions
            return false;
        return true;
    }

    /**********************************************************************************************
    Approach 1: Dijkstra's Algorithm using Min-Heap (Priority Queue)

    🔹 How it works:
    - The problem asks for the path that minimizes the *maximum* absolute difference in height.
    - This is a classic variation of the Shortest Path problem, where "distance" is not a sum but a "bottleneck" value (the maximum edge weight on the path).
    - We can adapt Dijkstra's algorithm for this. Instead of `dist[adjN] = min(dist[adjN], dist[curN] + edge_weight)`, we use `minEff[adjN] = min(minEff[adjN], max(minEff[curN], edge_weight))`.
    - The priority queue stores `{max_effort_so_far, {row, col}}` and always extracts the cell with the minimum maximum effort.
    - This ensures we always expand from the path with the smallest effort, guaranteeing the first time we reach the destination, it's via the minimum effort path.

    🔹 Why is Dijkstra's applicable here?
    - The "relaxation" step `new_min_maxDiff < minEff[adjN]` holds a similar property to standard Dijkstra: if we find a better path (one with a smaller maximum effort), we update the effort and explore from there.
    - The "edge weight" is the absolute height difference between adjacent cells.
    - The "path length" is the maximum of all edge weights along the path.

    🔹 Complexity:
    - V = m * n (number of cells)
    - E = 4 * (m * n) (each cell has up to 4 neighbors)
    - Time Complexity: O((V + E) * log V) = O((m*n) * log(m*n))
      (Similar to standard Dijkstra with a min-heap)
    - Space Complexity: O(V) = O(m*n) for `minEff` matrix and the priority queue.

    **********************************************************************************************/
    int minimumEffortPath(vector<vector<int>> &heights)
    {

        int m = heights.size();    // Get the number of rows
        int n = heights[0].size(); // Get the number of columns

        // Min-priority queue to store pairs of {max_effort, {row, col}}
        priority_queue<P, vector<P>, greater<P>> pq;
        // 2D matrix to store the minimum effort to reach each cell
        vector<vector<int>> minEff(m, vector<int>(n, 1e9));
        // Array to define directions for up, down, left, right movement
        vector<vector<int>> delta = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        pq.push({0, {0, 0}}); // Push the starting cell with effort 0
        minEff[0][0] = 0;     // The effort to reach the start is 0

        while (!pq.empty())
        {

            // Get the cell with the minimum effort from the priority queue
            int cur_min_maxDiff = pq.top().first;
            int curN_i = pq.top().second.first;
            int curN_j = pq.top().second.second;

            pq.pop(); // Remove the top element

            // If we have already found a path with less effort, skip this entry
            // This is analogous to the `if (curDist > dist[curN]) continue;` check in standard Dijkstra
            if (cur_min_maxDiff > minEff[curN_i][curN_j])
                continue;

            // If we reach the destination, we've found the minimum effort path
            if (curN_i == m - 1 && curN_j == n - 1)
                return cur_min_maxDiff;

            // Explore the neighbors of the current cell
            for (int k = 0; k < 4; k++)
            {
                int adjN_i = curN_i + delta[k][0];
                int adjN_j = curN_j + delta[k][1];

                if (isIdxVal(adjN_i, adjN_j, m, n))
                { // Check if the neighbor is valid

                    // Calculate the new effort: the maximum of the current path's effort
                    // and the effort to move to the neighbor
                    int new_min_maxDiff = max(cur_min_maxDiff, abs(heights[adjN_i][adjN_j] - heights[curN_i][curN_j]));

                    // If this new path has less effort than the previously recorded effort
                    if (new_min_maxDiff < minEff[adjN_i][adjN_j])
                    {
                        minEff[adjN_i][adjN_j] = new_min_maxDiff;     // Update the minimum effort
                        pq.push({new_min_maxDiff, {adjN_i, adjN_j}}); // Push the neighbor to the queue
                    }
                }
            }
        }

        return minEff[m - 1][n - 1]; // Return the effort to reach the destination
    }
};

int main()
{
    // Example 1
    std::vector<std::vector<int>> heights1 = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    Solution sol;
    std::cout << "Minimum effort path for Example 1: " << sol.minimumEffortPath(heights1) << std::endl; // Expected output: 2

    // Example 2
    std::vector<std::vector<int>> heights2 = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
    std::cout << "Minimum effort path for Example 2: " << sol.minimumEffortPath(heights2) << std::endl; // Expected output: 1

    // Example 3
    std::vector<std::vector<int>> heights3 = {{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}};
    std::cout << "Minimum effort path for Example 3: " << sol.minimumEffortPath(heights3) << std::endl; // Expected output: 0

    return 0;
}