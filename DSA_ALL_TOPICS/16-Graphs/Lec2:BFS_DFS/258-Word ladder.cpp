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

1. Title: Word Ladder - I


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

2. Title: Word Ladder-II

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
    sk == endWord.
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
    The sum of all shortest transformation sequences does not exceed 10^5.





INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Word Ladder - I
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Computes the length of the shortest transformation sequence.
     * * @idea
     * This is a shortest-path problem on an unweighted, implicit graph. Therefore,
     * Level-Order Breadth-First Search (BFS) is the optimal algorithm. The "levels"
     * of our BFS represent the number of transformation steps.
     * * @approach
     * 1. Load all valid words into an `unordered_set` for O(1) lookups.
     * 2. Start a BFS queue with the `beginWord` and set the step count to 1.
     * 3. For each word popped from the queue, generate all possible 1-letter mutations.
     * 4. If a mutated word exists in the dictionary, push it to the queue.
     * 5. CRITICAL: Erase the word from the set immediately. Removing it acts as our
     * O(1) visited tracking, preventing infinite loops (e.g., hot -> dot -> hot).
     * * @time O(N * L^2)
     * N is the number of words, L is the word length. We process up to N words.
     * For each word, we loop L times, replacing characters. Creating the new string
     * and hashing it for the set lookup takes O(L) time. (L * L * 26 -> O(L^2)).
     * * @space O(N * L)
     * We store up to N words in our `unordered_set` and the BFS `queue`.
     */
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {

        // --- STEP 1: INITIALIZE DICTIONARY & QUEUE ---
        unordered_set<string> dict(wordList.begin(), wordList.end());

        // If the target word isn't even in the dictionary, a path is impossible.
        if (dict.find(endWord) == dict.end())
        {
            return 0;
        }

        queue<string> q;
        q.push(beginWord);

        // The problem states the sequence length includes the starting word
        int steps = 1;

        // --- STEP 2: LEVEL-ORDER BFS ---
        while (!q.empty())
        {

            int qsize = q.size();

            // Process all words at the current transformation step
            while (qsize--)
            {

                string word = q.front();
                q.pop();

                // If we reached the target, return the steps immediately!
                if (word == endWord)
                {
                    return steps;
                }

                // --- GENERATE ALL 1-LETTER MUTATIONS ---
                for (int i = 0; i < word.length(); ++i)
                {

                    char originalChar = word[i]; // Remember the original letter

                    // Try replacing the current character with 'a' through 'z'
                    for (char c = 'a'; c <= 'z'; ++c)
                    {

                        // Don't bother checking the exact same word
                        if (c == originalChar)
                            continue;

                        word[i] = c; // Mutate the string

                        // If this valid mutation exists in our dictionary
                        if (dict.find(word) != dict.end())
                        {

                            q.push(word);

                            // Mark as visited by erasing it from the dictionary!
                            // This prevents other paths from redundantly processing it.
                            dict.erase(word);
                        }
                    }

                    // Backtrack the mutation so we can test the next letter position
                    word[i] = originalChar;
                }
            }

            // Increment steps after finishing a complete level of transformations
            steps++;
        }

        // Queue emptied, target never found
        return 0;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Word Ladder-II
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
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
