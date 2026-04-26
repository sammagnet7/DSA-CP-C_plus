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

Title: Longest Balanced Subarray II

Link:
https://www.youtube.com/watch?v=QxS30NMAjhE&t=1s
https://leetcode.com/problems/longest-balanced-subarray-ii/description/


Problem statement:
You are given an integer array nums.
A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.
Return the length of the longest balanced subarray.


Example 1:
Input: nums = [2,5,4,3]
Output: 4
Explanation:
The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.

Example 2:
Input: nums = [3,2,2,5,4]
Output: 5
Explanation:
The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.

Example 3:
Input: nums = [1,2,3,2]
Output: 3
Explanation:
The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.


Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5

-----------------------------------------------------------------------------------------

*/

/*
 * ======================================================================================
 * Approach 1: Simulation of Range Updates [Brute Force] [Slow]
 * ======================================================================================
 *
 * core Idea:
 * We maintain a 'cumulativeSum' array where cumulativeSum[l] represents the
 * "balance" of the subarray nums[l...r].
 * - Balance = (Count of Unique Evens) - (Count of Unique Odds).
 * - Goal: Find the smallest 'l' such that cumulativeSum[l] == 0 for the current 'r'.
 *
 * Handling Uniqueness (The Tricky Part):
 * When we encounter a number nums[r]:
 * 1. It adds +1 (if Even) or -1 (if Odd) to the balance of all subarrays ending at 'r'.
 * 2. However, if nums[r] has appeared before at index 'prev', it was ALREADY counted
 * for subarrays starting at 0 to prev.
 * 3. To avoid double-counting, we must SUBTRACT the previous contribution from
 * the range [0...prev].
 * - Net effect for range [0...prev]: Old (+1) + New (+1) - Correction (+1) = +1.
 * - The number is counted exactly once as a unique element.
 *
 * ----------------------------------------------------------------------------------
 * Complexity Analysis:
 * ----------------------------------------------------------------------------------
 * Time Complexity: O(N^2)
 * - We iterate 'r' from 0 to N-1 (Outer Loop).
 * - Inside, we iterate 'l' from 0 to 'r' multiple times to update sums and find the max.
 * - In the worst case (e.g., all unique elements), this performs ~ N*N/2 operations.
 *
 * Space Complexity: O(N)
 * - 'cumulativeSum' vector takes O(N) space.
 * - 'lastSeen' map takes O(N) space in the worst case (all elements unique).
 *
 * ----------------------------------------------------------------------------------
 * Optimization Path:
 * This O(N^2) approach is a conceptual prototype. The operations performed:
 * 1. Range Add (Update cumulativeSum[0...r] and cumulativeSum[0...prev])
 * 2. Range Search (Find first index with value 0)
 * These are standard operations for a SEGMENT TREE with Lazy Propagation, which
 * would optimize this to O(N log N).
 */

class Solution
{
public:
    int longestBalanced(vector<int> &nums)
    {

        int N = nums.size();

        // cumulativeSum[l] stores the net balance of Unique Evens vs Unique Odds
        // for the subarray starting at 'l' and ending at the current 'r'.
        // Value 0 means balanced. >0 means more Evens. <0 means more Odds.
        vector<int> cumulativeSum(N, 0);

        // Map to track the previous occurrence index of each number.
        // Used to enforce the "Unique" constraint.
        unordered_map<int, int> lastSeen;

        int maxLen = 0;

        // Sliding Window / Iteration: Expand 'r' from 0 to N-1
        for (int r = 0; r < N; ++r)
        {

            // Determine impact of current number:
            // Even numbers contribute +1 to the balance.
            // Odd numbers contribute -1 to the balance.
            int update_val = (nums[r] % 2 == 0) ? 1 : -1;

            // -------------------------------------------------------
            // Step 1: Handle Duplicates (Enforce Uniqueness)
            // -------------------------------------------------------
            // If nums[r] was seen before at 'lastSeen[nums[r]]', its contribution
            // was already added to subarrays starting before that index.
            // We must "undo" that previous addition to prevent double counting.
            if (lastSeen.find(nums[r]) != lastSeen.end())
            {
                int prevIdx = lastSeen[nums[r]];

                // Subtract the delta from the range [0...prevIdx]
                // This effectively cancels out the previous instance's contribution
                // for subarrays that now contain BOTH instances.
                for (int l = 0; l <= prevIdx; l++)
                {
                    cumulativeSum[l] -= update_val;
                }
            }

            // -------------------------------------------------------
            // Step 2: Update Current Range
            // -------------------------------------------------------
            // Add the current number's contribution to ALL subarrays ending at 'r'.
            // This conceptually adds nums[r] to subarrays starting at 0, 1, ... r.
            for (int l = 0; l <= r; ++l)
            {
                cumulativeSum[l] += update_val;
            }

            // -------------------------------------------------------
            // Step 3: Find Longest Balanced Subarray
            // -------------------------------------------------------
            // We check all possible start indices 'l'.
            // If cumulativeSum[l] == 0, it means Unique Evens == Unique Odds
            // for the range nums[l...r].
            for (int l = 0; l <= r; ++l)
            {
                if (cumulativeSum[l] == 0)
                {
                    // We found a valid balanced subarray.
                    // Since we iterate 'l' from 0, the first match gives the longest length.
                    maxLen = max(maxLen, (r - l + 1));

                    // Optimization: We can break here because we want the MAX length,
                    // and smaller 'l' yields larger length.
                    break;
                }
            }

            // Update the last seen position for the next iteration
            lastSeen[nums[r]] = r;
        }

        return maxLen;
    }
};

/**
 * ============================================================================
 * Approach 2: SEGMENT TREE: LAZY PROPAGATION + DESCENT [OPTIMAL]
 * ============================================================================
 * * [THE STEP-BY-STEP INTUITION JOURNEY]
 * * STEP 1: The Brute Force Barrier
 * We want the longest subarray [L...R] where (Distinct Evens) == (Distinct Odds).
 * A naive approach checks every subarray in O(N^2) or O(N^3) time. With N = 10^5,
 * this will Time Limit Exceed (TLE). We need an O(N log N) approach.
 * 
 * * STEP 2: The "Running Balance" Concept
 * Let's iterate the right endpoint `R` from left to right. At any point `R`,
 * imagine maintaining an array `val` where `val[L]` stores the exact balance of
 * the subarray starting at `L` and ending at `R`.
 * Balance = (Distinct Evens) - (Distinct Odds).
 * If `val[L] == 0`, the subarray [L...R] is perfectly balanced. Our goal for a
 * fixed `R` is to find the SMALLEST index `L` (the leftmost start) where `val[L] == 0`.
 * 
 * * STEP 3: Mapping the Updates (The "Aha!" Moment)
 * As `R` moves to the right, we process a new number: `nums[R]`. How does this
 * new number change the balance of all our possible starting points `L`?
 * - The new number only counts as "distinct" if it hasn't appeared recently.
 * - Let `prev` be the index where we last saw `nums[R]`.
 * - This new `nums[R]` only increases the distinct count for subarrays that
 * START strictly after `prev`.
 * - Therefore, the balance changes ONLY for starting points L in the range [prev + 1, R].
 * - If `nums[R]` is Even: Every `val[L]` in that range gets +1.
 * - If `nums[R]` is Odd: Every `val[L]` in that range gets -1.
 * 
 * * STEP 4: Why Lazy Propagation?
 * We now have a mathematical requirement: We need to add +1 or -1 to a MASSIVE
 * range of elements `[prev + 1, R]` at every step. If we update them one by one,
 * it takes O(N) time per step, leading to O(N^2) overall.
 * A Segment Tree with Lazy Propagation allows us to apply these range additions
 * in O(log N) time by deferring the updates to children until absolutely necessary.
 * 
 * * STEP 5: Finding the Leftmost '0' (The IVT Descent)
 * Now we have a tree updated with our balances. How do we find the leftmost `0`?
 * - Notice that `val[L]` and `val[L+1]` will differ by at most 1 (because moving
 * the left endpoint by 1 drops exactly one number).
 * - By the Intermediate Value Theorem (IVT), the values are contiguous.
 * - Therefore, if a Segment Tree node tells us its `min_val <= 0` and its
 * `max_val >= 0`, a `0` is MATHEMATICALLY GUARANTEED to exist in that branch!
 * - We can do an O(log N) descent: If a branch contains 0, dive Left first
 * (to get the longest subarray), and if it fails, dive Right.
 * 
 * * * [COMPLEXITY ANALYSIS]
 * - Time: O(N log N) -> N elements, each takes O(log N) to update and query.
 * - Space: O(N) -> Size 4*N for Segment Tree arrays + Hash map of size 10^5.
 * ============================================================================
 */
class LazySegmentTree
{
private:
    vector<int> min_val;
    vector<int> max_val;
    vector<int> lazy;
    int n;

    // LAZY PROPAGATION: Push pending updates to the left and right children
    void pushDown(int treeIdx)
    {
        if (lazy[treeIdx] != 0)
        {
            int left = 2 * treeIdx + 1;
            int right = 2 * treeIdx + 2;

            // Apply the deferred update to the left child
            lazy[left] += lazy[treeIdx];
            min_val[left] += lazy[treeIdx];
            max_val[left] += lazy[treeIdx];

            // Apply the deferred update to the right child
            lazy[right] += lazy[treeIdx];
            min_val[right] += lazy[treeIdx];
            max_val[right] += lazy[treeIdx];

            // Clear the current treeIdx's pending update
            lazy[treeIdx] = 0;
        }
    }

    // RANGE UPDATE: Add `val` to all leaves in the interval [L, R]
    void updateRange(int treeIdx, int start, int end, int L, int R, int val)
    {
        // Out of bounds
        if (start > R || end < L)
            return;

        // Full Overlap: Update this treeIdx and stop. Defer children updates.
        if (L <= start && end <= R)
        {
            lazy[treeIdx] += val;
            min_val[treeIdx] += val;
            max_val[treeIdx] += val;
            return;
        }

        // Partial Overlap: Push pending updates down before branching
        pushDown(treeIdx);

        int mid = start + (end - start) / 2;
        updateRange(2 * treeIdx + 1, start, mid, L, R, val);
        updateRange(2 * treeIdx + 2, mid + 1, end, L, R, val);

        // Post-Order Merge
        min_val[treeIdx] = min(min_val[2 * treeIdx + 1], min_val[2 * treeIdx + 2]);
        max_val[treeIdx] = max(max_val[2 * treeIdx + 1], max_val[2 * treeIdx + 2]);
    }

    // DESCENT QUERY: Find the leftmost leaf containing the value `0`
    int queryLeftmostZero(int treeIdx, int start, int end, int L, int R)
    {
        // Out of bounds
        if (start > R || end < L)
            return -1;

        // PRUNING: Intermediate Value Theorem.
        // If 0 is not between min and max, 0 does not exist in this segment.
        if (min_val[treeIdx] > 0 || max_val[treeIdx] < 0)
            return -1;

        // Base Case: We hit a valid leaf!
        if (start == end)
            return start;

        // Must push down pending updates before reading children!
        pushDown(treeIdx);

        int mid = start + (end - start) / 2;

        // Priority 1: Dive Left
        int leftResult = queryLeftmostZero(2 * treeIdx + 1, start, mid, L, R);
        if (leftResult != -1)
            return leftResult;

        // Priority 2: Dive Right
        return queryLeftmostZero(2 * treeIdx + 2, mid + 1, end, L, R);
    }

public:
    LazySegmentTree(int size)
    {
        n = size;
        min_val.assign(4 * n, 0);
        max_val.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(int L, int R, int val)
    {
        if (L > R)
            return;
        updateRange(0, 0, n - 1, L, R, val);
    }

    int getLeftmostZero(int R)
    {
        return queryLeftmostZero(0, 0, n - 1, 0, R);
    }
};

class Solution
{
public:
    int longestBalanced(vector<int> &nums)
    {
        int n = nums.size();
        LazySegmentTree segTree(n);

        // Use a flat array for O(1) lookups instead of unordered_map.
        // Elements are guaranteed to be <= 10^5 per constraints.
        vector<int> last_seen(100005, -1);

        int max_len = 0;

        for (int R = 0; R < n; ++R)
        {
            int num = nums[R];
            int prev_pos = last_seen[num];

            // If Even -> Add 1. If Odd -> Subtract 1.
            int update_val = (num % 2 == 0) ? 1 : -1;

            // Apply Range Update
            segTree.update(prev_pos + 1, R, update_val);

            // Query the leftmost starting point L where balance == 0
            int L = segTree.getLeftmostZero(R);

            if (L != -1)
            {
                max_len = max(max_len, R - L + 1);
            }

            // Update the last seen position for this number
            last_seen[num] = R;
        }

        return max_len;
    }
};

int main()
{

    return 0;
}