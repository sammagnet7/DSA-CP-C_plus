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
    1 ≤ text.size() ≤ 106
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


Problem statement:
Given two strings:
A text string in which you want to search.
A pattern string that you are looking for within the text.

Return all positions (0-based indexing) where the pattern occurs as a substring in the text.
Note: If the pattern does not occur in text, return an empty list.
      You have to use Rabin-Karp algorithm here.

Examples:
    Input: text = "geeksforgeeks", pattern = "geek"
    Output: [0, 8]
    Explanation: The string "geek" occurs twice in text, one starts at index 0 and the other at index 8.

    Input: text = "aabaacaadaabaaba", pattern = "aaba"
    Output: [0, 9, 12]
    Explanation:

Constraints:
    1 ≤ text.size() ≤ 106
    1 ≤ pattern.size() ≤ text.size()
    Both the strings consist of lowercase English alphabets.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

3. Title: KMP Algorithm or LPS array    | Knuth-Morris-Pratt


Links:

https://takeuforward.org/plus/dsa/problems/kmp-algorithm-or-lps-array?tab=editorial
https://www.youtube.com/watch?v=ynv7bbcSLKE
https://www.youtube.com/watch?v=V5-7GzOfADQ
https://www.youtube.com/watch?v=GTJr8OvyEVQ


Problem statement:
Given two strings, one is a text string txt and the other is a pattern string pat. The task is to print the indexes of all the occurrences of the pattern string in the text string. Use 0-based indexing while returning the indices.
Note: Return an empty list in case of no occurrences of pattern.

Examples :
Input: txt = "abcab", pat = "ab"
Output: [0, 3]
Explanation: The string "ab" occurs twice in txt, one starts at index 0 and the other at index 3. 
Input: txt = "abesdu", pat = "edu"
Output: []
Explanation: There's no substring "edu" present in txt.
Input: txt = "aabaacaadaabaaba", pat = "aaba"
Output: [0, 9, 12]
Explanation:

Constraints:
1 ≤ txt.size() ≤ 106
1 ≤ pat.size() < txt.size()
Both the strings consist of lowercase English alphabets.




INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

4. Title: Z function


Links:
https://takeuforward.org/plus/dsa/problems/z-function?tab=editorial



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Naive Pattern Matching (Brute Force)
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // Intuition:
    //   - Try aligning the pattern at every possible position in the text.
    //   - For each alignment, compare the pattern with the corresponding substring.
    //   - If all characters match, record the starting index.
    //   - Simple but inefficient for large inputs.
    //
    // Complexity Analysis:
    //   Let:
    //     T = length of text
    //     P = length of pattern
    //
    //   Time Complexity:
    //     - Outer loop runs (T - P + 1) times → O(T - P + 1).
    //     - Inner loop runs up to P comparisons in the worst case.
    //     - Total = O((T - P + 1) * P) ≈ O(T * P).
    //
    //   Space Complexity:
    //     - O(1) auxiliary space (only booleans and counters used).
    //     - O(K) for output vector, where K = number of matches.
    //     - Overall: O(1) extra space (ignoring output).
    // -----------------------------------------------------------------------------
    vector<int> patternMatch_brute(string &text, string &pattern)
    {

        vector<int> ans; // stores starting indices of matches

        int T = text.size();    // text length
        int P = pattern.size(); // pattern length

        // Loop over every possible starting position in `text`
        for (int i = 0; i <= T - P; i++)
        {
            bool mismatched = false; // flag to detect mismatch at this alignment

            // Compare pattern[j] with text[i+j] for j = 0..P-1
            for (int j = 0; j < P; j++)
            {
                int idx = i + j; // corresponding index in text

                if (text[idx] != pattern[j])
                {
                    mismatched = true; // mismatch found
                    break;             // exit loop for this alignment
                }
            }

            // If no mismatch occurred, record starting index `i`
            if (!mismatched)
                ans.push_back(i);
        }

        return ans; // return all match indices
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Rabin Karp Algorithm - Pattern Searching
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Rabin–Karp string search (rolling hash) — returns starting indices where
    // `pattern` occurs in `text`.
    //
    // Step-by-step overview:
    // 1. Precompute the hash of the pattern and the hash of the first window
    //    (first `ps` characters) of the text using a polynomial rolling hash:
    //       H(s[0..m-1]) = sum_{i=0..m-1} s[i] * (prime^i)  (mod MOD)
    //    (This implementation uses increasing powers prime^0, prime^1, ...).
    // 2. Compare the two hashes; if equal, verify by direct substring compare
    //    to avoid false positive due to hash collision. If equal, push index 0.
    // 3. Slide the window one position at a time:
    //      - Remove contribution of the outgoing character (left side).
    //      - Add contribution of the incoming character (right side) using the
    //        precomputed power for the `ps`-th place.
    //      - Update the *pattern* hash by multiplying it by `prime` to keep
    //        both hashes in the same "scale" for comparison.
    //      - On hash equality, verify with substring compare and record the
    //        starting index if it matches.
    //
    // Important implementation notes:
    // - We use modular arithmetic (MOD) to keep numbers bounded.
    // - When subtracting, we add MOD before taking % MOD to avoid negative
    //   intermediate values: (a - b + MOD) % MOD.
    // - Because hash collisions are possible, every hash match is followed by a
    //   direct string comparison to confirm a true match.
    //
    // Complexity:
    // - Let T = text.length(), P = pattern.length().
    // - Time (average): O(T + P) — computing initial hashes O(P), sliding O(T-P+1)
    //   with O(1) updates and only rare substring verifications.
    // - Time (worst-case, pathological collisions): O((T - P + 1) * P).
    // - Space: O(1) auxiliary (plus O(K) for the output indices).
    // ------------------------------------------------------------------------
    vector<int> rabinKarp(string &text, string &pattern)
    {
        // code here

        vector<int> ans;
        int ts = text.size();
        int ps = pattern.size();

        // Small constants controlling the rolling hash:
        int MOD = 101; // modulus (prime). Keeps hash values small.
        int prime = 7; // base multiplier used for powers.

        // prime_left will represent prime^i for the character being removed
        // from the left of the window (initially prime^0 = 1).
        int prime_left = 1;
        // prime_right will be used to compute the multiplier for a newly added
        // right-side character; after the initial loop it equals prime^ps.
        int prime_right = 1;

        int pat_hash = 0;  // hash of the pattern (mod MOD)
        int text_hash = 0; // hash of the current window in text (mod MOD)

        // --------------------------------------------------------------------
        // INITIAL HASH COMPUTATION for pattern and first text window
        // We compute:
        //   pat_hash  = sum_{i=0..ps-1} pattern[i] * prime^i  (mod MOD)
        //   text_hash = sum_{i=0..ps-1} text[i]    * prime^i  (mod MOD)
        // prime_right is multiplied by `prime` each iteration so that after the
        // loop prime_right == prime^ps (used later when adding the next char).
        // --------------------------------------------------------------------
        for (int i = 0; i < ps; i++)
        {
            // accumulate contribution of character at position i weighted by prime^i
            text_hash = (text_hash + (text[i] * prime_right) % MOD) % MOD;
            pat_hash = (pat_hash + (pattern[i] * prime_right) % MOD) % MOD;

            // advance multiplier for the next character (prime^0 -> prime^1 -> ...)
            prime_right = (prime_right * prime) % MOD; // NOTE: do mod here as well
        }

        // If initial window hash matches pattern hash, verify by direct compare.
        // (This prevents false positives caused by hash collisions.)
        if (text_hash == pat_hash)
        {
            if (text.substr(0, ps) == pattern)
                ans.push_back(0);
        }

        // --------------------------------------------------------------------
        // SLIDING WINDOW:
        // For each new starting index i (1 .. ts-ps), update the rolling hash:
        //
        // - Remove contribution of the character leaving the window:
        //     text[remIdx] * prime_left  (prime_left = prime^{i-1})
        //   We perform (text_hash - contribution + MOD) % MOD to avoid negative.
        //
        // - Add contribution of the new character entering the window:
        //     text[addIdx] * prime_right (prime_right == prime^ps for first slide,
        //                                 then grows as we slide further)
        //
        // - Update pat_hash := pat_hash * prime % MOD
        //   (this shifts pattern hash by one power so it stays comparable to the
        //    updated text_hash representation).
        //
        // - If the hashes match, verify the substring and store the starting index.
        //
        // - Update prime_right and prime_left by multiplying by prime for next slide.
        // --------------------------------------------------------------------
        for (int i = 1; i + ps <= ts; i++)
        {

            int remIdx = i - 1;      // index of character leaving the window
            int addIdx = i + ps - 1; // index of new character entering the window

            // Remove leftmost character's weighted contribution:
            // (text_hash - (text[remIdx]*prime_left) ) % MOD  -> ensure non-negative
            text_hash = (text_hash - (text[remIdx] * prime_left) % MOD + MOD) % MOD;
            // Add the new rightmost character's contribution using prime_right (p^ps)
            text_hash = (text_hash + (text[addIdx] * prime_right) % MOD) % MOD;

            // Shift pattern hash by one power so hashes remain comparable:
            // if pat_hash = sum pattern[j]*p^j, then after *p it becomes
            // sum pattern[j]*p^{j+1}, matching how the text_hash was updated.
            pat_hash = (pat_hash * prime) % MOD;

            // If the rolling hashes match, do direct verification to confirm:
            if (text_hash == pat_hash)
            {
                if (text.substr(i, ps) == pattern)
                    ans.push_back(i);
            }

            // Update multipliers for the next slide:
            // prime_right grows (initially p^ps, then p^{ps+1}, ...) and prime_left
            // grows as p^{i} so that it always equals p^{(window_start_index)}.
            prime_right = (prime_right * prime) % MOD;
            prime_left = (prime_left * prime) % MOD;
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 3. Title: KMP Algorithm or LPS array  - Pattern Searching
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /*
     * buildLPS(pat)
     * ----------------
     * Purpose / Idea:
     *   - Build the LPS (Longest Proper Prefix which is also Suffix) array for the
     *     pattern `pat`. LPS[i] stores the length of the longest proper prefix of
     *     pat[0..i] that is also a suffix of pat[0..i].
     *   - This array is the core of the Knuth–Morris–Pratt (KMP) algorithm and is
     *     used to skip unnecessary comparisons when a mismatch occurs during search.
     *
     * How it works (high level):
     *   - Maintain two indices:
     *       i -> current index we are computing LPS for (scans forward)
     *       j -> length of the current "matched" prefix (also points to char in prefix)
     *   - If pat[i] == pat[j], we extend the current matched prefix by one:
     *       LPS[i] = j + 1; i++; j++;
     *   - If mismatch and j > 0, we "fall back" to a shorter candidate prefix:
     *       j = LPS[j - 1]   (try the next smaller border)
     *     If j == 0 and mismatch, there is no border to fall back on and we set
     *       LPS[i] = 0; i++;
     *
     * Why this is efficient:
     *   - Each character is processed at most a constant number of times (i and j
     *     only move forward or fall to previously computed LPS values), hence
     *     the algorithm runs in linear time.
     *
     * Complexity:
     *   - Time:  O(m)   where m = pat.length()
     *   - Space: O(m)   the LPS array of length m
     */
    vector<int> buildLPS(string &pat)
    {

        int m = pat.size(); // m = length of pattern
        int i = 1;          // start building LPS from index 1 (LPS[0] = 0 by definition)
        int j = 0;          // length of current matched prefix

        vector<int> LPS(m, 0); // initialize LPS array with zeros

        // Process characters until we fill LPS for the whole pattern
        while (i < m)
        {
            if (pat[i] == pat[j])
            {
                // Characters match: extend the previous border by 1
                LPS[i] = j + 1; // LPS at i is length of matched prefix (j+1)
                i++;            // advance to next position in pattern
                j++;            // prefix length increased
            }
            else
            {
                // Mismatch case:
                if (j == 0)
                {
                    // No smaller border to try; LPS[i] remains 0, move forward
                    i++;
                }
                else
                    // Fall back to the next best (smaller) border length and try again.
                    // This avoids re-checking characters from the start of the pattern.
                    j = LPS[j - 1]; // move j to the length of the next candidate border
            }
        }

        return LPS; // return the prefix-function array for the pattern
    }

    /*
     * search(pat, txt)
     * -----------------
     * Purpose / Idea:
     *   - Use the LPS array of the pattern to scan the text and identify all
     *     starting indices where the pattern occurs in the text.
     *   - This implementation stores for every text index the length of the
     *     matched prefix of the pattern up to that text index in LPS_txt[].
     *   - After scanning the whole text, positions where LPS_txt[i] == m indicate
     *     a full match of the pattern that ends at index i in the text. The
     *     corresponding start index is i - m + 1.
     *
     * Algorithm steps:
     *   1. Compute LPS for the pattern: LPS_pat = buildLPS(pat)
     *   2. Initialize two pointers:
     *        i -> current index in text (scans forward)
     *        j -> current index in pattern (how many characters matched so far)
     *   3. While i < n:
     *        - If txt[i] == pat[j] then we matched one more character:
     *            LPS_txt[i] = j + 1; // matched length at text index i
     *            i++; j++;
     *        - If mismatch:
     *            If j == 0 -> advance i (no prefix matched)
     *            Else        -> set j = LPS_pat[j - 1] (fall back to next border)
     *   4. After the scan, collect indices where LPS_txt[i] == m and compute
     *      starting positions by (i - m + 1).
     *
     * Complexity:
     *   - Time:  O(n + m)
     *       * buildLPS takes O(m)
     *       * scanning the text with the help of LPS_pat is linear O(n)
     *   - Space: O(n + m)
     *       * LPS_pat: O(m)
     *       * LPS_txt: O(n) (this particular implementation stores match-lengths for text)
     *       * ans: up to O(n) in worst case (many matches)
     *
     * Notes on design:
     *   - Typical KMP implementations output matches immediately when j == m
     *     inside the main loop; this version instead records matched lengths in
     *     LPS_txt and post-processes them to produce starting indices. Both are
     *     correct; the choice here trades immediate pushes for a separate pass.
     */
    vector<int> search(string &pat, string &txt)
    {
        // code here

        int n = txt.size(); // length of text
        int m = pat.size(); // length of pattern

        // Build prefix-function for pattern (LPS for pattern)
        vector<int> LPS_pat = buildLPS(pat);

        // LPS_txt[i] will hold the number of characters of the pattern that are
        // matched ending exactly at txt[i]. This is an auxiliary array used by
        // this implementation to mark matches; many KMP variants don't store this.
        vector<int> LPS_txt(n, 0);
        vector<int> ans; // result list of starting indices

        int i = 0; // index into text
        int j = 0; // index into pattern (number of matched characters)

        // Scan text once using KMP logic
        while (i < n)
        {

            if (txt[i] == pat[j])
            {
                // characters match: record the matched length at this text index
                LPS_txt[i] = j + 1; // matched with pattern up to j-th index
                i++;                // advance in text
                j++;                // advance in pattern (one more matched)

                // Note: many implementations would check `if (j == m)` here and
                // immediately record a match (i - m) and then set j = LPS_pat[j - 1].
                // This code instead defers adding matches until after the loop and
                // populates LPS_txt for all positions.

                // Example of immediate handling (commented out in original):
                // if (j == m) {
                //     ans.push_back(i - m);      // pattern found ending at i-1
                //     j = LPS_pat[j - 1];        // continue searching for next match
                // }
            }
            else
            {
                // Mismatch: need to decide how to recover
                if (j == 0)
                {
                    // No prefix matched so far; advance text pointer
                    i++;
                }
                else
                    // Fall back in the pattern to try a shorter matching prefix.
                    // LPS_pat[j-1] gives the length of the longest proper prefix
                    // which is also a suffix for pat[0..j-1].
                    j = LPS_pat[j - 1];
            }
        }

        // Post-processing: any index i in text with LPS_txt[i] == m indicates the
        // pattern fully matched ending at i, so starting index is i - m + 1.
        for (int i = 0; i < n; i++)
        {
            if (LPS_txt[i] == m)
                ans.push_back(i - m + 1);
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 4. Title: Z function - Pattern Searching
//-------------------------------------------------------------------------------
//

class Solution
{
public:
};

int main()
{
    return 0;
}