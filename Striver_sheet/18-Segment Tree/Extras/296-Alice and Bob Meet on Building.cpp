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

*/

//-------------------------------------------------------------------------------
//
// APPROACH 1 : Segment Tree  + Binary search [Q * (Log N)^2] [sub-optimal]
//
//-------------------------------------------------------------------------------

/*
 * Problem: 2940. Find Building Where Alice and Bob Can Meet
 * ---------------------------------------------------------
 *
 * Approach: Segment Tree (Range Maximum Query) + Binary Search
 *
 * Core Concept:
 * 1. If Alice (index 'a') can directly jump to Bob (index 'b'), we are done.
 * 2. If not, we need to find the *leftmost* building 'k' such that:
 * - k > max(a, b)   (The building is to the right of both)
 * - heights[k] > heights[a] AND heights[k] > heights[b]
 *
 * Data Structure:
 * We use a Segment Tree to store the INDEX of the maximum height in a range.
 * Storing indices allows us to look up the height value and position simultaneously.
 *
 * Algorithm Steps:
 * 1. Build a Segment Tree over the 'heights' array.
 * 2. For each query (a, b):
 * - Sort a, b so a <= b.
 * - Check basic cases (a==b or heights[b] > heights[a]).
 * - If basic cases fail, we need to search in range [b+1, N-1].
 * - We perform a Binary Search on the range [b+1, N-1].
 * - Inside the binary search, we query the Segment Tree to see if a valid
 * building exists in the left half of the current search window.
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N + Q * log^2 N)
 * - Build Tree: O(N)
 * - Per Query: We do a Binary Search (log N steps).
 * Inside each step, we query the Segment Tree (log N steps).
 * Total per query: O(log N * log N) = O(log^2 N).
 * - Total: With N, Q = 5*10^4, ~1.2*10^7 operations. Fits well within 1s limit.
 *
 * Space Complexity: O(4 * N)
 * - Used for the Segment Tree array.
 */
class Solution
{
private:
    // Segment Tree stores indices of the maximum elements
    vector<int> segT;
    int N;

    /*
     * Method: buildTree
     * -----------------
     * Recursively builds the Segment Tree.
     * segT[node] will store the INDEX of the maximum height in range [l, r].
     * * Time: O(N)
     */
    void buildTree(int l, int r, int segI, vector<int> &heights)
    {

        // Base Case: Leaf Node
        if (l == r)
        {
            segT[segI] = l; // Store the index itself
            return;
        }

        int mid = l + (r - l) / 2;

        // Recursive Build
        buildTree(l, mid, 2 * segI + 1, heights);
        buildTree(mid + 1, r, 2 * segI + 2, heights);

        // Merge Logic:
        // We compare the HEIGHTS at the indices stored in children.
        // We pick the index corresponding to the greater height.
        int leftMaxIdx = segT[2 * segI + 1];
        int rightMaxIdx = segT[2 * segI + 2];

        int leftMaxVal = heights[leftMaxIdx];
        int rightMaxVal = heights[rightMaxIdx];

        // Store the index of the larger value
        segT[segI] = (leftMaxVal >= rightMaxVal) ? leftMaxIdx : rightMaxIdx;
    }

    /*
     * Method: findMaxInRange
     * ----------------------
     * Standard Range Maximum Query (RMQ).
     * Returns the INDEX of the maximum height in [rangeL, rangeR].
     * * Time: O(log N)
     */
    int findMaxInRange(int l, int r, int rangeL, int rangeR, int segI, vector<int> &heights)
    {

        // Case 1: Full Overlap
        if (rangeL <= l && r <= rangeR)
        {
            return segT[segI];
        }

        // Case 2: No Overlap
        else if (rangeR < l || r < rangeL)
        {
            return -1;
        }

        // Case 3: Partial Overlap
        int mid = l + (r - l) / 2;

        int lI = findMaxInRange(l, mid, rangeL, rangeR, 2 * segI + 1, heights);
        int rI = findMaxInRange(mid + 1, r, rangeL, rangeR, 2 * segI + 2, heights);

        if (lI == -1)
            return rI;
        if (rI == -1)
            return lI;

        // Compare heights at the retrieved indices to decide the winner
        if (heights[lI] >= heights[rI])
        {
            return lI;
        }
        else
        {
            return rI;
        }
    }

    /*
     * Method: getHigherClosestOnRight
     * -------------------------------
     * Finds the leftmost index 'k' in [rangeL, rangeR] such that heights[k] > lowerLimit.
     * * Strategy: Binary Search on the answer.
     * We keep narrowing the window. If the left half of our current window contains
     * a number > lowerLimit, we try to find the answer there (move left).
     * Otherwise, we are forced to look in the right half.
     * * Time: O(log^2 N)
     */
    int getHigherClosestOnRight(int rangeL, int rangeR, int lowerLimit, vector<int> &heights)
    {

        int closestAns = -1;

        // Binary Search Loop: O(log N) iterations
        while (rangeL <= rangeR)
        {

            int mid = rangeL + (rangeR - rangeL) / 2;

            // Query Segment Tree for max index in [rangeL, mid]
            // This query takes O(log N)
            int leftMaxIdx = findMaxInRange(0, N - 1, rangeL, mid, 0, heights);

            // Safety check although leftMaxIdx shouldn't be -1 given valid loop bounds
            int leftMaxVal = (leftMaxIdx != -1) ? heights[leftMaxIdx] : -1;

            // Decision:
            // If the max value in the left half [rangeL, mid] is greater than our limit,
            // it means a valid meeting place EXISTS in this left half.
            if (lowerLimit < leftMaxVal)
            {
                // Found a candidate!
                closestAns = leftMaxIdx;

                // Try to find a "closer" (more left) one by ignoring the right half
                rangeR = mid - 1;
            }
            else
            {
                // No valid building in [rangeL, mid].
                // We MUST search in the right half [mid+1, rangeR].
                rangeL = mid + 1;
            }
        }

        return closestAns;
    }

public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {

        N = heights.size();

        // 4*N Allocation for Segment Tree safety
        segT.resize(4 * N);

        // O(N) Build
        buildTree(0, N - 1, 0, heights);

        vector<int> ans;

        // Process Queries
        for (int i = 0; i < queries.size(); i++)
        {

            int ai = queries[i][0];
            int bi = queries[i][1];

            int ansi = -1;

            // Normalize indices
            int lefti = min(ai, bi);
            int righti = max(ai, bi);

            // Case A: Alice and Bob are at the same building
            if (lefti == righti)
            {
                ansi = lefti;
            }
            // Case B: The person at the left building can jump directly to the right building
            // (Because the destination is strictly higher)
            else if (heights[lefti] < heights[righti])
            {
                ansi = righti;
            }
            // Case C: Indirect Jump required
            else
            {
                // We need a building 'k' > righti
                // Such that heights[k] > heights[lefti]
                // (Since heights[lefti] >= heights[righti], checking > heights[lefti] suffices)
                int lowerLimit = heights[lefti];

                // Perform Binary Search + RMQ on range [righti + 1, End]
                //
                ansi = getHigherClosestOnRight(righti + 1, N - 1, lowerLimit, heights);
            }

            ans.push_back(ansi);
        }

        return ans;
    }
};

//--------------------------------------------------
//
// APPROACH 2 : Segment Tree [Q * Log N] [OPTIMAL]
//
//--------------------------------------------------

/*
 * Problem: 2940. Find Building Where Alice and Bob Can Meet
 * ---------------------------------------------------------
 *
 * Approach: Segment Tree Descent (Find First Element > X in Range)
 *
 * Core Concept:
 * 1. If Alice (index 'a') can directly jump to Bob (index 'b'), we are done.
 * 2. If not, we need to find the *leftmost* building 'k' such that:
 * - k > max(a, b)   (The building is to the right of both)
 * - heights[k] > heights[a] AND heights[k] > heights[b]
 *
 * Data Structure:
 * We use a Segment Tree where each node stores the INDEX of the maximum height
 * in its range. This allows us to check the max height of any range quickly.
 *
 * Algorithm Steps:
 * 1. Build a Segment Tree over the 'heights' array.
 * 2. For each query (a, b), normalize so a <= b.
 * 3. Handle simple cases (a==b or direct jump possible).
 * 4. For the complex case, we need to find the first building in range [b+1, N-1]
 * that is strictly taller than heights[a].
 * 5. Instead of Binary Search (which is O(log^2 N)), we use a recursive Segment Tree Walk.
 * We prune branches where max_height <= limit, and always prioritize the Left Child
 * to guarantee finding the leftmost index.
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N + Q * log N)
 * - Build Tree: O(N)
 * - Per Query: We descend the tree once. The "pruning" ensures we visit at most O(log N) nodes.
 * Total per query: O(log N).
 * - Total: Much faster than the binary search approach.
 *
 * Space Complexity: O(4 * N)
 * - Used for the Segment Tree array.
 */

class Solution
{
private:
    // Segment Tree stores indices of the maximum elements
    vector<int> segT;
    int N;

    /*
     * Method: buildTree
     * -----------------
     * Recursively builds the Segment Tree.
     * segT[node] will store the INDEX of the maximum height in range [l, r].
     * * Time: O(N)
     */
    void buildTree(int l, int r, int segI, vector<int> &heights)
    {

        // Base Case: Leaf Node
        if (l == r)
        {
            segT[segI] = l; // Store the index itself
            return;
        }

        int mid = l + (r - l) / 2;

        // Recursive Build
        buildTree(l, mid, 2 * segI + 1, heights);
        buildTree(mid + 1, r, 2 * segI + 2, heights);

        // Merge Logic:
        // We compare the HEIGHTS at the indices stored in children.
        // We pick the index corresponding to the greater height.
        int leftMaxIdx = segT[2 * segI + 1];
        int rightMaxIdx = segT[2 * segI + 2];

        int leftMaxVal = heights[leftMaxIdx];
        int rightMaxVal = heights[rightMaxIdx];

        // Store the index of the larger value
        segT[segI] = (leftMaxVal >= rightMaxVal) ? leftMaxIdx : rightMaxIdx;
    }

    /*
     * Method: getHigherClosestOnRight
     * -------------------------------
     * Finds the leftmost index 'k' in [rangeL, rangeR] such that heights[k] > lowerLimit.
     * * Strategy: Segment Tree Descent (Walk)
     * - Pruning: If max height in current node <= lowerLimit, stop searching (return -1).
     * - Greedy: Always try Left Child first. If found, return immediately. Else, try Right Child.
     * * Time Complexity: O(log N)
     */
    int getHigherClosestOnRight(int l, int r, int segI, int rangeL, int rangeR, int lowerLimit, vector<int> &heights)
    {

        // 1. Range Check: Completely outside the query range
        if (r < rangeL || rangeR < l)
        {
            return -1;
        }

        // 2. Pruning Optimization (CRITICAL)
        // If the max height in this current node range is not strictly greater
        // than the limit, there is no point searching here.
        if (heights[segT[segI]] <= lowerLimit)
        {
            return -1;
        }

        // 3. Base Case: Leaf Node
        // Since we passed the pruning check, we know heights[l] > lowerLimit.
        if (l == r)
        {
            return segT[segI];
        }

        int mid = l + (r - l) / 2;

        int leftSegI = 2 * segI + 1;
        int rightSegI = 2 * segI + 2;

        // 4. Greedy Descent
        // Try to find the answer in the Left Child first (Leftmost priority).
        int leftClosestI = getHigherClosestOnRight(l, mid, leftSegI, rangeL, rangeR, lowerLimit, heights);

        // If found in Left, return it immediately.
        if (leftClosestI != -1)
        {
            return leftClosestI;
        }
        else
        {
            // Otherwise, search in the Right Child.
            return getHigherClosestOnRight(mid + 1, r, rightSegI, rangeL, rangeR, lowerLimit, heights);
        }
    }

public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {

        N = heights.size();

        // 4*N Allocation for Segment Tree safety
        segT.resize(4 * N);

        // O(N) Build
        buildTree(0, N - 1, 0, heights);

        vector<int> ans;

        // Process Queries
        for (int i = 0; i < queries.size(); i++)
        {

            int ai = queries[i][0];
            int bi = queries[i][1];

            int ansi = -1;

            // Normalize indices so we always look from left to right
            int lefti = min(ai, bi);
            int righti = max(ai, bi);

            // Case A: Alice and Bob are at the same building
            if (lefti == righti)
            {
                ansi = lefti;
            }
            // Case B: The person at the left building can jump directly to the right building
            // (Because the destination is strictly higher)
            else if (heights[lefti] < heights[righti])
            {
                ansi = righti;
            }
            // Case C: Indirect Jump required
            else
            {
                // We need a building 'k' > righti
                // Such that heights[k] > heights[lefti]
                int lowerLimit = heights[lefti];

                // Perform Segment Tree Walk on range [righti + 1, N-1]
                // This finds the first valid index in O(log N) time.
                ansi = getHigherClosestOnRight(0, N - 1, 0, righti + 1, N - 1, lowerLimit, heights);
            }

            ans.push_back(ansi);
        }

        return ans;
    }
};

int main()
{

    return 0;
}