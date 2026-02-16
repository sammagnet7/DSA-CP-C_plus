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

1. Title: The Power Sum


Links:
https://www.hackerrank.com/challenges/the-power-sum/problem


Problem statement:
Given two integers, X and N, determine the number of ways that X can be expressed as the sum of the N-th powers of unique, natural numbers.

Formally, you need to count the number of distinct sets {a1, a2, …, ak} such that:

    X = a1^N + a2^N + … + ak^N

where each ai is a positive integer, and all ai are distinct.

Example
-------
Input:
X = 10
N = 2

Possible combinations:
- 10 = 1^2 + 3^2

So, there is only 1 way.

Output:
1

Function Description
--------------------
Complete the function powerSum in the editor below.

    int powerSum(int X, int N);

- X: the integer to be expressed as a sum.
- N: the exponent value.

Returns:
- An integer representing the number of ways X can be expressed as the sum of unique natural numbers raised to the power N.

Constraints
-----------
1 <= X <= 1000
1 <= N <= 10




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
    // 1. Title: The Power Sum
    //-------------------------------------------------------------------------------

    // ------------------------------------------------------------
    // Approach:
    // We are solving the "Power Sum" problem using recursion + DP.
    //
    // Step 1: Generate all possible powers a^N such that a^N <= X.
    // Step 2: Use recursion with memoization (top-down DP) to count
    //         the number of ways to form X using these powers.
    //         Each power can be used at most once (subset style).
    //
    // DP State: dp[idx][rem]
    //    - idx = index of current power being considered
    //    - rem = remaining sum we want to achieve
    // Value: number of ways to form 'rem' using powers[0..idx].
    //
    // Transition:
    //    - Either skip current power: dfs(idx-1, rem)
    //    - Or include current power: dfs(idx-1, rem - powers[idx])
    //
    // Base Cases:
    //    - rem == 0 → 1 way (found a valid combination)
    //    - rem < 0 or idx < 0 → 0 ways (invalid path)
    //
    // Time Complexity: O(n * X)
    //    where n ≈ X^(1/N) (number of valid powers).
    //    Because each state (idx, rem) is computed once.
    //
    // Space Complexity: O(n * X)
    //    for the memoization table dp.
    // ------------------------------------------------------------

    // Recursive helper with memoization
    int dfs(const vector<int> &powers, int idx, int rem, vector<vector<int>> &dp)
    {
        if (rem == 0)
            return 1; // exact sum formed → valid combination
        if (rem < 0)
            return 0; // overshot the target
        if (idx < 0)
            return 0; // no numbers left to use

        // if already computed, reuse the result
        if (dp[idx][rem] != -1)
            return dp[idx][rem];

        // choice 1: skip current power
        int without = dfs(powers, idx - 1, rem, dp);

        // choice 2: take current power (reduce rem accordingly)
        int withIt = dfs(powers, idx - 1, rem - powers[idx], dp);

        // store and return total ways
        return dp[idx][rem] = without + withIt;
    }

    int powerSum(int X, int N)
    {
        vector<int> powers;

        // generate all a^N <= X
        for (int a = 1;; ++a)
        {
            long long p = 1;
            for (int i = 0; i < N; ++i)
            {
                p *= a;
                if (p > X)
                    break; // stop if power exceeds X
            }
            if (p > X)
                break; // further a will only make bigger powers
            powers.push_back((int)p);
        }

        int n = powers.size();

        // initialize DP table with -1 (uncomputed states)
        vector<vector<int>> dp(n, vector<int>(X + 1, -1));

        // start recursion from last index (largest power) and full target X
        dfs(powers, n - 1, X, dp);

        // answer is number of ways to form X using all powers
        return dp[n - 1][X];
    }

    //------------------------------
    // Approach 2: Iterative
    //------------------------------

    /*
     * Function: powerSum
     * ------------------
     * Calculates the number of ways to express X as the sum of N-th powers
     * of unique, natural numbers.
     *
     * Approach: 0/1 Knapsack Pattern (Dynamic Programming)
     * - We have a set of "items": {1^N, 2^N, 3^N, ...}
     * - We want to find how many subsets of these items sum up exactly to X.
     * - Since each number must be unique, we can use each item at most once.
     */
    int powerSum(int X, int N)
    {
        int target = X;

        // 1. Determine the range of numbers to consider.
        // We only need bases 'b' where b^N <= X.
        // Example: X=10, N=2 -> 1^2=1, 2^2=4, 3^2=9. 4^2=16 (too big). Limit is 3.
        int baseLimit = 1;
        while (pow(baseLimit + 1, N) <= target)
        {
            baseLimit++;
        }

        // 2. Initialize DP Table
        // Rows (b): Considering numbers from 0 up to 'b'.
        // Cols (t): Target sum from 0 to X.
        // DP[b][t] = Number of ways to get sum 't' using a subset of {1^N ... b^N}
        vector<vector<int>> DP(baseLimit + 1, vector<int>(target + 1, 0));

        // 3. Base Case Initialization
        // If target sum is 0, there is exactly 1 way: choose the Empty Set {}.
        // This is true regardless of how many items we are allowed to consider.
        for (int b = 0; b <= baseLimit; ++b)
        {
            DP[b][0] = 1;
        }

        // 4. Fill the DP Table
        // Iterate through each number 'b' (representing item value b^N)
        for (int b = 1; b <= baseLimit; ++b)
        {

            // Iterate through all possible sums 't'
            for (int t = 1; t <= target; ++t)
            {

                // Value of the current item we are considering
                int curVal = pow(b, N); // Note: Variable name 'curSquare' generalized to 'curVal'

                // Option A: "Take" the current number b^N
                // We can only take it if the current sum 't' is large enough.
                // If we take it, we look at the remaining sum (t - curVal)
                // using previous items (b-1).
                int take = 0;
                if (t - curVal >= 0)
                {
                    take = DP[b - 1][t - curVal];
                }

                // Option B: "Not Take" the current number b^N
                // If we skip this number, the ways to form sum 't' is exactly the same
                // as the ways to form it using only the previous items {1^N ... (b-1)^N}.
                int notTake = DP[b - 1][t];

                // Total ways is sum of both choices
                DP[b][t] = take + notTake;
            }
        }

        // The answer is in the bottom-right cell:
        // Using all available numbers up to baseLimit to form the full target X.
        return DP[baseLimit][target];
    }

    //---------------------------------------
    // Approach 2: Iterative -Space Optimized
    //---------------------------------------

    /*
     * Function: powerSum
     * ------------------
     * Calculates the number of ways to represent 'X' as the sum of unique
     * natural numbers raised to the power 'N'.
     *
     * Approach: Dynamic Programming (Space Optimized - Two Rows)
     * Pattern: 0/1 Knapsack (Each number can be used at most once).
     *
     * Complexity Analysis:
     * --------------------
     * Time Complexity: O(X * X^(1/N))
     * - We iterate through 'baseLimit' numbers. baseLimit is approx X^(1/N).
     * - For each number, we iterate up to 'target' (X).
     * - Total operations ≈ X * X^(1/N).
     * - Example (X=1000, N=2): ~31 * 1000 = 31,000 operations (Very Fast).
     *
     * Space Complexity: O(X)
     * - We use two vectors 'prev' and 'cur' of size X.
     * - Standard 2D DP would be O(baseLimit * X). This is a significant reduction.
     */
    int powerSum(int X, int N)
    {
        int target = X;

        // 1. Calculate the Upper Limit
        // We only need to consider base numbers 'b' such that b^N <= X.
        // E.g., if X=10, N=2, we check 1, 2, 3 (since 3^2=9 <= 10, but 4^2=16 > 10).
        int baseLimit = 1;
        while (pow(baseLimit + 1, N) <= target)
        {
            baseLimit++;
        }

        // 2. Initialize Previous Row (prev)
        // prev[t] stores the number of ways to form sum 't' using previous numbers.
        vector<int> prev(target + 1, 0);

        // Base Case: There is 1 way to make sum 0 (Empty Set).
        prev[0] = 1;

        // 3. Iterate through each candidate number 'b'
        for (int b = 1; b <= baseLimit; ++b)
        {

            // Create Current Row (cur)
            // This will store results for the range [1...b]
            vector<int> cur(target + 1, 0);

            // CRITICAL STEP:
            // We must carry over the base case. Sum 0 is always possible (empty set).
            // Without this, the logic breaks for subsequent numbers.
            cur[0] = 1;

            // 4. Calculate states for the current number 'b'
            for (int t = 1; t <= target; ++t)
            {

                int take = 0;
                int curVal = pow(b, N); // The value being added (b^N)

                // Option 1: Take the current number
                // Only valid if the current target 't' is greater than or equal to b^N.
                // We look at 'prev' (row b-1) because we need unique numbers.
                if (t - curVal >= 0)
                {
                    take = prev[t - curVal];
                }

                // Option 2: Do not take the current number
                // The ways to form 't' remain the same as they were without 'b'.
                int notTake = prev[t];

                // Sum of possibilities
                cur[t] = take + notTake;
            }

            // 5. Shift Rows
            // The current row becomes the previous row for the next iteration.
            // This effectively slides our "window" of memory forward.
            prev = cur;
        }

        // The final answer is in the last computed row for the full target sum.
        return prev[target];
    }
};

int main()
{
    return 0;
}
