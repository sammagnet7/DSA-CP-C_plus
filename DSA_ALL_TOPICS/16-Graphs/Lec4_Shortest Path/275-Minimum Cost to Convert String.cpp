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

1. Title: Minimum Cost to Convert String I

Links:
https://leetcode.com/problems/minimum-cost-to-convert-string-i/description/


Problem statement:
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].

You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].


Example 1:
    Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
    Output: 28
    Explanation: To convert the string "abcd" to string "acbe":
    - Change value at index 1 from 'b' to 'c' at a cost of 5.
    - Change value at index 2 from 'c' to 'e' at a cost of 1.
    - Change value at index 2 from 'e' to 'b' at a cost of 2.
    - Change value at index 3 from 'd' to 'e' at a cost of 20.
    The total cost incurred is 5 + 1 + 2 + 20 = 28.
    It can be shown that this is the minimum possible cost.

Example 2:
    Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
    Output: 12
    Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.

Example 3:
    Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
    Output: -1
    Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.


Constraints:
    1 <= source.length == target.length <= 105
    source, target consist of lowercase English letters.
    1 <= cost.length == original.length == changed.length <= 2000
    original[i], changed[i] are lowercase English letters.
    1 <= cost[i] <= 106
    original[i] != changed[i]



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Minimum Cost to Convert String II


Links:
https://leetcode.com/problems/minimum-cost-to-convert-string-ii/description/



Problem statement:
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].

You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:

The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].


Example 1:
    Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
    Output: 28
    Explanation: To convert "abcd" to "acbe", do the following operations:
    - Change substring source[1..1] from "b" to "c" at a cost of 5.
    - Change substring source[2..2] from "c" to "e" at a cost of 1.
    - Change substring source[2..2] from "e" to "b" at a cost of 2.
    - Change substring source[3..3] from "d" to "e" at a cost of 20.
    The total cost incurred is 5 + 1 + 2 + 20 = 28.
    It can be shown that this is the minimum possible cost.

Example 2:
    Input: source = "abcdefgh", target = "acdeeghh", original = ["bcd","fgh","thh"], changed = ["cde","thh","ghh"], cost = [1,3,5]
    Output: 9
    Explanation: To convert "abcdefgh" to "acdeeghh", do the following operations:
    - Change substring source[1..3] from "bcd" to "cde" at a cost of 1.
    - Change substring source[5..7] from "fgh" to "thh" at a cost of 3. We can do this operation because indices [5,7] are disjoint with indices picked in the first operation.
    - Change substring source[5..7] from "thh" to "ghh" at a cost of 5. We can do this operation because indices [5,7] are disjoint with indices picked in the first operation, and identical with indices picked in the second operation.
    The total cost incurred is 1 + 3 + 5 = 9.
    It can be shown that this is the minimum possible cost.

Example 3:
    Input: source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"], changed = ["ddd","ddddd"], cost = [100,1578]
    Output: -1
    Explanation: It is impossible to convert "abcdefgh" to "addddddd".
    If you select substring source[1..3] as the first operation to change "abcdefgh" to "adddefgh", you cannot select substring source[3..7] as the second operation because it has a common index, 3, with the first operation.
    If you select substring source[3..7] as the first operation to change "abcdefgh" to "abcddddd", you cannot select substring source[1..3] as the second operation because it has a common index, 3, with the first operation.


Constraints:
    1 <= source.length == target.length <= 1000
    source, target consist only of lowercase English characters.
    1 <= cost.length == original.length == changed.length <= 100
    1 <= original[i].length == changed[i].length <= source.length
    original[i], changed[i] consist only of lowercase English characters.
    original[i] != changed[i]
    1 <= cost[i] <= 10^6


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Minimum Cost to Convert String I
//-------------------------------------------------------------------------------

class Solution
{
public:
    //============================================================================
    // Approach 1 — Floyd-Warshall Algorithm (Alphabet Graph)
    //============================================================================

    /**
     * @brief Finds the minimum cost to convert a source string to a target string.
     *
     * Idea & Intuition:
     * - The allowed character changes form a directed, weighted graph where the nodes
     * are the 26 lowercase English letters.
     * - Because we need to know the cheapest conversion cost from *any* character to
     * *any* other character, this is an All-Pairs Shortest Path problem.
     * - The graph has exactly 26 nodes. Floyd-Warshall runs in O(V^3) time, which is
     * 26^3 = 17,576 operations. This is phenomenally fast and effectively O(1)
     * constant time, making it the perfect algorithm here.
     *
     * Approach:
     * 1. Initialization:
     * - Create a 26x26 `dist` matrix initialized to `1e9`.
     * - Set the distance from any character to itself to 0 (`dist[i][i] = 0`).
     * - Populate the directed edges. If there are duplicate rules for the same
     * conversion, strictly keep the minimum cost.
     * 2. Floyd-Warshall DP:
     * - Run the standard 3 nested loops (k, i, j) strictly bounded to 26.
     * - Include overflow protection (`1e9` checks).
     * 3. Cost Calculation:
     * - Iterate through the `source` and `target` strings simultaneously.
     * - If `source[i] == target[i]`, no cost is incurred.
     * - If `dist[u][v] == 1e9`, the conversion is impossible. Return -1 immediately.
     * - Otherwise, add the pre-calculated shortest path cost to `minCost`.
     *
     * Time Complexity:
     * - O(N + L): Where N is the size of the `original` array and L is the length of
     * the `source` string. Building the graph takes O(N). Floyd-Warshall takes O(26^3)
     * which simplifies to O(1). Calculating the final cost takes O(L).
     *
     * Space Complexity:
     * - O(1): The `dist` matrix is fixed at 26x26 integers, meaning it requires O(1)
     * auxiliary memory regardless of the input size.
     */
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {

        // --- STEP 1: Graph Initialization ---
        // 26x26 matrix for the English alphabet
        vector<vector<int>> dist(26, vector<int>(26, 1e9));

        // Distance to self is always 0
        for (int i = 0; i < 26; ++i)
        {
            dist[i][i] = 0;
        }

        // Populate directed edges (keeping the cheapest option if duplicates exist)
        for (int i = 0; i < original.size(); ++i)
        {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            int w = cost[i];

            dist[u][v] = min(dist[u][v], w);
        }

        // --- STEP 2: Floyd-Warshall Algorithm ---
        for (int k = 0; k < 26; ++k)
        {
            for (int i = 0; i < 26; ++i)
            {
                for (int j = 0; j < 26; ++j)
                {

                    // Overflow protection
                    if (dist[i][k] == 1e9 || dist[k][j] == 1e9)
                    {
                        continue;
                    }

                    int newDist = dist[i][k] + dist[k][j];
                    dist[i][j] = min(dist[i][j], newDist);
                }
            }
        }

        // --- STEP 3: Final Cost Calculation ---
        // Must use long long as the accumulated cost can easily exceed 32-bit limits
        long long minCost = 0;

        for (int i = 0; i < source.length(); ++i)
        {

            int u = source[i] - 'a';
            int v = target[i] - 'a';

            // No change needed
            if (u == v)
            {
                continue;
            }

            // Impossible to convert
            if (dist[u][v] == 1e9)
            {
                return -1;
            }

            minCost += dist[u][v];
        }

        return minCost;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Minimum Cost to Convert String II
//-------------------------------------------------------------------------------

// ---------------------------------------------------------
// Approach 1: Using Hash + Backward/Pull DP [OPTIMAL]
// ---------------------------------------------------------

/*
 * METHOD: minimumCost
 * -------------------
 * APPROACH: Shortest Path (Floyd-Warshall) + Dynamic Programming
 *
 * * 1. PRE-PROCESSING (Graph Construction):
 * - We treat every unique string in 'original' and 'changed' as a node in a graph.
 * - Since strings are not integers, we map them to IDs (0, 1, 2...) using a HashMap.
 * - Build an adjacency matrix where dist[u][v] is the cost to change string 'u' to 'v'.
 * - Run Floyd-Warshall Algorithm to find the shortest path between ALL pairs of strings.
 * This handles transitive conversions (e.g., "a" -> "b" -> "c").
 *
 * * 2. OPTIMIZATION (Length Filtering):
 * - We collect all unique lengths of strings from the 'original' array into a Set.
 * - During DP, we only try to match substrings of these specific lengths.
 * - This reduces the inner loop complexity significantly compared to checking all j < i.
 *
 * * 3. MAIN LOGIC (Dynamic Programming) (Backward / Pull DP):
 * - dp[i] represents the minimum cost to convert the prefix source[0...i-1] to target[0...i-1].
 * - For each index 'i' (current character in source), we have two choices:
 * a) Exact Match: If source[i] == target[i], we can potentially carry over the cost from dp[i].
 * b) Replacement: Look back 'len' characters. If source[i-len+1...i] can be converted
 * to target[i-len+1...i] using our pre-computed graph, update the cost.
 * * COMPLEXITY:
 * Time: O(V^3 + N * K * L)
 * - V^3: Floyd-Warshall (V <= 200 unique strings).
 * - N: Length of source (1000).
 * - K: Number of unique lengths in 'original' (<= 100).
 * - L: Average length of substring hashing (<= 1000).
 * Space: O(V^2) for the distance matrix.
 */

using ll = long long;

class Solution
{
    // A safe infinity for long long that won't overflow when added to itself
    const ll INF = 1e15;

public:
    //============================================================================
    // Approach 1 — Floyd-Warshall (APSP) + Forward 1D Dynamic Programming
    //============================================================================

    /**
     * @brief Finds the minimum cost to convert source to target using disjoint substring replacements.
     *
     * Idea & Intuition:
     * - The problem explicitly states that chosen substrings must be "disjoint or identical".
     * In plain English, this means we are cutting the string into independent chunks and
     * paying for them sequentially. This perfectly sets up a 1D Dynamic Programming approach.
     * - However, to perform the DP, we first need to know the absolute cheapest cost to
     * convert ANY known chunk to ANY other known chunk. Because the number of unique
     * strings in the rules is very small (<= 200), we can map each string to an Integer ID
     * and use the Floyd-Warshall Algorithm to precompute all shortest paths in O(V^3) time.
     *
     * Approach:
     * 
     ** 1. Graph Construction & Floyd-Warshall:
     * - Iterate through `original` and `changed` to assign a unique integer ID to every
     * distinct string. Let this count be V.
     * - Initialize a V x V `dist` matrix to `INF` (1e15). Set the diagonal to 0.
     * - Populate the matrix with the given costs, taking the `min` to protect against
     * duplicate rules with worse costs.
     * - Run the 3-nested loop Floyd-Warshall algorithm to find All-Pairs Shortest Paths.
     * 
     * * 2. Precompute Available Lengths:
     * - Insert the lengths of all strings in `original` into a `set<int>`.
     * - OPTIMIZATION: A C++ `set` automatically sorts the lengths in ascending order.
     * This is crucial for early-breaking in the DP step.
     * 
     * * 3. Forward 1D Dynamic Programming:
     * - Let `minCost[k]` be the minimum cost to correctly convert the prefix of length `k`.
     * - Base Case: `minCost[0] = 0` (converting an empty prefix costs nothing).
     * - Loop `i` from 0 to N-1 (representing the current end character of our prefix):
     * a) Free Match: If `source[i] == target[i]`, we can trivially extend the previous
     *  prefix's cost: `curMinCost = minCost[i]`.
     * b) Chunk Replacement: Iterate through our sorted `avlLens`.
     * - Calculate the start index `l = i - len + 1`.
     * - EARLY BREAK: If `l < 0`, the chunk is too big for our current prefix. Because
     * the set is sorted ascending, all subsequent lengths will also be too big, so
     * we immediately `break`.
     * - Extract the `source` and `target` substrings. If both exist in our ID map,
     * check the `dist` matrix.
     * - If a valid path exists, calculate `newConvCost = minCost[l] + dist[u][v]`.
     * c) Finally, lock in the best found cost for the prefix of length `i + 1`:
     * `minCost[i + 1] = curMinCost`.
     *
     * Time Complexity:
     * - O(V^3 + N * U * L):
     * - V is the number of unique strings (<= 200). Floyd-Warshall takes O(V^3) ~ 8,000,000 ops.
     * - N is the string length (<= 1000).
     * - U is the number of unique string lengths in the rules (<= 100).
     * - L is the maximum length of a string being extracted via `substr` (<= N).
     * The set optimization keeps the DP extremely fast.
     *
     * Space Complexity:
     * - O(V^2 + V * L + N):
     * - `dist` matrix takes O(V^2).
     * - The string-to-ID hash map takes O(V * L) to store the strings.
     * - The DP array takes O(N).
     */
    ll minimumCost(string source, string target, vector<string> &original, vector<string> &changed, vector<int> &cost)
    {

        // ==========================================
        // STEP 1: Graph Construction & Floyd-Warshall
        // ==========================================
        unordered_map<string, int> mp;
        int count = 0;

        for (int i = 0; i < original.size(); ++i)
        {
            if (mp.find(original[i]) == mp.end())
                mp[original[i]] = count++;
            if (mp.find(changed[i]) == mp.end())
                mp[changed[i]] = count++;
        }

        // Upgraded to 1e15 Infinity
        vector<vector<ll>> dist(count, vector<ll>(count, INF));

        for (int i = 0; i < original.size(); ++i)
        {
            int u = mp[original[i]];
            int v = mp[changed[i]];
            ll w = cost[i];

            dist[u][v] = min(dist[u][v], w);
        }

        for (int i = 0; i < count; ++i)
        {
            dist[i][i] = 0;
        }

        for (int k = 0; k < count; ++k)
        {
            for (int i = 0; i < count; ++i)
            {
                for (int j = 0; j < count; ++j)
                {
                    if (dist[i][k] != INF && dist[k][j] != INF)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // ==========================================
        // STEP 2: Precompute Available Lengths
        // ==========================================
        // Set automatically sorts lengths ascending, which makes the DP break condition mathematically safe!
        set<int> avlLens;
        for (const string &s : original)
        {
            avlLens.insert(s.length());
        }

        // ==========================================
        // STEP 3: Forward 1D Dynamic Programming
        // ==========================================
        int n = source.length();
        vector<ll> minCost(n + 1, INF);

        minCost[0] = 0; // Cost to convert a prefix of length 0 is 0

        for (int i = 0; i < n; ++i)
        {

            ll curMinCost = INF;

            // Option 1: Free character match
            if (source[i] == target[i])
            {
                curMinCost = minCost[i];
            }

            // Option 2: Attempt chunk replacements ending at index i
            for (auto &len : avlLens)
            {

                int l = i - len + 1;

                // Because avlLens is sorted ascending, if this length is out of bounds, all larger lengths will be too!
                if (l < 0)
                {
                    break;
                }

                string srcStr = source.substr(l, len);
                string trgStr = target.substr(l, len);

                // If both chunks are recognized by our conversion graph
                if (mp.find(srcStr) != mp.end() && mp.find(trgStr) != mp.end())
                {

                    int u = mp[srcStr];
                    int v = mp[trgStr];
                    ll curConvCost = dist[u][v];
                    ll restConvCost = minCost[l];

                    // If a valid path exists
                    if (restConvCost != INF && curConvCost != INF)
                    {
                        ll newConvCost = restConvCost + curConvCost;
                        curMinCost = min(curMinCost, newConvCost);
                    }
                }
            }

            // Lock in the minimum cost for the prefix of length i + 1
            minCost[i + 1] = curMinCost;
        }

        return minCost[n] == INF ? -1 : minCost[n];
    }
};

// ---------------------------------------------------------
// Approach 2: Using Trie + Forward/Push DP [OPTIMAL]
// ---------------------------------------------------------
class Solution
{
    // Large infinity to safely handle cost accumulation without overflow
    const long long INF = 1e14;

    // --- Trie Structure Definition ---
    struct TrieNode
    {
        TrieNode *children[26];
        int id = -1; // Stores the mapped Graph ID if this node represents the end of a valid 'original' string

        TrieNode()
        {
            fill(begin(children), end(children), nullptr);
        }
    };

    // Helper to insert a string into the Trie and map it to a Graph ID
    void insert(TrieNode *root, const string &s, int id)
    {
        TrieNode *curr = root;
        for (char c : s)
        {
            int idx = c - 'a';
            if (!curr->children[idx])
            {
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
        }
        curr->id = id;
    }

public:
    /*
     * METHOD: minimumCost (Approach 2: Trie Optimization)
     * ---------------------------------------------------
     * APPROACH: Floyd-Warshall + Forward DP + Trie
     * * 1. PRE-PROCESSING (Graph & IDs):
     * - Map every unique string in 'original' and 'changed' to a unique integer ID (0, 1, ... V).
     * - Build a weighted directed graph where edges represent conversion costs.
     * - Run Floyd-Warshall Algorithm (O(V^3)) to compute the minimum cost between ALL pairs of strings.
     * This accounts for transitive conversions (e.g., A -> B -> C).
     *
     * 2. TRIE CONSTRUCTION:
     * - Insert all strings from the 'original' array into a Trie.
     * - WHY? In the naive approach, checking if a substring exists requires O(L) hashing.
     * With a Trie, we can traverse the 'source' string character by character. If we find a node
     * with a valid ID, we know we found a match in O(1) step per char.
     *
     * 3. DYNAMIC PROGRAMMING (Forward / Push DP):
     * - dp[i] = Min cost to convert the prefix source[0...i-1].
     * - Iterate 'i' from 0 to N. If dp[i] is reachable (not INF):
     * * a) Exact Match Optimization:
     * If source[i] == target[i], update dp[i+1] = min(dp[i+1], dp[i]).
     * * b) Trie Traversal (The Optimization):
     * - Start traversing the Trie from source[i].
     * - As we move to source[i+1], source[i+2]... we walk down the Trie.
     * - If we hit a node with a valid 'id' (say, length 'len'), it means source[i...i+len-1]
     * matches a rule in 'original'.
     * - We then check if target[i...i+len-1] exists in our ID map.
     * - If both exist, we update: dp[i+len] = min(dp[i+len], dp[i] + dist[u][v]).
     *
     * COMPLEXITY:
     * - Time: O(V^3 + N * L)
     * - V^3 for Floyd-Warshall (V <= 200).
     * - N is source length (1000). L is max substring length.
     * - The Trie ensures we visit each character in 'source' efficiently without repeatedly hashing substrings.
     * - Space: O(V^2 + V*L) for the cost matrix and Trie storage.
     */
    long long minimumCost(string source, string target, vector<string> &original, vector<string> &changed, vector<int> &cost)
    {

        // --- Step 1: Map Strings to IDs ---
        unordered_map<string, int> str_to_id;
        int idCounter = 0;

        auto getId = [&](const string &s)
        {
            if (str_to_id.find(s) == str_to_id.end())
            {
                str_to_id[s] = idCounter++;
            }
            return str_to_id[s];
        };

        // We need IDs for ALL strings involved in the graph rules
        for (const string &s : original)
            getId(s);
        for (const string &s : changed)
            getId(s);

        int V = idCounter;

        // --- Step 2: Build Trie ---
        // Insert only 'original' strings because we search for matches in 'source'
        TrieNode *root = new TrieNode();
        for (const string &s : original)
        {
            insert(root, s, str_to_id[s]);
        }

        // --- Step 3: Floyd-Warshall Algorithm ---
        vector<vector<long long>> dist(V, vector<long long>(V, INF));
        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;

        for (size_t i = 0; i < cost.size(); ++i)
        {
            int u = str_to_id[original[i]];
            int v = str_to_id[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        for (int k = 0; k < V; ++k)
        {
            for (int i = 0; i < V; ++i)
            {
                for (int j = 0; j < V; ++j)
                {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // --- Step 4: DP with Trie Traversal ---
        int n = source.length();
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        for (int i = 0; i < n; ++i)
        {
            if (dp[i] == INF)
                continue;

            // Option A: Character Match (Cost 0)
            if (source[i] == target[i])
            {
                dp[i + 1] = min(dp[i + 1], dp[i]);
            }

            // Option B: Trie Traversal
            // Check substrings starting at 'i' using the Trie
            TrieNode *curr = root;
            for (int len = 0; i + len < n; ++len)
            {
                int charIdx = source[i + len] - 'a';

                // If path breaks, no longer substrings will match either. Break loop.
                if (!curr->children[charIdx])
                    break;

                curr = curr->children[charIdx];

                // Found a valid 'original' string in the Trie?
                if (curr->id != -1)
                {
                    int u = curr->id;

                    // Construct the corresponding target substring
                    // (Note: Hashing here is unavoidable unless using a second Trie or rolling hash,
                    // but standard map is efficient enough for N=1000)
                    string subTgt = target.substr(i, len + 1);

                    if (str_to_id.count(subTgt))
                    {
                        int v = str_to_id[subTgt];

                        // If conversion is possible, update the future state
                        if (dist[u][v] < INF)
                        {
                            dp[i + len + 1] = min(dp[i + len + 1], dp[i] + dist[u][v]);
                        }
                    }
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};

int main()
{

    return 0;
}