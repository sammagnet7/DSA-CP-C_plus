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
#include <stack>

using namespace std;

/*
1)
Remove outer most paranthesis
https://leetcode.com/problems/remove-outermost-parentheses/description/

Problem statement:
A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.

For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.

Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.

Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.


Examples:

Example 1:
Input: s = "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:
Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:
Input: s = "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

INPUT::::::
3
(()())(())
(()())(())(()(()))
()()

OUTPUT::::::
()()()
()()()()(())

-----------------------------------------------------------------------
2)
https://takeuforward.org/data-structure/reverse-words-in-a-string/
https://leetcode.com/problems/reverse-words-in-a-string/

Problem Statement: Given a string s, reverse the words of the string.

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

Example:

Example 1:
Input: s = "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.


INPUT::::::
3
the sky is blue
  hello world
a good   example

OUTPUT::::::
blue is sky the
world hello
example good a

-----------------------------------------------------------------------
3)
Largest Odd Number in String
https://leetcode.com/problems/largest-odd-number-in-string/

You are given a string num, representing a large integer. Return the largest-valued odd integer (as a string) that is a non-empty substring of num, or an empty string "" if no odd integer exists.

A substring is a contiguous sequence of characters within a string.



Example 1:

Input: num = "52"
Output: "5"
Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.
Example 2:

Input: num = "4206"
Output: ""
Explanation: There are no odd numbers in "4206".
Example 3:

Input: num = "35427"
Output: "35427"
Explanation: "35427" is already an odd number.


Constraints:

1 <= num.length <= 105
num only consists of digits and does not contain any leading zeros.

-----------------------------------------------------------------------
4)
Longest Common Prefix in a String array
https://leetcode.com/problems/longest-common-prefix/description/

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".



Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.


Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters if it is non-empty.

-----------------------------------------------------------------------
5)
Isomorphic Strings:
https://leetcode.com/problems/isomorphic-strings/description/


Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true
Explanation:
The strings s and t can be made identical by:
Mapping 'e' to 'a'.
Mapping 'g' to 'd'.

Example 2:
Input: s = "foo", t = "bar"
Output: false
Explanation:
The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:
Input: s = "paper", t = "title"
Output: true


INPUT::::::
3
egg
add
foo
bar
paper
title

OUTPUT::::::
true
false
true

-----------------------------------------------------------------------
6)
Rotate String
https://leetcode.com/problems/rotate-string/description/

Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.

Example 1:
Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:
Input: s = "abcde", goal = "abced"
Output: false

INPUT::::::
2
abcde
cdeab
abcde
abced


OUTPUT::::::
true
false
-----------------------------------------------------------------------
7)
Valid Anagram
https://takeuforward.org/data-structure/check-if-two-strings-are-anagrams-of-each-other/
https://leetcode.com/problems/valid-anagram/

Problem Statement: Check if two Strings are anagrams of each other

Anagrams of a string are all the possible permutations of that string

Example 1:
Input: CAT, ACT
Output: true
Explanation: Since the count of every letter of both strings are equal.

Example 2:
Input: RULES, LESRT
Output: false
Explanation: Since the count of U and T  is not equal in both strings.
-----------------------------------------------------------------------

 */

class Solution
{
public:
    // 1)-----------------------------------------------------------------------

    // Optimal
    // Time: O(N)
    // Space: O(1)
    string removeOuterParentheses(string s)
    {
        int N = s.length(); // also .size() applicable

        // char *c=&s[0]; // If modification is needed
        // const char *c= s.c_str(); // No modification

        int count = 0;
        int idx = 0;

        for (int i = 0; i < N; i++)
        {

            if (s[i] == '(')
            {
                count++;
            }
            else if (s[i] == ')')
            {
                count--;
            }

            if ((count == 1 && s[i] == '(') || (count == 0 && s[i] == ')'))
                continue;
            else
                s[idx++] = s[i];
        }

        s.resize(idx); // Resize with new string length
                       // As this is not c style string, so s[idx]='\0' does not work

        return s;
    }

    // 2)-----------------------------------------------------------------------

    // Brute force: Using Stack
    // Time: O(N)
    // Space: O(N)
    string reverseWords(string s)
    {
        string ans = "";

        stack<string> st;

        stringstream ss(s);
        string inp;

        while (ss >> inp)
        {
            st.push(inp);
        }

        ans = ans + st.top();
        st.pop();

        while (!st.empty())
        {
            ans = ans + " ";
            ans = ans + st.top();
            st.pop();
        }

        return ans;
    }

    // Optimal approach: Removing stack space
    // Time: O(N)
    // Space: O(1)
    string reverseWords(string s)
    {
        int N = s.size();
        string ans = "";
        ans.reserve(N);

        stringstream ss(s);
        string inp;

        while (ss >> inp)
        {
            if (ans == "")
                ans = inp;
            else
            {
                ans.insert(0, " ");
                ans.insert(0, inp);
            }
        }

        // ans.resize(ans.length()-1);

        return ans;
    }

    // 3)-----------------------------------------------------------------------

    string largestOddNumber(string num)
    {
        int N = num.length();
        int oddIdx = -1;

        for (int i = N - 1; i >= 0; i--)
        {
            if ((num[i] - '0') % 2 == 1)
            { // Convert chat to int by adding ASCII value of '0'
                oddIdx = i;
                break;
            }
        }

        if (oddIdx == -1)
            return "";
        else
        {
            num.resize(oddIdx + 1);
            return num;
        }
    }

    // 4)-----------------------------------------------------------------------

    // O(N) * O(Min string length)
    string longestCommonPrefix(vector<string> &strs)
    {
        int N = strs.size();
        int minL = INT_MAX;
        string minLStr = "";

        // O(N)
        for (string str : strs)
        {
            if (str.length() < minL)
            {
                minL = str.length();
                minLStr = str;
            }
        }

        int matchedIdx = minLStr.size() - 1;

        // O(N) * O(Min string length)
        for (string str : strs)
        {
            bool modified = false;
            int i = -1;
            while ((i + 1) <= matchedIdx)
            { // O(Min string length)
                if (minLStr[i + 1] != str[i + 1])
                {
                    break;
                }
                else
                {
                    i++;
                    modified = true;
                }
            }

            if (i == -1)
                return "";
            if (i < matchedIdx)
                matchedIdx = i;
        }

        minLStr.resize(matchedIdx + 1);

        return minLStr;
    }

    // Another approach
    string longestCommonPrefix(vector<string> &strs)
    {
        int N = strs.size();

        if (strs.size() == 1)
        {
            return strs[0];
        }

        string prefMatched = "";

        for (int k = 0; k < min(strs[0].size(), strs[1].size()); k++)
        {
            if (strs[0][k] != strs[1][k])
            {
                break;
            }

            prefMatched.push_back(strs[0][k]);
        }

        for (int i = 2; i < N; i++)
        {
            int k;
            for (k = 0; k < min(prefMatched.size(), strs[i].size()); k++)
            {
                if (prefMatched[k] != strs[i][k])
                {
                    break;
                }
            }
            prefMatched.resize(k);
        }

        return prefMatched;
    }

    // 5)-----------------------------------------------------------------------
    //  Optimal approach
    //  Time: O(N Log N)
    //  Space: O(2N)
    bool isIsomorphic(string s, string t)
    {

        int m = s.size();
        int n = t.size();

        if (m != n)
            return false;

        map<int, int> mp1;  // keeps map from s->t
        map<int, int> mp2;  // keeps map from t->s

        // O(N)
        for (int i = 0; i < n; i++)
        {
            if (mp1.find(s[i]) != mp1.end())
            {
                if (mp1[s[i]] != t[i])
                    return false;
            }
            else
            {
                mp1[s[i]] = t[i]; // O(Log N)
            }
            if (mp2.find(t[i]) != mp2.end())
            {
                if (mp2[t[i]] != s[i])
                    return false;
            }
            else
            {
                mp2[t[i]] = s[i]; // O(Log N)
            }
        }

        return true;
    }

    // 6)-----------------------------------------------------------------------
    //  // Time: O(N^2)
    //  // Space: O(1)
    //  bool rotateString(string s, string goal)
    //  {

    //     int N = s.length();
    //     int M = goal.length();

    //     if (N != M)
    //         return false;

    //     for (int i = 0; i < N; i++)
    //     {
    //         int d = i;
    //         string shiftedStr = s.substr(d, (N - d)) + s.substr(0, d);

    //         if (goal == shiftedStr)
    //             return true;
    //     }

    //     return false;
    // }

    // Optimal approach: Using concatenation of the the strings
    // Time: O(2N)
    // Space: O(N)
    // Note: Anothe KMP method is available with same complexities
    bool rotateString(string s, string goal)
    {

        int N = s.length();
        int M = goal.length();

        if (N != M)
            return false;

        string conStr = s + s;

        if (conStr.find(goal) < conStr.length()) // O(N)
            return true;

        else
            return false;
    }

    // 7)-----------------------------------------------------------------------
    //  Approach: Optimal when unicode also involved
    //  Time: O(N)
    //  Space: O(1)
    //  Note: In case of only letters -> Take vector of 26 size. Faster
    bool isAnagram(string s, string t)
    {
        int n = s.length();
        int m = t.length();

        if (n != m)
            return false;

        unordered_map<int, int> mp;

        // O(N)
        for (int i = 0; i < n; i++)
        {
            mp[s[i]]++;
        }

        // O(N)
        for (int i = 0; i < n; i++)
        {
            mp[t[i]]--;
        }

        auto it = mp.begin();
        while (it != mp.end())
        {
            if (it->second != 0)
                return false;
            it++;
        }

        return true;
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
        cout << ob.removeOuterParentheses(input) << " ";
        // cout<< ob.reverseWords(input)<<" ";
        // cout<< ob.isIsomorphic(input1,input2);
        cout << endl;
    }
    return 0;
}