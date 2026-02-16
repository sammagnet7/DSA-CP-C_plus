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

1. Title: Word Ladder - I : G-29


Links:
https://takeuforward.org/graph/word-ladder-i-g-29/
https://www.youtube.com/watch?v=tRPda0rcf8E
https://takeuforward.org/plus/dsa/problems/word-ladder-i?tab=editorial
https://leetcode.com/problems/word-ladder/description/


Problem statement:
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

Examples:
    Example 1:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    Output: 5
    Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

    Example 2:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    Output: 0
    Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.


Constraints:
    1 <= beginWord.length <= 10
    endWord.length == beginWord.length
    1 <= wordList.length <= 5000
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: G-30 : Word Ladder-II

Links:
https://takeuforward.org/graph/g-30-word-ladder-ii/
https://www.youtube.com/watch?v=AD4SFl7tu7I
https://takeuforward.org/plus/dsa/problems/word-ladder-ii?tab=editorial
https://leetcode.com/problems/word-ladder-ii/submissions/1747769329/    [To get rid of TLE check TUF+ 2nd approach]
https://www.geeksforgeeks.org/problems/word-ladder-ii/1 [Runs fine on GFG]

Problem statement:
    A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    sk == endWord
    Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

Examples:
    Example 1:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
    Explanation: There are 2 shortest transformation sequences:
    "hit" -> "hot" -> "dot" -> "dog" -> "cog"
    "hit" -> "hot" -> "lot" -> "log" -> "cog"

    Example 2:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    Output: []
    Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.


Constraints:
    1 <= beginWord.length <= 5
    endWord.length == beginWord.length
    1 <= wordList.length <= 500
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.
    The sum of all shortest transformation sequences does not exceed 105.





INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Word Ladder - I : G-29
    //-------------------------------------------------------------------------------

    /**
     * Function: ladderLength
     * -----------------------
     * Computes the shortest transformation sequence length from `beginWord` to `endWord`
     * where each transformation changes only one character at a time and every intermediate
     * word must exist in the given word list.
     *
     * Approach:
     * - Use **Breadth-First Search (BFS)** because we need the shortest path in an unweighted graph.
     * - Treat each word as a node, and an edge exists between two words if they differ by exactly one character.
     * - Start BFS from `beginWord` with initial level = 1.
     * - For each word, generate all possible words by changing each character to every letter from 'a' to 'z'.
     * - If the new word exists in the word set, add it to the BFS queue and remove it from the set (to avoid revisiting).
     * - If `endWord` is found during BFS, return the current level (distance).
     * - If BFS finishes without finding `endWord`, return 0.
     *
     * Time Complexity:
     * - Let N = number of words in wordList, L = length of each word.
     * - For each word popped from the queue, we generate 26 * L possible transformations.
     * - Each transformation check in the unordered_set takes O(1) average.
     * - In worst case, all N words are processed: O(N * L * 26) ≈ O(N * L).
     *
     * Space Complexity:
     * - O(N) for unordered_set + O(N) for BFS queue → O(N).
     *
     * @param beginWord: Starting word
     * @param endWord: Target word
     * @param wordList: List of allowed words
     * @return Length of shortest transformation sequence (or 0 if none exists)
     */
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {

        // Convert wordList to unordered_set for O(1) lookup
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // If endWord not in dictionary, no valid transformation exists
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        // BFS queue: stores {currentWord, currentLevel}
        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        // Perform BFS
        while (!q.empty())
        {
            string curW = q.front().first;
            int curLv = q.front().second;
            q.pop();

            // If we reached the endWord, return level (distance)
            if (curW == endWord)
                return curLv;

            // Try changing each character in current word
            for (int i = 0; i < curW.size(); i++)
            {
                char origCh = curW[i]; // store original character

                // Replace with all 26 letters
                for (int j = 0; j < 26; j++)
                {
                    curW[i] = 'a' + j;

                    // If transformed word exists in dictionary
                    if (wordSet.find(curW) != wordSet.end())
                    {
                        wordSet.erase(curW); // mark as visited
                        q.push({curW, curLv + 1});
                    }
                }

                // Restore original character for next iteration
                curW[i] = origCh;
            }
        }

        // No transformation possible
        return 0;
    }

    //-------------------------------------------------------------------------------
    // 2. Title: G-30 : Word Ladder-II
    //-------------------------------------------------------------------------------

    /**
     * Function: findSequences
     * -----------------------
     * Finds all the shortest transformation sequences from `beginWord` to `endWord` such that:
     * - Only one letter can be changed at a time.
     * - Every transformed word must exist in the given word list.
     *
     * Unlike the ladderLength function (which returns only the length), this function returns **all paths**
     * that achieve the minimum transformation length.
     *
     * Approach:
     * 1. Use **Breadth-First Search (BFS)** because we are interested in shortest paths.
     * 2. Maintain a queue where each element stores:
     *      - current BFS level
     *      - the current transformation sequence (vector<string>).
     * 3. For each word, generate all possible words by changing each character to 'a'..'z'.
     * 4. If a generated word is in the wordSet, push the new sequence into the queue.
     * 5. Use `temp_erase_list` to collect words seen in the current level and erase them
     *    from the set **only after the level completes** (to allow multiple paths in the same level).
     * 6. Stop BFS once `endWord` is found (since we only need shortest sequences).
     *
     * Time Complexity:
     * - Let N = number of words, L = length of each word.
     * - Each word can generate 26 * L new words → O(26 * L) per word.
     * - In worst case, BFS explores all N words: O(N * L * 26).
     * - Additionally, storing paths adds overhead, but still within O(N * L) for minimal paths.
     *
     * Space Complexity:
     * - O(N) for unordered_set (dictionary)
     * - O(N * L) for BFS queue (since each path can be up to L words).
     *
     * @param beginWord: The starting word
     * @param endWord: The target word
     * @param wordList: List of allowed words
     * @return A vector of all shortest transformation sequences
     */
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {

        vector<vector<string>> ans;

        // Store all words in a set for O(1) lookup
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // Queue for BFS: {currentLevel, transformationSequence}
        queue<pair<int, vector<string>>> q;
        q.push({1, {beginWord}});

        bool found = false;                           // Flag to stop when we find the shortest sequences
        int prevLv = -1;                              // Tracks previous BFS level
        vector<string> temp_erase_list = {beginWord}; // Words to erase after level completes

        while (!q.empty())
        {
            int curLv = q.front().first;
            vector<string> curList = q.front().second;
            string curW = curList.back();
            q.pop();

            // When we reach a new level, erase all words from previous level
            if (prevLv < curLv)
            {
                if (found)
                    break; // Stop BFS if we've already found shortest sequences

                for (string s : temp_erase_list)
                    wordSet.erase(s);

                temp_erase_list.clear();
                prevLv = curLv;
            }

            // If we found endWord, store the current sequence
            if (curW == endWord)
            {
                found = true;
                ans.push_back(curList);
                continue; // Continue to find other sequences in the same level
            }

            // Try replacing each character of curW with 'a'..'z'
            for (int i = 0; i < curW.size(); i++)
            {
                char origChar = curW[i];

                for (int j = 0; j < 26; j++)
                {
                    curW[i] = 'a' + j;

                    // If transformed word exists in dictionary and not yet erased
                    if (wordSet.find(curW) != wordSet.end())
                    {
                        curList.push_back(curW);
                        q.push({curLv + 1, curList});
                        temp_erase_list.push_back(curW);
                        curList.pop_back(); // Backtrack
                    }
                }

                // Restore original character
                curW[i] = origChar;
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}
