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

1. Title: Implement Trie - 1 : Standard Tries (Strings & Prefixes)

Links:
https://takeuforward.org/data-structure/implement-trie-1/
https://www.youtube.com/watch?v=dBGUmUQhjaM&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp
https://takeuforward.org/plus/dsa/problems/trie-implementation-and-operations?tab=editorial
https://leetcode.com/problems/implement-trie-prefix-tree/


Problem statement:
A trie (pronounced as "try", short for Retrieval Tree) or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. This data structure built purely for raw speed and text processing. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:
Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix `prefix`, and false otherwise.


Example 1:
    Input
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    Output
    [null, null, true, false, true, null, true]
    Explanation
    Trie trie = new Trie();
    trie.insert("apple");
    trie.search("apple");   // return True
    trie.search("app");     // return False
    trie.startsWith("app"); // return True
    trie.insert("app");
    trie.search("app");     // return True


Constraints:
    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.


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
// 1. Title: Implement Trie - 1 : Basics : prefix existence
//-------------------------------------------------------------------------------

/**
 * @class TrieNode
 * @brief Represents a single character node within the Trie.
 * * Note: The node does not explicitly store its own character. Instead, its
 * character value is implicitly defined by the index (0-25) it occupies in
 * its parent's `children` vector.
 */
class TrieNode
{
public:
    vector<TrieNode *> children;
    // TrieNode* children[10] = {nullptr}; -> More optimized
    
    bool isEndOfWord;

    /**
     * @brief Constructs a new TrieNode.
     * Initializes a vector of 26 null pointers (representing 'a' through 'z')
     * and defaults the end-of-word flag to false.
     */
    TrieNode()
    {
        children.resize(26, nullptr);
        isEndOfWord = false;
    }

    /**
     * @brief Destructor to safely deallocate heap memory (Cascading Delete).
     * * By placing the deletion logic inside the Node itself, we leverage RAII
     * (Resource Acquisition Is Initialization). When a parent node is deleted,
     * it automatically triggers the deletion of all its children first via
     * Post-Order Traversal. This guarantees zero memory leaks.
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

// -----------------------------------------------------------------------------
// Trie Class: Main data structure
// Supports operations:
//   - insert(word)   → O(L)   (L = word length)
//   - search(word)   → O(L)   (true if word exists in Trie)
//   - startsWith(pre)→ O(L)   (true if any word starts with given prefix)
// -----------------------------------------------------------------------------

/**
 * @class Trie
 * @brief A Prefix Tree used for ultra-fast string retrieval and prefix matching.
 *
 * ============================================================================
 * 🧠 INTUITION & ARCHITECTURE
 * ============================================================================
 * The Trie stores strings as overlapping paths of characters. Words that share
 * the same prefix (e.g., "apple" and "ape") share the same parent nodes in memory,
 * branching off only when their characters differ.
 * * This provides strict O(L) time complexity for searches (where L is word length),
 * massively outperforming standard Hash Sets when querying prefixes.
 */
class Trie
{
private:
    TrieNode *root;

public:
    /**
     * @brief Initializes the Trie with an empty root node.
     * The root node conceptually represents the empty string ("").
     */
    Trie()
    {
        root = new TrieNode();
    }

    /**
     * @brief Destructor to safely tear down the entire Trie.
     * Deleting the root triggers the cascading `~TrieNode()` destructors,
     * safely wiping the entire tree from the heap in a single, elegant line.
     */
    ~Trie()
    {
        delete root;
    }

    /**
     * @brief Inserts a word into the Trie.
     * @param word The lowercase English string to insert.
     * * Time Complexity: O(L) where L is the length of the word.
     * Space Complexity: O(L) worst case if no prefix overlaps with existing words.
     */
    void insert(string word)
    {
        TrieNode *curNode = root;

        for (char c : word)
        {
            int idx = c - 'a';

            // If the path for this character doesn't exist, dynamically build it.
            if (curNode->children[idx] == nullptr)
            {
                curNode->children[idx] = new TrieNode();
            }

            // Step down to the next node.
            curNode = curNode->children[idx];
        }

        // Lock in the word by marking the final character's node.
        curNode->isEndOfWord = true;
    }

    /**
     * @brief Searches for a complete word in the Trie.
     * @param word The lowercase English string to search for.
     * @return True if the exact word is in the Trie, False otherwise.
     * * Time Complexity: O(L) where L is the length of the word.
     * Space Complexity: O(1) auxiliary space.
     */
    bool search(string word)
    {
        TrieNode *curNode = root;

        for (char c : word)
        {
            int idx = c - 'a';

            // If the path breaks before the word ends, the word does not exist.
            if (curNode->children[idx] == nullptr)
            {
                return false;
            }
            curNode = curNode->children[idx];
        }

        // We survived the loop, but we must check if this specific node was
        // explicitly marked as the end of an inserted word.
        return curNode->isEndOfWord;
    }

    /**
     * @brief Checks if there is any word in the Trie that starts with the given prefix.
     * @param prefix The lowercase English prefix to search for.
     * @return True if the prefix exists, False otherwise.
     * * Time Complexity: O(L) where L is the length of the prefix.
     * Space Complexity: O(1) auxiliary space.
     */
    bool startsWith(string prefix)
    {
        TrieNode *curNode = root;

        for (char c : prefix)
        {
            int idx = c - 'a';

            // If the path breaks, no words exist with this prefix.
            if (curNode->children[idx] == nullptr)
            {
                return false;
            }
            curNode = curNode->children[idx];
        }

        // If we successfully navigated the entire prefix string without hitting
        // a nullptr, the prefix exists. We do not care if it's the end of a full word.
        return true;
    }
};

/**
 * Usage Example:
 * Trie* obj = new Trie();
 * obj->insert("apple");
 * bool param_2 = obj->search("apple");   // returns true
 * bool param_3 = obj->search("app");     // returns false
 * bool param_4 = obj->startsWith("app"); // returns true
 * delete obj; // Safely cleans up memory via RAII
 */

int main()
{
    Trie *obj = new Trie();

    // Insert words
    obj->insert("apple");
    obj->insert("app");
    obj->insert("bat");

    // Search test cases
    cout << boolalpha;
    cout << "Search 'apple': " << obj->search("apple") << endl; // true
    cout << "Search 'app': " << obj->search("app") << endl;     // true
    cout << "Search 'appl': " << obj->search("appl") << endl;   // false
    cout << "Search 'bat': " << obj->search("bat") << endl;     // true
    cout << "Search 'bad': " << obj->search("bad") << endl;     // false

    // Prefix test cases
    cout << "Starts with 'app': " << obj->startsWith("app") << endl; // true
    cout << "Starts with 'ba': " << obj->startsWith("ba") << endl;   // true
    cout << "Starts with 'cat': " << obj->startsWith("cat") << endl; // false

    delete obj; // free memory
    return 0;
}
