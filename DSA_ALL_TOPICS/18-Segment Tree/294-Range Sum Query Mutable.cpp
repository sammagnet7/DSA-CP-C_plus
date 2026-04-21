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

----------------------------------------------------------------------------------------------------------------

*/

/**
 * ============================================================================
 * SEGMENT TREE: THE ULTIMATE INTERVAL DATA STRUCTURE
 * ============================================================================
 * * [1. THE CORE CONCEPT]
 * A Segment Tree is a binary tree where every node represents a specific interval
 * (range) of the original array. It is built using "Divide & Conquer on Indices."
 * - Root node covers the entire array [0, n-1].
 * - Leaves cover single elements [i, i].
 * - Internal nodes cover [start, end] and merge the results of their two children.
 * * [2. WHEN TO USE IT (THE TRIGGER PATTERN)]
 * Trigger: You need BOTH frequent Point Updates AND frequent Range Queries.
 * - Static Array + Range Queries -> Use Prefix Sums (O(1) query, but O(N) update).
 * - Dynamic Array + Range Queries -> Use Segment Tree (O(log N) for BOTH).
 * * [3. COMMON USE CASES]
 * - Range Sum Queries (as implemented below)
 * - Range Minimum/Maximum Queries (RMQ)
 * - Range XOR / GCD / LCM Queries
 * * [4. INTERVIEW TRICKS & MENTAL MODELS]
 * - The "Flat Array" Trick: We never use pointers/structs. We use a flat array
 * to represent the tree, exactly like a Binary Heap.
 * * Left Child: 2 * node + 1
 * * Right Child: 2 * node + 2
 * - The "4*N" Space Trick: To safely guarantee we have enough array indices to
 * hold a perfectly balanced representation (even if the input array size 'N'
 * is not a power of 2), allocating 4 * N space is mathematically proven to
 * prevent all OutOfBounds errors (2 * 2N).
 * - The "Range" Variables: Always track the node's boundaries [start, end] and
 * compare them against the target's boundaries [left, right] or index.
 * ============================================================================
 */
class NumArray
{
private:
    std::vector<int> tree; // The segment tree array
    std::vector<int> data; // Original data array (useful for leaf updates)
    int n;

    /**
     * Helper: Recursively builds the segment tree from the bottom up.
     * Logic: Post-order traversal. We go down to the leaves, grab the actual
     * array values, and then merge them as we bubble back up.
     * * Time Complexity: O(N) - We visit every node in the tree exactly once.
     * Space Complexity: O(log N) - Maximum depth of the recursive call stack.
     */
    void buildTree(int node, int start, int end)
    {
        // Base Case: Leaf node. The interval has narrowed to a single element.
        if (start == end)
        {
            tree[node] = data[start];
            return;
        }

        // Divide: Split the current interval exactly in half.
        int mid = start + (end - start) / 2;

        // Recurse: Build left child [start, mid] and right child [mid+1, end]
        buildTree(2 * node + 1, start, mid);
        buildTree(2 * node + 2, mid + 1, end);

        // Merge (Backtrack): Node value is the sum of its two children
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    /**
     * Helper: Updates a single element and recalculates affected tree nodes.
     * Logic: Binary search on indices. We navigate down to the specific leaf,
     * update it, and then recalculate the sums on the path back to the root.
     * * Time Complexity: O(log N) - We only traverse one branch down to the leaf.
     * Space Complexity: O(log N) - Depth of the recursive call stack.
     */
    void updateTree(int node, int start, int end, int index, int val)
    {
        // Base Case: Found the exact leaf node for the index. Update it.
        if (start == end)
        {
            data[index] = val; // Update underlying data (optional depending on problem)
            tree[node] = val;  // Update the tree leaf
            return;
        }

        int mid = start + (end - start) / 2;

        // Binary search routing: Which child contains our target 'index'?
        if (index <= mid)
        {
            updateTree(2 * node + 1, start, mid, index, val);
        }
        else
        {
            updateTree(2 * node + 2, mid + 1, end, index, val);
        }

        // Post-order update: Recalculate this node's sum based on updated children
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    /**
     * Helper: Queries the sum of elements in the range [left, right].
     * Logic: Compares the Node's Range [start, end] against the Query's Range [left, right].
     * This relies entirely on early-exit bounding to achieve logarithmic time.
     * * Time Complexity: O(log N) - Because of "Case 2", we don't visit all nodes;
     * we stop as soon as a node is perfectly swallowed by the query.
     * Space Complexity: O(log N) - Depth of the recursive call stack.
     */
    int sumRangeTree(int node, int start, int end, int left, int right)
    {
        // Case 1: Out of range (No overlap)
        // The node's interval is completely outside our search interval.
        // Return 0 (Identity value for Addition).
        if (end < left || right < start)
        {
            return 0;
        }

        // Case 2: Full Overlap (Node is completely swallowed by Query)
        // The node's entire interval is inside our search interval.
        // We can confidently return its pre-calculated sum without digging deeper.
        else if (left <= start && end <= right)
        {
            return tree[node];
        }

        // Case 3: Partial Overlap (Intersection)
        // Part of the node is inside the search interval, part is outside.
        // We must split the search and dig deeper into both children.
        else
        {
            int mid = start + (end - start) / 2;
            return sumRangeTree(2 * node + 1, start, mid, left, right) + sumRangeTree(2 * node + 2, mid + 1, end, left, right);
        }
    }

public:
    /**
     * Constructor
     * Time: O(N) | Space: O(N) allocated for the tree array.
     */
    NumArray(std::vector<int> &nums)
    {
        n = nums.size();
        // Allocate 4*N space to prevent out-of-bounds on deep branches
        tree.resize(4 * n, 0);
        data = nums;

        // Guard against empty array inputs
        if (n > 0)
        {
            buildTree(0, 0, n - 1);
        }
    }

    /**
     * API: Update index to a new value.
     * Time: O(log N)
     */
    void update(int index, int val)
    {
        updateTree(0, 0, n - 1, index, val);
    }

    /**
     * API: Get the sum between indices left and right (inclusive).
     * Time: O(log N)
     */
    int sumRange(int left, int right)
    {
        return sumRangeTree(0, 0, n - 1, left, right);
    }
};

/**
 * Usage Example:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index, val);
 * int result = obj->sumRange(left, right);
 */

int main()
{

    return 0;
}