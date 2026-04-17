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

1. Title: Minimum Add to Make Parentheses Valid


Links:
https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/


Problem statement:
A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.

Examples:
    Example 1:
    Input: s = "())"
    Output: 1

    Example 2:
    Input: s = "((("
    Output: 3


Constraints:
    1 <= s.length <= 1000
    s[i] is either '(' or ')'.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Minimum number of bracket reversals needed to make an expression balanced

Links:
https://takeuforward.org/plus/dsa/problems/minimum-number-of-bracket-reversals-to-make-an-expression-balanced?tab=editorial
https://www.geeksforgeeks.org/problems/count-the-reversals0401/1


Problem statement:
Given a string s consisting of only opening and closing curly brackets '{' and '}', find out the minimum number of reversals required to convert the string into a balanced expression. A reversal means changing '{' to '}' or vice-versa.

Examples:
    Input: s = "}{{}}{{{"
    Output: 3
    Explanation: One way to balance is: "{{{}}{}}".
    There is no balanced sequence that can be formed in lesser reversals.

    Input: s = "{{}{{{}{{}}{{"
    Output: -1
    Explanation: There's no way we can balance this sequence of braces.

Constraints:
    1 ≤ |s| ≤ 10^5


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Minimum Add to Make Parentheses Valid
    //-------------------------------------------------------------------------------

    /**
     * @brief Calculates the minimum additions to make a parentheses string valid.
     * * * 🧠 INTUITION & APPROACH:
     * A valid parentheses string requires every '(' to have a matching ')', and
     * the order must be strictly preserved (no closing bracket before an opening one).
     * If the string is invalid, we simply need to count how many brackets are left
     * unmatched and add that exact amount.
     * 1. Traverse the string once, maintaining counts for unmatched '(' and ')'.
     * 2. For every '(', we increment our left-count (`lc`) tracker.
     * 3. For every ')', we check if we have a pending '(' to cancel it out.
     * - If yes (`lc > 0`), we match them and decrement `lc`.
     * - If no, this ')' is permanently unmatched, so we increment `rc`.
     * 4. By the end of the string, all valid pairs have annihilated each other.
     * The total additions required is simply the sum of the remaining residues.
     * * * ⏱️ COMPLEXITY:
     * - Time: O(N) for a single pass through the string.
     * - Space: O(1) auxiliary space, utilizing only two integer variables.
     */
    int minAddToMakeValid(string s)
    {

        int n = s.length(); // .size() or .length() both compile to the same O(1) call

        int lc = 0; // Tracks unmatched opening brackets '('
        int rc = 0; // Tracks unmatched closing brackets ')'

        for (int i = 0; i < n; i++)
        {

            if (s[i] == '(')
            {
                // New opening bracket waiting for a match
                lc++;
            }
            else if (s[i] == ')')
            {

                // Does this closing bracket have an opening pair?
                if (lc > 0)
                {
                    lc--; // Match found, cancel them out
                }
                else
                {
                    rc++; // No opening bracket available, this is unmatched
                }
            }
        }

        // Total additions needed is the sum of both unmatched sets
        return (lc + rc);
    }

    //------------------------------------------------------------------------------------
    // 2. Title: Minimum number of bracket reversals needed to make an expression balanced
    //------------------------------------------------------------------------------------
    /**
     * @brief Finds the minimum reversals required to balance a bracket string.
     * * 🧠 INTUITION & APPROACH:
     * To balance the string with the minimum number of reversals, we must first
     * eliminate all the brackets that are ALREADY balanced.
     *
     * * Step 1: Filter out the noise.
     * As we iterate through the string, we cancel out any valid `{}` pairs.
     * Whatever is left over is the "residue" of unmatched brackets. Because all
     * valid pairs are gone, this residue will always look exactly like this:
     * `} } } ... { { {` (Unmatched closing brackets, followed by unmatched opening brackets).
     *
     * * Step 2: The Reversal Math.
     * Let `lc` be the number of unmatched '{' and `rc` be the number of unmatched '}'.
     * - If we have an even number of unmatched brackets of the same type (e.g., `{{`),
     * we only need to reverse half of them to balance the pair (`{}`). Math: 2 / 2 = 1.
     *
     * - If we have an odd number (e.g., `{{{`), we can fix the first two with 1 reversal (`{}{`),
     * but the leftover `{` will need to pair with a leftover `}` from the other side.
     * This requires an extra reversal.
     *
     * - Therefore, taking the ceiling of the count divided by 2 elegantly handles
     * both even and odd residues: `ceil(count / 2.0)`.
     *
     * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string.
     * - Space Complexity: O(1) auxiliary space. We use two integer trackers instead of a Stack.
     */
    int countMinReversals(string s)
    {

        int n = s.length();
        int ans = -1;

        // 1. Odd length check: An odd-length string can mathematically never be balanced.
        if (n % 2 != 0)
        {
            return ans;
        }

        int lc = 0; // Tracks unmatched opening brackets '{' (left count)
        int rc = 0; // Tracks unmatched closing brackets '}' (right count)

        // 2. Iterate through the string to cancel out valid pairs
        for (int i = 0; i < n; ++i)
        {
            char c = s[i];

            if (c == '{')
            {
                // We found an opening bracket, it is now waiting for a match
                ++lc;
            }
            else if (c == '}')
            {
                // We found a closing bracket. Does it have an opening bracket to pair with?
                if (lc > 0)
                {
                    // Match found! Cancel the pending opening bracket.
                    --lc;
                    continue;
                }

                // No opening bracket available. This is an unmatched closing bracket.
                ++rc;
            }
        }

        // 3. Apply the ceiling math formula to the remaining unmatched residue
        ans = ceil(lc / 2.0) + ceil(rc / 2.0);

        return ans;
    }
};

int main()
{
    return 0;
}