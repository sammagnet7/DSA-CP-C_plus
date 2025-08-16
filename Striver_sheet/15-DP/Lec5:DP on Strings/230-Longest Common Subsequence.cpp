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

1. Title: Longest Common Subsequence

Links:
https://takeuforward.org/data-structure/longest-common-subsequence-dp-25/
https://www.youtube.com/watch?v=NPZn9jBrX8U&feature=youtu.be
https://takeuforward.org/plus/dsa/problems/longest-common-subsequence?tab=editorial
https://leetcode.com/problems/longest-common-subsequence/description/



Problem statement:
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Examples:
    Example 1:
    Input: text1 = "abcde", text2 = "ace"
    Output: 3
    Explanation: The longest common subsequence is "ace" and its length is 3.

    Example 2:
    Input: text1 = "abc", text2 = "abc"
    Output: 3
    Explanation: The longest common subsequence is "abc" and its length is 3.

    Example 3:
    Input: text1 = "abc", text2 = "def"
    Output: 0
    Explanation: There is no such common subsequence, so the result is 0.


Constraints:
1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.


INPUT::::::


OUTPUT::::::


Similar quetion:
1) Longest Palindromic Subsequence | (DP-28) :
        https://takeuforward.org/data-structure/longest-palindromic-subsequence-dp-28/
        https://takeuforward.org/plus/dsa/problems/longest-palindromic-subsequence?tab=editorial
        https://leetcode.com/problems/longest-palindromic-subsequence/description/

        Sol: Ans is the LCS between the original string and its reversed version.

2) Minimum insertions to make string palindrome | DP-29
        https://takeuforward.org/data-structure/minimum-insertions-to-make-string-palindrome-dp-29/
        https://takeuforward.org/plus/dsa/problems/minimum-insertions-to-make-string-palindrome?tab=editorial
        https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

        Sol: Ans is the number of characters NOT in the Longest Palindromic Subsequence from the original string.

3) Minimum Insertions/Deletions to Convert String | (DP- 30)
        https://takeuforward.org/data-structure/minimum-insertions-deletions-to-convert-string-dp-30/
        https://www.youtube.com/watch?v=yMnH0jrir0Q
        https://takeuforward.org/plus/dsa/problems/minimum-insertions-or-deletions-to-convert-string-a-to-b?tab=editorial
        https://leetcode.com/problems/delete-operation-for-two-strings/description/

        Sol: If we know the LCS length, then:
            - The characters not in LCS must be deleted from both strings to match word1 and word2.
            - or we can say to make word1 same as word2 
                - first remove (len(word1) - LCS) chars from word1
                - then insert (len(word2) - LCS) chars from word2 to word1
                - Total Required operations: (len(word1) - LCS) + (len(word2) - LCS)


----------------------------------------------------------------------------------------------------

2. Title: Print Longest Common Subsequence | (DP - 26)

Links:
https://takeuforward.org/data-structure/print-longest-common-subsequence-dp-26/
https://www.youtube.com/watch?v=-zI4mrF2Pb4
https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383?leftPanelTabValue=PROBLEM


Problem statement:
You are given two strings ‘s1’ and ‘s2’.

Return the longest common subsequence of these strings.

If there’s no such string, return an empty string. If there are multiple possible answers, return any such string.

Note:
Longest common subsequence of string ‘s1’ and ‘s2’ is the longest subsequence of ‘s1’ that is also a subsequence of ‘s2’. A ‘subsequence’ of ‘s1’ is a string that can be formed by deleting one or more (possibly zero) characters from ‘s1’.


Example:
Input: ‘s1’  = “abcab”, ‘s2’ = “cbab”
Output: “bab”

Sample Input 1:
5 6
ababa
cbbcad


Expected Answer:
"bba"

Output on console:
1

Explanation of sample output 1:
“bba” is only possible longest subsequence present in both s1 = “ababa” and s2 = “cbbcad”. '1' is printed if the returned string is equal to "bba".
Sample Input 2:
3 3
xyz
abc

Expected Answer:
""
Output on console:
1

Explanation of sample output 2:
There’s no subsequence of ‘s1’ that is also present in ‘s2’. Thus an empty string is returned and '1' is printed.


Expected Time Complexity:
Try to solve this in O(n*m). Where ‘n’ is the length of ‘s1’ and ‘m’ is the length of ‘s2’.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Longest Common Subsequence
    //-------------------------------------------------------------------------------

    // -----------------
    // Approach 1
    // ----------------

    /*
        Method: recCountSubseq
        ----------------------
        Recursively computes the length of the Longest Common Subsequence (LCS) between
        text1[0..idx1] and text2[0..idx2] using memoization.

        Parameters:
            idx1   - current index in text1 (0-based)
            idx2   - current index in text2 (0-based)
            text1  - first input string
            text2  - second input string
            dp     - memoization table where dp[i][j] stores the LCS length
                    for text1[0..i] and text2[0..j]

        Returns:
            int - length of the LCS for the given indices.

        Time Complexity:
            O(N1 * N2)
            Each (idx1, idx2) pair is computed once due to memoization.
            N1 = length of text1
            N2 = length of text2

        Space Complexity:
            O(N1 * N2) for dp table
            O(N1 + N2) recursion stack space in the worst case.
    */
    int recCountSubseq(int idx1, int idx2, string &text1, string &text2, vector<vector<int>> &dp)
    {

        // Base case: if either string is fully traversed, no subsequence remains
        if (idx1 < 0 || idx2 < 0)
        {
            return 0;
        }

        // Return memoized result if already computed
        if (dp[idx1][idx2] != -1)
            return dp[idx1][idx2];

        int maxCount = 0;

        if (text1[idx1] == text2[idx2])
        {
            // Characters match → include this character in LCS
            int takeBoth = 1 + recCountSubseq(idx1 - 1, idx2 - 1, text1, text2, dp);
            maxCount = takeBoth;
        }
        else
        {
            // Characters don't match → try both possibilities and take the maximum
            int skipText1 = recCountSubseq(idx1 - 1, idx2, text1, text2, dp);
            int skipText2 = recCountSubseq(idx1, idx2 - 1, text1, text2, dp);
            maxCount = max(skipText1, skipText2);
        }

        // Store and return the result
        return dp[idx1][idx2] = maxCount;
    }

    /*
        Method: longestCommonSubsequence
        --------------------------------
        Computes the length of the Longest Common Subsequence (LCS) between two strings.

        Parameters:
            text1 - first input string
            text2 - second input string

        Returns:
            int - length of the LCS.

        Time Complexity:
            O(N1 * N2)
            N1 = length of text1
            N2 = length of text2

        Space Complexity:
            O(N1 * N2) for dp table
            O(N1 + N2) recursion stack space.
    */
    int longestCommonSubsequence(string text1, string text2)
    {

        int N1 = text1.size();
        int N2 = text2.size();

        // Initialize dp table with -1 (uncomputed states)
        vector<vector<int>> dp(N1, vector<int>(N2, -1));

        return recCountSubseq(N1 - 1, N2 - 1, text1, text2, dp);
    }

    // -----------------
    // Approach 2
    // ----------------

    /*
        Method: longestCommonSubsequence
        --------------------------------
        Computes the length of the Longest Common Subsequence (LCS) between two strings
        using bottom-up dynamic programming.

        Definition:
            - A subsequence is a sequence derived from another sequence by deleting
            some or no elements without changing the order of the remaining elements.
            - LCS is the longest subsequence present in both strings.

        Parameters:
            text1 - first input string
            text2 - second input string

        Returns:
            int - length of the longest common subsequence between text1 and text2.

        Approach:
            - We use a DP table `dp[i][j]` where:
                dp[i][j] = LCS length between the first `i` characters of text1
                        and the first `j` characters of text2.
            - Build the table iteratively:
                1. If characters match:
                    dp[i][j] = dp[i-1][j-1] + 1
                (extend the previous LCS by 1)
                2. If characters don't match:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                (skip a character from either text1 or text2)
            - Base case:
                dp[0][*] = 0  → empty first string → LCS length 0
                dp[*][0] = 0  → empty second string → LCS length 0

        Time Complexity:
            O(N1 * N2)
            - N1 = length of text1
            - N2 = length of text2
            - Each cell computed in O(1) time.

        Space Complexity:
            O(N1 * N2)
            - DP table of size (N1+1) × (N2+1)
    */
    int longestCommonSubsequence(string text1, string text2)
    {

        int N1 = text1.size();
        int N2 = text2.size();

        // DP table: dp[i][j] → LCS length between text1[0..i-1] and text2[0..j-1]
        // Initialized to 0 because LCS with an empty string is 0.
        vector<vector<int>> dp(N1 + 1, vector<int>(N2 + 1, 0));

        // Fill DP table bottom-up
        for (int i = 1; i <= N1; i++)
        {
            for (int j = 1; j <= N2; j++)
            {

                if (text1[i - 1] == text2[j - 1])
                {
                    // Characters match → extend the LCS from dp[i-1][j-1]
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    // Characters don't match → skip from either text1 or text2
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // The bottom-right cell contains the LCS length for the full strings
        return dp[N1][N2];
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Print Longest Common Subsequence | (DP - 26)
    //-------------------------------------------------------------------------------

    // -----------------
    // Approach 1
    // ----------------


    /*
        Helper Method: recCountSubseq
        -----------------------------
        Recursively computes the length of the Longest Common Subsequence (LCS)
        between s1[0..idx1] and s2[0..idx2] using memoization.

        Parameters:
            idx1 - current index in s1 (0-based)
            idx2 - current index in s2 (0-based)
            text1 - first string
            text2 - second string
            dp - memoization table where dp[i][j] stores the LCS length
                 for text1[0..i] and text2[0..j]

        Returns:
            int - length of the LCS for the given (idx1, idx2) pair

        Time Complexity:
            O(N1 * N2)  (each pair computed once)
        Space Complexity:
            O(N1 * N2) for dp + O(N1 + N2) recursion stack
    */
    int recCountSubseq(int idx1, int idx2, string &text1, string &text2, vector<vector<int>> &dp)
    {
        // Base case: if either string is fully traversed, no subsequence remains
        if (idx1 < 0 || idx2 < 0)
        {
            return 0;
        }

        // Return memoized result if already computed
        if (dp[idx1][idx2] != -1)
            return dp[idx1][idx2];

        int maxCount = 0;

        if (text1[idx1] == text2[idx2])
        {
            // Characters match → include this character in LCS
            int takeBoth = 1 + recCountSubseq(idx1 - 1, idx2 - 1, text1, text2, dp);
            maxCount = takeBoth;
        }
        else
        {
            // Characters don't match → try both possibilities and take the maximum
            int skipText1 = recCountSubseq(idx1 - 1, idx2, text1, text2, dp);
            int skipText2 = recCountSubseq(idx1, idx2 - 1, text1, text2, dp);
            maxCount = max(skipText1, skipText2);
        }

        // Store and return the result
        return dp[idx1][idx2] = maxCount;
    }

    /*
        Method: findLCS
        ---------------
        Finds and returns the Longest Common Subsequence (LCS) between two strings s1 and s2.

        Parameters:
            n  - length of s1
            m  - length of s2
            s1 - first input string
            s2 - second input string

        Returns:
            string - the LCS between s1 and s2

        Steps:
            1. Use `recCountSubseq` to compute the LCS length and fill the dp table.
            2. Reconstruct the actual LCS string by tracing back through dp.
               - If characters match, include them in the LCS.
               - Otherwise, move in the direction of the larger dp value.

        Time Complexity:
            O(N1 * N2) to fill dp + O(N1 + N2) to reconstruct string
        Space Complexity:
            O(N1 * N2) for dp
    */
    string findLCS(int n, int m, string &s1, string &s2)
    {
        int N1 = n;
        int N2 = m;

        // Initialize dp table with -1 (uncomputed states)
        vector<vector<int>> dp(N1, vector<int>(N2, -1));

        // Step 1: Get maximum LCS length
        int maxLen = recCountSubseq(N1 - 1, N2 - 1, s1, s2, dp);

        // Prepare LCS string (filled with placeholders)
        string matchCS(maxLen, 'X');

        // Start from the end of both strings
        int matchIdx = maxLen - 1;
        int idx1 = N1 - 1;
        int idx2 = N2 - 1;

        // Step 2: Trace back to reconstruct the LCS
        while (idx1 >= 0 && idx2 >= 0 && matchIdx >= 0)
        {

            if (s1[idx1] == s2[idx2])
            {
                // Characters match → add to LCS and move diagonally up-left
                matchCS[matchIdx] = s1[idx1];
                matchIdx--;
                idx1--;
                idx2--;
            }
            else
            {
                // Characters don't match → move towards the direction with larger LCS length
                if (idx1 - 1 < 0)
                    idx2--;
                else if (idx2 - 1 < 0)
                    idx1--;
                else if (dp[idx1 - 1][idx2] >= dp[idx1][idx2 - 1])
                {
                    idx1--;
                }
                else
                {
                    idx2--;
                }
            }
        }

        return matchCS;
    }

    // -----------------
    // Approach 2
    // ----------------

    /*
     Method: findLCS
     ----------------
     Finds the **Longest Common Subsequence (LCS)** string between two input strings.

     What is LCS?
     ------------
     - LCS is the longest sequence of characters that appear in the same order
       in both strings (not necessarily contiguous).
     - Example:
         word1 = "abcde"
         word2 = "ace"
         LCS   = "ace"

     Approach:
     ---------
     1. Build a DP table (n1+1 x n2+1):
        - dp[i][j] = length of LCS between word1[0..i-1] and word2[0..j-1].
        - If characters match → dp[i][j] = 1 + dp[i-1][j-1].
        - Otherwise → dp[i][j] = max(dp[i-1][j], dp[i][j-1]).

     2. After filling the table:
        - dp[n1][n2] contains the length of the LCS.

     3. Reconstruct the LCS string:
        - Start from bottom-right of the table (dp[n1][n2]).
        - If characters match → include it in result and move diagonally up-left.
        - If they do not match → move in the direction of the larger dp value (up or left).
        - Continue until reaching the top/left boundary.

     4. Return the reconstructed LCS string.

     Complexity:
     -----------
     - Time:  O(n1 * n2) for filling DP + O(n1 + n2) for reconstruction
              → overall O(n1 * n2)
     - Space: O(n1 * n2) for DP table
 */
    string findLCS(int n, int m, string &word1, string &word2)
    {
        int n1 = word1.size();
        int n2 = word2.size();

        // Step 1: Build DP table for LCS length
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; i++)
        {
            for (int j = 1; j <= n2; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int lcsqLen = dp[n1][n2];

        // Step 2: Prepare result string with placeholder size
        string matchCS(lcsqLen, 'X');

        // Step 3: Trace back to reconstruct the LCS
        int matchIdx = lcsqLen - 1;
        int idx1 = n1;
        int idx2 = n2;

        while (idx1 > 0 && idx2 > 0)
        {
            if (word1[idx1 - 1] == word2[idx2 - 1])
            {
                // Characters match → add to LCS and move diagonally
                matchCS[matchIdx] = word1[idx1 - 1];
                matchIdx--;
                idx1--;
                idx2--;
            }
            else
            {
                // Move towards the direction of greater LCS length
                if (dp[idx1 - 1][idx2] >= dp[idx1][idx2 - 1])
                {
                    idx1--;
                }
                else
                {
                    idx2--;
                }
            }
        }

        return matchCS;
    }
};

int main()
{
    return 0;
}
