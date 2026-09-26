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

1. Title: Number of Islands - II - Online Queries

Links:
https://takeuforward.org/graph/number-of-islands-ii-online-queries-dsu-g-51/
https://www.youtube.com/watch?v=Rn6B-Q4SNyA
https://takeuforward.org/plus/dsa/problems/number-of-islands-ii?tab=editorial
https://leetcode.com/problems/number-of-islands-ii/description/
https://www.naukri.com/code360/problems/number-of-islands-ii_1266048


Problem statement:
You have a 2D grid of ‘N’ rows and ‘M’ columns which are initially filled with water i.e. all 0s. You are given ‘Q’ queries each consisting of two integers ‘X’ and ‘Y’ and in each query operation, you have to turn the water at position (‘X’, ‘Y’) into a land. You are supposed to find the number of islands in the grid after each query.
The query/answer array will be of size k.

An island is a group of lands surrounded by water horizontally, vertically.
You may assume all four edges of the grid are all surrounded by water.

Examples:
    Input: n = 4, m = 5, q = [[1,1],[0,1],[3,3],[3,4]]
    Output: [1, 1, 2, 2]

    Input: n = 4, m = 5, q = [[0,0],[0,0],[1,1],[1,0],[0,1],[0,3],[1,3],[0,4], [3,2], [2,2],[1,2], [0,2]]
    Output: [1, 1, 2, 1, 1, 2, 2, 2, 3, 3, 1, 1]


Constraints:
      1 <= n, m <= 1000
      1 <= k <= 10^4
      0 <= A[i][0] < n
      0 <= A[i][1] < m


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
// 1. Title: Number of Islands - II - Online Queries
//-------------------------------------------------------------------------------
//

// ------------------------------------------------------------------------
// Approach 1: Disjoint Set + Visited matrix
// ------------------------------------------------------------------------

class Solution
{

    //============================================================================
    // Helper Class — Disjoint Set Union (Union-Find)
    //============================================================================
    class DSU
    {
        vector<int> parent, size;

    public:
        DSU(int n)
        {
            parent.resize(n);
            size.resize(n, 1);
            for (int i = 0; i < n; ++i)
            {
                parent[i] = i;
            }
        }

        int findPar(int i)
        {
            if (parent[i] == i)
            {
                return i;
            }
            return parent[i] = findPar(parent[i]);
        }

        void dunion(int u, int v)
        {
            int pu = findPar(u);
            int pv = findPar(v);

            if (pu == pv)
                return;

            if (size[pu] <= size[pv])
            {
                parent[pu] = pv;
                size[pv] += size[pu];
            }
            else
            {
                parent[pv] = pu;
                size[pu] += size[pv];
            }
        }
    };

public:
    //============================================================================
    // Approach — Dynamic Connectivity (2D Grid to 1D DSU)
    //============================================================================

    /**
     * @brief Dynamically calculates the number of islands after adding land step-by-step.
     *
     * Idea & Intuition:
     * - A standard BFS/DFS would require us to traverse the entire N x M grid after
     * EVERY single query. For 100,000 queries, this causes a Time Limit Exceeded (TLE).
     * - Instead, we use a Disjoint Set Union (DSU). Since DSU works on 1D arrays, we
     * "flatten" the 2D grid using the formula: Node ID = (Row * Total_Columns) + Col.
     * - Every time we place a new piece of land, we initially assume it forms a brand
     * new, isolated island (incrementing our island count).
     * - We then look at its 4 immediate neighbors. If any neighbor is already land, we
     * use our DSU to connect them. When two separate islands merge into one, we simply
     * decrement our total island count!
     *
     * Approach:
     * 1. Initialize a DSU of size (N * M) and a `visited` grid to track land.
     * 2. Loop through each query (r, c). If it's already land, record current count and skip.
     * 3. Mark (r, c) as land and increment `currentIslands`.
     * 4. Check the 4 neighbors (Up, Down, Left, Right).
     * 5. If a valid neighbor is also land, check if they belong to different components.
     * 6. If they do, `dunion` them and decrement `currentIslands` by 1.
     * 7. Store the current island count in our answer array.
     *
     * Time Complexity:
     * - O(Q * α(N * M)): Where Q is the number of queries. Checking 4 neighbors is O(1).
     * The DSU operations run in nearly O(1) amortized time. This safely bypasses TLE.
     *
     * Space Complexity:
     * - O(N * M): We require a 2D `visited` array of size N x M, and the DSU internally
     * requires 1D arrays of size (N * M) for parent and size tracking.
     */
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &q)
    {

        DSU ds(n * m);
        vector<vector<int>> visited(n, vector<int>(m, 0));

        int currentIslands = 0;
        vector<int> ans;

        // 4-directional traversal arrays (Up, Down, Left, Right)
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};

        for (auto &query : q)
        {
            int r = query[0];
            int c = query[1];

            // Edge Case: The cell is already land
            if (visited[r][c] == 1)
            {
                ans.push_back(currentIslands);
                continue;
            }

            // 1. Mark as land, assume it's an isolated island
            visited[r][c] = 1;
            currentIslands++;

            // The 1D ID for our current cell
            int currentId = r * m + c;

            // 2. Check all 4 neighbors
            for (int i = 0; i < 4; ++i)
            {
                int adjR = r + dRow[i];
                int adjC = c + dCol[i];

                // If neighbor is valid and is land
                if (adjR >= 0 && adjR < n && adjC >= 0 && adjC < m && visited[adjR][adjC] == 1)
                {

                    int adjId = adjR * m + adjC;

                    // If they belong to different components, merge them!
                    if (ds.findPar(currentId) != ds.findPar(adjId))
                    {
                        ds.dunion(currentId, adjId);

                        // Merging two isolated islands reduces the total count by 1
                        currentIslands--;
                    }
                }
            }

            // Record the dynamic island count after this query
            ans.push_back(currentIslands);
        }

        return ans;
    }
};

// ------------------------------------------------------------------------
// Approach 2: Disjoint Set as map
// ------------------------------------------------------------------------

//============================================================================
// Data Structure — Dynamic DSU (Sparse Matrix Variant)
//============================================================================
class DSU
{
private:
    // unordered_map allows us to handle incredibly massive grids (e.g., 10^9 x 10^9)
    // by only allocating memory for cells that are actually queried (O(Q) space).
    unordered_map<int, int> parent;
    unordered_map<int, int> size;
    int componentCount;

    int getPar(int i)
    {
        int p = parent[i];
        if (i == p)
        {
            return p;
        }
        // Path Compression
        return parent[i] = getPar(p);
    }

public:
    DSU()
    {
        componentCount = 0;
    }

    /**
     * @brief Dynamically adds a new piece of land to the graph.
     */
    void addNode(int pos)
    {
        // If the node already exists, this is a duplicate query. Ignore it.
        if (parent.find(pos) != parent.end())
        {
            return;
        }

        // Brand new isolated island created!
        parent[pos] = pos;
        size[pos] = 1;
        ++componentCount;
    }

    void dunion(int pos1, int pos2)
    {
        // Safety Check: If either node doesn't exist in the DSU, it means
        // that neighbor is currently WATER. We cannot merge with water.
        if (parent.find(pos1) == parent.end() || parent.find(pos2) == parent.end())
        {
            return;
        }

        int p1 = getPar(pos1);
        int p2 = getPar(pos2);

        // Already connected
        if (p1 == p2)
        {
            return;
        }

        // Successfully merging two isolated islands reduces the count by 1
        --componentCount;

        int s1 = size[p1];
        int s2 = size[p2];

        // Union by Size
        if (s1 <= s2)
        {
            parent[p1] = p2;
            size[p2] += size[p1];
        }
        else
        {
            parent[p2] = p1;
            size[p1] += size[p2];
        }
    }

    int getComponentCount()
    {
        return componentCount;
    }
};

class Solution
{
public:
    //============================================================================
    // Approach — Dynamic Connectivity using Sparse DSU
    //============================================================================

    /**
     * @brief Finds the number of islands after dynamically adding land.
     *
     * Time Complexity:
     * - O(Q * α(Q)) average time. Q is the number of queries. Hash map lookups
     * run in O(1) average time, making this vastly faster than BFS.
     *
     * Space Complexity:
     * - O(Q): We only store exactly the nodes that are queried as land. We
     * completely bypass the need for an O(N * M) visited grid!
     */
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &query)
    {

        vector<int> ans;
        DSU dsu;

        // Up, Right, Down, Left
        vector<vector<int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        for (auto &q : query)
        {
            int x = q[0];
            int y = q[1];

            // Flatten 2D coordinate into 1D ID
            int pos = (x * m) + y;

            // 1. Add the new land to the DSU
            dsu.addNode(pos);

            // 2. Look in all 4 directions for adjacent land
            for (int k = 0; k < 4; ++k)
            {
                int nx = x + dir[k][0];
                int ny = y + dir[k][1];

                // Bounds check
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                {
                    continue;
                }

                int npos = (nx * m) + ny;

                // 3. Attempt to merge. The DSU internally checks if 'npos' is valid land.
                dsu.dunion(pos, npos);
            }

            // 4. Record the current state of the board
            ans.push_back(dsu.getComponentCount());
        }

        return ans;
    }
};

int main()
{
    return 0;
}