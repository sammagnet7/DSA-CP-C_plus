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

1. Title: Shortest Common Supersequence

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

//-------------------------------------------------------------------------------
// 1. Title: Shortest Common Supersequence
//-------------------------------------------------------------------------------

/**
 * Problem: 1092. Shortest Common Supersequence
 * --------------------------------------------
 * Approach: Bottom-Up DP (LCS) + Traceback
 * 1. Build the classic LCS matrix `dp` where dp[i][j] is the length of the
 * LCS of str1[0...i-1] and str2[0...j-1].
 * 2. Start tracing back from dp[N][M].
 * 3. If str1[i-1] == str2[j-1], it's part of the LCS. Add it to the result,
 * and move diagonally (i--, j--).
 * 4. If they don't match, we must pick the character that leads to the
 * higher DP value (meaning it retains the longer subsequence). Add that
 * character and move in its direction.
 * 5. Add any remaining characters from the string we haven't exhausted.
 * 6. Reverse the result since we built it backward.
 * * Complexity:
 * - Time: O(M * N) to build the table + O(M + N) to trace back.
 * - Space: O(M * N) for the DP matrix.
 */

class Solution
{
public:
    string shortestCommonSupersequence(string str1, string str2)
    {
        int n = str1.length();
        int m = str2.length();

        // 1. Build the LCS Matrix
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (str1[i - 1] == str2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // 2. Traceback to build the Supersequence
        int i = n;
        int j = m;
        string scs = "";

        while (i > 0 && j > 0)
        {
            // Case 1: Match found (part of LCS). Take it once.
            if (str1[i - 1] == str2[j - 1])
            {
                scs += str1[i - 1];
                i--;
                j--;
            }
            // Case 2: Mismatch. Trace back in the direction of the larger value.
            // If moving UP gave a better/equal result, we take the character from str1
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                scs += str1[i - 1];
                i--;
            }
            // If moving LEFT gave a better result, we take the character from str2
            else
            {
                scs += str2[j - 1];
                j--;
            }
        }

        // 3. Collect any remaining characters
        while (i > 0)
        {
            scs += str1[i - 1];
            i--;
        }
        while (j > 0)
        {
            scs += str2[j - 1];
            j--;
        }

        // 4. Reverse the string because we traced backward from the end
        reverse(scs.begin(), scs.end());

        return scs;
    }
};

int main()
{
    return 0;
}
