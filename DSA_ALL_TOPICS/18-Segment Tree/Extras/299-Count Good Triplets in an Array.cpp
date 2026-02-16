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

 */

/*
 * Problem: 2179. Count Good Triplets in an Array
 * ----------------------------------------------
 * Goal: Find the number of triplets (x, y, z) such that:
 * 1. They appear in that relative order in nums1.
 * 2. They appear in that relative order in nums2.
 *
 * Approach: Segment Tree (or Fenwick Tree) + Line Sweep
 * -----------------------------------------------------
 * A brute force check is O(N^3), which is too slow. We need O(N log N).
 *
 * The Core Idea:
 * We iterate through 'nums1' and treat the current element as the MIDDLE element 'y' of the triplet.
 * For a fixed 'y', if we can efficiently count:
 * - L: Number of valid 'x' elements (appear before y in nums1 AND before y in nums2).
 * - R: Number of valid 'z' elements (appear after y in nums1 AND after y in nums2).
 *
 * Then the number of good triplets centered at 'y' is simply (L * R).
 * We sum this up for all possible 'y'.
 *
 * Data Structures:
 * 1. Hash Map (or Array): To quickly look up the index of a value in 'nums2'.
 * This allows us to translate the condition "before in nums2" to "index < pos2y".
 * 2. Segment Tree: To store the counts of elements we have processed so far based
 * on their positions in 'nums2'. This allows us to answer range sum queries in O(log N).
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N log N)
 * - We iterate through the array once (N steps).
 * - Inside the loop, we perform Segment Tree Update and Query operations.
 * - Each SegTree op is O(log N).
 * - Total: O(N log N).
 *
 * Space Complexity: O(N)
 * - O(N) for the mapping array/map.
 * - O(4*N) for the Segment Tree array.
 */

class Solution
{
private:
    vector<int> segT; // Segment Tree array
    int N;

    /*
     * Method: update
     * --------------
     * Performs a Point Update on the Segment Tree.
     * Logic: Adds 'updateVal' to the leaf node at 'updateI' and recalculates sums up the tree.
     * Used to mark an element as "visited" (processed in nums1).
     *
     * Time: O(log N)
     */
    void update(int l, int r, int segI, int updateI, int updateVal)
    {

        // Base Case: Leaf Node
        if (l == r)
        {
            segT[segI] = updateVal;
            return;
        }

        int mid = l + (r - l) / 2;
        int leftSegI = 2 * segI + 1;
        int rightSegI = 2 * segI + 2;

        // Recursive Step: Navigate to the correct child
        if (updateI <= mid)
        {
            update(l, mid, leftSegI, updateI, updateVal);
        }
        else
        {
            update(mid + 1, r, rightSegI, updateI, updateVal);
        }

        // Merge Step: Parent sum = Sum of children
        segT[segI] = segT[leftSegI] + segT[rightSegI];
    }

    /*
     * Method: getRangeVal
     * -------------------
     * Performs a Range Sum Query.
     * Logic: Returns the sum of values stored in the index range [rangeL, rangeR].
     * Context: Used to count how many visited elements appear before index 'pos2y' in nums2.
     *
     * Time: O(log N)
     */
    int getRangeVal(int l, int r, int segI, int rangeL, int rangeR)
    {

        // Case 1: Range completely outside
        if (r < rangeL || rangeR < l)
        {
            return 0;
        }
        // Case 2: Range completely inside
        else if (rangeL <= l && r <= rangeR)
        {
            return segT[segI];
        }
        // Case 3: Partial overlap
        else
        {
            int mid = l + (r - l) / 2;
            int leftSegI = 2 * segI + 1;
            int rightSegI = 2 * segI + 2;

            return getRangeVal(l, mid, leftSegI, rangeL, rangeR) +
                   getRangeVal(mid + 1, r, rightSegI, rangeL, rangeR);
        }
    }

public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2)
    {

        N = nums1.size();

        // Initialize Segment Tree with size 4*N to handle all possible indices
        // Initially all counts are 0.
        segT.resize(4 * N, 0);

        // Step 1: Pre-process indices of nums2.
        // mapping[val] = index of 'val' in nums2.
        // This effectively lets us ignore element values and just deal with permutation indices.
        unordered_map<int, int> mp;
        for (int i = 0; i < N; i++)
        {
            mp[nums2[i]] = i;
        }

        long long totalCounts = 0;

        // Pre-process the first element of nums1.
        // We consider it "visited" so it can serve as a Left Element (x) for future triplets.
        update(0, N - 1, 0, mp[nums1[0]], 1);

        // Step 2: Main Loop - Iterate through nums1
        // 'pos1y' represents the index of the MIDDLE element (y) in nums1.
        // We start from index 1 and go up to N-2.
        for (int pos1y = 1; pos1y < N - 1; ++pos1y)
        {

            // Get the position of the current element 'y' inside nums2
            int pos2y = mp[nums1[pos1y]];

            // Mark 'y' as present in the Segment Tree.
            // Note: Even though we update before querying, the query range is strictly [0, pos2y-1].
            // So the update at 'pos2y' does not affect the Left Common Count calculation.
            update(0, N - 1, 0, pos2y, 1);

            // ---------------------------------------------------------
            // CALCULATION PART 1: Find 'Left Common' (L)
            // ---------------------------------------------------------
            // We need count of elements 'x' such that:
            // 1. x appears before y in nums1 (Indices 0 to pos1y-1) -> Guaranteed by loop order.
            // 2. x appears before y in nums2 (Indices 0 to pos2y-1).
            // Query SegTree for sum in range [0, pos2y-1].
            int leftCommonCount = getRangeVal(0, N - 1, 0, 0, pos2y - 1);

            // ---------------------------------------------------------
            // CALCULATION PART 2: Find 'Right Common' (R)
            // ---------------------------------------------------------
            // We need count of elements 'z' such that:
            // 1. z appears after y in nums1.
            // 2. z appears after y in nums2.

            // Logic Derivation:
            // Total elements strictly to the right of y in nums1 = (N - 1) - pos1y.
            // Let's call this "TotalRightInNums1".

            // Some of these "TotalRightInNums1" appear to the LEFT of y in nums2.
            // How many?
            // - Total elements to the left of y in nums2 = pos2y.
            // - Elements left in both arrays = leftCommonCount.
            // - Therefore, elements (Left in nums2 BUT Right in nums1) = pos2y - leftCommonCount.

            // So, Right Common = (Total Right in nums1) - (Those that are Left in nums2).

            int leftExtraAtNums2 = pos2y - leftCommonCount; // Elements Left in nums2, Right in nums1
            int rightElmsCountAtNums1 = (N - 1) - pos1y;    // Total elements Right in nums1

            int rightCommonCount = rightElmsCountAtNums1 - leftExtraAtNums2;

            // ---------------------------------------------------------
            // ACCUMULATE RESULT
            // ---------------------------------------------------------
            long long tripletsCounts = (long long)leftCommonCount * rightCommonCount;

            totalCounts += tripletsCounts;
        }

        return totalCounts;
    }
};

int main()
{

    return 0;
}