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

1. Title: Distinct Subsequences| (DP-32)

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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Distinct Subsequences| (DP-32)
    //-------------------------------------------------------------------------------

    //----------
    // Approch 1
    // ---------

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

    //----------
    // Approch 2
    // ---------

    const int prime = 1e9 + 7;
    /* Function to count the number of
    distinct subsequences of s2 in s1*/
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        /* Initialize the first row: empty string s2
        can be matched with any non-empty s1 in one way*/
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        /* Initialize the first column:
        s1 can't match any non-empty s2*/
        for (int i = 1; i <= m; i++)
        {
            dp[0][i] = 0;
        }

        // Fill in the DP array
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                {
                    /* If the characters match, consider two options:
                    either leave one character in s and t or leave
                    one character in s and continue matching t*/
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % prime;
                }
                else
                {
                    /* If the characters don't match, we can
                    only leave the current character in s*/
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        /* The value at dp[n][m] contains
        the count of distinct subsequences*/
        return dp[n][m];
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
