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
1 ≤ s.size() ≤ 106
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
//

class Solution
{
public:
    /*
     * Problem: Longest Proper Prefix which is also Suffix (LPS)
     * --------------------------------------------------------
     * Given a string `s`, find the longest prefix which is also a suffix
     * (but not equal to the entire string itself). Return the actual substring.
     */

    /*
     * Approach 1: Brute Force Prefix-Suffix Comparison
     * ------------------------------------------------
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

    /*
     * Approach 2: KMP Prefix Function
     * -------------------------------
     * Intuition:
     *   - Use KMP preprocessing (LPS array) to efficiently compute
     *     the longest proper prefix that is also a suffix.
     *   - LPS[i] stores the length of the longest proper prefix of s[0..i]
     *     which is also a suffix.
     *   - At the end, LPS[n-1] gives the length of the longest proper prefix-suffix.
     *   - Return the substring of length LPS[n-1] from the start of the string.
     *
     * Time Complexity: O(n)
     *   - Each index is processed at most twice.
     * Space Complexity: O(n)
     *   - Extra LPS array of size n.
     */

    string longestPrefixSuffix(string &s)
    {

        int n = s.size();

        vector<int> LPS(n, 0); // LPS[i] = length of longest prefix-suffix for s[0..i]

        int i = 1; // current position in string
        int j = 0; // length of matched prefix so far

        while (i < n)
        {
            if (s[i] == s[j])
            {
                // extend the prefix match
                LPS[i] = j + 1;
                i++;
                j++;
            }
            else
            {
                if (j == 0)
                {
                    // no prefix match, move forward in string
                    i++;
                }
                else
                {
                    // fallback to next best prefix length
                    j = LPS[j - 1];
                }
            }
        }

        // return substring of length LPS[n-1]
        return s.substr(0, LPS[n - 1]);
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