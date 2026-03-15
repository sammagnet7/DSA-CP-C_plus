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

1. Title: Distinct Subsequences (Strict pattern & Asymmetric)

Links:
https://takeuforward.org/data-structure/distinct-subsequences-dp-32/
https://www.youtube.com/watch?v=nVG7eTiD2bY
https://takeuforward.org/plus/dsa/problems/distinct-subsequences?tab=editorial
https://leetcode.com/problems/distinct-subsequences/description/


Problem statement:
Given two strings s and t, return the number of distinct subsequences of s which equals t.
The test cases are generated so that the answer fits on a 32-bit signed integer.

Examples:
    Example 1:
    Input: s = "rabbbit", t = "rabbit"
    Output: 3
    Explanation:
    As shown below, there are 3 ways you can generate "rabbit" from s.
    rabbbit
    rabbbit
    rabbbit

    Example 2:
    Input: s = "babgbag", t = "bag"
    Output: 5
    Explanation:
    As shown below, there are 5 ways you can generate "bag" from s.
    babgbag
    babgbag
    babgbag
    babgbag
    babgbag


Constraints:
    1 <= s.length, t.length <= 1000
    s and t consist of English letters.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:


Problem statement:



INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Distinct Subsequences (Strict pattern & Asymmetric)
//-------------------------------------------------------------------------------
class Solution
{
public:
    //-----------------------------
    // Approch 1 : Recursive
    // ----------------------------

    /*
        Problem:
        --------
        Count the number of distinct subsequences of string `s`
        that equal string `t`.

        Example:
        --------
        s = "babgbag", t = "bag"
        Answer = 5
        Subsequences:
        - b(0) a(1) g(3)
        - b(0) a(1) g(6)
        - b(0) a(4) g(6)
        - b(2) a(4) g(6)
        - b(2) a(1) g(3)

        Idea:
        -----
        - We solve this using recursion + memoization.
        - At each step (sIndex, tIndex):
            - If s[sIndex] == t[tIndex], we have 2 choices:
                1. Take this match → move both indices (sIndex-1, tIndex-1)
                2. Skip this character in s → move (sIndex-1, tIndex)
            - If s[sIndex] != t[tIndex], only option is to skip (sIndex-1, tIndex).
        - Base cases:
            - If tIndex < 0 → we have matched all of t → return 1 (valid subsequence found).
            - If sIndex < 0 but tIndex >= 0 → s is exhausted before matching t → return 0.
        - Memoize results to avoid recomputation.

        Complexity:
        -----------
        - Time:  O(n1 * n2), where n1 = |s|, n2 = |t|
        - Space: O(n1 * n2) for memoization table (dp)
    */

    int countSubsequences(int sIndex, int tIndex, string &s, string &t, vector<vector<int>> &dp)
    {
        // Base case: matched all characters of t
        if (tIndex < 0)
        {
            return 1;
        }
        // Base case: exhausted s but not t
        if (sIndex < 0)
        {
            return 0;
        }

        // Return already computed value
        if (dp[sIndex][tIndex] != -1)
        {
            return dp[sIndex][tIndex];
        }

        int takeBoth = 0;
        if (s[sIndex] == t[tIndex])
        {
            // Option 1: use this character in both s and t
            takeBoth = countSubsequences(sIndex - 1, tIndex - 1, s, t, dp);
        }

        // Option 2: skip this character in s
        int skipCurrent = countSubsequences(sIndex - 1, tIndex, s, t, dp);

        // Store result in DP table
        return dp[sIndex][tIndex] = takeBoth + skipCurrent;
    }

    int numDistinct(string s, string t)
    {
        int n1 = s.size();
        int n2 = t.size();

        // Memoization table, initialized to -1
        vector<vector<int>> dp(n1, vector<int>(n2, -1));

        // Start recursion from the last indices of s and t
        return countSubsequences(n1 - 1, n2 - 1, s, t, dp);
    }

    //-----------------------------
    // Approch 2 : Iterative
    // ----------------------------

    /**
     * APPROACH 2: Standard Distinct Subsequences DP
     * * IDEA:
     * We want to find how many times string `t` appears as a subsequence in `s`.
     * We only ever delete characters from `s`. We NEVER delete characters from `t`.
     * * dp[i][j] stores the number of ways to form the prefix t[0...j-1]
     * using the prefix s[0...i-1].
     * * TIME COMPLEXITY: O(N * M)
     * SPACE COMPLEXITY: O(N * M) - Can be optimized to O(M) using a 1D array.
     */
    int numDistinct(string s, string t)
    {
        int n = s.length();
        int m = t.length();

        // Use unsigned long long to prevent intermediate overflow on massive test cases.
        // LeetCode guarantees the FINAL answer fits in a 32-bit int, but intermediate
        // additions can temporarily exceed that limit.
        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

        // --- BASE CASES ---
        // An empty string `t` (length 0) can be formed from any prefix of `s` in exactly 1 way
        // (by deleting all characters from `s`).
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }
        // Note: dp[0][j] for j > 0 remains 0, because an empty `s` cannot form a non-empty `t`.

        // --- DP TRANSITIONS ---
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {

                // CASE A: The current characters match.
                if (s[i - 1] == t[j - 1])
                {
                    // We have two choices:
                    // 1. USE the match: Inherit the successful paths from the diagonal (dp[i-1][j-1]).
                    // 2. IGNORE the match: Inherit the successful paths from the top (dp[i-1][j]),
                    //    meaning we pretend this character in `s` doesn't exist.
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                }
                // CASE B: The current characters DO NOT match.
                else
                {
                    // We have no choice but to IGNORE the current character in `s`.
                    // We just carry over whatever paths we already found previously.
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // The bottom-right cell contains the total number of ways to form the full string `t`
        return static_cast<int>(dp[n][m]);
    }

    //--------------------------------------------------
    // Approch 3 : Using Blue print of: LCS Path Counter
    // -------------------------------------------------
    /**
     * APPROACH 3: The "Superset" LCS Path Counter
     * * IDEA:
     * Calculate ALL distinct paths for the Longest Common Subsequence (LCS) between `s` and `t`.
     * This will naturally include paths that only partially match `t` (garbage paths).
     * At the very end, we check if the max LCS length equals the length of `t`. If it does,
     * the mathematically relevant paths will perfectly isolate themselves.
     * * TIME COMPLEXITY: O(N * M)
     * SPACE COMPLEXITY: O(N * M) - Uses two matrices (dp for length, cnt for paths).
     */
    int numDistinct(string s, string t)
    {
        int n = s.length();
        int m = t.length();

        // dp tracks the maximum LCS length found so far
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // cnt tracks the number of paths.
        // CRITICAL: We MUST use unsigned long long. The "garbage" paths for partial matches
        // will grow exponentially and overflow. Unsigned types in C++ safely wrap around
        // to 0 instead of crashing the program.
        vector<vector<unsigned long long>> cnt(n + 1, vector<unsigned long long>(m + 1, 0));

        // --- BASE CASES ---
        // 1 way to form an LCS of length 0.
        for (int i = 0; i <= n; i++)
            cnt[i][0] = 1;
        for (int j = 0; j <= m; j++)
            cnt[0][j] = 1;

        // --- DP TRANSITIONS ---
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {

                // 1. Standard LCS Length Calculation
                if (s[i - 1] == t[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }

                // 2. Combinatorial Path Counting
                unsigned long long ways = 0;

                // Path A: Diagonal Match
                if (s[i - 1] == t[j - 1])
                {
                    ways += cnt[i - 1][j - 1];
                }

                // Path B: Inherit from Top
                if (dp[i][j] == dp[i - 1][j])
                {
                    ways += cnt[i - 1][j];
                }

                // Path C: Inherit from Left
                // (Note: For valid paths where dp[i][j] == j, this condition silently fails,
                // successfully mimicking the strict one-directional rule of LC 115).
                if (dp[i][j] == dp[i][j - 1])
                {
                    ways += cnt[i][j - 1];
                }

                // Path D: Inclusion-Exclusion Overlap
                // (Note: Like Path C, this safely self-destructs for valid LC 115 paths).
                if (dp[i][j] == dp[i - 1][j - 1])
                {
                    // Unsigned subtraction safely wraps underflow in C++
                    ways -= cnt[i - 1][j - 1];
                }

                cnt[i][j] = ways;
            }
        }

        // --- STRICT FILTER ---
        // If the maximum LCS length is not exactly the length of `t`,
        // it means `t` does not exist fully inside `s`. Return 0.
        if (dp[n][m] != m)
        {
            return 0;
        }

        // Return the successfully isolated paths
        return static_cast<int>(cnt[n][m]);
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
