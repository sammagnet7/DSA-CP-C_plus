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

1. Title: Longest Common Substring

Links:
https://takeuforward.org/data-structure/longest-common-substring-dp-27/
https://www.youtube.com/watch?v=_wP9mWNPL5w
https://takeuforward.org/plus/dsa/problems/longest-common-substring?tab=editorial


Problem statement:
You have been given two strings “str1” and “str2”. You have to find the length of the longest common substring.
A string “s1” is a substring of another string “s2” if “s2” contains the same characters as in “s1”, in the same order and in continuous fashion also.

For example :
If “str1” = “abcjklp” and “str2” = “acjkp”  then the output will be 3.
Explanation : The longest common substring is “cjk” which is of length 3.


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
// 1. Title: Longest Common Substring
//-------------------------------------------------------------------------------

class Solution
{
public:
    // ----------------------
    // Approach 1: 3D (TLE)
    // ---------------------

    /*
    Method: recCountSubstr
    ----------------------
    Recursive + Memoization approach to compute the length of the
    Longest Common Substring (LCSubStr) between two strings.

    Key difference from Longest Common Subsequence (LCS):
        - LCS allows skipping characters and still continuing the sequence count.
        - LCSubStr requires characters to be contiguous (matched length resets to 0 on mismatch).

    Parameters:
        idx1       - current index in 'text1'
        idx2       - current index in 'text2'
        matchedLen - current length of the ongoing contiguous match
        text1      - first string
        text2      - second string
        dp         - 3D DP table where:
                        dp[i][j][len] stores the maximum substring length
                        considering text1[0..i], text2[0..j]
                        with 'len' characters already matched contiguously

    Returns:
        int - length of the longest common substring considering the
              given indices and current matched length.

    Time Complexity:
        O(N1 * N2 * min(N1, N2))
        N1 = length of text1, N2 = length of text2
        - We explore each pair (i, j) and matchedLen up to min(N1, N2).

    Space Complexity:
        O(N1 * N2 * min(N1, N2)) for the DP table +
        O(N1 + N2) recursion stack space in worst case.
*/
    int recCountSubstr(int idx1, int idx2, int matchedLen,
                       string &text1, string &text2,
                       vector<vector<vector<int>>> &dp)
    {
        // Base case: ran out of characters in either string
        // For LCSubStr, return the length of the last contiguous match
        if (idx1 < 0 || idx2 < 0)
            return matchedLen;

        // If already computed, return stored value
        if (dp[idx1][idx2][matchedLen] != -1)
            return dp[idx1][idx2][matchedLen];

        int currentCount = matchedLen;

        // Case 1: characters match
        // In LCS we would do 1 + recurse on (idx1-1, idx2-1)
        // In LCSubStr we increase matchedLen and continue
        if (text1[idx1] == text2[idx2])
        {
            currentCount = recCountSubstr(idx1 - 1, idx2 - 1, matchedLen + 1,
                                          text1, text2, dp);
        }

        // Case 2: skip one character from either string (reset matchedLen to 0)
        // For LCS skipping doesn't reset count
        // For LCSubStr we must reset to 0 because substring must be contiguous
        int skipText1 = recCountSubstr(idx1 - 1, idx2, 0, text1, text2, dp);
        int skipText2 = recCountSubstr(idx1, idx2 - 1, 0, text1, text2, dp);

        // Take the maximum among:
        //  - continuing the current match
        //  - skipping from text1
        //  - skipping from text2
        return dp[idx1][idx2][matchedLen] =
                   max({currentCount, skipText1, skipText2});
    }

    /*
        Method: LCSubStr
        ----------------
        Driver function to compute the length of the
        Longest Common Substring between two strings using recursion + memoization.

        Parameters:
            str1 - first string
            str2 - second string

        Returns:
            int - length of the longest common substring.

        Time Complexity:
            O(N1 * N2 * min(N1, N2))
            - N1 = length of str1
            - N2 = length of str2

        Space Complexity:
            O(N1 * N2 * min(N1, N2)) for DP table +
            O(N1 + N2) recursion stack.
    */
    int LCSubStr(string &str1, string &str2)
    {
        int N1 = str1.size();
        int N2 = str2.size();

        // 3D DP: dp[i][j][len] stores max substring length for (i, j) with ongoing match length 'len'
        vector<vector<vector<int>>> dp(
            N1, vector<vector<int>>(N2, vector<int>(max(N1, N2) + 1, -1)));

        return recCountSubstr(N1 - 1, N2 - 1, 0, str1, str2, dp);
    }

    // ---------------------------------------------------------
    // Approach 2 : Iterative (Optimal) [RECOMMENDED]
    // --------------------------------------------------------

    /**
     * Finds the length of the Longest Common Substring between two strings.
     *
     * A "substring" here means a sequence of characters that appears
     * consecutively and in the same order in both strings.
     *
     * How it works:
     * -------------
     * We use dynamic programming to compare the strings character by character.
     * We build a table (dp) where each cell dp[i][j] tells us:
     *
     * dp[i][j] represents the length of the longest common substring
     *  that ends EXACTLY at s1[i-1] and s2[j-1].
     *  Remember: (dp index i, j is equivalent to str index (i-1), (j-1))
     *
     * - If the characters match, we extend the previous substring length by 1.
     * - If the characters don't match, the length resets to 0
     *   because substrings must be continuous.
     * - While filling this table, we keep track of the largest number we see
     *   that's our answer.
     *
     * Why it works:
     * -------------
     * The idea is that any common substring ending at a certain position
     * must also be a common substring ending at the previous position in both strings,
     * just extended by one character. A mismatch breaks the chain, so we reset.
     *
     * Complexity:
     * -----------
     * Time:  O(N1 * N2) -> we check each character pair once.
     * Space: O(N1 * N2) -> we store the results for all character pairs.
     */
    int LCSubStr(string str1, string str2)
    {
        int N1 = str1.size();
        int N2 = str2.size();

        vector<vector<int>> dp(N1 + 1, vector<int>(N2 + 1, 0));
        int maxLen = 0;

        for (int i = 1; i <= N1; i++)
        {
            for (int j = 1; j <= N2; j++)
            {
                if (str1[i - 1] == str2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }

        return maxLen;
    }

    // --------------------------------
    // Approach 3 : recursive (Optimal)
    // --------------------------------
    /**
     * Problem: Longest Common Substring (Recursive / Top-Down)
     * --------------------------------------------------------
     * 1. What rec(i, j) signifies:
     * It returns the length of the longest common substring ending EXACTLY
     * at s1[i-1] and s2[j-1].
     * * 2. The "Side Effect" Traversal:
     * Because the actual maximum streak could be hiding anywhere, we use a
     * reference variable `maxLength` to trap the highest value. We also MUST
     * call `rec(i-1, j)` and `rec(i, j-1)` just to guarantee we explore
     * every single (i, j) pair in the grid.
     * * 3. Time and Space Complexity:
     * - Time: O(N * M) because memoization ensures we calculate each state once.
     * - Space: O(N * M) for the DP table, plus O(N + M) for the recursion stack.
     */

    int rec(int i, int j, string &s1, string &s2, int &maxLength, vector<vector<int>> &dp)
    {

        // Base case: If either string is empty, the streak is 0.
        if (i == 0 || j == 0)
        {
            return 0;
        }

        // Memoization check
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // --- THE SIDE QUEST (Matrix Traversal) ---
        // We MUST trigger these recursive calls to ensure we explore the
        // combinations where we skip a character in s1 or s2.
        // We don't use their return values here; their only purpose is
        // to eventually trigger the matching logic below at different indices!
        rec(i - 1, j, s1, s2, maxLength, dp);
        rec(i, j - 1, s1, s2, maxLength, dp);

        // --- THE ACTUAL MATCHING LOGIC ---
        int currentStreak = 0;

        // If the characters match, we extend the diagonal streak
        if (s1[i - 1] == s2[j - 1])
        {
            currentStreak = 1 + rec(i - 1, j - 1, s1, s2, maxLength, dp);

            // Spy on the streak and trap the maximum value globally!
            maxLength = max(maxLength, currentStreak);
        }
        // If they don't match, currentStreak safely remains 0 (the streak is broken).

        // Cache and return the exact streak for this specific (i, j)
        return dp[i][j] = currentStreak;
    }

    int longestCommonSubstring(string s1, string s2)
    {
        int n = s1.length();
        int m = s2.length();

        // Global tracker for the highest streak we find
        int maxLength = 0;

        // DP table initialized to -1
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        // Start recursion from the very end of both strings
        rec(n, m, s1, s2, maxLength, dp);

        return maxLength;
    }
};

/*
    Note: How reconstruct the longest common substring?
    Ans: Store end_index, then extract the substring using str1[(end_index - max_length) : end_index ].
*/

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
