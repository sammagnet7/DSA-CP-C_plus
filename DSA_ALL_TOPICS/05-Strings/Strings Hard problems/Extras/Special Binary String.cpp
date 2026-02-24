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

1. Title: Special Binary String

Links:
https://leetcode.com/problems/special-binary-string/description/


Problem statement:
Special binary strings are binary strings with the following two properties:

The number of 0's is equal to the number of 1's.
Every prefix of the binary string has at least as many 1's as 0's.
You are given a special binary string s.

A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.

Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.



Example 1:
Input: s = "11011000"
Output: "11100100"
Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.

Example 2:
Input: s = "10"
Output: "10"


Constraints:
1 <= s.length <= 50
s[i] is either '0' or '1'.
s is a special binary string.


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Special Binary String
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /*
     * METHOD: rec (Recursive Helper)
     * ------------------------------
     * APPROACH: Divide & Conquer with Index Pointers
     * Instead of creating new substrings for every recursive call, we pass the
     * original string by reference and use left (l) and right (r) bounds.
     */
    string rec(int l, int r, string &s)
    {

        // Base Case: If the bounds cross or are empty, return an empty string
        if (l >= r)
        {
            return "";
        }

        int sum = 0;   // Balance tracker
        int start = l; // Marks the beginning of the current valid component

        vector<string> pieces;

        // Iterate through the current bounds [l, r]
        for (int i = l; i <= r; ++i)
        {

            // Track balance: '0' increases sum, '1' decreases sum.
            // When sum == 0, we have an equal number of 1s and 0s.
            if (s[i] == '0')
            {
                ++sum;
            }
            else
            {
                --sum;
            }

            // We found a completely balanced special binary string
            if (sum == 0)
            {

                // Recursively process the inner part of the string.
                // start+1 to i-1 skips the outer '1' and '0'.
                string tmp = rec(start + 1, i - 1, s);

                // Reconstruct the string: outer '1' + maximized inner + outer '0'
                pieces.push_back(s[start] + tmp + s[i]);

                // Move the start pointer to the beginning of the next component
                start = i + 1;
            }
        }

        // Sort all top-level special components in descending order
        sort(pieces.begin(), pieces.end(), greater<string>());

        string mod = "";

        // Concatenate the sorted components to form the largest possible string
        // (Using a range-based for loop for cleaner syntax)
        for (const string &specialStr : pieces)
        {
            mod += specialStr;
        }

        return mod;
    }

    /*
     * METHOD: makeLargestSpecial (Entry Point)
     */
    string makeLargestSpecial(string s)
    {
        // Kick off recursion using the full bounds of the string
        return rec(0, s.length() - 1, s);
    }
};

int main()
{
    return 0;
}