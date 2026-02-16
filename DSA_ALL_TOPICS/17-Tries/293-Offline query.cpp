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

1. Title: Maximum Xor Queries | Trie | Maximum XOR With an Element From Array

Links:
https://takeuforward.org/trie/maximum-xor-queries-trie/
https://www.youtube.com/watch?v=Q8LhG9Pi5KM&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=8
https://takeuforward.org/plus/dsa/problems/maximum-xor-with-an-element-from-an-array?tab=editorial
https://leetcode.com/problems/maximum-xor-with-an-element-from-array/description/


Problem statement:
You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

Examples:
    Example 1:
    Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
    Output: [3,3,7]
    Explanation:
    1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
    2) 1 XOR 2 = 3.
    3) 5 XOR 2 = 7.

    Example 2:
    Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
    Output: [15,-1,5]


Constraints:
    1 <= nums.length, queries.length <= 105
    queries[i].length == 2
    0 <= nums[j], xi, mi <= 109


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
// 1. Title: Maximum XOR With an Element From Array
//-------------------------------------------------------------------------------
//

class Node
{
    Node *link[2]; // children: link[0] for bit 0, link[1] for bit 1

public:
    // Constructor: initialize child pointers to nullptr
    Node()
    {
        link[0] = link[1] = nullptr;
    }

    // Returns true if child for bit 'key' exists
    bool keyExists(int key)
    {
        return !(this->link[key] == nullptr);
    }

    // Return pointer to child node for bit 'key'
    Node *getNextNode(int key)
    {
        return this->link[key];
    }

    // Create/attach a child node for bit 'key' and return it
    Node *put(int key)
    {
        Node *newN = new Node();
        this->link[key] = newN;
        return newN;
    }
};

class Trie
{
    Node *root; // root of the binary trie

public:
    // Initialize trie with empty root node
    Trie()
    {
        root = new Node();
    }

    // Insert the 32-bit binary representation of num into the trie.
    // We traverse from bit 31 (most significant) down to bit 0 (least significant).
    // If the required child doesn't exist, create it.
    void insert(int num)
    {

        Node *tmp = root;

        for (int i = 31; i >= 0; i--)
        {
            int probe = num >> i; // shift right to bring bit i to LSB
            int cur = probe & 1;  // extract the i-th bit (0 or 1)

            if (tmp->keyExists(cur))
            {
                // If child exists for this bit, follow it
                tmp = tmp->getNextNode(cur);
            }
            else
            {
                // Otherwise create the child and move to it
                tmp = tmp->put(cur);
            }
        }
    }

    // Query the trie for the maximum XOR partner for 'num'.
    // For each bit (MSB → LSB) prefer the opposite bit (1-cur) if present;
    // that will set the corresponding XOR bit to 1. Otherwise follow the
    // same bit path.
    int max_XOR(int num)
    {

        Node *tmp = root;
        int max_XOR_val = 0;

        for (int i = 31; i >= 0; i--)
        {
            int probe = num >> i; // bring bit i to LSB
            int cur = probe & 1;  // current bit of num
            int needed = 1 - cur; // opposite bit to maximize XOR at this position

            if (tmp->keyExists(needed))
            {
                // Opposite bit exists → we can set this bit in the XOR result
                max_XOR_val = max_XOR_val | (1 << i);
                tmp = tmp->getNextNode(needed);
            }
            else
            {
                // Opposite bit doesn't exist → fallback to same bit
                tmp = tmp->getNextNode(cur);
            }
        }

        return max_XOR_val;
    }
};

#define P pair<pair<int, int>, int>

class Solution
{
public:
    // -------------------------------------------------------------------------
    // Problem: Maximum XOR With an Element From Array (LeetCode 1707)
    //
    // Intuition:
    // - We are asked multiple queries (xi, mi): find max XOR of xi with an element
    //   from nums[] that is ≤ mi. If no such element exists, return -1.
    // - Naively checking all nums for each query is too slow (O(N*Q)).
    // - Optimization:
    //   1. Sort nums[] and queries by mi.
    //   2. Process queries in increasing order of mi.
    //   3. Maintain a Trie of numbers ≤ current mi.
    //   4. For each query, insert new eligible nums into the Trie,
    //      then query max XOR with xi using Trie.
    //   5. If Trie is empty (no nums ≤ mi), answer is -1.
    //
    // Approach:
    // - Each number and xi is treated as a 32-bit binary string.
    // - Trie supports:
    //      insert(num): insert binary digits of num into Trie.
    //      max_XOR(xi): greedily match opposite bits to maximize XOR.
    //
    // Complexity:
    // - Sorting nums: O(N log N)
    // - Sorting queries: O(Q log Q)
    // - Trie insertion: O(32*N) = O(N)
    // - Trie query: O(32*Q) = O(Q)
    // - Total: O(N log N + Q log Q + N + Q) ≈ O(N log N + Q log Q)
    //
    // Space:
    // - Trie nodes: O(32*N) in worst case.
    // - Extra arrays: O(N + Q).
    // -------------------------------------------------------------------------
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries)
    {

        int nn = nums.size();
        int nq = queries.size();

        vector<int> ans(nq);
        vector<P> modifiedQueries; // Store queries as {{mi, xi}, original_index}

        // Step 1: Reformat queries -> pair {mi, xi} + original index
        for (int i = 0; i < nq; i++)
        {
            modifiedQueries.push_back({{queries[i][1], queries[i][0]}, i});
        }

        // Step 2: Sort nums ascending (for incremental insertion into Trie)
        sort(nums.begin(), nums.end());
        // Step 3: Sort queries by mi (so we process in increasing mi order)
        sort(modifiedQueries.begin(), modifiedQueries.end());

        Trie t;                            // binary Trie for numbers
        int numsArrayIndex = 0;            // pointer in nums[]
        int checkForSkip = numsArrayIndex; // track if Trie is empty (no insertion)

        // Step 4: Process queries one by one in order of increasing mi
        for (int i = 0; i < modifiedQueries.size(); i++)
        {

            int mi = modifiedQueries[i].first.first;  // max value allowed
            int xi = modifiedQueries[i].first.second; // query number
            int index = modifiedQueries[i].second;    // original query index

            // Insert all nums[] ≤ current mi into the Trie
            while (numsArrayIndex < nn && nums[numsArrayIndex] <= mi)
            {
                t.insert(nums[numsArrayIndex]);
                numsArrayIndex++;
            }

            // If no numbers inserted, Trie is empty → answer = -1
            if (numsArrayIndex == checkForSkip)
            {
                ans[index] = -1;
                continue;
            }

            // Step 5: Query Trie to get maximum XOR for xi
            int max_limited_XOR_val = t.max_XOR(xi);
            ans[index] = max_limited_XOR_val;
        }

        return ans;
    }
};
int main()
{
    return 0;
}