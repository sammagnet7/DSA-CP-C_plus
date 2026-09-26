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

1. Title: Most Stones Removed with Same Row or Column - DSU
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
    0 <= xi, yi <= 10^4
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
// 1. Title: Most Stones Removed with Same Row or Column - DSU
//-------------------------------------------------------------------------------
//

//============================================================================
// Helper Class — Disjoint Set Union (Vector Variant for Grid Offsets)
//============================================================================
class DSU
{
    vector<int> parent, size;
    int components;

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
    DSU(int n, int nodesCount)
    {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }

        // Initialize components to exactly the number of unique rows/cols present
        components = nodesCount;
    }

    void dunion(int u, int v)
    {
        int pu = getPar(u);
        int pv = getPar(v);

        // If they already share the same root, do nothing
        if (pu == pv)
        {
            return;
        }

        // A successful merge reduces the number of isolated networks by 1
        --components;

        int su = size[pu];
        int sv = size[pv];

        // Union by Size
        if (su <= sv)
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

    int getComponents()
    {
        return components;
    }
};

/**
 * @class Solution
 * @brief Solves the "Most Stones Removed with Same Row or Column" problem using DSU.
 *
 * ============================================================================
 * 🧠 INTUITION & APPROACH: The Bipartite Graph Trick
 * ============================================================================
 * * Step 1: Rethink the Graph (Nodes vs. Edges)
 * - Instead of treating the STONES as the nodes in our graph, we treat the
 * ROWS and COLUMNS as the nodes.
 * - A stone placed at coordinate (r, c) is simply an EDGE that connects
 * "Row Node r" to "Column Node c".
 * * Step 2: Coordinate Offsetting (Preventing Collisions)
 * - If we have a stone at (5, 5), how does our 1D DSU array know the difference
 * between "Row 5" and "Column 5"? They would collide at index 5!
 * - Since the constraints state coordinates go up to 10,000, we OFFSET all
 * Y-coordinates (columns) by 10,001.
 * - Now, "Row 5" is index 5, and "Column 5" is safely mapped to index 10006.
 * * Step 3: Network Building (Connected Components)
 * - We iterate through every stone and union its Row and its Column.
 * - If multiple stones share the same row or column, the DSU will chain them
 * together into a single, massive connected network (Component).
 * * Step 4: The Mathematical Deduction
 * - In any connected network of stones, the rules allow us to systematically
 * remove stones like a collapsing domino chain until exactly ONE stone remains.
 * - This final surviving stone has no more connections and cannot be removed.
 * - Therefore, the maximum number of stones we can remove across the entire board is:
 * [Total Number of Stones] - [Number of Isolated Networks (Components)]
 * * Step 5: The DSU Pre-Counting Optimization
 * - We don't want our DSU to count empty rows/cols as components.
 * - We first loop through the stones and dump all used X and Y (offset)
 * coordinates into an unordered_set. The size of this set tells us EXACTLY
 * how many active Row/Col nodes exist.
 * - We initialize the DSU component tracker with this exact count, and every
 * valid union dynamically subtracts 1 from it.
 * * ============================================================================
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) where N is the number of stones. Creating the set
 * takes O(N). Processing stones through DSU takes ~O(1) amortized time per stone.
 * - Space Complexity: O(N + MaxCoordinate). The set takes O(N), and the DSU
 * arrays take a fixed size of 20,002 elements (~160 KB), which is extremely
 * cache-friendly and memory efficient.
 */
class Solution
{
    int offset = 1e4 + 1;

public:
    int removeStones(vector<vector<int>> &stones)
    {

        int totalStoneCount = stones.size();

        // 1. Pre-count exactly how many unique rows and columns contain at least one stone
        unordered_set<int> coordinates;

        for (auto &stone : stones)
        {
            int x = stone[0];
            int y = offset + stone[1];

            coordinates.insert(x);
            coordinates.insert(y);
        }

        int nodesCount = coordinates.size();

        // 2. Initialize DSU. Max size is 2 * offset (20002) to cover all valid indices.
        DSU dsu((2 * offset), nodesCount);

        // 3. Group the networks by bridging the row and the column of each stone
        for (auto &stone : stones)
        {
            int x = stone[0];
            int y = offset + stone[1];

            dsu.dunion(x, y);
        }

        // 4. Mathematical formulation: Total Stones - Number of isolated survivor components
        int componentsCount = dsu.getComponents();

        return totalStoneCount - componentsCount;
    }
};

int main()
{
    return 0;
}