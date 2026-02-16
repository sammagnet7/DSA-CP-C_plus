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

1. Title: Postfix to Infix conversion

Links:
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://www.naukri.com/code360/problems/postfix-to-infix_8382386?leftPanelTabValue=PROBLEM

Evaluation of postfix: https://takeuforward.org/data-structure/evaluation-of-postfix-expression

Problem statement:
You are given a mathematical expression in postfix notation. The expression consists of alphabets(both lowercase and uppercase) and operators.
Convert this expression to infix notation.
Note:
    Surround every expression with a pair of parentheses “()”.

Example:
    Input: ‘postfix’ = “ab+c+”
    Output: ‘infix’ = “((a+b)+c)”
    Explanation: The expression ((a+b)+c)” in infix is equivalent to “ab+c+” in postfix.

    Sample Input 1:
    5
    ab+c+
    Sample Output 1:
    ((a+b)+c)
    Explanation Of Sample Input 1 :
    The expression “((a+b)+c)” in infix is equivalent to “ab+c+” in postfix.

    Sample Input 2 :
    9
    ABC/DA-*+
    Sample Output 2 :
    (A+((B/C)*(D-A)))

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
 2. Title: Postfix to Prefix conversion

Links:
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://www.naukri.com/code360/problems/postfix-to-prefix_1788455?leftPanelTabValue=PROBLEM

Problem statement:
You are given a string denoting a valid Postfix expression containing ‘+’, ’-’, ’*’, ‘/’ and lowercase letters.
Convert the given Postfix expression into a Prefix expression.
Note:
    Postfix notation is a method of writing mathematical expressions in which operators are placed after the operands. For example, "a b +" represents the addition of a and b.
    Prefix notation is a method of writing mathematical expressions in which operators are placed before the operands. For example, "+ a b" represents the addition of a and b.
    Expression contains lowercase English letters, ‘+’, ‘-’, ‘*’, and  ‘/’. 


Example:
    Input: abc*+
    Output: +a*bc
    Explanation:
    For the given postfix expression, infix expression is a+b*c. And it's corresponding prefix expression is +a*bc.

    Sample Input 1:
    ab+cd-*
    Expected Answer:
    *+ab-cd 
    Explanation Of Sample Input 1:
    For this testcase, the infix expression will be (a + b) * (c - d). Hence, our prefix expression will be *+ab-cd.

    Sample Input 2:
    ab+c-
    Expected Answer:
    -+abc

Expected Time Complexity:
Try to solve this in O(n), where n is the length of expression.    

INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Postfix to Infix conversion
//

// Optimal approach:
// Using operand stack
// traverse left to right
//
// Time: O(N * N) because of loop and string concatenation
// Space: O(N)
string postToInfix(string postfix)
{
    // Write your code here.

    stack<string> st; // Operand stack

    for (char c : postfix)
    {

        if (isalnum(c))
        { // operand

            st.push(string(1, c));
        }

        else
        { // operator

            string opd1 = st.top();
            st.pop();
            string opd2 = st.top();
            st.pop();

            string newopd = "(" + opd2 + c + opd1 + ")"; // can take upto O(N)
            st.push(newopd);
        }
    }

    return st.top();
}

//-----------------------------------------------------------------------
// 2. Title: Postfix to Prefix conversion

// Optimal approach:
// Traverse from left to right
//
// Time: O(N * N): loop*concat but ~Avg(N)
// Space: O(N)
string postfixToPrefix(string &s)
{
    // Write your code here.

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

            st.push(string(1, c) + opd2 + opd1);
        }
    }

    return st.top();
}

int main()
{
    return 0;
}
