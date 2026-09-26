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

1. Title: Alien Dictionary


Links:
https://takeuforward.org/data-structure/alien-dictionary-topological-sort-g-26/
https://www.youtube.com/watch?v=U3N_je7tWAs
https://takeuforward.org/plus/dsa/problems/alient-dictionary?tab=editorial
https://www.geeksforgeeks.org/problems/alien-dictionary/1


Problem statement:
A new alien language uses the English alphabet, but the order of letters is unknown. You are given a list of words[] from the alien language’s dictionary, where the words are claimed to be sorted lexicographically according to the language’s rules.
Your task is to determine the correct order of letters in this alien language based on the given words. If the order is valid, return a string containing the unique letters in lexicographically increasing order as per the new language's rules. If there are multiple valid orders, return any one of them.
However, if the given arrangement of words is inconsistent with any possible letter ordering, return an empty string ("").
A string a is lexicographically smaller than a string b if, at the first position where they differ, the character in a appears earlier in the alien language than the corresponding character in b. If all characters in the shorter word match the beginning of the longer word, the shorter word is considered smaller.


Examples:
    Input: words[] = ["baa", "abcd", "abca", "cab", "cad"]
    Output: true
    Explanation: A possible corrct order of letters in the alien dictionary is "bdac".
    The pair "baa" and "abcd" suggests 'b' appears before 'a' in the alien dictionary.
    The pair "abcd" and "abca" suggests 'd' appears before 'a' in the alien dictionary.
    The pair "abca" and "cab" suggests 'a' appears before 'c' in the alien dictionary.
    The pair "cab" and "cad" suggests 'b' appears before 'd' in the alien dictionary.
    So, 'b' → 'd' → 'a' → 'c' is a valid ordering.

    Input: words[] = ["caa", "aaa", "aab"]
    Output: true
    Explanation: A possible corrct order of letters in the alien dictionary is "cab".
    The pair "caa" and "aaa" suggests 'c' appears before 'a'.
    The pair "aaa" and "aab" suggests 'a' appear before 'b' in the alien dictionary.
    So, 'c' → 'a' → 'b' is a valid ordering.

    Input: words[] = ["ab", "cd", "ef", "ad"]
    Output: ""
    Explanation: No valid ordering of letters is possible.
    The pair "ab" and "ef" suggests "a" appears before "e".
    The pair "ef" and "ad" suggests "e" appears before "a", which contradicts the ordering rules.

Constraints:
    1 ≤ words.length ≤ 500
    1 ≤ words[i].length ≤ 100
    words[i] consists only of lowercase English letters.



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
// 1. Title: Alien Dictionary
//-------------------------------------------------------------------------------
class Solution
{
public:
    //============================================================================
    // Approach 1 — BFS (Kahn's Algorithm with Integer Mapping)
    //============================================================================

    /**
     * @brief Determines the valid character order for an alien dictionary.
     *
     * Intuition:
     * - The lexicographical rules of the dictionary can be modeled as a Directed Graph.
     * - By comparing adjacent words, the first non-matching character establishes a
     *   directional dependency (e.g., 'a' must come before 'c').
     * - Because the alphabet is limited to 26 lowercase English letters, we can heavily
     *   optimize performance by mapping characters ('a'-'z') to integers (0-25) and
     *   using fixed-size vectors instead of expensive Hash Maps.
     *
     * Understanding:
     * - Example: ["baa", "abcd"]
     *   'b' (index 1) differs from 'a' (index 0). We create a directed edge: 1 -> 0.
     * - Prefix Edge Case: If a longer word appears before its own exact prefix
     *   (e.g., ["abcd", "abc"]), the dictionary is fundamentally invalid. We return "".
     * - Cycle Detection: If the final sorted string length does not match the total
     *   number of unique characters discovered, Kahn's algorithm was trapped by a cycle.
     *
     * Approach (BFS / Kahn's Algorithm):
     * 1. Track Unique Characters:
     *    - Use a boolean array `exists[26]` to flag all unique characters present in the words.
     *
     * 2. Build the Graph:
     *    - Iterate through adjacent pairs of words.
     *    - Check for the prefix anomaly immediately. If triggered, return "".
     *    - Find the first differing character, add the edge `u -> v` to an array of Hash Sets
     *      (to prevent duplicate rules), and increment `ins[v]`.
     *
     * 3. Process BFS Queue:
     *    - Push all integers (characters) where `exists[i] == true` AND `ins[i] == 0` into the queue.
     *    - Pop elements, convert them back to characters (`'a' + curN`), and append to the result string.
     *    - Decrement neighbors' in-degrees. Push neighbors to the queue when they hit 0.
     *
     * 4. Verify Validity:
     *    - Check if the result string length equals the total number of unique characters.
     *
     * Time Complexity:
     * - O(C): Where C is the total number of characters across all words (used for alphabet extraction
     *   and word comparisons). The BFS graph traversal is O(V + E) bounded to O(26 + 26^2) = O(1).
     *
     * Space Complexity:
     * - O(1): Fixed size arrays for `exists` (26), `ins` (26), and `adjL` (max 26x26 edges).
     *   This is highly memory efficient.
     */
    string findOrder(vector<string> &words)
    {

        // Fixed-size memory allocation for O(1) space/time lookups
        vector<bool> exists(26, false);
        vector<unordered_set<int>> adjL(26); // Set prevents duplicate edges
        vector<int> ins(26, 0);
        queue<int> q;

        int totalUniqueChars = 0;

        // --- STEP 1: Mark all unique alphabets present in the dictionary ---
        for (const string &word : words)
        {
            for (char c : word)
            {
                if (!exists[c - 'a'])
                {
                    exists[c - 'a'] = true;
                    ++totalUniqueChars;
                }
            }
        }

        // --- STEP 2: Build the Graph by comparing adjacent words ---
        for (int i = 1; i < words.size(); ++i)
        {

            string w1 = words[i - 1];
            string w2 = words[i];

            int minLen = min(w1.length(), w2.length());

            // EDGE CASE: Prefix Anomaly (e.g., "abcd" before "abc")
            if (w1.length() > w2.length() && w1.substr(0, minLen) == w2)
            {
                return "";
            }

            // Find the first rule-defining difference
            for (int j = 0; j < minLen; ++j)
            {

                if (w1[j] != w2[j])
                {

                    int u = w1[j] - 'a';
                    int v = w2[j] - 'a';

                    // Prevent redundant duplicate edges from inflating the in-degree
                    if (adjL[u].find(v) == adjL[u].end())
                    {
                        adjL[u].insert(v);
                        ++ins[v];
                    }

                    break; // Only the first difference gives us a rule
                }
            }
        }

        // --- STEP 3: Setup Kahn's BFS Algorithm ---
        for (int i = 0; i < 26; ++i)
        {
            // Push ONLY existing characters that have NO prerequisites
            if (exists[i] && ins[i] == 0)
            {
                q.push(i);
            }
        }

        string ans = "";

        // --- STEP 4: Execute Topological Sort ---
        while (!q.empty())
        {

            int curN = q.front();
            q.pop();

            // Convert the integer back to the character and store it
            ans.push_back('a' + curN);

            for (int adjN : adjL[curN])
            {

                --ins[adjN];

                if (ins[adjN] == 0)
                {
                    q.push(adjN);
                }
            }
        }

        // --- STEP 5: Cycle Verification ---
        // If we didn't extract every unique character, a cyclic paradox exists
        if (ans.length() != totalUniqueChars)
        {
            return "";
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
