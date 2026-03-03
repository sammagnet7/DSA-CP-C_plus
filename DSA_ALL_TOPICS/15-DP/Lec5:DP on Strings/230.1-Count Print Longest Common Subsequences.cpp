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

1. Title: Counting All Longest Common Subsequences Unique by Index Paths (number of ways to form an LCS)

Links:


Problem statement:

Given two strings s and t, find the number of distinct index combinations (ways) to achieve the Longest Common Subsequence (LCS) between the two strings.

Since the number of ways can be very large, return it modulo 10^9 + 7.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

Two combinations are considered distinct if the indices used in string s or the indices used in string t are different, even if the resulting subsequence string is exactly the same.

Example 1:
Input: s = "a", t = "aa"
Output: 2
Explanation: The Longest Common Subsequence is "a" (length 1).
There are two distinct index combinations to form this LCS:
s[0] matches t[0]
s[0] matches t[1]

Example 2:
Input: s = "abc", t = "abc"
Output: 1
Explanation: The Longest Common Subsequence is "abc" (length 3).
There is exactly 1 way to form this using the entire strings.

Example 3:
Input: s = "aba", t = "bab"
Output: 2
Explanation: The max LCS length is 2. The valid index combinations are:
"ab" -> s[0], s[1] matches t[1], t[2]
"ba" -> s[1], s[2] matches t[0], t[1]

Constraints:
1 <= s.length, t.length <= 1000
s and t consist of only lowercase English letters.

INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Count Unique Longest Common Subsequences

Links:


Problem statement:
Given two strings s1 and s2, return the number of unique longest common subsequences between the two strings.

Since the answer may be very large, return it modulo 10^9 + 7.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".

A common subsequence of two strings is a subsequence that is common to both strings.

Two subsequences are considered unique if they form completely different strings. Even if the same string can be formed using different combinations of indices from s1 and s2, it should only be counted once.

Example 1:
Input: s1 = "aaa", s2 = "aa"
Output: 1
Explanation: The length of the longest common subsequence is 2.
There are mathematically 3 different ways to pick two 'a's from s1 to match with s2.
However, all of these combinations form the exact same string: "aa".
Since we only count unique strings, the answer is 1.

Example 2:
Input: s1 = "aba", s2 = "bab"
Output: 2
Explanation: The length of the longest common subsequence is 2.
The unique longest common subsequences are "ab" and "ba".

Example 3:
Input: s1 = "abcde", s2 = "xyz"
Output: 1
Explanation: There are no matching characters. The length of the longest common subsequence is 0.
The only valid sequence is the empty string "", so the answer is 1.

Constraints:
1 <= s1.length, s2.length <= 1000
s1 and s2 consist of only lowercase English letters.



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

3. Title: Print All Unique Longest Common Subsequences

Links:


Problem statement:
Given two strings s1 and s2, return a list of all unique Longest Common Subsequences (LCS) of the two strings.

The returned list must not contain any duplicate strings, and the sequences should be returned in lexicographical (alphabetical) order.

Note: A subsequence is a sequence that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

Examples

Example 1:
Input: s1 = "aba", s2 = "baa"
Output: ["aa", "ba"]
Explanation: The length of the longest common subsequence is 2. There are exactly two unique strings of length 2 that are subsequences of both s1 and s2.

Example 2:
Input: s1 = "abcaca", s2 = "baca"
Output: ["baca"]
Explanation: The length of the longest common subsequence is 4. Even though there are multiple ways to form "baca" using different indices, the actual string value is unique.

Example 3:
Input: s1 = "abc", s2 = "def"
Output: [] (or [""] depending on platform specifics)
Explanation: There are no common characters between the two strings, so the longest common subsequence has a length of 0.

Constraints:
1 <= s1.length, s2.length <= 100

s1 and s2 consist of only lowercase English letters.

Follow-up constraint warning: Because the number of valid paths can grow exponentially, constraints for this specific variation are usually kept strictly at or below 100 to prevent Time Limit Exceeded (TLE) errors during backtracking.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

//------------------------------------------------------------------------------------------------------
// 1. Title: Counting All Longest Common Subsequences Unique by Index Paths (number of ways to form an LCS)
//------------------------------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * IDEA:
     * To count distinct Longest Common Subsequence (LCS) strings, we track two things
     * simultaneously using Dynamic Programming: the maximum LCS length (`dp`), and the
     * number of unique strings that achieve that length (`count`).
     * * The magic lies in deduplication: When characters match, we strictly force the DP
     * to take the diagonal path and ignore the top/left paths. This ensures that every
     * unique string prefix gets the matching character appended exactly once, preventing
     * the "sliding match" problem where the same string is built via different grid paths.
     * * APPROACH:
     * 1. Initialize two 2D arrays: `dp` for lengths, `count` for the number of unique strings.
     * 2. Base Case: An empty string has an LCS length of 0, and exactly 1 way to form it.
     * 3. Iterate through every character combination of s1 and s2.
     * 4. Update the standard LCS length in `dp`.
     * 5. Update the `count`:
     * - CASE A (Match): Inherit ways purely from the diagonal (`count[i-1][j-1]`).
     * - CASE B (No Match): Inherit ways from Top and/or Left if they maintain the max length.
     * Apply the Inclusion-Exclusion principle if the diagonal also shares the max length,
     * to subtract overlapping double-counts.
     * 6. Return the final count (or 0 if no common characters exist).
     * * TIME COMPLEXITY:
     * O(N * M) where N is the length of s1 and M is the length of s2.
     * We iterate through a nested loop traversing the entire DP grid exactly once.
     * * SPACE COMPLEXITY:
     * O(N * M) to store the `dp` and `count` 2D vectors.
     * (Note: This can be optimized to O(M) by keeping only the previous and current rows).
     */
    int countUniqueLCS(string s1, string s2)
    {
        int n = s1.length();
        int m = s2.length();

        // Modulo to prevent integer overflow on large combinatorial results
        long long MOD = 1e9 + 7;

        // dp[i][j] stores the standard maximum LCS length for prefixes s1[0..i-1] and s2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // count[i][j] stores the number of UNIQUE strings to reach the length in dp[i][j]
        vector<vector<long long>> count(n + 1, vector<long long>(m + 1, 0));

        // --- Base Case Initialization ---
        // There is exactly 1 way to form an LCS of length 0 (by choosing nothing).
        for (int i = 0; i <= n; ++i)
            count[i][0] = 1;
        for (int j = 0; j <= m; ++j)
            count[0][j] = 1;

        // --- Fill the DP Grid ---
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                // --- 1. Standard LCS Length Calculation ---
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }

                long long ways = 0;

                // --- 2. Combinatorial String Counting ---

                // --- CASE A: Characters Match ---
                if (s1[i - 1] == s2[j - 1])
                {
                    // Greedily force the match. By ONLY taking the diagonal, we mathematically
                    // guarantee that this exact string combination is only counted once,
                    // preventing duplicate strings from alternate grid alignments.
                    ways += count[i - 1][j - 1];
                }
                // --- CASE B: Characters Do NOT Match ---
                else
                {
                    // Route 1: Did the TOP branch carry our maximum length?
                    if (dp[i][j] == dp[i - 1][j])
                    {
                        ways = (ways + count[i - 1][j]) % MOD;
                    }

                    // Route 2: Did the LEFT branch carry our maximum length?
                    if (dp[i][j] == dp[i][j - 1])
                    {
                        ways = (ways + count[i][j - 1]) % MOD;
                    }

                    // --- INCLUSION-EXCLUSION OVERLAP CHECK ---
                    // If the diagonal (the mathematical intersection of TOP and LEFT)
                    // also shares this exact max length, the strings flowing from it
                    // were just added twice (once via Top, once via Left). We must subtract it!
                    if (dp[i - 1][j - 1] == dp[i][j])
                    {
                        // We use the "+ MOD" trick because C++ modulo on negative
                        // numbers yields negative results. This wraps it safely.
                        ways = (ways - count[i - 1][j - 1] + MOD) % MOD;
                    }
                }

                // Store the accumulated valid unique strings for this state
                count[i][j] = ways;
            }
        }

        // --- Edge Case Handling ---
        // If the max length is 0, it means the strings have absolutely no characters
        // in common. We return 0 distinct valid LCS strings.
        if (dp[n][m] == 0)
        {
            return 0;
        }

        // Return the count of unique LCS strings for the full strings
        return static_cast<int>(count[n][m]);
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Count Unique Longest Common Subsequences
//-------------------------------------------------------------------------------

/**
 * Problem: Count the Number of UNIQUE Longest Common Subsequences
 * ---------------------------------------------------------------
 * Approach: Bottom-Up 2D Dynamic Programming with Inclusion-Exclusion
 * * 1. Idea of the Solution:
 * We maintain two 2D matrices simultaneously:
 * - `dp[i][j]` tracks the maximum length of the LCS for prefixes s1[0...i-1] and s2[0...j-1].
 * - `count[i][j]` tracks the number of DISTINCT LCS strings that achieve that maximum length.
 *
 *
 * * 2. Step-by-Step State Transitions:
 * - CASE A: Characters Match (s1[i-1] == s2[j-1])
 * We greedily take this match. To ensure we only count UNIQUE strings, we strictly
 * inherit the count from the diagonal (`count[i-1][j-1]`). We do NOT add paths from
 * the top or left, because doing so would count different index combinations that
 * form the exact same string.
 *
 * * - CASE B: Characters Do NOT Match (s1[i-1] != s2[j-1])
 * We look at the max lengths achieved by dropping a character from s1 (TOP)
 * or dropping a character from s2 (LEFT).
 * - If TOP is greater, we inherit the TOP's length and count.
 * - If LEFT is greater, we inherit the LEFT's length and count.
 * - If TOP == LEFT (The "Tie" Condition): We have diverging valid subsets. We must
 * combine their counts. However, to avoid double-counting distinct strings that
 * exist in both subsets, we apply the Principle of Inclusion-Exclusion:
 * |A ∪ B| = |A| + |B| - |A ∩ B|
 *
 * * 3. Complexity:
 * - Time: O(N * M) where N and M are the lengths of the two strings.
 * - Space: O(N * M) for the two DP matrices.
 */

class Solution
{
public:
    int countUniqueLCS(string s1, string s2)
    {
        int n = s1.length();
        int m = s2.length();

        // Modulo to prevent integer overflow on large combinatorial results
        long long MOD = 1e9 + 7;

        // dp stores the standard LCS length
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // count stores the number of UNIQUE strings to reach that length
        vector<vector<long long>> count(n + 1, vector<long long>(m + 1, 0));

        // Base Case Initialization:
        // There is exactly 1 way to form an LCS of length 0 (by choosing nothing).
        for (int i = 0; i <= n; ++i)
            count[i][0] = 1;
        for (int j = 0; j <= m; ++j)
            count[0][j] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                // --- 1. Standard LCS Length Calculation ---
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }

                long long ways = 0;

                // --- CASE A: Characters Match ---
                if (s1[i - 1] == s2[j - 1])
                {
                    // Greedily force the match to prevent counting duplicate strings
                    ways += count[i - 1][j - 1];
                }
                // --- CASE B: Characters Do NOT Match ---
                else
                {
                    // Route 1: TOP branch yielded a strictly longer LCS
                    if (dp[i][j] == dp[i - 1][j])
                    {
                        ways = (ways + count[i - 1][j]) % MOD;
                    }
                    // Route 2: LEFT branch yielded a strictly longer LCS
                    if (dp[i][j] == dp[i][j - 1])
                    {
                        ways = (ways + count[i][j - 1]) % MOD;
                    }

                    //
                    // INCLUSION-EXCLUSION OVERLAP CHECK:
                    // If the diagonal (the intersection of TOP and LEFT) also shares
                    // this exact max length, its distinct strings were just counted twice!
                    if (dp[i - 1][j - 1] == dp[i][j])
                    {

                        // We subtract the diagonal's count to deduplicate.
                        // We use the "+ MOD" trick because C++ modulo on negative
                        // numbers yields negative results. This wraps it safely.
                        ways = (ways - count[i - 1][j - 1] + MOD) % MOD;
                    }
                }

                // Store the accumulated valid paths
                count[i][j] = ways;
            }
        }

        if (dp[n][m] == 0)
        {
            return 0;
        }

        // Return the count of unique LCS strings for the full strings
        return static_cast<int>(count[n][m]);
    }
};

//-------------------------------------------------------------------------------
// 3. Title: Print All Unique Longest Common Subsequences
//-------------------------------------------------------------------------------
/**
 * Problem: Print All Unique Longest Common Subsequences
 * -----------------------------------------------------
 * 1. Idea:
 * - First, build the standard DP table to find the length of the LCS.
 * - Second, use a recursive DFS function to backtrack from the bottom-right
 * corner to the top-left corner.
 * - Whenever we hit a tie where dp[i-1][j] == dp[i][j-1], we branch the DFS
 * to explore both paths.
 * - We use a std::set to store the final strings so that identical strings
 * formed by different index paths are automatically deduplicated.
 * * 2. Complexity:
 * - Time: O(N * M) for the DP table + O(K * length) where K is the number
 * of valid LCS paths. In the worst-case scenario, K can be exponential,
 * making the backtracking phase O(2^(N+M)).
 * - Space: O(N * M) for the DP table + exponential space for the recursion
 * stack and storing the resulting strings.
 */

class Solution
{
private:
    // Helper function to backtrack and find all paths
    void backtrack(string &s1, string &s2, int i, int j,
                   string &current_str, vector<vector<int>> &dp, set<string> &unique_lcs)
    {

        // Base Case: We reached the end of one of the strings
        if (i == 0 || j == 0)
        {
            // Because we built the string backwards from the end, we must reverse it
            string result = current_str;
            reverse(result.begin(), result.end());
            unique_lcs.insert(result);
            return;
        }

        // Case 1: Characters Match
        if (s1[i - 1] == s2[j - 1])
        {
            current_str.push_back(s1[i - 1]);                             // Add character
            backtrack(s1, s2, i - 1, j - 1, current_str, dp, unique_lcs); // Move diagonally
            current_str.pop_back();                                       // Backtrack (remove character)
        }
        // Case 2: Characters do NOT match
        else
        {
            // If the max length came from the TOP, branch UP
            if (dp[i - 1][j] == dp[i][j])
            {
                backtrack(s1, s2, i - 1, j, current_str, dp, unique_lcs);
            }
            // If the max length came from the LEFT, branch LEFT
            // Notice this is NOT an 'else if'. If both are equal, both 'if' blocks
            // will execute, creating our required branching!
            if (dp[i][j - 1] == dp[i][j])
            {
                backtrack(s1, s2, i, j - 1, current_str, dp, unique_lcs);
            }
        }
    }

public:
    vector<string> all_longest_common_subsequences(string s1, string s2)
    {
        int n = s1.length();
        int m = s2.length();

        // Step 1: Build the standard DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Step 2: Backtrack to find all strings
        set<string> unique_lcs;
        string current_str = "";

        // Start the DFS from the bottom-right corner
        backtrack(s1, s2, n, m, current_str, dp, unique_lcs);

        // Step 3: Convert the set to a vector and return
        // The set automatically ensures strings are unique and sorted alphabetically
        return vector<string>(unique_lcs.begin(), unique_lcs.end());
    }
};

int main()
{
    return 0;
}
