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

1. Title: 0/1 Knapsack

Links:
https://takeuforward.org/data-structure/0-1-knapsack-dp-19/
https://www.youtube.com/watch?v=GqOmJHQZivw&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=22
https://www.naukri.com/code360/problems/0-1-knapsack_920542?leftPanelTabValue=PROBLEM


Problem statement:
A thief is robbing a store and can carry a maximal weight of W into his knapsack.
There are N items and the ith item weighs wi and is of value vi.
Considering the constraints of the maximum weight that a knapsack can carry,
you have to find and return the maximum value that a thief can generate by stealing items.

Sample Input:
1
4
1 2 4 5
5 4 8 6
5
Sample Output:
13

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
    // 1. Title: 0/1 Knapsack
    //-------------------------------------------------------------------------------

    /*
    ===============================================================================
        Approach 1:
        ---------
        1. Recursive definition:
           - We consider items from index `idx` down to 0.
           - For each item, we have two choices:
                a) Exclude it ? move to the next item (idx-1) without reducing capacity.
                b) Include it ? add its value and reduce capacity by its weight.
           - Take the maximum of these two choices.

        2. Memoization:
           - To avoid recomputation, we store results in a 2D DP table:
                dp[idx][remainingCapacity]
             which stores the maximum value obtainable from items 0..idx
             with the given remaining knapsack capacity.

        Time Complexity:
        ----------------
        O(n * maxWeight)
            - Each state (idx, sackSize) is computed once.
            - At most 'n' items and 'maxWeight+1' capacities.

        Space Complexity:
        -----------------
        O(n * maxWeight)  ? DP table
        O(n) recursion stack (due to function calls)
        Total: O(n * maxWeight + n)

    ===============================================================================
    */

    /**
     * Recursive helper function to find the maximum value for given remaining capacity.
     *
     * @param weight   Vector storing item weights.
     * @param value    Vector storing item values.
     * @param dp       2D memoization table.
     * @param sackSize Remaining knapsack capacity.
     * @param idx      Current item index under consideration.
     * @return         Maximum value achievable from items[0..idx] with 'sackSize' capacity.
     */
    int maxValRec(vector<int> weight, vector<int> value, vector<vector<int>> &dp,
                  int sackSize, int idx)
    {
        // Base case: no items left
        if (idx < 0)
            return 0;

        // If already computed, return stored result (memoization)
        if (dp[idx][sackSize] != -1)
            return dp[idx][sackSize];

        // Choice 1: Exclude current item
        int maxVal = maxValRec(weight, value, dp, sackSize, idx - 1);

        // Choice 2: Include current item (only if it fits in remaining capacity)
        if (weight[idx] <= sackSize)
        {
            // Add value of current item and solve remaining capacity
            maxVal = max(maxVal, value[idx] +
                                     maxValRec(weight, value, dp, sackSize - weight[idx], idx - 1));
        }

        // Store result in dp table before returning
        return dp[idx][sackSize] = maxVal;
    }

    /**
     * Main function to solve the knapsack problem with Recursice Memoization.
     *
     * @param weight    Vector storing item weights.
     * @param value     Vector storing item values.
     * @param n         Number of items.
     * @param maxWeight Maximum capacity of knapsack.
     * @return          Maximum value achievable.
     */
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
    {
        // Create DP table of size n x (maxWeight+1), initialized to -1
        // dp[i][w] = max value from items[0..i] with capacity w
        vector<vector<int>> dp(weight.size(), vector<int>(maxWeight + 1, -1));

        // Call recursive solver starting from last item (n-1) and full capacity
        return maxValRec(weight, value, dp, maxWeight, n - 1);
    }

    /*
    ===============================================================================
        Approach 2:
        ---------
        1. Bottom-Up Dynamic Programming:
           - We build a DP table where:
                dp[i][w] = maximum value achievable from items[0..i] with capacity w.
           - Start by filling the first row (i = 0) for all capacities >= weight[0].
             For these capacities, the best value is simply value[0].
           - For each subsequent item:
                a) Exclude it ? value remains dp[i-1][w].
                b) Include it ? value is value[i] + dp[i-1][w - weight[i]].
             Take the maximum of these two choices.

        2. Iterative filling:
           - Outer loop ? items (index from 1 to n-1).
           - Inner loop ? capacities (1 to maxWeight).
           - This ensures subproblems are solved before being used.

        Time Complexity:
        ----------------
        O(n * maxWeight)
            - Each of the n items processes all capacities from 1 to maxWeight.

        Space Complexity:
        -----------------
        O(n * maxWeight) ? DP table storing all subproblem results.

    ===============================================================================
    */

    /**
     * Solves the 0/1 Knapsack problem using iterative Bottom-Up DP.
     *
     * @param weight    Vector storing item weights.
     * @param value     Vector storing item values.
     * @param n         Number of items.
     * @param maxWeight Maximum capacity of knapsack.
     * @return          Maximum value achievable.
     */
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
    {
        int N = weight.size();

        // Create DP table: dp[i][w] = max value from items[0..i] with capacity w
        vector<vector<int>> dp(weight.size(), vector<int>(maxWeight + 1, 0));

        // Base case: fill first row for capacities >= weight[0]
        if (weight[0] <= maxWeight)
        {
            for (int k = weight[0]; k <= maxWeight; k++)
            {
                dp[0][k] = value[0];
            }
        }

        // Fill DP table iteratively
        for (int idx = 1; idx < N; idx++)
        {
            for (int sackSize = 1; sackSize <= maxWeight; sackSize++)
            {

                // Choice 1: Exclude current item
                int maxVal = dp[idx - 1][sackSize];

                // Choice 2: Include current item (only if it fits in remaining capacity)
                if (weight[idx] <= sackSize)
                {
                    // Add value of current item and check previous row for remaining capacity
                    maxVal = max(maxVal, value[idx] +
                                             dp[idx - 1][sackSize - weight[idx]]);
                }

                // Store the best of the two choices
                dp[idx][sackSize] = maxVal;
            }
        }

        // Final answer: max value using all items and full capacity
        return dp[N - 1][maxWeight];
    }

    /*
    ===============================================================================
        Approach 3:
        ---------
        1. Bottom-Up Dynamic Programming (Space Optimized):
           - Instead of storing all n rows in a DP table, we only keep two 1D arrays:
                prev[w] ? results for previous item index
                cur[w]  ? results for current item index
           - This works because dp[i][w] only depends on dp[i-1][*] (the previous row).

        2. Initialization:
           - For the first item (index 0), fill prev[w] = value[0] for all w >= weight[0].

        3. Iterative filling:
           - For each item index `idx` from 1 to N-1:
                a) Choice 1: Exclude current item ? max value is prev[w].
                b) Choice 2: Include current item (if it fits) ? value[idx] + prev[w - weight[idx]].
                c) Store the best in cur[w].
           - After processing current item, set prev = cur for the next iteration.

        Time Complexity:
        ----------------
        O(n * maxWeight)
            - Each of the n items processes all capacities from 1 to maxWeight.

        Space Complexity:
        -----------------
        O(maxWeight) ? Only two arrays of size maxWeight+1 are used.

    ===============================================================================
    */

    /**
     * Solves the 0/1 Knapsack problem using iterative Bottom-Up DP with space optimization.
     *
     * @param weight    Vector storing item weights.
     * @param value     Vector storing item values.
     * @param n         Number of items.
     * @param maxWeight Maximum capacity of knapsack.
     * @return          Maximum value achievable.
     */
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
    {
        int N = weight.size();

        // prev ? results for previous item
        // cur  ? results for current item
        vector<int> prev(maxWeight + 1, 0), cur(maxWeight + 1, 0);

        // Base case: first item
        if (weight[0] <= maxWeight)
        {
            for (int k = weight[0]; k <= maxWeight; k++)
            {
                prev[k] = value[0];
            }
        }

        // Process items iteratively
        for (int idx = 1; idx < N; idx++)
        {

            for (int sackSize = 1; sackSize <= maxWeight; sackSize++)
            {

                // Choice 1: Exclude current item
                int maxVal = prev[sackSize];

                // Choice 2: Include current item (only if it fits)
                if (weight[idx] <= sackSize)
                {
                    maxVal = max(maxVal, value[idx] +
                                             prev[sackSize - weight[idx]]);
                }

                // Store result for this capacity
                cur[sackSize] = maxVal;
            }

            // Move current results to prev for next iteration
            prev = cur;
        }

        // Final answer: max value using all items and full capacity
        return prev[maxWeight];
    }

    /*
    ===============================================================================
        Approach 4: [OPTIMAL]
        ---------
        1. Bottom-Up Dynamic Programming (Single Array Optimization):
           - Uses only one 1D array `prev` to store the maximum value for each capacity.
           - Processes items one by one and updates capacities **in reverse order**.
             This reverse iteration ensures that when computing the current item's
             result, we are only using values from the "previous item state"
             (avoiding overwriting values needed later in the same iteration).

        2. Initialization:
           - For the first item (index 0), fill prev[w] = value[0] for all w >= weight[0].

        3. Iterative filling:
           - For each subsequent item index `idx`:
                a) Iterate sackSize from maxWeight down to 1.
                b) Choice 1: Exclude current item ? value remains prev[w].
                c) Choice 2: Include current item (if it fits) ? value[idx] + prev[w - weight[idx]].
                d) Take the maximum and store back in prev[w].

        Time Complexity:
        ----------------
        O(n * maxWeight)
            - For each of the n items, we process all capacities from maxWeight down to 1.

        Space Complexity:
        -----------------
        O(maxWeight) ? Single array of size maxWeight+1.

    ===============================================================================
    */

    /**
     * Solves the 0/1 Knapsack problem using iterative Bottom-Up DP with single-array optimization.
     *
     * @param weight    Vector storing item weights.
     * @param value     Vector storing item values.
     * @param n         Number of items.
     * @param maxWeight Maximum capacity of knapsack.
     * @return          Maximum value achievable.
     */
    int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
    {
        int N = weight.size();

        // prev[w] = maximum value achievable with capacity w using processed items
        vector<int> prev(maxWeight + 1, 0);

        // Base case: first item
        if (weight[0] <= maxWeight)
        {
            for (int k = weight[0]; k <= maxWeight; k++)
            {
                prev[k] = value[0];
            }
        }

        // Process remaining items
        for (int idx = 1; idx < N; idx++)
        {

            // Iterate in reverse to prevent overwriting values we still need
            for (int sackSize = maxWeight; sackSize > 0; sackSize--)
            {

                // Choice 1: Exclude current item
                int maxVal = prev[sackSize];

                // Choice 2: Include current item (only if it fits)
                if (weight[idx] <= sackSize)
                {
                    maxVal = max(maxVal, value[idx] +
                                             prev[sackSize - weight[idx]]);
                }

                // Store best choice directly in the same array
                prev[sackSize] = maxVal;
            }
        }

        // Final answer: max value using all items and full capacity
        return prev[maxWeight];
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
