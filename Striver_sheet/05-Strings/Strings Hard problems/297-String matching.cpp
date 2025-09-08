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
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.



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

1 <= haystack.length, needle.length <= 104
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

1 <= a.length, b.length <= 104
a and b consist of lowercase English letters.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Find the Index of the First Occurrence in a String
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Approach 1 — Brute Force (naive)
    //
    // Intuition:
    //  - Try every possible alignment of `needle` inside `haystack`.
    //  - For each starting position i, compare characters one-by-one.
    //  - If all characters match for that alignment, return i.
    //
    // When to use:
    //  - Simple and easy to implement; OK when strings are small.
    //  - Not suitable for large inputs because it can do many repeated comparisons.
    //
    // Method-level complexity (let T = haystack.length(), P = needle.length()):
    //  - Time:    O(T * P) in the worst case (for each of ≈T positions we compare up to P chars).
    //  - Space:   O(1) auxiliary (only a few integer variables); O(1) ignoring output.
    // ------------------------------------------------------------------------
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

    // ------------------------------------------------------------------------
    // Approach 2 — Rabin–Karp (rolling hash)
    //
    // Intuition:
    //  - Compute a numeric hash for the pattern and for each text window of length P.
    //  - Use a rolling hash so each window hash can be updated in O(1) from the
    //    previous window instead of recomputing from scratch.
    //  - When hashes match, verify by direct substring comparison to avoid
    //    false positives due to collisions.
    //
    // When to use:
    //  - Good average-case performance O(T + P). Useful when you need simpler code
    //    than KMP but better than naive. Still needs verification on hash matches.
    //
    // Method-level complexity (let T = text.length(), P = pattern.length()):
    //  - Time (expected/average): O(T + P)
    //    * Initial hashes: O(P)
    //    * Sliding windows: ~O(T - P + 1) with O(1) updates and occasional verification.
    //  - Time (worst-case): O((T - P + 1) * P) if many hash collisions occur.
    //  - Space: O(1) auxiliary (few integers). Output not counted.
    // ------------------------------------------------------------------------
    int rabinKarp(string &text, string &pattern)
    {
        int ts = text.size();    // T
        int ps = pattern.size(); // P

        // Small primes used for polynomial rolling hash:
        int MOD = 101; // modulus (small prime here; for robustness use large prime)
        int prime = 7; // base multiplier

        // prime_left = prime^{window_start_index} (initially prime^0 = 1)
        int prime_left = 1;
        // prime_right will be advanced so that after initial loop prime_right == prime^ps
        int prime_right = 1;

        int pat_hash = 0;  // pattern hash (mod MOD)
        int text_hash = 0; // current window hash (mod MOD)

        // --------------------------------------------------------------------
        // Compute initial hashes for pattern and first window of text:
        // hash = sum_{i=0..ps-1} char * prime^i  (mod MOD)
        // prime_right advances as prime^0 -> prime^1 -> ... -> prime^{ps-1}
        // --------------------------------------------------------------------
        for (int i = 0; i < ps; i++)
        {
            // Add weighted character contributions for both pattern and text window
            text_hash = (text_hash + (text[i] * prime_right) % MOD) % MOD;
            pat_hash = (pat_hash + (pattern[i] * prime_right) % MOD) % MOD;

            // Advance multiplier for next character (keep modulo to avoid overflow)
            prime_right = (prime_right * prime) % MOD;
        }

        // If initial hashes match, verify with direct compare to avoid false match
        if (text_hash == pat_hash)
        {
            if (text.substr(0, ps) == pattern)
                return 0;
        }

        // --------------------------------------------------------------------
        // Slide the window across the text from i=1 to i = ts-ps
        // For each slide:
        //  - remove contribution of text[remIdx] weighted by prime_left
        //  - add contribution of text[addIdx] weighted by prime_right (which was
        //    precomputed as prime^ps initially)
        //  - shift pat_hash by multiplying by prime so both hashes remain
        //    comparable (they use same power offsets)
        //  - verify on hash equality
        //  - update prime_right and prime_left for the next slide
        // --------------------------------------------------------------------
        for (int i = 1; i + ps <= ts; i++)
        {
            int remIdx = i - 1;      // index leaving the window
            int addIdx = i + ps - 1; // index entering the window

            // Remove leftmost char's weighted contribution (use +MOD to avoid negative)
            text_hash = (text_hash - (text[remIdx] * prime_left) % MOD + MOD) % MOD;
            // Add new rightmost char's weighted contribution
            text_hash = (text_hash + (text[addIdx] * prime_right) % MOD) % MOD;

            // Shift pattern hash by one power so hash representations stay comparable
            pat_hash = (pat_hash * prime) % MOD;

            // On hash equality do exact compare to confirm (collision-safe)
            if (text_hash == pat_hash)
            {
                if (text.substr(i, ps) == pattern)
                    return i;
            }

            // Update multipliers for the next slide:
            // prime_right grows (initially p^ps -> now p^{ps+1} -> ...)
            // prime_left grows to reflect next window's left power
            prime_right = (prime_right * prime) % MOD;
            prime_left = (prime_left * prime) % MOD;
        }

        // No occurrence found
        return -1;
    }

    // ------------------------------------------------------------------------
    // Public wrapper: choose which implementation to use.
    // Currently forwards to Rabin–Karp implementation (better average-case).
    // To use brute-force instead, change to: return strStr_bruteforce(haystack, needle);
    // ------------------------------------------------------------------------
    int strStr(string haystack, string needle)
    {
        // You can switch implementations here:
        // return strStr_bruteforce(haystack, needle);
        return rabinKarp(haystack, needle);
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Repeated String Match
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    bool rabinKarp(string &text, string &pattern)
    {
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
                return true;
        }

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
                    return true;
            }

            // Update multipliers for the next slide:
            // prime_right grows (initially p^ps, then p^{ps+1}, ...) and prime_left
            // grows as p^{i} so that it always equals p^{(window_start_index)}.
            prime_right = (prime_right * prime) % MOD;
            prime_left = (prime_left * prime) % MOD;
        }

        return false;
    }

    /*
     repeatedStringMatch

     Intuition:
     - We want the smallest k such that repeating string `a` k times contains `b` as a substring.
     - If we repeat `a` until the concatenated string's length >= length(b), that repeated string (call it tmp)
         is the shortest repeated string of `a` that could possibly contain `b` entirely inside it without needing
         additional characters to the right. However, `b` might start near the end of `tmp` and continue into the
         next repetition of `a`. Therefore, it's sufficient to check:
         1) tmp (the minimal repetition with length >= |b|)
         2) tmp + a (one extra repetition)
         If neither contains `b`, no larger k will help (because any occurrence would have to be aligned within one
         of these two lengths).

     Approach (step-by-step):
     1) Compute lengths m = |a|, n = |b|.
     2) Build tmp by appending `a` repeatedly until tmp.length() >= n. Keep track of how many copies (count).
         - After this loop, tmp is the smallest concatenation of `a` whose length is at least n.
     3) If tmp == b, return count (exact match).
     4) Use a substring-search (here called rabinKarp) to check whether b occurs in tmp:
         - If found, return count.
     5) Append one more `a` to tmp (tmp now equals the minimal-length string plus one more copy).
         - Increment count accordingly (count++).
     6) Check again with rabinKarp(tmp, b); if found, return count.
     7) If not found in either tmp or tmp + a, return -1.

     Why this works / correctness sketch:
     - Any occurrence of `b` in repeated `a` must begin somewhere within the first `count` copies of `a`
         or overlap into the next copy by at most |a| characters. Therefore checking tmp and tmp+a covers all
         possible placements of b that could appear when repeating a sufficient number of times.
     - We choose the minimal `count` such that tmp.length() >= n; that ensures we return the smallest k if an
         occurrence exists.

     Complexity:
     - Let m = |a|, n = |b|.
     - Building tmp: we append `a` ceil(n / m) times → O(m * ceil(n/m)) = O(n + m) time to build strings (amortized).
     - Each substring check (rabinKarp) typically runs in O(|tmp|) average-case (rolling hash), and worst-case O(|tmp| * n) if pathological collisions and verifying; but with good hashing average is linear.
     - We call rabinKarp at most twice on strings of length O(n + m), so overall average time ≈ O(n + m).
     - Space: tmp takes O(n + m) space (we explicitly build the repeated string). Auxiliary space O(1) (ignoring rabinKarp internals and output).

     Edge cases handled by the steps:
     - If a == b (short-circuit by detection when tmp==b or rabinKarp finds it).
     - If |a| >= |b| then the while loop may append a only once; still checks tmp and tmp+a as needed.
     - If no possible repetition can contain b, returns -1.

     Note:
     - This function assumes an external function `rabinKarp(string&, string&)` exists which returns true if the
         second string is a substring of the first (or equivalent boolean indicator). Do not change rabinKarp's behavior.
     */

    int repeatedStringMatch(string a, string b)
    {

        int m = a.size(); // length of string a
        int n = b.size(); // length of string b

        int count = 0;   // how many copies of `a` we've appended to tmp
        string tmp = ""; // repeated string built from copies of `a`

        // Step 1: Append `a` until tmp.length() >= n (so tmp is long enough to possibly contain b)
        while (m * count < n)
        {
            tmp.append(a); // append one copy of a
            count++;       // increment count of copies
        }

        // Step 2: If tmp exactly equals b, it's contained and we can return current count
        if (tmp == b)
            return count;

        // Step 3: If b is a substring of tmp, return current count
        if (rabinKarp(tmp, b))
            return count;

        // Step 4: Append one more copy of a to cover cases where b overlaps the boundary
        tmp.append(a);
        count++;

        // Step 5: If b is a substring of the extended tmp, return updated count
        if (rabinKarp(tmp, b))
            return count;

        // Step 6: If none matched, b cannot be contained by any repetition count of a
        return -1;
    }
};

int main()
{
    return 0;
}