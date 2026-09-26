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

1. Title: Printing Longest Increasing Subsequence

Links:
https://takeuforward.org/data-structure/printing-longest-increasing-subsequence-dp-42/
https://www.youtube.com/watch?v=IFfYfonAFGc
https://takeuforward.org/plus/dsa/problems/print-longest-increasing-subsequence?tab=editorial
https://www.naukri.com/code360/problems/printing-longest-increasing-subsequence_8360670?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array 'arr' of length 'n'.
Find the Longest Increasing Subsequence of the array.
A subsequence is a subset of an array achieved by removing some (possibly 0) elements without changing the order of the remaining elements.
Increasing subsequence means a subsequence in which all the elements are strictly increasing.
Longest increasing subsequence is an increasing subsequence that has the largest length possible.
Please note that there may be more than one LIS (Longest Increasing Subsequence) possible. Return any one of the valid sequences.

Example:
Input: ‘arr’ = [5, 6, 3, 4, 7, 6]
Output: LIS = [5, 6, 7] OR [3, 4, 7] OR [3, 4, 6]
Explanation: All these three subsequences are valid Longest Increasing Subsequences. Returning any of them is correct.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Printing Longest Increasing Subsequence
//-------------------------------------------------------------------------------

class Solution
{
public:
    // -----------------------------------------------------------------------------
    // Approach 1: Iterative DP (Bottom-Up Tabulation) => Then Trace-back
    //             Note: This same trace-back won't work for Top-down dp. Need tweak.
    // -----------------------------------------------------------------------------
    //
    // Approach:
    // 1. Bottom-up DP table construction (tabulation).
    //    - dp[curIdx][prevIdx+1] stores the length of LIS
    //      starting from index curIdx, given the last taken element is prevIdx.
    //    - Offset (+1) is used for prevIdx to handle -1 (no element taken yet).
    // 2. Traceback using the dp table to actually build the LIS sequence.
    //    - At each step, check if including arr[curIdx] was part of the optimal LIS.
    //    - If yes, add it to the subsequence and update prevIdx.
    //    - Otherwise, skip to the next index.
    //
    // **NoteS:**
    // 1. What the DP table stores
    //      In your bottom-up DP for LIS:
    //      dp[curIdx][prevIdx+1] = length of LIS starting at curIdx when previous chosen index is prevIdx.
    //      The recurrence compares two choices:
    //      Take arr[curIdx] (if valid) ? 1 + dp[curIdx+1][curIdx+1]
    //      Not take arr[curIdx] ? dp[curIdx+1][prevIdx+1]
    //      So when we build LIS, we can trace which branch (take / notTake) gave the maximum.
    // 2. Traceback idea
    //      Start at (curIdx=0, prevIdx=-1):
    //      At each step:
    //           If dp[curIdx][prevIdx+1] == 1 + dp[curIdx+1][curIdx+1] (and condition prevIdx==-1 || arr[prevIdx]<arr[curIdx] holds), then we took arr[curIdx].
    //                Add arr[curIdx] to the LIS sequence.
    //                Move to (curIdx+1, prevIdx=curIdx).
    //           Else, we didn?t take ? move to (curIdx+1, prevIdx).
    //         Stop when curIdx == n.
    //
    //
    // Time Complexity: O(n^2)
    //   - Outer loop over curIdx (n iterations)
    //   - Inner loop over prevIdx (up to n iterations)
    //   - Traceback loop O(n)
    //   - Total: O(n^2)
    //
    // Space Complexity: O(n^2)
    //   - DP table of size (n+1) x (n+1)
    //   - LIS vector output of size at most O(n)
    //
    // ---------------------------------------------------------

    vector<int> printingLongestIncreasingSubsequence(vector<int> arr, int n)
    {
        // DP table: dp[curIdx][prevIdx+1] = LIS length starting at curIdx with prevIdx
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Bottom-up DP filling
        for (int curIdx = n - 1; curIdx >= 0; curIdx--)
        {
            for (int prevIdx = curIdx - 1; prevIdx >= -1; prevIdx--)
            {

                int take = 0, notTake = 0;

                // Option 1: Take current element if increasing condition satisfied
                if (prevIdx == -1 || arr[prevIdx] < arr[curIdx])
                {
                    take = 1 + dp[curIdx + 1][curIdx + 1]; // include arr[curIdx]
                }

                // Option 2: Skip current element
                notTake = dp[curIdx + 1][prevIdx + 1];

                // Store the best option
                dp[curIdx][prevIdx + 1] = max(take, notTake);
            }
        }

        // Length of LIS can be obtained at dp[0][0] (start with no element chosen)
        int lisLen = dp[0][0];
        vector<int> lis;

        // Traceback phase: Reconstruct LIS from DP table
        int curIdx = 0;
        int prevIdx = -1;

        while (curIdx < n)
        {
            // Check if taking arr[curIdx] leads to optimal solution
            bool check1 = (dp[curIdx][prevIdx + 1] == 1 + dp[curIdx + 1][curIdx + 1]);
            // Check increasing property
            bool check2 = (prevIdx == -1 || arr[prevIdx] < arr[curIdx]);

            if (check1 && check2)
            {
                // If both checks satisfied ? arr[curIdx] is part of LIS
                lis.push_back(arr[curIdx]);
                prevIdx = curIdx; // Update last taken index
            }
            curIdx++; // Move to next element
        }

        return lis;
    }

    // -----------------------------------------------------------------------------
    // Approach 2: Iterative DP (Tabulation) [RECOMMENDED]
    // Note: This approach
    //            - optimizes space
    //            - Best for Back tracing
    //            - So used for printing LIS
    // -----------------------------------------------------------------------------
    /**
     * @brief Computes and reconstructs the actual Longest Increasing Subsequence (LIS).
     * * --- THE APPROACH (DP + Parent Pointers) ---
     * 1. Calculate the LIS using standard O(N^2) 1D DP.
     * 2. Maintain a `prev` array. Whenever we update `dp[curI]` to a better length
     * by appending to `prevI`, we record `prev[curI] = prevI`. This creates a
     * chain of indices we can follow backward.
     * 3. Track the index `lisLastI` where the absolute longest sequence ends.
     * 4. Trace backward from `lisLastI` using the `prev` array to build the sequence,
     * then reverse it to get the correct forward order.
     * * --- COMPLEXITY ---
     * Time Complexity: O(N^2) to build the DP table, plus O(N) to reconstruct. Total: O(N^2).
     * Space Complexity: O(N) for the dp array, prev array, and the answer array.
     */
    vector<int> printingLongestIncreasingSubsequence(vector<int> arr, int n)
    {

        // dp[i] stores the max length of LIS ending at index i. Initialized to 1.
        // prev[i] stores the index of the previous element in the LIS ending at i.
        // Initialized to -1 (meaning "no previous element / start of sequence").
        vector<int> dp(n, 1), prev(n, -1);

        // Trackers for the global maximum LIS
        int maxLen = 1;

        // Default the last index to the end of the array. (If the array is strictly
        // decreasing, any single element is a valid LIS of length 1, so picking n-1 is safe).
        int lisLastI = n - 1;

        // --- STEP 1: BUILD DP TABLE & PARENT POINTERS ---
        for (int curI = 0; curI < n; ++curI)
        {

            // Look back at all previous elements
            for (int prevI = 0; prevI < curI; ++prevI)
            {

                // Check if we can strictly increase the sequence
                if (arr[prevI] < arr[curI])
                {

                    // Calculate the potential new length if we append arr[curI] to arr[prevI]
                    int take = 1 + dp[prevI];

                    // If this new length is strictly better than what we currently have for curI...
                    if (dp[curI] < take)
                    {

                        // 1. Update the max length for curI
                        dp[curI] = take;

                        // 2. PARENT TRACKING: Remember that prevI is the element that
                        // gave us this optimal length!
                        prev[curI] = prevI;
                    }
                }
            }

            // --- STEP 2: TRACK THE GLOBAL MAXIMUM ---
            // After fully evaluating curI, check if it forms the longest sequence seen so far globally.
            if (maxLen < dp[curI])
            {
                maxLen = dp[curI];
                // Update the starting point for our backward reconstruction
                lisLastI = curI;
            }
        }

        // --- STEP 3: RECONSTRUCT THE SEQUENCE ---
        vector<int> ans;

        // Start tracing back from the index that holds the end of the global longest sequence
        int i = lisLastI;

        // Follow the breadcrumbs in the `prev` array until we hit -1 (the start of the sequence)
        while (i != -1)
        {
            ans.push_back(arr[i]); // Add the actual value to our answer
            i = prev[i];           // Jump backwards to the parent index
        }

        // Because we traced backwards from the end to the start, our sequence is in reverse order.
        // Reverse it to get the correct chronological LIS!
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
