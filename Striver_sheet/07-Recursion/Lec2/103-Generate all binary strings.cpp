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
Generate Binary Strings Without Adjacent Zeros:
https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/description/
https://www.geeksforgeeks.org/problems/generate-all-binary-strings/1

Problem statement:
You are given a positive integer n.
A binary string x is valid if all substrings of x of length 2 contain at least one "1".
Return all valid strings with length n, in any order.

Example 1:
Input: n = 3
Output: ["010","011","101","110","111"]
Explanation:
The valid strings of length 3 are: "010", "011", "101", "110", and "111".

Example 2:
Input: n = 1
Output: ["0","1"]
Explanation:
The valid strings of length 1 are: "0" and "1".


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------

    // O(2^N)
    void findStringsRecursively(vector<string> &v, int N, bool isPrevZero, string &s)
    {

        if (N == 0)
        {
            v.push_back(s);
            return;
        }

        if (isPrevZero)
        {
            s.push_back('1');
            findStringsRecursively(v, (N - 1), false, s);
            s.pop_back();
        }
        else
        {
            s.push_back('0');
            findStringsRecursively(v, (N - 1), true, s);
            s.pop_back();

            s.push_back('1');
            findStringsRecursively(v, (N - 1), false, s);
            s.pop_back();
        }
    }

    // Optimal approach : Uses recursion for creating a partial Binary tree stack
    // Time: o(2^N)
    // Space: O(N) i.e. stack space
    vector<string> validStrings(int n)
    {
        vector<string> ans;

        string s = "";
        findStringsRecursively(ans, n, false, s);

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
