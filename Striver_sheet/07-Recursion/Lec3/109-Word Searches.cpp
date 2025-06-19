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

Word Search:

https://takeuforward.org/data-structure/word-search-leetcode/
https://leetcode.com/problems/word-search/description/


Problem statement:
Given an m x n grid of characters board and a string word, return true if word exists in the grid.
The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Examples:

Example 1:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

Follow up: Could you use search pruning to make your solution faster with a larger board?
Apply DP for that.

INPUT::::::


OUTPUT::::::

---------------------------------------------------------------------------

Word Break:

https://leetcode.com/problems/word-break/description/

Problem statement:
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
Note that the same word in the dictionary may be reused multiple times in the segmentation.

Examples:

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false


Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.


Follow up: Could you make your solution faster with DP?

INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Word Search:

    // 4^l
    bool recurseSearch(vector<vector<char>> &board, string &word, int rows, int cols, int i, int j, int matchCount)
    {
        if (matchCount == word.size())
            return true;

        if (i < 0 || i >= rows || j < 0 || j >= cols)
            return false;

        if (board[i][j] == '!' || board[i][j] != word[matchCount])
            return false;

        int cur = board[i][j];
        board[i][j] = '!';

        bool left = recurseSearch(board, word, rows, cols, i, j - 1, (matchCount + 1));
        bool right = recurseSearch(board, word, rows, cols, i, j + 1, (matchCount + 1));
        bool top = recurseSearch(board, word, rows, cols, i - 1, j, (matchCount + 1));
        bool down = recurseSearch(board, word, rows, cols, i + 1, j, (matchCount + 1));

        board[i][j] = cur;

        if (left || right || top || down)
            return true;
        else
            return false;
    }

    // Optimal approach: Use Iteration to start with matching char + Use recursion to match left,right,top,down
    // Time: O((M*N)* 4^l) because of iterating matrix size of (M*N)
    // and in the worst case for each iteration there are 4 possible recursion stack, max stack length `l`
    // where `l` is the length of the given word to match
    // Space: O(l) because of Recustion stack space
    bool exist(vector<vector<char>> &board, string word)
    {
        int rows = board.size();
        int cols = board[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] == word[0])
                {
                    if (recurseSearch(board, word, rows, cols, i, j, 0))
                        return true;
                }
            }
        }

        return false;
    }

    // ---------------------------------------------
    // Word Break:

    // O(k*x)
    bool existsInDict(string &s, unordered_set<string> &wordDictSet, int sIdx, int eIdx)
    {

        return wordDictSet.count(s.substr(sIdx, eIdx - sIdx + 1)) > 0;
    }

    //
    bool recursiveSegment(string &s, unordered_set<string> &wordDictSet, int sIdx)
    {

        if (sIdx == s.size())
            return true;

        bool ret;

        for (int i = sIdx; i < s.size(); i++)
        {
            if (!existsInDict(s, wordDictSet, sIdx, i))
                continue;

            ret = recursiveSegment(s, wordDictSet, (i + 1));

            if (ret)
                return true;
        }

        return false;
    }

    // Note: Apply DP to pass all test cases
    // Approach: Backtracking
    // Time: O(2^N) for Binary recursion tree
    // Space: O(N) for recursion stack
    bool wordBreak(string s, vector<string> &wordDict)
    {

        unordered_set<string> wordDictSet(wordDict.begin(), wordDict.end());

        return recursiveSegment(s, wordDictSet, 0);
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
