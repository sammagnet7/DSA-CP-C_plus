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

1. Title: Longest Increasing Subsequence

Links:
https://takeuforward.org/data-structure/longest-increasing-subsequence-dp-41/
https://www.youtube.com/watch?v=ekcwMsSIzVc
https://takeuforward.org/plus/dsa/problems/longest-increasing-subsequence?tab=editorial
https://leetcode.com/problems/longest-increasing-subsequence/description/


Problem statement:
Given an integer array nums, return the length of the longest strictly increasing subsequence.

Examples:
    Example 1:
    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

    Example 2:
    Input: nums = [0,1,0,3,2,3]
    Output: 4

    Example 3:
    Input: nums = [7,7,7,7,7,7,7]
    Output: 1

Constraints:
    1 <= nums.length <= 2500
    -104 <= nums[i] <= 104


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Longest Increasing Subsequence | Binary Search

Links:
https://takeuforward.org/data-structure/longest-increasing-subsequence-binary-search-dp-43/
https://www.youtube.com/watch?v=on2hvxBXJH4
https://takeuforward.org/plus/dsa/problems/longest-increasing-subsequence?tab=editorial
https://leetcode.com/problems/longest-increasing-subsequence/description/


Problem statement:
Given an integer array nums, return the length of the longest strictly increasing subsequence.

Can you come up with an algorithm that runs in O(n log(n)) time complexity?

Examples:
    Example 1:
    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

    Example 2:
    Input: nums = [0,1,0,3,2,3]
    Output: 4

    Example 3:
    Input: nums = [7,7,7,7,7,7,7]
    Output: 1

Constraints:
    1 <= nums.length <= 2500
    -104 <= nums[i] <= 104


INPUT::::::

OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Longest Increasing Subsequence
//-------------------------------------------------------------------------------

class Solution
{
public:
    // -----------------------------------------------------------------------------
    // Approach 1: Recursive + Memoization (Top-Down DP)
    // -----------------------------------------------------------------------------
    //
    /**
     * @brief Top-Down DP for LIS using explicit boundary checks instead of index shifting.
     * * --- STATE DEFINITION ---
     * dp[curIdx][prevIdx] stores the max LIS from 'curIdx' to the end of the array,
     * given that the last selected element was at 'prevIdx'.
     * * --- THE -1 AVOIDANCE TRICK ---
     * Instead of shifting all prevIdx values by +1 to fit into the DP array, this
     * implementation explicitly bypasses the DP table whenever prevIdx == -1.
     * Since prevIdx remains -1 ONLY if we have skipped all previous elements, there
     * is exactly one unique path to reach any state where prevIdx == -1. Therefore,
     * those specific states never overlap and do not require memoization!
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2) - We compute each unique (curIdx, prevIdx) state exactly once.
     * Space Complexity : O(N^2) - We allocate an N x N matrix (saving an entire column of
     * memory compared to the N x N+1 approach).
     */
    int recLIScount(int curIdx, int prevIdx, vector<int> &nums, int n, vector<vector<int>> &dp)
    {
        // --- BASE CASE ---
        // If we reach the end of the array, no more elements can be added.
        if (curIdx == n)
            return 0;

        // We only check the DP table if we have actually picked a previous element (prevIdx > -1).
        if (prevIdx > -1 && dp[curIdx][prevIdx] != -1)
            return dp[curIdx][prevIdx];

        int take = 0, notTake = 0;

        // Valid if it's the very first element picked (-1) OR if it is strictly increasing.
        if (prevIdx == -1 || nums[prevIdx] < nums[curIdx])
        {
            // If taken, length increases by 1, and the current element becomes the new prevIdx.
            take = 1 + recLIScount(curIdx + 1, curIdx, nums, n, dp);
        }

        // Skip this element and carry forward the same prevIdx.
        notTake = recLIScount(curIdx + 1, prevIdx, nums, n, dp);

        // We only store the result in the DP table if prevIdx is a valid array index (> -1).
        if (prevIdx > -1)
        {
            return dp[curIdx][prevIdx] = max(take, notTake);
        }
        else
        {
            // If prevIdx is -1, just return the answer without caching.
            // (It will never be asked for this exact state again anyway!)
            return max(take, notTake);
        }
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        // Initialize an N x N DP table, saving memory by not adding the +1 pad.
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // Start at index 0 with no previous element selected.
        return recLIScount(0, -1, nums, n, dp);
    }

    // -----------------------------------------------------------------------------
    // Approach 2: Iterative DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------------------------
    //
    // Idea:
    //   - Reverse the recursion: fill DP table starting from the end.
    //   - dp[curIdx][prevIdx+1] = LIS length starting from `curIdx`
    //     given last picked index `prevIdx`.
    //   - Iterate backwards to ensure future states are already computed.
    //
    // Transition:
    //   - If we "take" nums[curIdx], then move to curIdx+1 with prevIdx = curIdx.
    //   - If we "skip", then move to curIdx+1 keeping same prevIdx.
    //
    // Base Initialization:
    //   - dp[n][*] = 0 (if index is beyond array → LIS length = 0).
    //
    // Time Complexity: O(n^2)
    //   - Two nested loops over curIdx and prevIdx → O(n * n).
    // Space Complexity: O(n^2)
    //   - DP table of size (n+1) x (n+1).
    //   - Can be optimized to O(n) with space compression.
    // -----------------------------------------------------------------------------

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int curIdx = n - 1; curIdx >= 0; curIdx--)
        {
            for (int prevIdx = curIdx - 1; prevIdx >= -1; prevIdx--)
            {

                int take = 0, notTake = 0;

                // Option 1: Take current element
                if (prevIdx == -1 || nums[prevIdx] < nums[curIdx])
                {
                    take = 1 + dp[curIdx + 1][curIdx + (1)];
                }

                // Option 2: Skip current element
                notTake = dp[curIdx + 1][prevIdx + (1)];

                dp[curIdx][prevIdx + 1] = max(take, notTake);
            }
        }

        return dp[0][-1 + (1)]; // starting at index 0 with prevIdx = -1 (mapped to 0)
    }

    // -----------------------------------------------------------------------------
    // Approach 3: Iterative [1D DP] [RECOMMENDED]
    // Note: This approach
    //            - optimizes space
    //            - Best for Back tracing
    //            - So used for printing LIS
    // -----------------------------------------------------------------------------
    // ---------------------------------------------------------
    /**
     * @brief Computes the length of the Longest Increasing Subsequence (LIS).
     * * --- STATE DEFINITION ---
     * dp[i] represents the length of the longest strictly increasing subsequence
     * that ENDS EXACTLY at the element nums[i-1] (using 1-based indexing).
     * * --- APPROACH ---
     * We initialize the DP array with 1s because every individual number is,
     * at minimum, an increasing subsequence of length 1.
     * As we iterate through the array (curI), we look backwards at every single
     * previous element (prevI). If the current number is strictly greater than
     * the previous number, it means we can safely extend the subsequence that
     * ended at prevI. We take the maximum of all these possible extensions.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2) - The nested loops compare every pair of elements.
     * Space Complexity : O(N)   - We use a single 1D array of size N+1.
     */
    int lengthOfLIS(vector<int> &nums)
    {

        int n = nums.size();

        // Initialize a DP array of size n+1 with 1s.
        // Base case: A single element is always an increasing sequence of length 1.
        vector<int> dp(n + 1, 1);

        // Keeps track of the absolute longest sequence found anywhere in the array.
        int maxLen = 1;

        // curI represents the current element we are evaluating as the "end" of a sequence.
        // (Using 1-based indexing, so it maps to nums[curI-1])
        for (int curI = 1; curI <= n; ++curI)
        {

            // prevI scans every element that came BEFORE curI
            for (int prevI = 1; prevI < curI; ++prevI)
            {

                // STRICTLY INCREASING CHECK:
                // Can we append the current number to the sequence ending at prevI?
                if (nums[prevI - 1] < nums[curI - 1])
                {

                    // If yes, the new sequence length would be the best sequence
                    // from prevI, plus 1 (for the current number).
                    int take = 1 + dp[prevI];

                    // We want the MAXIMUM possible length ending at curI,
                    // so we compare this new 'take' length against whatever we already found.
                    dp[curI] = max(dp[curI], take);
                }
            }

            // Update our global maximum
            maxLen = max(maxLen, dp[curI]);
        }

        // Return the length of the longest sequence found overall
        return maxLen;
    }

    // -----------------------------------------------------------------------------
    // Approach 4: Using Patience Sorting + Binary Search [OPTIMAL]
    // -----------------------------------------------------------------------------
    /**
     * @brief Computes the length of LIS using Greedy + Binary Search (Patience Sorting).
     *
     * * --- THE IDEA (Greedy Strategy) ---
     * To build the longest possible increasing subsequence, we want the numbers
     * inside our sequence to grow as SLOWLY as possible.
     * If we have a choice between ending a sequence of length 2 with a '10' or a '3',
     * we should ALWAYS choose the '3', because a smaller tail makes it much easier
     * to append future numbers!
     * * `sortedSeq[k]` will store the SMALLEST possible tail element for an increasing
     * subsequence of length `k + 1`.
     *
     * Note: The elements inside the sorted sequence don't form a valid sequence from the original array.
     *
     * * --- THE RULES ---
     * As we iterate through 'nums', for every number 'x':
     * 1. If 'x' is larger than the last element in 'sortedSeq', it means we can
     * extend our longest sequence. We just append 'x' to the end.
     * 2. If 'x' is smaller, we can't extend the max length. BUT, we can use 'x'
     * to "upgrade" a previous tail. We use Binary Search to find the first
     * element in 'sortedSeq' that is >= 'x', and we overwrite it with 'x'.
     * (This keeps our tails as small as possible for future numbers).
     *
     * * --- STEP-BY-STEP EXAMPLE ---
     * nums = [10, 9, 2, 5, 3, 7, 101, 18]
     * * 1. x = 10  -> sortedSeq is empty. Append 10.
     * sortedSeq = [10]
     * * 2. x = 9   -> 9 is not > 10. Binary search finds 10. Overwrite 10 with 9.
     * sortedSeq = [9]  (We upgraded our tail for length 1 from 10 to 9!)
     * * 3. x = 2   -> Overwrite 9 with 2.
     * sortedSeq = [2]
     * * 4. x = 5   -> 5 > 2. Append 5.
     * sortedSeq = [2, 5]
     * * 5. x = 3   -> 3 is not > 5. Binary search finds 5. Overwrite 5 with 3.
     * sortedSeq = [2, 3] (Upgraded tail for length 2 from 5 to 3. Brilliant!)
     * * 6. x = 7   -> 7 > 3. Append 7.
     * sortedSeq = [2, 3, 7]
     * * 7. x = 101 -> 101 > 7. Append 101.
     * sortedSeq = [2, 3, 7, 101]
     * * 8. x = 18  -> Overwrite 101 with 18.
     * sortedSeq = [2, 3, 7, 18]
     * * Result: Size is 4. (Notice how the tails were kept perfectly minimal!)
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N log N) - We iterate N times, and each binary search is O(log N).
     * Space Complexity : O(N)       - The sortedSeq array can grow up to size N.
     */
    int lengthOfLIS(vector<int> &nums)
    {

        int n = nums.size();
        if (n == 0)
            return 0;

        // This array holds the smallest tails of all increasing subsequences found.
        vector<int> sortedSeq;

        for (int i = 0; i < n; ++i)
        {

            // RULE 1: If 'sortedSeq' is empty, or the current number is strictly
            // greater than the largest tail we've found, we extend our max length!
            if (sortedSeq.empty() || sortedSeq.back() < nums[i])
            {
                sortedSeq.push_back(nums[i]);
            }
            // RULE 2: If the current number is smaller, we can't extend the length,
            // but we CAN optimize one of our previous tails to be smaller.
            else
            {
                // lower_bound uses binary search to find the FIRST iterator pointing
                // to a value that is greater than or equal to nums[i].
                auto it = lower_bound(sortedSeq.begin(), sortedSeq.end(), nums[i]);

                // Overwrite the old, larger tail with our new, smaller tail.
                *it = nums[i];
            }
        }

        // The length of sortedSeq represents the length of the longest sequence.
        return sortedSeq.size();
    }
};

int main()
{
    return 0;
}
