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

1. Title: Rotten Oranges : Min time to rot all oranges : BFS

Links:
https://takeuforward.org/data-structure/rotten-oranges-min-time-to-rot-all-oranges-bfs/
https://www.youtube.com/watch?v=yf3oUhkvqA0
https://takeuforward.org/plus/dsa/problems/rotten-oranges?tab=editorial
https://leetcode.com/problems/rotting-oranges/description/


Problem statement:
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 Examples:
    Example 1:
    Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
    Output: 4

    Example 2:
    Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
    Output: -1
    Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

    Example 3:
    Input: grid = [[0,2]]
    Output: 0
    Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.


Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    grid[i][j] is 0, 1, or 2.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Distance of Nearest Cell having 1


Links:
https://takeuforward.org/graph/distance-of-nearest-cell-having-1/
https://www.youtube.com/watch?v=edXdVwkYHF8
https://takeuforward.org/plus/dsa/problems/distance-of-nearest-cell-having-one?tab=editorial
https://leetcode.com/problems/01-matrix/

Similar:
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
    1 <= m, n <= 10^4
    1 <= m * n <= 10^4
    mat[i][j] is either 0 or 1.
    There is at least one 0 in mat.



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Rotten Oranges : Min time to rot all oranges : BFS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------
//  Approach 1: Multi-Source BFS using Level-Size (qSize) Loop [RECOMMENDED]
//-------------------------------------------------------------
class Solution
{
private:
    // Direction array for moving right, down, left, and up
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
    /**
     * @brief Computes the minimum time required to rot all fresh oranges.
     * * --- THE CORE IDEA: MULTI-SOURCE BFS ---
     * Instead of running a separate Breadth-First Search for every fresh orange,
     * we gather ALL initially rotten oranges and push them into the queue at minute 0.
     * This allows the rot to spread outward simultaneously, simulating the passage of time
     * perfectly level-by-level.
     * * --- IMMUTABILITY & BEST PRACTICES ---
     * This solution uses a 'vis' (visited) matrix to track newly rotted oranges.
     * While taking O(M*N) extra space, it perfectly preserves the original input 'grid',
     * which is often a strict requirement in real-world production environments.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(M * N). We scan the grid once to initialize, and the BFS
     * processes each cell at most once.
     * Space Complexity : O(M * N) for the 'vis' matrix and the queue.
     */
    int orangesRotting(vector<vector<int>> &grid)
    {

        int m = grid.size();
        int n = grid[0].size();

        // Queue to hold the coordinates of rotting oranges for our BFS
        queue<pair<int, int>> q;

        // Track exactly how many fresh oranges we need to rot
        int freshCount = 0;

        // --- STEP 1: INITIALIZE MULTI-SOURCE QUEUE & COUNT FRESH ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    ++freshCount; // Found a target to rot
                }
                else if (grid[i][j] == 2)
                {
                    q.push({i, j}); // Found a starting source for the rot
                }
            }
        }

        // Base Case: If there are no fresh oranges to begin with, it takes 0 minutes.
        if (freshCount == 0)
        {
            return 0;
        }

        // Visited matrix to ensure we don't process the same orange twice
        // without mutating the original input grid.
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        int minsTaken = 0;

        // --- STEP 2: MULTI-SOURCE BFS (LEVEL-ORDER) ---
        while (!q.empty())
        {

            // Capture the number of rotting oranges at this exact minute
            int qsize = q.size();

            // Pre-increment the time. We only reach here if we have active rot spreading.
            ++minsTaken;

            // Process this entire minute (level) before moving to the next
            while (qsize--)
            {

                int curi = q.front().first;
                int curj = q.front().second;
                q.pop();

                // Attempt to spread rot in all 4 adjacent directions
                for (int k = 0; k < 4; ++k)
                {

                    int adji = curi + dir[k][0];
                    int adjj = curj + dir[k][1];

                    // 1. Boundary Check
                    if (adji < 0 || adjj < 0 || adji >= m || adjj >= n)
                    {
                        continue;
                    }

                    // 2. State Check: Ignore if already visited OR if it's NOT a fresh orange
                    if (vis[adji][adjj] || grid[adji][adjj] != 1)
                    {
                        continue;
                    }

                    // --- SPREAD THE ROT ---
                    vis[adji][adjj] = true;
                    --freshCount; // We successfully rotted one fresh orange!

                    q.push({adji, adjj});

                    // OPTIMIZATION: Instant Exit
                    // The exact moment the final fresh orange rots, return the time.
                    // This prevents the BFS from running unnecessary trailing loops.
                    if (freshCount == 0)
                    {
                        return minsTaken;
                    }
                }
            }
        }

        // --- STEP 3: CHECK FOR SURVIVORS ---
        // If the queue emptied out but fresh oranges still remain, they must be
        // walled off by 0s. They will never rot.
        return -1;
    }
};
//-----------------------------------------------------
//  Approach 2: Multi-Source BFS using Two-Queue System
//-----------------------------------------------------
class Solution
{
    /**
     * @brief Computes minimum time to rot all oranges using Grid Cloning and a Two-Queue system.
     * * --- THE IDEA & TRICK ---
     * 1. Non-Destructive Cloning: We clone the grid to `copiedGrid` so we don't mutate the
     * input data (a great best practice in real-world software engineering).
     * 2. The Two-Queue System: Instead of using `qSize` to track levels, we dump all newly
     * rotted oranges into a temporary `newlyRotten` queue. At the end of the minute, we
     * swap the queues. This naturally separates the current minute from the next minute.
     * 3. The Elapsed Time Compensation: Because the outer `while(1)` loop increments time
     * at the very beginning, the final iteration (which just confirms there are no more
     * oranges to rot) will overcount by 1. We fix this by returning `elapsed - 1`.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(M * N). Scanning and cloning takes O(M*N), and BFS visits
     * each cell at most once.
     * Space Complexity : O(M * N) for the `copiedGrid` matrix and the queues.
     */
    int orangesRotting(vector<vector<int>> &grid)
    {

        int m = grid.size();
        int n = grid[0].size();

        // --- STEP 1: CLONE AND INITIALIZE ---
        // Work on a copy to preserve the original grid
        vector<vector<int>> copiedGrid(m, vector<int>(n, 0));

        // Queue representing the rotting frontier for the CURRENT minute
        queue<pair<int, int>> rotten;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                copiedGrid[i][j] = grid[i][j];

                if (grid[i][j] == 2)
                {
                    rotten.push({i, j});
                }
            }
        }

        // Edge case handling: If there are no rotten oranges initially, we need to
        // handle the elapsed logic carefully, but the check at the bottom catches it.
        int elapsed = 0;
        int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        // --- STEP 2: MULTI-SOURCE BFS (TWO-QUEUE SYSTEM) ---
        while (1)
        {

            elapsed++; // Assume a minute passes (compensated at the end)

            // Queue representing the rotting frontier for the NEXT minute
            queue<pair<int, int>> newlyRotten;

            // Empty the entire current queue
            while (!rotten.empty())
            {

                int curI = rotten.front().first;
                int curJ = rotten.front().second;
                rotten.pop();

                // Explore neighbors
                for (int k = 0; k < 4; k++)
                {
                    int newI = curI + dir[k][0];
                    int newJ = curJ + dir[k][1];

                    if (newI < 0 || newI >= m || newJ < 0 || newJ >= n)
                    {
                        continue;
                    }

                    // If neighbor is fresh, rot it on the cloned grid and queue it for next minute
                    if (copiedGrid[newI][newJ] == 1)
                    {
                        copiedGrid[newI][newJ] = 2;
                        newlyRotten.push({newI, newJ});
                    }
                }
            }

            // If the next minute's queue is empty, the rot has completely stopped spreading
            if (newlyRotten.empty())
            {
                break;
            }

            // Promote the newly rotted oranges to become the source for the next iteration
            rotten = newlyRotten;
        }

        // --- STEP 3: CHECK FOR SURVIVORS ---
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (copiedGrid[i][j] == 1)
                {
                    return -1; // Isolated fresh orange found
                }
            }
        }

        // Compensate for the extra increment that occurred on the final "empty" while iteration
        return elapsed - 1;
    }
};


//-------------------------------------------------------------------------------
// 2. Title: Distance of Nearest Cell having 1
//-------------------------------------------------------------------------------
class Solution
{
private:
    // Direction array for moving right, down, left, and up
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    /**
     * @brief Helper function to perform Multi-Source Breadth-First Search.
     * * @idea
     * By initializing the queue with ALL the 0s at once, the BFS radiates outward
     * in simultaneous, uniform rings. The first time our BFS wave touches an
     * unvisited cell, we are mathematically guaranteed that it is the absolute
     * shortest path to that cell.
     * * @approach
     * We use a level-order traversal (`while(qsize--)`). For every level we process,
     * we increment `curDist` by 1. We check all 4 neighbors of the current cell.
     * If a neighbor's distance is still `1e9` (infinity), it means it is unvisited.
     * We update its distance to `curDist` and push it into the queue to act as a
     * stepping stone for the next distance ring.
     * * @param q The queue pre-loaded with the coordinates of all 0s.
     * @param mat The original binary matrix.
     * @param dist The distance matrix that doubles as our visited tracker.
     */
    void bfs(queue<tuple<int, int>> &q, vector<vector<int>> &mat, vector<vector<int>> &dist)
    {

        int curDist = 0;

        while (!q.empty())
        {

            // Capture the number of cells at the current distance radius
            int qsize = q.size();

            // Increment distance as we prepare to step outward to the next ring
            ++curDist;

            // Process the entire current ring
            while (qsize--)
            {

                auto [curi, curj] = q.front();
                q.pop();

                // Attempt to spread the distance to all 4 adjacent neighbors
                for (int k = 0; k < 4; ++k)
                {

                    int adi = curi + dir[k][0];
                    int adj = curj + dir[k][1];

                    // Boundary Check: Ensure we don't step out of the grid
                    if (adi < 0 || adj < 0 || adi >= mat.size() || adj >= mat[0].size())
                    {
                        continue;
                    }

                    // State Check:
                    // 1. If it's a 0, its distance is already 0.
                    // 2. If dist < 1e9, we have already found a shorter/equal path to it.
                    if (mat[adi][adj] == 0 || dist[adi][adj] < 1e9)
                    {
                        continue;
                    }

                    // --- SPREAD THE DISTANCE ---
                    // Lock in the shortest distance
                    dist[adi][adj] = curDist;

                    // Queue the neighbor to continue the wave outward
                    q.push({adi, adj});
                }
            }
        }
    }

public:
    /**
     * @brief Computes the distance of the nearest 0 for each cell in the matrix.
     * * @idea
     * Instead of running a massive, redundant DFS from every single 0 or 1,
     * we gather all the targets (the 0s) and search outwards simultaneously.
     * * @approach
     * 1. Create a `dist` matrix initialized to infinity (`1e9`). This brilliantly
     * acts as both our answer grid AND our visited array.
     * 2. Scan the grid. Every time we find a `0`, set its distance to `0` and
     * push its coordinates into our BFS queue.
     * 3. Pass the fully loaded queue to our `bfs` helper to simulate the expansion.
     * * @time O(M * N)
     * We scan the grid once to initialize. During the BFS, every cell is pushed
     * and popped from the queue exactly once. No redundant overwriting occurs.
     * * @space O(M * N)
     * Auxiliary space is required for the `dist` matrix and the BFS `queue`.
     * In the worst case (e.g., a grid full of 0s), the queue holds M * N elements.
     */
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {

        int m = mat.size();
        int n = mat[0].size();

        // Initialize with 1e9 to represent "infinity" / "unvisited"
        vector<vector<int>> dist(m, vector<int>(n, 1e9));
        queue<tuple<int, int>> q;

        // --- STEP 1: GATHER ALL SOURCES ---
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                // Found a source: distance is 0, add to queue
                if (mat[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // --- STEP 2: LAUNCH THE MULTI-SOURCE WAVES ---
        bfs(q, mat, dist);

        return dist;
    }
};

int main()
{
    return 0;
}
