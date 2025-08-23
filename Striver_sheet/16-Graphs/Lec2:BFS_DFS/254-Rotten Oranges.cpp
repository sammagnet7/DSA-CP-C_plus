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

2. Title: Flood Fill Algorithm - Graphs

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
    0 <= image[i][j], color < 216
    0 <= sr < m
    0 <= sc < n


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Rotten Oranges : Min time to rot all oranges : BFS
    //-------------------------------------------------------------------------------
    /*
           /**
    * Approach:
    *  - Use Breadth-First Search (BFS) to simulate the rotting process level by level.
    *  - Each rotten orange rots its adjacent fresh oranges (up, down, left, right) in one time unit.
    *  - Push all initially rotten oranges into a queue and process them in rounds (time steps).
    *  - Maintain a 'vis' matrix to track which oranges are fresh (0) or processed (1).
    *  - For each round, if any fresh orange becomes rotten, increment the time counter.
    *  - After BFS completes, check if any fresh orange remains. If yes, return -1.
    *
    * Time Complexity:
    *  - O(m * n), where m = number of rows and n = number of columns.
    *  - Each cell is visited at most once in the BFS.
    *
    * Space Complexity:
    *  - O(m * n) for the 'vis' matrix and BFS queue in the worst case (all cells are oranges).
    */

    int orangesRotting(vector<vector<int>> &grid)
    {

        int m = grid.size();    // Number of rows
        int n = grid[0].size(); // Number of columns

        // Visited matrix to track processed cells:
        // 1 -> processed (either empty cell or rotten orange)
        // 0 -> fresh orange (unprocessed)
        vector<vector<int>> vis(m, vector<int>(n, 1));

        // Queue for BFS to store positions of rotten oranges
        queue<pair<int, int>> rotten;

        // Initialize 'vis' and 'rotten' queue
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (grid[i][j] == 1)
                {
                    // Fresh orange found -> mark as unprocessed in vis
                    vis[i][j] = 0;
                }
                else if (grid[i][j] == 2)
                {
                    // Rotten orange -> add its position to BFS queue
                    rotten.push({i, j});
                }
                // If grid[i][j] == 0 (empty cell), keep vis[i][j] = 1 (already processed)
            }
        }

        int time = 0; // To count the time (in minutes) for all oranges to rot

        // Directions array to move in 4 directions: up, down, left, right
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // BFS traversal
        while (!rotten.empty())
        {

            int qSize = rotten.size(); // Number of rotten oranges to process at current level (time step)
            bool isNewRot = false;     // To check if any new orange rotted in this iteration

            // Process all oranges at current time step
            while (qSize--)
            {

                auto [i, j] = rotten.front();
                rotten.pop();

                // Explore all 4 adjacent cells
                for (auto &d : dirs)
                {

                    int ni = i + d[0]; // New row index
                    int nj = j + d[1]; // New column index

                    // Check boundaries and whether it's an unprocessed fresh orange
                    if (ni >= 0 && nj >= 0 && ni < m && nj < n && !vis[ni][nj])
                    {
                        vis[ni][nj] = 1;       // Mark as processed (rotten now)
                        rotten.push({ni, nj}); // Add to queue for next BFS level
                        isNewRot = true;       // At least one new orange rotted
                    }
                }
            }

            // Increment time if any new orange rotted in this round
            if (isNewRot)
            {
                time++;
            }
        }

        // After BFS, check if any fresh orange remains unprocessed
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (vis[i][j] == 0)
                    return -1; // Impossible to rot all oranges
            }
        }

        return time; // Minimum time required for all oranges to rot
    }


    
    //-------------------------------------------------------------------------------
    // 2. Title: Flood Fill Algorithm - Graphs
    //-------------------------------------------------------------------------------

    /**
     * Helper function: trDFS
     * Performs a DFS traversal to fill connected pixels of the same initial color with the new color.
     *
     * @param ans       The image (copy of original) being updated.
     * @param i, j      Current pixel coordinates.
     * @param color     The new color to apply.
     * @param dir       Direction array for moving up, down, left, right.
     * @param m, n      Dimensions of the image.
     * @param iniColor  The initial color of the starting pixel, used to identify connected region.
     *
     * Time Complexity: O(M * N) in the worst case (entire grid is filled).
     * Space Complexity: O(M * N) due to recursive stack in worst case (DFS).
     */
    void trDFS(vector<vector<int>> &ans, int i, int j, int color, int dir[4][2], int m, int n, int iniColor)
    {

        // Fill the current pixel with the new color
        ans[i][j] = color;

        // Explore all 4 adjacent directions
        for (int k = 0; k < 4; k++)
        {
            int p = i + dir[k][0];
            int q = j + dir[k][1];

            // Skip if the neighbor is out of bounds
            if (p < 0 || q < 0 || p >= m || q >= n)
            {
                continue;
            }

            // If the neighbor is not already colored and has the same initial color
            if (ans[p][q] != color && ans[p][q] == iniColor)
            {
                trDFS(ans, p, q, color, dir, m, n, iniColor); // Recurse for the neighbor
            }
        }
    }

    /**
     * Main function: floodFill
     * Changes the color of a region connected to (sr, sc) that has the same initial color.
     * Uses DFS to propagate the color change to all connected cells.
     *
     * @param image  The original image represented as a 2D grid.
     * @param sr, sc Starting pixel coordinates.
     * @param color  The new color to fill.
     *
     * Approach:
     *  - Copy the original image into 'ans' to avoid modifying the input.
     *  - If the starting pixel already has the target color, return the original image (no work needed).
     *  - Perform DFS from (sr, sc) to change all connected pixels of the same color.
     *
     * Time Complexity: O(M * N) because each pixel is processed at most once.
     * Space Complexity: O(M * N) for recursive stack in the worst case.
     */
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int m = image.size();
        int n = image[0].size();
        int iniColor = image[sr][sc]; // The original color of the starting cell

        // Create a copy of the image to store the result
        vector<vector<int>> ans = image;

        // Direction array for moving: left, right, up, down
        int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        // If the starting pixel already has the target color, return the original image
        if (image[sr][sc] == color)
        {
            return image;
        }

        // Start DFS from the starting pixel
        trDFS(ans, sr, sc, color, dir, m, n, iniColor);

        return ans;
    }
};

int main()
{
    return 0;
}
