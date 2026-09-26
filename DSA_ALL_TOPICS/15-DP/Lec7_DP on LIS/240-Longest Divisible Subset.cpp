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

1. Title: Longest Divisible Subset

Links:
https://takeuforward.org/data-structure/longest-divisible-subset-dp-44/
https://www.youtube.com/watch?v=gDuZwBW9VvM
https://takeuforward.org/plus/dsa/problems/largest-divisible-subset?tab=editorial
https://leetcode.com/problems/largest-divisible-subset/description/

Problem statement:
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
    answer[i] % answer[j] == 0, or
    answer[j] % answer[i] == 0
If there are multiple solutions, return any of them.

Examples:
    Example 1:
    Input: nums = [1,2,3]
    Output: [1,2]
    Explanation: [1,3] is also accepted.

    Example 2:
    Input: nums = [1,2,4,8]
    Output: [1,2,4,8]


Constraints:
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 109
    All the integers in nums are unique.

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
// 1. Title: Longest Divisible Subset
//-------------------------------------------------------------------------------
class Solution
{
public:
    /**
     * @brief Computes and reconstructs the Largest Divisible Subset.
     *
     *
     * * --- THE APPROACH (LIS Variant + Math Transitivity) ---
     * 1. Sort the array. This guarantees that for any valid subset [a, b, c]
     * where a < b < c, we only need to check if c % b == 0. If it is,
     * transitivity ensures c % a == 0 is also true!
     *
     * 2. Use a DP array to track the longest subset ending at each index.
     *
     * 3. Use a 'pre' (parent) array to remember exactly which previous element
     * gave us the optimal length.
     *
     * 4. Trace backward from the best ending index to reconstruct the subset.
     *
     *
     * * --- COMPLEXITY ---
     * Time Complexity: O(N log N) for sorting + O(N^2) for the nested DP loops = O(N^2).
     * Space Complexity: O(N) to store the dp and parent arrays.
     */
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {

        // --- STEP 1: THE CRUCIAL SORT ---
        // Sorting guarantees that we only ever check smaller divisors against
        // larger multiples, unlocking the transitivity rule.
        sort(nums.begin(), nums.end());

        int n = nums.size();

        // Edge case safety (though LeetCode constraints guarantee n >= 1)
        if (n == 0)
            return {};

        // dp[i] stores the max length of a divisible subset ending at index i.
        // pre[i] stores the index of the previous element in that subset.
        vector<int> dp(n, 1), pre(n, -1);

        // Trackers for the global maximum subset found anywhere in the array.
        int maxLen = 1;

        // Initialize to n-1. If no elements divide each other (e.g., [2, 3, 5]),
        // any single element is a valid subset of length 1. Picking the last one is fine.
        int lastIdx = n - 1;

        // --- STEP 2: BUILD DP TABLE & PARENT POINTERS ---
        for (int curI = 1; curI < n; ++curI)
        {

            // Look back at all smaller numbers before curI
            for (int prevI = 0; prevI < curI; ++prevI)
            {

                // THE CONDITION: Is curI completely divisible by prevI?
                if (nums[curI] % nums[prevI] == 0)
                {

                    // If yes, we can append curI to the subset that ended at prevI
                    int take = 1 + dp[prevI];

                    // If this forms a strictly longer subset than what curI currently has:
                    if (dp[curI] < take)
                    {

                        // 1. Update the max length for curI
                        dp[curI] = take;

                        // 2. PARENT TRACKING: Remember that prevI is the element that
                        // successfully divided curI to give us this optimal length!
                        pre[curI] = prevI;
                    }
                }
            }

            // --- STEP 3: TRACK THE GLOBAL MAXIMUM ---
            // After evaluating all predecessors for curI, check if it forms
            // the longest divisible subset seen so far globally.
            if (maxLen < dp[curI])
            {
                maxLen = dp[curI];

                // Update the starting point for our backward reconstruction
                lastIdx = curI;
            }
        }

        // --- STEP 4: RECONSTRUCT THE SUBSET ---
        vector<int> ans;

        // Start tracing back from the index that holds the end of the longest subset
        int i = lastIdx;

        // Follow the breadcrumbs in the 'pre' array until we hit -1
        while (i != -1)
        {
            ans.push_back(nums[i]); // Add the actual value to our answer
            i = pre[i];             // Jump backwards to the parent index
        }

        // Because we traced backwards, the subset is currently largest-to-smallest.
        // Reverse it to return it in standard smallest-to-largest order.
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
