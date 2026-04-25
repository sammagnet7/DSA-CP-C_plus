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
//
Title: Count Good Triplets in an Array

Link:
https://leetcode.com/problems/count-good-triplets-in-an-array/description/


Problem statement:
You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of [0, 1, ..., n - 1].

A good triplet is a set of 3 distinct values which are present in increasing order by position both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z) where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.

Return the total number of good triplets.


Example 1:
Input: nums1 = [2,0,1,3], nums2 = [0,1,2,3]
Output: 1
Explanation:
There are 4 triplets (x,y,z) such that pos1x < pos1y < pos1z. They are (2,0,1), (2,0,3), (2,1,3), and (0,1,3).
Out of those triplets, only the triplet (0,1,3) satisfies pos2x < pos2y < pos2z. Hence, there is only 1 good triplet.

Example 2:
Input: nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
Output: 4
Explanation: The 4 good triplets are (4,0,3), (4,0,2), (4,1,3), and (4,1,2).


Constraints:
n == nums1.length == nums2.length
3 <= n <= 10^5
0 <= nums1[i], nums2[i] <= n - 1
nums1 and nums2 are permutations of [0, 1, ..., n - 1].

--------------------------------------------------------------------------------------
 */

/**
 * ============================================================================
 * SEGMENT TREE: VALUE-SPACE FREQUENCY COUNTER (COUNTING INVERSIONS)
 * ============================================================================
 * * Problem: Find triplets (x, y, z) that appear in the exact same increasing
 * positional order in BOTH nums1 and nums2.
 *
 * * * 1. THE NORMALIZATION TRICK (Two Arrays -> One Array)
 * Dealing with two arrays simultaneously is too complex. Because both arrays are
 * permutations of [0...n-1], we can map them together. We record the index of
 * every value in `nums1`, and then replace the values in `nums2` with those indices.
 * - Result: We now have a single array `A`. Any strictly increasing triplet
 * (A[i] < A[j] < A[k] where i < j < k) in `A` is guaranteed to be a valid
 * "Good Triplet" in the original two arrays.
 *
 * * * 2. THE MATH PATTERN ("Fix the Middle")
 * To find triplets A[i] < A[j] < A[k], we iterate through `A` and treat every
 * element as the middle element (A[j]).
 * - The number of valid triplets centered on A[j] is simply:
 * (Numbers to its left that are smaller) * (Numbers to its right that are greater).
 * - Let's call these `smaller_left` and `greater_right`.
 *
 * * * 3. THE SEGMENT TREE (Finding 'smaller_left')
 * We need to count `smaller_left` dynamically as we iterate. We build a Range Sum
 * Segment Tree where the leaves represent the actual VALUES [0 to n-1], and the nodes
 * store the FREQUENCY of how many times we've seen that value so far.
 * - For middle element A[j], we query the tree for the sum of range [0, A[j] - 1].
 * - This takes O(log N) time and gives us `smaller_left`.
 * - We then insert A[j] into the tree so it exists for future queries.
 *
 * * * 4. THE O(1) ARITHMETIC HACK (Finding 'greater_right')
 * Do we need a second tree to find `greater_right`? No. Because `A` is a permutation
 * of 0 to n-1, we can use pure math:
 * - Total numbers greater than A[j] in the ENTIRE array: (n - 1 - A[j])
 * - Total numbers greater than A[j] seen SO FAR (to the left): (j - smaller_left)
 * - Therefore, numbers greater than A[j] to the RIGHT:
 * greater_right = (n - 1 - A[j]) - (j - smaller_left)
 *
 *
 * * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N) to normalize + O(N log N) to iterate and query the tree.
 * - Space Complexity: O(N) for the Segment Tree array and normalization maps.
 * ============================================================================
 */
class SegmentTree
{
private:
    vector<int> tree;
    int n;

    /**
     * @brief Point Update: Increments the frequency of a specific value.
     * * * [THE VALUE-SPACE INTUITION: WHY DO WE DO THIS?]
     * Standard segment trees map leaves to array *indices*. But we can't ask a
     * standard tree "how many elements are < X?".
     * By changing the leaves to represent the *universe of possible values* [0 to n-1],
     * we physically map the SIZE of a number to its POSITION in the tree.
     * As we iterate through the array, we increment the frequency of values we see.
     * Because values are perfectly ordered left-to-right, counting "how many numbers < X
     * have I seen?" simply becomes a Range Sum Query for everything to the left of X!
     * * * [THE MECHANICS]
     * We navigate down to the exact leaf representing our value `idx` and increment
     * its frequency counter. Because the ranges [start, end] are perfectly ordered,
     * we find the leaf using standard binary search logic.
     *
     * In Value-Space Segment Tree, the tree's leaves represent the actual values of the array.
     *
     * * @time O(log N) - We only traverse exactly one path from root to leaf.
     * @space O(log N) - Depth of the recursive call stack.
     *
     * @param treeIdx  The current index in the flat segment tree array.
     * @param start The lower bound of the value range this treeIdx represents.
     * @param end   The upper bound of the value range this treeIdx represents.
     * @param idx   The specific value we are inserting (our target leaf).
     */
    void updateTree(int treeIdx, int start, int end, int idx)
    {
        // Base Case: We hit the specific value's leaf. Increment its frequency.
        if (start == end)
        {
            tree[treeIdx]++;
            return;
        }
        int mid = start + (end - start) / 2;

        // Binary search routing to find the leaf for 'idx'
        if (idx <= mid)
        {
            updateTree(2 * treeIdx + 1, start, mid, idx);
        }
        else
        {
            updateTree(2 * treeIdx + 2, mid + 1, end, idx);
        }

        // Post-order update: Recalculate frequency sums bubbling up
        tree[treeIdx] = tree[2 * treeIdx + 1] + tree[2 * treeIdx + 2];
    }

    /**
     * @brief Range Sum Query: Counts how many times we've seen values in [L, R].
     * * [THE INTUITION]
     * We want to find the sum of frequencies for all values between L and R.
     * Instead of visiting every leaf, we check if a treeIdx's entire range [start, end]
     * is completely swallowed by our target range [L, R]. If it is, we return its
     * pre-calculated sum in O(1) time and stop digging.
     * * @time O(log N) - Bounded by early exits on Full Overlaps and Out of Bounds.
     * @space O(log N) - Depth of the recursive call stack.
     *
     * @param treeIdx  The current index in the flat segment tree array.
     * @param start The lower bound of the value range this treeIdx represents.
     * @param end   The upper bound of the value range this treeIdx represents.
     * @param L     The lower bound of our target query range.
     * @param R     The upper bound of our target query range.
     * @return      The total frequency sum of values existing in [L, R].
     */
    int queryTree(int treeIdx, int start, int end, int L, int R)
    {
        // Case 1: Out of Bounds (or invalid query bounds)
        if (L > R || start > R || end < L)
        {
            return 0;
        }

        // Case 2: Full Overlap - return precalculated frequency sum
        if (L <= start && end <= R)
        {
            return tree[treeIdx];
        }

        // Case 3: Partial Overlap - dig deeper
        int mid = start + (end - start) / 2;
        return queryTree(2 * treeIdx + 1, start, mid, L, R) +
               queryTree(2 * treeIdx + 2, mid + 1, end, L, R);
    }

public:
    SegmentTree(int size)
    {
        n = size;
        tree.assign(4 * n, 0);
    }

    // Point Update: Increments the frequency of the given value
    void add(int idx)
    {
        updateTree(0, 0, n - 1, idx);
    }

    // Range Sum Query: Gets the total frequency of all values between L and R
    int query(int L, int R)
    {
        return queryTree(0, 0, n - 1, L, R);
    }
};

class Solution
{
public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();

        // Step 1: Normalization (Map nums1 values to their indices)
        vector<int> pos(n);
        for (int i = 0; i < n; ++i)
        {
            pos[nums1[i]] = i;
        }

        // Create the unified array A based on nums1's positional mapping
        vector<int> A(n);
        for (int i = 0; i < n; ++i)
        {
            A[i] = pos[nums2[i]];
        }

        SegmentTree segTree(n);
        long long totalTriplets = 0;

        // Step 2: Iterate and "Fix the Middle"
        for (int j = 0; j < n; ++j)
        {
            long long val = A[j];

            // Query: How many values seen so far are strictly smaller than `val`?
            long long smaller_left = segTree.query(0, val - 1);

            // Math Hack: Calculate how many values to the right are strictly greater
            long long total_greater = (n - 1 - val);
            long long greater_seen_so_far = (j - smaller_left);
            long long greater_right = total_greater - greater_seen_so_far;

            // Multiply combinations and add to running total
            totalTriplets += (smaller_left * greater_right);

            // Add the current value's frequency to the Segment Tree for future iterations
            segTree.add(val);
        }

        return totalTriplets;
    }
};

int main()
{

    return 0;
}