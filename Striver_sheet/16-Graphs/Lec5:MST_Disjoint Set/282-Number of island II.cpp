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

1. Title: Number of Islands - II - Online Queries - DSU: G-51

Links:
https://takeuforward.org/graph/number-of-islands-ii-online-queries-dsu-g-51/
https://www.youtube.com/watch?v=Rn6B-Q4SNyA
https://takeuforward.org/plus/dsa/problems/number-of-islands-ii?tab=editorial
https://www.naukri.com/code360/problems/number-of-islands-ii_1266048?leftPanelTabValue=PROBLEM


Problem statement:
Given n, m denoting the row and column of the 2D matrix, and an array A of size k denoting the number of operations. Matrix elements are 0 if there is water or 1 if there is land. Originally, the 2D matrix is all 0 which means there is no land in the matrix. The array has k operator(s) and each operator has two integers A[i][0], A[i][1] means that you can change the cell matrix[A[i][0]][A[i][1]] from sea to island. Return how many islands are there in the matrix after each operation.
The answer array will be of size k.

Examples:
    Input: n = 4, m = 5, k = 4, A = [[1,1],[0,1],[3,3],[3,4]]
    Output: [1, 1, 2, 2]
    Explanation: The following illustration is the representation of the operation:
    Input: n = 4, m = 5, k = 12, A = [[0,0],[0,0],[1,1],[1,0],[0,1],[0,3],[1,3],[0,4], [3,2], [2,2],[1,2], [0,2]]

    Output: [1, 1, 2, 1, 1, 2, 2, 2, 3, 3, 1, 1]
    Explanation: If we follow the process like in example 1, we will get the above result.

Constraints:
      1 <= n, m <= 1000
      1 <= k <= 104
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
// 1. Title: Accounts Merge - DSU: G-50
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
    };

    // ------------------------------------------------------------------------
    // Utility: Boundary check for grid indices
    // ------------------------------------------------------------------------
    bool isIdxVal(int x, int y, int n, int m)
    {
        return !(x < 0 || x >= n || y < 0 || y >= m);
    }

    // ------------------------------------------------------------------------
    // Problem: Number of Islands II (Dynamic)
    // Intuition:
    // - We start with an empty water grid (n x m).
    // - Each query converts a cell (x, y) from water ? land.
    // - Each land cell can be seen as a DSU node: nodeId = x*m + y.
    // - Initially, every new land cell forms a new island (compCount++).
    // - If it touches existing land neighbors, merge them using DSU.
    // - Each successful merge reduces island count by 1.
    // - After each query, store the current island count.
    //
    // Approach:
    // 1. Initialize DSU with n*m nodes (one for each cell).
    // 2. Keep a visited[][] grid to mark land cells.
    // 3. For each query (x, y):
    //    - If already land ? skip.
    //    - Else, mark as land, increment compCount.
    //    - For each of its 4 neighbors (up, down, left, right):
    //        - If neighbor is land and belongs to a different DSU component:
    //            - Merge sets (UBS).
    //            - Decrement compCount.
    //    - Push current compCount into result.
    // 4. Return result after all queries.
    //
    // Complexity:
    // - For K queries, each processes 4 neighbors.
    // - Each union/find: O(?(n*m)) ? O(1).
    // - Total: O(K * 4?) ? O(K).
    // - Space: O(n*m) for DSU + visited, O(K) for result.
    // ------------------------------------------------------------------------
    vector<int> numOfIslandsII(int n, int m, vector<vector<int>> &q)
    {
        int nodes = n * m;                                              // total possible cells
        DJS DS(nodes);                                                  // DSU for all cells
        vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 directions
        vector<vector<int>> vis(n, vector<int>(m, 0));                  // visited grid

        vector<int> ans;
        int compCount = 0; // number of islands so far

        for (auto &cord : q)
        {
            int x = cord[0];
            int y = cord[1];

            if (vis[x][y] == 1)
            {
                // Already land ? skip, just push current island count
                ans.push_back(compCount);
                continue;
            }

            // Step 1: Convert (x, y) ? land
            vis[x][y] = 1;
            compCount++; // new island assumed

            // Step 2: Try merging with neighbors
            for (int k = 0; k < 4; k++)
            {
                int x_k = x + delta[k][0];
                int y_k = y + delta[k][1];

                if (isIdxVal(x_k, y_k, n, m) && vis[x_k][y_k] == 1)
                {
                    int u = (x * m) + y;     // current cell's node ID
                    int v = (x_k * m) + y_k; // neighbor's node ID

                    if (DS.fUP(u) != DS.fUP(v))
                    {
                        DS.UBS(u, v); // merge two islands
                        compCount--;  // merged ? reduce island count
                    }
                }
            }

            // Step 3: Record current island count
            ans.push_back(compCount);
        }

        return ans;
    }
};

int main()
{
    return 0;
}