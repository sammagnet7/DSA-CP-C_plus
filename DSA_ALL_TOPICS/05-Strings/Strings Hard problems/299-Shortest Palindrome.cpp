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

1. Title: Shortest Palindrome

Links:
https://takeuforward.org/plus/dsa/problems/shortest-palindrome?tab=editorial
https://leetcode.com/problems/shortest-palindrome/description/


Problem statement:
You are given a string `s`. You can convert `s` to a palindrome by adding characters in front of it.

Return the shortest palindrome you can find by performing this transformation.

Examples:
    Example 1:
    Input: s = "aacecaaa"
    Output: "aaacecaaa"

    Example 2:
    Input: s = "abcd"
    Output: "dcbabcd"


Constraints:
0 <= s.length <= 5 * 10^4
s consists of lowercase English letters only.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Shortest Palindrome
//-------------------------------------------------------------------------------

// ---------------------------------------
// Approach 1: String concatenation + KMP
// ---------------------------------------

class Solution
{
public:
    /**
     * @brief Finds the shortest palindrome by prepending characters.
     * * * * * * 🧠 INTUITION (The KMP Mirror Trick):
     * To add the minimum characters to the front, we must find the Longest
     * Palindromic Prefix (LPP) of the original string. The characters remaining
     * after this prefix are the ones we need to reverse and prepend.
     * * We can find the LPP by concatenating: `s + "#" + reverse(s)`.
     * By building a KMP LPS array on this combined string, the final value
     * `LPS[m - 1]` will give us the exact length of the longest prefix of `s`
     * that matches a suffix of `reverse(s)` (which is a palindrome!).
     * * * * * * 🛡️ WHY THE '#' SEPARATOR?:
     * If s = "aaaa", reverse(s) = "aaaa". Without the separator, combined = "aaaaaaaa".
     * The LPS of the last character would be 7, which is larger than the original
     * string! The "#" acts as a hard boundary to prevent overlapping matches.
     * * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: \mathcal{O}(N). Reversing takes \mathcal{O}(N), KMP LPS takes \mathcal{O}(N).
     * - Space Complexity: \mathcal{O}(N) to store the combined string and the LPS array.
     */
    string shortestPalindrome(string s)
    {

        int n = s.length();
        if (n <= 1)
            return s;

        // 1. Create the reverse of the string
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());

        // 2. Create the mirrored string with a strict boundary
        string combined = s + "#" + rev_s;
        int m = combined.length();

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY (Standard KMP Template)
        // =========================================================
        vector<int> LPS(m, 0);
        int len = 0; // Length Pointer
        int i = 1;   // Right Index

        while (i < m)
        {
            if (combined[len] == combined[i])
            {
                ++len;
                LPS[i] = len;
                ++i;
            }
            else
            {
                if (len != 0)
                {
                    len = LPS[len - 1]; // Safe fallback
                }
                else
                {
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: EXTRACT AND PREPEND
        // =========================================================

        // The last value in the LPS array is the length of the Longest Palindromic Prefix
        int longest_pal_prefix_len = LPS[m - 1];

        // The characters that are NOT part of the palindromic prefix
        string remaining_suffix = s.substr(longest_pal_prefix_len);

        // Reverse the leftovers
        reverse(remaining_suffix.begin(), remaining_suffix.end());

        // Prepend them to the original string
        return remaining_suffix + s;
    }
};

// -------------------------------------------
// Approach 2: Raw KMP [OPTIMAL] [RECOMMENDED]
// -------------------------------------------

class Solution
{
public:
    /**
     * @brief Finds the shortest palindrome by prepending characters to a string.
     * * * * * * * 🧠 INTUITION (Reverse-Engineering the Palindrome):
     * Every string can be split into two parts:
     * 1. A Longest Palindromic Prefix (LPP).
     * 2. A leftover, non-palindromic suffix.
     * Example: s = "aacecaaa" -> LPP = "aacecaa", Leftover = "a".
     * To make the shortest palindrome, we simply take that leftover suffix,
     * reverse it, and glue it to the front of the original string.
     * Therefore, the entire problem boils down to finding the LPP!
     * * * * * * * 🔍 THE KMP SEARCH MAGIC:
     * A palindrome reads the same forwards and backwards. This means the LPP
     * of a string `s` will perfectly match a suffix of `reverse(s)`.
     * * Instead of the traditional (and memory-heavy) `s + "#" + reverse(s)` trick,
     * we map this directly to a KMP Two-Pointer Search:
     * - PATTERN = The original string `s`.
     * - TEXT = The reversed string.
     * * By running a standard KMP search of the Pattern against the Text, the
     * algorithm inherently tries to match prefixes of the Pattern against suffixes
     * of the Text. When the `while` loop finishes consuming the entire Text, the
     * final state of the `len` pointer tells us exactly how many characters of the
     * Pattern successfully matched the end of the Text.
     * That number is the exact length of our Longest Palindromic Prefix.
     * * * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) to build the LPS array + O(N) to search the text.
     * - Space Complexity: O(N) for the reversed text string and the LPS array.
     * (This is highly optimized, saving the extra O(N) allocation required by
     * the standard separator-concatenation approach).
     * * @param s The input string.
     * @return The shortest transformed palindrome.
     */
    string shortestPalindrome(string &s)
    {

        int n = s.length();

        // Edge Case: Empty strings or single characters are already palindromes
        if (n <= 1)
        {
            return s;
        }

        // To map this to KMP, the original string is our Pattern
        string &pattern = s;

        // The reversed string is the Text we are searching through
        string text = s;
        reverse(text.begin(), text.end());

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY FOR THE PATTERN
        // =========================================================
        vector<int> LPS(n, 0);

        int len = 0; // Tracks the matching prefix length
        int i = 1;   // Scans the suffix of the pattern

        while (i < n)
        {
            if (pattern[len] == pattern[i])
            {
                ++len;
                LPS[i] = len;
                ++i;
            }
            else
            {
                if (len != 0)
                {
                    // Mismatch: Safely fall back to the last known prefix
                    len = LPS[len - 1];
                }
                else
                {
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: RUN KMP SEARCH TO FIND LONGEST MATCHING PREFIX
        // =========================================================
        len = 0; // Reset length pointer to track matches against the Text
        i = 0;   // Reset Right Index to scan the Text

        while (i < n)
        {
            if (pattern[len] == text[i])
            {
                ++len;
                ++i;
            }
            else
            {
                if (len != 0)
                {
                    len = LPS[len - 1];
                }
                else
                {
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 3: EXTRACT AND PREPEND THE REMAINDER
        // =========================================================
        // `len` now perfectly holds the length of the Longest Palindromic Prefix
        int restLen = n - len;

        // Extract the non-palindromic suffix from the original string
        string rest = s.substr(len, restLen);

        // Reverse it
        reverse(rest.begin(), rest.end());

        // Attach it to the front of the original string
        string ans = rest + pattern;

        return ans;
    }
};

int main()
{
    return 0;
}