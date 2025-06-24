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

1. Title: Infix to postfix conversion

Links:
https://takeuforward.org/data-structure/infix-to-postfix/
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://www.naukri.com/code360/problems/day-23-:-infix-to-postfix-_1382146?leftPanelTabValue=PROBLEM

Problem statement:
You are given a string 'exp' which is a valid infix expression.

Convert the given infix expression to postfix expression.


Note:
Infix notation is a method of writing mathematical expressions in which operators are placed between operands.

For example, "3 + 4" represents the addition of 3 and 4.

Postfix notation is a method of writing mathematical expressions in which operators are placed after the operands.

For example, "3 4 +" represents the addition of 3 and 4.

Expression contains digits, lower case English letters, ‘(’, ‘)’, ‘+’, ‘-’, ‘*’, ‘/’, ‘^’.


Example:
Input: exp = ‘3+4*8’

Output: 348*+

Explanation:
Here multiplication is performed first and then the addition operation. Hence postfix expression is  3 4 8 * +.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
1. Title: Infix to prefix conversion

Links:
https://takeuforward.org/data-structure/infix-to-prefix/
https://www.youtube.com/watch?v=4pIc9UBHJtk
https://onecompiler.com/c/43nr8fnex


Problem statement:
Given an infix expression, Your task is to convert the given infix expression to a prefix expression.

Examples:

Example 1:
Input: x+y*z/w+u
Output: ++x/*yzwu
Explanation: Infix to prefix

Example 2:
Input: a+b
Output: +ab
Explanation: Infix to prefix


INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Infix to postfix conversion
//

int priority(char c)
{

    switch (c)
    {
    case '^':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    case '+':
        return 1;
    case '-':
        return 1;
    default:
        return -1;
    }
}

// Optimal Approach: Traverse string from left to right
// If operands, then add to `ans` immediately.
// If operand then push to stack only if priority is greater than operator top of stack
// pop from stack all higher or equal priority operator and add to `ans`
// then push the current operator into stack
// if closing bracket is found then pop until the prev starting bracket is poped and add ops to `ans`
// Repeat this until string ends. Then pop and add rest operators to the `ans`
//
// Time: O(N)
// Space: O(N) because an extra stack space is needed
string infixToPostfix(string exp)
{
    // Write your code here

    stack<char> st;
    string ans;

    for (char c : exp)
    {

        if (isalnum(c))
            ans.push_back(c);

        else
        {

            if (c == '(')
                st.push(c);

            else if (c == ')')
            {

                while (st.top() != '(')
                {
                    ans.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else
            {
                if (st.empty())
                    st.push(c);
                else
                {
                    while (!st.empty() && priority(st.top()) >= priority(c)) // Note: '>=' is used here
                    {
                        ans.push_back(st.top());
                        st.pop();
                    }

                    st.push(c);
                }
            }
        }
    }

    while (!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
}

//-----------------------------------------------------------------------
// 2. Title: Infix to prefix conversion
// below code is in C

// O(N)
void reverse(char arr[])
{
    // int len = sizeof(arr)/sizeof(arr[0]); // Wrong
    int len = strlen(arr); // correct

    for (int i = 0; i <= ((len - 1) / 2); i++)
    {
        char tmp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = tmp;
    }
}

// Optimal approach:
// Step1: reverse input; step2: swap brackets; step3: perform infix to postfix; step4: reverse again
//
// Time: O(N)
// Space: O(N)
void infixToPrefix(char infix[], char prefix[])
{

    // reversing the input string
    reverse(infix); // do reverse

    // int len = sizeof(infix)/sizeof(infix[0]);  // Wrong
    int len = strlen(infix); // Correct

    for (int i = 0; i < len; i++) // swaps the brackets
    {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }

    char stack[len];
    int stkIdx = -1;
    int pfIdx = 0;

    // now infix to postfix conversion except one small modification i.e. here we use `>' instead of '>='
    for (int i = 0; i < len; i++)
    {
        char cur = infix[i];

        if ((cur >= '0' && cur <= '9') || (cur >= 'a' && cur <= 'z') || (cur >= 'A' && cur <= 'Z'))
        {
            prefix[pfIdx++] = cur;
        }
        else
        {

            if (cur == '(')
                stack[++stkIdx] = cur;

            else if (cur == ')')
            {
                while (stkIdx >= 0 && stack[stkIdx] != '(')
                {
                    prefix[pfIdx++] = stack[stkIdx--];
                }
                stkIdx--;
            }

            else
            {

                while (stkIdx >= 0 && priority(stack[stkIdx]) > priority(cur)) // Note: '>' is used here
                {
                    prefix[pfIdx++] = stack[stkIdx--];
                }
                stack[++stkIdx] = cur;
            }
        }
    }

    while (stkIdx >= 0)
        prefix[pfIdx++] = stack[stkIdx--];

    prefix[pfIdx] = '\0';

    reverse(prefix); // do reverse
}

int main()
{
    return 0;
}
