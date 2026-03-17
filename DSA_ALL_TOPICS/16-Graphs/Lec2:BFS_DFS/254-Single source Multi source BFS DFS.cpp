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

1. Title: Flood Fill Algorithm - Graphs

Links:
https://takeuforward.org/graph/flood-fill-algorithm-graphs/
https://www.youtube.com/watch?v=C-2_uSRli8o&feature=youtu.be
https://takeuforward.org/plus/dsa/problems/flood-fill-algorithm?tab=editorial
https://leetcode.com/problems/flood-fill/description/


Problem statement:
You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:
Begin with the starting pixel and change its color to color.
Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
The process stops when there are no more adjacent pixels of the original color to update.
Return the modified image after performing the flood fill.

Examples:
    Example 1:
    Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
    Output: [[2,2,2],[2,2,0],[2,0,1]]
    Explanation:
    From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
    Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.

    Example 2:
    Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
    Output: [[0,0,0],[0,0,0]]
    Explanation:
    The starting pixel is already colored with 0, which is the same as the target color. Therefore, no changes are made to the image.


Constraints:
    m == image.length
    n == image[i].length
    1 <= m, n <= 50
    0 <= image[i][j], color < 2^16
    0 <= sr < m
    0 <= sc < n


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Rotten Oranges : Min time to rot all oranges : BFS

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

*/

//-------------------------------------------------------------------------------
// 1. Title: Flood Fill Algorithm - Graphs
//-------------------------------------------------------------------------------

//-------------------------------
//  Approach 1: Single-Source BFS
//-------------------------------
class Solution
{
private:
    // Direction array for moving right, down, up, and left
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

public:
    /**
     * @brief Performs a flood fill on an image starting from (sr, sc).
     * * --- THE CORE IDEA: SINGLE-SOURCE BFS ---
     * This is the classic "Paint Bucket" tool found in image editors.
     * We start at a single pixel and radiate outwards using a Queue (BFS).
     * * --- THE TRICKS ---
     * 1. In-Place Visited Tracking: We don't need a `vis` matrix. By immediately
     * changing the pixel's color to the target `color`, it will no longer match
     * `matchClr`, naturally preventing the BFS from visiting it again!
     * 2. The Infinite Loop Guard: If the starting pixel is ALREADY the target color,
     * the BFS would run forever. Catching `matchClr == color` instantly solves this.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(M * N). In the absolute worst case, we color the entire grid.
     * Space Complexity : O(M * N) for the queue in the worst-case scenario.
     * (Auxiliary space for visited tracking is O(1)).
     */
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {

        int m = image.size();
        int n = image[0].size();

        queue<pair<int, int>> q;

        // --- STEP 1: INITIALIZE THE SOURCE ---
        q.push({sr, sc});
        int matchClr = image[sr][sc]; // The original color we need to replace

        // Immediately color the starting pixel
        image[sr][sc] = color;

        // EDGE CASE GUARD: If the new color is the same as the old color,
        // there is nothing to do. Return immediately to prevent an infinite loop.
        if (matchClr == color)
        {
            return image;
        }

        // --- STEP 2: BREADTH-FIRST SEARCH ---
        while (!q.empty())
        {

            int curi = q.front().first;
            int curj = q.front().second;
            q.pop();

            // Check all 4 adjacent pixels
            for (int k = 0; k < 4; ++k)
            {

                int adji = curi + dir[k][0];
                int adjj = curj + dir[k][1];

                // Boundary Check: Ensure we don't step outside the image
                if (adji < 0 || adjj < 0 || adji >= m || adjj >= n)
                {
                    continue;
                }

                // State Check: If the neighbor matches the ORIGINAL color
                if (image[adji][adjj] == matchClr)
                {

                    // Color it immediately (this acts as our visited mark!)
                    image[adji][adjj] = color;

                    // Push to the queue so we can evaluate its neighbors next
                    q.push({adji, adjj});
                }
            }
        }

        return image;
    }
};
//-------------------------------
//  Approach 2: Single-Source DFS
//-------------------------------
class Solution
{
private:
    /**
     * @brief Recursive DFS helper to flood fill the image.
     * * --- THE CORE IDEA: THE CALL STACK AS A QUEUE ---
     * Instead of pushing neighbors into a manual queue, we just call a function on them!
     * The OS Call Stack automatically remembers where we are. We dive as deep as possible
     * in one direction until we hit a boundary or a different color, then we naturally
     * backtrack and try the other directions.
     */
    void trDFS(vector<vector<int>> &ans, int i, int j, int color, int dir[4][2], int m, int n, int iniColor)
    {

        // --- 1. VISIT AND MODIFY ---
        // Fill the current pixel with the new color.
        // This instantly acts as our "visited" mark to prevent infinite loops!
        ans[i][j] = color;

        // --- 2. EXPLORE NEIGHBORS ---
        // Attempt to plunge deeper in all 4 adjacent directions
        for (int k = 0; k < 4; k++)
        {

            int p = i + dir[k][0];
            int q = j + dir[k][1];

            // Boundary Check: Ensure we don't step outside the image
            if (p < 0 || q < 0 || p >= m || q >= n)
            {
                continue;
            }

            // State Check: Only recurse if the neighbor matches the ORIGINAL color
            if (ans[p][q] == iniColor)
            {

                // Plunge deeper!
                trDFS(ans, p, q, color, dir, m, n, iniColor);
            }
        }
    }

public:
    /**
     * @brief Performs a flood fill on an image using Depth-First Search (DFS).
     * * --- COMPLEXITY ---
     * Time Complexity  : O(M * N). In the absolute worst case, we color the entire grid.
     * Space Complexity : O(M * N) to store the `ans` copy + O(M * N) for the recursion
     * call stack in the worst case (e.g., a massive zig-zag of the same color).
     * (Note: If we modified `image` directly instead of creating `ans`, space would be O(1) auxiliary).
     */
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {

        int m = image.size();
        int n = image[0].size();

        // The original color we need to replace
        int iniColor = image[sr][sc];

        // EDGE CASE GUARD: If the new color is the same as the old color,
        // there is nothing to do. Return immediately to prevent an infinite recursion loop!
        if (iniColor == color)
        {
            return image;
        }

        // Create a copy of the image to store the result without mutating the input
        vector<vector<int>> ans = image;

        // Direction array for moving: left, right, up, down
        int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        // Kick off the Depth-First Search from the starting pixel
        trDFS(ans, sr, sc, color, dir, m, n, iniColor);

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Rotten Oranges : Min time to rot all oranges : BFS
//-------------------------------------------------------------------------------

//------------------------------------------------------------
//  Approach 1: Multi-Source BFS using Level-Size (qSize) Loop
//------------------------------------------------------------
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
    int orangesRotting2(vector<vector<int>> &grid)
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
// 3. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
