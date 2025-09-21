#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Kadane's Algorithm : Stock Buy and Sell

https://takeuforward.org/data-structure/stock-buy-and-sell/
https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock?tab=editorial
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
https://www.naukri.com/code360/problems/893405?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: You are given an array of prices where prices[i] is the price of a given stock on an ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock. Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Examples:

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.


INPUT::::::
7
7 1 5 3 6 4
7 6 4 3 1
2 100 150 120
1 2 3 4
2 2 2 2
17 20 11 9 12 6
98 101 66 72

OUTPUT::::::

5
0
148
3
0
3
6
 */

class Solution
{
public:
    /**
     * Best Time to Buy and Sell Stock (LeetCode 121)
     * ----------------------------------------------
     * Problem:
     *   - You are given an array `prices` where prices[i] is the stock price on day i.
     *   - You want to maximize your profit by choosing a single day to buy one stock
     *     and a different day in the future to sell it.
     *   - Return the maximum profit you can achieve. If no profit is possible, return 0.
     *
     * Approaches:
     *   1. Brute Force
     *   2. Better (with auxiliary array of suffix max values)
     *   3. Optimal (two-pointer greedy)
     */

    /*--------------------------------------------------------------
      1. Brute Force Approach
      --------------------------------------------------------------
      Idea:
      - Check every possible pair (i, j) with i < j.
      - Compute profit = prices[j] - prices[i].
      - Keep track of the maximum profit.

      Time Complexity:  O(N^2)   (two nested loops)
      Space Complexity: O(1)     (only variables)
    */
    int maxProfit_bruteforce(vector<int> &prices)
    {
        int maxP = 0;

        for (int i = 0; i < prices.size(); i++)
        {
            for (int j = i; j < prices.size(); j++)
            {
                // update max profit if selling at j after buying at i gives higher profit
                if (prices[j] - prices[i] > maxP)
                    maxP = prices[j] - prices[i];
            }
        }

        return maxP;
    }

    /*--------------------------------------------------------------
      2. Better Approach (Suffix Maximum Array)
      --------------------------------------------------------------
      Intuition:
      - For each day i, the best possible selling price comes from
        the maximum price on any future day.
      - Precompute an array `maxArr[i]` = maximum price from day i..N-1.
      - Then compute max profit as max(maxArr[i+1] - prices[i]).

      Time Complexity:  O(N)    (two passes)
      Space Complexity: O(N)    (for storing maxArr)
    */
    int maxProfit_better(vector<int> &prices)
    {
        int N = prices.size();
        int maxP = 0;
        int maxE = INT_MIN;

        vector<int> maxArr(N);

        // Build suffix max array: maxArr[i] = max price from day i to end
        for (int i = N - 1; i > 0; i--)
        {
            maxE = max(prices[i], maxE);
            maxArr[i] = maxE;
        }

        // Compute profit by buying at day i and selling at future max price
        for (int i = 0; i < N - 1; i++)
        {
            maxP = max(maxP, maxArr[i + 1] - prices[i]);
        }

        return maxP;
    }

    /*--------------------------------------------------------------
      3. Optimal Approach (Two-Pointer Greedy)
      --------------------------------------------------------------
      Intuition:
      - Traverse prices with two pointers: l = buy day, r = sell day.
      - For each r:
          * Compute profit = prices[r] - prices[l].
          * Update maxProfit if profit is higher.
          * If prices[r] < prices[l], reset l = r (better buy point).
      - This ensures we always buy at the lowest price so far,
        and sell at the best price after it.

      Time Complexity:  O(N)    (single pass)
      Space Complexity: O(1)    (just variables)
    */
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int l = 0; // left pointer (buy day)
        int r = 0; // right pointer (sell day)
        int maxProfit = 0;

        while (r < n)
        {
            int profit = prices[r] - prices[l];

            maxProfit = max(maxProfit, profit);

            // If a lower price is found at r, reset l = r (better buy opportunity)
            if (prices[r] < prices[l])
                l = r;

            r++;
        }

        return maxProfit;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
        // int k;
        // cin >> k;
        // cin.ignore();

        string input;
        getline(cin, input);
        stringstream ss(input);

        vector<int> arr;
        int num;
        while (ss >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.maxProfit(arr);

        cout << endl;
    }
}