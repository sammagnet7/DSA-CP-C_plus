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

1. Title: Longest Palindromic Substring

Links:
https://www.youtube.com/watch?v=tGAMyZxlwuA
https://leetcode.com/problems/longest-palindromic-substring/description/


Problem statement:
Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Constraints:
    1 <= s.length <= 1000
    s consist of only digits and English letters.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Count Palindromic Substrings

Links:
https://www.youtube.com/watch?v=tGAMyZxlwuA
https://leetcode.com/problems/palindromic-substrings/description/


Problem statement:
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.
A substring is a contiguous sequence of characters within the string.


Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".


Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Longest Palindromic Substring
//-------------------------------------------------------------------------------

// -------------------------------------
// Approach 1: Extra space [Interval DP]
// -------------------------------------
/**
 * Problem: 1. Longest Palindromic Substring
 * -----------------------------------------
 * Approach 1: Bottom-Up Interval Dynamic Programming

 * * 1. Idea of the Solution:
 * A substring is a palindrome if its outer boundary characters match AND the
 * substring strictly inside those boundaries is also a palindrome.
 * We can build a 2D boolean matrix where dp[i][j] is 'true' if the substring
 * from index 'i' to 'j' is a perfect palindrome.

 * * 2. Step-by-Step Approach:
 * - Step 1 (Initialization): Create an N x N boolean matrix initialized to false.
 * - Step 2 (Base Case): Every individual character is a palindrome of length 1.
 * Set dp[i][i] = true for all i.

 * - Step 3 (Matrix Filling): Loop by the 'length' of the interval (from 2 to N).
 * Then, slide a starting pointer 'i' across the string.

 * - Step 4 (State Transition): If the outer characters s[i] and s[j] match, we
 * check if the length is 2 (base case for even palindromes) OR if the inner
 * substring dp[i+1][j-1] is true. If so, dp[i][j] = true.

 * - Step 5 (Tracking): Update 'maxLen' and 'strStartIdx' whenever a longer
 * palindrome is verified.

 * * 3. Pros and Cons:
 * - PROS: Highly systemic and easy to reason about mathematically. This exact
 * matrix can be reused to solve harder variations like "Palindrome Partitioning".

 * - CONS: Requires O(N^2) memory. For a string of length 10,000, this requires
 * a massive matrix that will likely trigger a Memory Limit Exceeded (MLE) error.

 * * 4. Complexity:
 * - Time: O(N^2) - We evaluate every possible start and end index exactly once.
 * - Space: O(N^2) - To store the N x N boolean DP matrix.
 */

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int N = s.length();
        if (N == 0)
            return "";

        vector<vector<bool>> dp(N, vector<bool>(N, false));

        // Base case: length 1 substrings
        for (int i = 0; i < N; ++i)
        {
            dp[i][i] = true;
        }

        int maxLen = 0;
        int strStartIdx = -1;

        // Loop by length, then by start index
        for (int len = 2; len <= N; ++len)
        {
            for (int i = 0; i + len - 1 < N; ++i)
            {

                int j = i + len - 1;

                // If outer characters match
                if (s[i] == s[j])
                {

                    // It is a valid palindrome if it's length 2 OR the inner string is valid
                    if (len == 2 || dp[i + 1][j - 1])
                    {
                        dp[i][j] = true;

                        // Track the longest one found
                        if (len > maxLen)
                        {
                            maxLen = len;
                            strStartIdx = i;
                        }
                    }
                }
            }
        }

        // If no palindrome of length > 1 was found, return the first character
        if (maxLen == 0)
        {
            return string(1, s[0]);
        }
        else
        {
            return s.substr(strStartIdx, maxLen);
        }
    }

    // -------------------------------------
    // Approach 2: Extra space [Recursive DP]
    // -------------------------------------

    /**
     * Problem 1: Longest Palindromic Substring
     * -----------------------------------------
     * Approach: Top-Down Recursive DP with 'isPal' Check
     * * 1. Idea of the Solution:
     * We create a recursive function `isPal(l, r)` that checks if a substring
     * is a palindrome.
     * - Base Case: If the pointers cross or meet (l >= r), it's a valid center, return true.
     * - Transition: If s[l] == s[r], the answer depends purely on the inner substring isPal(l+1, r-1).
     * We cache these boolean results in a 2D memoization table to avoid redundant work.
     * * 2. Step-by-Step Approach:
     * - Step 1: Initialize an N x N memoization table with -1 (uncomputed).
     * - Step 2: Iterate through all possible start indices 'i' and end indices 'j'.
     * - Step 3: For each interval, call the recursive `isPal(i, j)` function.
     * - Step 4: If `isPal` returns true AND the length `(j - i + 1)` is greater
     * than our current max, update the max length and starting index.
     * * 3. Complexity:
     * - Time: O(N^2) - There are N^2 possible (i, j) pairs. Because of memoization,
     * the recursive function computes each state exactly once.
     * - Space: O(N^2) - For the N x N memoization table + O(N) for the recursion stack depth.
     */

    // Helper function to check if s[l...r] is a palindrome using Recursion + Memoization
    bool isPal(string &s, int l, int r, vector<vector<int>> &memo)
    {

        // Base Case: Pointers met in the middle (length 1) or crossed (empty inner string)
        if (l >= r)
        {
            return true;
        }

        // Memoization Check: If already computed, return the cached result
        if (memo[l][r] != -1)
        {
            return memo[l][r];
        }

        // Transition: Outer characters must match AND the inner substring must be a palindrome
        if (s[l] == s[r])
        {
            return memo[l][r] = isPal(s, l + 1, r - 1, memo);
        }

        // If outer characters do not match, it's definitively false
        return memo[l][r] = 0; // 0 represents false
    }

    string longestPalindrome(string s)
    {
        int N = s.length();
        if (N == 0)
            return "";

        // Memoization table initialized to -1 (meaning "uncomputed")
        // We use 'int' instead of 'bool' because we need 3 states: -1 (unknown), 0 (false), 1 (true)
        vector<vector<int>> memo(N, vector<int>(N, -1));

        int maxLen = 0;
        int strStartIdx = 0;

        // Check every possible substring interval
        for (int i = 0; i < N; ++i)
        {
            for (int j = i; j < N; ++j)
            {

                // If the current interval is a palindrome
                if (isPal(s, i, j, memo))
                {

                    int currentLen = j - i + 1;

                    // Update global max if it's the longest we've seen
                    if (currentLen > maxLen)
                    {
                        maxLen = currentLen;
                        strStartIdx = i;
                    }
                }
            }
        }

        // Extract and return the final longest substring
        return s.substr(strStartIdx, maxLen);
    }

    // -----------------------------
    // Approach 3: Optimal (Skipped)
    // -----------------------------
    /**
     * Problem: 1. Longest Palindromic Substring
     * -----------------------------------------
     * Approach 2: Expand Around Center (Two Pointers)
     * * 1. Idea of the Solution:
     * Palindromes are perfectly mirrored around their center. Instead of checking
     * boundaries and shrinking inward (which requires memory of inner states), we
     * can pick a "center" and expand outward as long as the mirror holds!
     * A center can be a single character (for odd-length palindromes like "aba")
     * or the gap between two characters (for even-length palindromes like "abba").
     * * 2. Step-by-Step Approach:
     * - Step 1: Iterate through every character in the string, treating it as a pivot.
     * - Step 2 (Odd Expansion): Expand outwards with left=i, right=i.
     * - Step 3 (Even Expansion): Expand outwards with left=i, right=i+1.
     * - Step 4 (Expansion Logic): While s[left] == s[right] and we are inside the
     * string bounds, move left inward (-) and right outward (+).
     * - Step 5 (Tracking): Keep track of the maximum length found. When a new max
     * is found, calculate its starting index mathematically using the pivot 'i'.
     * * 3. Pros and Cons:
     * - PROS: Uses strictly O(1) space. It is also significantly faster in practice
     * because the while loop breaks instantly upon the first mismatch, whereas
     * DP matrix allocation adds massive overhead.
     * - CONS: The math to calculate the `start` index (i - (len - 1) / 2) can be
     * slightly unintuitive to write out during a high-pressure interview.
     * * 4. Complexity:
     * - Time: O(N^2) - In the worst case (a string of all identical characters like
     * "aaaaa"), expanding from the center takes linear time for every single index.
     * - Space: O(1) - We only store a few integer variables (pointers and lengths).
     */

    string longestPalindrome(string s)
    {
        if (s.empty())
            return "";

        int start = 0;
        int maxLen = 0;

        for (int i = 0; i < s.length(); i++)
        {

            // Check for odd-length palindrome (center is character 'i')
            int len1 = expandAroundCenter(s, i, i);

            // Check for even-length palindrome (center is between 'i' and 'i+1')
            int len2 = expandAroundCenter(s, i, i + 1);

            int currentMax = max(len1, len2);

            if (currentMax > maxLen)
            {
                maxLen = currentMax;

                // Mathematically derive the starting index of the substring
                // based on the pivot 'i' and the total length.
                start = i - (currentMax - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }

private:
    int expandAroundCenter(const string &s, int left, int right)
    {

        // Expand outward as long as characters match and bounds are safe
        while (left >= 0 && right < s.length() && s[left] == s[right])
        {
            left--;
            right++;
        }

        // At the point of exiting the loop, left and right point to the first MISMATCH.
        // The actual length of the valid palindrome inside those bounds is:
        // (right - 1) - (left + 1) + 1  ==>  right - left - 1
        return right - left - 1;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Count Palindromic Substrings
//-------------------------------------------------------------------------------
// -------------------------------------
// Approach 1: Extra space [Interval DP]
// -------------------------------------
/**
 * Problem 2: Palindromic Substrings
 * ------------------------------------
 * Approach: Bottom-Up Interval DP
 * 1. Build an N x N boolean matrix where dp[i][j] is true if s[i...j] is a palindrome.
 * 2. Every single time we set a cell to true, we increment our counter.
 * * Complexity:
 * - Time: O(N^2) to fill the matrix.
 * - Space: O(N^2) to store the matrix. (This is why Expand Around Center is preferred!)
 */

class Solution
{
public:
    int countSubstrings(string s)
    {
        int N = s.length();
        if (N == 0)
            return 0;

        vector<vector<bool>> dp(N, vector<bool>(N, false));
        int totalCount = 0;

        // Base case: length 1 substrings
        for (int i = 0; i < N; ++i)
        {
            dp[i][i] = true;
            totalCount++; // A single character is a palindrome
        }

        // Loop by length, then by start index
        for (int len = 2; len <= N; ++len)
        {
            for (int i = 0; i + len - 1 < N; ++i)
            {

                int j = i + len - 1;

                // If outer characters match...
                if (s[i] == s[j])
                {
                    // ...and it's length 2 OR the inner string is a palindrome
                    if (len == 2 || dp[i + 1][j - 1])
                    {
                        dp[i][j] = true;
                        totalCount++; // We found a new palindromic substring!
                    }
                }
            }
        }

        return totalCount;
    }

    // -------------------------------------
    // Approach 2: Optimal (Skipped)
    // -------------------------------------
    /**
     * Problem 2: Palindromic Substrings
     * ------------------------------------
     * Approach: Expand Around Center
     * 1. Treat every character (and every gap between characters) as a center pivot.
     * 2. Expand outwards. Every time s[left] == s[right], it means we just formed
     * a valid palindrome, so we increment our count.
     * 3. Stop expanding for that center the moment the characters don't match or
     * we hit the string boundaries.
     * * Complexity:
     * - Time: O(N^2) in the worst case (e.g., "aaaaa").
     * - Space: O(1) strictly, as we only use a few tracking integer variables.
     */

    int countSubstrings(string s)
    {
        int totalPalindromes = 0;

        for (int i = 0; i < s.length(); ++i)
        {
            // Count odd-length palindromes (center is at character 'i')
            totalPalindromes += countAroundCenter(s, i, i);

            // Count even-length palindromes (center is between 'i' and 'i+1')
            totalPalindromes += countAroundCenter(s, i, i + 1);
        }

        return totalPalindromes;
    }

    int countAroundCenter(const string &s, int left, int right)
    {
        int count = 0;

        // Keep expanding as long as bounds are safe and characters match
        while (left >= 0 && right < s.length() && s[left] == s[right])
        {
            count++; // We found a valid palindrome!
            left--;  // Expand left
            right++; // Expand right
        }

        return count;
    }
};

int main()
{
    return 0;
}
