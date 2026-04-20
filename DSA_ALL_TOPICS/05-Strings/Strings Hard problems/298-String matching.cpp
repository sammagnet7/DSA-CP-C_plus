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

1. Title: Find the Index of the First Occurrence in a String

Links:
https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/


Problem statement:
Given two strings `needle` and `haystack`, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.



Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.


Constraints:

1 <= haystack.length, needle.length <= 10^4
haystack and needle consist of only lowercase English characters.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Repeated String Match


Links:
https://leetcode.com/problems/repeated-string-match/


Problem statement:
Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.

Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".



Example 1:

Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
Example 2:

Input: a = "a", b = "aa"
Output: 2


Constraints:

1 <= a.length, b.length <= 10^4
a and b consist of lowercase English letters.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Find the Index of the First Occurrence in a String
//-------------------------------------------------------------------------------

class Solution
{
public:
    // ---------------------------------------
    // Approach 1: Brute force
    // ---------------------------------------

    /**
     Intuition:
      - Try every possible alignment of `needle` inside `haystack`.
      - For each starting position i, compare characters one-by-one.
      - If all characters match for that alignment, return i.

     Complexity (let N = haystack.length(), M = needle.length()):
      - Time:    O(N * M) in the worst case (for each of ≈N positions we compare up to M chars).
      - Space:   O(1) auxiliary (only a few integer variables); O(1) ignoring output.
    */
    int strStr_bruteforce(string haystack, string needle)
    {

        int lh = haystack.length(); // T = length of haystack
        int ln = needle.length();   // P = length of needle
        int index = 0;              // stores potential starting index if match begins here

        // Edge case: empty needle — by convention often return 0.
        // (Original code didn't check this; if desired add `if(ln==0) return 0;`)

        // Iterate over every possible starting index in haystack where needle could fit
        for (int i = 0; i < lh; i++)
        {

            // Quick candidate check: first character must match
            if (ln == 0)
                return 0; // optional guard if needle empty
            if (i + ln > lh)
                break; // remaining text shorter than needle -> stop
            if (haystack[i] == needle[0])
            {
                index = i; // potential starting index

                int check = ln;  // how many characters left to check
                int locIdxH = i; // pointer into haystack (current window)
                int locIdxN = 0; // pointer into needle

                // Compare needle with substring haystack[i .. i+ln-1]
                while (check)
                {
                    if (haystack[locIdxH] == needle[locIdxN])
                    {
                        locIdxH++; // advance in haystack
                        locIdxN++; // advance in needle
                        check--;   // one fewer char left to check
                        continue;
                    }
                    else
                    {
                        // mismatch at this alignment -> abandon this i
                        break;
                    }
                }

                // If all characters matched (check==0) -> return starting index
                if (check == 0)
                {
                    return index;
                }
            }
        }

        // No occurrence found
        return -1;
    }

    // ----------------------------------------------
    // Approach 2: Rabin–Karp (rolling hash) [Slower]
    // ----------------------------------------------

    using ll = long long;

    /**
     * @brief Finds the starting index of the first occurrence of a pattern in a text.
     * * * * * 🧠 INTUITION (Rabin-Karp Rolling Hash):
     * Instead of comparing strings character by character (which takes O(N*M)), we treat
     * strings as large numbers in a specific base (e.g., Base 256 for ASCII). We compute
     * the hash of the pattern and a sliding window of the text.
     * * When the window slides right by one character, we do not recompute the hash from
     * scratch. Instead, we perform an O(1) mathematical "roll":
     * 1. Subtract the value of the outgoing character.
     * 2. Shift the remaining window left (multiply by base).
     * 3. Add the value of the incoming character.
     * * * * * * ⚠️ THE COLLISION CAVEAT:
     * Two different strings can produce the same hash (a Hash Collision). Therefore,
     * when `pHash == tHash`, we MUST perform a strict character-by-character verification
     * to guarantee it is a true match and not a false positive.
     * * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: Average O(N + M). Worst-case O(N * M) if the hash function
     * experiences catastrophic collisions (highly mitigated by a large prime MOD).
     * - Space Complexity: O(1) auxiliary space.
     * * @param haystack The text string to search within.
     * @param needle The pattern string to search for.
     * @return The 0-based index of the first occurrence, or -1 if not found.
     */
    int strStr(string haystack, string needle)
    {

        // Use references to prevent expensive deep copies of large strings
        string &text = haystack;
        string &pattern = needle;

        int n = text.length();
        int m = pattern.length();

        // Edge cases: Pattern is empty or physically too large to fit in the text
        if (m == 0 || n < m)
        {
            return -1;
        }

        // Base 256 covers the entire extended ASCII character set
        int base = 256;
        // Large prime number to mathematically minimize hash collisions and prevent overflow
        int MOD = 1e9 + 7;

        ll pHash = 0; // Pattern Hash
        ll tHash = 0; // Text Window Hash

        // The multiplier for the Most Significant Byte (MSB)
        // This is strictly used to subtract the outgoing character when the window slides.
        ll msbMult = 1;

        // =========================================================
        // PHASE 1: PRE-COMPUTE MSB MULTIPLIER (base^(m-1) % MOD)
        // =========================================================
        for (int i = 1; i <= m - 1; ++i)
        {
            msbMult = (msbMult * base) % MOD;
        }

        // =========================================================
        // PHASE 2: CALCULATE INITIAL HASHES
        // =========================================================
        // Compute the hash for the entire pattern and the FIRST window of the text.
        for (int i = 0; i < m; ++i)
        {
            pHash = ((pHash * base) + pattern[i]) % MOD;
            tHash = ((tHash * base) + text[i]) % MOD;
        }

        // =========================================================
        // PHASE 3: SLIDING WINDOW SEARCH
        // =========================================================
        // Note on Indexing: `i` represents the index of the INCOMING character
        // that will be added to the hash on the NEXT iteration.
        // Therefore, the current window being evaluated ends at `i - 1` and starts at `i - m`.
        for (int i = m; i <= n; ++i)
        {

            // 1. Check for a Hash Match
            if (pHash == tHash)
            {

                bool matched = true;

                // Hash collision verification: strictly compare the characters
                for (int p = 0; p < m; ++p)
                {
                    if (pattern[p] != text[(i - m) + p])
                    {
                        matched = false;
                        break; // False positive (collision), break out of verification
                    }
                }

                // True match confirmed!
                if (matched)
                {
                    return (i - m);
                }
            }

            // 2. Roll the Hash for the next window
            // We only roll if there are more characters left in the text to consume.
            if (i < n)
            {
                // Step A: Remove the outgoing character (at index i - m)
                // We add MOD before taking % MOD to guarantee C++ doesn't return a negative modulo
                tHash = ((tHash - ((text[i - m] * msbMult) % MOD)) + MOD) % MOD;

                // Step B: Shift left and add the incoming character (at index i)
                tHash = ((tHash * base) + text[i]) % MOD;
            }
        }

        // Pattern not found anywhere in the text
        return -1;
    }

    // ---------------------------------------
    // Approach 3: KMP [OPTIMAL] [RECOMMENDED]
    // ---------------------------------------

    /**
     * @brief Finds the starting index of the first occurrence of a pattern (needle) in a text (haystack).
     * * * * * 🧠 INTUITION (The KMP State Machine):
     * This is a textbook application of the Knuth-Morris-Pratt (KMP) algorithm.
     * To avoid the O(N * M) worst-case time complexity of Brute-Force searching, we
     * use a Two-Pointer state machine powered by an LPS (Longest Prefix Suffix) array.
     * * - `len` (Length Pointer): Tracks the length of our currently matched prefix.
     * - `i` (Right Index): Scans steadily forward.
     * * When a mismatch occurs, we do not restart the search from scratch. Instead, we
     * freeze the text pointer `i` and use the LPS array to slide the `len` pointer
     * safely backward to the last known valid prefix state.
     * * * * * 💡 IMPLEMENTATION NOTE (First Occurrence vs. All Occurrences):
     * Because this problem only asks for the FIRST occurrence, we do not need to fall
     * back the pattern pointer (`len = LPS[len - 1]`) after a complete match. We can
     * simply return the calculated starting index immediately, saving CPU cycles.
     * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N + M) where N is haystack length and M is needle length.
     * - Space Complexity: O(M) auxiliary space to pre-compute the LPS array.
     * * @param haystack The text string to search within.
     * @param needle The pattern string to search for.
     * @return The 0-based index of the first occurrence, or -1 if not found.
     */
    int strStr(string haystack, string needle)
    {

        // Use references to match standard KMP naming conventions without copying strings
        string &text = haystack;
        string &pattern = needle;

        int n = text.length();
        int m = pattern.length();

        // Edge cases: Pattern is empty or physically too large to fit in the text
        if (m == 0 || n < m)
        {
            return -1;
        }

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY
        // =========================================================
        vector<int> LPS(m, 0);

        int len = 0; // Length Pointer: Tracks the matching prefix length
        int i = 1;   // Right Index: Scans the suffix of the pattern

        while (i < m)
        {

            if (pattern[len] == pattern[i])
            {
                // Match found: Expand the known prefix length
                ++len;
                LPS[i] = len;
                ++i;
            }
            else
            {
                // Mismatch: Slide the `len` pointer backward using the LPS safety net
                if (len != 0)
                {
                    len = LPS[len - 1];
                    // Note: 'i' is NOT incremented, so we re-evaluate pattern[i]
                }
                else
                {
                    // `len` is 0. No prefix matches this character. Advance 'i'.
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: THE KMP SEARCH
        // =========================================================
        len = 0; // `len` now tracks our matched state against the Text
        i = 0;   // Right Index now steadily scans the Text

        while (i < n)
        {

            if (pattern[len] == text[i])
            {

                ++len;
                ++i;

                // Complete pattern match found!
                if (len == m)
                {
                    // OPTIMIZATION: We only need the FIRST occurrence.
                    // No need to do `len = LPS[len - 1];` to check for overlapping
                    // matches. Just calculate the start index and return instantly.
                    return i - m;
                }
            }
            else
            {
                // Mismatch after a partial match.
                // Slide the `len` pointer backward using the pre-computed LPS array.
                if (len != 0)
                {
                    len = LPS[len - 1];
                }
                else
                {
                    // Total mismatch from the very first character. Advance text pointer.
                    ++i;
                }
            }
        }

        // If the loop finishes without returning, the pattern does not exist in the text
        return -1;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Repeated String Match
//-------------------------------------------------------------------------------

// -----------------------------------------------
// Approach : String concatenation + KMP [OPTIMAL]
// -----------------------------------------------

class Solution
{
private:
    /**
     * @brief Helper method to determine if a pattern exists within a text using KMP.
     * * * * * 🧠 INTUITION:
     * This is a customized version of the Knuth-Morris-Pratt (KMP) algorithm.
     * Because we only care IF the pattern exists (not where, or how many times),
     * this implementation features an "Early Exit". The moment a full match is
     * detected, it immediately returns `true` rather than continuing to scan
     * the rest of the text.
     * * * * * ⏱️ COMPLEXITY:
     * - Time: O(N + M)
     * - Space: O(M) for the LPS array.
     */
    bool searchKMP(string &text, string &pattern)
    {

        int n = text.size();
        int m = pattern.size();

        // Edge cases: Pattern is empty or physically too large to fit
        if (m == 0 || n < m)
            return false;

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY
        // =========================================================
        vector<int> LPS(m, 0);
        int len = 0; // Tracks the matching prefix length
        int i = 1;   // Scans the suffix of the pattern

        while (i < m)
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
                    len = LPS[len - 1]; // Fallback to last safe prefix
                }
                else
                {
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: EARLY-EXIT KMP SEARCH
        // =========================================================
        len = 0;
        i = 0;

        while (i < n)
        {
            if (pattern[len] == text[i])
            {
                ++len;

                // Complete pattern match found!
                if (len == m)
                {
                    // OPTIMIZATION: Return immediately instead of scanning the rest of the string
                    return true;
                }
                ++i;
            }
            else if (len != 0)
            {
                len = LPS[len - 1]; // Safe fallback on mismatch
            }
            else
            {
                ++i;
            }
        }

        return false;
    }

public:
    /**
     * @brief Finds the minimum repeats of 'a' required for 'b' to be a substring.
     * * * * * * 🧠 INTUITION (The Mathematical Bounds):
     * To fit string `b`, our repeated string must obviously be at least as long
     * as `b`. Let `q` be the minimum number of times we must repeat `a` to reach
     * or exceed the length of `b` (q = ceil(length_b / length_a)).
     * * * * * * 🔍 THE "WHY" BEHIND ONLY TWO CHECKS:
     * It feels intuitive to pad the front and back of the string "just to be safe"
     * (e.g., checking q, q+1, and q+2 copies). However, string math proves we
     * ONLY ever need to check exactly two states: `q` and `q + 1`.
     * * 1. CHECK 1 (Exactly `q` repeats):
     * If `b` perfectly aligns with the start of our repeating `a` blocks, it
     * will fit entirely within the absolute minimum required copies.
     * * 2. CHECK 2 (Exactly `q + 1` repeats):
     * What if `b` starts at an offset (e.g., index 2 of the first `a`)?
     * Because the start of `b` shifted right by *less than the length of `a`*,
     * the end of `b` will spill over the boundary of our `q` copies by
     * *less than the length of `a`*. Therefore, appending exactly ONE more
     * copy of `a` to the end perfectly catches this spillover.
     * * ❌ Why not `q + 2` or front-padding?
     * - Because a repeated string is identical everywhere (abcabcabc),
     * padding the front is mathematically identical to padding the back.
     * - If `b` required a `q + 2` copy, it means the start of `b` shifted
     * so far right that it actually started inside the SECOND copy of `a`.
     * If it started in the second copy, the first copy was useless, which
     * violates our premise of `q` being the minimum bounding window.
     * * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N + M) if using KMP/Rabin-Karp for the search.
     * (Using standard `string::find` is O(N * M) worst-case, though highly
     * optimized in the C++ standard library).
     * - Space Complexity: O(N + M) to store the repeated baseline string.
     */
    int repeatedStringMatch(string a, string b)
    {

        int m = a.length();
        int n = b.length();

        // 1. Calculate the minimum repeats required for 'a' to span the length of 'b'
        // This is the integer equivalent of ceil((double)n / m)
        int min_repeats = (n + m - 1) / m;

        // 2. Build the baseline bounding string (exactly 'q' repeats)
        string repeated_a = "";
        for (int i = 0; i < min_repeats; ++i)
        {
            repeated_a += a;
        }

        // 3. Check Scenario 1: 'b' fits inside the minimal bounding string
        // if (repeated_a.find(b) != string::npos)
        if (searchKMP(repeated_a, b))
        {
            return min_repeats;
        }

        // 4. Check Scenario 2: The Offset Spillover
        // Append exactly ONE final copy of 'a' to catch a rightward-shifted pattern
        repeated_a += a;
        // if (repeated_a.find(b) != string::npos)
        if (searchKMP(repeated_a, b))
        {
            return min_repeats + 1;
        }

        // 5. Mathematical Impossibility
        return -1;
    }
};

int main()
{
    return 0;
}