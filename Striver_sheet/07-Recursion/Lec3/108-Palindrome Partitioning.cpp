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

Palindrome Partitioning:

https://takeuforward.org/data-structure/palindrome-partitioning/
https://leetcode.com/problems/palindrome-partitioning/description/


Problem statement:
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Examples:

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Palindrome Partitioning:

    // O(N/2)
    bool isPalindrome(string &s, int sIdx, int eIdx)
    {
        while (sIdx <= eIdx)
        {
            if (s[sIdx++] != s[eIdx--])
                return false;
        }
        return true;
    }

    // O(2^N * N/2 * k)
    void recursePartition(vector<vector<string>> &ans, vector<string> &partitions, string &s, int sIdx)
    {

        if (sIdx == s.size())
        {
            ans.push_back(partitions); // O(k)
            return;
        }

        for (int i = sIdx; i < s.size(); i++)
        {

            if (isPalindrome(s, sIdx, i))
            { // O(N/2)

                partitions.push_back(s.substr(sIdx, (i - sIdx + 1)));

                recursePartition(ans, partitions, s, (i + 1));
                partitions.pop_back();
            }
        }
    }

    // Optimal approach: Recurson+Iteration
    // Time: O(2^N * N/2 * k) where `N` is length of the given string and `k` is avg length of partitions
    // Space: O(k*x) where k is the avg length of palindromes and if we have x such lists in answer
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> ans;
        vector<string> partitions;

        recursePartition(ans, partitions, s, 0);
        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
