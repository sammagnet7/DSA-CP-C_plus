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
You are given a string s. You can convert s to a palindrome by adding characters in front of it.

Return the shortest palindrome you can find by performing this transformation.

Examples:
    Example 1:
    Input: s = "aacecaaa"
    Output: "aaacecaaa"

    Example 2:
    Input: s = "abcd"
    Output: "dcbabcd"


Constraints:
0 <= s.length <= 5 * 104
s consists of lowercase English letters only.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title:


Links:


Problem statement:


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Shortest Palindrome
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // longestPrefixSuffix(s)
    //
    // Purpose / Idea:
    //   - Compute the KMP prefix-function (also called LPS array) for the string s.
    //   - LPS[i] = length of the longest proper prefix of s[0..i] that is also a
    //     suffix of s[0..i].
    //   - We return LPS[n-1], which is the length of the longest proper prefix
    //     of the whole string that is also its suffix.
    //
    // Why we need it:
    //   - This prefix-function lets us know how much of the prefix matches a
    //     suffix, so we can quickly reuse that information instead of re-checking
    //     characters from the beginning when mismatches occur.
    //
    // Complexity:
    //   - Time: O(n) where n = s.length(). Each index is visited a constant
    //     number of times because i only increases and j only falls back via
    //     previously computed LPS values.
    //   - Space: O(n) for the LPS array.
    // ------------------------------------------------------------------------
    int longestPrefixSuffix(string &s)
    {
        int n = s.size();

        // LPS[i] = length of longest proper prefix that is also a suffix for s[0..i]
        vector<int> LPS(n, 0);

        int i = 1; // current index in `s` we are computing LPS for (start at 1)
        int j = 0; // length of current matched prefix (also index into prefix)

        // Build LPS array using classic KMP preprocessing
        while (i < n)
        {
            if (s[i] == s[j])
            {
                // We can extend the current matched prefix by 1
                LPS[i] = j + 1; // matched prefix length ending at i is j+1
                i++;            // move to next character in s
                j++;            // matched prefix length increased
            }
            else
            {
                if (j == 0)
                {
                    // No current match to fallback to, so LPS[i] stays 0
                    // Move forward in string
                    i++;
                }
                else
                {
                    // Fallback: try a shorter previously computed border
                    // LPS[j-1] gives the next best candidate for a border length
                    j = LPS[j - 1];
                }
            }
        }

        // The value for the whole string is stored at LPS[n-1]
        return LPS[n - 1];
    }

    // ------------------------------------------------------------------------
    // shortestPalindrome(s)
    //
    // Problem:
    //   - Given a string s, create the shortest palindrome by adding characters
    //     in front of s.
    //
    // Intuition / Approach:
    //   - If the longest prefix of s that is also a palindrome (i.e., matches a
    //     prefix of the reversed string) has length L, then the minimal addition
    //     to front is the reverse of the remaining suffix s[L..n-1].
    //
    //   - Construct a helper string `probstr = s + '$' + rev(s)` where '$' is a
    //     delimiter not present in s. Compute the LPS of probstr.
    //
    //   - Explanation:
    //       * Consider the string s and its reverse rev.
    //       * When we compute the LPS of s + '$' + rev, the LPS at the last
    //         position tells us the longest prefix of s that matches a suffix
    //         of rev, which is equivalent to the longest prefix of s that is
    //         a palindrome (because matching a suffix of rev means reading the
    //         same characters backwards).
    //       * Let L = longestPrefixSuffix(probstr). Then the suffix of s
    //         starting at index L (i.e., s[L..n-1]) is the part that is not
    //         already a palindrome prefix. We reverse that suffix and prepend it.
    //
    // Steps:
    //   1. rev = reverse(s)
    //   2. probstr = s + '$' + rev
    //   3. L = longestPrefixSuffix(probstr)
    //   4. appendLen = n - L (characters from rev to prepend)
    //   5. result = rev.substr(0, appendLen) + s
    //
    // Complexity:
    //   - Let n = s.length().
    //   - Constructing rev and probstr: O(n)
    //   - longestPrefixSuffix(probstr): runs in O(n) (probstr has length 2n+1)
    //   - Building the final string: O(n)
    //   - Overall Time: O(n)
    //   - Space: O(n) for rev and probstr and the LPS array (auxiliary O(n))
    // ------------------------------------------------------------------------
    string shortestPalindrome(string s)
    {

        int n = s.size();

        // rev = reverse of s
        string rev = s;
        reverse(rev.begin(), rev.end());

        // probstr combines s and rev with a delimiter to avoid cross matches
        // that span both strings erroneously.
        string probstr = s + "$" + rev;

        // L gives length of longest prefix of `s` that is also a prefix of `rev`
        // when considering the combined string — equivalently, the length of the
        // longest palindrome prefix of s.
        int exitingPalLen = longestPrefixSuffix(probstr);

        // Number of characters from rev that need to be prepended
        int appendLen = n - exitingPalLen;

        // Take first appendLen chars from rev and prepend to s
        string appendStr = rev.substr(0, appendLen);

        // Final answer: characters to prepend + original string
        string ans = appendStr + s;

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------
//

int main()
{
    return 0;
}