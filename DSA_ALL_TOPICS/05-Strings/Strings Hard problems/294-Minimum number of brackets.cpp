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

1. Title: Minimum number of bracket reversals needed to make an expression balanced

Links:
https://takeuforward.org/plus/dsa/problems/minimum-number-of-bracket-reversals-to-make-an-expression-balanced?tab=editorial
https://www.geeksforgeeks.org/problems/count-the-reversals0401/1


Problem statement:
Given a string s consisting of only opening and closing curly brackets '{' and '}', find out the minimum number of reversals required to convert the string into a balanced expression. A reversal means changing '{' to '}' or vice-versa.

Examples:
    Input: s = "}{{}}{{{"
    Output: 3
    Explanation: One way to balance is:
    "{{{}}{}}". There is no balanced sequence
    that can be formed in lesser reversals.

    Input: s = "{{}{{{}{{}}{{"
    Output: -1
    Explanation: There's no way we can balance
    this sequence of braces.

Constraints:
    1 ≤ |s| ≤ 105


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Minimum Add to Make Parentheses Valid


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

*/

//-------------------------------------------------------------------------------
// 1. Title: Minimum number of bracket reversals needed to make an expression balanced
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // -------------------------------------------------------------------------
    // Problem: Count minimum reversals needed to balance a string of '{' and '}'
    //
    // Intuition:
    // - We are given a string consisting of only '{' and '}'.
    // - We need to make the string balanced (properly matched braces) using
    //   the minimum number of reversals of braces.
    // - For example: "}{" → reverse either of them → "{}" → 1 reversal.
    //
    // Approach:
    // 1. Traverse the string once.
    // 2. Maintain two counters:
    //      lc = count of unmatched '{'
    //      rc = count of unmatched '}'
    // 3. When we see '{', increment lc.
    // 4. When we see '}', if there is an unmatched '{' (lc > 0),
    //    we can match it (decrement lc). Otherwise, this '}' is unmatched,
    //    so increment rc.
    // 5. At the end of traversal, lc = unmatched '{', rc = unmatched '}'.
    // 6. If (lc + rc) is odd, balancing is impossible → return -1.
    // 7. Otherwise:
    //      - If lc and rc are even → answer = (lc + rc)/2
    //      - If lc and rc are odd → one extra reversal is required
    //        → answer = (lc + rc)/2 + 1
    //
    // Complexity:
    // - Time: O(N), one pass over the string.
    // - Space: O(1), just counters.
    // -------------------------------------------------------------------------
    int countMinReversals(string s)
    {
        int n = s.size();

        // If braces is odd → impossible to balance
        if (n % 2 != 0)
            return -1;

        int lc = 0; // counts unmatched '{'
        int rc = 0; // counts unmatched '}'

        // Traverse string
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '{')
            {
                lc++; // new '{' → unmatched for now
            }
            else if (s[i] == '}')
            {
                if (lc > 0)
                {
                    lc--; // match this '}' with a previous unmatched '{'
                }
                else
                {
                    rc++; // no unmatched '{' → this '}' is unmatched
                }
            }
        }

        // If both are even → half reversals needed
        if (lc % 2 == 0)
        {
            return (lc + rc) / 2;
        }
        else
        {
            // If odd → one extra reversal needed
            return (lc + rc) / 2 + 1;
        }
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Minimum Add to Make Parentheses Valid
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // -------------------------------------------------------------------------
    // Problem: Minimum Additions to Make Parentheses Valid (LC 921)
    //
    // Intuition:
    // - We are given a string with only '(' and ')'.
    // - A valid parentheses string means:
    //     - Every '(' has a matching ')'.
    //     - Order must be correct (no extra closing before an opening).
    // - If the string is not valid, we need to add the minimum number of
    //   parentheses to make it valid.
    //
    // Approach:
    // 1. Traverse the string once.
    // 2. Maintain:
    //      lc = count of unmatched '('
    //      rc = count of unmatched ')'
    // 3. For every '(' → increment lc.
    // 4. For every ')' →
    //      - if lc > 0 → match it with an existing '(' (decrement lc).
    //      - else → this ')' is unmatched, so increment rc.
    // 5. At the end:
    //      - lc = remaining unmatched '('.
    //      - rc = remaining unmatched ')'.
    // 6. To make the string valid, we must add (lc + rc) parentheses.
    //
    // Complexity:
    // - Time: O(N) for one pass.
    // - Space: O(1), only counters used.
    // -------------------------------------------------------------------------
    int minAddToMakeValid(string s)
    {
        int n = s.size();

        int lc = 0; // counts unmatched '('
        int rc = 0; // counts unmatched ')'

        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                lc++; // new '(' unmatched so far
            }
            else if (s[i] == ')')
            {
                if (lc > 0)
                {
                    lc--; // match with a previous '('
                }
                else
                {
                    rc++; // unmatched ')'
                }
            }
        }

        // total unmatched '(' + unmatched ')' = additions needed
        return (lc + rc);
    }
};

int main()
{
    return 0;
}