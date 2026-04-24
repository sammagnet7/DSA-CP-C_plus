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

Range Minimum Query

https://www.geeksforgeeks.org/problems/range-minimum-query/1


Problem statement:
Given an array A[ ] and its size N your task is to complete two functions: a constructST  function which builds the segment tree  and a function RMQ which finds range minimum query in a range [a,b] of the given array.

Input:
The task is to complete two functions constructST and RMQ.
The constructST function builds the segment tree and takes two arguments the array A[ ] and the size of the array N.
It returns a pointer to the first element of the segment tree array.
The RMQ function takes 4 arguments the first being the segment tree st constructed, second being the size N and then third and forth arguments are the range of query a and b. The function RMQ returns the min of the elements in the array from index range a and b. There are multiple test cases. For each test case, this method will be called individually.

Output:
The function RMQ should return the min element in the array from range a to b.

Example:

    Input
    arr:    1 2 3 4
    range:    [0 2], [2 3]

    Output
    1, 3

    Explanation
    1. For query 1 ie 0 2 the element in this range are 1 2 3
    and the min element is 1.
    2. For query 2 ie 2 3 the element in this range are 3 4
    and the min element is 3.

Constraints:
    1<=T<=100
    1<=N<=10^3+1
    1<=A[i]<=10^9
    1<=Q(no of queries)<=10^4
    0<=a<=b

-----------------------------------------------------------------------------------------
*/

/**
 * ============================================================================
 * SEGMENT TREE: RANGE MINIMUM QUERY (RMQ)
 * ============================================================================
 * Core Concept: A binary tree where each node stores the minimum value of a
 * specific sub-array (interval) of the original array.
 * * Time Complexities:
 * - Build: O(N)       -> We visit every node exactly once.
 * - Query: O(log N)   -> We prune branches using "Full Overlap" bounds checking.
 * - Space: O(N)       -> We allocate an array of size 4*N.
 * ============================================================================
 */
class SegmentTree
{
private:
    int *tree; // The segment tree represented as a flat array
    int *data; // Pointer to the original array (to fetch leaf values)
    int n;     // Size of the original array

    /**
     * HELPER: Recursively builds the tree bottom-up (Post-order traversal).
     * @param treeIdx: The current node's index in the 'tree' array.
     * @param start: The starting index of the original array segment this node covers.
     * @param end: The ending index of the original array segment this node covers.
     */
    void buildTree(int treeIdx, int start, int end)
    {
        // Base Case: We've hit a leaf node (segment size of 1).
        if (start == end)
        {
            tree[treeIdx] = data[start];
            return;
        }

        // Divide: Split the segment exactly in half.
        int mid = start + (end - start) / 2;

        // Recurse: Build the left and right children.
        // Left child index: 2*i + 1 | Right child index: 2*i + 2
        buildTree(2 * treeIdx + 1, start, mid);
        buildTree(2 * treeIdx + 2, mid + 1, end);

        // Merge: The minimum of this node's range is the smaller of its two children.
        tree[treeIdx] = min(tree[2 * treeIdx + 1], tree[2 * treeIdx + 2]);
    }

    /**
     * HELPER: Recursively searches for the minimum value in the requested range.
     * @param lRange: The target query's left boundary.
     * @param rRange: The target query's right boundary.
     */
    int rangeMin(int treeIdx, int start, int end, int lRange, int rRange)
    {
        // CASE 1: Full Overlap
        // The node's interval [start, end] is completely inside the query [lRange, rRange].
        // We can safely return this node's minimum without digging any deeper.
        if (lRange <= start && end <= rRange)
        {
            return tree[treeIdx];
        }

        // CASE 2: No Overlap (Out of Bounds)
        // The node's interval is completely outside the query interval.
        // CRITICAL: We return INT_MAX (Infinity) so it doesn't affect the min() calculation.
        else if (rRange < start || end < lRange)
        {
            return INT_MAX; // NOTE THIS
        }

        // CASE 3: Partial Overlap
        // The query partially covers this node. We must split the search and check both children.
        else
        {
            int mid = start + (end - start) / 2;
            return min(
                rangeMin(2 * treeIdx + 1, start, mid, lRange, rRange),
                rangeMin(2 * treeIdx + 2, mid + 1, end, lRange, rRange));
        }
    }

public:
    /**
     * CONSTRUCTOR
     * Initializes the class state and triggers the recursive tree build.
     */
    SegmentTree(int arr[], int n)
    {
        this->n = n;
        data = arr;

        // Allocate 4*N space. This guarantees enough bounds for a perfect
        // binary tree representation, even if 'N' is not a power of 2.
        tree = new int[4 * n];

        // Begin building from the root (index 0) covering the whole array [0, n-1]
        buildTree(0, 0, n - 1);
    }

    /**
     * API: Returns the raw array pointer (required by the GFG platform).
     */
    int *getRoot()
    {
        return tree;
    }

    /**
     * API: Public wrapper for the RMQ function.
     */
    int RMQ(int lRange, int rRange)
    {
        return rangeMin(0, 0, n - 1, lRange, rRange);
    }
};

// =====================================================================
// Note: This wrapper is used specifically to adapt our clean OOP class.
// =====================================================================

SegmentTree *segTree; // Global pointer to persist state between driver calls

/* * The function which builds the segment tree.
 * Called once per testcase by the platform.
 */
int *constructST(int arr[], int n)
{
    // Note: In a real system, you would delete the old segTree to prevent memory leaks
    // before reassigning it, but GFG RAM limits are high enough to permit this.
    segTree = new SegmentTree(arr, n);
    return segTree->getRoot();
}

/* * The function returns the min element in the range from a and b.
 * Called multiple times per testcase by the platform.
 */
int RMQ(int st[], int n, int a, int b)
{
    // Bypass the raw st[] array provided by the platform and route the query
    // directly into our instantiated SegmentTree class.
    return segTree->RMQ(a, b);
}

int main()
{

    return 0;
}