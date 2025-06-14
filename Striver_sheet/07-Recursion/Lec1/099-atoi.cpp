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

using namespace std;

/*
https://leetcode.com/problems/string-to-integer-atoi/

Problem statement:
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.

The algorithm for myAtoi(string s) is as follows:

Whitespace: Ignore any leading whitespace (" ").
Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
Return the integer as the final result.

Examples:

Example 1:
Input: s = "42"
Output: 42
Explanation:
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^

Example 2:
Input: s = " -042"
Output: -42
Explanation:
Step 1: "   -042" (leading whitespace is read and ignored)
            ^
Step 2: "   -042" ('-' is read, so the result should be negative)
             ^
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
               ^

Example 3:
Input: s = "1337c0d3"
Output: 1337
Explanation:
Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
         ^
Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)
             ^

Example 4:
Input: s = "0-1"
Output: 0
Explanation:
Step 1: "0-1" (no characters read because there is no leading whitespace)
         ^
Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)
          ^

Example 5:
Input: s = "words and 987"
Output: 0
Explanation:
Reading stops at the first non-digit character 'w'.

*/

class Solution
{
public:
    //-----------------------------------------------------------------------

    // Optimal approach: Recursive
    // Time: O(N)
    // Space: O(1)
    int myAtoi(string s)
    {

        int N = s.size();
        int ans = 0;
        int idx = 0;
        bool isNeg = false;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == ' ')
                idx++;
            else
                break;
        }

        if (s[idx] == '-')
        {
            isNeg = true;
            idx++;
        }
        else if (s[idx] == '+')
        {
            isNeg = false;
            idx++;
        }

        for (int i = idx; i < N; i++)
        {

            if (isdigit(s[i]))
            {

                int curDigit = s[i] - '0';
                bool isOverflow = (ans > INT_MAX / 10) || (ans == INT_MAX / 10 && curDigit > 7);

                if (ans == 0)
                    ans = curDigit; // convert digit char to decimal int by subtracting '0'

                // Handling integer overflow
                else if (isOverflow)
                {
                    return isNeg ? INT_MIN : INT_MAX;
                }

                else
                    ans = (ans * 10) + curDigit;

                // Handle int overflow
                // if(isNeg && -ans<INT_MIN) return INT_MIN;
                // else if(!isNeg && ans>INT_MAX) return INT_MAX;
            }
            else
                break;
        }

        return isNeg ? -ans : ans;
    }

    // --------------------------------------------------------------------
    // recursive approach: complex

    // int recursiveAtoI(string s, int i, int sign, int prev, bool digitStarted)
    // {

    //     if (i == s.size())
    //         return (prev * sign);
    //     if (digitStarted && !isdigit(s[i]))
    //         return (prev * sign);

    //     if (s[i] == ' ')
    //         return recursiveAtoI(s, ++i, sign, prev, digitStarted);
    //     if (s[i] == '+')
    //     {
    //         digitStarted = true;
    //         return recursiveAtoI(s, ++i, 1, prev, digitStarted);
    //     }
    //     if (s[i] == '-')
    //     {
    //         digitStarted = true;
    //         return recursiveAtoI(s, ++i, -1, prev, digitStarted);
    //     }
    //     if (!digitStarted && s[i] == '0')
    //     {
    //         digitStarted = true;
    //         return recursiveAtoI(s, ++i, sign, prev, digitStarted);
    //     }
    //     if (!isdigit(s[i]))
    //         return (prev * sign);

    //     if (isdigit(s[i]))
    //         digitStarted = true;

    //     int cur = s[i] - '0';

    //     if ((prev > (INT_MAX / 10)) || ((prev == (INT_MAX / 10)) && cur > 7))
    //     {
    //         if (sign > 0)
    //             return INT_MAX;
    //         else
    //             return INT_MIN;
    //     }

    //     cur = prev * 10 + cur;

    //     return recursiveAtoI(s, ++i, sign, cur, digitStarted);
    // }

    // // Optimal approach: Recursive
    // // Time: O(N)
    // // Space: O(N): Stack space
    // int myAtoi(string s)
    // {
    //     return recursiveAtoI(s, 0, 1, 0, false);
    // }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
