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


*/

//-------------------------------------------------------------------------------
// 1. Title: Count palindromic subsequence in given string
//-------------------------------------------------------------------------------

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
            return dp[i][j] = (ignoreLeft + ignoreRight + 1) % MOD;
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

//-------------------------------------------------------------------------------
// 2. Title: Count Palindromic Subsequences with string length constraint
//-------------------------------------------------------------------------------
/**
 * Problem: 2484. Count Palindromic Subsequences (Length 5)
 * --------------------------------------------------------
 * 1. Idea of the Solution:
 * A length-5 palindrome looks like: [d1, d2, d3, d2, d1].
 * We can fix the middle character (d3) at index 'i'.
 * Then, we just need to count how many times the sequence "d1, d2" appears
 * to the left of 'i', and how many times "d2, d1" appears to the right of 'i'.
 * We multiply these counts together for all 100 possible (d1, d2) digit pairs.
 * * 2. Prefix and Suffix Arrays:
 * - suf_pair[i][d1][d2]: The number of times the subsequence (d1, d2)
 * appears strictly in the suffix from s[i...n-1].
 * - pre_pair[d1][d2]: The number of times the subsequence (d1, d2)
 * appears strictly in the prefix processed so far.
 * * 3. The Math Step (At center 'i'):
 * For every digit combination d1 (0-9) and d2 (0-9):
 * palindromes += (pre_pair[d1][d2] * suf_pair[i+1][d2][d1])
 * * 4. Time and Space Complexity:
 * - Time: O(N * 100). We do a linear scan, doing 100 operations per character.
 * - Space: O(N * 100) to store the suffix pairs for every index.
 */

#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int countPalindromes(string s)
    {
        int n = s.length();
        long long MOD = 1e9 + 7;

        // If string is smaller than 5, impossible to form a length 5 palindrome
        if (n < 5)
            return 0;

        // suf_pair[i][d1][d2] stores the count of subsequence "d1 d2" in s[i...n-1]
        vector<vector<vector<long long>>> suf_pair(n + 1, vector<vector<long long>>(10, vector<long long>(10, 0)));
        vector<long long> suf_cnt(10, 0); // Temporary array to count single digits on the right

        // Step 1: Build the Suffix Array (Right to Left)
        for (int i = n - 1; i >= 0; i--)
        {
            int curr = s[i] - '0';

            // First, copy the pairs from the previous index
            for (int d1 = 0; d1 < 10; d1++)
            {
                for (int d2 = 0; d2 < 10; d2++)
                {
                    suf_pair[i][d1][d2] = suf_pair[i + 1][d1][d2];
                }
            }

            // Second, add the NEW pairs formed by 'curr' acting as the first digit (d1)
            // It pairs with every digit 'd2' we have seen to the right so far!
            for (int d2 = 0; d2 < 10; d2++)
            {
                suf_pair[i][curr][d2] = (suf_pair[i][curr][d2] + suf_cnt[d2]) % MOD;
            }

            // Finally, update the single digit count for the right side
            suf_cnt[curr]++;
        }

        long long total_palindromes = 0;

        // pre_pair[d1][d2] stores the count of subsequence "d1 d2" seen so far on the left
        vector<vector<long long>> pre_pair(10, vector<long long>(10, 0));
        vector<long long> pre_cnt(10, 0); // Temporary array to count single digits on the left

        // Step 2: Build Prefix on the fly and Calculate Answer (Left to Right)
        for (int i = 0; i < n; i++)
        {
            int curr = s[i] - '0';

            // If 'i' is a valid center (needs at least 2 chars on left, 2 on right)
            if (i >= 2 && i <= n - 3)
            {
                // Try all 100 possible digit pairs for the outer shell
                for (int d1 = 0; d1 < 10; d1++)
                {
                    for (int d2 = 0; d2 < 10; d2++)
                    {

                        // left_ways  = count of "d1 d2" on the left
                        // right_ways = count of "d2 d1" on the right
                        long long left_ways = pre_pair[d1][d2];
                        long long right_ways = suf_pair[i + 1][d2][d1];

                        // Multiply combinations and add to total
                        total_palindromes = (total_palindromes + (left_ways * right_ways)) % MOD;
                    }
                }
            }

            // Update the Prefix pairs array with the new character acting as 'd2'
            // It pairs with every digit 'd1' we have seen to the left so far!
            for (int d1 = 0; d1 < 10; d1++)
            {
                pre_pair[d1][curr] = (pre_pair[d1][curr] + pre_cnt[d1]) % MOD;
            }

            // Finally, update the single digit count for the left side
            pre_cnt[curr]++;
        }

        return static_cast<int>(total_palindromes);
    }
};

int main()
{
    return 0;
}
