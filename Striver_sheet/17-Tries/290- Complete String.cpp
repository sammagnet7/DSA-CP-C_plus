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

1. Title: Longest String with All Prefixes

Links:
https://takeuforward.org/trie/longest-string-with-all-prefixes
https://www.youtube.com/watch?v=AWnBa91lThI&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=4
https://takeuforward.org/plus/dsa/problems/longest-word-with-all-prefixes?tab=editorial
https://www.naukri.com/code360/problems/complete-string_2687860?leftPanelTabValue=PROBLEM


Problem statement:
Ninja developed a love for arrays and strings so this time his teacher gave him an array of strings, ‘A’ of size ‘N’. Each element of this array is a string. The teacher taught Ninja about prefixes in the past, so he wants to test his knowledge.
A string is called a complete string if every prefix of this string is also present in the array ‘A’. Ninja is challenged to find the longest complete string in the array ‘A’.If there are multiple strings with the same length, return the lexicographically smallest one and if no string exists, return "None".

Note :
String ‘P’ is lexicographically smaller than string ‘Q’, if :
1. There exists some index ‘i’ such that for all ‘j’ < ‘i’ , ‘P[j] = Q[j]’ and ‘P[i] < Q[i]’. E.g. “ninja” < “noder”.
2. If ‘P’ is a prefix of string ‘Q’, e.g. “code” < “coder”.

Examples:
    Example 1:
    N = 4
    A = [ “ab” , “abc” , “a” , “bp” ]
    Explanation :
    Only prefix of the string “a” is “a” which is present in array ‘A’. So, it is one of the possible strings.
    Prefixes of the string “ab” are “a” and “ab” both of which are present in array ‘A’. So, it is one of the possible strings.
    Prefixes of the string “bp” are “b” and “bp”. “b” is not present in array ‘A’. So, it cannot be a valid string.
    Prefixes of the string “abc” are “a”,“ab” and “abc” all of which are present in array ‘A’. So, it is one of the possible strings.
    We need to find the maximum length string, so “abc” is the required string.

    Sample Input 1 :
        2
        6
        n ni nin ninj ninja ninga
        2
        ab bc
    Sample Output 1 :
        ninja
        None
    Explanation Of Sample Input 1 :
        For test case 1 we have,
        All the prefixes of “ninja” -> “n”, “ni”, “nin”, “ninj” and “ninja” are present in array ‘A’. So, “ninja” is a valid answer whereas for “ninga” , the prefix “ning” is not present in array ‘A’.
        So we output “ninja”.

    For test case 2 we have,
        The prefixes of “ab” are “a” and “ab”. “a” is not present in array ‘A’. So, “ab” is not a valid answer.
        The prefixes of “bc” are “b” and “bc”. “b” is not present in array ‘A’. So, “ab” is not a valid answer.
        Since none of the strings is a valid answer we output “None”.
    Sample Input 2 :
        2
        5
        g a ak szhkb hy
        4
        kez vfj vfjq vfjqo
    Sample Output 2 :
        ak
        None


Constraints :
    1 <= T <= 10
    1 <= N <= 10^5
    1 <= A[i].length <= 10^5
    A[i] only consists of lowercase english letters.
    Sum of A[i].length <= 10^5 over all test cases

    Time Limit : 1 sec



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
// 1. Title: Longest String with All Prefixes
//-------------------------------------------------------------------------------
//

#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------------------------------------
Problem context: "Complete String" helper using a Trie with counts.

Intuition:
- A string is called "complete" if all of its prefixes are present as complete
  words in the set. For example, "apple" is complete if "a", "ap", "app",
  "appl", and "apple" are all present in the input list.
- A Trie (prefix tree) augmented with:
    * prefixMatchCount: how many words pass through a node
    * endsWithCount: how many words end at a node
  lets us efficiently answer whether all prefixes of a word exist as words.

Approach (high-level):
1. Build a Trie and insert every word from the list, updating prefix and end counts.
2. For each candidate word s:
   - Walk down the Trie along s's characters.
   - After each step check if the node has endsWithCount > 0 (i.e., that prefix is a complete word).
   - If all prefixes are valid complete words, s is a "complete string".
3. Track the longest complete string; if tie on length pick lexicographically smallest.
4. If no complete string exists, return "None".

Complexity:
- Let N be total characters across all words and M be number of words.
- Building Trie: O(N) time, O(N) space (each character may create a node).
- Checking all words: for each word of length L, O(L) time. Total O(N) across all words.
- Overall time: O(N). Space: O(N) for the Trie.
-------------------------------------------------------------------------------
*/

// -----------------------------------------------------------------------------
// Node: a single Trie node
// - arr[26]: children pointers for letters 'a'..'z'
// - prefixMatchCount: number of words that pass through this node (prefix frequency)
// - endsWithCount   : number of words that end exactly at this node
// -----------------------------------------------------------------------------
class Node
{
private:
    // children links: index 0 -> 'a', 1 -> 'b', ..., 25 -> 'z'
    std::vector<Node *> arr;
    // how many words include the prefix represented by the path to this node
    int prefixMatchCount = 0;
    // how many words end exactly at this node
    int endsWithCount = 0;

public:
    // Constructor: initialize children to nullptr and counters to 0
    Node() : arr(std::vector<Node *>(26, nullptr))
    {
        prefixMatchCount = 0;
        endsWithCount = 0;
    }

    // Destructor: recursively delete children to avoid memory leaks
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

    // Does a child for this character index exist?
    bool charExists(int chID)
    {
        return (this->arr[chID] != nullptr);
    }

    // Create a new child node at chID and return it.
    // Note: newly created node's prefix count is incremented since it's part of a path.
    Node *insertChar(int chID)
    {
        Node *newN = new Node();
        this->arr[chID] = newN;
        newN->increasePrefixMatchCount();
        return newN;
    }

    // Return pointer to the child node at chID
    Node *getNextNode(int chID)
    {
        return this->arr[chID];
    }

    // Increase the number of words passing through this node (prefix count)
    void increasePrefixMatchCount()
    {
        this->prefixMatchCount++;
    }

    // Decrease the prefix count (used when erasing a word)
    void decreasePrefixMatchCount()
    {
        this->prefixMatchCount--;
    }

    // Increase count of words that end exactly at this node
    void insreaseEndsWithCount()
    {
        this->endsWithCount++;
    }

    // Decrease count of words that end exactly at this node
    void decreaseEndsWithCount()
    {
        this->endsWithCount--;
    }

    // How many words end at this node?
    int getEndsWithCount()
    {
        return this->endsWithCount;
    }

    // How many words share the prefix up to this node?
    int getPrefixMatchCount()
    {
        return this->prefixMatchCount;
    }
};

// -----------------------------------------------------------------------------
// Trie: public interface built on top of Node
// - root: the root node (doesn't store a character itself)
// Operations supported:
//   - insert(string&)
//   - countWordsEqualTo(string&)
//   - countWordsStartingWith(string&)
//   - erase(string&)
//   - isAllPrefixWordsPresent(string&)
// -----------------------------------------------------------------------------
class Trie
{
private:
    Node *root; // root of the trie (empty node)

public:
    // Constructor: allocate root node
    Trie()
    {
        root = new Node();
    }

    // Destructor: free entire trie recursively via Node destructor
    ~Trie()
    {
        delete root;
    }

    // -------------------------------------------------------------------------
    // insert(word)
    // - Traverse/extend the path for each character. For every visited/created node:
    //   * If it already exists, move to it and increase the prefix count.
    //   * If it does not exist, create it and (inside insertChar) increase prefix count.
    // - After finishing characters, increment endsWith count at terminal node.
    // Time: O(L), auxiliary space O(1)
    // -------------------------------------------------------------------------
    void insert(std::string &word)
    {
        Node *tmp = root;

        for (int i = 0; i < (int)word.size(); i++)
        {
            int chID = word[i] - 'a'; // map character to index [0..25]

            if (tmp->charExists(chID))
            {
                // Move to existing child and update its prefix count
                tmp = tmp->getNextNode(chID);
                tmp->increasePrefixMatchCount();
            }
            else
            {
                // Create child and move to it (insertChar increments prefix count)
                tmp = tmp->insertChar(chID);
            }
        }

        // Mark that one more word ends at this node
        tmp->insreaseEndsWithCount();
    }

    // -------------------------------------------------------------------------
    // countWordsEqualTo(word)
    // - Follow the path for 'word'; if any required child is missing -> return 0.
    // - Otherwise return the endsWith count at the terminal node.
    // Time: O(L)
    // -------------------------------------------------------------------------
    int countWordsEqualTo(std::string &word)
    {
        Node *tmp = root;

        for (int i = 0; i < (int)word.size(); i++)
        {
            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                // word not present
                return 0;
            }
            else
            {
                tmp = tmp->getNextNode(chID);
            }
        }

        return tmp->getEndsWithCount();
    }

    // -------------------------------------------------------------------------
    // countWordsStartingWith(prefix)
    // - Traverse characters of prefix; if missing -> return 0.
    // - Otherwise return prefixMatchCount at the final node of the prefix.
    // Time: O(L)
    // -------------------------------------------------------------------------
    int countWordsStartingWith(std::string &word)
    {
        Node *tmp = root;

        for (int i = 0; i < (int)word.size(); i++)
        {
            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                // No words have this prefix
                return 0;
            }
            else
            {
                tmp = tmp->getNextNode(chID);
            }
        }

        // Number of words sharing this prefix
        return tmp->getPrefixMatchCount();
    }

    // -------------------------------------------------------------------------
    // erase(word)
    // - Walk down the path of 'word' and decrement prefix counters.
    // - At the terminal node, decrement endsWith count.
    // - This version updates counts but does not free nodes even if counts drop to zero.
    // Time: O(L)
    // -------------------------------------------------------------------------
    void erase(std::string &word)
    {
        Node *tmp = root;

        for (int i = 0; i < (int)word.size(); i++)
        {
            int chID = word[i] - 'a';
            // Move to next node (assumes word exists at least once)
            tmp = tmp->getNextNode(chID);
            // Decrease prefix match count as this occurrence is being erased
            tmp->decreasePrefixMatchCount();
        }

        // Decrease terminal ends-with count
        tmp->decreaseEndsWithCount();
    }

    // -------------------------------------------------------------------------
    // isAllPrefixWordsPresent(word)
    // - Check whether every prefix of 'word' is itself a complete word in the Trie.
    // - Walk the Trie and at each step verify endsWithCount > 0 for that prefix.
    // - If any prefix is not a complete word, return false.
    // Time: O(L)
    // -------------------------------------------------------------------------
    bool isAllPrefixWordsPresent(std::string &word)
    {
        Node *tmp = root;

        for (int i = 0; i < (int)word.size(); i++)
        {
            int chID = word[i] - 'a';

            if (!tmp->charExists(chID))
            {
                // If the path doesn't exist, the prefix can't be present
                return false;
            }
            else
            {
                tmp = tmp->getNextNode(chID);
                // If this prefix hasn't been inserted as a full word (endsWithCount == 0),
                // then the word cannot be "complete"
                if (tmp->getEndsWithCount() == 0)
                    return false;
            }
        }

        // All prefixes exist as words
        return true;
    }
};

// -----------------------------------------------------------------------------
// completeString: Uses the Trie above to find the longest "complete" word.
// If multiple longest complete words exist, returns lexicographically smallest.
// If none are complete, returns "None".
// -----------------------------------------------------------------------------
string completeString(int n, vector<string> &a)
{
    Trie obj;

    // Insert all words into Trie
    for (string &s : a)
    {
        obj.insert(s);
    }

    string maxCompleteString = "None";
    int maxCompleteStringLen = 0;

    // Check each word if it's "complete"
    for (string &s : a)
    {
        bool isCompleteWord = obj.isAllPrefixWordsPresent(s);

        if (isCompleteWord)
        {
            // Prefer longer strings
            if ((int)s.size() > maxCompleteStringLen)
            {
                maxCompleteStringLen = s.size();
                maxCompleteString = s;
            }
            // If same length, pick lexicographically smaller
            else if ((int)s.size() == maxCompleteStringLen && s < maxCompleteString)
            {
                maxCompleteString = s;
            }
        }
    }

    return maxCompleteString;
}

int main()
{
    return 0;
}