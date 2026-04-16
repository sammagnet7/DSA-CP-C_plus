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

using namespace std;

/*

Title: String to Integer (atoi)

Link:
https://leetcode.com/problems/string-to-integer-atoi/description/


Problem statement:
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.

The algorithm for myAtoi(string s) is as follows:
Whitespace: Ignore any leading whitespace (" ").
Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
Rounding: If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], then round the integer to remain in the range. Specifically, integers less than -2^31 should be rounded to -2^31, and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.
Return the integer as the final result.

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


INPUT::::::
7
42
   -042
1337c0d3
0-1
words and 987
-91283472332
+1

OUTPUT::::::
42
-42
1337
0
0
-2147483648
1

 */

//-------------------------------------------------------------------------------
// 1. Title: String to Integer (atoi)
//-------------------------------------------------------------------------------
class Solution
{
public:
    //-----------------------------------
    // Approach: 1 : For each loop
    //-----------------------------------
    /**
     * @brief Converts a string to a 32-bit signed integer using a State Machine.
     * * 🧠 INTUITION & APPROACH:
     * We must process the string in four strict, sequential phases:
     * 1. Ignore leading whitespace.
     * 2. Capture the sign (+ or -) exactly once.
     * 3. Read contiguous digits. The moment a non-digit appears, stop completely.
     * 4. Accumulate the number while constantly checking for 32-bit integer overflow.
     * * 💡 OVERFLOW MATH TRICK:
     * A 32-bit signed integer has a maximum value of 2,147,483,647 (INT_MAX)
     * and a minimum value of -2,147,483,648 (INT_MIN).
     * To prevent overflow before multiplying our current answer by 10:
     * - We check if ans > INT_MAX / 10 (214,748,364).
     * - If ans == INT_MAX / 10, we must check the next incoming digit.
     * -> INT_MAX % 10 calculates the last digit of the max limit (7).
     * -> For positive numbers, exceeding 7 causes overflow.
     * -> For negative numbers, exceeding 7 (so 8 or 9) causes underflow.
     * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string.
     * - Space Complexity: O(1) auxiliary space.
     */
    int myAtoi(string s)
    {

        int ans = 0;

        // State flags
        bool num_started = false;
        bool isPositive = true;

        for (char c : s)
        {

            // ==========================================
            // PHASES 1 & 2: Handle Whitespace and Signs
            // ==========================================
            if (!num_started)
            {
                if (c == ' ')
                {
                    continue; // Keep skipping spaces until we hit our first character
                }
                else if (c == '+')
                {
                    num_started = true;
                    continue; // Sign recorded, move to digits
                }
                else if (c == '-')
                {
                    num_started = true;
                    isPositive = false;
                    continue; // Sign recorded, move to digits
                }
            }

            // ==========================================
            // PHASE 3: Process Valid Digits
            // ==========================================
            if (isdigit(c))
            {

                // If we skipped the sign and went straight to a number, flag it as started
                num_started = true;
                int dig = c - '0';

                // ==========================================
                // PHASE 4: Proactive Overflow / Underflow Checks
                // ==========================================

                // Case A: The base number is already strictly larger than the safe boundary
                if (ans > (INT_MAX / 10))
                {
                    return isPositive ? INT_MAX : INT_MIN;
                }

                // Case B: We are exactly at the safe boundary (214748364).
                // We must evaluate the final digit.
                if (ans == (INT_MAX / 10))
                {

                    // INT_MAX % 10 perfectly evaluates to 7.

                    // If positive, 2147483647 is the max. Digits 7, 8, 9 trigger MAX limit.
                    if (isPositive && dig >= INT_MAX % 10)
                    {
                        return INT_MAX;
                    }

                    // If negative, -2147483648 is the min. Digits 8, 9 trigger MIN limit.
                    // Notice the strict '>' instead of '>=' because 7 is valid for negatives!
                    if (!isPositive && dig > INT_MAX % 10)
                    {
                        return INT_MIN;
                    }
                }

                // Safe to accumulate
                ans = ans * 10 + dig;
            }
            // ==========================================
            // TERMINATION: Invalid Character Found
            // ==========================================
            else
            {
                // The moment we see a non-digit after processing has started
                // (or if the very first char is invalid), we immediately halt.
                break;
            }
        }

        // Apply the recorded sign to the safely accumulated magnitude
        return isPositive ? ans : -ans;
    }

    //-----------------------------------
    // Approach 2: For indexed loop
    //-----------------------------------
    /**
     * @brief Converts a string to a 32-bit signed integer using Sequential State Parsing.
     * * * 🧠 INTUITION & APPROACH:
     * Instead of looping through every character and checking boolean flags to see
     * what state we are in, we use sequential loops to physically force the parser
     * through the 4 required phases in strict order:
     * 1. Space Phase: Consume all spaces. The moment it ends, we never check for spaces again.
     * 2. Sign Phase: Look exactly once at the current pointer for a '+' or '-'.
     * 3. Digit Phase: Consume all valid digits.
     * 4. Overflow Phase: Guard against 32-bit integer limits before multiplying.
     * * * 💡 THE OVERFLOW LOGIC:
     * INT_MAX =  2147483647
     * INT_MIN = -2147483648
     * If `result` is greater than 214748364, the next *10 will definitely overflow.
     * If `result` exactly equals 214748364, the next digit cannot exceed 7.
     * (Wait, what about 8 for INT_MIN? If `sign` is -1 and the digit is 8, it triggers
     * `digit > 7`, drops into the return statement, and correctly returns `INT_MIN`!)
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string. Each character is
     * visited exactly once by the `i` pointer.
     * - Space Complexity: O(1) auxiliary space.
     */
    int myAtoi(string s)
    {

        int i = 0;
        int n = s.length();
        int sign = 1;
        int result = 0;

        // ==========================================
        // PHASE 1: Skip leading whitespace
        // ==========================================
        while (i < n && s[i] == ' ')
        {
            i++;
        }

        // ==========================================
        // PHASE 2: Check for optional sign
        // ==========================================
        // Use an 'if' instead of a 'while' because we can only have ONE sign.
        // "++-2" is invalid and should stop parsing immediately.
        if (i < n && (s[i] == '+' || s[i] == '-'))
        {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        // ==========================================
        // PHASE 3: Process contiguous digits
        // ==========================================
        // isdigit() natively handles '0' through '9'
        while (i < n && isdigit(s[i]))
        {

            int digit = s[i] - '0';

            // ==========================================
            // PHASE 4: Handle 32-bit integer overflow/underflow
            // ==========================================
            // INT_MAX is 2147483647. INT_MAX / 10 is 214748364.
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > 7))
            {
                // If it overflows, return the max or min bounds based on the recorded sign
                return sign == 1 ? INT_MAX : INT_MIN;
            }

            // Accumulate the number safely
            result = result * 10 + digit;
            i++;
        }

        // Apply the sign to the magnitude
        return result * sign;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        string input;
        getline(cin, input);

        // int m, n;
        /// cin >> m >> n;

        // vector<vector<int>> matrix(m, vector<int>(n));

        // Read the matrix
        // for (int i = 0; i < m; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cin >> matrix[i][j];
        //     }
        // }

        Solution ob;
        cout << ob.myAtoi(input) << " ";
        // cout<< ob.reverseWords(input)<<" ";
        // cout<< ob.isIsomorphic(input1,input2);
        cout << endl;
    }
    return 0;
}