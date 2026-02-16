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
    1 <= nums.length <= 2 * 105
    0 <= nums[i] <= 231 - 1


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
//
// -----------------------------------------------------------------------------
// Problem: Maximum XOR of two numbers in an array
// Intuition:
//  - For any bit position, XOR is maximized when the two bits differ (1^0 = 1).
//  - To maximize the overall XOR between two numbers, we try to maximize the
//    contribution from the most significant bit down to the least significant.
//  - A binary Trie (0/1 children) stores bit paths of numbers (MSB → LSB).
//    For a query number, we greedily walk the Trie choosing the opposite bit
//    if present (to set the current XOR bit to 1); otherwise we follow the
//    same bit. This yields the maximum XOR achievable with any inserted number.
// Approach:
//  - Build a Trie by inserting all numbers' 32-bit representations.
//  - For each number, query the Trie to find the best partner that gives the
//    maximum XOR, and track the global maximum.
// Complexity:
//  - Time: O(32*N) for insertion + O(32*N) for queries ≈ O(N) (constants: 32 bits).
//  - Space: O(32*N) worst-case for Trie nodes (each number potentially adds 32 nodes).
// -----------------------------------------------------------------------------

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

class Solution
{
public:
    // Build the trie with all numbers and then query each number to find the
    // maximum XOR partner. Return the maximum found.
    int findMaximumXOR(vector<int> &nums)
    {

        Trie t;

        // Insert all numbers into the trie (building the search space)
        for (int i = 0; i < nums.size(); i++)
        {
            t.insert(nums[i]);
        }

        // Initialize to the smallest integer so the first comparison succeeds
        int max_XOR_val = INT_MIN;

        // For every number, query the trie to compute the best XOR partner
        for (int i = 0; i < nums.size(); i++)
        {
            max_XOR_val = max(max_XOR_val, t.max_XOR(nums[i]));
        }

        return max_XOR_val;
    }
};

int main()
{
    return 0;
}