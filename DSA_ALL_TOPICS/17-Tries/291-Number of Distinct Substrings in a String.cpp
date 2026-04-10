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

1. Title: Number of Distinct Substrings in a String

Links:
https://takeuforward.org/data-structure/number-of-distinct-substrings-in-a-string-using-trie/
https://www.youtube.com/watch?v=RV0QeTyHZxo&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=5
https://takeuforward.org/plus/dsa/problems/number-of-distinct-substrings-in-a-string?tab=editorial
https://www.naukri.com/code360/problems/count-distinct-substrings_985292?leftPanelTabValue=PROBLEM


Problem statement:
Given a string 'S', you are supposed to return the number of distinct substrings(including empty substring) of the given string. You should implement the program using a trie.
Note :
A string ‘B’ is a substring of a string ‘A’ if ‘B’ that can be obtained by deletion of, several characters(possibly none) from the start of ‘A’ and several characters(possibly none) from the end of ‘A’.

Two strings ‘X’ and ‘Y’ are considered different if there is at least one index ‘i’  such that the character of ‘X’ at index ‘i’ is different from the character of ‘Y’ at index ‘i’(X[i]!=Y[i]).


Constraints :
1 <= T <= 5
1 <= |S| <= 10^3
‘S’ contains only lowercase English letters.
Time Limit: 1 sec

Sample Input 1 :
2
sds
abc
Sample Output 1 :
6
7
Explanation of Sample Input 1 :
In the first test case, the 6 distinct substrings are { ‘s’,’ d’, ”sd”, ”ds”, ”sds”, “” }
In the second test case, the 7 distinct substrings are {‘a’, ‘b’, ‘c’, “ab”, “bc”, “abc”, “” }.

Sample Input 2 :
2
aa
abab
Sample Output 2 :
3
8
Explanation of Sample Input 2 :
In the first test case, the two distinct substrings are {‘a’, “aa”, “” }.
In the second test case, the seven distinct substrings are {‘a’, ‘b’, “ab”, “ba”, “aba”, “bab”, “abab”, “” }


Hints:
1. Can you think about a data structure that can be used to store the distinct substrings?
2. Can you think about using the fact that every substring of ‘S’ is a prefix of some suffix string of ‘S’?
3. Try to insert every suffix of the string in Trie.


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
// 1. Title: Number of Distinct Substrings in a String Using Trie
//-------------------------------------------------------------------------------
//

#include <unordered_set>
class Solution
{
    // -----------------------------------------------------------------------------
    // Approach1: Count Distinct Substrings (Suboptimal Approach)
    // -----------------------------------------------------------------------------
    // Idea:
    //   Generate all substrings and store them in a set to remove duplicates.
    //   The size of the set = number of distinct substrings.
    //
    // Complexity:
    //   - Time: O(n^3) (O(n^2) substrings * O(n) copy per substring).
    //   - Space: O(n^2) for storing substrings.
    //   Works only for very small strings. Efficient methods use SAM or Suffix Array.
    // -----------------------------------------------------------------------------

    int countDistinctSubstrings(string &s)
    {
        int n = s.size();
        unordered_set<string> subStrs;
        subStrs.insert(""); // include the empty substring

        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j >= i; j--)
            {
                subStrs.insert(s.substr(i, (j - i + 1)));
            }
        }

        return subStrs.size();
    }
};

// -----------------------------------------------------------------------------
// Approach2: Trie-based solution [Optimal Approach]
// -----------------------------------------------------------------------------

/**
 * @class TrieNode
 * @brief Stripped-down Prefix Tree Node optimized for substring counting.
 * Note: We omit the standard `isEndOfWord` boolean here because in this specific
 * algorithm, every single physically created node represents a valid, distinct substring.
 */
class TrieNode
{
public:
    // Raw array for maximum performance and minimum memory overhead
    TrieNode *children[26];

    /**
     * @brief Constructs a new TrieNode and initializes child pointers.
     */
    TrieNode()
    {
        for (int i = 0; i < 26; ++i)
        {
            children[i] = nullptr;
        }
    }

    /**
     * @brief Cascading Destructor (RAII).
     * Recursively deletes all child nodes before deleting itself (Post-Order).
     * This guarantees zero memory leaks when the root Trie dies.
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
 * @brief Specialized Trie to count distinct substrings using the "Prefix of a Suffix" method.
 */
class Trie
{
private:
    TrieNode *root;

    // Encapsulated state to track the number of distinct substrings discovered
    int nodeCount;

public:
    /**
     * @brief Initializes the Trie.
     * nodeCount starts at 1 to automatically account for the empty string ("").
     */
    Trie()
    {
        root = new TrieNode();
        nodeCount = 1;
    }

    /**
     * @brief Safely destroys the Trie, triggering the cascading node destructors.
     */
    ~Trie()
    {
        delete root;
    }

    /**
     * @brief Inserts a virtual substring into the Trie and counts new nodes.
     * * ZERO-COPY OPTIMIZATION: Instead of generating and passing expensive string
     * copies (like `s.substr()`), we pass the original string by constant reference
     * alongside logical boundary pointers `l` and `r`.
     * * @param word The original complete string.
     * @param l The starting index of the current suffix.
     * @param r The ending index of the string.
     * * Time Complexity: O(K) where K is the length of the suffix (r - l + 1).
     * Space Complexity: O(K) worst case if all characters form a new branch.
     */
    void insert(const string &word, int l, int r)
    {
        TrieNode *curNode = root;

        for (int i = l; i <= r; ++i)
        {
            int idx = word[i] - 'a';

            // If the path breaks, we just discovered a brand new distinct substring!
            if (curNode->children[idx] == nullptr)
            {
                curNode->children[idx] = new TrieNode();
                ++nodeCount; // Increment our global count
            }

            // Step down the tree
            curNode = curNode->children[idx];
        }
    }

    /**
     * @brief Safely retrieves the encapsulated total count of distinct substrings.
     */
    int getDistinctCount()
    {
        return nodeCount;
    }
};

/**
 * @brief Returns the number of distinct substrings (including empty) of a given string.
 * * APPROACH: "Prefix of a Suffix"
 * Every substring is simply a prefix of some suffix. By generating every possible
 * suffix of the string and inserting them into a Trie, the Trie naturally filters
 * out duplicates. The total number of nodes created equals the number of distinct substrings.
 * * @param s The input string.
 * @return The integer count of distinct substrings.
 * * Time Complexity: O(N^2) where N is the length of the string.
 * Space Complexity: O(N^2) max nodes in the worst-case scenario.
 */
int countDistinctSubstrings(string &s)
{
    Trie trie;
    int n = s.length();

    // Iterate through every starting character to generate every suffix
    for (int i = 0; i < n; ++i)
    {
        // Insert the suffix starting at index 'i' to the end of the string.
        trie.insert(s, i, n - 1);
    }

    return trie.getDistinctCount();
}

int main()
{
    return 0;
}