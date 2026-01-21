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

1. Title: Subset Sum Equal To K

Links:
https://takeuforward.org/data-structure/subset-sum-equal-to-target-dp-14/
https://www.youtube.com/watch?v=fWX9xDmIzRI
https://www.naukri.com/code360/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM


Problem statement:
You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.


Time Limit: 1 sec
Sample Input 1:
2
4 5
4 3 2 1
5 4
2 5 1 6 7
Sample Output 1:
true
false
Explanation For Sample Input 1:
In example 1, ‘ARR’ is {4,3,2,1} and ‘K’ = 5. There exist 2 subsets with sum = 5. These are {4,1} and {3,2}. Hence, return true.
In example 2, ‘ARR’ is {2,5,1,6,7} and ‘K’ = 4. There are no subsets with sum = 4. Hence, return false.
Sample Input 2:
2
4 4
6 1 2 1
5 6
1 7 2 9 10
Sample Output 2:
true
false
Explanation For Sample Input 2:
In example 1, ‘ARR’ is {6,1,2,1} and ‘K’ = 4. There exist 1 subset with sum = 4. That is {1,2,1}. Hence, return true.
In example 2, ‘ARR’ is {1,7,2,9,10} and ‘K’ = 6. There are no subsets with sum = 6. Hence, return false.


Hints:
1. Can you find every possible subset of ‘ARR’ and check if its sum is equal to ‘K’?
2. Can you use dynamic programming and use the previously calculated result to calculate the new result?
3. Try to use a recursive approach followed by memoization by including both index and sum we can form.



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
    // 1. Title: Subset Sum Equal To K
    //-------------------------------------------------------------------------------

    //-----------------------------------------------
    // Approach1: Recursive
    //-----------------------------------------------

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
     * - O(n * target), where n = size of array, target = target sum.
     *   Each (index, target) pair is computed at most once.
     *
     * Space Complexity:
     * - O(n * target) for memoization table.
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
     * @brief Checks if a subset with sum equal to target exists in the array.
     *
     * @param n   Size of array
     * @param target   Target sum
     * @param arr Input array
     *
     * @return true if such subset exists, false otherwise.
     *
     * Approach:
     *   - Standard Subset Sum dynamic programming with memoization.
     *   - State: dp[i][target] = whether it is possible to form "target" using
     *     elements from arr[0..i].
     *   - Transition: include arr[i] or exclude arr[i].
     *   - Recursion depth O(n), total states O(n * target).
     *
     * Complexity:
     *   - Time Complexity: O(n * target) (each state solved once).
     *   - Space Complexity: O(n * target) for the DP table + O(n) recursion stack.
     *
     * Practical limits (important):
     *   - Memory use ≈ n * (target+1) integers.
     *     * With 4-byte ints: ~4 * n * target bytes.
     *   - For n ~ 100 and target ~ 10^5 → ~40 MB (borderline but feasible).
     *   - For n ~ 1000 and target ~ 10^4 → ~40 MB (feasible).
     *   - For target ~ 10^6 and n ~ 100 → ~400 MB (too large).
     *   - For very large target (like 10^9, as in "Meet in the Middle" problem),
     *     this DP is **impossible** due to memory/time blowup.
     *
     * Rule of thumb:
     *   - Suitable if n * target ≤ ~10^7 (time) and memory ≤ a few hundred MB.
     *   - If target is very large (≥10^7–10^8), switch to:
     *       • Bitset optimization (O(n*target/word_size)) for feasibility,
     *       • Or alternative strategies like "Meet in the Middle" if n ≤ 40.
     */
    bool subsetSumToK(int n, int target, vector<int> &arr)
    {
        // Memoization table initialized to -1 (unvisited states)
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));

        // Start recursion from last index with target target
        return recFind(arr, dp, target, n - 1);
    }

    //-----------------------------------------------
    // Approach2: Iterative
    //-----------------------------------------------

    /*
     * Function: subsetSumToK
     * ----------------------
     * Determines if there exists a subset of 'arr' that sums up to 'target'.
     *
     * Approach: Bottom-Up Dynamic Programming (Tabulation)
     *
     * State Definition:
     * DP[i][sum] = true if it is possible to achieve 'sum' using a subset of
     * elements from index 0 to i. Otherwise false.
     *
     * Complexity:
     * Time: O(N * Target)
     * Space: O(N * Target)
     */
    bool subsetSumToK(int n, int target, vector<int> &arr)
    {

        // DP Table Initialization
        // Rows (n): Elements of the array considered so far.
        // Cols (target+1): All possible target sums from 0 to 'target'.
        // Initialized to 'false' assuming no sum is possible initially.
        vector<vector<bool>> DP(n, vector<bool>(target + 1, false));

        // ---------------------------------------------------------
        // 1. Base Case: Sum = 0
        // ---------------------------------------------------------
        // It is ALWAYS possible to achieve a target sum of 0 (by choosing an empty subset).
        // This is true for any index, but we specifically set it for the 0th row
        // to kickstart the iteration. (Later loops will propagate this 'true' down).
        DP[0][0] = true;

        // ---------------------------------------------------------
        // 2. Base Case: First Element (Index 0)
        // ---------------------------------------------------------
        // If we only have the first element arr[0], we can only achieve a sum equal to arr[0].
        // IMPORTANT NOTE: We must check if arr[0] <= target to avoid accessing
        // an index outside the DP table bounds.
        if (arr[0] <= target)
        {
            DP[0][arr[0]] = true;
        }

        // ---------------------------------------------------------
        // 3. Iterate Tabulation
        // ---------------------------------------------------------
        for (int i = 1; i < n; i++)
        {

            // Check for every possible sum from 0 to target
            for (int sum = 0; sum <= target; sum++)
            {

                bool take = false;
                bool notTake = false;

                // Option 1: Take the current element arr[i]
                // We can only take it if the current required 'sum' is greater than or equal to arr[i].
                // If we take it, we check if the remaining sum (sum - arr[i]) was possible
                // using the previous elements (row i-1).
                if (sum - arr[i] >= 0)
                {
                    take = DP[i - 1][sum - arr[i]];
                }

                // Option 2: Do not take the current element
                // If we don't take arr[i], the possibility depends entirely on whether
                // the current 'sum' was already achievable using previous elements (row i-1).
                notTake = DP[i - 1][sum];

                // Final Logic:
                // If EITHER taking the element OR not taking it leads to a valid solution,
                // then the current state is valid (true).
                DP[i][sum] = take || notTake;
            }
        }

        // Return the result for the full array (index n-1) and the desired target.
        return DP[n - 1][target];
    }

    //-----------------------------------------------
    // Approach3: Iterative 2 1D arrays[OPTIMAL]
    //-----------------------------------------------

    /*
     * Function: subsetSumToK
     * ----------------------
     * Space Optimized Bottom-Up Dynamic Programming.
     * * Instead of a full 2D table DP[N][Target], we only need the previous row
     * to calculate the current row.
     * * Complexity:
     * Time: O(N * Target)
     * Space: O(Target)  <-- Significantly reduced from O(N*Target)
     */
    bool subsetSumToK(int n, int target, vector<int> &arr)
    {

        // 1. Initialize 'prev' array (Represents row i-1)
        // Size is target+1 to cover sums from 0 to target.
        vector<bool> prev(target + 1, false);

        // We can also define 'cur' here, or inside the loop.
        // 'cur' represents the current row i.
        vector<bool> cur(target + 1, false);

        // ---------------------------------------------------------
        // 2. Base Case Initialization (Equivalent to Row 0)
        // ---------------------------------------------------------

        // Base Case 1: Target Sum = 0
        // It is always possible to make sum 0 (empty subset).
        prev[0] = true;

        // Base Case 2: First Element arr[0]
        // If we are at index 0, we can achieve sum == arr[0] by taking it.
        // Check bounds to prevent crash.
        if (arr[0] <= target)
        {
            prev[arr[0]] = true;
        }

        // ---------------------------------------------------------
        // 3. Iterate (From Index 1 to N-1)
        // ---------------------------------------------------------
        for (int i = 1; i < n; i++)
        {

            // Calculate 'cur' state based on 'prev' state
            // Important: We must also handle sum=0 for the 'cur' row effectively.
            // Since prev[0] is true, notTake (prev[sum]) handles it automatically.
            for (int sum = 0; sum <= target; sum++)
            {

                bool take = false;
                bool notTake = false;

                // Option 1: Not Take
                // If we don't take arr[i], can we achieve 'sum' using previous elements?
                // Look at the same column in the previous row.
                notTake = prev[sum];

                // Option 2: Take
                // Check if valid index, then look at the shifted index in previous row.
                if (sum - arr[i] >= 0)
                {
                    take = prev[sum - arr[i]];
                }

                // Update Current State
                cur[sum] = take || notTake;
            }

            // ---------------------------------------------------------
            // 4. Shift States
            // ---------------------------------------------------------
            // The current row ('cur') becomes the previous row ('prev')
            // for the next iteration.
            prev = cur;
        }

        // ---------------------------------------------------------
        // 5. Return Result
        // ---------------------------------------------------------
        // CRITICAL FIX: Return 'prev[target]', NOT 'cur[target]'.
        // Reason: If n=1, the loop above never runs. 'cur' remains all false.
        // The correct answer for n=1 is stored in 'prev' during initialization.
        // For n>1, 'prev' is updated to 'cur' at the end of the loop, so it is valid there too.
        return prev[target];
    }
    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
