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

1. Title: Number of Longest Increasing Subsequences

Links:
https://takeuforward.org/data-structure/number-of-longest-increasing-subsequences-dp-47/
https://www.youtube.com/watch?v=cKVl1TFdNXg
https://takeuforward.org/plus/dsa/problems/number-of-longest-increasing-subsequences?tab=editorial
https://leetcode.com/problems/number-of-longest-increasing-subsequence/


Problem statement:
Given an integer array nums, return the number of longest increasing subsequences.
Notice that the sequence has to be strictly increasing.

Examples:
    Example 1:
    Input: nums = [1,3,5,4,7]
    Output: 2
    Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

    Example 2:
    Input: nums = [2,2,2,2,2]
    Output: 5
    Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.

Constraints:
    1 <= nums.length <= 2000
    -10^6 <= nums[i] <= 10^6
    The answer is guaranteed to fit inside a 32-bit integer.



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
// 1. Title: Number of Longest Increasing Subsequences
//-------------------------------------------------------------------------------
class Solution
{
public:
    /**
     * @brief Computes the total number of Longest Increasing Subsequences.
     *
     * * * --- STATE DEFINITION ---
     * dp[cur]    : Max length of a strictly increasing subsequence ending exactly at index 'cur'.
     * count[cur] : Number of ways to form an LIS of length dp[cur] ending exactly at 'cur'.
     *
     * * * --- APPROACH (Single-Pass Parallel DP) ---
     * 1. Every element is initially an LIS of length 1, with exactly 1 way to form it.
     * 2. As we evaluate 'cur', we look back at 'pre'. If nums[pre] < nums[cur], we can extend it.
     * - If extending gives a STRICTLY LONGER sequence, we overwrite dp[cur] and inherit count[pre].
     * - If extending gives a sequence of the EXACT SAME length, we found an alternative path!
     * We add count[pre] to count[cur].
     * 3. We maintain global trackers (`maxlen` and `countLcs`) on-the-fly to avoid a second pass.
     *
     * * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2) for the nested loops comparing every pair.
     * Space Complexity : O(N) to store the parallel `dp` and `count` arrays.
     */
    int findNumberOfLIS(vector<int> &nums)
    {

        int n = nums.size();

        // Initialize parallel arrays.
        // Base case: every individual number is a sequence of length 1, and there is 1 way to make it.
        vector<int> dp(n, 1), count(n, 1);

        // Global trackers for the absolute longest sequence length and its total count across the array.
        int maxlen = 1;
        int countLcs = 0; // Note: 'Lcs' usually stands for Longest Common Subsequence, but acts as our LIS counter here.

        // Outer loop: 'cur' is the end of the subsequence we are currently building.
        for (int cur = 0; cur < n; ++cur)
        {

            // Inner loop: 'pre' looks back at all previously evaluated elements.
            for (int pre = 0; pre < cur; ++pre)
            {

                // Check if appending nums[cur] to nums[pre] maintains a strictly increasing sequence.
                if (nums[pre] < nums[cur])
                {

                    // Calculate the potential new length if we extend the sequence ending at 'pre'.
                    int take = 1 + dp[pre];

                    // SCENARIO 1: We found a strictly longer sequence path!
                    if (dp[cur] < take)
                    {
                        dp[cur] = take;          // Update the max length for 'cur'
                        count[cur] = count[pre]; // Reset the ways to reach 'cur' to match 'pre'
                    }
                    // SCENARIO 2: We found a tie! Another path of the exact same max length.
                    else if (dp[cur] == take)
                    {
                        count[cur] += count[pre]; // Add the alternative paths to our running total for 'cur'
                    }
                }
            }

            // Did the sequence ending at 'cur' break the global length record?
            if (maxlen < dp[cur])
            {
                maxlen = dp[cur];      // Set a new global max length
                countLcs = count[cur]; // Reset the global count to match this new record
            }
            // Did it tie the current global length record?
            else if (maxlen == dp[cur])
            {
                countLcs += count[cur]; // Accumulate these paths into the global total
            }
        }

        // Return the accumulated count of all sequences that reached the maximum length
        return countLcs;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
