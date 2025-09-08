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

1. Title: Count palindromic subsequence in given string

Links:
https://www.geeksforgeeks.org/problems/count-palindromic-subsequences/1
https://www.youtube.com/watch?v=9hsnkf0MRhQ&t=3s
https://www.youtube.com/watch?v=JbeHChnm09Q&t=16s


Problem statement:
Given a string s, you have to find the number of palindromic subsequences (need not necessarily be distinct) present in the string s.

Examples:
Input: s = "abcd"
Output: 4
Explanation: palindromic subsequence are : 'a' ,'b', 'c' ,'d'
Input: s = "aab"
Output: 4
Explanation: palindromic subsequence are : 'a', 'a', 'b', 'aa'
Input: s = "b"
Output: 1
Explanation: palindromic subsequence are : 'b'
Constraints:
1<= s.size() <=30



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Count Palindromic Subsequences with string length constraint

Links:
https://leetcode.com/problems/count-palindromic-subsequences/description/


Problem statement:
Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.

Note:
A string is palindromic if it reads the same forward and backward.
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

Examples:
    Example 1:
    Input: s = "103301"
    Output: 2
    Explanation:
    There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301".
    Two of them (both equal to "10301") are palindromic.

    Example 2:
    Input: s = "0000000"
    Output: 21
    Explanation: All 21 subsequences are "00000", which is palindromic.

    Example 3:
    Input: s = "9999900000"
    Output: 2
    Explanation: The only two palindromic subsequences are "99999" and "00000".


Constraints:
    1 <= s.length <= 104
    s consists of digits.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Count palindromic subsequence in given string
    //-------------------------------------------------------------------------------

    /*
     * Recursive (memoized) approach to count palindromic subsequences in s[i..j].
     *
     * Let f(i,j) be the number of palindromic subsequences in the substring s[i..j].
     *
     * Base cases:
     *  - if i > j : empty substring -> 0 palindromic subsequences
     *  - if i == j: single character -> 1 palindromic subsequence (the char itself)
     *
     * Recurrence:
     *  - If s[i] == s[j]:
     *       f(i,j) = f(i+1, j) + f(i, j-1) + 1
     *    Explanation: all palindromes from left and right parts plus the new
     *    subsequences formed by pairing s[i] and s[j].
     *
     *  - Else (s[i] != s[j]):
     *       f(i,j) = f(i+1, j) + f(i, j-1) - f(i+1, j-1)
     *    Explanation: include palindromes from both sides but subtract the
     *    overlap that was counted twice.
     *
     * Memoization:
     *  - dp[i][j] stores computed result for substring [i..j], initialized to -1.
     *
     * Complexity:
     *  - Time: O(n^2) distinct states (every pair i,j), each computed once.
     *  - Space: O(n^2) for memo table + O(n) recursion depth (stack).
     */
    long long countPS(const string &s)
    {
        int n = s.size();
        // dp initialized to -1 (meaning not computed)
        dp.assign(n, vector<long long>(n, -1));
        return solve(s, 0, n - 1);
    }

private:
    vector<vector<long long>> dp;

    long long solve(const string &s, int i, int j)
    {
        // i > j -> empty substring
        if (i > j)
            return 0;
        // single character -> one palindromic subsequence
        if (i == j)
            return 1;

        // return memoized result if present
        if (dp[i][j] != -1)
            return dp[i][j];

        long long ans;
        if (s[i] == s[j])
        {
            // characters match: combine left & right and add 1 for new combos
            ans = solve(s, i + 1, j) + solve(s, i, j - 1) + 1;
        }
        else
        {
            // characters differ: sum left & right then remove overlap
            ans = solve(s, i + 1, j) + solve(s, i, j - 1) - solve(s, i + 1, j - 1);
        }

        dp[i][j] = ans;
        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Count Palindromic Subsequences with string length constraint
    //-------------------------------------------------------------------------------

    
};

int main()
{
    return 0;
}
