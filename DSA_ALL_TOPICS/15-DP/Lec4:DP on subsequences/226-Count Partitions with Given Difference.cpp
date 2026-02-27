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

1. Title: Count Partitions with Given Difference

Links:
https://takeuforward.org/data-structure/count-partitions-with-given-difference-dp-18/
https://www.youtube.com/watch?v=zoilQD1kYSg
https://takeuforward.org/plus/dsa/problems/count-partitions-with-given-difference?tab=editorial
https://www.naukri.com/code360/problems/partitions-with-given-difference_3751628?leftPanelTabValue=PROBLEM


Problem statement:
Given an array ‘ARR’, partition it into two subsets (possibly empty) such that their union is the original array. Let the sum of the elements of these two subsets be ‘S1’ and ‘S2’.

Given a difference ‘D’, count the number of partitions in which ‘S1’ is greater than or equal to ‘S2’ and the difference between ‘S1’ and ‘S2’ is equal to ‘D’. Since the answer may be too large, return it modulo ‘10^9 + 7’.

If ‘Pi_Sj’ denotes the Subset ‘j’ for Partition ‘i’. Then, two partitions P1 and P2 are considered different if:

1) P1_S1 != P2_S1 i.e, at least one of the elements of P1_S1 is different from P2_S2.
2) P1_S1 == P2_S2, but the indices set represented by P1_S1 is not equal to the indices set of P2_S2. Here, the indices set of P1_S1 is formed by taking the indices of the elements from which the subset is formed.
Refer to the example below for clarification.
Note that the sum of the elements of an empty subset is 0.

For example :
If N = 4, D = 3, ARR = {5, 2, 5, 1}
There are only two possible partitions of this array.
Partition 1: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
Partition 2: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
These two partitions are different because, in the 1st partition, S1 contains 5 from index 0, and in the 2nd partition, S1 contains 5 from index 2.



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------
Similar question:
2. Title: Target Sum

Links:
    https://takeuforward.org/data-structure/target-sum-dp-21/
    https://takeuforward.org/plus/dsa/problems/target-sum?tab=editorial
    https://leetcode.com/problems/target-sum/description/


Problem statement:
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.



Example 1:
    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3

Example 2:
    Input: nums = [1], target = 1
    Output: 1


Constraints:
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Count Partitions with Given Difference
//-------------------------------------------------------------------------------

/**
 * Problem: Count Partitions with Given Difference
 * -----------------------------------------------
 * Approach: Math + 0/1 Knapsack (Top-Down DP / Memoization)
 *
 * Mathematical Derivation:
 * Let the array be divided into two subsets: S1 and S2.
 * We are given:
 * 1. S1 - S2 = d      (The difference between subsets is d)
 * 2. S1 + S2 = tot    (The sum of both subsets equals the total array sum)
 * * Subtracting equation 1 from equation 2:
 * (S1 + S2) - (S1 - S2) = tot - d
 * 2 * S2 = tot - d
 * S2 = (tot - d) / 2
 *
 * Conclusion:
 * The problem reduces to finding how many subsets in the array sum up to exactly S2.
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N * target)
 * Space Complexity: O(N * target) for DP table + O(N) for recursion stack.
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution
{
private:
    int modulo = 1e9 + 7;

    /**
     * Method: recCount
     * ----------------
     * Recursive helper function to count subsets that sum to 'target'.
     *
     * WHY WE GO DOWN TO (index < 0):
     * You might wonder: "If target == 0, why not just return 1 immediately?"
     * If all elements were strictly > 0, we absolutely could! However, this array
     * can contain 0s.
     * * If we reach target == 0 but still have a '0' left at index 0, there are actually
     * TWO valid subsets: one where we pick the '0', and one where we skip it. If we
     * stopped early, we would only count it as one subset. By forcing the recursion
     * to evaluate every element until the array is fully exhausted (index < 0), we
     * ensure all permutations involving zeros are perfectly counted.
     */
    int recCount(vector<int> &arr, vector<vector<int>> &dp, int target, int index)
    {
        /* Base Case 1: Array fully exhausted */
        if (index < 0)
        {
            if (target == 0)
            {
                return 1; // Valid subset found
            }
            return 0; // Invalid subset
        }

        /* Base Case 2: Overshot the target */
        if (target < 0)
        {
            return 0;
        }

        /* Memoization Check: Return cached result if already computed */
        if (dp[index][target] != -1)
        {
            return dp[index][target];
        }

        /* Choice 1: Skip current element (target remains unchanged) */
        int noTake = recCount(arr, dp, target, index - 1);

        /* Choice 2: Include current element (subtract its value from target) */
        int take = recCount(arr, dp, target - arr[index], index - 1);

        /* Store the result in DP table and apply modulo to prevent overflow */
        return dp[index][target] = (take + noTake) % modulo;
    }

public:
    /**
     * Method: countPartitions
     * -----------------------
     * Prepares the math formulas, validates constraints, and sets up
     * the DP table for the recursive subset-sum function.
     */
    int countPartitions(int n, int d, vector<int> &arr)
    {
        long long tot = 0;

        /* Step 1: Compute total sum of the array */
        for (int el : arr)
        {
            tot += el;
        }

        /* Step 2: Validate if a partition is mathematically possible
           - Condition A: (tot - d) < 0 -> Impossible to have a difference larger than total sum.
           - Condition B: (tot - d) % 2 != 0 -> Difference must allow for an integer subset sum. */
        if ((tot - d) < 0 || (tot - d) % 2 != 0)
        {
            return 0;
        }

        /* Step 3: Calculate the target subset sum for one of the partitions */
        int subsetSum = abs(tot - d) / 2;

        /* Step 4: Initialize DP table with -1 (uncomputed states) */
        vector<vector<int>> dp(n, vector<int>(subsetSum + 1, -1));

        /* Step 5: Start recursion from the last index looking for 'subsetSum' */
        return recCount(arr, dp, subsetSum, n - 1);
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Target sum
//-------------------------------------------------------------------------------

/**
 * Problem: 494. Target Sum
 * ------------------------
 * Approach: Math Reduction + Iterative DP (Bottom-Up Tabulation)
 * * Mathematical Derivation:
 * Let S1 be the subset of numbers assigned '+' and S2 be the subset assigned '-'.
 * 1. S1 - S2 = target
 * 2. S1 + S2 = totalSum
 * Adding them: 2 * S1 = totalSum + target  =>  S1 = (totalSum + target) / 2
 * * We just need to find the number of subsets (S1) that sum to 'targetSum'.
 * * Key Takeaways & Edge Cases Handled:
 * 1. Negative Targets: The constraints say target can be down to -1000.
 * This doesn't break our array indexing because the validation check uses `abs(target)`.
 * Since `totalSum >= abs(target)`, the numerator `(totalSum + target)` is mathematically
 * guaranteed to be >= 0. Thus, `targetSum` will NEVER be negative.
 * 2. Zero Elements: If the array contains 0s, picking or not picking a 0 both yield
 * the same sum but represent TWO distinct valid choices. Starting loops at sum=0
 * and using `+=` during initialization ensures these are counted perfectly.
 * * Complexity:
 * Time: O(N * targetSum)
 * Space: O(N * targetSum) for the 2D DP matrix.
 */
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {

        int N = nums.size();

        // Step 1: Compute total sum
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        // Step 2: Validate if partition is possible
        // Note: totalSum < abs(target) guarantees our calculated targetSum won't be negative!
        if (totalSum < abs(target) || (totalSum + target) % 2 != 0)
        {
            return 0;
        }

        // The exact subset sum we need to find
        int targetSum = (totalSum + target) / 2;

        // Step 3: Initialize DP table
        // dp[i][j] = number of ways to make sum 'j' using elements from index 0 to 'i'
        vector<vector<int>> dp(N, vector<int>(targetSum + 1, 0));

        // Step 4: Base Case Initialization (0th row)
        dp[0][0] = 1; // Note: 1 way to make sum 0 (by picking nothing)

        if (nums[0] <= targetSum)
        {
            // Note: We use += 1 instead of = 1 here. Don't assign blindly!
            // If nums[0] is 0, dp[0][0] becomes 1 + 1 = 2.
            // This elegantly handles the case where the first element is a 0
            // (1 way to not take it, 1 way to take it).
            dp[0][nums[0]] += 1;
        }

        // Step 5: Fill the DP table
        for (int idx = 1; idx < N; ++idx)
        {

            // Note: MUST start with sum == 0, not sum == 1.
            // If nums[idx] == 0, we need the 0th column to update correctly
            // so the number of ways doubles (take the 0 vs don't take the 0).
            for (int sum = 0; sum <= targetSum; ++sum)
            {

                int take = 0;

                // Choice 1: Do not include the current number
                int notTake = dp[idx - 1][sum];

                // Choice 2: Include the current number (if it fits)
                if (nums[idx] <= sum)
                {
                    take = dp[idx - 1][sum - nums[idx]];
                }

                // Total ways is the sum of both choices
                dp[idx][sum] = take + notTake;
            }
        }

        // Return the bottom-right corner of the DP matrix
        return dp[N - 1][targetSum];
    }
};

int main()
{
    return 0;
}
