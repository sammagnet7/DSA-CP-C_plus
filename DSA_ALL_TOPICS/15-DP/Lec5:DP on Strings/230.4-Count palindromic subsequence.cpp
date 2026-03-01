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

1. Title: Count palindromic subsequence in given string

Links:
https://www.youtube.com/watch?v=9hsnkf0MRhQ&t=3s
https://www.youtube.com/watch?v=JbeHChnm09Q&t=16s
https://www.geeksforgeeks.org/problems/count-palindromic-subsequences/1


Problem statement:
Given a string s, you have to find the number of palindromic subsequences (need not necessarily be distinct) present in the string s.

Examples:
Input: s = "abcd"
Output: 4
Explanation: palindromic subsequence are : 'a' ,'b', 'c' ,'d'
Input: s = "aab"
Output: 4
Explanation: palindromic subsequence are : 'a', 'a', 'b', 'aa'
Input: s = "b"
Output: 1
Explanation: palindromic subsequence are : 'b'
Constraints:
1<= s.size() <=30



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Count Palindromic Subsequences with string length constraint

Links:
https://leetcode.com/problems/count-palindromic-subsequences/description/


Problem statement:
Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 10^9 + 7.

Note:
A string is palindromic if it reads the same forward and backward.
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

Examples:
    Example 1:
    Input: s = "103301"
    Output: 2
    Explanation:
    There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301".
    Two of them (both equal to "10301") are palindromic.

    Example 2:
    Input: s = "0000000"
    Output: 21
    Explanation: All 21 subsequences are "00000", which is palindromic.

    Example 3:
    Input: s = "9999900000"
    Output: 2
    Explanation: The only two palindromic subsequences are "99999" and "00000".


Constraints:
    1 <= s.length <= 104
    s consists of digits.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

3. Title: Unique Length-3 Palindromic Subsequences

Links:
https://www.youtube.com/watch?v=EdEvy2_o5OE
https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/


Problem statement:
Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".


Example 1:
Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")

Example 2:
Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".

Example 3:
Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")


Constraints:
3 <= s.length <= 105
s consists of only lowercase English letters.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Count palindromic subsequence in given string
//-------------------------------------------------------------------------------

// ------------------------------
// Approach 1: Recursive
// ------------------------------

/**
 * Problem: Count Palindromic Subsequences
 *
 * * 1. Idea of the solution:
 * ------------------------
 * We use Interval Dynamic Programming. By maintaining two pointers, 'i' at the start
 * and 'j' at the end of a substring, we evaluate smaller and smaller intervals.
 * We build the total count using the Inclusion-Exclusion principle, combining the
 * results of substrings that exclude the left character, exclude the right character,
 * or exclude both.
 *
 * * 2. What DP[i][j] signifies:
 * ---------------------------
 * DP[i][j] represents the total number of palindromic subsequences (not necessarily
 * distinct) present strictly within the substring s[i...j].
 *
 * * 3. Derivation of the DP formula (Case-Wise):
 * --------------------------------------------
 * Let DP(i, j) be the count of palindromes in s[i...j]. We look at the outer characters:
 * * CASE 1: s[i] != s[j] (Outer characters do NOT match)
 * - They cannot form a palindrome together.
 * - We take the palindromes formed by ignoring the left char: DP(i+1, j)
 * - We take the palindromes formed by ignoring the right char: DP(i, j-1)
 * - If we just add them, we double-count the palindromes in the strictly middle
 * section (which ignores BOTH outer chars). So, we must subtract the overlap.
 * - Formula: DP(i, j) = DP(i+1, j) + DP(i, j-1) - DP(i+1, j-1)
 * * CASE 2: s[i] == s[j] (Outer characters DO match)
 * - We still have all the palindromes from Case 1: [DP(i+1, j) + DP(i, j-1) - DP(i+1, j-1)]
 * - PLUS, we can take the matching outer characters (s[i] and s[j]) and wrap them
 * around EVERY existing palindrome in the middle section to form brand new ones.
 * The number of palindromes in the middle section is: DP(i+1, j-1)
 * - PLUS, the outer characters form a new 2-letter palindrome just by themselves: 1
 * - Let's combine it all:
 * [DP(i+1, j) + DP(i, j-1) - DP(i+1, j-1)]  <-- (Base palindromes)
 * + DP(i+1, j-1)                            <-- (New wrapped palindromes)
 * + 1                                       <-- (The "s[i]s[j]" pair itself)
 * - Notice how the negative overlap and positive wrapped palindromes cancel out!
 * - Formula: DP(i, j) = DP(i+1, j) + DP(i, j-1) + 1
 *
 * * 4. Final DP Formula and Approach:
 * ---------------------------------
 * We shrink the interval recursively based on the derivation above.
 * - If s[i] == s[j]: rec(i+1, j) + rec(i, j-1) + 1
 * - If s[i] != s[j]: rec(i+1, j) + rec(i, j-1) - rec(i+1, j-1)
 *
 * * 5. Base Cases:
 * --------------
 * - if (i > j): Return 0. (The interval has crossed; empty string has 0 palindromes).
 * - if (i == j): Return 1. (A single character is always exactly 1 palindrome).
 *
 * * 6. Time and Space Complexity:
 * -----------------------------
 * - Time Complexity: O(N^2). There are N^2 possible pairs of (i, j). Memoization
 * ensures we calculate each state exactly once.
 * - Space Complexity: O(N^2) for the 2D DP matrix + O(N) for the maximum depth
 * of the recursion stack.
 *
 * * 7. Why +MOD before %MOD :
 * ------------------------
 * Let's say our modulo is 100.
 * In Case 1 (s[i] != s[j]), we subtract the overlap. Because we apply modulo at every
 * recursive step to prevent overflow, our DP table stores remainders, not true values.
 * If (dp_Left + dp_Right) happens to be smaller than dp_Overlap, the subtraction
 * results in a negative number (e.g., 20 + 10 - 90 = -60).
 * In C++, (-60 % 100) results in -60.
 * By explicitly adding MOD before the final modulo operation, we safely wrap the
 * negative remainder back into the correct positive space:
 * (-60 + 100) % 100 = 40.
 */

class Solution
{
private:
    long long MOD = 1e9 + 7;

    long long rec(int i, int j, string &s, vector<vector<long long>> &dp)
    {

        // Base Case 1: Empty string (pointers crossed)
        if (i > j)
        {
            return 0;
        }

        // Base Case 2: Single character
        if (i == j)
        {
            return 1;
        }

        // Memoization Check
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // Step 1: Calculate the subproblems
        long long ignoreLeft = rec(i + 1, j, s, dp) % MOD;
        long long ignoreRight = rec(i, j - 1, s, dp) % MOD;
        long long overlap = rec(i + 1, j - 1, s, dp) % MOD;

        // Step 2: Apply the correct formula based on character match
        if (s[i] == s[j])
        {
            // Overlap naturally cancels out, add 1 for the new pair
            return dp[i][j] = (ignoreLeft + ignoreRight + 1) % MOD; // 1+ ( (ignoreLeft + ignoreRight - overlap) + overlap )
        }
        else
        {
            // Inclusion-Exclusion Principle with the C++ negative modulo fix
            return dp[i][j] = (ignoreLeft + ignoreRight - overlap + MOD) % MOD;
        }
    }

public:
    long long countPS(string str)
    {
        int n = str.length();

        // Initialize an N x N DP table with -1
        vector<vector<long long>> dp(n, vector<long long>(n, -1));

        // Start the recursive count from the full bounds of the string
        return rec(0, n - 1, str, dp);
    }
};

// ------------------------------
// Approach 2: Iterative
// ------------------------------

/**
 * Problem: Count Palindromic Subsequences
 * ---------------------------------------
 * Approach: Bottom-Up Interval Dynamic Programming
 * * 1. What DP[l][r] signifies:
 * dp[l][r] stores the total number of palindromic subsequences strictly
 * within the substring str[l...r].
 * * 2. Why we loop by 'len' first:
 * In Interval DP, larger intervals depend on the results of smaller,
 * nested intervals. If we looped normally (l from 0 to n, r from l to n),
 * we would ask for dp[l+1][r] before it was even calculated!
 * By looping by 'len' (2, 3, 4...), we guarantee all smaller subproblems
 * are fully solved before we expand our window.
 * * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N^2) - Two nested loops evaluating every possible interval.
 * Space Complexity: O(N^2) - To store the 2D DP table. No recursion stack overhead!
 */

class Solution
{
private:
    long long MOD = 1e9 + 7;

public:
    long long countPS(string str)
    {
        int n = str.length();

        // Initialize an N x N DP table with 0.
        // Using 'long long' internally to prevent overflow during additions before the modulo.
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Base Case: Every single character is a palindrome of length 1.
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = 1;
        }

        // Step 1: Iterate over the length of the interval (from 2 up to the full string length N)
        for (int len = 2; len <= n; ++len)
        {

            // Step 2: Slide the starting pointer 'l' across the string
            for (int l = 0; l <= (n - len); ++l)
            {

                // Calculate the ending pointer 'r' based on the start and current length
                int r = (l + len - 1);

                // Fetch the previously computed subproblems.
                // (Applying % MOD here is optional but safe, as the table already stores modded values)
                long long ignoreLeft = dp[l + 1][r] % MOD;
                long long ignoreRight = dp[l][r - 1] % MOD;
                long long overlap = dp[l + 1][r - 1] % MOD;

                // Case 1: Outer characters match
                if (str[l] == str[r])
                {
                    // Logic breakdown:
                    // 1 (the new pair itself)
                    // + (ignoreLeft + ignoreRight - overlap) [existing palindromes without pairing]
                    // + overlap [new palindromes formed by wrapping the outer matching chars around the middle]
                    // The 'overlap' mathematically cancels out!
                    dp[l][r] = (ignoreLeft + ignoreRight + 1) % MOD;
                }
                // Case 2: Outer characters do NOT match
                else
                {
                    // Inclusion-Exclusion Principle:
                    // Add both subproblems, but subtract the intersecting middle part
                    // to prevent counting the middle palindromes twice.
                    // Critical Fix: Add '+ MOD' before the final modulo because
                    // (ignoreLeft + ignoreRight) could be smaller than 'overlap', yielding a negative remainder in C++.
                    dp[l][r] = (ignoreLeft + ignoreRight - overlap + MOD) % MOD;
                }
            }
        }

        // The answer for the entire string is located at the interval covering index 0 to n-1
        return dp[0][n - 1];
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Count Palindromic Subsequences with fixed length
//-------------------------------------------------------------------------------

// --------------------------------------------------------------------
// Approach: Simultaneous Prefix/Suffix Existence Arrays
// --------------------------------------------------------------------

/**
 * Problem: 2484. Count Palindromic Subsequences (Length 5)
 * --------------------------------------------------------
 *
 * 1. Idea of the Solution:
 * A length-5 palindrome always follows the exact pattern: [a, b, c, b, a].
 * - 'c' is the center pivot at some index 'i'.
 * - "a b" is a length-2 subsequence strictly to the left of 'i'.
 * - "b a" is a length-2 subsequence strictly to the right of 'i'.
 * Since the string consists only of digits (0-9), there are only 100 possible
 * (a, b) combinations. If we know how many times "a b" appears to the left of 'i',
 * and how many times "b a" appears to the right of 'i', we can multiply them
 * to get the total number of valid palindromes centered at 'i' for those digits.
 *
 * * 2. Step-by-Step Approach:
 * - Step 1 (State Initialization): We use 3D arrays `left` and `right`.
 * `left[i][a][b]` stores the count of subsequence "a b" ending strictly before index `i`.
 * `right[i][b][a]` stores the count of subsequence "b a" starting strictly after index `i`.
 *
 * - Step 2 (Simultaneous Precomputation): Instead of separate left-to-right
 * and right-to-left passes, we use two pointers (`l` and `r`) to build both
 * the prefix and suffix matrices simultaneously in a single loop.
 *
 * - Step 3 (History Carry-Over): Before adding new pairs formed by the current
 * character, we deep-copy the 10x10 matrix from the previous index so we
 * don't lose previously formed pairs.
 *
 * - Step 4 (Combinatorial Counting): We iterate through every valid center pivot 'i'.
 * For each pivot, we iterate through all 100 (a, b) pairs, multiplying the
 * left occurrences by the right occurrences.
 *
 * * 3. Time and Space Complexity:
 * - Time Complexity: O(N * 100) -> O(N)
 * We do one pass of size N doing 100 operations, and a second pass of size N
 * doing 100 operations. This is strictly linear time.
 * - Space Complexity: O(N * 100) -> O(N)
 * The two 3D vectors take up `N * 10 * 10 * 8 bytes`. For N = 10,000,
 * this is roughly 1.6 MB, safely avoiding the Memory Limit Exceeded errors
 * of traditional O(N^2) Interval DP.
 *
 */

class Solution
{
private:
    const long long MOD = 1e9 + 7;

public:
    int countPalindromes(string s)
    {

        int N = s.length();

        // A string shorter than 5 characters cannot contain a length-5 palindrome
        if (N < 5)
            return 0;

        // lSeen[k] and rSeen[k] track the frequencies of single digits seen so far
        vector<long long> lSeen(10, 0), rSeen(10, 0);

        // 3D matrices for tracking length-2 subsequences.
        // left[i][a][b] = count of "a b" strictly to the left of index i
        vector<vector<vector<long long>>> left(N, vector<vector<long long>>(10, vector<long long>(10, 0)));
        vector<vector<vector<long long>>> right(N, vector<vector<long long>>(10, vector<long long>(10, 0)));

        // --- PHASE 1: SIMULTANEOUS PRECOMPUTATION ---
        // We iterate l from 0 up to N-2. The r pointer mirrors it from the back.
        for (int l = 0; l < N - 1; ++l)
        {

            int r = N - 1 - l;

            int curL = s[l] - '0';
            int curR = s[r] - '0';

            // Critical Step: Deep copy the entire 10x10 history to the NEXT index state.
            // This ensures pairs formed earlier are safely carried forward.
            left[l + 1] = left[l];
            right[r - 1] = right[r];

            // Form new pairs using the current characters acting as the SECOND digit
            for (int k = 0; k < 10; ++k)
            {

                // If we have seen digit 'k' on the left, we can form a new "k curL" pair
                if (lSeen[k] > 0)
                {
                    left[l + 1][k][curL] = (left[l + 1][k][curL] + lSeen[k]) % MOD;
                }

                // If we have seen digit 'k' on the right, we can form a new "curR k" pair
                if (rSeen[k] > 0)
                {
                    right[r - 1][curR][k] = (right[r - 1][curR][k] + rSeen[k]) % MOD;
                }
            }

            // Update the single digit frequencies for the next iteration
            lSeen[curL]++;
            rSeen[curR]++;
        }

        long long ans = 0;

        // --- PHASE 2: PIVOT COUNTING ---
        // A valid center 'i' must have at least 2 characters on its left (starts at 2)
        // and at least 2 characters on its right (ends at N-3).
        for (int i = 2; i < N - 2; ++i)
        {

            // Check all 100 possible digit pairs (a, b)
            for (int a = 0; a < 10; ++a)
            {
                for (int b = 0; b < 10; ++b)
                {

                    // Fetch occurrences of "a b" strictly to the left of 'i'
                    long long leftCount = left[i][a][b];

                    // Fetch occurrences of "b a" strictly to the right of 'i'
                    long long rightCount = right[i][b][a];

                    // Multiply left choices by right choices and add to total ways
                    ans = (ans + (leftCount * rightCount) % MOD) % MOD;
                }
            }
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Unique Length-3 Palindromic Subsequences
//-------------------------------------------------------------------------------
// --------------------------------------------------------
// Approach 1: Simultaneous Prefix/Suffix Existence Arrays
// --------------------------------------------------------
class Solution
{
public:
    /**
     * Approach: Simultaneous Prefix/Suffix Existence Arrays
     * ----------------------------------------------------
     * 1. Idea of the Solution:
     * Every length-3 palindrome follows the structure: [outer, middle, outer].
     * If we treat every character at index 'i' as the 'middle' pivot, we just
     * need to know if a specific 'outer' character exists strictly to the left
     * of 'i' AND strictly to the right of 'i'. Since there are only 26 lowercase
     * letters, we can easily check all 26 possibilities for every pivot.
     * * 2. Step-by-Step Mechanics:
     * - Phase 1 (Existence Matrices): We build two 2D boolean arrays, `left` and `right`.
     * `left[i][c]` is true if character 'c' exists anywhere in s[0...i-1].
     * `right[i][c]` is true if character 'c' exists anywhere in s[i+1...N-1].
     * We build these simultaneously in a single O(N) pass using two pointers (l and r),
     * deep-copying the previous state to carry the history forward.
     * * - Phase 2 (Pivot Counting): We iterate 'i' from 1 to N-2. The character
     * s[i] becomes our 'mid'. We then loop through all 26 possible 'outer' letters.
     * If `left[i][outer]` AND `right[i][outer]` are both true, we have found a
     * valid palindrome: [outer, mid, outer].
     * * - Phase 3 (Deduplication): The problem asks for *unique* palindromes.
     * Instead of using a heavy string Hash Set, we use a 26x26 boolean matrix
     * `uniquePals[outer][mid]`. If we haven't seen this specific combination
     * before, we mark it true and increment our count.
     * * 3. Complexity:
     * - Time Complexity: O(N * 26) -> O(N)
     * Phase 1 does constant work (copying 26 booleans) N times.
     * Phase 2 does 26 checks for N pivots. The time is strictly linear.
     * - Space Complexity: O(N * 26) -> O(N)
     * The `left` and `right` tables store N arrays of 26 booleans. This takes
     * a fraction of a megabyte, safely operating well within memory limits.
     */
    int countPalindromicSubsequence(string s)
    {
        int N = s.length();

        // Edge case: strings smaller than 3 cannot have a length-3 subsequence
        if (N < 3)
            return 0;

        // DP Tables tracking existence (true/false) instead of counts
        vector<vector<bool>> left(N, vector<bool>(26, false));
        vector<vector<bool>> right(N, vector<bool>(26, false));

        // --- PHASE 1: PRECOMPUTE EXISTENCE ---
        for (int l = 0; l < N - 1; ++l)
        {
            int r = N - 1 - l;

            int curL = s[l] - 'a';
            int curR = s[r] - 'a';

            // Carry over the history of characters seen so far
            left[l + 1] = left[l];
            right[r - 1] = right[r];

            // Mark the current characters as 'seen' for the next boundaries
            left[l + 1][curL] = true;
            right[r - 1][curR] = true;
        }

        // 2D matrix to track unique [outer][middle] palindrome combinations
        vector<vector<bool>> uniquePals(26, vector<bool>(26, false));
        int totalUnique = 0;

        // --- PHASE 2: PIVOT COUNTING ---
        for (int i = 1; i < N - 1; ++i)
        {

            int mid = s[i] - 'a'; // The middle character of our palindrome

            // Check all 26 possible outer characters
            for (int outer = 0; outer < 26; ++outer)
            {

                // If the outer character exists on both sides of our pivot
                if (left[i][outer] && right[i][outer])
                {

                    // If we haven't recorded this specific palindrome yet
                    if (!uniquePals[outer][mid])
                    {
                        uniquePals[outer][mid] = true;
                        totalUnique++;
                    }
                }
            }
        }

        return totalUnique;
    }
};

// --------------------------------------------------------------------
// Approach 2: First and Last Occurrence
// --------------------------------------------------------------------
/**
 * Problem: 1930. Unique Length-3 Palindromic Subsequences
 * -------------------------------------------------------
 * Approach: First and Last Occurrence (The "Bread and Filling" Method)
 * 1. Idea of the Solution:
 * Since we strictly want length-3 palindromes, they must follow the format
 * [outer, middle, outer] (e.g., "aba", "zxz").
 * Because the string only consists of 26 lowercase English letters, we can
 * completely invert our thinking: instead of iterating through the string,
 * we iterate through the alphabet!
 * For every letter from 'a' to 'z', we find its VERY FIRST occurrence and
 * its VERY LAST occurrence in the string. These act as our "bread".
 * Any unique character that appears strictly between these two bounds can act
 * as the "filling" to create exactly one unique length-3 palindrome.
 * * 2. Step-by-Step Mechanics:
 * - Step 1: Loop through all 26 possible outer characters.https://www.youtube.com/watch?v=EdEvy2_o5OE
 * - Step 2: Use built-in `find_first_of` and `find_last_of` to get the bounds.
 * - Step 3: If the bounds exist and have a gap of at least 1 character between
 * them, we scan the substring inside the gap.
 * - Step 4: We use a boolean array of size 26 to count exactly how many unique
 * characters live inside that gap. We add this count to our total.
 * * 3. Complexity:
 * - Time Complexity: O(26 * N) -> O(N)
 * Finding the first and last occurrence takes O(N) time. Scanning the gap takes
 * at most O(N) time. We do this exactly 26 times. The time is strictly linear.
 * - Space Complexity: O(1)
 * We only allocate a boolean array of size 26 for counting the middle characters.
 * This requires literally a few bytes of memory, making it incredibly lightweight.
 */

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int countPalindromicSubsequence(string s)
    {

        int totalUnique = 0;

        // Step 1: Loop through all 26 possible outer characters ('a' to 'z')
        for (int i = 0; i < 26; ++i)
        {

            char outer = 'a' + i;

            // Step 2: Find the extreme boundaries of this character
            // string::find_first_of scans from left to right
            int first_idx = s.find_first_of(outer);

            // string::find_last_of scans from right to left
            int last_idx = s.find_last_of(outer);

            // Step 3: Check if valid boundaries exist.
            // We need a gap of at least 1 character (last_idx - first_idx > 1)
            // to place a middle character.
            if (first_idx != string::npos && last_idx != string::npos && last_idx - first_idx > 1)
            {

                // Track which middle characters we've already found in this gap
                vector<bool> unique_middle(26, false);
                int middle_count = 0;

                // Step 4: Scan the gap to count unique middle characters
                for (int j = first_idx + 1; j < last_idx; ++j)
                {

                    int char_idx = s[j] - 'a';

                    // If this is a new character for this specific gap
                    if (!unique_middle[char_idx])
                    {
                        unique_middle[char_idx] = true;
                        middle_count++;

                        // Optimization: If we found all 26 possible middle
                        // characters, no need to keep checking the rest of the gap!
                        if (middle_count == 26)
                        {
                            break;
                        }
                    }
                }

                // Add the unique palindromes formed by this 'outer' character
                totalUnique += middle_count;
            }
        }

        return totalUnique;
    }
};

int main()
{
    return 0;
}
