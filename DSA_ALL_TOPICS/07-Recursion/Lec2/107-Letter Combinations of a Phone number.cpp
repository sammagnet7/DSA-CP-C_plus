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

Letter Combinations of a Phone Number:

https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/


Problem statement:
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Examples:

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]



INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Letter Combinations of a Phone Number:

    // O(3^N)
    void recurseDialPad(vector<string> &ans, map<char, vector<char>> &mp, string &digits, string &combs, int idx)
    {

        if (idx == digits.size())
        {
            ans.push_back(combs);
            return;
        }

        char cur = digits[idx];

        for (char c : mp[cur])
        {
            combs.push_back(c);
            recurseDialPad(ans, mp, digits, combs, (idx + 1));
            combs.pop_back();
        }
    }

    // Optimal approach: Backtracking and iteration
    // Time: 3^N where N is length of the string
    // and each digit has 3 chars associated with it on avg
    // Space: O(25+ 3^N * N) i.e 25 for the map space
    // and 3^N combinations each size of N
    vector<string> letterCombinations(string digits)
    {

        if (digits.empty())
            return {};

        map<char, vector<char>> mp = {
            {'2', {'a', 'b', 'c'}},
            {'3', {'d', 'e', 'f'}},
            {'4', {'g', 'h', 'i'}},
            {'5', {'j', 'k', 'l'}},
            {'6', {'m', 'n', 'o'}},
            {'7', {'p', 'q', 'r', 's'}},
            {'8', {'t', 'u', 'v'}},
            {'9', {'w', 'x', 'y', 'z'}}};

        vector<string> ans;
        string combs;

        recurseDialPad(ans, mp, digits, combs, 0);

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
