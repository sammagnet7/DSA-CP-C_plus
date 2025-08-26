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

1. Title: Alien Dictionary - Topological Sort: G-26


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

Note: Your implementation will be tested using a driver code. It will print true if your returned order correctly follows the alien language’s lexicographic rules; otherwise, it will print false.

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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Alien Dictionary - Topological Sort: G-26
    //-------------------------------------------------------------------------------

    /**
     * @brief Finds the order of characters in an alien dictionary.
     *
     * Approach:
     * - Model the problem as a graph problem where letters are nodes and directed edges
     *   represent ordering constraints derived from consecutive words.
     * - Perform topological sorting (BFS / Kahn’s algorithm) to get the character order.
     *
     * Intuition:
     * - Comparing consecutive words reveals the relative order of letters.
     * - Any character that appears earlier in a word but differs from the next word's character
     *   must come before the next character in the ordering.
     * - Letters not appearing in the dictionary words are ignored in the final output.
     *
     * Time Complexity:
     * - O(N * L + V + E), where N = number of words, L = max word length,
     *   V = 26 (letters), E = number of edges added.
     *
     * Space Complexity:
     * - O(V + E) for adjacency list and indegree array
     * - O(V) for queue and topological ordering
     *
     * @param words Vector of words in alien dictionary order.
     * @return string Characters in the determined order.
     */
    string findOrder(vector<string> &words)
    {
        int n = words.size();

        unordered_set<char> seen;  // Set of characters that appear in the dictionary
        vector<vector<int>> edges; // Store directed edges as pairs [u, v] (u -> v)

        // Step 0: Record all characters that appear in the words
        for (auto &w : words)
        {
            for (char c : w)
            {
                seen.insert(c);
            }
        }

        // Step 1: Build edges based on consecutive words
        for (int i = 0; i <= n - 2; i++)
        {
            string s1 = words[i];
            string s2 = words[i + 1];

            // Edge case: if s2 is prefix of s1 but longer, ordering is invalid
            if (s1.size() > s2.size() && s1.find(s2) == 0)
            {
                return ""; // invalid order
            }

            int ptr = 0;

            // Find first differing character between two consecutive words
            while (ptr < s1.size() && ptr < s2.size())
            {
                if (s1[ptr] != s2[ptr])
                {
                    // Add edge s1[ptr] -> s2[ptr]
                    edges.push_back({(s1[ptr] - 'a'), (s2[ptr] - 'a')});
                    break; // Only the first differing character matters
                }
                ptr++;
            }
        }

        int V = 26; // Total letters in English alphabet

        // Step 2: Build adjacency list and indegree array
        vector<vector<int>> adjL(V); // adjL[u] = list of nodes v such that u -> v
        vector<int> indegree(V, 0);  // indegree[v] = number of incoming edges to node v

        for (auto &e : edges)
        {
            adjL[e[0]].push_back(e[1]);
            indegree[e[1]]++;
        }

        queue<int> q;     // Queue for Kahn's algorithm
        vector<int> topo; // Topologically sorted nodes

        // Step 3: Push all nodes with indegree 0 (no dependencies) into queue
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // Step 4: Process nodes using BFS (Kahn's algorithm)
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Reduce indegree of neighbors; add to queue if indegree becomes 0
            for (int adj : adjL[node])
            {
                indegree[adj]--;
                if (indegree[adj] == 0)
                {
                    q.push(adj);
                }
            }
        }

        string ans = "";

        // Step 5: Build answer string only from characters that actually appear in words
        if (topo.size() == V)
        { // Ensure topological sort completed
            for (int i : topo)
            {
                char cur = (char)(i + 'a');
                if (seen.find(cur) != seen.end())
                {
                    ans.append(1, cur);
                }
            }
        }

        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
