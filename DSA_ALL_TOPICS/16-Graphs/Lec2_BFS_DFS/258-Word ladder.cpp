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

// ======================================================
// Approach 1 : maintain ALL shortest paths [sub-optimal]
// ======================================================

class Solution
{
public:
    /**
     * @brief Finds all shortest transformation sequences from beginWord to endWord.
     * * @idea
     * We use a Level-Order BFS, but instead of just storing the current word, we store
     * the entire PATH taken to reach it. To ensure we find ALL shortest paths, we
     * cannot immediately delete a visited word from the dictionary (as another path
     * might need it on the same level). Instead, we track used words and delete them
     * at the END of each BFS level.
     * * @approach
     * 1. Initialize a queue holding paths (`vector<string>`).
     * 2. For each path popped, take the last word and generate all 1-letter mutations.
     * 3. If a mutation is valid, append it to the path and push the new path to the queue.
     * 4. If the mutation is `endWord`, flag `found = true` and save the path to `ans`.
     * 5. Collect all valid mutations in `usedWords` and erase them from `wordSet`
     * only after the current level (while(qSize--)) completely finishes.
     * 6. The outer loop naturally breaks early thanks to `!found`, ensuring we don't
     * keep digging deeper once the shortest paths are found!
     * * @time O(N * L^2 + P)
     * Where N is the dictionary size, L is word length, and P is the total number
     * of valid paths. The time can grow exponentially in the worst case if the graph
     * is highly dense and branches heavily.
     * * @space O(P * K)
     * Where P is the number of paths stored in the queue and K is the average path
     * length. Storing entire paths in the queue is very memory-intensive.
     */
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {

        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> ans;

        // Queue now holds the sequence of words (the path)
        queue<vector<string>> q;
        q.push({beginWord});

        // Flag to stop the BFS from going deeper once we find the shortest path layer
        bool found = false;

        // --- LEVEL-ORDER BFS ---
        while (!q.empty() && !found)
        {

            int qSize = q.size();

            // Tracks words visited DURING THIS SPECIFIC LEVEL
            unordered_set<string> usedWords;

            while (qSize--)
            {

                vector<string> curVec = q.front();
                q.pop();

                // The word we are currently trying to mutate is the last one in the path
                string curWord = curVec.back();

                // Generate all 1-letter mutations
                for (int i = 0; i < curWord.size(); ++i)
                {

                    char exChar = curWord[i];

                    for (char upChar = 'a'; upChar <= 'z'; ++upChar)
                    {

                        curWord[i] = upChar;

                        if (exChar == upChar)
                        {
                            continue;
                        }

                        if (wordSet.find(curWord) != wordSet.end())
                        {
                            // --- VALID NEIGHBOR FOUND ---
                            curVec.push_back(curWord);
                            q.push(curVec);

                            // EARLY EXIT CHECK: Did we hit the target?
                            if (curWord == endWord)
                            {
                                found = true; // Signals the outer loop to stop after this level
                                ans.push_back(curVec);
                            }

                            // Backtrack the path vector so we can reuse it for the next mutation
                            curVec.pop_back();

                            // Mark this word to be deleted at the end of the level
                            usedWords.insert(curWord);
                        }
                    }

                    // Backtrack the string mutation
                    curWord[i] = exChar;
                }
            }

            // --- DEFERRED ERASURE ---
            // Now that the level is over, delete the used words so deeper levels
            // don't visit them, preventing infinite loops.
            for (const string &used : usedWords)
            {
                wordSet.erase(used);
            }
        }

        return ans;
    }
};

// =================================
// Approach 2 : BFS + DFS [OPTIMAL]
// =================================

class Solution
{
private:
    // Maps each word to its shortest distance from the beginWord
    unordered_map<string, int> mpp;

    // Stores all valid shortest transformation sequences
    vector<vector<string>> ans;

    /**
     * @brief DFS helper to reconstruct paths by backtracking from endWord to beginWord.
     */
    void dfs(string word, string &beginWord, vector<string> &path)
    {

        // BASE CASE: We successfully backtracked all the way to the start!
        if (word == beginWord)
        {
            vector<string> validPath = path;
            // Because we built this path backwards (end -> begin), we must reverse it
            reverse(validPath.begin(), validPath.end());
            ans.push_back(validPath);
            return;
        }

        int currentSteps = mpp[word];

        // Generate all 1-letter mutations to find valid parents
        for (int i = 0; i < word.size(); ++i)
        {

            char originalChar = word[i];

            for (char c = 'a'; c <= 'z'; ++c)
            {

                word[i] = c;

                // STATE CHECK: Is this mutated word a valid parent?
                // It must exist in our BFS map AND it must be exactly 1 step
                // closer to the beginWord than our current word.
                if (mpp.count(word) && mpp[word] == currentSteps - 1)
                {

                    path.push_back(word);       // Add to current path
                    dfs(word, beginWord, path); // Plunge deeper backwards
                    path.pop_back();            // Backtrack to explore other routes
                }
            }

            word[i] = originalChar; // Restore the character
        }
    }

public:
    /**
     * @brief Finds all shortest transformation sequences.
     * * @idea
     * Storing entire `vector<string>` paths inside a BFS queue consumes massive memory
     * and causes MLE on highly branched graphs. To fix this, we split the logic:
     * 1. Use BFS ONLY to find the shortest distance from beginWord to every node.
     * 2. Use DFS to backtrack from endWord to beginWord, relying on the BFS distance map
     * to only step onto valid nodes that are exactly 1 step closer to the start.
     * * @approach
     * PHASE 1 (BFS Distances): Start a queue with beginWord. Generate 1-letter mutations.
     * If a valid word is found in the dictionary, record its distance in the map
     * (`mpp[word] = steps + 1`), queue it, and erase it from the set. Stop expanding
     * paths once the `endWord` level is reached.
     * PHASE 2 (DFS Backtracking): Start at `endWord`. Generate mutations. If a mutation
     * is in our map and its distance is `current_distance - 1`, recursively explore it.
     * When `beginWord` is reached, reverse the path and add it to our answers.
     * * @time O(N * L^2 + P * L)
     * N = dictionary size, L = word length, P = number of valid shortest paths.
     * BFS maps the distances in O(N * L^2). DFS reconstructs P paths, taking O(P * L).
     * * @space O(N * L)
     * We eliminated storing massive arrays in the queue. The BFS queue and distance map
     * only store strings and integers, dropping our memory footprint drastically to O(N * L).
     * DFS call stack takes at most O(N) space.
     */
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
    {

        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> q;

        // --- PHASE 1: BFS TO MAP SHORTEST DISTANCES ---
        q.push(beginWord);
        mpp[beginWord] = 1;
        st.erase(beginWord);

        while (!q.empty())
        {

            string word = q.front();
            q.pop();

            int steps = mpp[word];

            // Optimization: If we reached the endWord, we don't need to map anything further away.
            // We just need to finish processing the other words CURRENTLY at this distance level.
            if (word == endWord)
                break;

            for (int i = 0; i < word.size(); ++i)
            {

                char originalChar = word[i];

                for (char c = 'a'; c <= 'z'; ++c)
                {

                    word[i] = c;

                    // If we find an unvisited valid word
                    if (st.count(word))
                    {
                        q.push(word);
                        st.erase(word);        // Instantly erase to prevent redundant processing
                        mpp[word] = steps + 1; // Record its exact shortest distance
                    }
                }

                word[i] = originalChar; // Backtrack mutation
            }
        }

        // --- PHASE 2: DFS BACKTRACKING ---
        // If the endWord was never reached during BFS, it won't be in the map.
        // We only trigger DFS if a valid path actually exists!
        if (mpp.count(endWord))
        {
            vector<string> path;
            path.push_back(endWord);
            dfs(endWord, beginWord, path);
        }

        return ans;
    }
};

int main()
{
    return 0;
}
