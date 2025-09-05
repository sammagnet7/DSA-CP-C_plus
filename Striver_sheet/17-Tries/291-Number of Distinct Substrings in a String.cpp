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

1. Title: Number of Distinct Substrings in a String Using Trie

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
Detailed explanation ( Input/output format, Notes, Images )

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

// -----------------------------------------------------------------------------
// Approach1: Count Distinct Substrings (Suboptimal Approach)
// -----------------------------------------------------------------------------
// Idea:
//   Generate all substrings and store them in a set to remove duplicates.
//   The size of the set = number of distinct substrings.
//
// Complexity:
//   - Time: O(n^3) (O(n^2) substrings ? O(n) copy per substring).
//   - Space: O(n^2) for storing substrings.
//   Works only for very small strings. Efficient methods use SAM or Suffix Array.
// -----------------------------------------------------------------------------

// int countDistinctSubstrings(string &s)
// {
//     int n = s.size();
//     unordered_set<string> subStrs;
//     subStrs.insert(""); // include the empty substring

//     for (int i = 0; i < n; i++) {
//         for (int j = n - 1; j >= i; j--) {
//             subStrs.insert(s.substr(i, (j - i + 1)));
//         }
//     }

//     return subStrs.size();
// }

// -----------------------------------------------------------------------------
// Approach2: Trie-based solution (Optimal Approach)
// -----------------------------------------------------------------------------
/*
  Trie-based solution to count distinct substrings (non-empty).
  Idea:
    - Insert all suffixes of the string into a Trie.
    - Each time we create a new Trie node it corresponds to a distinct substring
      that was not seen before (because that character-path didn't exist).
    - The total number of new nodes created while inserting all suffixes equals
      the number of distinct non-empty substrings.
    - We return that count + 1 if we want to include the empty substring.

  Complexity:
    - Time:  O(N^2) worst-case. For each of N starting positions we may walk up
      to O(N) characters inserting nodes or following existing links.
    - Space: O(N^2) worst-case (there can be ?(N^2) distinct substrings -> nodes).
*/

class Node
{
    Node *link[26]; // fixed 26-ary children for 'a'..'z'

public:
    // Constructor: initialize all child pointers to nullptr
    Node()
    {   
        // Need to initialize.
        for (int i = 0; i < 26; i++)
        {
            link[i] = nullptr;
        }
    }

    // Check if a child for character index 'key' exists
    // key: integer in [0..25] representing a lower-case letter
    bool keyExists(int key)
    {
        return (this->link[key] != nullptr);
    }

    // Return pointer to the child node for 'key' (may be nullptr)
    Node *getNextNode(int key)
    {
        return this->link[key];
    }

    // Create a new child node at 'key' and return pointer to it
    // Caller is responsible for counting/usage
    Node *insertKey(int key)
    {
        Node *newN = new Node();
        this->link[key] = newN;
        return newN;
    }
};

class Trie
{
    Node *root; // root node (does not represent any character)

public:
    // Constructor: allocate an empty root
    Trie()
    {
        root = new Node();
    }

    // countWhileInserting:
    // - Walk all suffixes of `str` and insert characters into the Trie.
    // - Each time we create a new node we increment `count` because that node
    //   represents a substring that wasn't present before.
    //
    // Returns:
    // - number of NEW nodes created while inserting all suffixes = number of
    //   distinct non-empty substrings.
    int countWhileInserting(string &str)
    {
        Node *tmp;
        int count = 0; // counts newly created nodes (distinct substrings)

        // For each starting index (i.e., each suffix)
        for (int start = 0; start < (int)str.size(); start++)
        {
            tmp = root; // start traversal from root for this suffix

            // Extend the current suffix one character at a time
            for (int i = start; i < (int)str.size(); i++)
            {
                int cur = str[i] - 'a'; // map char -> index [0..25]

                if (tmp->keyExists(cur))
                {
                    // Path already exists: this substring was already seen
                    tmp = tmp->getNextNode(cur);
                }
                else
                {
                    // New path: create node and increment distinct-substring count
                    tmp = tmp->insertKey(cur);
                    count++;
                }
            }
            // end of one suffix; move to next suffix
        }

        return count;
    }
};

// Public function required by problem: countDistinctSubstrings
// - returns number of distinct substrings including empty string (+1)
int countDistinctSubstrings(string &s)
{
    Trie t;
    // The trie count returns distinct non-empty substrings; add 1 for empty string
    return t.countWhileInserting(s) + 1;
}

int main()
{
    return 0;
}