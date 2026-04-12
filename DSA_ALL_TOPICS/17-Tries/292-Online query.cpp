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

1. Title: Maximum XOR of Two Numbers in an Array

Links:
Pre-requisite:
    https://www.youtube.com/watch?v=5iyuU4hQFrw
    https://takeuforward.org/trie/bit-prerequisites-for-trie-problems

https://takeuforward.org/data-structure/maximum-xor-of-two-numbers-in-an-array/
https://www.youtube.com/watch?v=EIhAwfHubE8&list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp&index=7
https://takeuforward.org/plus/dsa/problems/maximum-xor-of-two-numbers-in-an-array?tab=editorial
https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/description/


Problem statement:
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

Examples:
    Example 1:
    Input: nums = [3,10,5,25,2,8]
    Output: 28
    Explanation: The maximum result is 5 XOR 25 = 28.

    Example 2:
    Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
    Output: 127


Constraints:
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 2^31 - 1


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
// 1. Title: Maximum XOR of Two Numbers in an Array
//-------------------------------------------------------------------------------

class TrieNode
{
public:
    TrieNode *children[2];

    TrieNode()
    {
        children[0] = nullptr;
        children[1] = nullptr;
    }

    /* HACK: Destructor intentionally commented out for Competitive Programming platforms
     * like LeetCode to bypass slow memory deallocation times (prevents MLE).
     */
    // ~TrieNode(){
    //     if(children[0] != nullptr){ delete children[0]; children[0] = nullptr; }
    //     if(children[1] != nullptr){ delete children[1]; children[1] = nullptr; }
    // }
};

/**
 * @class Trie
 * @brief A Bitwise Prefix Tree designed to find the Maximum XOR in O(N) time.
 * * ============================================================================
 * 🧠 INTUITION & WHY WE USE A TRIE
 * ============================================================================
 * A brute-force approach compares every pair in the array, resulting in O(N^2)
 * time complexity. For an array of size 10^5, this requires 10 billion operations,
 * which guarantees a Time Limit Exceeded (TLE) error.
 * * The goal of XOR is to find differing bits (1 ^ 0 = 1). To yield the maximum
 * numerical value, we desperately want '1's in the Most Significant Bit (MSB)
 * positions. For example, securing a '1' in the 31st bit is worth over 2 billion,
 * which is mathematically better than having '1's in every single bit after it.
 * * WHY A TRIE?
 * A Trie perfectly organizes and groups numbers by their leading bits. By inserting
 * binary representations from MSB (31) down to LSB (0), the Trie transforms into a
 * "greedy decision tree". Instead of checking all numbers, we can take a number
 * and actively "hunt" down the branches of the Trie for the exact bits that will
 * maximize our XOR, skipping millions of suboptimal pairs instantly.
 * * ============================================================================
 * ⚙️ APPROACH
 * ============================================================================
 * 1. Build Phase: Insert every number's 32-bit sequence into the Trie.
 * 2. Query Phase: For every number, calculate its max possible XOR by walking
 * down the Trie.
 * 3. The Greedy Choice: At each bit level, identify the "opposite" bit. If the
 * Trie has a branch for the opposite bit, we MUST take it. We shift our running
 * total left and append a '1'. If the opposite bit doesn't exist, we are forced
 * to take the matching bit, shifting our total left and appending a '0'.
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

    // ~Trie(){ delete root; }

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

class Solution
{
public:
    int findMaximumXOR(vector<int> &nums)
    {
        Trie trie;

        // 1. Build the Trie
        for (int i = 0; i < nums.size(); ++i)
        {
            trie.insert(nums[i]);
        }

        int globalMax = 0;

        // 2. Greedily find the max XOR for every number
        for (int i = 0; i < nums.size(); ++i)
        {
            int curMaxXor = trie.getMaxXor(nums[i]);
            globalMax = max(globalMax, curMaxXor);
        }

        return globalMax;
    }
};

int main()
{
    return 0;
}