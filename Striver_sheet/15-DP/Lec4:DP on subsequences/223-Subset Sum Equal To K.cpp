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

    // Approach1
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
     * @brief Checks if a subset with sum equal to k exists in the array.
     *
     * @param n   Size of array
     * @param k   Target sum
     * @param arr Input array
     *
     * @return true if such subset exists, false otherwise.
     *
     * Time Complexity: O(n * k)
     * Space Complexity: O(n * k) + O(n) recursion stack
     */
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        // Memoization table initialized to -1 (unvisited states)
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));

        // Start recursion from last index with target k
        return recFind(arr, dp, k, n - 1);
    }

    //-------------------------------------------------------------------------------
    // Approach2
    /**
     * Function: subsetSumToK
     * ----------------------
     * Determines if there exists a subset in `arr` of size `n` whose sum equals `k`.
     * This approach uses bottom-up dynamic programming with a 2D DP table.
     *
     * Time Complexity: O(n * k)
     *   - Outer loop runs for each element (n)
     *   - Inner loop runs for each target sum from 1 to k
     *
     * Space Complexity: O(n * k)
     *   - DP table stores boolean states: dp[i][j] = true if a subset of the first i+1 elements can sum to j
     */
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        vector<vector<bool>> dp(n, vector<bool>(k + 1, false)); // [index][target sum]

        // Base case: sum 0 is always achievable with empty subset
        for (int idx = 0; idx < n; idx++)
        {
            dp[idx][0] = true;
        }

        // Base case: first element alone can contribute to a sum if it's ? k
        if (arr[0] <= k)
            dp[0][arr[0]] = true;

        // Fill the DP table
        for (int idx = 1; idx < n; idx++)
        {
            for (int target = 1; target <= k; target++)
            {
                bool take = false, notTake = false;

                // Include current element if it does not exceed target
                if (target >= arr[idx])
                    take = dp[idx - 1][target - arr[idx]];

                // Exclude current element
                notTake = dp[idx - 1][target];

                dp[idx][target] = take || notTake;
            }
        }

        // Final answer: is target k achievable using all n elements?
        return dp[n - 1][k];
    }

    //-------------------------------------------------------------------------------
    // Approach3: [OPTIMAL]
    /**
     * Function: subsetSumToK
     * ----------------------
     * Optimized version of the 2D DP approach by using 1D space.
     * At each index, we maintain only the current and previous rows of DP.
     *
     * Time Complexity: O(n * k)
     * Space Complexity: O(k)
     *   - Reduces space from O(n * k) to O(k) using rolling array technique
     */
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        vector<bool> prev(k + 1, false);

        // Base cases
        prev[0] = true; // Always possible to make sum 0
        if (arr[0] <= k)
            prev[arr[0]] = true;

        for (int idx = 1; idx < n; idx++)
        {
            vector<bool> cur(k + 1, false);

            for (int target = 1; target <= k; target++)
            {
                bool take = false, notTake = false;

                // Include current element if it fits
                if (target >= arr[idx])
                    take = prev[target - arr[idx]];

                // Exclude current element
                notTake = prev[target];

                cur[target] = take || notTake;
            }

            // Move to next state
            prev = cur;
            prev[0] = true; // sum 0 always possible
        }

        return prev[k];
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
