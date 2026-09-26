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

1. Title: Longest Bitonic Subsequence

Links:
https://takeuforward.org/data-structure/longest-bitonic-subsequence-dp-46/
https://www.youtube.com/watch?v=y4vN0WNdrlg
https://takeuforward.org/plus/dsa/problems/longest-bitonic-subsequence?tab=editorial
https://www.naukri.com/code360/problems/longest-bitonic-sequence_1062688?leftPanelTabValue=PROBLEM

Problem statement:
A Bitonic Sequence is a sequence of numbers that is first strictly increasing and then strictly decreasing.
A strictly ascending order sequence is also considered bitonic, with the decreasing part as empty, and same for a strictly descending order sequence.

For example, the sequences [1, 3, 5, 3, 2], [1, 2, 3, 4] are bitonic, whereas the sequences [5, 4, 1, 4, 5] and [1, 2, 2, 3] are not.
You are given an array 'arr' consisting of 'n' positive integers.
Find the length of the longest bitonic subsequence of 'arr'.

Example :
Input: 'arr' = [1, 2, 1, 2, 1]
Output: 3
Explanation: The longest bitonic subsequence for this array will be [1, 2, 1]. Please note that [1, 2, 2, 1] is not a valid bitonic subsequence, because the consecutive 2's are neither strictly increasing, nor strictly decreasing.


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
// 1. Title: Longest Bitonic Subsequence
//-------------------------------------------------------------------------------

class Solution
{
public:
    //------------------------------------------------------
    // Approach 1: Recursive [Extra space]
    //------------------------------------------------------
    /**
     * @brief Recursive helper using Top-Down DP with a State Machine to find the Longest Bitonic Subsequence.
     *
     * * * --- THE IDEA (The Continuous State Machine) ---
     * This approach builds the sequence in a single left-to-right pass. It treats a bitonic sequence as
     * a subsequence where you are allowed to change your direction from "increasing" to
     * "decreasing" exactly ONCE.
     *
     *
     * * * --- STATE DEFINITION ---
     * dp[curI][preI][flipped]
     * 1. curI    : The current index we are evaluating to "Take" or "Not Take".
     * 2. preI    : The index of the last element we successfully added to our sequence.
     * 3. flipped : A boolean representing our current phase.
     * false = We are in the strictly INCREASING phase.
     * true  = We have peaked and are now in the strictly DECREASING phase.
     *
     *
     * * * --- STATE TRANSITIONS ---
     * - If arr[preI] < arr[curI] (Numbers are going UP):
     * -> If !flipped: We can TAKE it and remain !flipped.
     * -> If flipped:  We CANNOT take it (violates the decreasing rule).
     *
     * - If arr[preI] > arr[curI] (Numbers are going DOWN):
     * -> If !flipped: We can TAKE it, but this forces us to FLIP our state to true (we peaked!).
     * -> If flipped:  We can TAKE it and happily remain flipped.
     *
     * - If arr[preI] == arr[curI] (Numbers are EQUAL):
     * -> Violates "strictly" increasing/decreasing. We are forced to NOT TAKE.
     *
     *
     * * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2). We evaluate each (curI, preI, flipped) state exactly once.
     * Space Complexity : O(N^2). The 3D DP table allocates N * N * 2 integers.
     */
    int rec(int curI, int preI, bool flipped, vector<int> &arr, vector<vector<vector<int>>> &dp)
    {

        // --- BASE CASE ---
        // If we have evaluated the entire array, no more elements can be added.
        if (curI == arr.size())
        {
            return 0;
        }

        // --- MEMOIZATION CHECK ---
        // We only check the DP table if we have actually picked a previous element (preI > -1).
        if (preI > -1 && dp[curI][preI][flipped] != -1)
        {
            return dp[curI][preI][flipped];
        }

        int take = 0;
        // SKIP (We always have the option to not take the current element)
        int notTake = rec(curI + 1, preI, flipped, arr, dp);

        // --- BRANCH 1: THE SEQUENCE IS GOING UP (or it's the very first element) ---
        if (preI == -1 || arr[preI] < arr[curI])
        {

            // If we haven't peaked yet, we are allowed to take this larger number.
            if (!flipped)
            {
                // TAKE: Length increases by 1, state remains !flipped.
                take = 1 + rec(curI + 1, curI, false, arr, dp);
            }
            // If we HAVE peaked (flipped), we are not allowed to take larger numbers anymore.
        }
        // --- BRANCH 2: THE SEQUENCE IS GOING DOWN ---
        else if (arr[preI] > arr[curI])
        {

            // If we haven't peaked yet, taking this smaller number FORCES us to peak.
            if (!flipped)
            {
                // TAKE: Length increases by 1, and we FLIP the state to true!
                take = 1 + rec(curI + 1, curI, true, arr, dp);
            }
            // If we are already in the decreasing phase (flipped), we can keep taking smaller numbers.
            else if (flipped)
            {
                // TAKE: Length increases by 1, state remains flipped.
                take = 1 + rec(curI + 1, curI, true, arr, dp);
            }
        }

        // Evaluate the best choice we could make from this position
        int ret = max(take, notTake);

        // --- MEMOIZATION STORE ---
        // If preI is -1, there is only one unique path to get here, so we don't cache it.
        // Otherwise, cache the result in our 3D state table.
        if (preI == -1)
        {
            return ret;
        }
        else
        {
            return dp[curI][preI][flipped] = ret;
        }
    }

    int longestBitonicSubsequence(vector<int> &arr, int n)
    {
        // Initialize the 3D DP table with -1.
        // Dimensions: [N current indices] x [N previous indices] x [2 boolean states]
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));

        // Start at index 0, with no previous element (-1), and in the increasing phase (false).
        return rec(0, -1, false, arr, dp);
    }

    //------------------------------------------------------
    // Approach 2: Iterative [Extra space]
    //------------------------------------------------------
    /*
     Logic:
     1. Use a 2D dp array of size 2 x n:
        - dp[0][i] = length of longest increasing subsequence ending at index i
        - dp[1][i] = length of longest (increasing then->) decreasing subsequence ending at index i
     2. Iterate through each element cur from 1 to n-1:
         a) Compare with all previous elements pre (0 to cur-1)
         b) If arr[pre] < arr[cur], we can extend the increasing subsequence:
            dp[0][cur] = max(dp[0][cur], dp[0][pre]+1)
         c) If arr[pre] > arr[cur], we can extend a decreasing subsequence:
            dp[1][cur] = max(dp[1][cur], max(dp[0][pre]+1, dp[1][pre]+1))
            (We can start decreasing from an increasing sequence or continue decreasing)
     3. Finally, for each index i, the longest bitonic subsequence ending at i is:
        max(dp[0][i], dp[1][i])
     4. Return the maximum among all indices.

     Time Complexity: O(n^2)
         - Two nested loops: cur (1..n-1) and pre (0..cur-1)
     Space Complexity: O(2*n) ~ O(n)
         - dp array with two rows: increasing and decreasing
 */
    int longestBitonicSubsequence(vector<int> &arr, int n)
    {
        // dp[0][i] = LIS ending at i, dp[1][i] = LDS ending at i
        vector<vector<int>> dp(2, vector<int>(n, 1));

        for (int cur = 1; cur < n; cur++)
        {
            for (int pre = 0; pre < cur; pre++)
            {

                if (arr[pre] < arr[cur])
                { // Increasing case
                    int newCount_inc = dp[0][pre] + 1;
                    if (newCount_inc > dp[0][cur])
                    {
                        dp[0][cur] = newCount_inc;
                    }
                }
                else if (arr[pre] > arr[cur])
                { // Decreasing case
                    // Can start decreasing from an increasing sequence or continue decreasing
                    int newCount_dec = max(dp[0][pre] + 1, dp[1][pre] + 1);
                    if (newCount_dec > dp[1][cur])
                    {
                        dp[1][cur] = newCount_dec;
                    }
                }
            }
        }

        // Find the maximum among all dp values
        int maxLength = 0;
        for (int i = 0; i < n; i++)
        {
            maxLength = max(maxLength, max(dp[0][i], dp[1][i]));
        }

        return maxLength;
    }

    //------------------------------------------------------
    // Approach 3: Uses Forward + Backward LIS [RECOMMENDED]
    //------------------------------------------------------
    /**
     * @brief Computes the length of the Longest Bitonic Subsequence.
     * * * --- THE INTUITION ("The Peak") ---
     * A Bitonic Sequence goes strictly up, reaches a "peak", and then goes strictly down.
     * If we pick any element `arr[i]` and declare it as the "peak", the longest bitonic
     * sequence centered exactly at `arr[i]` is composed of two parts:
     * 1. The Longest Increasing Subsequence (LIS) ending at `arr[i]` (coming from the left).
     * 2. The Longest Decreasing Subsequence (LDS) starting at `arr[i]` (going to the right).
     *
     *
     * * * --- THE LOGIC (3-Step Strategy) ---
     * Step 1: Run the standard LIS algorithm from left to right. `dp1[i]` will store the
     * length of the longest increasing sequence ending at index `i`.
     *
     * Step 2: Run the LIS algorithm from right to left. `dp2[i]` will store the length
     * of the longest decreasing sequence starting at index `i`.
     *
     * Step 3: Loop through the array one last time, treating every element as a potential
     * peak.
     *  The total length of the bitonic sequence at peak `i` is:
     * `dp1[i] + dp2[i] - 1` (We subtract 1 because `arr[i]` is counted twice).
     *
     *
     * * * --- EDGE CASES HANDLED ---
     * The problem states a strictly increasing or strictly decreasing sequence is also valid.
     * Our formula handles this naturally! If an array is strictly increasing, `dp2[i]` will
     * just be `1` everywhere, making `dp1[i] + 1 - 1 = dp1[i]`.
     *
     *
     * * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2)
     * We run two separate nested loops (each taking N^2 time) to build the dp1 and dp2 arrays.
     * Space Complexity : O(N)
     * We allocate two 1D arrays of size N to store the left and right subsequence lengths.
     */
    int longestBitonicSubsequence(vector<int> &arr, int n)
    {

        // Edge case: An empty array has a bitonic sequence of length 0.
        if (n == 0)
            return 0;

        // --- STEP 1: LIS from Left to Right ---
        vector<int> dp1(n, 1);
        for (int i = 0; i < n; i++)
        {
            for (int prev = 0; prev < i; prev++)
            {
                // If the sequence is strictly increasing
                if (arr[prev] < arr[i])
                {
                    dp1[i] = max(dp1[i], 1 + dp1[prev]);
                }
            }
        }

        // --- STEP 2: LDS from Right to Left ---
        // (Which is identical to finding an LIS, but iterating backward)
        vector<int> dp2(n, 1);
        for (int i = n - 1; i >= 0; i--)
        {
            // Look at elements to the right of 'i'
            for (int prev = n - 1; prev > i; prev--)
            {
                // If the sequence is strictly decreasing as we move right
                // (meaning arr[prev] is smaller than arr[i])
                if (arr[prev] < arr[i])
                {
                    dp2[i] = max(dp2[i], 1 + dp2[prev]);
                }
            }
        }

        // --- STEP 3: Find the Maximum Bitonic Length ---
        int maxBitonicLen = 0;

        // Treat every index as the "peak" of the sequence
        for (int i = 0; i < n; i++)
        {

            // Combine the left increasing part and the right decreasing part,
            // subtracting 1 to avoid double-counting the peak element itself.
            int currentBitonicLen = dp1[i] + dp2[i] - 1;

            // Track the global maximum
            maxBitonicLen = max(maxBitonicLen, currentBitonicLen);
        }

        return maxBitonicLen;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
