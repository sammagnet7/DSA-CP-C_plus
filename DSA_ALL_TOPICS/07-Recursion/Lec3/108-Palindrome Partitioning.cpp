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

using namespace std;

/*

Palindrome Partitioning:

https://takeuforward.org/data-structure/palindrome-partitioning/
https://www.youtube.com/watch?v=WBgsABoClE0&t=1s
https://www.youtube.com/watch?v=jHR7KUAAEzw
https://leetcode.com/problems/palindrome-partitioning/description/


Problem statement:
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Examples:

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]


INPUT::::::


OUTPUT::::::

*/

// ---------------------------------------------
// Palindrome Partitioning:
// ---------------------------------------------

// ---------------------------------------------
// Approach 1 : without DP [sub optimal]
// ---------------------------------------------
class Solution
{
private:
    /**
     * @brief Checks if a substring is a palindrome IN-PLACE without allocating new memory.
     * * @details
     * By passing the original string by const reference and using two pointers (l and r),
     * we avoid the expensive overhead of creating a new string via .substr() just to check it.
     */
    bool isPal(const string &s, int l, int r)
    {
        while (l < r)
        {
            if (s[l] != s[r])
            {
                return false;
            }
            l++;
            r--;
        }
        return true;
    }

    /**
     * @brief Core Backtracking DFS to explore all valid palindrome partitions.
     * * @details
     * --- THE PARADIGM ---
     * This uses the standard Backtracking template:
     * 1. CHOOSE: Identify a valid palindromic prefix and add it to the current path.
     * 2. EXPLORE: Recursively partition the remaining suffix of the string.
     * 3. UN-CHOOSE: Pop the prefix off the path so the loop can try the next, longer prefix.
     * * --- STATE DEFINITION ---
     * @param idx: The starting index of the current suffix we are trying to partition.
     * @param str: The original string (passed by const reference to avoid copies).
     * @param partitions: Our current active "backpack" holding a sequence of valid palindromes.
     * @param allParts: The master list storing all successfully completed partitions.
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N * 2^N). In the absolute worst case (e.g., "aaaaa"), there are
     * 2^(N-1) possible partitions. For each successful partition, we spend O(N) time copying
     * the strings into the final result array.
     * Space Complexity : O(N) auxiliary space for the recursion call stack and the
     * 'partitions' vector. (Excluding the space required for the output array).
     */
    void rec(int idx, const string &str, vector<string> &partitions, vector<vector<string>> &allParts, int n)
    {

        // --- BASE CASE ---
        // If our starting index has reached the length of the string, it means we have
        // successfully partitioned the entire string into valid palindromes!
        if (idx == n)
        {
            allParts.emplace_back(partitions);
            return;
        }

        // Try placing the right boundary 'r' at every position from 'idx' to the end
        for (int r = idx; r < n; ++r)
        {

            // OPTIMIZATION: Check if it's a palindrome first using indices!
            if (!isPal(str, idx, r))
            {
                continue; // Skip this cut if it doesn't form a palindrome
            }

            // --- 1. CHOOSE ---
            // Now that we mathematically know it's a palindrome, it is finally safe
            // to spend the memory to extract the substring.
            string curPartStr = str.substr(idx, (r - idx + 1));
            partitions.push_back(curPartStr);

            // --- 2. EXPLORE ---
            // Recursively evaluate the rest of the string starting from r + 1
            rec(r + 1, str, partitions, allParts, n);

            // --- 3. UN-CHOOSE ---
            // Remove the substring we just added so the loop can advance 'r' and
            // try a longer palindromic prefix on the next iteration.
            partitions.pop_back();
        }
    }

public:
    /**
     * @brief Generates all possible palindrome partitionings of a string.
     */
    vector<vector<string>> partition(string s)
    {

        vector<string> partitions;
        vector<vector<string>> allParts;

        // Kick off the backtracking starting at index 0
        rec(0, s, partitions, allParts, s.length());

        return allParts;
    }
};

// ---------------------------------------------
// Approach 2 : using DP [OPTIMAL]
// ---------------------------------------------

class Solution
{
private:
    /**
     * @brief Core Backtracking DFS to explore all valid palindrome partitions.
     * * @details
     * --- THE PARADIGM ---
     * 1. CHOOSE: Identify a valid palindromic prefix using our O(1) DP table lookup.
     * 2. EXPLORE: Recursively partition the remaining suffix of the string.
     * 3. UN-CHOOSE: Pop the prefix off the path to try the next, longer prefix.
     */
    void rec(int idx, const string &str, vector<string> &partitions, vector<vector<string>> &allParts, vector<vector<bool>> &dp, int n)
    {

        // --- BASE CASE ---
        if (idx == n)
        {
            allParts.emplace_back(partitions);
            return;
        }

        // Try placing the right boundary 'r' at every position from 'idx' to the end
        for (int r = idx; r < n; ++r)
        {

            // --- O(1) OPTIMIZATION ---
            // Instant lookup instead of a manual O(N) string check!
            if (!dp[idx][r])
            {
                continue;
            }

            // --- 1. CHOOSE ---
            string curPartStr = str.substr(idx, (r - idx + 1));
            partitions.push_back(curPartStr);

            // --- 2. EXPLORE ---
            rec(r + 1, str, partitions, allParts, dp, n);

            // --- 3. UN-CHOOSE ---
            partitions.pop_back();
        }
    }

public:
    /**
     * @brief Generates all possible palindrome partitionings of a string.
     * * @details
     * --- WHY THIS APPROACH IS SUPERIOR (DP + BACKTRACKING) ---
     * 1. The Bottleneck: In pure backtracking, checking if a substring is a
     * palindrome takes O(N) time. Since the recursive tree explores up to
     * O(2^N) paths, doing an O(N) check at every single branch is massively redundant.
     * 2. The Solution: We pre-compute all palindromes upfront using an O(N^2) Interval DP table.
     * Now, when the exponential backtracking tree asks "Is this a palindrome?",
     * it gets an instant O(1) answer from dp[idx][r].
     * 3. The Trade-off: We happily trade a tiny bit of space (O(N^2) for the boolean matrix)
     * to completely remove the O(N) string-checking multiplier from our O(2^N) recursion tree.
     * * --- COMPLEXITY ---
     * Time: O(N^2) to build the DP table + O(N * 2^N) for backtracking and substring copying.
     * Space: O(N^2) for the DP table + O(N) for the recursion stack.
     */
    vector<vector<string>> partition(string s)
    {

        int n = s.length();

        vector<string> partitions;
        vector<vector<string>> allParts;

        // --- PRE-COMPUTE PALINDROMES (INTERVAL DP) ---
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // Base Case 1: All single characters are palindromes
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = true;
        }

        // Evaluate substrings by length (from length 2 up to the full string length)
        for (int len = 2; len <= n; ++len)
        {
            for (int i = 0; i < n - len + 1; ++i)
            {

                int j = i + len - 1;

                // A substring s[i...j] is a palindrome ONLY IF:
                // 1. The outer characters match (s[i] == s[j])
                // 2. AND the inner substring (dp[i+1][j-1]) is also a palindrome.
                dp[i][j] = (s[i] == s[j]) ? (len == 2 ? true : dp[i + 1][j - 1]) : false;
            }
        }

        // Kick off the backtracking armed with our O(1) lookup table
        rec(0, s, partitions, allParts, dp, n);

        return allParts;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
