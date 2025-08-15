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

1. Title: Partition Equal Subset Sum

Links:
https://takeuforward.org/data-structure/partition-equal-subset-sum-dp-15/
https://www.youtube.com/watch?v=7win3dcgo3k
https://takeuforward.org/plus/dsa/problems/partition-equal-subset-sum?tab=editorial
https://leetcode.com/problems/partition-equal-subset-sum/


Problem statement:
Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

Examples:
    Example 1:
    Input: nums = [1,5,11,5]
    Output: true
    Explanation: The array can be partitioned as [1, 5, 5] and [11].

    Example 2:
    Input: nums = [1,2,3,5]
    Output: false
    Explanation: The array cannot be partitioned into equal sum subsets.



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Partition Equal Subset Sum
    //-------------------------------------------------------------------------------

    /**
     * @brief Recursive helper to determine if a subset with the given target sum exists.
     *
     * Approach:
     * - Uses top-down recursion with memoization.
     * - At each step, we can either:
     *      1. Exclude the current element and check the remaining elements.
     *      2. Include the current element and reduce the target accordingly.
     * - The function terminates early if:
     *      - target becomes negative (no valid subset possible).
     *      - target becomes zero (subset found).
     *      - index goes out of bounds without reaching target.
     * - Memoization table `dp[index][target]` stores:
     *      - 1 if subset sum possible for current state.
     *      - 0 if not possible.
     *      - -1 if state not yet computed.
     *
     * Time Complexity:
     * - O(n * k), where n = size of array, k = target sum.
     *   Each (index, target) pair is computed at most once.
     *
     * Space Complexity:
     * - O(n * k) for memoization table.
     * - O(n) recursion stack in worst case (when all elements are considered).
     */
    bool recFind(vector<int> &arr, vector<vector<int>> &dp, int target, int index)
    {

        // Base case: Target becomes negative → invalid path
        if (target < 0)
            return 0;

        // Base case: Target achieved
        else if (target == 0)
        {
            if (index >= 0)
                return dp[index][target] = 1; // store result if within bounds
            else
                return 1; // no need to store if index < 0
        }

        // Base case: No elements left to consider
        else if (index < 0)
            return false;

        // Memoization check
        if (dp[index][target] != -1)
            return dp[index][target];

        // Choice 1: Skip current element
        bool ret = recFind(arr, dp, target, index - 1);
        if (ret)
        {
            return dp[index][target] = 1; // store & return true
        }

        // Choice 2: Include current element
        ret = recFind(arr, dp, target - arr[index], index - 1);
        if (ret)
        {
            return dp[index][target] = 1; // store & return true
        }

        // If both choices fail, store and return false
        return dp[index][target] = 0;
    }

    /**
     * Function: canPartition
     * ----------------------
     * Determines if the given array `nums` can be partitioned into two subsets
     * with equal sums. This is essentially a variation of the Subset Sum problem,
     * where we are looking for a subset that sums to half of the total sum.
     *
     * Time Complexity: O(n * sum/2)
     *   - n = number of elements in the array
     *   - sum = total sum of elements
     *   - We compute states only once due to memoization
     *
     * Space Complexity: O(n * sum/2)
     *   - 2D DP array for memoization
     *
     * Approach:
     * - If total sum is odd, partition is impossible.
     * - Use top-down recursion with memoization to check for subset with sum = totalSum / 2
     */
    bool canPartition(vector<int> &nums)
    {
        int totSum = 0;

        // Step 1: Compute total sum
        for (auto i : nums)
        {
            totSum += i;
        }

        // Step 2: If total sum is odd, can't split equally
        if (totSum % 2 != 0)
            return false;

        int targetSum = totSum / 2;

        // Step 3: Create memoization table initialized to -1 (unvisited)
        // dp[i][s] = whether we can achieve sum `s` from index `i` onwards
        vector<vector<int>> dp(nums.size(), vector<int>(targetSum, -1));

        // Step 4: Try to find a subset with sum = targetSum
        return recFind(nums, dp, targetSum, nums.size() - 1);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
