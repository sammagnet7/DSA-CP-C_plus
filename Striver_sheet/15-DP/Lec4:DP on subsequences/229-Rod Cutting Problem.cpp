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

1. Title: Unbounded Knapsack (DP - 23)

Links:
https://takeuforward.org/data-structure/unbounded-knapsack-dp-23/
https://www.youtube.com/watch?v=OgvOZ6OrJoY
https://takeuforward.org/plus/dsa/problems/unbounded-knapsack?tab=editorial
https://www.naukri.com/code360/problems/unbounded-knapsack_1215029?leftPanelTabValue=PROBLEM


Problem statement:
You are given ‘n’ items with certain ‘profit’ and ‘weight’ and a knapsack with weight capacity ‘w’.
You need to fill the knapsack with the items in such a way that you get the maximum profit. You are allowed to take one item multiple times.

Example:
Input:
'n' = 3, 'w' = 10,
'profit' = [5, 11, 13]
'weight' = [2, 4, 6]
Output: 27
Explanation:
We can fill the knapsack as:

1 item of weight 6 and 1 item of weight 4.
1 item of weight 6 and 2 items of weight 2.
2 items of weight 4 and 1 item of weight 2.
5 items of weight 2.

The maximum profit will be from case 3 = 11 + 11 + 5 = 27. Therefore maximum profit = 27.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Rod Cutting Problem |

Links:
https://www.youtube.com/watch?v=mO8XpGoJwuo
https://takeuforward.org/plus/dsa/problems/rod-cutting-problem?tab=editorial
https://www.naukri.com/code360/problems/rod-cutting-problem_800284?leftPanelTabValue=PROBLEM


Problem statement:
Given a rod of length ‘N’ units. The rod can be cut into different sizes and each size has a cost associated with it. Determine the maximum cost obtained by cutting the rod and selling its pieces.

Note:
1. The sizes will range from 1 to ‘N’ and will be integers.
2. The sum of the pieces cut should be equal to ‘N’.
3. Consider 1-based indexing.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Unbounded Knapsack (DP - 23)
    //-------------------------------------------------------------------------------

#include <climits>

    /*
        Method: recMaxProfit
        --------------------
        Solves the Unbounded Knapsack problem recursively with memoization.
        In the unbounded knapsack, each item can be chosen multiple times
        (including zero times) as long as the total weight does not exceed capacity.

        Parameters:
            idx     - Current item index being considered.
            w       - Remaining weight capacity of the knapsack.
            profit  - profit[i] stores profit from the i-th item.
            dp      - Memoization table where dp[i][cap] stores the maximum
                      profit for items 0..i with capacity 'cap'.
            weight  - weight[i] stores weight of the i-th item.

        Returns:
            int - Maximum profit obtainable with items up to index `idx`
                  and capacity `w`.

        Logic:
            1. Base Case (idx == 0):
                - If the current item fits, take as many copies as possible:
                  profit = (capacity / weight[0]) * profit[0]
                - Otherwise, profit = 0.
            2. Recursive Case:
                - Option 1 (take): If the current item fits, take it and
                  stay on the same index (since unlimited copies allowed).
                - Option 2 (notTake): Skip the current item and move to the
                  previous index.
                - Return max of take and notTake.
            3. Memoization ensures each (idx, w) pair is computed once.

        Time Complexity:
            O(n * W)
            - n = number of items
            - W = knapsack capacity
            - Each state (idx, w) is computed once.

        Space Complexity:
            O(n * W) for dp table
            O(n) recursion stack space in worst case.
    */
    int recMaxProfit(int idx, int w, vector<int> &profit, vector<vector<int>> &dp, vector<int> &weight)
    {

        // Base case: only the first item is available
        if (idx == 0)
        {
            if (w >= weight[0])
                return dp[0][w] = (w / weight[0]) * profit[0];
            else if (w >= 0)
                return dp[0][w] = 0;
            else
                return 0;
        }

        // If capacity becomes negative, no profit possible
        // if (w < 0)
        //     return 0;

        // Return already computed result
        if (dp[idx][w] != -1)
            return dp[idx][w];

        int take = INT_MIN;

        // Option 1: Take the current item (unbounded => stay at idx)
        if (weight[idx] <= w)
            take = profit[idx] + recMaxProfit(idx, w - weight[idx], profit, dp, weight);

        // Option 2: Skip the current item
        int notTake = recMaxProfit(idx - 1, w, profit, dp, weight);

        // Store and return the best option
        return dp[idx][w] = max(take, notTake);
    }

    /*
        Method: unboundedKnapsack
        -------------------------
        Entry point for solving the unbounded knapsack problem using top-down DP.

        Parameters:
            n       - Number of available items.
            w       - Maximum capacity of the knapsack.
            profit  - Vector of profits for each item.
            weight  - Vector of weights for each item.

        Returns:
            int - Maximum profit achievable.

        Time Complexity:
            O(n * W), where W = knapsack capacity.

        Space Complexity:
            O(n * W) for dp table
            O(n) recursion stack space.
    */
    int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
    {
        vector<vector<int>> dp(n, vector<int>(w + 1, -1));
        return recMaxProfit(n - 1, w, profit, dp, weight);
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Rod Cutting Problem |
    //-------------------------------------------------------------------------------

    /*
    Method: recMax
    --------------
    Recursively computes the maximum profit obtainable from cutting a rod
    of length 'w' into pieces, where each piece of length (i+1) has a given price[i].

    Parameters:
        idx   - current index in 'price' array (represents piece length = idx+1)
        w     - remaining length of rod
        price - vector containing prices for rod pieces of length 1 to n
        dp    - memoization table, dp[i][len] stores max profit for rod length 'len'
                using pieces of size up to i+1

    Returns:
        int - maximum obtainable profit for given 'idx' and 'w'.

    Time Complexity:
        O(n * w) - Each state (idx, w) is computed once due to memoization.
        n = number of available piece sizes
        w = rod length

    Space Complexity:
        O(n * w) for dp table +
        O(n) recursion stack space in worst case.
*/
    int recMax(int idx, int w, vector<int> &price, vector<vector<int>> &dp)
    {

        // Base case: only piece length = 1 is available (idx == 0)
        if (idx == 0)
        {
            if ((idx + 1) <= w)
                // Take as many pieces of length 1 as possible
                // Profit = (number of pieces) * price of 1-length piece
                return dp[0][w] = (w / (idx + 1)) * price[0]; // basically: w * price[0]
            else
                // No space to cut even a single piece of length 1
                return 0;
        }

        // If already computed, return memoized value
        if (dp[idx][w] != -1)
            return dp[idx][w];

        int take = INT_MIN;

        // Option 1: Take the current piece length (idx + 1) if it fits
        if ((idx + 1) <= w)
            take = price[idx] + recMax(idx, w - (idx + 1), price, dp);

        // Option 2: Skip the current piece length, try smaller ones
        int notTake = recMax(idx - 1, w, price, dp);

        // Store and return the maximum profit
        return dp[idx][w] = max(take, notTake);
    }

    /*
        Method: cutRod
        --------------
        Driver function to compute maximum profit from cutting a rod of length 'n'.

        Parameters:
            price - vector containing prices of rod pieces of lengths 1 to n
            n     - length of the rod

        Returns:
            int - maximum obtainable profit.

        Time Complexity:
            O(n * n) - Since w = n in this case.

        Space Complexity:
            O(n * n) for dp table +
            O(n) recursion stack space.
    */
    int cutRod(vector<int> &price, int n)
    {
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return recMax(n - 1, n, price, dp);
    }
};

int main()
{
    return 0;
}
