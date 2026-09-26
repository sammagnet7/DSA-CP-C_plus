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

1. Title: Build Array Where You Can Find The Maximum Exactly K Comparisons

Links:
https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/description/


Problem statement:
You are given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:

You should build the array arr which has the following properties:
    ```cpp
    maximum_value = -1
    maximum_index = -1
    search_cost = 0
    n = arr.length
    for (i = 0; i < n; i++) {
        if (maximum_value < arr[i]) {
            maximum_value = arr[i]
            maximum_index = i
            search_cost = search_cost + 1
        }
    }
    return maximum_index
    ```

arr has exactly n integers.
1 <= arr[i] <= m where (0 <= i < n).
After applying the mentioned algorithm to arr, the value search_cost is equal to k.
Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the answer must be computed modulo 109 + 7.


Example 1:
Input: n = 2, m = 3, k = 1
Output: 6
Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]

Example 2:
Input: n = 5, m = 2, k = 3
Output: 0
Explanation: There are no possible arrays that satisfy the mentioned conditions.

Example 3:
Input: n = 9, m = 1, k = 1
Output: 1
Explanation: The only possible array is [1, 1, 1, 1, 1, 1, 1, 1, 1]


Constraints:
1 <= n <= 50
1 <= m <= 100
0 <= k <= n


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
// 1. Title: Build Array Where You Can Find The Maximum Exactly K Comparisons
//-------------------------------------------------------------------------------

class Solution
{
private:
    int MOD = 1e9 + 7;

    /**
     * @brief Recursively builds the array and counts valid configurations.
     * * * --- STATE DEFINITION ---
     * dp[idx][prevMax][prevCost]
     * 1. idx      : Current index of the array we are placing a number into.
     * 2. prevMax  : The maximum number we have placed in the array so far.
     * 3. prevCost : How many times the maximum has been updated (search cost).
     * * * --- TRANSITIONS & OPTIMIZATIONS ---
     * We have two main choices for the current number:
     * - "Hide": Pick a number <= prevMax. The cost and max do not change.
     * - "Peak": Pick a number > prevMax. The cost and max both increase.
     * * * --- COMPLEXITY ---
     * Time Complexity  : O(N * M^2 * K).
     * Space Complexity : O(N * M * K) for the 3D memoization table.
     */
    int recCount(int idx, int prevMax, int prevCost, vector<vector<vector<int>>> &dp, int n, int m, int k)
    {

        // --- BASE CASES ---
        // Success: We filled the array of size 'n' and hit exactly the target cost 'k'.
        if (idx == n && prevCost == k)
        {
            return 1;
        }
        // Failure: We went out of bounds OR exceeded our allowed target cost.
        if (idx >= n || prevCost > k)
        {
            return 0;
        }

        // --- MEMOIZATION CHECK ---
        // If we have already solved this exact subproblem, return the cached result.
        if (dp[idx][prevMax][prevCost] != -1)
        {
            return dp[idx][prevMax][prevCost];
        }

        int curCount = 0;

        // --- OPTIMIZATION: PRE-COMPUTE "HIDE" STATE ---
        // Since choosing any number <= prevMax leads to the exact same recursive state,
        // we calculate it ONCE here. This prevents pushing the exact same parameters
        // to the call stack inside the loop, massively speeding up execution.
        int notIncreasing = recCount(idx + 1, prevMax, prevCost, dp, n, m, k);

        // Evaluate all possible numbers we can place at the current 'idx'
        for (int curVal = 1; curVal <= m; ++curVal)
        {

            // SCENARIO 1: "Hide" behind the current maximum
            if (curVal <= prevMax)
            {
                // Use the pre-calculated result instead of making a redundant recursive call
                curCount = (curCount + notIncreasing) % MOD;
            }
            // SCENARIO 2: "Peak" and become the new maximum
            else
            {
                // --- BRILLIANT PRUNING ---
                // Since curVal is strictly increasing, every subsequent number in this loop
                // will also be a new maximum. If our cost is already at 'k', we can't afford
                // any more maximums. We can safely abort the rest of the loop entirely!
                if (prevCost >= k)
                {
                    break;
                }
                else
                {
                    // Cost increases by 1, and our new maximum is curVal.
                    curCount = (curCount + recCount(idx + 1, curVal, prevCost + 1, dp, n, m, k)) % MOD;
                }
            }
        }

        // Cache the calculated total for this state and return it
        return dp[idx][prevMax][prevCost] = curCount;
    }

public:
    int numOfArrays(int n, int m, int k)
    {

        // Initialize the 3D DP matrix with -1
        // Dimensions: [n array slots] x [m maximum value + 1] x [k maximum cost + 1]
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));

        // Kick off the recursion starting at index 0, with a max of 0, and cost of 0.
        return recCount(0, 0, 0, dp, n, m, k);
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
