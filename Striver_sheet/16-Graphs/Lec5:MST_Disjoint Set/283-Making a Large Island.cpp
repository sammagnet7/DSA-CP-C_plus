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

1. Title: Making a Large Island - DSU: G-52

Links:
https://takeuforward.org/data-structure/making-a-large-island-dsu-g-52/
https://www.youtube.com/watch?v=lgiz0Oup6gM
https://takeuforward.org/plus/dsa/problems/making-a-large-island?tab=editorial
https://leetcode.com/problems/making-a-large-island/description/


Problem statement:
You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
Return the size of the largest island in grid after applying this operation.
An island is a 4-directionally connected group of 1s.

Examles:
    Example 1:
    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

    Example 2:
    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

    Example 3:
    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.


Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 500
    grid[i][j] is either 0 or 1.


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
// 1. Title: Making a Large Island - DSU: G-52
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Disjoint Set (Union-Find) with Union by Size + Path Compression
    // ------------------------------------------------------------------------
    class DJS
    {
    public:
        vector<int> p, s; // parent array, size array

        // Constructor
        // Initialize DSU with n nodes, each node is its own parent
        // Complexity: O(n)
        DJS(int n)
        {
            p.resize(n);
            s.resize(n, 1); // each set starts with size = 1
            for (int i = 0; i < n; i++)
            {
                p[i] = i; // parent of itself
            }
        }

        // Find ultimate parent with path compression
        // Complexity: Amortized O(?(n)) ? O(1)
        int fUP(int u)
        {
            if (u == p[u])
                return u;
            return p[u] = fUP(p[u]); // compress path
        }

        // Check if two nodes belong to the same set
        bool isSame(int u, int v)
        {
            return (fUP(u) == fUP(v));
        }

        // Union by Size
        // Attach smaller set to larger set
        // Complexity: Amortized O(?(n))
        void UBS(int u, int v)
        {
            int pu = fUP(u);
            int pv = fUP(v);

            if (pu == pv)
                return; // already connected

            if (s[pu] < s[pv])
            {
                p[pu] = pv;
                s[pv] += s[pu];
            }
            else
            {
                p[pv] = pu;
                s[pu] += s[pv];
            }
        }

        int getSize(int node)
        {
            return s[node];
        }
    };

    // ------------------------------------------------------------------------
    // Utility: Boundary check for grid indices
    // ------------------------------------------------------------------------
    bool isIdxVal(int x, int y, int row, int col)
    {
        return !(x < 0 || x >= row || y < 0 || y >= col);
    }

    // ------------------------------------------------------------------------
    // Problem: Making A Large Island (LC 827)
    //
    // Intuition:
    // - The grid contains islands (connected 1s).
    // - We are allowed to flip at most one 0 → 1.
    // - Goal: find the size of the largest island possible after one flip.
    //
    // Understanding:
    // - Model each cell (i, j) as a DSU node: nodeId = i * n + j.
    // - First, union all connected 1s to form initial islands.
    // - Then, for each 0 cell:
    //     - Pretend to flip it → check its 4 neighbors.
    //     - Collect unique neighboring island parents.
    //     - Potential island size = 1 (flipped cell) + sum of neighbor sizes.
    //     - Track maximum.
    // - Edge case: if no 0 exists, the entire grid is already 1s → answer is n*n.
    //
    // Approach:
    // 1. Build DSU for all land cells (union adjacent 1s).
    // 2. Traverse each 0 cell:
    //     - Use set to avoid counting same island twice.
    //     - Compute merged island size.
    // 3. Return max island size found.
    //
    // Complexity:
    // - Building DSU: O(N^2 * 4α) ≈ O(N^2)
    // - Evaluating each 0: O(N^2 * 4) ≈ O(N^2)
    // - Total: O(N^2)
    // - Space: O(N^2) for DSU parent/size arrays.
    // ------------------------------------------------------------------------
    int largestIsland(vector<vector<int>> &grid)
    {
        int n = grid.size();
        DJS DS(n * n);                                                  // DSU for n*n cells
        vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 directions

        // Step 1: Union all adjacent land cells to form initial islands
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                    continue; // skip water

                for (int k = 0; k < 4; k++)
                {
                    int i_k = i + delta[k][0];
                    int j_k = j + delta[k][1];

                    if (isIdxVal(i_k, j_k, n, n) && grid[i_k][j_k] == 1)
                    {
                        int u = i * n + j;
                        int v = i_k * n + j_k;
                        DS.UBS(u, v);
                    }
                }
            }
        }

        bool isModified = false; // whether at least one 0 exists
        int maxCompSize = 0;

        // Step 2: Try flipping each 0 → compute potential island size
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                    continue; // skip existing land

                isModified = true;
                unordered_set<int> parents; // store unique island parents
                int compSize = 1;           // count flipped cell itself

                for (int k = 0; k < 4; k++)
                {
                    int i_k = i + delta[k][0];
                    int j_k = j + delta[k][1];

                    if (isIdxVal(i_k, j_k, n, n) && grid[i_k][j_k] == 1)
                    {
                        int v = i_k * n + j_k;
                        int v_p = DS.fUP(v); // ultimate parent
                        if (parents.find(v_p) == parents.end())
                        {
                            compSize += DS.getSize(v_p);
                            parents.insert(v_p);
                        }
                    }
                }

                maxCompSize = max(maxCompSize, compSize);
            }
        }

        // Step 3: Handle edge case — grid already full of 1s
        if (!isModified)
            return n * n;

        return maxCompSize;
    }
};

int main()
{
    return 0;
}