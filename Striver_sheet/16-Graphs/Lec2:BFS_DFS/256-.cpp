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

1. Title: Distance of Nearest Cell having 1


Links:
https://takeuforward.org/graph/distance-of-nearest-cell-having-1/
https://www.youtube.com/watch?v=edXdVwkYHF8
https://takeuforward.org/plus/dsa/problems/distance-of-nearest-cell-having-one?tab=editorial
https://leetcode.com/problems/01-matrix/
https://leetcode.com/problems/map-of-highest-peak/description/


Problem statement:
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
The distance between two cells sharing a common edge is 1.

Examples:
    Example 1:
    Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
    Output: [[0,0,0],[0,1,0],[0,0,0]]

    Example 2:
    Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
    Output: [[0,0,0],[0,1,0],[1,2,1]]


Constraints:
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 104
    1 <= m * n <= 104
    mat[i][j] is either 0 or 1.
    There is at least one 0 in mat.



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
    // 1. Title: Distance of Nearest Cell having 1
    //-------------------------------------------------------------------------------

    /**
     * Function: updateMatrix
     * Given a binary matrix `mat` (containing only 0s and 1s), returns a matrix where each cell
     * contains the distance to the nearest 0.
     *
     * Approach:
     *  - This is a **multi-source BFS problem**:
     *      - All cells containing 0 are considered as sources and enqueued initially with distance = 0.
     *      - For every cell dequeued, update its neighbors if they are unvisited and assign distance = current distance + 1.
     *  - This ensures that the shortest distance to the nearest 0 is calculated because BFS explores level by level.
     *
     * Steps:
     *  1. Initialize `vis` matrix of size m x n with -1 (indicating unvisited).
     *  2. Traverse `mat`:
     *      - For every cell with value 0:
     *          - Mark its distance as 0 in `vis`.
     *          - Push it into the queue with depth 0.
     *  3. Perform BFS:
     *      - For each cell, check its 4 neighbors (up, down, left, right).
     *      - If the neighbor is within bounds and unvisited:
     *          - Update its distance = current depth + 1.
     *          - Push it into the queue with updated depth.
     *  4. Continue until queue is empty.
     *  5. Return `vis` as the result.
     *
     * Time Complexity: O(m * n)
     *  - Each cell is pushed into the queue at most once and processed in O(1) time.
     * Space Complexity: O(m * n)
     *  - For the visited (or distance) matrix and BFS queue.
     *
     * @param mat Input binary matrix.
     * @return Matrix with shortest distances to the nearest 0 for each cell.
     */
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int m = mat.size();
        int n = mat[0].size();

        // Initialize visited/distance matrix with -1 (unvisited)
        vector<vector<int>> vis(m, vector<int>(n, -1));

        // Queue will store ((row, col), distance)
        queue<pair<pair<int, int>, int>> q;

        // 4 possible directions: up, down, left, right
        int dist[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Step 1: Push all cells with 0 into queue as starting points
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] == 0)
                {
                    q.push({{i, j}, 0});
                    vis[i][j] = 0; // Distance of 0-cell to nearest 0 is 0
                }
            }
        }

        // Step 2: BFS traversal
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();

            int i = p.first.first;
            int j = p.first.second;
            int depth = p.second;

            // Explore all 4 directions
            for (int k = 0; k < 4; k++)
            {
                int r = i + dist[k][0];
                int c = j + dist[k][1];

                // Skip if out of bounds
                if (r < 0 || r >= m || c < 0 || c >= n)
                    continue;

                // Skip if already visited
                if (vis[r][c] != -1)
                    continue;

                // Assign distance and push into queue
                vis[r][c] = depth + 1;
                q.push({{r, c}, depth + 1});
            }
        }

        return vis;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
