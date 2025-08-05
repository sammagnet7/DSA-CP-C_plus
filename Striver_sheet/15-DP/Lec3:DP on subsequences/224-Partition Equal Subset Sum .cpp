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
     * Helper Function: recFind
     * ------------------------
     * Recursive function with memoization to determine if a subset of `arr`
     * starting from `index` can form a sum equal to `target`.
     *
     * Parameters:
     * - arr: input array of numbers
     * - dp: memoization table
     * - target: target sum to achieve
     * - index: current index in the array
     * - prevSum: running sum of current subset
     */
    bool recFind(vector<int> &arr, vector<vector<int>> &dp, int target, int index, int prevSum)
    {
        // Base Case 1: Reached end of array or sum exceeded
        if (index == arr.size() || prevSum > target)
            return false;

        // Base Case 2: Found a subset whose sum equals the target
        if ((prevSum + arr[index]) == target)
        {
            dp[index][prevSum] = 1; // Memoize as true
            return true;
        }

        // Memoization Check
        if (dp[index][prevSum] != -1)
            return dp[index][prevSum] == 1;

        // Option 1: Skip current element
        bool ret = recFind(arr, dp, target, index + 1, prevSum);
        if (ret)
        {
            dp[index][prevSum] = 1;
            return true;
        }

        // Option 2: Include current element in sum
        ret = recFind(arr, dp, target, index + 1, prevSum + arr[index]);
        if (ret)
        {
            dp[index][prevSum] = 1;
            return true;
        }

        // If both options fail, mark as not possible
        dp[index][prevSum] = 0;
        return false;
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
        return recFind(nums, dp, targetSum, 0, 0);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
