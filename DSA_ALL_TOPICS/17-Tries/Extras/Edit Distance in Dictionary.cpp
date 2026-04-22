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

1. Title: Words Within Two Edits of Dictionary

Links:
https://leetcode.com/problems/words-within-two-edits-of-dictionary/description/


Problem statement:
You are given two string arrays, queries and dictionary. All words in each array comprise of lowercase English letters and have the same length.

In one edit you can take a word from queries, and change any letter in it to any other letter. Find all words from queries that, after a maximum of two edits, equal some word from dictionary.

Return a list of all words from queries, that match with some word from dictionary after a maximum of two edits. Return the words in the same order they appear in queries.



Example 1:
    Input: queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
    Output: ["word","note","wood"]
    Explanation:
    - Changing the 'r' in "word" to 'o' allows it to equal the dictionary word "wood".
    - Changing the 'n' to 'j' and the 't' to 'k' in "note" changes it to "joke".
    - It would take more than 2 edits for "ants" to equal a dictionary word.
    - "wood" can remain unchanged (0 edits) and match the corresponding dictionary word.
    Thus, we return ["word","note","wood"].

Example 2:
    Input: queries = ["yes"], dictionary = ["not"]
    Output: []
    Explanation:
    Applying any two edits to "yes" cannot make it equal to "not". Thus, we return an empty array.


Constraints:
    1 <= queries.length, dictionary.length <= 100
    n == queries[i].length == dictionary[j].length
    1 <= n <= 100
    All queries[i] and dictionary[j] are composed of lowercase English letters.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Words Within Two Edits of Dictionary
//-------------------------------------------------------------------------------

using namespace std;

// ============================================================================
// APPROACH 1: The "Cache-Friendly" Brute Force
// ----------------------------------------------------------------------------
// Best used when constraints are small (e.g., N, M <= 100).
// Why? std::vector guarantees contiguous memory allocation. Iterating through
// contiguous memory is incredibly fast because the CPU prefetcher loads the
// data directly into the L1/L2 cache. For small datasets, this raw speed
// easily beats the overhead of jumping around memory in a complex Tree structure.
// ============================================================================
namespace std
{

    class Solution
    {
    public:
        vector<string> twoEditWords(const vector<string> &queries, const vector<string> &dictionary)
        {
            int n = queries[0].length();
            int m = queries.size();

            vector<string> ans;

            // OPTIMIZATION: Prevent expensive dynamic array reallocations by
            // reserving the maximum possible memory we might need upfront.
            ans.reserve(m);

            // OPTIMIZATION: Use 'const string&' to avoid deep copying strings.
            for (const string &q : queries)
            {
                for (const string &d : dictionary)
                {

                    int dist = 0;

                    // Calculate Hamming Distance
                    for (int i = 0; i < n; ++i)
                    {
                        if (q[i] != d[i])
                        {
                            ++dist;

                            // EARLY EXIT 1: Once we exceed our 2-edit budget,
                            // stop comparing characters. This branch is dead.
                            if (dist > 2)
                            {
                                break;
                            }
                        }
                    }

                    // EARLY EXIT 2: If we found a valid dictionary word, add the query
                    // to the results and immediately skip to the next query.
                    if (dist <= 2)
                    {
                        ans.push_back(q);
                        break;
                    }
                }
            }

            return ans;
        }
    };

} // namespace std

// ============================================================================
// APPROACH 2: The "Highly Scalable" Trie + DFS
// ----------------------------------------------------------------------------
// Best used when the dictionary scales massively (e.g., 100,000+ words).
// Why? Prefix sharing. If 1,000 words start with the same 5 characters, we
// evaluate those 5 characters once, not 1,000 times. We use DFS to traverse
// the Trie, utilizing a "mistake budget" to prune invalid branches instantly.
// ============================================================================
namespace ScalableTrie
{

    class TrieNode
    {
    public:
        // OPTIMIZATION: Use a fixed-size raw array. It has less memory overhead
        // than std::vector and avoids secondary heap allocations per node.
        TrieNode *children[26] = {nullptr};

        // C++ RAII: Destructors are mandatory to prevent memory leaks in C++
        // when managing raw pointers. When a TrieNode goes out of scope or is
        // deleted, it recursively deletes its children.
        ~TrieNode()
        {
            for (int i = 0; i < 26; ++i)
            {
                delete children[i];
            }
        }
    };

    class Trie
    {
    private:
        TrieNode *root;

        // Depth-First Search with a Mistake Budget
        bool checkDist(const string &query, int qIdx, int dist, TrieNode *curNode)
        {
            // BASE CASES
            if (dist < 0)
                return false; // Ran out of edits
            if (qIdx == query.length())
                return true; // Reached the end successfully

            int idx = query[qIdx] - 'a';

            // PATH PRIORITY 1: The "Free" Path.
            // Always try the exact character match first. It costs 0 edits.
            if (curNode->children[idx] != nullptr)
            {
                if (checkDist(query, qIdx + 1, dist, curNode->children[idx]))
                {
                    return true;
                }
            }

            // PATH PRIORITY 2: The "Expensive" Paths.
            // Only if the free path fails (or doesn't exist), we spend an edit
            // and explore the mismatched branches.
            if (dist > 0)
            { // Optimization: Don't bother looping if budget is 0
                for (int i = 0; i < 26; ++i)
                {

                    // Skip the exact match index, we already checked it above!
                    if (i != idx && curNode->children[i] != nullptr)
                    {
                        if (checkDist(query, qIdx + 1, dist - 1, curNode->children[i]))
                        {
                            return true;
                        }
                    }
                }
            }

            // All explored paths for this branch failed. Prune it.
            return false;
        }

    public:
        Trie()
        {
            root = new TrieNode();
        }

        // Clean up the entire Tree when the Trie object is destroyed.
        ~Trie()
        {
            delete root;
        }

        void insert(const string &word)
        {
            TrieNode *curNode = root;
            for (int i = 0; i < word.length(); ++i)
            {
                int idx = word[i] - 'a';
                if (curNode->children[idx] == nullptr)
                {
                    curNode->children[idx] = new TrieNode();
                }
                curNode = curNode->children[idx];
            }
        }

        bool checkMaxEditDist(const string &query, int max_edits)
        {
            return checkDist(query, 0, max_edits, root);
        }
    };

    class Solution
    {
    public:
        vector<string> twoEditWords(const vector<string> &queries, const vector<string> &dictionary)
        {
            int m = queries.size();

            vector<string> ans;
            ans.reserve(m);

            // The Trie object is instantiated on the stack. When this function
            // returns, 'trie' goes out of scope, its destructor is called,
            // and the entire heap-allocated tree is safely wiped clean.
            Trie trie;

            for (const string &d : dictionary)
            {
                trie.insert(d);
            }

            for (const string &q : queries)
            {
                if (trie.checkMaxEditDist(q, 2))
                {
                    ans.push_back(q);
                }
            }

            return ans;
        }
    };

} // namespace ScalableTrie

int main()
{
    return 0;
}