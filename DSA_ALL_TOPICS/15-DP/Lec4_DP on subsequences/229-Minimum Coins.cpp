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

1. Title: Minimum Coins [Return the fewest number of coins]

Links:
https://takeuforward.org/data-structure/minimum-coins-dp-20/
https://www.youtube.com/watch?v=myPeWb3Y68A
https://takeuforward.org/plus/dsa/problems/minimum-coins?tab=editorial
https://leetcode.com/problems/coin-change/description/


Problem statement:
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Examples:
    Example 1:
    Input: coins = [1,2,5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

    Example 2:
    Input: coins = [2], amount = 3
    Output: -1

    Example 3:
    Input: coins = [1], amount = 0
    Output: 0


Constraints:
1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Coin Change 2 (DP - 22) [Return the number of combinations ]

Links:
https://takeuforward.org/data-structure/coin-change-2-dp-22/
https://takeuforward.org/plus/dsa/problems/coin-change-ii?tab=editorial
https://leetcode.com/problems/coin-change-ii/description/


Problem statement:
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
You may assume that you have an infinite number of each kind of coin.
The answer is guaranteed to fit into a signed 32-bit integer.

Examples:
    Example 1:
    Input: amount = 5, coins = [1,2,5]
    Output: 4
    Explanation: there are four ways to make up the amount:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1

    Example 2:
    Input: amount = 3, coins = [2]
    Output: 0
    Explanation: the amount of 3 cannot be made up just with coins of 2.

    Example 3:
    Input: amount = 10, coins = [10]
    Output: 1

Constraints:
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000

INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Minimum Coins
//-------------------------------------------------------------------------------
class Solution
{
public:
    // Approach 1: Greedy [FAILS]
    // This approach is FAILING for test case #52
    // beacuse alway substracting with the highest possible substractor may not be perfect always
    // some unexpected smaller numbers we can be left with
    int coinChange(vector<int> &coins, int amount)
    {
        sort(coins.begin(), coins.end());

        int i = coins.size() - 1;
        int count = 0;

        while (amount > 0 && i >= 0)
        {
            if (coins[i] > amount)
            {
                i--;
                continue;
            }
            if (amount % coins[i] == 0)
            {
                int q = amount / coins[i];
                amount = amount - (q * coins[i]);
                count += q;
            }
            else
            {
                count++;
                amount -= coins[i];
            }
        }

        if (amount == 0)
            return count;
        else
            return -1;
    }

    /*
    ===============================================================================
        Approach 2:
        ---------
        1. Recursive Definition:
        - We consider coins from index `idx` down to 0.
        - Base cases:
                a) amount == 0 → 0 coins needed.
                b) idx < 0 → No coins left to use → return infinity (1e9).
        - Recursive choices:
                a) notTake = recMinCount(idx-1, amount) → Exclude current coin.
                b) take = 1 + recMinCount(idx, amount - coins[idx]) → Include current coin
                (since coin change allows unlimited usage of the same coin).
        - Return the minimum of these two choices.

        2. Memoization:
        - To avoid recomputation, we store results in a 2D DP table:
                dp[idx][amount]
            which stores the minimum number of coins needed to make `amount`
            using coins[0..idx].

        3. Answer:
        - If dp[N-1][amount] is infinity (1e9), no combination exists → return -1.
            Otherwise, return the computed value.

        Time Complexity:
        ----------------
        O(N * amount)
            - Each state (idx, amount) is computed once.
            - At most N * (amount+1) states.

        Space Complexity:
        -----------------
        O(N * amount) → DP table
        O(N) recursion stack (due to function calls)
        Total: O(N * amount + N)

    ===============================================================================
    */

    /**
     * Recursive helper to compute the minimum coins needed.
     *
     * @param coins  Vector of coin denominations.
     * @param dp     2D memoization table.
     * @param idx    Current coin index under consideration.
     * @param amount Remaining target amount.
     * @return       Minimum number of coins to form `amount` using coins[0..idx].
     */
    int recMinCount(vector<int> &coins, vector<vector<int>> &dp, int idx, int amount)
    {

        // Base case: exact amount achieved
        if (amount == 0)
        {
            return 0;
        }

        // Base case: no coins left but amount > 0 → impossible
        else if (idx < 0)
        {
            return 1e9; // Infinity placeholder
        }

        // If already computed, return stored result
        if (dp[idx][amount] != -1)
            return dp[idx][amount];

        // Choice 1: Include current coin (if it fits in remaining amount)
        int take = 1e9;
        if ((amount - coins[idx]) >= 0)
        {
            take = 1 + recMinCount(coins, dp, idx, (amount - coins[idx]));
        }

        // Choice 2: Exclude current coin
        int notTake = recMinCount(coins, dp, idx - 1, amount);

        // Store and return minimum of the two choices
        return dp[idx][amount] = min(take, notTake);
    }

    /**
     * Main function to find minimum coins to make `amount` using recursive memoization.
     *
     * @param coins  Vector of coin denominations.
     * @param amount Target amount to form.
     * @return       Minimum number of coins required, or -1 if impossible.
     */
    int coinChange(vector<int> &coins, int amount)
    {

        int N = coins.size();

        // Initialize DP table with -1 (uncomputed states)
        vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, -1));

        int ret = recMinCount(coins, dp, N - 1, amount);

        // If impossible, return -1
        return ret == 1e9 ? -1 : ret;
    }

    /*
    ===============================================================================
        Approach 3:
        ---------
        1. Bottom-Up Dynamic Programming:
        - Goal: Find the minimum number of coins needed to make up a given amount.
        - Define dp[i][amt] = minimum number of coins needed to make `amt` using coins[0..i].
        - Initialization:
                a) dp[i][0] = 0 for all i (0 coins needed to make amount 0).
                b) First row (i = 0): If amt is divisible by coins[0], then
                dp[0][amt] = amt / coins[0], else set as infinity (1e9 here).

        2. Transition:
        - For each coin index `idx` from 1 to N-1:
                a) notTake = dp[idx-1][amt] → Exclude current coin.
                b) take = 1 + dp[idx][amt - coins[idx]] → Include current coin (unbounded usage).
                c) dp[idx][amt] = min(take, notTake).

        3. Answer:
        - If dp[N-1][totAmount] is infinity (1e9), no combination exists → return -1.
            Otherwise, return dp[N-1][totAmount].

        Time Complexity:
        ----------------
        O(N * totAmount)
            - Each of the N coins processes all amounts from 1 to totAmount.

        Space Complexity:
        -----------------
        O(N * totAmount) → DP table of size N x (totAmount+1).

    ===============================================================================
    */

    /**
     * Finds the minimum number of coins needed to make up `totAmount`.
     *
     * @param coins     Vector storing coin denominations.
     * @param totAmount Target amount to form.
     * @return          Minimum number of coins required, or -1 if impossible.
     */
    int coinChange(vector<int> &coins, int totAmount)
    {

        int N = coins.size();

        // dp[i][amt] = min coins needed to make amount amt using coins[0..i]
        // Initialize with "infinity" (here, 1e9) for impossible cases
        vector<vector<int>> dp(coins.size(), vector<int>(totAmount + 1, 1e9));

        // Base case: amount 0 requires 0 coins for all i
        for (int idx = 0; idx < N; idx++)
        {
            dp[idx][0] = 0;
        }

        // Base case: fill first row (only using coins[0])
        for (int amount = 1; amount <= totAmount; amount++)
        {
            if (amount % coins[0] == 0)
            {
                dp[0][amount] = amount / coins[0]; // exact multiple possible ** Note here **
            }
        }

        // Fill DP table iteratively
        for (int idx = 1; idx < N; idx++)
        {
            for (int amount = 1; amount <= totAmount; amount++)
            {

                // Choice 1: Include current coin (unbounded)
                int take = 1e9;
                if ((amount - coins[idx]) >= 0)
                {
                    take = 1 + dp[idx][amount - coins[idx]];
                }

                // Choice 2: Exclude current coin
                int notTake = dp[idx - 1][amount];

                // Store minimum coins needed
                dp[idx][amount] = min(take, notTake);
            }
        }

        // If no solution, return -1
        return dp[N - 1][totAmount] == 1e9 ? -1 : dp[N - 1][totAmount];
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Coin Change 2 (DP - 22)
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * Recursive helper function using Top-Down Dynamic Programming (Memoization).
     * This models an "Unbounded Knapsack" problem where each item (coin)
     * can be selected an infinite number of times.
     *
     * @param arr    Reference to the array of available coins.
     * @param dp     2D memoization table to cache computed subproblem results.
     * @param target The remaining amount we need to form.
     * @param index  The current coin denomination we are considering.
     * @return       The total number of valid combinations for this state.
     */
    int recCount(vector<int> &arr, vector<vector<int>> &dp, int target, int index)
    {
        // --- BASE CASES ---

        // 1. Target Achieved: We successfully reduced the amount to exactly 0.
        // This represents 1 valid combination of coins.
        if (target == 0)
        {
            return 1;
        }

        // 2. Overshot Target: The last coin picked was too large.
        // This is an invalid combination, so we return 0 ways.
        if (target < 0)
        {
            return 0;
        }

        // 3. Exhausted Coins: We ran out of coin denominations to try,
        // but the target is still greater than 0.
        if (index < 0)
        {
            return 0;
        }

        // --- MEMOIZATION CHECK ---

        // If this specific state (current coin index + remaining target)
        // has been calculated in a previous recursive branch, return it immediately.
        if (dp[index][target] != -1)
        {
            return dp[index][target];
        }

        // --- STATE TRANSITIONS (The Core Logic) ---

        // CHOICE 1: "No Take" (Skip the current coin)
        // We decide to not use the coin at 'index' at all.
        // The target stays the same, and we move to the next coin (index - 1).
        int noTake = recCount(arr, dp, target, index - 1);

        // CHOICE 2: "Take" (Use the current coin)
        // We subtract the coin's value from the target.
        // CRITICAL: We pass 'index' (not index - 1) down the recursion tree.
        // Because we have infinite coins, we stay on the same coin to potentially use it again.
        int take = 0;
        if (target >= arr[index])
        { // Minor optimization: only branch if the coin actually fits
            take = recCount(arr, dp, target - arr[index], index);
        }

        // Store the sum of both decision branches into the DP table and return it.
        return dp[index][target] = (take + noTake);
    }

    int change(int amount, vector<int> &coins)
    {
        int N = coins.size();

        // Initialize the 2D DP memoization table.
        // dp[i][t] maps to: ways to make sum 't' using coins from index 0 up to 'i'.
        // We fill it with -1 to differentiate between "0 ways" and "uncomputed".
        vector<vector<int>> dp(N, vector<int>(amount + 1, -1));

        // Start the recursion tree from the last coin index, looking for the full amount.
        return recCount(coins, dp, amount, N - 1);
    }
};

int main()
{
    return 0;
}
