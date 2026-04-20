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

1. Title: Longest Prefix Which is Suffix

Links:
https://takeuforward.org/plus/dsa/problems/longest-happy-prefix?tab=editorial
https://www.naukri.com/code360/problems/longest-prefix-which-is-suffix_3146849?leftPanelTabValue=PROBLEM
https://www.geeksforgeeks.org/problems/longest-prefix-suffix2527/1
https://leetcode.com/problems/longest-happy-prefix/description/


Problem statement:
A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s, of lowercase english alphabets, find the length of the longest proper prefix which is also a suffix.
Note: Prefix and suffix can be overlapping but they should not be equal to the entire string.

Examples :
    Input: s = "abab"
    Output: 2
    Explanation: The string "ab" is the longest prefix and suffix.

    Input: s = "aabcdaabc"
    Output: 4
    Explanation: The string "aabc" is the longest prefix and suffix.

    Input: s = "aaaa"
    Output: 3
    Explanation: "aaa" is the longest prefix and suffix.

Constraints:
1 ≤ s.size() ≤ 10^6
s contains only lowercase English alphabets.


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
// 1. Title: Longest Prefix Which is Suffix
//-------------------------------------------------------------------------------

// ------------------------------------------------
// Approach 1: Brute Force [Slower]
// ------------------------------------------------

class Solution
{
public:
    /*
     * Intuition:
     *   - Try all possible lengths of proper prefix (from n-1 down to 1).
     *   - For each length `len`, compare prefix s[0..len-1] with suffix s[n-len..n-1].
     *   - The first match found (largest `len`) is the longest prefix-suffix.
     *   - If no match is found, return "".
     *
     * Time Complexity: O(n^2)
     *   - substring extraction + comparison takes O(len), repeated up to n times.
     * Space Complexity: O(1)
     *   - No extra space used beyond loop variables.
     */

    string longestPrefixSuffix(string &s)
    {
        int n = s.size();

        // longest proper prefix which is also suffix (not equal to whole string)
        for (int len = n - 1; len >= 1; --len)
        {
            // compare prefix s[0..len-1] with suffix s[n-len .. n-1]
            if (s.substr(0, len) == s.substr(n - len, len))
                return s.substr(0, len); // return actual substring
        }

        return ""; // no prefix-suffix found
    }
};

// ------------------------------------------------
// Approach 2: KMP Prefix Function [OPTIMAL]
// ------------------------------------------------

using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the longest prefix of a string that is also a suffix (excluding the full string).
     * * * * * 🧠 INTUITION (The LPS Array Magic):
     * The problem asks for the longest prefix that is also a suffix. This is the
     * exact mathematical definition of the final value in a KMP LPS array!
     * 1. We build the LPS array for the entire string using the standard KMP Two-Pointer method.
     * 2. The value at the very last index, `LPS[n-1]`, gives us the exact length of this
     * longest prefix-suffix.
     * 3. We simply return the substring from the start of the string up to that length.
     * * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string. We iterate through
     * the string exactly once to build the LPS array, and `substr` takes O(K) where K is the prefix length.
     * - Space Complexity: O(N) auxiliary space to store the LPS array.
     * * @param s The input string to analyze.
     * @return The longest prefix that is also a suffix, or an empty string if none exists.
     */
    string longestPrefix(string s)
    {

        int n = s.length();

        // =========================================================
        // PHASE 1: PRE-COMPUTE THE LPS ARRAY
        // =========================================================
        vector<int> LPS(n, 0);

        int len = 0; // Length Pointer: Tracks the matching prefix length
        int i = 1;   // Right Index: Scans the suffix of the string

        while (i < n)
        {

            if (s[len] == s[i])
            {
                // Match found: Expand the known prefix length
                ++len;
                LPS[i] = len;
                ++i;
            }
            else
            {
                if (len != 0)
                {
                    // Mismatch: Slide the `len` pointer backward to the last safe prefix length.
                    // Note: 'i' is NOT incremented, so we stay frozen on this character
                    // to re-evaluate it against the new, smaller prefix.
                    len = LPS[len - 1];
                }
                else
                {
                    // `len` is 0. No prefix matches this character. Advance 'i'.
                    ++i;
                }
            }
        }

        // =========================================================
        // PHASE 2: EXTRACT THE LONGEST PREFIX-SUFFIX
        // =========================================================

        // If the LPS value at the last character is 0, no valid border exists.
        if (LPS[n - 1] == 0)
        {
            return "";
        }
        else
        {
            // Extract the substring from index 0 up to the length found in LPS[n-1]
            int lhp_len = LPS[n - 1];
            return s.substr(0, lhp_len);
        }
    }
};

int main()
{
    return 0;
}