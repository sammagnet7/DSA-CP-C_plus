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
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
