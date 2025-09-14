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

    /*
     * Complete the 'powerSum' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER X → target sum
     *  2. INTEGER N → exponent to raise natural numbers
     */
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

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
