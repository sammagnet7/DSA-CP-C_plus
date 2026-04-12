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
    1 <= nums.length, queries.length <= 10^5
    queries[i].length == 2
    0 <= nums[j], xi, mi <= 10^9


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

/**
 * @class TrieNode
 * @brief A Bitwise Prefix Tree Node optimized for binary math (0s and 1s).
 */
class TrieNode
{
public:
    TrieNode *children[2];

    TrieNode()
    {
        children[0] = nullptr;
        children[1] = nullptr;
    }
    // HACK: Destructor omitted for competitive programming to prevent MLE.
};

/**
 * @class Trie
 * @brief Bitwise Trie designed to greedily maximize XOR operations.
 */
class Trie
{
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    /**
     * @brief Inserts a 32-bit integer into the Trie.
     * * APPROACH:
     * We iterate from the Most Significant Bit (31) down to the Least Significant Bit (0).
     * By placing the highest-value bits at the top of the tree, we set up the structure
     * perfectly for the greedy search later. If a path for a bit doesn't exist, we build it.
     */
    void insert(int num)
    {
        TrieNode *curNode = root;

        for (int i = 31; i >= 0; --i)
        {
            int curBit = (num >> i) & 1;

            if (curNode->children[curBit] == nullptr)
            {
                curNode->children[curBit] = new TrieNode();
            }

            curNode = curNode->children[curBit];
        }
    }

    /**
     * @brief Greedily finds the maximum possible XOR for a given number.
     * @param num The number we want to XOR against the Trie.
     * @return The maximum XOR value achieved.
     * * APPROACH:
     * Starting from the MSB (31), we look at the current bit of `num`. To maximize XOR,
     * we desperately want to find the opposite bit in the Trie (since 1^0=1 and 0^1=1).
     * - If the opposite bit branch exists: We take it! We shift our running `maxXor`
     * left by 1 and turn the new bit ON (| 1).
     * - If the opposite bit branch does NOT exist: We are forced to take the matching bit.
     * We shift our running `maxXor` left by 1, leaving the new bit OFF (0).
     */
    int getMaxXor(int num)
    {
        TrieNode *curNode = root;
        int maxXor = 0;

        for (int i = 31; i >= 0; --i)
        {
            int curBit = (num >> i) & 1;
            int oppBit = (!curBit);

            if (curNode->children[oppBit] != nullptr)
            {
                maxXor = (maxXor << 1) | 1;
                curNode = curNode->children[oppBit];
            }
            else
            {
                maxXor = (maxXor << 1);
                curNode = curNode->children[curBit];
            }
        }

        return maxXor;
    }
};

// Alias to cleanly store {threshold_m, original_index_i, value_x}
using T = tuple<int, int, int>;

class Solution
{
public:
    /**
     * @brief Finds the max XOR for queries bounded by a maximum element threshold 'm_i'.
     * * APPROACH (Offline Queries):
     * Deleting numbers from a Trie is difficult. Instead of processing queries in the
     * order they are given, we process them "offline".
     * 1. Sort the `nums` array in ascending order.
     * 2. Store the original indices of the queries, then sort the queries based on their
     * threshold `m` in ascending order.
     * 3. Because `m` is strictly increasing, we can use a two-pointer approach. We iterate
     * through the sorted queries and continuously `insert` numbers into the Trie as long
     * as they are <= the current `m`. We never have to remove a number!
     * 4. Query the Trie and store the result in the original index.
     */
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries)
    {

        // 1. Sort the data array
        sort(nums.begin(), nums.end());

        int q = queries.size();
        vector<T> offlineQueries;

        // 2. Bind query data together to preserve the original index during sorting
        for (int i = 0; i < q; ++i)
        {
            int x = queries[i][0];
            int m = queries[i][1];
            offlineQueries.push_back({m, i, x});
        }

        // Sort queries by threshold 'm' (first element of the tuple)
        sort(offlineQueries.begin(), offlineQueries.end());

        Trie trie;

        // Pre-fill answers with -1 to safely handle cases where the Trie remains empty
        vector<int> ans(q, -1);

        int numsIdx = 0;

        // 3. Process the queries in increasing order of 'm'
        for (int idx = 0; idx < q; ++idx)
        {

            // Unpack the tuple
            auto [m, i, x] = offlineQueries[idx];

            // Insert numbers into the Trie strictly up to the current threshold
            while (numsIdx < nums.size() && nums[numsIdx] <= m)
            {
                trie.insert(nums[numsIdx]);
                ++numsIdx;
            }

            // If numsIdx > 0, the Trie has at least one number, so it is safe to query
            if (numsIdx > 0)
            {
                int curMaxXor = trie.getMaxXor(x);
                ans[i] = curMaxXor;
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}