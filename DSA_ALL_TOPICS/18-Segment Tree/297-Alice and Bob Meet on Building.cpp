#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*

Find Building Where Alice and Bob Can Meet

Link:
https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/


Problem statement:
You are given a 0-indexed array heights of positive integers, where heights[i] represents the height of the ith building.

If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].

You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is in building ai while Bob is in building bi.

Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.



Example 1:
Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
Output: [2,5,-1,5,2]
Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2].
In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5].
In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
In the fifth query, Alice and Bob are already in the same building.
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Example 2:
Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
Output: [7,6,-1,4,6]
Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.


Constraints:
1 <= heights.length <= 5 * 10^4
1 <= heights[i] <= 10^9
1 <= queries.length <= 5 * 10^4
queries[i] = [ai, bi]
0 <= ai, bi <= heights.length - 1

-------------------------------------------------------------------------------------------------------
*/

/**
 * ============================================================================
 * SEGMENT TREE: CONSTRAINED DESCENT (RANGE MAXIMUM QUERY)
 * ============================================================================
 * * [THE INTUITION]
 * Problem: Find the *leftmost* building strictly to the right of Bob (index > b)
 * that is strictly taller than Alice (height > heights[a]).
 * * - Why not Brute Force? Scanning rightward for every query is O(N*Q), causing TLE.
 * - Why not std::lower_bound? Binary search requires a sorted array. Sorting
 * destroys the original building indices, making the "leftmost index" rule
 * impossible to enforce cleanly online.
 * * * The Segment Tree Solution: We build a Range Maximum Tree to answer queries
 * online. Instead of just returning the maximum value in a range, we perform a
 * "Descent" (binary searching the tree itself). We use a Dual-Pruning strategy:
 * 1. Index Bounds: Is this node's segment inside our valid window [b + 1, n - 1]?
 * 2. Value Bounds: Is the absolute tallest building here > Alice's height?
 * * If both are true, we dive into the tree, always prioritizing the LEFT child
 * to guarantee we find the minimum possible index. If either check fails, we
 * prune the entire sub-tree in O(1) time.
 * * * [COMPLEXITY ANALYSIS]
 * - Time Complexity:
 * * Build: O(N) -> We visit each node exactly once bottom-up.
 * * Query: O(log N) -> The pruning strategy guarantees we bound our search
 * and only traverse down a valid path.
 * * Total Time: O(N + Q log N) where Q is the number of queries.
 * - Space Complexity:
 * * Tree: O(N) -> We allocate a flat vector of size 4*N to represent the tree.
 * * Recursion Stack: O(log N) depth.
 * * Total Space: O(N)
 * ============================================================================
 */
class SegmentTree
{
private:
    vector<int> tree;
    int n;

    // Standard Range Maximum Query Build
    void buildTree(int node, int start, int end, const vector<int> &heights)
    {
        if (start == end)
        {
            tree[node] = heights[start];
            return;
        }
        int mid = start + (end - start) / 2;
        buildTree(2 * node + 1, start, mid, heights);
        buildTree(2 * node + 2, mid + 1, end, heights);

        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

public:
    SegmentTree(int n, const vector<int> &heights)
    {
        this->n = n;
        tree.assign(4 * n, 0);
        buildTree(0, 0, n - 1, heights);
    }

    /**
     * @param L: The minimum index we are allowed to search from (Bob's index + 1)
     * @param R: The maximum index (n - 1)
     * @param target: The height we must strictly exceed (Alice's height)
     * @return The leftmost index satisfying the conditions, or -1 if none exists.
     */
    int queryLeftmost(int node, int start, int end, int L, int R, int target)
    {
        // PRUNING 1: Out of Bounds
        // If this node's segment is completely outside our valid [L, R] window, prune.
        if (start > R || end < L)
        {
            return -1;
        }

        // PRUNING 2: Capacity Check
        // If the absolute tallest building in this segment is too short, prune.
        if (tree[node] <= target)
        {
            return -1;
        }

        // BASE CASE: We survived pruning and hit a leaf node. This is our answer.
        if (start == end)
        {
            return start;
        }

        int mid = start + (end - start) / 2;

        // PRIORITY 1: Always try the LEFT branch first to satisfy "leftmost" building
        int leftResult = queryLeftmost(2 * node + 1, start, mid, L, R, target);

        // If the left branch successfully found a building, return it immediately.
        if (leftResult != -1)
        {
            return leftResult;
        }

        // PRIORITY 2: Left branch failed (either out of bounds or too short).
        // We must check the RIGHT branch.
        return queryLeftmost(2 * node + 2, mid + 1, end, L, R, target);
    }
};

class Solution
{
public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {
        int n = heights.size();
        SegmentTree segTree(n, heights);

        vector<int> ans(queries.size(), -1);

        for (int i = 0; i < queries.size(); ++i)
        {
            int a = queries[i][0];
            int b = queries[i][1];

            // Standardize: Force 'a' to be the person on the left
            if (a > b)
            {
                swap(a, b);
            }

            // Case 1 & 2: Same building, or Alice can jump directly to Bob
            if (a == b || heights[a] < heights[b])
            {
                ans[i] = b;
            }
            // Case 3: Alice is taller or equal to Bob.
            // They must meet at some index strictly > b, and height strictly > heights[a].
            else
            {
                ans[i] = segTree.queryLeftmost(0, 0, n - 1, b + 1, n - 1, heights[a]);
            }
        }

        return ans;
    }
};

int main()
{

    return 0;
}