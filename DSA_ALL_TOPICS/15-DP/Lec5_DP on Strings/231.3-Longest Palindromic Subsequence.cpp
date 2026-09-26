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


1. Title: Longest Palindromic Subsequence (LPS)

Links:
    https://takeuforward.org/data-structure/longest-palindromic-subsequence-dp-28/
    https://takeuforward.org/plus/dsa/problems/longest-palindromic-subsequence?tab=editorial
    https://leetcode.com/problems/longest-palindromic-subsequence/description/


Problem statement:
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.


Example 1:
Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:
Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".


Constraints:
1 <= s.length <= 1000
s consists only of lowercase English letters.


INPUT::::::


OUTPUT::::::

Similar question:

    1) Minimum insertions to make string palindrome | DP-29
            https://takeuforward.org/data-structure/minimum-insertions-to-make-string-palindrome-dp-29/
            https://takeuforward.org/plus/dsa/problems/minimum-insertions-to-make-string-palindrome?tab=editorial
            https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

            Sol: Ans is the number of characters NOT in the Longest Palindromic Subsequence from the original string.


----------------------------------------------------------------------------------------------------

2. Title:
Links:



Problem statement:



INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Longest Palindromic Subsequence
//-------------------------------------------------------------------------------

//-------------------------------------------
// Approach 1: Using Iterative LCS (Prefix DP)
//-------------------------------------------
class Solution
{
public:
    /*
        Method: longestPalindromeSubseq
        --------------------------------
        Finds the length of the Longest Palindromic Subsequence (LPS) in a given string.

        Approach:
        ---------
        - The LPS problem can be transformed into a **Longest Common Subsequence (LCS)** problem:
            • If we reverse the string, the LPS in the original string will be the LCS between
            the original string and its reversed version.
            • Example:
                s   = "bbbab"
                rev = "babbb"
            LCS(s, rev) = "bbbb" → length 4, which is the LPS length.

        Steps:
        ------
        1. Create a reversed copy of the input string.
        2. Use **Dynamic Programming** to compute the LCS length between the original string `s`
        and its reversed version `rev`.
        3. Since we only need the previous row to compute the current row, use **1D space optimization**
        with two vectors: `prev` (previous row) and `cur` (current row).
        4. Fill the DP table:
            - If characters match → extend previous subsequence: `cur[j] = prev[j-1] + 1`
            - If characters don't match → take the max of skipping one char from either string:
                `cur[j] = max(prev[j], cur[j-1])`
        5. The last value of `prev[n]` will contain the LPS length.

        Complexity:
        -----------
        - Time:  O(n²) → We compare every pair of characters.
        - Space: O(n)  → Only two arrays of size n+1 are stored (space-optimized DP).

        Example:
        --------
            Input:  "bbbab"
            Reverse: "babbb"
            LCS = 4 → "bbbb"
            Output: 4
    */
    int longestPalindromeSubseq(string s)
    {

        string rev = s;
        reverse(rev.begin(), rev.end());

        int n = s.size();

        vector<int> prev(n + 1, 0), cur(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (s[i - 1] == rev[j - 1])
                {
                    cur[j] = prev[j - 1] + 1;
                }
                else
                {
                    cur[j] = max(prev[j], cur[j - 1]);
                }
            }
            prev = cur;
        }

        return prev[n];
    }
};

//---------------------------------------------
// Approach 2: Using Recursive Interval DP
//---------------------------------------------

/**
 * Problem: Longest Palindromic Subsequence
 * ----------------------------------------
 * 1. Idea of the solution:
 * We use Top-Down Interval Dynamic Programming (Recursion + Memoization).
 * We maintain two pointers, 'l' at the start and 'r' at the end of a substring.
 * We evaluate the characters at these pointers and shrink the interval inwards.
 * * 2. What DP[l][r] signifies:
 * DP[l][r] represents the maximum length of a palindromic subsequence
 * strictly within the bounds of the substring s[l...r].
 * * 3. Derivation of the DP formula:
 * - CASE 1: s[l] == s[r] (Outer characters DO match)
 * Since they match, they form a palindrome of length 2. We add this 2 to the
 * longest palindrome we can find in the remaining inner substring (l+1 to r-1).
 * Formula: 2 + rec(l+1, r-1)
 * * - CASE 2: s[l] != s[r] (Outer characters do NOT match)
 * They cannot be part of the same palindrome together. We must see which
 * choice gives us a longer palindrome:
 * Choice A: Skip the left character and check the rest (l+1 to r)
 * Choice B: Skip the right character and check the rest (l to r-1)
 * Formula: max(rec(l+1, r), rec(l, r-1))
 * * 4. Base Cases:
 * - if (l == r): Return 1. A single character is always a palindrome of length 1.
 * - if (r < l): Return 0. The pointers have crossed, meaning the substring is empty.
 * * 5. Time and Space Complexity:
 * - Time Complexity: O(N^2)
 * There are N^2 possible pairs of (l, r). Memoization ensures we compute
 * each state exactly once.
 * - Space Complexity: O(N^2)
 * We use an N x N matrix for the DP table, plus O(N) auxiliary stack space
 * for the maximum depth of the recursion tree.
 */

class Solution
{
private:
    int rec(int l, int r, string &s, vector<vector<int>> &dp)
    {

        // Base Case 1: Pointers meet in the middle.
        // A single character contributes a length of 1 to the palindrome.
        if (l == r)
        {
            return 1;
        }

        // Base Case 2: Pointers cross.
        // No characters left to process, contributes 0 length.
        if (r < l)
        {
            return 0;
        }

        // Memoization Check: If we have already solved this exact interval,
        // return the cached answer to avoid redundant calculations.
        if (dp[l][r] != -1)
        {
            return dp[l][r];
        }

        int len = 0;

        // Case 1: Outer characters match
        if (s[l] == s[r])
        {
            // Add 2 for the matching outer characters, then move BOTH pointers inward
            len = 2 + rec(l + 1, r - 1, s, dp);
        }
        // Case 2: Outer characters do NOT match
        else
        {
            // Take the maximum length found by either skipping the left character
            // OR skipping the right character
            len = max(rec(l + 1, r, s, dp), rec(l, r - 1, s, dp));
        }

        // Cache the result in the DP table before returning
        return dp[l][r] = len;
    }

public:
    int longestPalindromeSubseq(string s)
    {

        int N = s.length();

        // Initialize an N x N DP table with -1 (representing uncomputed states)
        vector<vector<int>> dp(N, vector<int>(N, -1));

        // Start the recursive function with bounds covering the entire string
        return rec(0, N - 1, s, dp);
    }
};

//---------------------------------------------
// Approach 3: Using Iterative Interval DP
//---------------------------------------------
/**
 * Problem: Longest Palindromic Subsequence (Iterative / Bottom-Up)
 * ----------------------------------------------------------------
 * 1. Idea of the solution:
 * We use Bottom-Up Interval DP. Instead of recursion, we fill a 2D table manually.
 * To ensure smaller subproblems are solved before larger ones, our outer loop
 * iterates over the *length* of the interval (from 2 to N), and our inner loop
 * slides that interval across the string.
 * 
 * * 2. What DP[l][r] signifies:
 * The maximum length of a palindromic subsequence strictly within s[l...r].
 * 
 * * 3. DP Transitions:
 * - If s[l] == s[r]: dp[l][r] = 2 + dp[l+1][r-1]
 * - If s[l] != s[r]: dp[l][r] = max(dp[l+1][r], dp[l][r-1])
 * 
 * * 4. Base Cases:
 * Every single character is a palindrome of length 1.
 * Therefore, for all indices 'i', dp[i][i] = 1.
 * 
 * * 5. Time and Space Complexity:
 * - Time Complexity: O(N^2). We have two nested loops evaluating every possible interval.
 * - Space Complexity: O(N^2) for the DP table. (Unlike recursion, there is no stack memory used!)
 */


class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        int N = s.length();

        // Initialize an N x N DP table with 0.
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Base Case: Every individual character is a palindrome of length 1.
        for (int i = 0; i < N; ++i)
        {
            dp[i][i] = 1;
        }

        // Loop 1: 'len' is the current length of the interval we are solving.
        // We start at length 2, up to the full length N.
        for (int len = 2; len <= N; ++len)
        {

            // Loop 2: 'l' is the starting index of our interval.
            // We slide the window of size 'len' across the string.
            for (int l = 0; l <= N - len; ++l)
            {

                // Calculate the ending index 'r' based on the start index and length
                int r = l + len - 1;

                // Case 1: Outer characters match
                if (s[l] == s[r])
                {
                    // 2 for the outer matches + the best palindrome inside them
                    dp[l][r] = 2 + dp[l + 1][r - 1];
                }
                // Case 2: Outer characters do NOT match
                else
                {
                    // Take the max of ignoring the left character OR ignoring the right character
                    dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
                }
            }
        }

        // The answer for the entire string is stored in the interval from 0 to N-1
        return dp[0][N - 1];
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
