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

    /**
     * @brief Checks if the substring s[sIdx...eIdx] is a palindrome.
     *
     * @param s The input string.
     * @param sIdx Start index of the substring.
     * @param eIdx End index of the substring.
     * @return true if the substring is a palindrome, false otherwise.
     *
     * Time Complexity: O(N) in the worst case (where N = length of substring).
     * Space Complexity: O(1) (no extra space used).
     */
    bool isPalindrome(string &s, int sIdx, int eIdx)
    {
        while (sIdx <= eIdx)
        {
            if (s[sIdx++] != s[eIdx--]) // Compare characters from both ends
                return false;
        }
        return true;
    }

    /**
     * @brief Recursive helper to generate all palindrome partitions.
     *
     * @param ans Reference to the final result vector.
     * @param partitions Current list of palindromic substrings being built.
     * @param s The input string.
     * @param sIdx Current starting index to partition from.
     *
     * Approach:
     * - At each index, try all possible partitions (i to end of string).
     * - For each substring, check if it's a palindrome.
     * - If yes, include it in the current partition and recurse for the remaining part.
     * - Backtrack after exploring the branch.
     *
     * Time Complexity:
     * - There are at most 2^(N-1) ways to partition (choose cut or not at each gap).
     * - For each substring check, palindrome verification costs O(N).
     * - Copying substring costs O(N) in worst case.
     * - So overall: O(N^2 * 2^N).
     *
     * Space Complexity:
     * - Recursion depth = O(N).
     * - Extra space for `partitions` (current path) and result.
     */
    void recursePartition(vector<vector<string>> &ans, vector<string> &partitions, string &s, int sIdx)
    {
        // Base Case: If we've reached the end, add the current partition
        if (sIdx == s.size())
        {
            ans.push_back(partitions); // Copy current partition into result
            return;
        }

        // Try all possible partitions starting from sIdx
        for (int i = sIdx; i < s.size(); i++)
        {
            // Check if substring s[sIdx..i] is a palindrome
            if (isPalindrome(s, sIdx, i))
            {
                // If palindrome, include this substring in the current path
                partitions.push_back(s.substr(sIdx, i - sIdx + 1));

                // Recurse for the remaining part of the string
                recursePartition(ans, partitions, s, i + 1);

                // Backtrack: remove the last added substring
                partitions.pop_back();
            }
        }
    }

    /**
     * @brief Generates all possible palindrome partitions of the given string.
     *
     * @param s The input string.
     * @return A vector of all possible palindrome partitions.
     *
     * Approach:
     * - Uses backtracking to explore all valid palindromic partitions.
     * - For each valid substring (palindrome), recursively partition the remaining string.
     *
     * Time Complexity: O(N^2 * 2^N)
     * Space Complexity: O(N) (recursion stack + partitions) + space for output.
     */
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
