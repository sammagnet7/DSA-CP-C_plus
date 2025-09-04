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

1. Title: Implement Trie - 1

Links:
https://takeuforward.org/data-structure/implement-trie-1/
https://www.youtube.com/watch?v=dBGUmUQhjaM&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp
https://takeuforward.org/plus/dsa/problems/trie-implementation-and-operations?tab=editorial
https://leetcode.com/problems/implement-trie-prefix-tree/


Problem statement:
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:
Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.


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
    At most 3 * 104 calls in total will be made to insert, search, and startsWith.


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
// 1. Title: Implement Trie - 1
//-------------------------------------------------------------------------------
//

// -----------------------------------------------------------------------------
// Node Class: Represents a single Trie Node
// Each node stores:
//   - arr[26]: pointers to child nodes (for 'a' to 'z')
//   - endStatus: marks if the node represents the end of a valid word
// -----------------------------------------------------------------------------
class Node
{
private:
    vector<Node *> arr; // children links: size 26 (for lowercase English letters)
    bool endStatus;     // true if node represents the end of a word

public:
    // Constructor: initialize children as null, endStatus = false
    Node() : arr(vector<Node *>(26, nullptr))
    {
        endStatus = false;
    }

    // Destructor: recursively delete all children to free memory
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

    // Check if child node for character (chID) exists
    bool charExists(int chID)
    {
        return (this->arr[chID] != nullptr);
    }

    // Insert new child node for character (chID) and return pointer
    Node *insertChar(int chID)
    {
        Node *newN = new Node();
        this->arr[chID] = newN;
        return newN;
    }

    // Get pointer to child node for character (chID)
    Node *getNextNode(int chID)
    {
        return this->arr[chID];
    }

    // Update the end-of-word flag
    void updateEndStatus(bool status)
    {
        this->endStatus = status;
    }

    // Check if this node marks the end of a word
    bool getStatus()
    {
        return this->endStatus;
    }
};

// -----------------------------------------------------------------------------
// Trie Class: Main data structure
// Supports operations:
//   - insert(word)   → O(L)   (L = word length)
//   - search(word)   → O(L)   (true if word exists in Trie)
//   - startsWith(pre)→ O(L)   (true if any word starts with given prefix)
// -----------------------------------------------------------------------------
class Trie
{

private:
    Node *root; // Root node (does not store any character)

public:
    // Constructor: initialize empty Trie with root node
    Trie()
    {
        root = new Node();
    }

    // Destructor: delete entire Trie (frees memory recursively via Node destructor)
    ~Trie()
    {
        delete root;
    }

    // -------------------------------------------------------------------------
    // Insert a word into the Trie
    // Approach:
    // - Start from root, traverse each character
    // - If child node exists → move to it
    // - If not → create new node and move to it
    // - After last character, mark node as "end of word"
    // Complexity: O(L), where L = word length
    // -------------------------------------------------------------------------
    void insert(string word)
    {
        Node *tmp = this->root;

        for (int i = 0; i < word.size(); i++)
        {
            int chID = word[i] - 'a'; // map character → index [0-25]

            if (tmp->charExists(chID))
            {
                tmp = tmp->getNextNode(chID); // go to child
            }
            else
            {
                tmp = tmp->insertChar(chID); // create child if missing
            }
        }
        tmp->updateEndStatus(true); // mark last node as end of word
    }

    // -------------------------------------------------------------------------
    // Search for a complete word in the Trie
    // Approach:
    // - Traverse each character from root
    // - If at any step character link missing → word not found
    // - After last character, check end flag to ensure it's a full word
    // Complexity: O(L)
    // -------------------------------------------------------------------------
    bool search(string word)
    {
        Node *tmp = this->root;

        for (int i = 0; i < word.size(); i++)
        {
            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                return false; // missing link → word not present
            }
            tmp = tmp->getNextNode(chID);
        }

        return tmp->getStatus(); // must be marked as end of word
    }

    // -------------------------------------------------------------------------
    // Check if there exists any word with the given prefix
    // Approach:
    // - Traverse characters of prefix
    // - If missing link found → return false
    // - If all chars matched → return true
    // Complexity: O(L)
    // -------------------------------------------------------------------------
    bool startsWith(string prefix)
    {
        Node *tmp = this->root;

        for (int i = 0; i < prefix.size(); i++)
        {
            int chID = prefix[i] - 'a';

            if (!tmp->charExists(chID))
            {
                return false; // missing link → prefix not present
            }
            tmp = tmp->getNextNode(chID);
        }

        return true; // successfully matched full prefix
    }
};

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
