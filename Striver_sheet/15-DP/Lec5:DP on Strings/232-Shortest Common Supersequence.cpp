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

1. Title: Shortest Common Supersequence | (DP - 31)

Links:
https://takeuforward.org/data-structure/shortest-common-supersequence-dp-31/
https://www.youtube.com/watch?v=xElxAuBcvsU
https://takeuforward.org/plus/dsa/problems/shortest-common-supersequence?tab=editorial
https://leetcode.com/problems/shortest-common-supersequence/description/


Problem statement:
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.

Example 1:
Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation:
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.

Example 2:
Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"


Constraints:
1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.


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
    // 1. Title: Shortest Common Supersequence | (DP - 31)
    //-------------------------------------------------------------------------------

    // -----------------
    // Approach 1
    // ----------------

    int lcsqLen(string &word1, string &word2, vector<vector<int>> &dp)
    {
        int n1 = word1.size();
        int n2 = word2.size();

        // Fill LCS DP table
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
        return dp[n1][n2];
    }

    /*
        Problem:
        --------
        Find the Shortest Common Supersequence (SCS) of two strings.
        - SCS is the shortest string that contains both str1 and str2 as subsequences.

        Example:
        --------
        str1 = "abac"
        str2 = "cab"
        SCS   = "cabac"

        Approach:
        ---------
        1. Use the Longest Common Subsequence (LCS) as the backbone:
        - Any common subsequence between str1 and str2 needs to be included only once in SCS.
        - Formula:  SCS length = n1 + n2 - LCS length.

        2. Build a DP table for LCS length:
        - dp[i][j] = length of LCS between str1[0..i-1] and str2[0..j-1].

        3. Reconstruct the actual SCS:
        - Start from dp[n1][n2] (end of both strings).
        - If characters match → put the character in SCS and move diagonally (i-1, j-1).
        - If they differ → pick the direction with the larger LCS value and add that character to SCS.
        - If one string is exhausted, append the remaining characters from the other string.

        4. Return the constructed SCS string.

        Complexity:
        -----------
        - Time:  O(n1 * n2) for DP + O(n1 + n2) for reconstruction
        - Space: O(n1 * n2) for DP table
    */
    string shortestCommonSupersequence(string str1, string str2)
    {
        int n1 = str1.size();
        int n2 = str2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        // Step 1: Compute LCS length
        int _lcsqLen = lcsqLen(str1, str2, dp);

        // Step 2: SCS length = total lengths - LCS length
        int supersqLen = n1 + n2 - _lcsqLen;

        // Prepare SCS string with placeholder size
        string supersq(supersqLen, 'X');

        // Step 3: Reconstruct SCS from bottom-right of DP
        int matchIdx = supersqLen - 1;
        int idx1 = n1;
        int idx2 = n2;

        while (idx1 > 0 && idx2 > 0)
        {
            if (str1[idx1 - 1] == str2[idx2 - 1])
            {
                // Characters match → include once and move diagonally
                supersq[matchIdx--] = str1[idx1 - 1];
                idx1--;
                idx2--;
            }
            else
            {
                // Choose direction based on larger LCS value
                if (dp[idx1 - 1][idx2] >= dp[idx1][idx2 - 1])
                {
                    supersq[matchIdx--] = str1[idx1 - 1];
                    idx1--;
                }
                else
                {
                    supersq[matchIdx--] = str2[idx2 - 1];
                    idx2--;
                }
            }
        }

        // If any characters remain in str1
        while (idx1 > 0)
        {
            supersq[matchIdx--] = str1[idx1 - 1];
            idx1--;
        }

        // If any characters remain in str2
        while (idx2 > 0)
        {
            supersq[matchIdx--] = str2[idx2 - 1];
            idx2--;
        }

        return supersq;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
