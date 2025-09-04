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
//

// ---------------------------------------------
// Trie with Counts (Prefix Tree)
// ---------------------------------------------
// Intuition:
// A Trie efficiently stores strings so that common prefixes are shared.
// This variant also tracks:
//  - prefixMatchCount: how many words pass through a node (i.e., share this prefix)
//  - endsWithCount   : how many words end exactly at this node
//
// Supported operations (all O(L), where L = length of input string):
//  - insert(word): add a word; increments prefix counts along path and end count at last node
//  - countWordsEqualTo(word): return how many times 'word' was inserted
//  - countWordsStartingWith(prefix): return how many words start with 'prefix'
//  - erase(word): remove one occurrence of 'word'; decrements counts along the path
//
// Space Complexity:
// Let N be the total number of characters across all inserted words.
// Each unique path character may allocate a node with:
//   - 26 child pointers (for 'a'..'z')
//   - two integers (prefix and end counters)
// Total space is O(N) (26 is constant for lowercase English alphabet).
//
// Notes:
// - The code below preserves your exact logic and function names.
// - Only comments were added for clarity; no behavioral changes were made.
//

#include <bits/stdc++.h>

// -----------------------------------------------------------------------------
// Node: a single Trie node
// - arr[26]: children pointers for letters 'a'..'z'
// - prefixMatchCount: number of words that pass through this node (prefix frequency)
// - endsWithCount   : number of words that end exactly at this node
// -----------------------------------------------------------------------------
class Node
{
private:
    // Children links: index 0 -> 'a', 1 -> 'b', ..., 25 -> 'z'
    std::vector<Node *> arr;
    // Count of words that include the prefix represented by the path to this node
    int prefixMatchCount = 0;
    // Count of words that end exactly at this node
    int endsWithCount = 0;

public:
    // Constructor: initialize all children to nullptr; counts to 0
    Node() : arr(std::vector<Node *>(26, nullptr))
    {
        prefixMatchCount = 0;
        endsWithCount = 0;
    }

    // Destructor: recursively delete allocated children to prevent memory leaks
    ~Node()
    {
        for (int i = 0; i < 26; i++)
        {
            if (arr[i] != nullptr)
            {
                delete arr[i];
                arr[i] = nullptr;
            }
        }
    }

    // Return true if there is an existing child for character id chID (0..25)
    bool charExists(int chID)
    {
        return (this->arr[chID] != nullptr);
    }

    // Create a new child node at chID and return it
    // Also increments the child's prefix count because the new node is now part of a path
    Node *insertChar(int chID)
    {
        Node *newN = new Node();
        this->arr[chID] = newN;
        newN->increasePrefixMatchCount();
        return newN;
    }

    // Get pointer to the child node at chID
    Node *getNextNode(int chID)
    {
        return this->arr[chID];
    }

    // Increment the number of words passing through this node (prefix count)
    void increasePrefixMatchCount()
    {
        this->prefixMatchCount++;
    }

    // Decrement the number of words passing through this node (prefix count)
    void decreasePrefixMatchCount()
    {
        this->prefixMatchCount--;
    }

    // Increment the number of words ending at this node
    void insreaseEndsWithCount()
    {
        this->endsWithCount++;
    }

    // Decrement the number of words ending at this node
    void decreaseEndsWithCount()
    {
        this->endsWithCount--;
    }

    // Getter: how many words end at this node?
    int getEndsWithCount()
    {
        return this->endsWithCount;
    }

    // Getter: how many words share the prefix up to this node?
    int getPrefixMatchCount()
    {
        return this->prefixMatchCount;
    }
};

// -----------------------------------------------------------------------------
// Trie: public interface built on top of Node
// - root: the root node (doesn't store a character itself)
// Operations:
//   insert(string&), countWordsEqualTo(string&), countWordsStartingWith(string&), erase(string&)
// -----------------------------------------------------------------------------
class Trie
{

private:
    Node *root; // root of the trie (empty node)

public:
    // Constructor: allocate a fresh root node
    Trie()
    {
        root = new Node();
    }

    // Destructor: deletes root; nodes are freed recursively via Node::~Node
    ~Trie()
    {
        delete root;
    }

    // -------------------------------------------------------------------------
    // insert(word)
    // Traverse/extend the path for each character. For every visited/created node:
    //  - If it already exists, move to it and increase the prefix count.
    //  - If it does not exist, create it and (inside insertChar) increase prefix count.
    // Finally, mark the end node by increasing its endsWith count.
    // Time: O(L), Space: O(1) auxiliary (amortized)
    // -------------------------------------------------------------------------
    void insert(std::string &word)
    {
        // Write your code here.

        Node *tmp = root;

        for (int i = 0; i < word.size(); i++)
        {

            int chID = word[i] - 'a'; // map char to index [0..25]

            if (tmp->charExists(chID))
            {
                // Move to existing child and update its prefix count
                tmp = tmp->getNextNode(chID);
                tmp->increasePrefixMatchCount();
            }
            else
            {
                // Create child and move to it (insertChar also bumps prefix count)
                tmp = tmp->insertChar(chID);
            }
        }

        // Increase number of words that end exactly at this terminal node
        tmp->insreaseEndsWithCount();
    }

    // -------------------------------------------------------------------------
    // countWordsEqualTo(word)
    // Follow the path for 'word'; if any required child is missing -> 0.
    // Otherwise, return the endsWith count at the terminal node.
    // Time: O(L)
    // -------------------------------------------------------------------------
    int countWordsEqualTo(std::string &word)
    {
        // Write your code here.
        Node *tmp = root;

        for (int i = 0; i < word.size(); i++)
        {

            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                // Word not present in trie
                return 0;
            }
            else
            {
                tmp = tmp->getNextNode(chID);
            }
        }
        // Number of times this exact word was inserted
        return tmp->getEndsWithCount();
    }

    // -------------------------------------------------------------------------
    // countWordsStartingWith(prefix)
    // Traverse characters of prefix; if missing -> 0.
    // Otherwise return prefixMatchCount at the final node of the prefix.
    // Time: O(L)
    // -------------------------------------------------------------------------
    int countWordsStartingWith(std::string &word)
    {
        // Write your code here.
        Node *tmp = root;

        for (int i = 0; i < word.size(); i++)
        {

            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                // No word has this prefix
                return 0;
            }
            else
            {
                tmp = tmp->getNextNode(chID);
            }
        }
        // How many words share this prefix
        return tmp->getPrefixMatchCount();
    }

    // -------------------------------------------------------------------------
    // erase(word)
    // Assumes the word exists at least once.
    // Walk down the path of 'word' and decrement prefix counters.
    // At the terminal node, decrement endsWith count.
    // (This version does not physically delete nodes; it only updates counts.)
    // Time: O(L)
    // -------------------------------------------------------------------------
    void erase(std::string &word)
    {
        // Write your code here.
        Node *tmp = root;

        for (int i = 0; i < word.size(); i++)
        {

            int chID = word[i] - 'a';

            // Move down the path and decrement prefix count at each node
            tmp = tmp->getNextNode(chID);
            tmp->decreasePrefixMatchCount();
        }

        // Decrement how many words end at the terminal node
        tmp->decreaseEndsWithCount();
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
