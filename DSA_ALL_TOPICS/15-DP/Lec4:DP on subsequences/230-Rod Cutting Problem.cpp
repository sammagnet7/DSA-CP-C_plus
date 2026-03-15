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

2. Title: Rod Cutting Problem

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


Sample Input 1:
2
5
2 5 7 8 10
8
3 5 8 9 10 17 17 20
Sample Output 1:
12
24
Explanation of sample input 1:
Test case 1:

All possible partitions are:
1,1,1,1,1           max_cost=(2+2+2+2+2)=10
1,1,1,2             max_cost=(2+2+2+5)=11
1,1,3               max_cost=(2+2+7)=11
1,4                 max_cost=(2+8)=10
5                   max_cost=(10)=10
2,3                 max_cost=(5+7)=12
1,2,2               max _cost=(1+5+5)=12

Clearly, if we cut the rod into lengths 1,2,2, or 2,3, we get the maximum cost which is 12.


Test case 2:

Possible partitions are:
1,1,1,1,1,1,1,1         max_cost=(3+3+3+3+3+3+3+3)=24
1,1,1,1,1,1,2           max_cost=(3+3+3+3+3+3+5)=23
1,1,1,1,2,2             max_cost=(3+3+3+3+5+5)=22
and so on….

If we cut the rod into 8 pieces of length 1, for each piece 3 adds up to the cost. Hence for 8 pieces, we get 8*3 = 24.
Sample Input 2:
1
6
3 5 6 7 10 12
Sample Output 2:
18



INPUT::::::


OUTPUT::::::


*/

#include <climits>

//-------------------------------------------------------------------------------
// 1. Title: Unbounded Knapsack (DP - 23)
//-------------------------------------------------------------------------------
class Solution
{
public:
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
            else
                return dp[0][w] = 0;
        }

        // if(w == 0){
        //     return 0;
        // }
        // if(idx<0){
        //     return INT_MIN;
        // }

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
};

//-------------------------------------------------------------------------------
// 2. Title: Rod Cutting Problem |
//-------------------------------------------------------------------------------

class Solution
{
public:
    //------------------------
    // Approach 1 : Recursive
    // -----------------------
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

    //------------------------
    // Approach 2 : Iterative
    // -----------------------

    /*
     * Problem: Rod Cutting
     * --------------------
     * Approach: Iterative DP (Bottom-Up Tabulation) / Unbounded Knapsack
     * * Concept:
     * This problem perfectly maps to the "Unbounded Knapsack" pattern.
     * - Knapsack Capacity: The total length of the rod (N).
     * - Items: The different lengths we can cut the rod into (1 to N).
     * - Item Weights: The lengths of these cuts.
     * - Item Values: The prices of these cuts.
     * - Unbounded: Since we can cut multiple pieces of the same length,
     * we have an infinite supply of each item.
     * * Complexity Analysis:
     * --------------------
     * Time Complexity: O(N^2)
     * - We have nested loops iterating N times and 'totalCap' (which is N) times.
     * Space Complexity: O(N^2)
     * - For the 2D DP table of size N x (N + 1).
     */

    int cutRod(vector<int> &price, int n)
    {
        int N = n;

        // The maximum length of the rod we need to form
        int totalCap = N;

        // Step 1: Create an array to represent the sizes of the cuts.
        // Cut sizes range from 1 to N.
        vector<int> size(N);
        for (int i = 0; i < N; ++i)
        {
            size[i] = i + 1;
        }

        // Step 2: Initialize the DP table
        // dp[idx][cap] stores the maximum profit we can get using cut sizes
        // from index 0 to 'idx' to form a rod of exactly length 'cap'.
        vector<vector<int>> dp(N, vector<int>(totalCap + 1, 0));

        // Step 3: Base Case Initialization (0th row)
        // If we only consider the first cut size (which is 1 unit long):
        // To make a rod of length 's', we simply use 's' pieces of length 1.
        if (size[0] <= totalCap)
        {
            for (int s = size[0]; s <= totalCap; ++s)
            {
                // Max profit = (number of pieces of size 1) * (price of size 1)
                dp[0][s] = ((s / size[0]) * price[0]);
            }
        }

        // Step 4: Fill the DP table
        for (int idx = 1; idx < N; ++idx)
        {
            for (int cap = 1; cap <= totalCap; ++cap)
            {

                int take = 0;

                // Choice 1: Make a cut of the current size (if it fits)
                if (size[idx] <= cap)
                {
                    // UNBOUNDED KNAPSACK KEY: Notice it is dp[idx], NOT dp[idx-1]!
                    // Because we can cut multiple pieces of the same size, we stay
                    // on the current row 'idx' after taking the piece to allow picking it again.
                    take = price[idx] + dp[idx][cap - size[idx]];
                }

                // Choice 2: Do not use the current cut size, move to smaller sizes
                int notTake = dp[idx - 1][cap];

                // Store the maximum of both choices
                dp[idx][cap] = max(take, notTake);
            }
        }

        // Return the max profit considering all cut sizes for the full rod length
        return dp[N - 1][totalCap];
    }
};

int main()
{
    return 0;
}
