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

1. Title: Palindrome Partitioning - II | Front Partition : DP 53

Links:
https://takeuforward.org/data-structure/palindrome-partitioning-ii-front-partition-dp-53/
https://www.youtube.com/watch?v=_H8V5hJUGd0
https://takeuforward.org/plus/dsa/problems/palindrome-partitioning-ii-?tab=editorial
https://leetcode.com/problems/palindrome-partitioning-ii/


Problem statement:
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Examples:
    Example 1:
    Input: s = "aab"
    Output: 1
    Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

    Example 2:
    Input: s = "a"
    Output: 0

    Example 3:
    Input: s = "ab"
    Output: 1


Constraints:
1 <= s.length <= 2000
s consists of lowercase English letters only.



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Palindrome Partitioning - II | Front Partition : DP 53
    //-------------------------------------------------------------------------------

    /**************************************************************************
     * Approach 1 (Interval DP - top-down with 2D memo)
     *
     * Idea / Intuition:
     *  - Define dp[i][j] = minimum number of cuts needed so that every
     *    substring in s[i..j] is a palindrome.
     *  - If s[i..j] is already a palindrome -> 0 cuts.
     *  - Otherwise try every split k (i <= k < j) and combine:
     *        dp[i][j] = min_{k} { 1 + dp[i][k] + dp[k+1][j] }
     *  - Use memoization to avoid recomputation of the same (i,j) interval.
     *
     * Data structures used:
     *  - vector<vector<int>> dp : 2D memo table sized n x n, stores -1 or answer.
     *
     * Time complexity:
     *  - Number of states = O(n^2) (all pairs (i,j)).
     *  - For each state we try O(n) split positions k.
     *  - Each state also checks whether s[i..j] is a palindrome once (isPal),
     *    which costs O(length) = O(n) in worst case.
     *  => Overall worst-case time = O(n^3). (pal check is done once per state,
     *     so it contributes within the same O(n^3) bound.)
     *
     * Space complexity:
     *  - O(n^2) for dp table + recursion stack O(n).
     **************************************************************************/

    /* O(n) palindrome check for substring s[i..j] */
    bool isPal(string &s, int i, int j)
    {
        while (i <= j)
        {
            if (s[i++] != s[j--])
            {
                return false;
            }
        }
        return true;
    }

    /* Top-down DP over intervals (i..j) */
    int recPartCount(int i, int j, string &s, vector<vector<int>> &dp)
    {
        // Base: empty or single char -> no cut needed
        if (i >= j)
        {
            return 0;
        }

        // Return memoized result if present
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // If whole substring is palindrome -> 0 cuts
        if (isPal(s, i, j))
        {
            return dp[i][j] = 0;
        }

        int minCuts = INT_MAX;

        // Try every possible split point k between i and j-1
        for (int k = i; k < j; k++)
        {
            // 1 cut for splitting at k + best for left + best for right
            int count = 1 + recPartCount(i, k, s, dp) + recPartCount(k + 1, j, s, dp);
            minCuts = min(minCuts, count);
        }

        return dp[i][j] = minCuts;
    }

    /* Entry for Approach 1 */
    int minCut(string s)
    {
        int n = s.size();

        // dp[i][j] stores min cuts for substring s[i..j], -1 = unknown
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // Solve for full string
        return recPartCount(0, n - 1, s, dp);
    }

    /**************************************************************************
     * Approach 2 (Start-index DP + palindrome memoization)
     *
     * Idea / Intuition:
     *  - Let dp[start] = minimum cuts needed for substring s[start..n-1].
     *  - We iterate end = start..n-1; if s[start..end] is palindrome, we can
     *    make 1 cut at end (conceptually) and add dp[end+1].
     *    dp[start] = min_{end in [start..n-1] and s[start..end] is pal} { 1 + dp[end+1] }
     *  - Final answer = dp[0] - 1 (we count partitions; cuts = partitions - 1).
     *  - To avoid repeated O(n) palindrome checks we memoize pal[i][j].
     *
     * Data structures used:
     *  - vector<int> dp : dp[start] minimal cuts from start to end.
     *  - vector<vector<int>> pal : memo table for palindrome checks; -1 = unknown,
     *      pal[i][j] = 1/0 for palindrome true/false.
     *
     * Time complexity:
     *  - If palindrome test pal[i][j] is O(1) (precomputed), then:
     *      - For each start we try O(n) ends => O(n^2) total.
     *  - With the lazy palindrome routine implemented here (while loop cached in pal),
     *    each pal[i][j] is computed at most once, but each computation costs O(length).
     *    The naive bound for computing all pal pairs is O(n^3) in worst case.
     *  - Practically, with a DP precomputation of pal table (expand-around-center or DP),
     *    you get O(n^2) time overall for the algorithm.
     *
     * Space complexity:
     *  - O(n) for dp + O(n^2) for palindrome table.
     **************************************************************************/

    /* Palindrome check with memoization in `pal` table */
    bool isPal(string &s, int i, int j, vector<vector<int>> &pal)
    {
        if (i >= j)
            return true; // single char or empty -> palindrome
        if (pal[i][j] != -1)
            return pal[i][j]; // cached result

        // Compute and cache result (naive O(length) check)
        int ii = i, jj = j;
        while (ii <= jj)
        {
            if (s[ii++] != s[jj--])
            {
                pal[i][j] = 0;
                return false;
            }
        }
        pal[i][j] = 1;
        return true;
    }

    /* DP over start index: dp[start] = min cuts from start..n-1 */
    int recPartCount(int start, int n, string &s, vector<int> &dp, vector<vector<int>> &pal)
    {
        // If start reached end -> no more cuts needed (no characters left)
        if (start >= n)
        {
            return 0;
        }

        // Return memoized result if present
        if (dp[start] != -1)
        {
            return dp[start];
        }

        int minCuts = INT_MAX;

        // Try each endpoint k for the palindrome s[start..k]
        for (int k = start; k < n; k++)
        {
            if (isPal(s, start, k, pal))
            {
                // Make one partition here and solve remainder
                int count = 1 + recPartCount(k + 1, n, s, dp, pal);
                minCuts = min(minCuts, count);
            }
        }

        return dp[start] = minCuts;
    }

    /* Entry for Approach 2
     * Note: this returns recPartCount(0,n,s,dp,pal)-1 because dp counts partitions,
     * and the number of cuts is partitions - 1.
     */
    int minCut(string s)
    {
        int n = s.size();

        vector<int> dp(n, -1);                          // dp[start] memo
        vector<vector<int>> pal(n, vector<int>(n, -1)); // pal[i][j] memo for palindrome

        // compute minimal partitions then convert to cuts
        return recPartCount(0, n, s, dp, pal) - 1;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
