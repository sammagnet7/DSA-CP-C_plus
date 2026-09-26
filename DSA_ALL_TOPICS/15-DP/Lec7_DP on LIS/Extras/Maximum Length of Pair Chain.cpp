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

1. Title: Maximum Length of Pair Chain

Links:
https://leetcode.com/problems/maximum-length-of-pair-chain/description/


Problem statement:
You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.

You do not need to use up all the given intervals. You can select pairs in any order.



Example 1:
Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4].

Example 2:
Input: pairs = [[1,2],[7,8],[4,5]]
Output: 3
Explanation: The longest chain is [1,2] -> [4,5] -> [7,8].


Constraints:
n == pairs.length
1 <= n <= 1000
-1000 <= lefti < righti <= 1000


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
// 1. Title: Maximum Length of Pair Chain
//-------------------------------------------------------------------------------

class Solution
{
public:
    // -----------------------------------
    // Approach 1: Using LIS [sub-optimal]
    // -----------------------------------

    /**
     * @brief Computes the maximum length of a pair chain using Dynamic Programming.
     * * * --- APPROACH (LIS Variant) ---
     * This solution treats the pairs exactly like a Longest Increasing Subsequence problem.
     * 1. Sort the pairs by their starting values. This guarantees that any valid
     * predecessor pair will always be evaluated before the current pair.
     * 2. Use a 1D DP array where dp[i] represents the max chain length ending exactly at pairs[i].
     * 3. For every pair, look back at all previous pairs. If the previous pair ends
     * strictly before the current pair starts (b < c), we can extend the chain!
     * * * --- COMPLEXITY ---
     * Time Complexity  : O(N log N) for sorting + O(N^2) for the nested loops = O(N^2).
     * Space Complexity : O(N) to store the DP array.
     */
    int findLongestChain(vector<vector<int>> &pairs)
    {

        int n = pairs.size();

        // --- STEP 1: SORT BY START TIME ---
        // We sort by the first element (a[0] < b[0]). In DP, we must process smaller
        // intervals first so their max chain lengths are finalized by the time
        // larger intervals look back at them.
        sort(pairs.begin(), pairs.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });

        // --- STEP 2: DP ARRAY INITIALIZATION ---
        // dp[i] stores the length of the longest valid chain ending at pairs[i].
        // Initialize all to 1, because every individual pair is a valid chain of length 1.
        vector<int> dp(n, 1);

        // Global tracker for the absolute longest chain found anywhere.
        int longestChainLen = 1;

        // --- STEP 3: BOTTOM-UP DP TRANSITIONS ---
        // Outer loop: 'cur' is the pair we are currently trying to append to a chain.
        for (int cur = 0; cur < n; ++cur)
        {

            // Inner loop: 'pre' looks back at all previously evaluated pairs.
            for (int pre = 0; pre < cur; ++pre)
            {

                // Extracting variables to match the problem description perfectly for readability
                int a = pairs[pre][0]; // Start of previous pair
                int b = pairs[pre][1]; // End of previous pair

                int c = pairs[cur][0]; // Start of current pair
                int d = pairs[cur][1]; // End of current pair

                // THE CONDITION: Does the previous pair end strictly before the current one starts?
                if (b < c)
                {
                    // If yes, calculate the potential new chain length
                    int take = 1 + dp[pre];

                    // Take the maximum of what we already have vs this newly extended chain
                    dp[cur] = max(dp[cur], take);
                }
            }

            // --- STEP 4: TRACK GLOBAL MAXIMUM ---
            // Update our global tracker to ensure we don't lose the max value found so far
            longestChainLen = max(longestChainLen, dp[cur]);
        }

        return longestChainLen;
    }

    // ------------------------------------------------
    // Approach 2: Greedy + Earliest end time [OPTIMAL]
    // ------------------------------------------------

    /**
     * @brief Computes the maximum length of a pair chain using a Greedy strategy.
     * * --- APPROACH (Activity Selection / Greedy) ---
     * 1. Sort the pairs strictly by their END times in ascending order.
     * 2. By always choosing the pair that finishes the earliest, we maximize the
     * remaining capacity on the timeline to fit more pairs.
     * 3. Iterate through the sorted pairs. If a pair's start time is strictly
     * greater than our current chain's end time, we safely append it.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N log N) dominated by the sorting step. The subsequent
     * array traversal is just O(N).
     * Space Complexity : O(1) or O(log N) depending on the language's sorting
     * algorithm overhead. We do not allocate any DP arrays!
     */
    int findLongestChain(vector<vector<int>> &pairs)
    {

        int n = pairs.size();
        if (n == 0)
            return 0;

        // --- STEP 1: SORT BY END TIME ---
        // We use a custom lambda to sort based on the second element (pairs[i][1]).
        sort(pairs.begin(), pairs.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });

        // --- STEP 2: INITIALIZE TRACKERS ---
        // We always take the first element in our sorted list because it ends the earliest.
        int maxChainLen = 1;
        int currentEndTime = pairs[0][1];

        // --- STEP 3: GREEDY SCAN ---
        for (int i = 1; i < n; ++i)
        {

            // If the current pair starts strictly after our previous pair ended...
            if (pairs[i][0] > currentEndTime)
            {

                // ...we successfully add it to our chain!
                maxChainLen++;

                // Update our tracker to the end time of this newly added pair
                currentEndTime = pairs[i][1];
            }
        }

        return maxChainLen;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
