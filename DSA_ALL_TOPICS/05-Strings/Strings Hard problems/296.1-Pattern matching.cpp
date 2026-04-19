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

1. Title: Search Pattern (Brute force approach)

Links:
https://www.geeksforgeeks.org/problems/search-pattern-rabin-karp-algorithm--141631/1


Problem statement:
Given two strings:
A text string in which you want to search.
A pattern string that you are looking for within the text.

Return all positions (0-based indexing) where the pattern occurs as a substring in the text.
Note: If the pattern does not occur in text, return an empty list.

Examples:
    Input: text = "geeksforgeeks", pattern = "geek"
    Output: [0, 8]
    Explanation: The string "geek" occurs twice in text, one starts at index 0 and the other at index 8.

    Input: text = "aabaacaadaabaaba", pattern = "aaba"
    Output: [0, 9, 12]
    Explanation:

Constraints:
    1 ≤ text.size() ≤ 10^6
    1 ≤ pattern.size() ≤ text.size()
    Both the strings consist of lowercase English alphabets.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Rabin Karp Algorithm - Pattern Searching


Links:
https://takeuforward.org/string/rabin-karp-algorithm-pattern-searching/
https://takeuforward.org/plus/dsa/problems/rabin-karp-algorithm?tab=editorial
https://www.geeksforgeeks.org/problems/search-pattern-rabin-karp-algorithm--141631/1


Problem statement: Same as before


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

3. Title: KMP Algorithm or LPS array    | Knuth-Morris-Pratt


Links:

https://takeuforward.org/plus/dsa/problems/kmp-algorithm-or-lps-array?tab=editorial
https://www.youtube.com/watch?v=ynv7bbcSLKE
https://www.youtube.com/watch?v=V5-7GzOfADQ
https://www.youtube.com/watch?v=GTJr8OvyEVQ
https://www.youtube.com/watch?v=yKhPWrdA6U8


Problem statement: Same as before



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

4. Title: Z function


Links:
https://takeuforward.org/plus/dsa/problems/z-function?tab=editorial



Problem statement: Same as before



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Naive Pattern Matching (Brute Force)
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Finds all occurrences of a pattern using the Naive Brute-Force approach.
     * * * 🧠 INTUITION & APPROACH:
     * This is the most literal translation of string matching. We slide a "window"
     * exactly the size of the pattern across the text, one character at a time.
     * At every single position, we stop and check character-by-character to see if
     * the window perfectly matches the pattern.
     * If we hit a mismatch, we immediately abort the inner loop (`break`), shift the
     * window forward by exactly one position, and start checking from scratch.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N * M) in the worst-case scenario (where N is text length
     * and M is pattern length).
     * -> Best Case: O(N) if the first character of the pattern rarely appears in the text.
     * -> Worst Case: O((N - M + 1) * M). Imagine text = "aaaaaaaaaab" and pattern = "aab".
     * The algorithm successfully matches 'a' and 'a', but fails on 'b', forcing it to
     * shift by 1 and re-evaluate all those 'a's over and over again.
     * - Space Complexity: O(1) auxiliary space. We only use two integer pointers (`i` and `j`).
     */
    vector<int> patternMatch_brute(string &text, string &pattern)
    {

        vector<int> ans;

        int n = text.size();
        int m = pattern.size();

        // 1. Loop over every possible valid starting position in the text.
        // We stop at `tn - pn` because any index after that physically cannot
        // fit the full pattern.
        for (int i = 0; i <= n - m; i++)
        {

            bool mismatched = false;

            // 2. Character-by-character comparison for the current alignment `i`
            for (int j = 0; j < m; j++)
            {

                int idx = i + j; // Map the pattern index `j` to the text index

                if (text[idx] != pattern[j])
                {
                    mismatched = true; // Mismatch detected!
                    break;             // OPTIMIZATION: Stop checking the rest of the pattern
                }
            }

            // 3. If the inner loop finished without triggering the mismatch flag,
            // we have found a perfect contiguous match.
            if (!mismatched)
            {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Rabin Karp Algorithm - Pattern Searching
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Finds all occurrences of a pattern in a text using the Rabin-Karp algorithm.
     * * * * 🌍 FREQUENT USE CASES:
     * 1. Plagiarism Detection Systems: Finding overlapping sentences across massive documents.
     * 2. Multiple Pattern Matching: By hashing multiple patterns and storing them in a
     * Bloom filter/Hash Set, Rabin-Karp can search for thousands of different words
     * simultaneously in a single pass over the text.
     * 3. Data Deduplication (e.g., the `rsync` utility): Identifying identical data
     * chunks across networks.
     * * * * 🧠 INTUITION:
     * Instead of comparing strings character-by-character (which is slow), what if we
     * converted the pattern into a single number (a hash)? Comparing two numbers takes O(1) time.
     * The magic of Rabin-Karp is the "Rolling Hash". When we slide our search window
     * forward by one character, we do NOT recompute the hash from scratch. Instead,
     * we mathematically subtract the value of the character leaving the window, and
     * add the value of the new character entering the window. This takes exactly O(1) time.
     * * * * 🧮 THE HASH ALGORITHM (Decreasing Powers):
     * Think of how we read normal base-10 numbers. In the number 123, the '1' is the most
     * significant digit: (1 * 10^2) + (2 * 10^1) + (3 * 10^0).
     * The powers decrease from left to right. We apply this exact same math to strings!
     * Instead of base-10, we use base-256 (for the ASCII alphabet).
     * Hash = (char[0] * 256^(m-1)) + (char[1] * 256^(m-2)) + ... + (char[m-1] * 256^0)
     * * * * 🚀 STEP-BY-STEP APPROACH:
     * 1. Initialize two math constants: base `d` (256 for the ASCII character set)
     * and a large prime `q` (to prevent integer overflow and minimize hash collisions).
     * 2. Calculate the initial hash value for the Pattern, and the first Window of the Text.
     * 3. Slide the window across the text:
     * - If Current Window Hash == Pattern Hash, we might have a match!
     * - Do a quick character-by-character check to ensure it's not a "spurious hit"
     * (a hash collision where different strings produce the same number).
     * - Mathematically "roll" the hash forward to the next window.
     * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: Expected O(N + M). Hash generation takes O(M). Sliding the window
     * takes O(N). The worst-case is O(N * M) if the prime number is very small and
     * causes a hash collision at every single index, but using a large prime prevents this.
     * - Space Complexity: O(1) auxiliary space. Only primitive integer variables are used.
     */
    vector<int> patternMatch_rabinKarp(string text, string pattern)
    {

        int n = text.length();
        int m = pattern.length();
        vector<int> result;

        if (m == 0 || n < m)
            return result;

        // 'd' is the number of characters in the input alphabet (ASCII)
        long long d = 256;

        // 'q' is a prime number. 10^9 + 7 is standard in competitive programming.
        long long q = 1e9 + 7;

        long long pHash = 0; // Hash value for the target pattern
        long long tHash = 0; // Hash value for the sliding text window

        // 'h' is the multiplier for the most significant digit (the character being removed).
        // Mathematically: h = pow(d, m-1) % q
        long long h = 1;
        for (int i = 0; i < m - 1; i++)
        {
            h = (h * d) % q;
        }

        // 1. Calculate the initial hash values for pattern and the first text window
        for (int i = 0; i < m; i++)
        {
            pHash = (d * pHash + pattern[i]) % q;
            tHash = (d * tHash + text[i]) % q;
        }

        // 2. Slide the pattern over the text one character at a time
        for (int i = 0; i <= n - m; i++)
        {

            // Check if the current window's hash matches the pattern's hash
            if (pHash == tHash)
            {

                // Collision Verification: Ensure the strings actually match
                bool match = true;
                for (int j = 0; j < m; j++)
                {
                    if (text[i + j] != pattern[j])
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                {
                    result.push_back(i);
                }
            }

            // 3. Calculate the hash value for the NEXT window
            if (i < n - m)
            {

                // Rolling Hash Formula:
                // 1. Subtract the leading character safely (ensuring it stays positive)
                tHash = (tHash - ((text[i] * h) % q) + q) % q;

                // 2. Multiply by base and add the trailing character
                tHash = ((tHash * d) + text[i + m]) % q;
            }
        }

        return result;
    }
};

//-------------------------------------------------------------------------------
// 3. Title: KMP Algorithm or LPS array  - Pattern Searching    [RECOMMENDED]
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Finds all occurrences of a pattern in a text using the Knuth-Morris-Pratt (KMP) Algorithm.
     * * =========================================================================================
     * 🧠 THE CORE PROBLEM KMP SOLVES:
     * In a Brute-Force search, if we match 5 characters but fail on the 6th, we throw away
     * all our progress, shift the pattern by 1, and start over. This causes an O(N * M)
     * Time Limit Exceeded (TLE) error on large datasets.
     * KMP asks: "Instead of throwing away our progress, how can we use the characters we
     * JUST matched to figure out exactly where to safely resume the search?"
     *
     * * 🧠 THE INTUITION (The Two-Pointer State Machine):
     * View KMP as a sophisticated Two-Pointer algorithm:
     * - `li` (Left Index): Tracks the length of our currently matched prefix. Because
     * arrays are 0-indexed, it ALSO represents the index of the next character in the
     * PATTERN we need to match!
     * - `i` (Right Index): Scans steadily forward through the text. It NEVER moves backward.
     * * 🛡️ THE SECRET WEAPON: THE LPS ARRAY
     * LPS stands for "Longest Prefix Suffix".
     * It is an array of the same length as the PATTERN. For every character, it answers:
     * "If a mismatch happens here, what is the length of the longest prefix that is ALSO
     * a suffix of the part we just successfully matched?"
     * * Example: Pattern = "A B C A B Y"
     * If we match "ABCAB" but fail on 'Y', we look at the LPS value for the previous
     * character ('B'). It tells us: "You just matched an 'AB' at the end of your streak,
     * which matches the 'AB' at the start of your pattern! Just slide your Left Index (`li`)
     * back to index 2 and keep going!"
     * * 🚀 STEP-BY-STEP EXECUTION:
     * PHASE 1: Build the LPS Array
     * We run our Two Pointers (`li` and `i`) over the pattern itself. If they match,
     * the prefix grows. If they mismatch, we use the previously computed LPS values to
     * safely slide `li` backward until we find a smaller matching prefix, or hit 0.
     * * PHASE 2: The Search
     * We run our Two Pointers again, but this time `i` scans the Text, and `li` scans
     * the PATTERN.
     * - MATCH: Both pointers move forward.
     * - MISMATCH: Freeze the text pointer (`i`). Slide the pattern pointer (`li`) backward
     * using the LPS array. Try again.
     * * ⏱️ COMPLEXITY ANALYSIS:
     * - Time Complexity: O(N + M).
     * Building the LPS array takes O(M) time. Scanning the text takes O(N) time.
     * Because the text pointer `i` never moves backward, and `li` can only fall back
     * as many times as it has moved forward, the loop executes in strictly linear time.
     * - Space Complexity: O(M) auxiliary space.
     * We allocate a single vector of size M to store the LPS array.
     * =========================================================================================
     */
    vector<int> patternMatch_searchKMP(string &text, string &pattern)
    {

        int n = text.size();
        int m = pattern.size();

        // Edge cases: Pattern is empty or physically too large to fit in text
        if (m == 0 || n < m)
            return {};

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY
        // =========================================================
        vector<int> LPS(m, 0);

        int li = 0; // Left Index: Tracks the matching prefix length
        int i = 1;  // Right Index: Scans the suffix of the pattern

        while (i < m)
        {

            if (pattern[li] == pattern[i])
            {
                // Match found: The safe prefix length expands
                ++li;
                LPS[i] = li;
                ++i;
            }
            else
            {
                if (li != 0)
                {
                    // Mismatch: Slide Left Index backward to the last safe prefix length.
                    // Note: 'i' is NOT incremented, so we stay frozen on this character
                    // to re-evaluate it against the new, smaller prefix.
                    li = LPS[li - 1];
                }
                else
                {
                    // Left Index is 0. No prefix matches this character. Advance 'i'.
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: THE KMP SEARCH
        // =========================================================
        vector<int> ans;
        li = 0; // Left Index now tracks our matched state against the Text
        i = 0;  // Right Index now steadily scans the Text

        while (i < n)
        {

            if (pattern[li] == text[i])
            {

                ++li;

                // Complete pattern match found!
                if (li == m)
                {
                    // `i` is at the current matching end. Start index is `i - m + 1`.
                    ans.push_back(i - m + 1);

                    // Fall back the pattern to look for overlapping matches
                    li = LPS[li - 1];
                }

                ++i;
            }
            else if (li != 0)
            {
                // Mismatch after a partial match.
                // Slide Left Index backward using the LPS safety net.
                li = LPS[li - 1];
            }
            else
            {
                // Total mismatch from the very first character.
                // Advance the Text pointer to keep searching.
                ++i;
            }
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 4. Title: Z function - Pattern Searching
//-------------------------------------------------------------------------------
//

/*
For a Senior Backend Engineer targeting FAANG and stable product-based MNCs, learning the Z-Algorithm right now offers a very low return on investment.

You already have KMP (deterministic state machine) and Rabin-Karp (rolling hash). Those two algorithms cover 99.9% of the string matching paradigms expected in elite technical interviews.

*/

class Solution
{
public:
};

int main()
{
    return 0;
}