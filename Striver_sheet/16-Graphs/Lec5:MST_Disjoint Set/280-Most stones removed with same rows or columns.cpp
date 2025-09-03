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

1. Title: Most Stones Removed with Same Row or Column - DSU: G-53
Links:
https://takeuforward.org/data-structure/most-stones-removed-with-same-row-or-column-dsu-g-53/
https://www.youtube.com/watch?v=OwMNX8SPavM
https://takeuforward.org/plus/dsa/problems/most-stones-removed-with-same-row-or-column?tab=editorial
https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/


Problem statement:
On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.

Examples:
    Example 1:
    Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
    Output: 5
    Explanation: One way to remove 5 stones is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,1].
    2. Remove stone [2,1] because it shares the same column as [0,1].
    3. Remove stone [1,2] because it shares the same row as [1,0].
    4. Remove stone [1,0] because it shares the same column as [0,0].
    5. Remove stone [0,1] because it shares the same row as [0,0].
    Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.

    Example 2:
    Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
    Output: 3
    Explanation: One way to make 3 moves is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,0].
    2. Remove stone [2,0] because it shares the same column as [0,0].
    3. Remove stone [0,2] because it shares the same row as [0,0].
    Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.

    Example 3:
    Input: stones = [[0,0]]
    Output: 0
    Explanation: [0,0] is the only stone on the plane, so you cannot remove it.


Constraints:
    1 <= stones.length <= 1000
    0 <= xi, yi <= 104
    No two stones are at the same coordinate point.



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
// 1. Title: Most Stones Removed with Same Row or Column - DSU: G-53
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Disjoint Set (Union-Find) with Union by Size + Path Compression
    // ------------------------------------------------------------------------
    class Disjoint
    {
    private:
        vector<int> p, size; // parent array, size array
    public:
        // Constructor: O(N)
        Disjoint(int n)
        {
            p.resize(n);
            size.resize(n, 1);
            for (int i = 0; i < n; i++)
                p[i] = i; // initially each node is its own parent
        }

        // Find with Path Compression: Amortized O(α(N)) ≈ O(1)
        int findUPar(int u)
        {
            if (u == p[u])
                return u;
            return p[u] = findUPar(p[u]); // compress path
        }

        // Union by Size: Amortized O(α(N)) ≈ O(1)
        void UbyS(int u, int v)
        {
            int u_p = findUPar(u);
            int v_p = findUPar(v);

            if (u_p == v_p)
                return; // already in same set

            // attach smaller set to larger set
            if (size[u_p] < size[v_p])
            {
                p[u_p] = v_p;
                size[v_p] += size[u_p];
            }
            else
            {
                p[v_p] = u_p;
                size[u_p] += size[v_p];
            }
        }
    };

    // ------------------------------------------------------------------------
    // Problem: Most Stones Removed with Same Row or Column (LC 947)
    // Intuition:
    // - Stones can be removed if they share a row or column with another stone.
    // - Model each row and column as a node in a graph.
    // - Union (row, col) for each stone → stones in same row/col belong to same component.
    // - Number of removable stones = total stones - number of connected components.
    //
    // Complexity:
    // - Finding max dimension: O(stCount)
    // - Union operations: O(stCount * α(N)) ≈ O(stCount)
    // - Counting components: O(stCount), since only active nodes are checked
    // - Overall: O(stCount + α(N)) ≈ O(stCount)
    //   where:
    //      stCount = number of stones
    //      N = total DSU nodes = rows + cols
    // ------------------------------------------------------------------------
    int removeStones(vector<vector<int>> &stones)
    {

        int stCount = stones.size();    // number of stones
        int maxDim = 0;                 // track maximum coordinate among rows/cols
        int compCount = 0;              // number of connected components
        unordered_set<int> stoneKeeper; // keeps track of all nodes used (rows+cols)

        // --------------------------------------------------------------------
        // Step 1: Find maximum row/col index (for DSU size allocation)
        // Complexity: O(stCount)
        // --------------------------------------------------------------------
        for (auto &st : stones)
        {
            maxDim = max({maxDim, st[0], st[1]});
        }

        int rows = (maxDim + 1); // number of row nodes
        int cols = (maxDim + 1); // number of column nodes
        int nodes = rows + cols; // total nodes (rows + cols)
        Disjoint DS(nodes);

        // --------------------------------------------------------------------
        // Step 2: Union row node and col node for each stone
        // Each stone connects its row index and col index
        // Complexity: O(stCount * α(N))
        // --------------------------------------------------------------------
        for (auto &st : stones)
        {
            int u = st[0];        // row node
            int v = rows + st[1]; // column node (shifted to avoid overlap with row indices)
            DS.UbyS(u, v);
            stoneKeeper.insert(u);
            stoneKeeper.insert(v);
        }

        // --------------------------------------------------------------------
        // Step 3: Count number of connected components among active nodes
        // Only check the nodes that were actually used by stones.
        // Complexity: O(stCount) (reduced by stoneKeeper).
        // --------------------------------------------------------------------
        for (auto &it : stoneKeeper)
        {
            if (DS.findUPar(it) == it)
            {
                compCount++;
            }
        }

        // --------------------------------------------------------------------
        // Step 4: Answer = total stones - number of connected components
        // Because in each connected component, we can remove all stones except 1.
        // --------------------------------------------------------------------
        return stCount - compCount;
    }
};

int main()
{
    return 0;
}