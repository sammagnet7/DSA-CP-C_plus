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

1. Title: Longest String with All Prefixes matched

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
// 1. Title: Longest String with All Prefixes matched
//-------------------------------------------------------------------------------

/**
 * @class TrieNode
 * @brief Represents a single character node in the Prefix Tree.
 */
class TrieNode
{
public:
    // Uses a vector of 26 pointers for 'a' through 'z'
    vector<TrieNode *> children;

    // True if this specific node marks the end of a completely inserted word
    bool isEndOfWord;

    /**
     * @brief Constructor using a Member Initializer List for optimal memory allocation.
     * Directly sizes the vector to 26 and fills it with nullptrs in one step.
     */
    TrieNode() : children(vector<TrieNode *>(26, nullptr))
    {
        isEndOfWord = false;
    }

    /**
     * @brief Cascading Destructor (RAII).
     * Recursively cleans up all child nodes before deleting the current node,
     * guaranteeing zero memory leaks without needing a separate cleanup function.
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
 * @brief A Prefix Tree customized to quickly validate "Complete Strings".
 */
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root; // Triggers the cascading ~TrieNode() destructor
    }

    /**
     * @brief Inserts a word into the Trie.
     * @param word Passed by constant reference to avoid expensive string copies.
     * * Time Complexity: O(L) where L is the length of the word.
     * Space Complexity: O(L) in the worst case (if no prefixes are shared).
     */
    void insert(const string &word)
    {
        TrieNode *curNode = root;

        for (auto c : word)
        {
            int idx = c - 'a';

            if (curNode->children[idx] == nullptr)
            {
                curNode->children[idx] = new TrieNode();
            }

            curNode = curNode->children[idx];
        }

        // Lock in the word by marking the final character's node
        curNode->isEndOfWord = true;
    }

    /**
     * @brief Checks if EVERY prefix of a given string exists as a standalone word in the Trie.
     * @param prefix The string to validate.
     * @return True if all prefixes exist, False if any prefix is missing.
     * * Time Complexity: O(L) where L is the length of the word.
     */
    bool isAllPrefixMatch(const string &prefix)
    {
        TrieNode *curNode = root;

        for (auto c : prefix)
        {
            int idx = c - 'a';

            // CRITICAL CHECK:
            // 1. If the node doesn't exist, the prefix is missing.
            // 2. If the node exists but isEndOfWord is false, it means this path
            //    was created by a longer word, but this specific prefix was NEVER
            //    inserted as a standalone word in the original array.
            if (curNode->children[idx] == nullptr || !(curNode->children[idx]->isEndOfWord))
            {
                return false;
            }

            curNode = curNode->children[idx];
        }

        return true;
    }
};

/**
 * @brief Finds the longest complete string in the array.
 * A string is "complete" if every single one of its prefixes is also in the array.
 * * @param n Size of the array.
 * @param a The array of strings.
 * @return The longest complete string, or "None" if no such string exists.
 * * Time Complexity: O(N * L) where N is the number of words and L is max length.
 * Space Complexity: O(N * L) for storing all characters in the Trie.
 */
string completeString(int n, vector<string> &a)
{
    Trie trie;
    string longestMatch = "";

    // Step 1: Populate the Trie with all words.
    // This establishes the 'isEndOfWord' truth map for every valid prefix.
    for (auto &s : a)
    {
        trie.insert(s);
    }

    // Step 2: Validate every word against the Trie.
    for (auto &s : a)
    {
        if (trie.isAllPrefixMatch(s))
        {

            // Step 3: Track the longest valid string
            if (s.length() > longestMatch.length())
            {
                longestMatch = s;
            }
            // Step 4: Tie-breaker - If lengths are equal, pick the lexicographically smaller one
            else if (s.length() == longestMatch.length() && s < longestMatch)
            {
                longestMatch = s;
            }
        }
    }

    // If no valid string was found, return "None" as required by the problem
    return longestMatch == "" ? "None" : longestMatch;
}

int main()
{
    return 0;
}