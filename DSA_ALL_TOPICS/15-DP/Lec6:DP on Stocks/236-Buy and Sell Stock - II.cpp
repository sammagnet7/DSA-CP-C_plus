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

1. Title: Buy and Sell Stock - II|(DP-36)

Links:
https://takeuforward.org/data-structure/buy-and-sell-stock-ii-dp-36/
https://www.youtube.com/watch?v=nGJmxkUJQGs
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-ii?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/


Problem statement:
You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.
Find and return the maximum profit you can achieve.

Examples:
    Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
    Total profit is 4 + 3 = 7.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Total profit is 4.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.


Constraints:
1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Buy and Sell Stocks With Transaction Fees | (DP - 40)

Links:
https://takeuforward.org/data-structure/buy-and-sell-stocks-with-transaction-fees-dp-40/
https://www.youtube.com/watch?v=k4eK-vEmnKg
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-with-cooldown-and-transaction-fees?tab=editorial


Problem statement:
You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.
Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

Note:
You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
The transaction fee is only charged once for each stock purchase and sale.

Examples:
    Example 1:
    Input: prices = [1,3,2,8,4,9], fee = 2
    Output: 8
    Explanation: The maximum profit can be achieved by:
    - Buying at prices[0] = 1
    - Selling at prices[3] = 8
    - Buying at prices[4] = 4
    - Selling at prices[5] = 9
    The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

    Example 2:
    Input: prices = [1,3,7,5,10,3], fee = 3
    Output: 6

Constraints:
    1 <= prices.length <= 5 * 104
    1 <= prices[i] < 5 * 104
    0 <= fee < 5 * 104


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Buy and Sell Stock - II|(DP-36)
    //-------------------------------------------------------------------------------
    // ------------
    // Approach: 1
    //-------------

    /*
        Problem:
        --------
        Given stock prices for N days, maximize profit by performing as many
        buy/sell transactions as you like.
        Constraint: You must sell before buying again (i.e., cannot hold more than 1 stock at a time).

        Approach (Recursive + Memoization):
        -----------------------------------
        - At each day, we have 2 states:
            carry = 0 → we are NOT holding a stock
            carry = 1 → we ARE holding a stock

        - Choices:
            If carry == 0 (no stock in hand):
                • Option 1: Skip buying today → move to next day with carry = 0
                • Option 2: Buy today → pay price[day] (subtract), move to next day with carry = 1

            If carry == 1 (stock in hand):
                • Option 1: Sell today → gain price[day] (add), move to next day with carry = 0
                • Option 2: Hold stock → skip selling, move to next day with carry = 1

        - Recurrence ensures we explore all possibilities while memoization (dp) avoids recomputation.

        Complexity:
        -----------
        Time:  O(N * 2)  (two states per day)
        Space: O(N * 2)  (DP table + recursion stack)
    */

    int recmaxProf(int day, int carry, vector<int> &prices, int n, vector<vector<int>> &dp)
    {

        // Base Case 1: Last day, and no stock is held → nothing to gain
        if (day == n - 1 && carry == 0)
        {
            return 0;
        }
        // Base Case 2: Last day, and stock is held → best option is to sell today
        else if (day == n - 1 && carry == 1)
        {
            return dp[day][carry] = prices[day];
        }

        // Return already computed state
        if (dp[day][carry] != -1)
            return dp[day][carry];

        // Case 1: Currently NOT holding a stock
        if (carry == 0)
        {
            // Option A: Do nothing, move to next day with no stock
            int skipBuy = recmaxProf(day + 1, 0, prices, n, dp);

            // Option B: Buy today (spend money → subtract), move to next day holding stock
            int buy = -prices[day] + recmaxProf(day + 1, 1, prices, n, dp);

            return dp[day][carry] = max(skipBuy, buy);
        }
        // Case 2: Currently holding a stock
        else
        {
            // Option A: Sell today (earn money → add), move to next day with no stock
            int sell = prices[day] + recmaxProf(day + 1, 0, prices, n, dp);

            // Option B: Hold stock, move to next day still holding
            int hold = recmaxProf(day + 1, 1, prices, n, dp);

            return dp[day][carry] = max(sell, hold);
        }
    }

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // cur[carry] → maximum profit achievable starting from `day` with given carry state
        vector<vector<int>> dp(n, vector<int>(2, -1));

        // Start from day 0, with no stock in hand
        return recmaxProf(0, 0, prices, n, dp);
    }

    // ------------
    // Approach: 2
    //-------------

    /*
        Problem:
        --------
        Given stock prices for N days, maximize profit by performing as many
        buy/sell transactions as you like.
        Constraint: Cannot hold more than 1 stock at a time.

        Approach (Tabulation DP):
        -------------------------
        - Define state:
            cur[carry] = maximum profit achievable starting from `day`
                            with current stock-holding status `carry`.
                carry = 0 → we do NOT have a stock
                carry = 1 → we ARE holding a stock

        - Transition:
            If carry == 0 (no stock in hand):
                • Option A: Skip buying → profit = ahead[0]
                • Option B: Buy today   → profit = -prices[day] + ahead[1]
                cur[0] = max(OptionA, OptionB)

            If carry == 1 (stock in hand):
                • Option A: Sell today → profit = prices[day] + ahead[0]
                • Option B: Hold stock → profit = ahead[1]
                cur[1] = max(OptionA, OptionB)

        - Base Cases (last day):
            • dp[n-1][0] = 0  (if no stock left, profit is 0)
            • dp[n-1][1] = prices[n-1] (best is to sell on last day)

        Complexity:
        -----------
        Time:  O(N * 2)  = O(N)
        Space: O(N * 2)  = O(N)
        (can be further optimized to O(1) using two variables since
        we only need ahead[..] at each step)
    */

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // cur[carry] → maximum profit achievable from `day` onward
        vector<vector<int>> dp(n, vector<int>(2, 0));

        // Base cases for the last day
        dp[n - 1][0] = 0;             // no stock in hand
        dp[n - 1][1] = prices[n - 1]; // holding a stock, best to sell today

        // Fill DP table backwards (from day n-2 down to day 0)
        for (int day = n - 2; day >= 0; day--)
        {
            for (int carry = 1; carry >= 0; carry--)
            {

                if (carry == 0)
                {
                    // Option A: Do nothing
                    int skipBuy = dp[day + 1][0];

                    // Option B: Buy today
                    int buy = -prices[day] + dp[day + 1][1];

                    dp[day][carry] = max(skipBuy, buy);
                }
                else
                { // carry == 1
                    // Option A: Sell today
                    int sell = prices[day] + dp[day + 1][0];

                    // Option B: Hold stock
                    int hold = dp[day + 1][1];

                    dp[day][carry] = max(sell, hold);
                }
            }
        }

        // Answer: max profit starting from day 0 with no stock in hand
        return dp[0][0];
    }

    // ------------
    // Approach: 3
    //-------------

    /*
        Problem:
        --------
        Maximize profit by buying/selling stocks multiple times
        (cannot hold more than 1 stock at a time).

        Idea:
        -----
        Use Dynamic Programming, but optimize space:
        - At any given `day`, profit depends only on `day+1`.
        - So, we don't need a full dp[][] table, only two arrays:
            ahead[] → profit from next day (day+1)
            cur[]   → profit from current day being calculated

        State:
        ------
        carry = 0 → not holding a stock
        carry = 1 → holding a stock

        Transition:
        -----------
        If carry == 0 (no stock currently in hand):
            • Option A: Skip buying → profit = ahead[0]
            • Option B: Buy today   → profit = -prices[day] + ahead[1]
            cur[0] = max(OptionA, OptionB)

        If carry == 1 (already holding a stock):
            • Option A: Sell today → profit = prices[day] + ahead[0]
            • Option B: Hold stock → profit = ahead[1]
            cur[1] = max(OptionA, OptionB)

        Base Case (last day):
        ---------------------
        • ahead[0] = 0             (if no stock, profit = 0)
        • ahead[1] = prices[n-1]   (if holding stock, best is to sell)

        Complexity:
        -----------
        Time:  O(N * 2) = O(N)
        Space: O(2)    = O(1)    → only two arrays of size 2
    */

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();

        // cur[carry] → profit for current day
        // ahead[carry] → profit for next day
        vector<int> cur(2, 0), ahead(2, 0);

        // Base case for last day
        ahead[0] = 0;             // no stock left
        ahead[1] = prices[n - 1]; // holding stock, sell today

        // Work backwards from second-last day to day 0
        for (int day = n - 2; day >= 0; day--)
        {
            for (int carry = 1; carry >= 0; carry--)
            {

                if (carry == 0)
                {
                    // Option A: Do nothing
                    int skipBuy = ahead[0];

                    // Option B: Buy today
                    int buy = -prices[day] + ahead[1];

                    cur[carry] = max(skipBuy, buy);
                }
                else
                { // carry == 1
                    // Option A: Sell today
                    int sell = prices[day] + ahead[0];

                    // Option B: Keep holding
                    int hold = ahead[1];

                    cur[carry] = max(sell, hold);
                }
            }

            // Move current results to ahead for next iteration
            ahead = cur;
        }

        // Final answer: profit starting at day 0 with no stock
        return cur[0];
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Buy and Sell Stocks With Transaction Fees | (DP - 40)
    //-------------------------------------------------------------------------------

    /*
    Function: recmaxProf
    ---------------------
    Recursive + Memoization approach for
    "Best Time to Buy and Sell Stock with Transaction Fee" (LeetCode 714).

    Parameters:
        - day   : current index in prices[]
        - carry : state indicator
                  0 → not holding stock
                  1 → holding stock
        - prices: stock price array
        - n     : total number of days
        - dp    : memoization table, dp[day][carry] stores the
                  maximum profit achievable from this state
        - fee   : transaction fee paid per sale

    Returns:
        Maximum profit achievable starting from (day, carry).

    Recurrence:
        If carry == 0:
            profit = max(skipBuy, buy)
                skipBuy = move to next day without buying
                buy     = -prices[day] + f(day+1, holding)
        If carry == 1:
            profit = max(sell, hold)
                sell = prices[day] - fee + f(day+1, not holding)
                hold = f(day+1, holding)

    Complexity:
        - Time  : O(n * 2) = O(n)
                  (Each day has 2 states, computed once)
        - Space : O(n * 2) for dp + O(n) recursion stack (worst case)
*/

    int recmaxProf(int day, int carry, vector<int> &prices, int n, vector<vector<int>> &dp, int fee)
    {
        // Base Case 1: Last day, no stock → nothing to gain
        if (day == n - 1 && carry == 0)
            return 0;

        // Base Case 2: Last day, holding stock → best option is to sell today (minus fee)
        else if (day == n - 1 && carry == 1)
            return dp[day][carry] = prices[day] - fee;

        // Already computed → return cached result
        if (dp[day][carry] != -1)
            return dp[day][carry];

        // Case 1: Not holding stock
        if (carry == 0)
        {
            int skipBuy = recmaxProf(day + 1, 0, prices, n, dp, fee);            // do nothing
            int buy = -prices[day] + recmaxProf(day + 1, 1, prices, n, dp, fee); // buy today
            return dp[day][carry] = max(skipBuy, buy);
        }
        // Case 2: Holding stock
        else
        {
            int sell = prices[day] - fee + recmaxProf(day + 1, 0, prices, n, dp, fee); // sell today
            int hold = recmaxProf(day + 1, 1, prices, n, dp, fee);                     // hold stock
            return dp[day][carry] = max(sell, hold);
        }
    }

    /*
        Function: maxProfit
        -------------------
        Wrapper function that initializes DP and calls recursion.

        Parameters:
            - prices : stock price array
            - fee    : transaction fee

        Returns:
            Maximum profit possible with unlimited transactions and fee per sale.

        Complexity:
            - Time  : O(n)
            - Space : O(n)
    */

    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();

        // dp[day][carry] → max profit starting from given state
        // carry = 0 (not holding), 1 (holding)
        vector<vector<int>> dp(n, vector<int>(2, -1));

        // Start from day 0, with no stock in hand
        return recmaxProf(0, 0, prices, n, dp, fee);
    }
};

int main()
{
    return 0;
}
