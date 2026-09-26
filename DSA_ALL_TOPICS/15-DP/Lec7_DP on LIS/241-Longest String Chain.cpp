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

1. Title: Longest String Chain

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

//-------------------------------------------------------------------------------
// 1. Title: Longest String Chain
//-------------------------------------------------------------------------------

class Solution
{
private:
    /**
     * @brief Checks if 'pred' can be formed by inserting exactly one character into 'succ'.
     * * --- TWO POINTER APPROACH ---
     * i tracks the longer string (succ), j tracks the shorter string (pred).
     * We count the number of mismatches. If the characters don't match, we increment
     * only the pointer for the longer string (i). If they do match, we increment both.
     * Finally, we add any leftover characters to the mismatch count.
     */
    bool insertDistance(const string &succ, const string &pred)
    {

        int n = succ.length();
        int m = pred.length();

        // 1. FAST FAIL: A valid predecessor MUST be exactly 1 character shorter.
        // If it isn't, there's no way a single insertion makes them equal.
        if (n != m + 1)
        {
            return false;
        }

        int i = 0; // Pointer traversing the longer string (succ)
        int j = 0; // Pointer traversing the shorter string (pred)
        int mismatch = 0;

        // Traverse both strings simultaneously
        while (i < n && j < m)
        {

            // 2. MISMATCH FOUND
            if (succ[i] != pred[j])
            {
                ++mismatch;

                // Since 'succ' is the longer string, we assume the current character
                // in 'succ' is the "extra" inserted character. We skip it by moving 'i'
                // forward, but keep 'j' where it is to compare against the next char.
                ++i;
            }
            // 3. MATCH FOUND
            else
            {
                // Characters match perfectly, move both pointers forward
                ++i;
                ++j;
            }
        }

        // 4. LEFTOVER CHARACTERS IN 'SUCC'
        // If 'pred' was completely traversed but 'succ' still has characters left,
        // those remaining characters are considered mismatches.
        if (i < n)
        {
            mismatch += (n - i);
        }

        // 5. LEFTOVER CHARACTERS IN 'PRED'
        // If 'succ' was traversed but 'pred' has characters left (mathematically rare
        // here due to the n != m+1 check, but good safety practice).
        if (j < m)
        {
            mismatch += (m - j);
        }

        // 6. FINAL VERDICT
        // For 'pred' to be a valid predecessor, there must be EXACTLY 1 mismatch
        // (which represents the 1 allowed insertion).
        return mismatch == 1;
    }

public:
    /**
     * @brief Computes the length of the longest possible word chain.
     * * --- APPROACH (LIS Variant) ---
     * 1. Sort the words by length. A word can only be a predecessor to a longer word.
     * 2. Use a 1D DP array where dp[i] represents the max chain length ending at words[i].
     * 3. For every word, look back at all previous (shorter) words. If a previous word
     * is a valid predecessor, extend the chain: dp[curI] = max(dp[curI], 1 + dp[preI]).
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N log N) for sorting + O(N^2 * L) for the nested DP loops and
     * string comparisons, where N is the number of words and L is the max word length.
     * Space Complexity : O(N) to store the DP array.
     */
    int longestStrChain(vector<string> &words)
    {
        int n = words.size();

        // Edge case: No words means no chain possible.
        if (n == 0)
            return 0;

        // --- STEP 1: PRE-PROCESSING (SORT BY LENGTH) ---
        // We MUST evaluate shorter words first. By sorting from shortest to longest,
        // we guarantee that by the time we evaluate words[curI], all of its potential
        // predecessors (which must be shorter) have already been fully calculated.
        sort(words.begin(), words.end(), [](const string &a, const string &b)
             { return a.length() < b.length(); });

        // --- STEP 2: DP ARRAY INITIALIZATION ---
        // dp[i] stores the length of the longest valid chain ending EXACTLY at words[i].
        // Initialize all to 1, because every individual word forms a valid chain of length 1.
        vector<int> dp(n, 1);

        // Tracker for the absolute longest chain found anywhere in the array
        int maxChainLen = 1;

        // --- STEP 3: BOTTOM-UP DP TRANSITIONS ---
        // Evaluate every word acting as the "end" of our chain
        for (int curI = 1; curI < n; ++curI)
        {
            // Look backward at every previously evaluated word
            for (int preI = 0; preI < curI; ++preI)
            {
                // Check if the previous word is a valid 1-character predecessor
                if (insertDistance(words[curI], words[preI]))
                {
                    // If it is, the new chain length would be the longest chain
                    // ending at the predecessor, plus 1 (for the current word).
                    int take = 1 + dp[preI];

                    // Take the best option: either our current known best for curI,
                    // or this newly discovered extended chain.
                    dp[curI] = max(dp[curI], take);
                }
            }

            // --- STEP 4: TRACK GLOBAL MAXIMUM ---
            // Update our global tracker to ensure we don't lose the max value
            maxChainLen = max(maxChainLen, dp[curI]);
        }

        // Return the length of the longest chain found
        return maxChainLen;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
