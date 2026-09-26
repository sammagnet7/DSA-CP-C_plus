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


*/

//-------------------------------------------------------------------------------
// 1. Title: Flood Fill Algorithm - Graphs
//-------------------------------------------------------------------------------

//-------------------------------
//  Approach 1: Single-Source BFS  [RECOMMENDED]
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
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
