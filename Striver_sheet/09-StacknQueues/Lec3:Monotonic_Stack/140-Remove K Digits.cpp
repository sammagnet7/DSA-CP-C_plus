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

1. Title: Remove K Digits

Links:
https://www.youtube.com/watch?v=jmbuRzYPGrg&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=14
https://takeuforward.org/plus/dsa/problems/remove-k-digits?tab=editorial
https://leetcode.com/problems/remove-k-digits/description/

Problem statement:
Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

Examples:
    Example 1:
    Input: num = "1432219", k = 3
    Output: "1219"
    Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

    Example 2:
    Input: num = "10200", k = 1
    Output: "200"
    Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

    Example 3:
    Input: num = "10", k = 2
    Output: "0"
    Explanation: Remove all the digits from the number and it is left with nothing which is 0.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Remove K Digits
//

// Optimal approach:  uses stack: Traverse left to right. Replace k greater elements to the left by smaller elements to the right.
// Time: O(N+K)
// Space: O(N)
string removeKdigits(string num, int k)
{

    int N = num.size();
    string st; // O(N)

    for (int i = 0; i < N; i++)
    { // O(N)

        int curChar = num[i];
        int curDig = curChar - '0';

        while (!st.empty() && (st.back() - '0') > curDig && k > 0)
        { // O(K) for looping N times
            st.pop_back();
            k--;
        }

        st.push_back(curChar);
    }

    while (k--)
    { // edge case: If digits in given string is in Ascending order like 123456, then at the end pop last k digits from stack
        st.pop_back();
    }

    while (st[0] == '0')
    { // edge case:  If starting of the string consists of '0's
        st.erase(0, 1);
    }

    if (st.empty())
    { // edge case: Instead of empty string return '0'
        return "0";
    }

    return st;
}

int main()
{
    return 0;
}
