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

Similar question:
Target Sum (DP - 21) : follow exact similar approach
    https://takeuforward.org/data-structure/target-sum-dp-21/
    https://takeuforward.org/plus/dsa/problems/target-sum?tab=editorial
    https://leetcode.com/problems/target-sum/description/


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
    // 1. Title: Count Partitions with Given Difference
    //-------------------------------------------------------------------------------
    int modulo = 1e9 + 7;

    // ----------
    // Approach1
    // ----------

    /*
    Function: recCount
    ------------------
    A recursive + memoization function to count the number of ways to partition an array
    into two subsets such that the difference between their sums is exactly `d`.

    Parameters:
        arr     - The input array of integers.
        dp      - 2D memoization table where dp[idx][curSum] stores the computed result for
                  state (idx, curSum).
        d       - Desired difference between subset sums.
        tot     - Total sum of the array elements.
        idx     - Current index being considered in the recursion.
        prevSum - Sum of the chosen elements so far in the recursion path.

    Returns:
        Number of valid partitions from index `idx` onwards that meet the given difference `d`.

    Time Complexity:
        O(n * tot)
        - n = arr.size()
        - tot = total sum of array
        For each index, we compute results for possible `curSum` values up to `tot`.

    Space Complexity:
        O(n * tot) for the `dp` table, plus O(n) recursion stack depth.
*/
    int recDiffCount(vector<int> &arr, vector<vector<int>> &dp, int d, int tot, int idx, long long prevSum)
    {
        /* Base case: If we have processed all elements, no further partitions possible */
        if (idx == arr.size())
            return 0;

        /* Calculate current sum by including arr[idx] in the chosen subset */
        int curSum = prevSum + arr[idx];

        /* If already computed for this state, return stored value */
        if (dp[idx][curSum] != -1)
            return dp[idx][curSum];

        int ret = 0;

        /* If the current partition satisfies (sum(S1) - sum(S2) = d), count this as a valid way */
        if ((2 * curSum - tot) == d)
        {
            ret = 1;
        }

        /* Choice 1: Skip current element */
        ret += recDiffCount(arr, dp, d, tot, idx + 1, prevSum);

        /* Choice 2: Include current element */
        ret += recDiffCount(arr, dp, d, tot, idx + 1, prevSum + arr[idx]);

        /* Store and return result modulo `modulo` constant */
        return dp[idx][curSum] = ret % modulo;
    }

    /*
        Function: countPartitions
        -------------------------
        Computes the total number of partitions of the array into two subsets
        whose difference in sum equals `d`.

        Parameters:
            n   - Number of elements in the array.
            d   - Desired difference between subset sums.
            arr - The input array.

        Returns:
            Number of valid partitions.

        Time Complexity:
            O(n * tot) — where `tot` is total sum of elements.

        Space Complexity:
            O(n * tot) — for memoization table.
    */
    int countPartitions(int n, int d, vector<int> &arr)
    {
        long long tot = 0;

        /* Compute total sum of array elements */
        for (int el : arr)
        {
            tot += el;
        }

        /* Initialize memoization table with -1 (uncomputed states) */
        vector<vector<int>> dp(arr.size(), vector<int>(tot + 1, -1));

        /* Start recursion from index 0 with initial sum 0 */
        return recDiffCount(arr, dp, d, tot, 0, 0);
    }

    // ----------
    // Approach2
    // ----------

    /*
        Function: recCount
        ------------------
        A recursive + memoization approach to count the number of subsets
        from the given array that sum up to the target value.

        Special handling is done for index == 0 to correctly count subsets
        when the first element is zero (because zero can be included or excluded
        without changing the sum, giving multiple ways).

        Approach:
            - If index == 0: handle as base case (taking care of zeros explicitly).
            - If target < 0: no valid subset possible.
            - Otherwise, recursively explore two choices:
                1. Skip the current element (noTake)
                2. Include the current element (take)
            - Use memoization table dp[index][target] to store computed results
              to avoid recomputation.
            - Apply modulo to prevent integer overflow.

        Time Complexity:
            O(n * target)
            - n: number of elements
            - target: desired subset sum
            Each state (index, target) is computed at most once.

        Space Complexity:
            O(n * target) for dp table + O(n) recursion stack space.

        Parameters:
            arr    : input array of integers
            dp     : memoization table initialized with -1
            target : required sum to achieve
            index  : current index in the array

        Returns:
            Number of subsets (modulo 'modulo') that sum up to 'target'.
    */
    int recCount(vector<int> &arr, vector<vector<int>> &dp, int target, int index)
    {
        /* Base case: if we are at the first element (index == 0) */
        if (index == 0)
        {
            /* Case 1: If target == 0 and arr[0] == 0, two valid subsets: {} and {0} */
            if (target == 0 && arr[0] == 0)
                return dp[index][target] = 2;
            /* Case 2: If target == 0 (arr[0] != 0), only {} works */
            if (target == 0)
                return dp[index][target] = 1;
            /* Case 3: If target equals arr[0], only {arr[0]} works */
            if (target == arr[0])
                return dp[index][target] = 1;
            /* Otherwise: no valid subset */
            else
                return 0;
        }

        /* If target becomes negative -> invalid path */
        if (target < 0)
            return 0;

        /* Check if result already computed */
        if (dp[index][target] != -1)
            return dp[index][target];

        /* Choice 1: Skip current element */
        int noTake = recCount(arr, dp, target, index - 1);

        /* Choice 2: Include current element */
        int take = recCount(arr, dp, target - arr[index], index - 1);

        /* Store and return result (modulo applied) */
        return dp[index][target] = (take + noTake) % modulo;
    }

    /*
        Function: countPartitions
        -------------------------
        Given an array and a difference 'd', counts the number of ways to split
        the array into two subsets such that the absolute difference of their sums
        equals 'd'.

        Approach:
            - Let total sum = sum(arr)
            - Partition problem can be transformed to finding number of subsets
              with sum = (total - d) / 2
            - If (total - d) is odd, no valid partitions exist
            - Use recCount() to count the number of subsets of sum = (total - d)/2

        Time Complexity:
            O(n * subsetSum) where subsetSum = (total - d)/2

        Space Complexity:
            O(n * subsetSum) for dp table + recursion stack space O(n)

        Parameters:
            n   : number of elements
            d   : required difference
            arr : input array

        Returns:
            Number of valid partitions.
    */
    int countPartitions(int n, int d, vector<int> &arr)
    {

        long long tot = 0;

        /* Compute total sum of array */
        for (int el : arr)
        {
            tot += el;
        }

        /* Step 2: Check if (tot - d) is valid for subset sum formulation
        - If negative: impossible since d is too large in magnitude.
        - If odd: impossible because sum difference must be even. */
        if ((tot - d) < 0 || (tot - d) % 2 != 0)
            return 0;

        /* Target subset sum for one partition */
        int subsetSum = abs(tot - d) / 2;

        /* Initialize dp table with -1 */
        vector<vector<int>> dp(n, vector<int>(subsetSum + 1, -1));

        /* Count number of subsets with sum = subsetSum */
        return recCount(arr, dp, subsetSum, n - 1);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
