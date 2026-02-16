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

Range Sum Query - Mutable

https://leetcode.com/problems/range-sum-query-mutable/description/


Problem statement:
Given an integer array nums, handle multiple queries of the following types:

Update the value of an element in nums.
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
void update(int index, int val) Updates the value of nums[index] to be val.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).


Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8


Constraints:

1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
At most 3 * 10^4 calls will be made to update and sumRange.


*/

//-------------------------------------------
// Approach: Segment tree
//-------------------------------------------

/*
 * Segment Tree Implementation for Range Sum Queries (Mutable)
 * ==========================================================
 *
 * Problem Statement:
 * Given an integer array nums, handle multiple queries of:
 * 1. Update the value of an element at a specific index.
 * 2. Calculate the sum of elements within a specific range [left, right].
 *
 * Data Structure: Segment Tree
 * ----------------------------
 * A Segment Tree is a binary tree used for storing intervals or segments.
 * It allows querying which segment contains a given point. It is a static structure;
 * meaning, it's a structure that cannot be modified once built.
 * However, we can update the values of the nodes.
 *
 * Array Representation:
 * We use a flat array 'segT' to represent the tree.
 * - Root is at index 0.
 * - For node at index 'i':
 * - Left Child:  2*i + 1
 * - Right Child: 2*i + 2
 *
 * Space Complexity: O(4*N)
 * Time Complexity:
 * - Build: O(N)
 * - Update: O(log N)
 * - Query: O(log N)
 */

#include <vector>

using namespace std;

class NumArray
{

private:
    vector<int> segT; // The flat array storing segment tree nodes
    int N;            // Size of the original input array

    /*
     * Method: buildSegTree
     * --------------------
     * Recursively builds the Segment Tree from the input array.
     *
     * Process:
     * 1. Divide the current range [l, r] into two halves.
     * 2. Recursively build the left child for range [l, mid].
     * 3. Recursively build the right child for range [mid+1, r].
     * 4. Merge step: The value of the current node is the sum of its children.
     *
     * Base Case:
     * If l == r, we are at a leaf node representing a single element of the array.
     * Store nums[l] in the tree.
     *
     * Time Complexity: O(N) - We visit every node exactly once.
     * Space Complexity: O(N) - Recursion stack depth is O(log N).
     *
     * @param nums: Reference to the input array
     * @param l: Left boundary of the current segment
     * @param r: Right boundary of the current segment
     * @param segTIdx: Index in the segment tree array for the current node
     */
    void buildSegTree(vector<int> &nums, int l, int r, int segTIdx)
    {

        // Base Case: Leaf Node
        if (l == r)
        {
            segT[segTIdx] = nums[l];
            return;
        }

        int mid = l + (r - l) / 2;

        // Recursive Build
        buildSegTree(nums, l, mid, (2 * segTIdx + 1));     // Left Child
        buildSegTree(nums, mid + 1, r, (2 * segTIdx + 2)); // Right Child

        // Merge Logic (Sum)
        segT[segTIdx] = segT[2 * segTIdx + 1] + segT[2 * segTIdx + 2];
    }

    /*
     * Method: updateSum
     * -----------------
     * Updates a value in the original array and reflects changes in the Segment Tree.
     *
     * Process:
     * 1. Check if the 'updateIdx' is within the current range [l, r].
     * If not, return immediately (pruning).
     * 2. If we reached the leaf node corresponding to 'updateIdx' (l == r == updateIdx),
     * update the value.
     * 3. Otherwise, recurse to children.
     * 4. Backtracking: After returning from children, re-calculate the current node's sum
     * to ensure consistency up to the root.
     *
     * Time Complexity: O(log N) - We traverse the height of the tree.
     * Space Complexity: O(log N) - Recursion stack.
     *
     * @param updateIdx: Index in the original array to update
     * @param updateVal: New value to set
     * @param l: Current segment left boundary
     * @param r: Current segment right boundary
     * @param segTIdx: Current node index in the tree
     */
    void updateSum(int updateIdx, int updateVal, int l, int r, int segTIdx)
    {

        // Base Case: Leaf Node Found
        if (l == r && l == updateIdx)
        {
            segT[segTIdx] = updateVal;
            return;
        }

        int mid = l + (r - l) / 2;

        // Recurse to children
        if (updateIdx <= mid)
        {
            updateSum(updateIdx, updateVal, l, mid, 2 * segTIdx + 1);
        }
        else
        {
            updateSum(updateIdx, updateVal, mid + 1, r, 2 * segTIdx + 2);
        }

        // Update current node sum after child modification
        segT[segTIdx] = segT[2 * segTIdx + 1] + segT[2 * segTIdx + 2];
    }

    /*
     * Method: getRangeSum
     * -------------------
     * Queries the sum of elements in the range [searchL, searchR].
     *
     * Process:
     * 1. Total Overlap: If the current segment [l, r] is completely inside [searchL, searchR],
     * return the pre-calculated sum stored in this node. This is the O(log N) optimization.
     * 2. No Overlap: If the current segment is completely outside the query range, return 0.
     * 3. Partial Overlap: If the segment partially overlaps, we must split the query
     * and ask both children. Return the sum of results from left and right children.
     *
     * Time Complexity: O(log N) - In worst case, we visit ~4 nodes per level.
     * Space Complexity: O(log N) - Recursion stack.
     *
     * @param searchL: Query range start
     * @param searchR: Query range end
     * @param l: Current segment left boundary
     * @param r: Current segment right boundary
     * @param segTIdx: Current node index in the tree
     */
    int getRangeSum(int searchL, int searchR, int l, int r, int segTIdx)
    {

        // Case 1: Total Overlap
        if (searchL <= l && r <= searchR)
        {
            return segT[segTIdx];
        }

        // Case 2: No Overlap
        else if (searchR < l || r < searchL)
        {
            return 0;
        }

        // Case 3: Partial Overlap
        int mid = l + (r - l) / 2;
        int leftSum = getRangeSum(searchL, searchR, l, mid, (2 * segTIdx + 1));
        int rightSum = getRangeSum(searchL, searchR, mid + 1, r, (2 * segTIdx + 2));

        return (leftSum + rightSum);
    }

public:
    /*
     * Constructor: NumArray
     * ---------------------
     * Initializes the Segment Tree.
     * * Allocation Note:
     * We allocate size 4*N for the segment tree array.
     * Reason: A Segment Tree is a binary tree. For an array of size N, the tree height is ceil(log2(N)).
     * The maximum number of nodes in a complete binary tree of this height can approach 4*N
     * due to the way array indexing (2*i+1, 2*i+2) skips indices when the tree is not perfect.
     */
    NumArray(vector<int> &nums)
    {

        N = nums.size();

        if (N > 0)
        {
            segT.resize(4 * N);
            buildSegTree(nums, 0, N - 1, 0);
        }
    }

    /*
     * Public API: update
     * ------------------
     * Wrapper for updateSum. Updates nums[index] to val.
     */
    void update(int index, int val)
    {
        if (N > 0 && 0<=index && index<N)
        {
            updateSum(index, val, 0, N - 1, 0);
        }
    }

    /*
     * Public API: sumRange
     * --------------------
     * Wrapper for getRangeSum. Returns sum of nums[left...right].
     */
    int sumRange(int left, int right)
    {
        if (N == 0)
            return 0;
        return getRangeSum(left, right, 0, N - 1, 0);
    }
};

/**
 * Usage Example:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index, val);
 * int param_2 = obj->sumRange(left, right);
 */

int main()
{

    return 0;
}