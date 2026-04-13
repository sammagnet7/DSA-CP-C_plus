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

1. Title: Word Search II

Links:
https://leetcode.com/problems/word-search-ii/description/


Problem statement:
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Examples:
    Example 1:
                o a a n
                e t a e
                i h k r
                i f l v
    Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
    Output: ["eat","oath"]

    Example 2:
                a b
                c d
    Input: board = [["a","b"],["c","d"]], words = ["abcb"]
    Output: []


Constraints:
    m == board.length
    n == board[i].length
    1 <= m, n <= 12
    board[i][j] is a lowercase English letter.
    1 <= words.length <= 3 * 10^4
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.
    All the strings of words are unique.


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
// 1. Title: Word Search II
//-------------------------------------------------------------------------------

// ================================
// Approach 1: Trie + DFS
// ================================

/**
 * @class TrieNode
 * @brief Highly optimized Prefix Tree Node for Word Search II.
 */
class TrieNode
{
public:
    // OPTIMIZATION: Raw arrays avoid the massive memory and performance overhead of std::vector
    TrieNode *children[26];

    // OPTIMIZATION: Instead of building strings character by character during DFS,
    // we store a direct memory pointer to the original word.
    const string *wordPtr;

    TrieNode()
    {
        for (int i = 0; i < 26; ++i)
        {
            children[i] = nullptr;
        }
        wordPtr = nullptr;
    }
};

/**
 * @class Trie
 * @brief Combines a Prefix Tree with a Grid DFS to solve Word Search II.
 * * ============================================================================
 * 🧠 IDEA & INTUITION
 * ============================================================================
 * Doing a standard DFS for every single word in the dictionary takes too long.
 * Instead, we put all the words into a Trie, and we only do a DFS on the grid ONCE
 * per cell. As the DFS walks around the grid, it simultaneously walks down the Trie.
 * If the DFS tries to step on a letter that doesn't exist in the current Trie node,
 * we immediately kill that DFS branch. The Trie acts as a massive "pruning" machine.
 * * ============================================================================
 * ⏱️ COMPLEXITY ANALYSIS
 * ============================================================================
 * - Time Complexity: O(W * L + M * N * 3^L)
 * -> W * L to build the Trie (W = number of words, L = max length of a word).
 * -> M * N to start a DFS from every cell on the board.
 * -> 3^L for the DFS traversal. (It is 3^L instead of 4^L because we never look
 * backward at the cell we just came from). The Trie drastically reduces the
 * average case by pruning dead ends instantly.
 * - Space Complexity: O(W * L)
 * -> O(W * L) to store the characters in the Trie.
 * -> O(L) for the recursive DFS call stack.
 * -> O(1) auxiliary space on the board (In-place visited tracking via '#').
 */
class Trie
{
private:
    TrieNode *root;

    // Direction array for standard Up, Right, Down, Left movement
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

public:
    Trie()
    {
        root = new TrieNode();
    }

    /**
     * @brief Inserts a dictionary word into the Trie.
     */
    void insert(const string &word)
    {
        TrieNode *curNode = root;

        for (int i = 0; i < word.size(); ++i)
        {
            int idx = word[i] - 'a';

            if (curNode->children[idx] == nullptr)
            {
                curNode->children[idx] = new TrieNode();
            }

            curNode = curNode->children[idx];
        }

        // Store the memory address of the word so we can grab it in O(1) time later
        curNode->wordPtr = &word;
    }

    /**
     * @brief Simultaneous Grid DFS and Trie Traversal.
     * @param x, y Current coordinates on the grid.
     * @param curNode Current node in the Trie.
     * @param board The character grid (passed by reference to modify in-place).
     * @param ans The reference array storing found words.
     * @param m, n Dimensions of the board.
     * * * APPROACH / STEP-BY-STEP LOGIC:
     * 1. Initialize Root: If starting a fresh DFS, point `curNode` to the Trie root.
     * 2. Prune: Look ahead in the Trie. If the current board character doesn't match
     * a valid Trie path, immediately return and kill the branch.
     * 3. Word Match: If the new Trie node has a `wordPtr`, we found a complete word.
     * Add it to our answers and set `wordPtr` to nullptr to prevent duplicates.
     * 4. Mark Visited: Temporarily change the board character to '#' to avoid cycles.
     * 5. Explore: Loop through 4 directions. Check bounds and '#' BEFORE recursing.
     * 6. Backtrack: Restore the board character so other DFS branches can use this cell.
     */
    void findMatches(int x, int y, TrieNode *curNode, vector<vector<char>> &board, vector<string> &ans, int m, int n)
    {

        // STEP 1: If this is the start of a new DFS from the Solution class, start at root
        if (curNode == nullptr)
        {
            curNode = root;
        }

        char curChar = board[x][y];
        int curIdx = curChar - 'a';
        TrieNode *nextNode = curNode->children[curIdx];

        // STEP 2: PRUNING - If the Trie doesn't have this letter, this path is a dead end
        if (nextNode == nullptr)
        {
            return;
        }

        // STEP 4 (Done slightly out of order to protect our curChar): Mark Visited in-place
        board[x][y] = '#';

        // STEP 3: Check if the node we just stepped onto marks the end of a valid word
        if (nextNode->wordPtr != nullptr)
        {
            string curWord = *(nextNode->wordPtr);
            ans.push_back(curWord);

            // DE-DUPLICATION: Remove the pointer so we never add this word again
            nextNode->wordPtr = nullptr;
        }

        // STEP 5: Explore 4 valid directions
        for (int k = 0; k < 4; ++k)
        {
            int nx = x + dir[k][0];
            int ny = y + dir[k][1];

            // BOUNDS & VISITED CHECK: Notice we safely check for '#' here to prevent
            // out-of-bounds array access inside the next recursive call.
            if (nx < 0 || ny < 0 || nx >= m || ny >= n || board[nx][ny] == '#')
            {
                continue;
            }

            findMatches(nx, ny, nextNode, board, ans, m, n);
        }

        // STEP 6: BACKTRACK - Restore the board character
        board[x][y] = curChar;
    }
};

class Solution
{
public:
    /**
     * @brief Main driver function to initialize the board and start the search.
     */
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {

        int m = board.size();
        int n = board[0].size();

        Trie trie;

        // 1. Build the Trie with all words from the dictionary
        for (const string &word : words)
        {
            trie.insert(word);
        }

        vector<string> ans;

        // 2. Start a fresh DFS from every single cell on the board
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // Pass nullptr to signal the DFS to start at the Trie root
                trie.findMatches(i, j, nullptr, board, ans, m, n);
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}