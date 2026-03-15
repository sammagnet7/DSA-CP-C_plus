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

1. Title: Palindrome Partitioning - II

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

//-------------------------------------------------------------------------------
// 1. Title: Palindrome Partitioning - II
//-------------------------------------------------------------------------------

//*************************************************************************
// Approach 1 (Interval DP - top-down with 2D memo) [O(n^3)] [TLE]
//*************************************************************************

class Solution
{
public:
    /*
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
};

//*************************************************************************
// Approach 2 Front partitioning Top down [O(n^2)] [RECOMMENDED]
//*************************************************************************
class Solution
{

private:
    /**
     * @brief Recursive helper to find the minimum partitions for a suffix of the string.
     * * * * --- THE CORE IDEA: UNKNOWN COST VS. FIXED COST ---
     * Why does this avoid the O(N^3) Matrix Chain Multiplication (MCM) trap?
     * 1. MCM (Unknown Cost): Splits require recursively solving BOTH the left and right
     * halves because the cost of grouping the left half is unknown.
     * 2. Palindrome Partitioning (Fixed Cost): We anchor our search at 'start'. We ONLY
     * make a cut at 'p' if the prefix s[start...p] is ALREADY a valid palindrome.
     * Because it is a verified palindrome, we know its cost is exactly 1 piece! We don't
     * recurse on the left; we lock in that 1 piece and only recurse on the right suffix.
     * * * * --- 1D STATE DEFINITION ---
     * @param start: The current starting index. We want the min partitions for s[start...n-1].
     * @param dp: dp[start] stores the memoized result for the suffix starting at 'start'.
     * * * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2). There are N unique states for 'start'. For each state,
     * the loop runs up to N times. Finding if it's a palindrome is O(1) via the table.
     * Space Complexity : O(N) for the DP array + O(N) for the recursion call stack.
     */
    int rec(int start, string &s, vector<vector<bool>> &isPal, vector<int> &dp)
    {

        // --- BASE CASE ---
        // If we have successfully partitioned the entire string and reached the end,
        // the remaining empty string requires 0 partitions.
        if (start == s.length())
        {
            return 0;
        }

        // --- MEMOIZATION CHECK ---
        if (dp[start] != -1)
        {
            return dp[start];
        }

        int minCount = 1e9 + 7; // Initialize with a safely large number

        // Try placing a cut after every index 'p' from 'start' to the end of the string.
        for (int p = start; p < s.length(); ++p)
        {

            // CRITICAL OPTIMIZATION:
            // We ONLY make a cut if the left prefix s[start...p] is a perfect palindrome.
            if (!isPal[start][p])
            {
                continue; // Not a palindrome? Skip it.
            }

            // Cost = 1 (for the locked-in left palindrome piece)
            //        + the minimum partitions needed for the remaining right suffix.
            int countParts = 1 + rec(p + 1, s, isPal, dp);

            minCount = min(minCount, countParts);
        }

        // Cache and return the best result for this 'start' index
        return dp[start] = minCount;
    }

public:
    /**
     * @brief Computes the minimum cuts needed for a palindrome partitioning.
     * Time: O(N^2) | Space: O(N^2) due to the 2D boolean palindrome table.
     */
    int minCut(string s)
    {

        int n = s.length();

        // --- STEP 1: PRE-COMPUTE PALINDROMES (INTERVAL DP) ---
        // isPal[i][j] is true if the substring s[i...j] is a valid palindrome.
        // This gives our recursive function an instant O(1) lookup.
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        for (int i = 0; i < n; ++i)
        {
            isPal[i][i] = true;
        }

        for (int len = 2; len <= n; ++len)
        {
            for (int i = 0; i < n - len + 1; ++i)
            {

                int j = i + len - 1;

                if (s[i] == s[j])
                {
                    if (len == 2)
                    {
                        isPal[i][j] = true;
                    }
                    else
                    {
                        isPal[i][j] = isPal[i + 1][j - 1];
                    }
                }
            }
        }

        // --- STEP 2: 1D TOP-DOWN DP ---
        // dp[i] will store the minimum partitions needed for the suffix starting at 'i'
        vector<int> dp(n, -1);

        // We calculate the minimum *partitions* required.
        // A string built of 3 partitions means we made 2 cuts.
        // Therefore, we return total_partitions - 1.
        return rec(0, s, isPal, dp) - 1;
    }
};

//*************************************************************************
// Approach 3: Front partitioning Bottom up[O(n^2)]
//*************************************************************************

class Solution
{
public:
    /**
     * @brief Computes the minimum cuts needed for a palindrome partitioning using Bottom-Up Tabulation.
     * * * * --- THE CORE IDEA: UNKNOWN COST VS. FIXED COST ---
     * 1. MCM (Unknown Cost): Requires an O(N^3) loop because the left partition must be
     * recursively chopped up to find its optimal internal cost.
     * 2. Palindrome Partitioning (Fixed Cost): We ONLY cut when the prefix s[i...j]
     * is ALREADY a valid palindrome. A valid palindrome is exactly 1 solid piece.
     * We don't recurse on the left; we lock in that 1 piece and only ask our 1D DP
     * array for the pre-calculated cost of the right suffix!
     * * * * --- 1D STATE DEFINITION & TOPOLOGICAL ORDER ---
     * dp[i]: The minimum number of PARTITIONS needed for the suffix s[i...n-1].
     * Topological Order: To calculate dp[i], we need the answer to dp[j+1] (where j >= i).
     * Because j+1 is to the right of i, we MUST loop 'i' backwards from n-1 down to 0.
     * * * * --- COMPLEXITY ---
     * Time Complexity  : O(N^2). O(N^2) to build the 2D boolean palindrome table, and
     * O(N^2) to fill the 1D DP array. No recursive call stack overhead!
     * Space Complexity : O(N^2) for the boolean matrix + O(N) for the 1D DP array.
     */
    int minCut(string s)
    {

        int n = s.length();

        // Base case: A string of length 0 or 1 requires 0 cuts.
        if (n <= 1)
            return 0;

        // --- STEP 1: PRE-COMPUTE PALINDROMES (INTERVAL DP) ---
        // isPal[i][j] gives us an instant O(1) answer to "Is s[i...j] a palindrome?"
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        for (int i = 0; i < n; ++i)
        {
            isPal[i][i] = true;
        }

        for (int len = 2; len <= n; ++len)
        {
            for (int i = 0; i < n - len + 1; ++i)
            {

                int j = i + len - 1;

                if (s[i] == s[j])
                {
                    if (len == 2)
                    {
                        isPal[i][j] = true;
                    }
                    else
                    {
                        isPal[i][j] = isPal[i + 1][j - 1];
                    }
                }
            }
        }

        // --- STEP 2: 1D BOTTOM-UP DP (TABULATION) ---
        // dp[i] will store the minimum partitions needed for the suffix starting at 'i'.
        // We make the array size n + 1 so we can cleanly handle the base case.
        vector<int> dp(n + 1, 0);

        // Base Case equivalent to `if (start == s.length()) return 0;`
        // An empty string at the very end requires 0 pieces.
        dp[n] = 0;

        // Loop backwards: Solve smaller suffixes first so larger suffixes can use them.
        for (int i = n - 1; i >= 0; --i)
        {

            int minCount = 1e9 + 7; // Initialize with a safely large number

            // Try placing a cut after every index 'j' from 'i' to the end
            for (int j = i; j < n; ++j)
            {

                // We ONLY make a cut if the left prefix s[i...j] is a perfect palindrome.
                if (!isPal[i][j])
                {
                    continue; // Skip invalid prefixes
                }

                // Cost = 1 (for the locked-in left palindrome piece)
                //        + the minimum partitions needed for the remaining right suffix.
                int countParts = 1 + dp[j + 1];

                minCount = min(minCount, countParts);
            }

            // Store the best result for this 'i' index
            dp[i] = minCount;
        }

        // We calculated the minimum *partitions* required.
        // If a string is built of 3 partitions, we made exactly 2 cuts.
        return dp[0] - 1;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
