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

1. Title: Buy and Sell Stock - III

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
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^5



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Buy and Sell Stock - IV

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

3. Title: Buy and Sell Stocks With Cooldown

Links:
https://takeuforward.org/data-structure/buy-and-sell-stock-iii-dp-37/
https://www.youtube.com/watch?v=-uQGzhYj8BQ
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iii?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/


Problem statement:
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).



Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0


Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Buy and Sell Stock - III
//-------------------------------------------------------------------------------
class Solution
{
public:
    // ---------------------
    // Approach 1: Recursive
    //----------------------

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

    // ---------------------
    // Approach 2: Iterative
    //----------------------

    /**
     * @brief Computes the max profit with at most 2 transactions using a backward 3D DP.
     * * --- STATE DEFINITION ---
     * dp[day][carry][txn]
     * 1. day: The current day index (from N-1 down to 0).
     * 2. carry: Are we holding a stock? 0 = Not Holding, 1 = Holding.
     * 3. txn: How many transactions are we STILL ALLOWED to complete? (0, 1, or 2).
     * (Note: A transaction is considered "completed" only when we SELL).
     *
     * * --- APPROACH ---
     * We start from the end of the array (the last day) and work our way backward to Day 0.
     * At every step, we evaluate the optimal choice (Buy vs Skip, or Sell vs Skip) and
     * store the maximum possible future profit from that point onward.
     *
     * * --- COMPLEXITY ---
     * Time Complexity: O(N * 2 * 3) -> O(N), as we visit each state exactly once.
     * Space Complexity: O(N * 2 * 3) -> O(N), to store the 3D DP table.
     */
    int maxProfit(vector<int> &prices)
    {

        int N = prices.size();

        // Edge case: if there are no prices, it's impossible to make a profit.
        if (N == 0)
            return 0;

        // Initialize a 3D DP table with 0s.
        // Dimensions: [N days] x [2 carry states] x [3 transaction limits]
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(2, vector<int>(3, 0)));

        // --- BASE CASE (The Last Day) ---
        // If it is the very last day (N-1), and we are HOLDING a stock (carry = 1),
        // our only logical move to maximize profit is to forcefully SELL it at today's price.
        // If we are NOT holding a stock, we do nothing (profit remains 0).
        for (int txn = 1; txn <= 2; ++txn)
        {
            dp[N - 1][1][txn] = prices[N - 1];
        }

        // --- DP TRANSITIONS (Backward Iteration) ---
        // We move from the second-to-last day all the way back to the start (Day 0).
        for (int day = N - 2; day >= 0; --day)
        {

            // Evaluate both possible holding states (1 = Holding, 0 = Not Holding)
            for (int carry = 1; carry >= 0; --carry)
            {

                // Evaluate for the remaining transaction limits we might have.
                // We don't check txn=0 because if we have 0 transactions left, future profit is 0.
                for (int txn = 2; txn > 0; --txn)
                {

                    // --- STATE 0: NOT HOLDING STOCK ---
                    if (carry == 0)
                    {
                        // Choice 1: BUY today.
                        // We pay today's price (subtract from profit). We move to the 'holding'
                        // state (1) for tomorrow. We DO NOT decrease 'txn' yet, because a
                        // transaction is only counted once a buy/sell pair is completed.
                        int buyToday = (dp[day + 1][1][txn] - prices[day]);

                        // Choice 2: SKIP today.
                        // We do nothing and carry over tomorrow's best profit for 'not holding'.
                        int skipToday = dp[day + 1][carry][txn];

                        // Take the most profitable action
                        dp[day][carry][txn] = max(buyToday, skipToday);
                    }

                    // --- STATE 1: HOLDING STOCK ---
                    else if (carry == 1)
                    {
                        // Choice 1: SELL today.
                        // We gain today's price (add to profit). We move to the 'not holding'
                        // state (0) for tomorrow. Because we finished a trade, we DECREASE
                        // our remaining allowed transactions (txn - 1).
                        int sellToday = (dp[day + 1][0][txn - 1] + prices[day]);

                        // Choice 2: SKIP today.
                        // We hold onto the stock and carry over tomorrow's best profit for 'holding'.
                        int skipToday = dp[day + 1][carry][txn];

                        // Take the most profitable action
                        dp[day][carry][txn] = max(sellToday, skipToday);
                    }
                }
            }
        }

        // After evaluating backwards, the answer lies at the very beginning of time:
        // Day 0, NOT holding any stock, with exactly 2 transactions allowed to be made.
        return dp[0][0][2];
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Buy and Sell Stock - IV
//-------------------------------------------------------------------------------
class Solution
{
public:
    // ---------------------
    // Approach 1: Recursive
    //----------------------
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

    // ---------------------
    // Approach 2: Iterative
    //----------------------
    /**
     * @brief Computes the maximum profit achievable with at most 'k' transactions.
     * * --- STATE DEFINITION ---
     * This algorithm uses a 3D Dynamic Programming (DP) table: dp[day][carry][txn]
     * 1. day   : The current index in the prices array (evaluating backwards from N-1 to 0).
     * 2. carry : A boolean state representing if we currently hold a stock (1) or not (0).
     * 3. txn   : The number of remaining transaction pairs (Buy + Sell) we are allowed to execute.
     * * --- APPROACH (Backward Iteration / Bottom-Up) ---
     * Instead of asking "What is the best I could have done up to today?", this backward
     * approach asks: "If I am at this specific day, in this exact state, what is the MAXIMUM
     * future profit I can extract from the remaining days?"
     * * By starting at the last day (N-1) and working backward to Day 0, we continuously
     * pass the optimal future decisions back in time.
     * * --- STATE TRANSITIONS ---
     * - If Not Holding (carry = 0): We can either BUY (spending money today, moving to holding
     * state tomorrow) or SKIP (doing nothing).
     * - If Holding (carry = 1): We can either SELL (gaining money today, moving to not holding
     * tomorrow, and consuming 1 transaction limit) or SKIP (doing nothing).
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N * 2 * K) -> O(N * K), where N is the number of days. We evaluate
     * each state in the 3D grid exactly once.
     * Space Complexity : O(N * 2 * K) -> O(N * K), required to store the 3D DP table.
     * (Note: This can be optimized to O(K) by only keeping the previous day).
     * * @param k      Maximum number of transactions allowed.
     * @param prices Vector containing the daily prices of the stock.
     * @return       Maximum profit possible.
     */
    int maxProfit(int k, vector<int> &prices)
    {

        int N = prices.size();

        // Edge case: if there are no prices, or we aren't allowed any transactions,
        // it's impossible to make a profit.
        if (N == 0 || k == 0)
            return 0;

        // Initialize a 3D DP table with 0s.
        // Dimensions: [N days] x [2 carry states] x [k+1 transaction limits]
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        // --- BASE CASE (The Last Day) ---
        // If it is the very last day (N-1), and we are HOLDING a stock (carry = 1),
        // our only logical move to maximize profit is to forcefully SELL it at today's price.
        // If we are NOT holding a stock, we do nothing (profit remains 0).
        for (int txn = 1; txn <= k; ++txn)
        {
            dp[N - 1][1][txn] = prices[N - 1];
        }

        // --- DP TRANSITIONS (Backward Iteration) ---
        // We move from the second-to-last day all the way back to the start (Day 0).
        for (int day = N - 2; day >= 0; --day)
        {

            // Evaluate both possible holding states (1 = Holding, 0 = Not Holding)
            for (int carry = 1; carry >= 0; --carry)
            {

                // Evaluate for the remaining transaction limits we might have.
                // We don't check txn=0 because if we have 0 transactions left, future profit is strictly 0.
                for (int txn = k; txn > 0; --txn)
                {

                    // --- STATE 0: NOT HOLDING STOCK ---
                    if (carry == 0)
                    {
                        // Choice 1: BUY today.
                        // We pay today's price (subtract from profit). We move to the 'holding'
                        // state (1) for tomorrow. We DO NOT decrease 'txn' yet, because a
                        // transaction is only counted once a buy/sell pair is completely finished.
                        int buyToday = (dp[day + 1][1][txn] - prices[day]);

                        // Choice 2: SKIP today.
                        // We do nothing and carry over tomorrow's best profit for 'not holding'.
                        int skipToday = dp[day + 1][carry][txn];

                        // Take the most profitable action
                        dp[day][carry][txn] = max(buyToday, skipToday);
                    }

                    // --- STATE 1: HOLDING STOCK ---
                    else if (carry == 1)
                    {
                        // Choice 1: SELL today.
                        // We gain today's price (add to profit). We move to the 'not holding'
                        // state (0) for tomorrow. Because we finished a trade, we DECREASE
                        // our remaining allowed transactions (txn - 1).
                        int sellToday = (dp[day + 1][0][txn - 1] + prices[day]);

                        // Choice 2: SKIP today.
                        // We hold onto the stock and carry over tomorrow's best profit for 'holding'.
                        int skipToday = dp[day + 1][carry][txn];

                        // Take the most profitable action
                        dp[day][carry][txn] = max(sellToday, skipToday);
                    }
                }
            }
        }

        // After evaluating backwards, the answer lies at the very beginning of time:
        // Day 0, NOT holding any stock, with exactly k transactions allowed to be made.
        return dp[0][0][k];
    }
};

//-------------------------------------------------------------------------------
// 3. Title: Buy and Sell Stocks With Cooldown
//-------------------------------------------------------------------------------

class Solution
{
public:
    // ---------------------
    // Approach 1: Recursive : [Uses 3 states: Holding + Not Holding + Cooldown]
    //----------------------

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

    // ---------------------
    // Approach 2: Iterative : [Uses 3 states: Holding + Not Holding + Cooldown]
    //----------------------

    /**
     * @brief Computes max profit with unlimited transactions and a 1-day cooldown using an explicit 3-State DP.
     * * --- STATE DEFINITION ---
     * dp[day][carry]
     * 1. day: The current index in the prices array (from N-1 down to 0).
     * 2. carry: Represents our exact status in the trading cycle (0, 1, or 2).
     * - State 0 (Not Holding) : We have cash and are free to buy.
     * - State 1 (Holding)     : We own a stock and are looking to sell.
     * - State 2 (Cooldown)    : We just sold yesterday. We are forced to rest today.
     * * --- APPROACH (Backward Iteration) ---
     * We iterate backwards from the end of the array to Day 0.
     * Because we explicitly track the Cooldown as State 2, we never have to jump
     * to `day + 2`. Every transition strictly flows into `day + 1`:
     * - Buy  (0 -> 1)
     * - Sell (1 -> 2)
     * - Rest (2 -> 0)
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N) - We evaluate 3 states for each of the N days.
     * Space Complexity : O(N) - We allocate an N x 3 matrix. (Can be optimized to O(1) space).
     */
    int maxProfit(vector<int> &prices)
    {

        int N = prices.size();

        // Edge case: Need at least 2 days to complete a Buy/Sell pair.
        if (N <= 1)
            return 0;

        // Initialize a 2D DP table with 0s. Dimensions: [N days] x [3 states]
        vector<vector<int>> dp(N, vector<int>(3, 0));

        // --- BASE CASE (The Last Day) ---
        // If it is the very last day (N-1) and we are holding a stock (State 1),
        // our only logical move is to force a sell at today's price.
        // For States 0 and 2, the profit remains 0 because the market is closing.
        dp[N - 1][1] = prices[N - 1];

        // --- DP TRANSITIONS (Backward Iteration) ---
        // Start from the second-to-last day and work backwards to day 0.
        for (int day = N - 2; day >= 0; --day)
        {

            // Evaluate all 3 states: Cooldown (2), Holding (1), Not Holding (0)
            for (int carry = 2; carry >= 0; --carry)
            {

                // --- STATE 0: NOT HOLDING (Ready to Buy) ---
                if (carry == 0)
                {
                    // Choice 1: BUY today. Pay the price and move to 'holding' (1) tomorrow.
                    int buyToday = dp[day + 1][1] - prices[day];

                    // Choice 2: SKIP today. Carry over tomorrow's 'not holding' profit (0).
                    int skipToday = dp[day + 1][carry];

                    dp[day][carry] = max(buyToday, skipToday);
                }

                // --- STATE 1: HOLDING (Ready to Sell) ---
                else if (carry == 1)
                {
                    // Choice 1: SELL today. Add today's price to our profit.
                    // Crucially, we transition to the Cooldown state (2) for tomorrow.
                    int sellToday = dp[day + 1][2] + prices[day];

                    // Choice 2: SKIP today. Carry over tomorrow's 'holding' profit (1).
                    int skipToday = dp[day + 1][carry];

                    dp[day][carry] = max(sellToday, skipToday);
                }

                // --- STATE 2: COOLDOWN (Forced Rest) ---
                else if (carry == 2)
                {
                    // Choice 1: FORCED REST.
                    // We cannot buy or sell today. We simply transition back to the
                    // 'Not Holding' state (0) for tomorrow, having served our penalty.
                    int skipToday = dp[day + 1][0];

                    dp[day][carry] = skipToday;
                }
            }
        }

        // Return the maximum profit on Day 0, starting with no stock (State 0).
        return dp[0][0];
    }

    // ---------------------
    // Approach 2: Iterative : [ On cooldown skips 1 day ]
    //----------------------

    /**
     * @brief Computes max profit with unlimited transactions and a 1-day cooldown.
     * * --- STATE DEFINITION ---
     * dp[day][carry]
     * 1. day: The current index in the prices array (from N-1 down to 0).
     * 2. carry: Are we currently holding a stock? 0 = Not Holding, 1 = Holding.
     * * --- APPROACH (Backward Iteration) ---
     * We iterate backwards from the end of the array to Day 0.
     * The core twist is the COOLDOWN rule during the "SELL" transition:
     * When we sell a stock on `day`, we cannot buy on `day + 1`. Therefore,
     * the profit of selling today is `prices[day] + dp[day + 2][0]`.
     * * To prevent out-of-bounds errors when trying to jump to `day + 2`, we explicitly
     * check if `day < N - 2`. If it isn't, it means the cooldown consumes the rest
     * of the available days, so the future profit is simply 0.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N) - We visit 2 states for each of the N days.
     * Space Complexity : O(N) - We allocate an N x 2 matrix. (Can be optimized to O(1)).
     */
    int maxProfit(vector<int> &prices)
    {

        int N = prices.size();

        // Edge case: Need at least 2 days to complete a Buy/Sell pair.
        if (N <= 1)
            return 0;

        // Initialize a 2D DP table with 0s. Dimensions: [N days] x [2 states]
        vector<vector<int>> dp(N, vector<int>(2, 0));

        // --- BASE CASE (The Last Day) ---
        // If it is the very last day (N-1) and we are holding a stock,
        // our only logical move is to force a sell at today's price.
        // If we are not holding, profit is 0 (already set by initialization).
        dp[N - 1][1] = prices[N - 1];

        // --- DP TRANSITIONS (Backward Iteration) ---
        // Start from the second-to-last day and work backwards to day 0.
        for (int day = N - 2; day >= 0; --day)
        {

            // Evaluate both states: Holding (1) and Not Holding (0)
            for (int carry = 1; carry >= 0; --carry)
            {

                // --- STATE 0: NOT HOLDING STOCK ---
                if (carry == 0)
                {
                    // Choice 1: BUY today. Pay the price and move to 'holding' (1) tomorrow.
                    int buyToday = dp[day + 1][1] - prices[day];

                    // Choice 2: SKIP today. Carry over tomorrow's 'not holding' profit.
                    int skipToday = dp[day + 1][carry];

                    // Take the most profitable action
                    dp[day][carry] = max(buyToday, skipToday);
                }

                // --- STATE 1: HOLDING STOCK ---
                else if (carry == 1)
                {

                    int sellToday = 0;

                    // Choice 1: SELL today.
                    // COOLDOWN LOGIC: If we sell, we must skip day+1.
                    // We check if day+2 actually exists to prevent out-of-bounds array access.
                    if (day < N - 2)
                    {
                        // Add today's price to the optimal profit from 2 days away.
                        sellToday = dp[day + 2][0] + prices[day];
                    }
                    else
                    {
                        // If day+2 doesn't exist (i.e., we are on day N-2), selling today
                        // triggers a cooldown on the final day. So future profit is just 0.
                        sellToday = prices[day];
                    }

                    // Choice 2: SKIP today. Carry over tomorrow's 'holding' profit.
                    int skipToday = dp[day + 1][carry];

                    // Take the most profitable action
                    dp[day][carry] = max(sellToday, skipToday);
                }
            }
        }

        // Return the maximum profit on Day 0, starting with no stock.
        return dp[0][0];
    }
};

int main()
{
    return 0;
}
