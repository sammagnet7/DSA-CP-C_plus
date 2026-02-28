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

1. Title: Count All Longest Common Subsequences

Links:



Problem statement:
Given two strings s1 and s2, find the length of their Longest Common Subsequence (LCS) and determine the total number of distinct subsequences (by index) that achieve this maximum length.

Since the total number of longest common subsequences can be incredibly large, return the count modulo $10^9 + 7$.

Note: A subsequence is a sequence that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

Examples

Example 1:
Input: s1 = "abc", s2 = "acb"
Output: 2
Explanation: The length of the LCS is 2. There are exactly 2 different subsequences that achieve this length: "ac" and "ab".

Example 2:
Input: s1 = "bd", s2 = "abcd"
Output: 1
Explanation: The length of the LCS is 2. There is only 1 subsequence that achieves this length: "bd".

Example 3:
Input: s1 = "aba", s2 = "bba"
Output: 3
Explanation: The length of the LCS is 2. The subsequences of length 2 are formed by matching different indices:
    s1[1], s1[2] ("ba") with s2[0], s2[2] ("ba")
    s1[1], s1[2] ("ba") with s2[1], s2[2] ("ba")
    s1[0], s1[2] ("aa") is not valid since "aa" isn't in s2. Wait, no, the third one is actually "ba" using different character indices! (There are 3 distinct paths in the DP table to form the LCS).

Constraints:
1 <= s1.length, s2.length <= 1000
s1 and s2 consist of lowercase English letters.



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Print All Longest Common Subsequences

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

//-------------------------------------------------------------------------------
// 1. Title: Count All Longest Common Subsequences
//-------------------------------------------------------------------------------

/**
 * Problem: Count All Longest Common Subsequences (By Index)
 * ---------------------------------------------------------
 * 1. The Core Idea:
 * We use two matrices:
 * - 'dp' simply calculates the standard LCS length.
 * - 'count' tracks the number of distinct ways (paths) to achieve that exact max length.
 *
 *
 * * 2. DP Transitions for the 'count' Matrix:
 *
 * - CASE A : Characters Match (s1[i-1] == s2[j-1])
 * Since the sequence strictly extends by 1, all valid paths from the diagonal
 * simply append this new character. We inherit the exact number of ways from the diagonal.
 * => count[i][j] = count[i-1][j-1]
 *
 * * - CASE B : Characters Do NOT Match (s1[i-1] != s2[j-1])
 * We look at the max lengths from the TOP cell and the LEFT cell.
 *
 * - If TOP is strictly greater, all max paths come from the TOP.
 * => count[i][j] = count[i-1][j]
 *
 * - If LEFT is strictly greater, all max paths come from the LEFT.
 * => count[i][j] = count[i][j-1]
 *
 * * 3. The "TIE" Condition & Inclusion-Exclusion (TOP == LEFT):
 * If TOP and LEFT provide the exact same max length, we have diverging paths.
 * We must add their counts together. However, we might double-count paths that
 * originated from the DIAGONAL (i-1, j-1) and branched out to both TOP and LEFT.
 *
 * * The "Apples and Oranges" Rule for Double-Counting:
 * We ONLY subtract the diagonal's count if its length is EXACTLY EQUAL to our
 * current max length. If the diagonal's length is smaller, it means TOP and LEFT
 * found completely independent matches on their edges. They don't share overlapping
 * paths of our current max length, so we do not subtract.
 *
 * => IF dp[i-1][j-1] == dp[i][j], THEN subtract count[i-1][j-1]
 *
 *
 * * 4. The Modulo Fix (+ MOD):
 * When subtracting the diagonal's count, the result can become negative if the
 * sum of TOP and LEFT recently wrapped around the modulo limit. In C++, a negative
 * remainder stays negative. We explicitly add MOD before the final modulo operation
 * to safely wrap it back into the positive range.
 *
 *
 * * Complexity:
 * - Time: O(N * M)
 * - Space: O(N * M)
 */

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int countAllLCS(string s1, string s2)
    {
        int n = s1.length();
        int m = s2.length();
        long long MOD = 1e9 + 7;

        // dp stores the standard LCS length
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // count stores the number of valid paths to reach that length
        // Base case: 1 way to form an empty string
        vector<vector<long long>> count(n + 1, vector<long long>(m + 1, 1));

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {

                // --- Standard LCS length update ---
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;

                    // Count logic: Inherit ways from diagonal
                    count[i][j] = count[i - 1][j - 1];
                }
                else
                {
                    // --- Check lengths to route the count updates ---
                    if (dp[i - 1][j] > dp[i][j - 1])
                    {
                        dp[i][j] = dp[i - 1][j];

                        // Count logic: Inherit ways from TOP
                        count[i][j] = count[i - 1][j];
                    }
                    else if (dp[i - 1][j] < dp[i][j - 1])
                    {
                        dp[i][j] = dp[i][j - 1];

                        // Count logic: Inherit ways from LEFT
                        count[i][j] = count[i][j - 1];
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j];

                        // Count logic: TIE condition! Add both paths.
                        count[i][j] = (count[i - 1][j] + count[i][j - 1]) % MOD;

                        // Count logic: Inclusion-Exclusion overlapping check
                        if (dp[i - 1][j - 1] == dp[i][j])
                        {
                            // Apply the '+ MOD' trick to prevent negative remainders
                            count[i][j] = (count[i][j] - count[i - 1][j - 1] + MOD) % MOD;
                        }
                    }
                }
            }
        }

        return static_cast<int>(count[n][m]);
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Print All Longest Common Subsequences
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

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

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
