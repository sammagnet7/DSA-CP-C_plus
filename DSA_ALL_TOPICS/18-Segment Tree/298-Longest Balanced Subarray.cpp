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
            int curDelta = (nums[r] % 2 == 0) ? 1 : -1;

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
                    cumulativeSum[l] -= curDelta;
                }
            }

            // -------------------------------------------------------
            // Step 2: Update Current Range
            // -------------------------------------------------------
            // Add the current number's contribution to ALL subarrays ending at 'r'.
            // This conceptually adds nums[r] to subarrays starting at 0, 1, ... r.
            for (int l = 0; l <= r; ++l)
            {
                cumulativeSum[l] += curDelta;
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
 * ======================================================================================
 * Approach 2: optimization of Range Updates with Segment Tree [O(N log N)] [OPTIMAL]
 * ======================================================================================
 * * APPROACH OVERVIEW:
 * ------------------
 * We need to find the longest subarray where:
 * (Count of Unique Evens) == (Count of Unique Odds)
 * * 1. MAPPING TO VALUES:
 * - Even numbers contribute +1.
 * - Odd numbers contribute -1.
 * - We want a subarray range [L, R] where the "Unique Sum" is 0.
 * * 2. THE "UNIQUE" CONSTRAINT CHALLENGE:
 * - Standard prefix sums don't work because if a number appears twice, it shouldn't
 * be counted twice.
 * - We iterate 'R' from 0 to N-1. For a fixed 'R', we want to find the smallest 'L'
 * such that the unique sum of subarray nums[L...R] is 0.
 * * 3. SEGMENT TREE STATE:
 * - The Segment Tree maintains a "Cumulative Sum" for every possible start index 'i'.
 * - Specifically, leaf node 'i' stores the value of the unique balance for the
 * subarray nums[i...R] (where R is the current iteration index).
 * - As 'R' moves to 'R+1', we update these sums using Range Updates.
 * * 4. OPTIMIZATION (Why O(N log N)?):
 * - Previous Brute Force: Iterate 'L' from 0 to R for every R -> O(N^2).
 * - Segment Tree:
 * a) Range Update: Add/Subtract values across a range [0...index] in O(log N).
 * b) Range Query: Find the leftmost index with value 0 in O(log N).
 * - We use a "Min-Max" Segment Tree to PRUNE the search. If 0 is not
 * between min and max of a node, we skip that subtree.
 * * COMPLEXITY:
 * -----------
 * Time: O(N log N)
 * - We iterate R from 0 to N (N steps).
 * - Inside, we do at most 2 Range Updates and 1 Query.
 * - Each operation takes O(log N).
 * * Space: O(N)
 * - Segment Tree array size is 4*N.
 */

class Solution
{
private:
    // Segment Tree stores a pair <min, max> for each range.
    // This allows us to quickly check if a specific target value exists in a subtree.
    vector<pair<int, int>> segT;

    // Lazy array for Lazy Propagation updates
    vector<int> lazy;

    int N;

    /**
     * Helper: propagateUpdate
     * -----------------------
     * Pushes pending updates from a parent node down to its children.
     * Crucial for O(log N) range updates.
     */
    void propagateUpdate(int l, int r, int segI)
    {

        if (lazy[segI] != 0)
        {
            // Apply the pending update to the current node
            segT[segI].first += lazy[segI];
            segT[segI].second += lazy[segI];

            // If not a leaf node, push the lazy value to children
            if (l != r)
            {
                int segIL = 2 * segI + 1;
                int segIR = 2 * segI + 2;
                lazy[segIL] += lazy[segI];
                lazy[segIR] += lazy[segI];
            }

            // Clear the lazy value for current node
            lazy[segI] = 0;
        }
    }

    /**
     * Method: updateRange
     * -------------------
     * Updates the cumulative sum for all subarrays starting in range [rangeL, rangeR].
     * * Logic:
     * 1. Standard Lazy Propagation structure.
     * 2. If range matches fully, update lazy and return.
     * 3. Else, recurse to children and update min/max on the way back.
     */
    void updateRange(int l, int r, int segI, int rangeL, int rangeR, int updateDelta)
    {

        // 1. Always propagate first to ensure current node state is clean
        propagateUpdate(l, r, segI);

        // 2. Out of Range: Do nothing
        if (r < rangeL || rangeR < l)
        {
            return;
        }
        // 3. Full Overlap: Apply update lazily
        else if (rangeL <= l && r <= rangeR)
        {
            lazy[segI] += updateDelta;
            propagateUpdate(l, r, segI); // Apply immediately to current node
            return;
        }
        // 4. Partial Overlap: Recurse
        else
        {
            int mid = l + (r - l) / 2;

            int segIL = 2 * segI + 1;
            int segIR = 2 * segI + 2;

            updateRange(l, mid, segIL, rangeL, rangeR, updateDelta);
            updateRange(mid + 1, r, segIR, rangeL, rangeR, updateDelta);

            // Backtracking: Update current node's min/max from children
            segT[segI].first = min(segT[segIL].first, segT[segIR].first);
            segT[segI].second = max(segT[segIL].second, segT[segIR].second);

            return;
        }
    }

    /**
     * Method: leftMostIdxOfValueAtRange
     * ---------------------------------
     * Searches for the LEFTMOST index 'i' in [rangeL, rangeR] where the cumulative sum is 'targetVal'.
     * * OPTIMIZATIONS (vs O(N) linear search):
     * 1. Pruning: If 'targetVal' is outside [node.min, node.max], we return -1 immediately.
     * This skips entire subtrees, making the search O(log N) on average.
     * 2. Greedy Search: We always check the Left Child first. If found, we don't check Right.
     */
    int leftMostIdxOfValueAtRange(int l, int r, int segI, int rangeL, int rangeR, int targetVal)
    {

        // Ensure current node is up-to-date
        propagateUpdate(l, r, segI);

        // 1. PRUNING: Is the target impossible in this subtree?
        // If min > target or max < target, the value doesn't exist here.
        if (targetVal < segT[segI].first || segT[segI].second < targetVal)
        {
            return -1;
        }
        // 2. Boundary Check: Out of query range
        else if (r < rangeL || rangeR < l)
        {
            return -1;
        }
        // 3. Leaf Node: We found a potential candidate
        else if (l == r)
        {
            if (segT[segI].first == targetVal)
                return l;
            else
                return -1;
        }

        int mid = l + (r - l) / 2;
        int segIL = 2 * segI + 1;
        int segIR = 2 * segI + 2;

        int leftMostidx = -1;

        // 4. Greedy Left Search
        leftMostidx = leftMostIdxOfValueAtRange(l, mid, segIL, rangeL, rangeR, targetVal);

        // If found in left, return it (priority to leftmost index)
        if (leftMostidx != -1)
        {
            return leftMostidx;
        }
        // Otherwise, search right
        else
            return leftMostIdxOfValueAtRange(mid + 1, r, segIR, rangeL, rangeR, targetVal);
    }

public:
    int longestBalanced(vector<int> &nums)
    {

        N = nums.size();

        // Resize Segment Tree (4*N is safe upper bound)
        // Default init to 0 is correct as initial cumulative sums are 0
        segT.resize(4 * N);
        lazy.resize(4 * N);

        // Map to track the previous index of each number (for uniqueness constraint)
        unordered_map<int, int> lastSeen;

        int maxLen = 0;

        // Main Loop: Sliding Window / Line Sweep
        // We move 'r' (End of subarray) one by one.
        for (int r = 0; r < N; ++r)
        {

            int curDelta = (nums[r] % 2 == 0) ? 1 : -1;

            // -------------------------------------------------------
            // Step 1: Handle Duplicates (Enforce Uniqueness)
            // -------------------------------------------------------
            // If nums[r] appeared before at 'prevIdx', it was already contributing
            // +1 or -1 to subarrays starting at 0...prevIdx.
            // Since it appears again, we must REMOVE its old contribution from those
            // subarrays to avoid double counting.
            if (lastSeen.find(nums[r]) != lastSeen.end())
            {
                int prevIdx = lastSeen[nums[r]];

                // Range Update: Subtract curDelta from range [0...prevIdx]
                // Complexity: O(log N)
                int rangeL = 0;
                int rangeR = prevIdx;
                int updateDelta = (-curDelta);
                updateRange(0, N - 1, 0, rangeL, rangeR, updateDelta);
            }

            // -------------------------------------------------------
            // Step 2: Update Current Range
            // -------------------------------------------------------
            // Add the current number's contribution to ALL subarrays ending at 'r'.
            // Conceptually, this updates cumulativeSum[0...r] += curDelta.
            // Complexity: O(log N)
            int rangeL = 0;
            int rangeR = r;
            int updateDelta = curDelta;
            updateRange(0, N - 1, 0, rangeL, rangeR, updateDelta);

            // -------------------------------------------------------
            // Step 3: Find Longest Balanced Subarray
            // -------------------------------------------------------
            // We need to find the smallest 'l' such that cumulativeSum[l] == 0.
            // This means subarray nums[l...r] is balanced.
            // Complexity: O(log N) due to pruning
            rangeL = 0;
            rangeR = r;
            int targetVal = 0;
            int leftMostIdx = leftMostIdxOfValueAtRange(0, N - 1, 0, rangeL, rangeR, targetVal);

            // If a valid start index exists
            if (leftMostIdx != -1)
            {
                maxLen = max(maxLen, (r - leftMostIdx + 1));
            }

            // Record current index for future duplicate handling
            lastSeen[nums[r]] = r;
        }

        return maxLen;
    }
};

int main()
{

    return 0;
}