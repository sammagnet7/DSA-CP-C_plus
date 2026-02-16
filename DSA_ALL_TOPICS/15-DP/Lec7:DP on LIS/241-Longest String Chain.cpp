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
#include <list>

using namespace std;

/*

1. Title: Longest String Chain | (DP- 45)

Links:
https://takeuforward.org/data-structure/longest-string-chain-dp-45/
https://www.youtube.com/watch?v=YY8iBaYcc4g
https://takeuforward.org/plus/dsa/problems/longest-string-chain?tab=editorial
https://leetcode.com/problems/longest-string-chain/description/


Problem statement:
You are given an array of words where each word consists of lowercase English letters.
wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
Return the length of the longest possible word chain with words chosen from the given list of words.

Examples:
    Example 1:
    Input: words = ["a","b","ba","bca","bda","bdca"]
    Output: 4
    Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
    Example 2:
    Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
    Output: 5
    Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].
    Example 3:
    Input: words = ["abcd","dbqca"]
    Output: 1
    Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
    ["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.


Constraints:
    1 <= words.length <= 1000
    1 <= words[i].length <= 16
    words[i] only consists of lowercase English letters.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Longest String Chain | (DP- 45)

    /*
        Method: checkInWordChain
        ----------------------------------------
        Checks whether 'cur' can be formed by adding exactly one character
        to the previous word 'pre'.

        Parameters:
        - pre : reference to the previous word in the chain
        - cur : reference to the current word to check

        Returns:
        - true if cur can follow pre in the word chain
        - false otherwise

        Logic:
        1. First, check if lengths differ exactly by 1. If not, return false.
        2. Use two pointers (id1 for pre, id2 for cur) to compare characters.
        3. Count mismatches. If a mismatch occurs, skip a character in cur.
        4. Continue until all characters are checked.
        5. After the loops, check if exactly one character difference occurred.
        If yes, return true; otherwise, false.

        Time Complexity: O(L) where L = length of current word (cur)
        Space Complexity: O(1)
    */
    bool checkInWordChain(string &pre, string &cur)
    {
        if (pre.size() + 1 != cur.size())
            return false;

        int missMatch = 0;
        int n1 = pre.size();
        int n2 = cur.size();

        int id1 = 0;
        int id2 = 0;

        while (id1 < n1 && id2 < n2)
        {
            if (pre[id1] != cur[id2])
            {
                missMatch++;
                id2++;
            }
            else
            {
                id1++;
                id2++;
            }
        }

        while (id1 < n1)
        {
            id1++;
            missMatch++;
        }

        while (id2 < n2)
        {
            id2++;
            missMatch++;
        }

        return missMatch == 1;
    }

    /*
        Method: longestStrChain
        ----------------------------------------
        Finds the length of the longest string chain in a given list of words.
        A word chain is valid if each next word is formed by adding exactly
        one character to the previous word.

        Parameters:
        - words : reference to vector of strings

        Returns:
        - Length of the longest string chain.

        Logic:
        1. Sort words in increasing order of length.
        2. Use a dp array where dp[i] = length of longest chain ending at words[i].
        3. For each word words[curI], check all previous words words[preI].
        If words[preI] can be a predecessor (checkInWordChain), update dp[curI].
        4. Return the maximum value in dp.

        Time Complexity: O(n^2 * L)
            - n = number of words
            - L = maximum length of a word (for checkInWordChain)
        Space Complexity: O(n) for dp array
    */
    int longestStrChain(vector<string> &words)
    {
        int n = words.size();

        // Sort words by increasing length to ensure predecessors appear before successors
        sort(words.begin(), words.end(), [](string &a, string &b)
             { return a.size() < b.size(); });

        vector<int> dp(n, 1); // dp[i] = longest chain ending at words[i]

        for (int curI = 1; curI < n; curI++)
        {
            for (int preI = 0; preI < curI; preI++)
            {
                if (checkInWordChain(words[preI], words[curI]))
                {
                    dp[curI] = max(dp[curI], dp[preI] + 1);
                }
            }
        }

        // Find the maximum length from all dp values
        int maxLen = 0;
        for (int i = 0; i < n; i++)
        {
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
