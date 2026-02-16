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

1. Title: Wildcard Matching | (DP-34)

Links:
https://takeuforward.org/data-structure/wildcard-matching-dp-34/
https://www.youtube.com/watch?v=ZmlQ3vgAOMo
https://leetcode.com/problems/wildcard-matching/description/


Problem statement:
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Examples:
    Example 1:
    Input: s = "aa", p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".

    Example 2:
    Input: s = "aa", p = "*"
    Output: true
    Explanation: '*' matches any sequence.

    Example 3:
    Input: s = "cb", p = "?a"
    Output: false
    Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.


Constraints:
    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.


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
    // 1. Title: Wildcard Matching | (DP-34)
    //-------------------------------------------------------------------------------
    /*
        Problem:
        --------
        Given:
        - string s (input text)
        - string p (pattern with wildcards):
                '?' matches exactly one character
                '*' matches zero or more characters
        Determine if s matches p.

        Example:
        --------
        s = "abcde", p = "a*e"  → true
        s = "abc",   p = "a?d"  → false

        Idea:
        -----
        Use recursion + memoization:
        - At each step (sIndex, pIndex):
            1. If both indices < 0 → both strings are fully matched → return true.
            2. If string still has characters but pattern is exhausted → return false.
            3. If string exhausted but pattern still has characters → only valid if remaining pattern is all '*'.
            4. If characters match directly (or pattern has '?') → move diagonally (sIndex-1, pIndex-1).
            5. If pattern has '*' → two possibilities:
                - Match one char of s (consume s char → sIndex-1, pIndex).
                - Match zero char (consume '*' in pattern → sIndex, pIndex-1).
            6. Otherwise return false.

        Complexity:
        -----------
        - Time:  O(n1 * n2), where n1 = |s|, n2 = |p|
        - Space: O(n1 * n2) for memoization table
    */

    int recMatcher(int sIndex, int pIndex, string &s, string &p, vector<vector<int>> &dp)
    {
        // Case 1: both string and pattern exhausted → match
        if (sIndex == -1 && pIndex == -1)
            return 1;

        // Case 2: string has characters left, pattern is exhausted → no match
        if (sIndex >= 0 && pIndex == -1)
            return 0;

        // Case 3: string exhausted but pattern still left
        // It’s only valid if all remaining characters in pattern are '*'
        if (sIndex == -1 && pIndex >= 0)
        {
            while (pIndex >= 0)
            {
                if (p[pIndex] != '*')
                    return 0;
                pIndex--;
            }
            return 1;
        }

        // Memoization check
        if (dp[sIndex][pIndex] != -1)
            return dp[sIndex][pIndex];

        // Case 4: Characters match directly or pattern has '?'
        if (p[pIndex] == '?' || s[sIndex] == p[pIndex])
        {
            return dp[sIndex][pIndex] = recMatcher(sIndex - 1, pIndex - 1, s, p, dp);
        }

        // Case 5: Pattern has '*'
        else if (p[pIndex] == '*')
        {
            // Option 1: Match '*' with one char of s → move sIndex - 1
            int matchChar = recMatcher(sIndex - 1, pIndex, s, p, dp);

            // Option 2: Match '*' with zero chars → move pIndex - 1
            int skipChar = recMatcher(sIndex, pIndex - 1, s, p, dp);

            return dp[sIndex][pIndex] = (matchChar || skipChar);
        }

        // Case 6: No match
        return dp[sIndex][pIndex] = 0;
    }

    bool isMatch(string s, string p)
    {
        int n1 = s.size();
        int n2 = p.size();

        // Initialize DP with -1
        vector<vector<int>> dp(n1, vector<int>(n2, -1));

        // Start recursion from the last characters
        return recMatcher(n1 - 1, n2 - 1, s, p, dp);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
