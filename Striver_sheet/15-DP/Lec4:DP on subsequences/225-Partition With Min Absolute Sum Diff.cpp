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

1. Title: Partition Set Into 2 Subsets With Min Absolute Sum Diff
            [Array having non-negative only and partitions can be of any sizes]

Links:
https://takeuforward.org/data-structure/partition-set-into-2-subsets-with-min-absolute-sum-diff-dp-16/
https://www.youtube.com/watch?v=GS_OqZb2CWc
https://takeuforward.org/plus/dsa/problems/partition-a-set-into-two-subsets-with-minimum-absolute-sum-difference?tab=editorial
https://www.naukri.com/code360/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494

Problem statement:
You are given an array 'arr' containing 'n' non-negative integers.
Your task is to partition this array into two subsets such that the absolute difference between subset sums is minimum.
You just need to find the minimum absolute difference considering any valid division of the array elements.

Note:
1. Each array element should belong to exactly one of the subsets.
2. Subsets need not always be contiguous.
3. Here each subset size need to be same
4. No negetive elements are present in given array

For example, for the array : [1, 2, 3], some of the possible divisions are
   a) {1,2} and {3}
   b) {1,3} and {2}.
3. Subset-sum is the sum of all the elements in that subset.
Example:
Input: 'n' = 5, 'arr' = [3, 1, 5, 2, 8].
Ouput: 1
Explanation: We can partition the given array into {3, 1, 5} and {2, 8}.
This will give us the minimum possible absolute difference i.e. (10 - 9 = 1).

Example:
    Sample Input 1:
    4
    1 2 3 4
    Sample Output 1:
    0
    Explanation for sample input 1:
    We can partition the given array into {2,3} and {1,4}.
    This will give us the minimum possible absolute difference i.e. (5 - 5 = 0) in this case.
    Sample Input 2:
    3
    8 6 5
    Sample Output 2:
    3
    Explanation for sample input 2:
    We can partition the given array into {8} and {6,5}.
    This will give us the minimum possible absolute difference i.e. (11 - 8 = 3).

Expected time complexity:
The expected time complexity is O(n * 𝚺 'arr'[i]), where 𝚺 'arr'[i] denotes the sum of all elements in 'arr'.

Constraints:
1 <= 'n' <= 10^3
0 <= 'arr'[i] <= 10^3
0 <= 𝚺 'arr'[i] <= 10^4,
where 𝚺 'arr'[i] denotes the sum of all elements in 'arr'.

Time Limit: 1sec



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Partition Array Into Two Arrays to Minimize Sum Difference with
            [Array having negetives and partitions  are of same size]

Links:
https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/



Problem statement:
You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
Return the minimum possible absolute difference.

Note:
    1. Array having negetives as well
    2. Partitions must be of same size i.e. N/2

Examples:
    Example 1:
    Input: nums = [3,9,7,3]
    Output: 2
    Explanation: One optimal partition is: [3,9] and [7,3].
    The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.

    Example 2:
    Input: nums = [-36,36]
    Output: 72
    Explanation: One optimal partition is: [-36] and [36].
    The absolute difference between the sums of the arrays is abs((-36) - (36)) = 72.

    Example 3:
    Input: nums = [2,-1,0,4,-2,-9]
    Output: 0
    Explanation: One optimal partition is: [2,4,-9] and [-1,0,-2].
    The absolute difference between the sums of the arrays is abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0.


Constraints:
1 <= n <= 15
nums.length == 2 * n
-107 <= nums[i] <= 107


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Partition Set Into 2 Subsets With Min Absolute Sum Diff
    //      [Array having non-negative only and partitions can be of any sizes]
    //-------------------------------------------------------------------------------

    // ----------
    // Approach1
    // ----------

    /*
        Approach: Recursive Backtracking with Memoization (Top-Down DP)
        ---------------------------------------------------------------
        The goal is to partition the given array into two subsets such that
        the absolute difference between their sums is minimized.

        Key idea:
        - Total sum = S
        - Let one subset have sum = curSum
        - Then the other subset has sum = S - curSum
        - The absolute difference = abs(S - 2*curSum)
        - We try all possible subset sums using recursion with memoization
        and track the minimum abs(S - 2*curSum)

        Note: This code assumes all elements are non-negative.

        Time Complexity:
        - There are N elements and at most 'total' unique values for curSum
        - So: O(N * total) in worst case

        Space Complexity:
        - DP table of size O(N * total)
    */

    // Recursive helper function to explore subset sums
    // nums         : input array
    // dp           : 2D memoization table to store minimum difference at [idx][curSum]
    // minDiff      : reference to global minimum difference so far
    // total        : total sum of all elements in the array
    // targetLength : number of elements we aim to pick (not essential here, but kept for generality)
    // curSum       : current accumulated sum of picked elements
    // idx          : current index in nums we are processing
    void traverseMinDiff(vector<int> &nums, vector<vector<bool>> &dp, int &minDiff, int total, int targetLength, int curSum, int idx)
    {

        // Calculate the current difference between two subsets
        int absDiff = abs(total - 2 * curSum); // (Sum of other subset - curSum)

        // Update minimum difference
        minDiff = min(minDiff, absDiff);

        // Base case: if index is out of bounds or we've already computed this state
        if (idx == nums.size() || dp[idx][curSum])
            return;

        // Explore possibility of excluding the current element
        traverseMinDiff(nums, dp, minDiff, total, targetLength, curSum, idx + 1);

        // Explore possibility of including the current element
        traverseMinDiff(nums, dp, minDiff, total, --targetLength, curSum + nums[idx], idx + 1);

        // Memoize the result to avoid recomputation
        dp[idx][curSum] = true;
    }

    // Main function to compute the minimum subset sum difference
    int minSubsetSumDifference(vector<int> &nums, int N)
    {
        int minDiff = INT_MAX;   // Initialize answer with a large number
        int total = 0;           // Will hold the sum of all elements
        int n = nums.size() / 2; // Not essential here; retained from previous context

        // Compute total sum of the array
        for (int el : nums)
        {
            total += el;
        }

        // Create a 2D DP array initialized with INT_MIN
        // dp[i][j] represents the minimum difference possible using first i elements and current sum j
        vector<vector<bool>> dp(nums.size(), vector<bool>(total + 1, false));

        // Start recursive traversal
        traverseMinDiff(nums, dp, minDiff, total, n, 0, 0);

        // Return the minimum difference found
        return minDiff;
    }
};

// ----------------------
// Approach 2 [Mine]
// ----------------------
class Solution
{
public:
    /*
     * Function: rec
     * -------------
     * Recursively generates subset sums to find the minimum difference.
     * * Parameters:
     * - idx: Current element index we are considering.
     * - sum: The current sum of "Subset A".
     * - totalSum: The total sum of all elements (used to derive Subset B's sum).
     * - DP: A memoization table. DP[idx][sum] = true means "we have already explored
     * this state".
     * - ans: Reference to the global minimum difference found so far.
     */
    void rec(int idx, int sum, int totalSum, vector<vector<bool>> &DP, vector<int> &nums, int &ans)
    {

        // ---------------------------------------------------------
        // 1. Base Case: Processed all elements
        // ---------------------------------------------------------
        if (idx == nums.size())
        {
            // 'sum' represents the sum of Subset A.
            // The remaining elements must form Subset B.
            int a = sum;
            int b = totalSum - sum;

            // Calculate absolute difference
            int diff = abs(a - b);

            // Update the global minimum answer
            ans = min(ans, diff);
            return;
        }

        // ---------------------------------------------------------
        // 2. Memoization Check (Pruning)
        // ---------------------------------------------------------
        // If we have already reached this specific state (at this index with this sum),
        // there is no need to proceed. We've already explored all paths from here
        // in a previous branch of the recursion.
        if (DP[idx][sum])
        {
            return;
        }

        // ---------------------------------------------------------
        // 3. Recursive Transitions (Take / Not Take)
        // ---------------------------------------------------------

        // Option A: Include nums[idx] in Subset A
        // We move to the next index (idx+1) and add the value to 'sum'.
        rec(idx + 1, sum + nums[idx], totalSum, DP, nums, ans);

        // Option B: Do Not Include nums[idx] in Subset A
        // (This implies nums[idx] will be in Subset B).
        // We move to the next index (idx+1) but keep 'sum' unchanged.
        rec(idx + 1, sum, totalSum, DP, nums, ans);

        // ---------------------------------------------------------
        // 4. Mark State as Visited
        // ---------------------------------------------------------
        // Record that we have processed this state so we don't repeat work.
        DP[idx][sum] = true;
    }

    int minSubsetSumDifference(vector<int> &nums, int n)
    {
        int N = n;

        // Calculate the total sum of the array
        long long totalSum = accumulate(nums.begin(), nums.end(), (long long)0);

        // Initialize answer to a large value
        int ans = INT_MAX;

        // Initialize DP table.
        // Rows: Index (0 to N-1)
        // Cols: Possible Sums (0 to TotalSum).
        // Note: Technically we only need cols up to TotalSum/2 + something,
        // but TotalSum is safe bounds.
        vector<vector<bool>> DP(N, vector<bool>(totalSum + 1, false));

        // Start recursion from index 0 with current sum 0
        rec(0, 0, totalSum, DP, nums, ans);

        return ans;
    }
};

// ----------------------
// Approach 3
// ----------------------

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

    // Base case: Target becomes negative ? invalid path
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
 * @brief Computes the minimum difference between the sums of two subsets of the given array.
 *
 * Approach:
 * - Let `total` be the sum of all elements.
 * - The problem reduces to finding a subset with sum as close as possible to `total / 2`.
 * - Uses `recFind()` to fill a boolean dp table marking achievable subset sums.
 * - The minimum difference is then computed by:
 *      min(|total - 2 * subset_sum|) over all achievable subset sums.
 *      Because (s1+s2=tot;) and (s1-s2 = d;) =>(d=tot-2*s2)
 *
 * Time Complexity:
 * - O(N * total), where `total` = sum of array.
 *   Because each (index, sum) state is computed once.
 *
 * Space Complexity:
 * - O(N * total) for dp table.
 * - O(N) recursion stack space.
 */
int minSubsetSumDifference(vector<int> &nums, int N)
{
    int total = 0;
    for (int el : nums)
        total += el; // Compute total sum

    // dp[i][sum] = 1 if a subset using first i+1 elements can form 'sum'
    vector<vector<int>> dp(N, vector<int>(total + 1, -1));

    // Fill dp table for all possible sums
    for (int sum = total; sum >= 0; sum--)
        recFind(nums, dp, sum, N - 1);

    int minDiff = INT_MAX;

    // Check achievable sums and track minimum difference
    for (int sum = total; sum >= 0; sum--)
    {
        if (dp[N - 1][sum])
        {
            int diff = abs(2 * sum - total);
            minDiff = min(minDiff, diff);
        }
    }

    return minDiff;
}

//-------------------------------------------------------------------------------
// 2. Title: Partition Array Into Two Arrays to Minimize Sum Difference with
//      [Array having negetives and partitions  are of same size]
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
