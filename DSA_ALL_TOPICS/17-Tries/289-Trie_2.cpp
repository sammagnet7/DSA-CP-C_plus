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

1. Title: Implement Trie - II

Links:
https://takeuforward.org/data-structure/implement-trie-ii/
https://www.youtube.com/watch?v=K5pcpkEMCN0
https://takeuforward.org/plus/dsa/problems/trie-implementation-and-advanced-operations?tab=editorial
https://www.naukri.com/code360/problems/implement-trie_1387095?leftPanelTabValue=PROBLEM


Problem statement:
Implement "TRIE” data structure from scratch with the following functions.
    Trie(): Initialize the object of this “TRIE” data structure.
    insert(“WORD”): Insert the string “WORD” into this “TRIE” data structure.
    countWordsEqualTo(“WORD”): Return how many times this “WORD” is present in this “TRIE”.
    countWordsStartingWith(“PREFIX”): Return how many words are there in this “TRIE” that have the string “PREFIX” as a prefix.
    erase(“WORD”): Delete one occurrence of the string “WORD” from the “TRIE”.

Examples:
    Input : ["Trie", "insert", "countWordsEqualTo", "insert", "countWordsStartingWith", "erase", "countWordsStartingWith"]
    [ "apple", "apple", "app", "app", "apple", "app" ]
    Output : [null, null, 1, null, 2, null, 1]
    Explanation :
    Trie trie = new Trie()
    trie.insert("apple")
    trie.countWordsEqualTo("apple")  // return 1
    trie.insert("app")
    trie.countWordsStartingWith("app") // return 2
    trie.erase("apple")
    trie.countWordsStartingWith("app")   // return 1

    Input : ["Trie", "insert", "countWordsEqualTo", "insert", "erase", "countWordsStartingWith"]
    [ "mango", "apple", "app", "app", "mango" ]
    Output : [null, null, 0, null, null, 1]
    Explanation :
    Trie trie = new Trie()
    trie.insert("mango")
    trie.countWordsEqualTo("apple")  // return 0
    trie.insert("app")
    trie.erase("app")
    trie.countWordsStartingWith("mango") // return 1


Constraints:
    1 <= word.length , prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3*104 calls in total will be made to insert, countWordsEqualTo , countWordsStartingWith and erase.


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
// 1. Title: Implement Trie - II
//-------------------------------------------------------------------------------


/**
 * @class TrieNode
 * @brief Represents a single character node in an Advanced Prefix Tree (Trie II).
 * Unlike a standard Trie that only tracks booleans, this node tracks frequencies.
 */
class TrieNode
{
public:
    vector<TrieNode *> children;
    int cntEndWith; // Tracks how many explicit words terminate at this node
    int cntPrefix;  // Tracks how many words share this node as part of their path

    TrieNode()
    {
        children.resize(26, nullptr);
        cntEndWith = 0;
        cntPrefix = 0;
    }

    /**
     * @brief Cascading Destructor for RAII memory management.
     * Recursively deletes all children before deleting itself (Post-Order).
     */
    ~TrieNode()
    {
        for (int i = 0; i < 26; ++i)
        {
            if (children[i] != nullptr)
            {
                delete children[i];
                children[i] = nullptr;
            }
        }
    }
};

/**
 * @class Trie
 * @brief Advanced Prefix Tree supporting insertion, deletion, and frequency counting.
 */
class Trie
{
private:
    TrieNode *root;

    /**
     * @brief Recursive helper to physically delete branches when words are erased.
     * * @param wi The current character index in the word.
     * @param word The word being erased.
     * @param curNode The parent node we are currently standing on.
     * * Approach (Post-Order Traversal):
     * 1. Base Case: Dive all the way to the end of the word first. Decrement
     * `cntEndWith` to remove one instance of the explicit word.
     * 2. On the way back UP the recursion stack, decrement `cntPrefix` for each child.
     * 3. If a child's `cntPrefix` hits 0, no words use it anymore. Physically
     * `delete` it to prevent memory bloat, and sever the pointer.
     * * Time Complexity: O(L) where L is the length of the word.
     * Space Complexity: O(L) for the recursion call stack.
     */
    void erase(int wi, string &word, TrieNode *curNode)
    {

        // Base Case: We have reached the final character's node.
        if (wi == word.length())
        {
            --(curNode->cntEndWith);
            return;
        }

        char c = word[wi];
        int idx = c - 'a';
        TrieNode *nextNode = curNode->children[idx];

        if (nextNode != nullptr)
        {
            // Dive deeper
            erase(wi + 1, word, nextNode);

            // Backtrack: Decrement prefix count on the way up
            --(nextNode->cntPrefix);

            // Physical Cleanup: If no words pass through here, destroy the node.
            if (nextNode->cntPrefix <= 0)
            {
                delete nextNode; // Triggers ~TrieNode() cascading delete if needed
                curNode->children[idx] = nullptr;
            }
        }
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root;
    }

    /**
     * @brief Inserts a word into the Trie and updates frequency counters.
     * * Approach:
     * - Iterate through the string. Create missing nodes as needed.
     * - Every time we step INTO a node, increment its `cntPrefix` because
     * this new word is now utilizing this path.
     * - At the final node, increment `cntEndWith`.
     * * Time Complexity: O(L) where L is the length of the word.
     * Space Complexity: O(L) worst case if a completely new branch is built.
     */
    void insert(string &word)
    {
        TrieNode *curNode = root;

        for (char c : word)
        {
            int idx = c - 'a';
            if (curNode->children[idx] == nullptr)
            {
                curNode->children[idx] = new TrieNode();
            }
            curNode = curNode->children[idx];
            ++(curNode->cntPrefix);
        }

        ++(curNode->cntEndWith);
    }

    /**
     * @brief Counts exactly how many times a word was inserted into the Trie.
     * * Approach:
     * - Walk down the path of the word. If at any point the path breaks (nullptr),
     * the word doesn't exist, return 0.
     * - If we successfully reach the end, return the node's `cntEndWith`.
     * * Time Complexity: O(L)
     * Space Complexity: O(1)
     */
    int countWordsEqualTo(string &word)
    {
        TrieNode *curNode = root;

        for (char c : word)
        {
            int idx = c - 'a';
            if (curNode->children[idx] == nullptr)
            {
                return 0;
            }
            curNode = curNode->children[idx];
        }

        return curNode->cntEndWith;
    }

    /**
     * @brief Counts how many words share the given prefix.
     * * Approach:
     * - Walk down the prefix path. If it breaks, 0 words share this prefix.
     * - If we reach the end of the prefix, return the `cntPrefix` counter,
     * which perfectly tracks how many words branched off from this point.
     * * Time Complexity: O(L)
     * Space Complexity: O(1)
     */
    int countWordsStartingWith(string &word)
    { // Note: variable named 'word' but acts as 'prefix'
        TrieNode *curNode = root;

        for (char c : word)
        {
            int idx = c - 'a';
            if (curNode->children[idx] == nullptr)
            {
                return 0;
            }
            curNode = curNode->children[idx];
        }

        return curNode->cntPrefix;
    }

    /**
     * @brief Public wrapper to erase one occurrence of a word.
     * Note: Problem constraints guarantee the word already exists in the Trie.
     * Time Complexity: O(L)
     */
    void erase(string &word)
    {
        erase(0, word, root);
    }
};

int main()
{
    using namespace std;

    Trie t;

    string a = "apple";
    string b = "app";
    string c = "bat";
    string d = "ball";
    string e = "ba";
    string x = "cat";

    // Insert words (with duplicates to test counts)
    t.insert(a); // "apple"
    t.insert(a); // "apple" again
    t.insert(b); // "app"
    t.insert(c); // "bat"
    t.insert(d); // "ball"
    t.insert(d); // "ball" again

    // Initial counts
    cout << t.countWordsEqualTo(a) << "\n"; // expect 2 ("apple" inserted twice)
    cout << t.countWordsEqualTo(b) << "\n"; // expect 1
    cout << t.countWordsEqualTo(d) << "\n"; // expect 2
    cout << t.countWordsEqualTo(x) << "\n"; // expect 0 (not inserted)

    // Prefix counts
    cout << t.countWordsStartingWith(b) << "\n"; // "app": matches "app"(1) + "apple"(2) => 3
    cout << t.countWordsStartingWith(e) << "\n"; // "ba": matches "bat"(1) + "ball"(2) => 3
    cout << t.countWordsStartingWith(x) << "\n"; // "cat": expect 0

    // Erase some words
    t.erase(a); // remove one "apple"
    t.erase(d); // remove one "ball"

    // Counts after erase
    cout << t.countWordsEqualTo(a) << "\n";      // expect 1
    cout << t.countWordsEqualTo(d) << "\n";      // expect 1
    cout << t.countWordsStartingWith(b) << "\n"; // "app": now "app"(1) + "apple"(1) => 2
    cout << t.countWordsStartingWith(e) << "\n"; // "ba": now "bat"(1) + "ball"(1) => 2

    return 0;
}
