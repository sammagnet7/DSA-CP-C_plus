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

using namespace std;

/*

1. Title: Prefix to Infix conversion

Links:
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://www.naukri.com/code360/problems/prefix-to-infix_1215000?leftPanelTabValue=PROBLEM


Problem statement:
You are given a string denoting a valid Prefix expression containing ‘+’, ’-’, ’*’, ‘/’ and lowercase letters.
Convert the given Prefix expression into an Infix expression.
Note:
    Infix notation is a method of writing mathematical expressions in which operators are placed between operands. For example, "a + b" represents the addition of a and b.
    Prefix notation is a method of writing mathematical expressions in which operators are placed before the operands. For example, "+ a b" represents the addition of a and b.
    Expression contains lowercase English letters, ‘+’, ‘-’, ‘*’, and  ‘/’.


Example:
Input: /-ab+-cde
Output: ((a-b)/((c-d)+e))
Explanation:
    In this test case, there are four operators ‘/’, ‘-’, ‘+’, ‘-’.
    Prefix expression:  /-ab+-cde.
    The operator between  ‘a’ and ‘b’ is ‘-’. Resulting expression: /(a-b)+-cde.
    The operator between  ‘c’ and ‘d’ is ‘-’. Resulting expression: /(a-b)+(c-d)e.
    The operator between ‘c-d’ and ‘e’ is +. Resulting expression: /(a-b)((c-d)+e).
    The operator between ‘a-b’ and ‘((c-d)+e)’ is ‘/’. Resulting expression: ((a-b)/((c-d)+e)).

Sample Input 1:
*-a/bc-/dkl
Expected Answer:
((a-(b/c))*((d/k)-l))
Output on console:
((a-(b/c))*((d/k)-l))
Explanation for Sample Input 1:
    In this testcase, there are five operators ‘*’, ‘-’, ‘/’, ‘-’, ‘/’.
    Prefix Expression: *-a/bc-/dkl.
    The operator between  ‘b’ and ‘c’ is ‘/’. Resulting expression: *-a(b/c)-/dkl.
    The operator between  ‘d’ and ‘k’ is ‘/’. Resulting expression: *-a(b/c)-(d/k)l.
    The operator between  ‘a’ and ‘(b/c)’ is ‘-’. Resulting expression: *(a-(b/c))-(d/k)l.
    The operator between  ‘d/k’ and ‘l’ is ‘-’. Resulting expression: *(a-(b/c))((d/k)-l).
    The operator between  ‘(a-(b/c))’ and ‘((d/k)-l)’ is ‘*’. Resulting expression: ((a-(b/c))*((d/k)-l)).

Sample Input 2:
*-a/bc-/del
Expected Answer:
((a-(b/c))*((d/e)-l))
Output on console:
((a-(b/c))*((d/e)-l))


Expected Time Complexity:
Try to solve this in O(n^2), where n is the length of expression.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
2. Title: Prfix to postfix conversion

Links:
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://www.naukri.com/code360/problems/convert-prefix-to-postfix_8391014

Problem statement:
You are given a string ‘s’ of size ’n’, representing the prefix form of a valid mathematical expression.
Your task is to find out its corresponding postfix expression.
The expected time and space complexity is O(n) and O(n), where ‘n’ is the size of the string ‘s’.
Note:
    The only operators used in the expressions are ‘+’, ‘-’, ‘*’, ‘/’.


Example:
    Input: ‘n’ = 5, ‘s’ = “/A+BC”
    Output: ABC+/
    Explanation: For ‘s’ = “/A+BC”, the correct postfix expression is “ABC+/”.

    Sample Input 1:
    5
    /A+BC
    Sample Output 1 :
    ABC+/
    Explanation Of Sample Input 1:
    Input: ‘n’ = 5, ‘s’ = “/A+BC”
    Output: ABC+/
    Explanation: For ‘s’ = “/A+BC”, the correct postfix expression is “ABC+/”.

    Sample Input 2:
    9
    -/A+BC*DE
    Sample Output 2:
    ABC+/DE*-
    Explanation of sample output 2:
    Input: ‘n’ = 9, ‘s’ = “-/A+BC*DE”
    Output: ABC+/DE*-
    Explanation: For ‘s’ = “-/A+BC*DE”, the correct postfix expression is “ABC+/DE*-”.


INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Prefix to Infix conversion
//

// Using operand stack
// Reverse input
// perform ditto same as `postfix to infix` to get the ans
// reverse ans
//
// Note: alternate to reverse the input we can traverse end to start then st.push("(" + opd1 + string(1, c) + opd2 + ")";)
//
// Time: O(N * N) for loop and string concatenation
// Space: O(N)
string prefixToInfixConversion(string &s)
{
    // Write your code here.

    reverse(s.begin(), s.end()); // O(N)
    stack<string> st;            // Operand stack

    for (char c : s)
    { // O(N)

        if (isalnum(c))
        {
            st.push(string(1, c));
        }
        else
        {

            string opd1 = st.top();
            st.pop();
            string opd2 = st.top();
            st.pop();

            // note: here appending brackets in reverse order
            string newopd = ")" + opd2 + string(1, c) + opd1 + "("; // can take upto O(N)
            st.push(newopd);
        }
    }

    reverse(st.top().begin(), st.top().end()); // O(N)
    reverse(s.begin(), s.end());

    return st.top();
}

//-----------------------------------------------------------------------
// 2. Title: Prfix to postfix conversion
//

// Optimal approach:
// Reverse input
// perform ditto same as postfix to prefix to get the ans
// reverse ans
// Note: alternate to reverse the input we can traverse end to start then st.push(opd1 , opd2, c)
//
// Time: O(N*N)
// Space: O(N)
string preToPost(string s)
{
    // Write Your Code Here

    reverse(s.begin(), s.end()); // O(n)

    stack<string> st; // operand stack

    for (char c : s)
    {
        if (isalnum(c))
        {
            st.push(string(1, c));
        }
        else
        {
            string opd1 = st.top();
            st.pop();

            string opd2 = st.top();
            st.pop();

            st.push(string(1, c) + opd2 + opd1); // O(N) for concatenation
        }
    }

    reverse(st.top().begin(), st.top().end());
    reverse(s.begin(), s.end());

    return st.top();
}


int main()
{
    return 0;
}
