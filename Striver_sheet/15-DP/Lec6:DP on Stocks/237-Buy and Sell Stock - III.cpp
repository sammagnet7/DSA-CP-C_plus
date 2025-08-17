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

1. Title: Buy and Sell Stock - III | (DP - 37)

Links:
https://takeuforward.org/data-structure/buy-and-sell-stock-iii-dp-37/
https://www.youtube.com/watch?v=-uQGzhYj8BQ
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iii?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/


Problem statement:
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Examples:
    Example 1:
    Input: prices = [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
    Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.


Constraints:
    1 <= prices.length <= 105
    0 <= prices[i] <= 105



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Buy and Sell Stock - IV | (DP - 38)

Links:
https://takeuforward.org/data-structure/buy-and-sell-stock-iv-dp-38/
https://www.youtube.com/watch?v=IV1dHbk5CDc
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iv?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/


Problem statement:
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.
Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Examples:
    Example 1:
    Input: k = 2, prices = [2,4,1]
    Output: 2
    Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

    Example 2:
    Input: k = 2, prices = [3,2,6,5,0,3]
    Output: 7
    Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.


Constraints:
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000


INPUT::::::

---------------------------------------------------------------------------------------------------

OUTPUT::::::

3. Title: Buy and Sell Stocks With Cooldown | (DP - 39)

Links:
https://takeuforward.org/data-structure/buy-and-sell-stock-iii-dp-37/
https://www.youtube.com/watch?v=-uQGzhYj8BQ
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iii?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/


Problem statement:
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Examples:
    Example 1:
    Input: prices = [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
    Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.


Constraints:
    1 <= prices.length <= 105
    0 <= prices[i] <= 105



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Buy and Sell Stock - III | (DP - 37)
    //-------------------------------------------------------------------------------
    // ------------
    // Approach: 1
    //-------------

    /*
    Problem:
    --------
    "Best Time to Buy and Sell Stock III"
    → At most 2 transactions allowed (1 buy + 1 sell = 1 transaction).

    Approach:
    ---------
    Use recursion + memoization with 3D DP:
    dp[day][txns][carry] = maximum profit achievable starting from `day`,
                           with `txns` transactions left,
                           and current stock holding status (`carry`).

    State:
    ------
    day   → index of current day
    carry → 0 (not holding stock), 1 (holding stock)
    txns  → how many transactions left (max = 2 here)

    Transition:
    -----------
    If carry == 0 (not holding stock):
        • Option A: Skip buying today → profit = dp[day+1][txns][0]
        • Option B: Buy today → profit = -prices[day] + dp[day+1][txns][1]

    If carry == 1 (holding stock):
        • Option A: Sell today → profit = prices[day] + dp[day+1][txns-1][0]
                    (transaction count decreases since sell completes 1 txn)
        • Option B: Hold stock → profit = dp[day+1][txns][1]

    Base Cases:
    -----------
    1. If day == n-1 (last day):
        • carry == 0 → no stock in hand → profit = 0
        • carry == 1 → must sell → profit = prices[n-1]

    2. If txns == 0:
        → No transactions left, so profit = 0 (can't buy/sell anymore)

    Complexity:
    -----------
    Time:  O(n * 2 * k) = O(n * 2 * 2) = O(4n) → O(n)
    Space: O(n * 2 * k) = O(n * 2 * 3) = O(6n) → O(n)
*/

    int recmaxProf(int day, int carry, int txns,
                   vector<int> &prices, int n,
                   vector<vector<vector<int>>> &dp)
    {
        // Base Case 1: Last day, and no stock is held → nothing to gain
        if (day == n - 1 && carry == 0)
            return dp[day][txns][carry] = 0;

        // Base Case 2: Last day, and stock is held → best option is to sell today
        else if (day == n - 1 && carry == 1)
            return dp[day][txns][carry] = prices[day];

        // Base Case 3: No transactions left → profit is 0
        if (txns == 0)
            return dp[day][txns][carry] = 0;

        // Return already computed state
        if (dp[day][txns][carry] != -1)
            return dp[day][txns][carry];

        // Case 1: Currently NOT holding a stock
        if (carry == 0)
        {
            // Option A: Do nothing
            int skipBuy = recmaxProf(day + 1, 0, txns, prices, n, dp);

            // Option B: Buy today
            int buy = -prices[day] + recmaxProf(day + 1, 1, txns, prices, n, dp);

            return dp[day][txns][carry] = max(skipBuy, buy);
        }
        // Case 2: Currently holding a stock
        else
        {
            // Option A: Sell today → transaction count decreases
            int sell = prices[day] + recmaxProf(day + 1, 0, txns - 1, prices, n, dp);

            // Option B: Hold stock
            int hold = recmaxProf(day + 1, 1, txns, prices, n, dp);

            return dp[day][txns][carry] = max(sell, hold);
        }
    }

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // 3D DP: [day][transactionsLeft][carry]
        // transactionsLeft ranges from 0..2
        // carry = 0 or 1
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2, -1)));

        // Start from day 0, no stock, and 2 transactions allowed
        return recmaxProf(0, 0, 2, prices, n, dp);
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Buy and Sell Stock - IV | (DP - 38)
    //-------------------------------------------------------------------------------

    /*
        Recursive Helper Function
        -------------------------
        recmaxProf(day, carry, txns, prices, n, dp)

        Meaning of State:
        -----------------
        • day   → current index in prices array (0-based)
        • carry → 0 → not holding stock, 1 → holding stock
        • txns  → number of transactions still allowed
                  (1 transaction = 1 buy + 1 sell)

        dp[day][txns][carry] stores:
        → maximum profit achievable starting from `day`,
          given `txns` transactions left,
          and current holding status `carry`.

        Transition:
        -----------
        If carry == 0 (not holding stock):
            • Option A: Skip → profit = dp[day+1][txns][0]
            • Option B: Buy  → profit = -prices[day] + dp[day+1][txns][1]

        If carry == 1 (holding stock):
            • Option A: Sell → profit = prices[day] + dp[day+1][txns-1][0]
                             (transaction count decreases after selling)
            • Option B: Hold → profit = dp[day+1][txns][1]

        Base Cases:
        -----------
        1. If day == n-1 (last day):
            • carry == 0 → profit = 0 (no stock left to sell)
            • carry == 1 → profit = prices[n-1] (best option: sell today)

        2. If txns == 0:
            • No transactions left → profit = 0

        Complexity:
        -----------
        Time  → O(n * k * 2) = O(2nk) ≈ O(nk)
        Space → O(n * k * 2) = O(2nk) ≈ O(nk)
    */
    int recmaxProf(int day, int carry, int txns,
                   vector<int> &prices, int n,
                   vector<vector<vector<int>>> &dp)
    {
        // Base Case 1: Last day, no stock held → nothing to gain
        if (day == n - 1 && carry == 0)
            return dp[day][txns][carry] = 0;

        // Base Case 2: Last day, stock is held → best to sell today
        else if (day == n - 1 && carry == 1)
            return dp[day][txns][carry] = prices[day];

        // Base Case 3: No transactions left
        if (txns == 0)
            return dp[day][txns][carry] = 0;

        // Return already computed state
        if (dp[day][txns][carry] != -1)
            return dp[day][txns][carry];

        // Case 1: Not holding stock
        if (carry == 0)
        {
            // Option A: Skip
            int skipBuy = recmaxProf(day + 1, 0, txns, prices, n, dp);

            // Option B: Buy today
            int buy = -prices[day] + recmaxProf(day + 1, 1, txns, prices, n, dp);

            return dp[day][txns][carry] = max(skipBuy, buy);
        }
        // Case 2: Holding stock
        else
        {
            // Option A: Sell today (txn count decreases)
            int sell = prices[day] + recmaxProf(day + 1, 0, txns - 1, prices, n, dp);

            // Option B: Hold stock
            int hold = recmaxProf(day + 1, 1, txns, prices, n, dp);

            return dp[day][txns][carry] = max(sell, hold);
        }
    }

    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;

        // 3D DP: [day][transactionsLeft][carry]
        // transactionsLeft ranges from 0..k
        // carry = 0 or 1
        vector<vector<vector<int>>> dp(n,
                                       vector<vector<int>>(k + 1, vector<int>(2, -1)));

        // Start from day 0, not holding stock, with k transactions allowed
        return recmaxProf(0, 0, k, prices, n, dp);
    }

    //-------------------------------------------------------------------------------
    // 3. Title: Buy and Sell Stocks With Cooldown | (DP - 39)
    //-------------------------------------------------------------------------------
    /*
        Function: recmaxProf
        ---------------------
        Recursive + Memoization approach for
        "Best Time to Buy and Sell Stock with Cooldown" (LeetCode 309).

        Parameters:
            - day   : current index in prices[]
            - carry : state indicator
                      0 → not holding stock
                      1 → holding stock
                      2 → cooldown (just sold yesterday, can't buy today)
            - prices: stock price array
            - n     : total number of days
            - dp    : memoization table, dp[day][carry] stores the
                      maximum profit achievable from this state

        Returns:
            Maximum profit achievable starting from (day, carry).

        Recurrence:
            If carry == 0:
                profit = max(skipBuy, buy)
            If carry == 1:
                profit = max(sell, hold)
            If carry == 2:
                profit = cooldown transition → move to carry=0

        Complexity:
            - Time  : O(n * 3) = O(n)
                      (Each day has 3 states, and each state is solved once)
            - Space : O(n * 3) for dp + O(n) recursion stack (worst case)
    */

    int recmaxProf(int day, int carry, vector<int> &prices, int n, vector<vector<int>> &dp)
    {
        // Base Case 1: Last day, no stock or in cooldown → nothing to gain
        if (day == n - 1 && (carry == 0 || carry == 2))
            return 0;

        // Base Case 2: Last day, holding stock → best option is to sell today
        else if (day == n - 1 && carry == 1)
            return dp[day][carry] = prices[day];

        // Already computed → return cached value
        if (dp[day][carry] != -1)
            return dp[day][carry];

        // Case 1: Not holding stock
        if (carry == 0)
        {
            int skipBuy = recmaxProf(day + 1, 0, prices, n, dp);            // do nothing
            int buy = -prices[day] + recmaxProf(day + 1, 1, prices, n, dp); // buy today
            return dp[day][carry] = max(skipBuy, buy);
        }
        // Case 2: Holding stock
        else if (carry == 1)
        {
            int sell = prices[day] + recmaxProf(day + 1, 2, prices, n, dp); // sell today → cooldown
            int hold = recmaxProf(day + 1, 1, prices, n, dp);               // keep holding
            return dp[day][carry] = max(sell, hold);
        }
        // Case 3: Cooldown
        else if (carry == 2)
        {
            return dp[day][carry] = recmaxProf(day + 1, 0, prices, n, dp); // cooldown → next day not holding
        }

        return -1; // invalid state
    }

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // DP table: dp[day][carry]
        // carry = 0 → not holding
        // carry = 1 → holding
        // carry = 2 → cooldown
        vector<vector<int>> dp(n, vector<int>(3, -1));

        // Start on day 0, not holding any stock
        return recmaxProf(0, 0, prices, n, dp);
    }
};

int main()
{
    return 0;
}
