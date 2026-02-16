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
//
class Solution
{
    using ll = long long;
    const ll INF = 1e9; // Sentinel value for infinity (larger than any possible path sum)

public:
    /*
     * METHOD: minimumCost
     * -------------------
     * APPROACH: All-Pairs Shortest Path (Floyd-Warshall)
     * * 1. Graph Representation:
     * - We treat the 26 lowercase English letters as nodes in a directed weighted graph.
     * - The input arrays (original, changed, cost) represent directed edges with specific weights.
     * * 2. Algorithm Choice: Floyd-Warshall
     * - The problem requires us to find the cheapest way to convert ANY character 'u' to ANY character 'v',
     * possibly through intermediate steps (e.g., a -> b -> c).
     * - Since the number of nodes (V) is very small (26), Floyd-Warshall is the optimal choice.
     * - It computes the shortest path between all pairs of nodes in O(V^3) time.
     * * 3. Process:
     * - Initialize a 26x26 adjacency matrix with INF, where minCost[i][i] = 0.
     * - Populate the matrix with the given direct conversion costs. Handle duplicate edges by keeping the minimum.
     * - Run the 3 nested loops of Floyd-Warshall to update the matrix with transitive shortest paths.
     * - Iterate through the 'source' string and sum up the conversion costs for each character to match 'target'.
     * * COMPLEXITY:
     * Time: O(M + 26^3 + N)
     * - M: Number of entries in the 'cost' array (Graph construction).
     * - 26^3: Floyd-Warshall algorithm (Constant time ~17,576 operations).
     * - N: Length of 'source' string (Final linear scan).
     * Space: O(1)
     * - We use a fixed 26x26 matrix, which is constant space regardless of input size.
     */
    ll minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {

        // 1. Initialize Distance Matrix (26x26)
        // minCost[i][j] stores the minimum cost to convert char (i+'a') to char (j+'a')
        vector<vector<ll>> minCost(26, vector<ll>(26, INF));

        // Base case: The cost to convert a character to itself is always 0.
        for (int i = 0; i < 26; i++)
        {
            minCost[i][i] = 0;
        }

        // 2. Build the Graph from Input
        // Populate the matrix with initial direct edge weights.
        for (int i = 0; i < cost.size(); i++)
        {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            // If multiple edges exist between u and v, keep the one with the smallest cost.
            minCost[u][v] = min(minCost[u][v], (ll)cost[i]);
        }

        // 3. Run Floyd-Warshall Algorithm
        // Update matrix to find the shortest path between every pair of nodes considering intermediate nodes 'k'.
        int V = 26;
        for (int k = 0; k < V; k++)
        { // Intermediate node
            for (int i = 0; i < V; i++)
            { // Source node
                for (int j = 0; j < V; j++)
                { // Destination node
                    // Relaxation: If going through 'k' is cheaper, update the path i->j
                    // Check for INF to prevent overflow (though logic ensures safe range with 1e9)
                    if (minCost[i][k] < INF && minCost[k][j] < INF)
                    {
                        minCost[i][j] = min(minCost[i][j], minCost[i][k] + minCost[k][j]);
                    }
                }
            }
        }

        // 4. Calculate Total Transformation Cost
        ll finalCost = 0;
        int N = source.size();

        for (int i = 0; i < N; i++)
        {
            int u = source[i] - 'a';
            int v = target[i] - 'a';

            // No conversion needed
            if (u == v)
                continue;

            // If the cost is still INF, it means 'v' is unreachable from 'u'
            if (minCost[u][v] >= INF)
            {
                return -1;
            }

            finalCost += minCost[u][v];
        }

        return finalCost;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Minimum Cost to Convert String II
//-------------------------------------------------------------------------------

// ---------------------------------------------------------
// Approach 1: Using Hash + Backward/Pull DP [OPTIMAL]
// ---------------------------------------------------------

class Solution
{
    // Use a large infinity value (1e14) to prevent overflow when adding costs.
    // Max cost is ~1e6, max operations could correspond to string length ~1000.
    // 1e9 might overflow if we sum many edge weights.
    const long long INF = 1e14;

public:
    /*
     * METHOD: minimumCost
     * -------------------
     * APPROACH: Shortest Path (Floyd-Warshall) + Dynamic Programming
     * * 1. PRE-PROCESSING (Graph Construction):
     * - We treat every unique string in 'original' and 'changed' as a node in a graph.
     * - Since strings are not integers, we map them to IDs (0, 1, 2...) using a HashMap.
     * - Build an adjacency matrix where dist[u][v] is the cost to change string 'u' to 'v'.
     * - Run Floyd-Warshall Algorithm to find the shortest path between ALL pairs of strings.
     * This handles transitive conversions (e.g., "a" -> "b" -> "c").
     * * 2. OPTIMIZATION (Length Filtering):
     * - We collect all unique lengths of strings from the 'original' array into a Set.
     * - During DP, we only try to match substrings of these specific lengths.
     * - This reduces the inner loop complexity significantly compared to checking all j < i.
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
    long long minimumCost(string source, string target, vector<string> &original, vector<string> &changed, vector<int> &cost)
    {

        int M = cost.size();
        int N = source.size();

        // --- Step 1: Map Strings to Integer IDs ---
        unordered_map<string, int> str_to_id;
        int id = 0;

        for (int i = 0; i < M; i++)
        {
            if (str_to_id.find(original[i]) == str_to_id.end())
            {
                str_to_id[original[i]] = id++;
            }
            if (str_to_id.find(changed[i]) == str_to_id.end())
            {
                str_to_id[changed[i]] = id++;
            }
        }

        int V = id; // Total number of unique string nodes

        // --- Step 2: Initialize Distance Matrix ---
        vector<vector<long long>> dist(V, vector<long long>(V, INF));

        // Base case: Cost to convert a string to itself is 0
        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;

        // Populate direct edges from input
        for (int i = 0; i < M; i++)
        {
            int u = str_to_id[original[i]];
            int v = str_to_id[changed[i]];
            // Handle duplicate rules: keep the minimum cost
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // --- Step 3: Floyd-Warshall Algorithm ---
        // Compute All-Pairs Shortest Path to handle chained conversions (A->B->C)
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    // Check bounds to prevent overflow and ensure reachability
                    if (dist[i][k] < INF && dist[k][j] < INF)
                    {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // --- Step 4: Optimization Setup ---
        // Store only valid lengths to avoid iterating irrelevant substring sizes
        unordered_set<int> validLens;
        for (const auto &s : original)
        {
            validLens.insert(s.size());
        }

        // --- Step 5: Dynamic Programming ---
        // DP[i] = Min cost to convert prefix of length 'i'
        vector<long long> DP(N + 1, INF);
        DP[0] = 0;

        // Iterate through the string. 'i' represents the index of the character
        // we are currently trying to resolve (0-based index in source/target).
        // We are computing the state for DP[i+1] (prefix length i+1).
        for (int i = 0; i < N; i++)
        {

            long long minCost = INF;

            // Option A: Skip Character (if they match)
            // If characters are identical, we can carry over the cost from the previous prefix.
            if (source[i] == target[i])
            {
                minCost = DP[i]; // Equivalent to DP[(i+1)-1]
            }

            // Option B: Apply Substring Conversion Rule
            // Try all possible substring lengths that exist in our rules
            for (auto it = validLens.begin(); it != validLens.end(); it++)
            {

                int len = *it;

                // Boundary Check: Ensure the substring starts at a valid non-negative index
                // Substring range: [i - len + 1, i]
                if (i - len + 1 < 0)
                {
                    continue;
                }

                // Extract substrings from source and target
                string srcStr = source.substr((i - len + 1), len);
                string targetStr = target.substr((i - len + 1), len);

                // Check if both substrings are known nodes in our graph
                if (str_to_id.count(srcStr) > 0 && str_to_id.count(targetStr) > 0)
                {
                    int srcId = str_to_id[srcStr];
                    int targetId = str_to_id[targetStr];

                    // Transition:
                    // Cost = (Cost to reach state BEFORE this substring) + (Cost to transform this substring)
                    // Previous state is at index: (i - len + 1)
                    if (dist[srcId][targetId] < INF && DP[i - len + 1] < INF)
                    {
                        long long curDist = DP[i - len + 1] + dist[srcId][targetId];
                        minCost = min(minCost, curDist);
                    }
                }
            }

            // Store result for prefix length i+1
            DP[i + 1] = minCost;
        }

        return DP[N] == INF ? -1 : DP[N];
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