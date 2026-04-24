#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*

Fruits Into Baskets III

Link:
https://leetcode.com/problems/fruits-into-baskets-iii/description/


Problem statement:
You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.

From left to right, place the fruits according to these rules:

Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
Each basket can hold only one type of fruit.
If a fruit type cannot be placed in any basket, it remains unplaced.
Return the number of fruit types that remain unplaced after all possible allocations are made.


Example 1:
    Input: fruits = [4,2,5], baskets = [3,5,4]
    Output: 1
    Explanation:
    fruits[0] = 4 is placed in baskets[1] = 5.
    fruits[1] = 2 is placed in baskets[0] = 3.
    fruits[2] = 5 cannot be placed in baskets[2] = 4.
    Since one fruit type remains unplaced, we return 1.

Example 2:
    Input: fruits = [3,6,1], baskets = [6,4,7]
    Output: 0
    Explanation:
    fruits[0] = 3 is placed in baskets[0] = 6.
    fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity) but can be placed in the next available basket, baskets[2] = 7.
    fruits[2] = 1 is placed in baskets[1] = 4.
    Since all fruits are successfully placed, we return 0.


Constraints:
    n == fruits.length == baskets.length
    1 <= n <= 10^5
    1 <= fruits[i], baskets[i] <= 10^9

-----------------------------------------------------------------------------------------------------------

*/

#include <vector>
#include <algorithm>

using namespace std;

/**
 * ============================================================================
 * SEGMENT TREE: RANGE MAXIMUM QUERY (RMaxQ) + DESCENT ALGORITHM
 * ============================================================================
 * * [THE INTUITION: WHY A SEGMENT TREE?]
 * Problem Goal: Find the *leftmost* basket with capacity >= fruit quantity.
 * * 1. Why Brute Force Fails: Scanning left-to-right for every fruit takes
 * O(N) per fruit, leading to O(N^2) total time. With N=10^5, this TLEs.
 * 2. Why Standard Binary Search Fails: To use std::lower_bound in O(log N),
 * the array MUST be sorted. But sorting the baskets destroys their original
 * left-to-right order, making it impossible to guarantee the "leftmost" rule.
 * 3. The Segment Tree Solution: We need a structure that preserves the original
 * indices but allows us to skip massive chunks of the array. By building a
 * Range Maximum tree, we can look at a node covering a huge sub-array and ask:
 * "Is the absolute biggest basket in this entire section >= my fruit?"
 * If NO, we prune the whole section in O(1) time.
 * If YES, we dive into the LEFT child first, guaranteeing we find the leftmost match.
 * * * Time Complexities:
 * - Build: O(N)       -> We visit every node exactly once to build max capacities.
 * - Find & Update: O(log N) -> We only traverse a single path from root to leaf.
 * - Total: O(N log N) -> Processing all N fruits.
 * - Space: O(N)       -> 4*N array allocation.
 * ============================================================================
 */
class SegmentTree
{
private:
    vector<int> tree;
    int n;

    /**
     * HELPER: Bottom-up construction of the Range Maximum Tree.
     * @param data Passed by reference to avoid a massive O(N) deep copy.
     */
    void buildTree(int treeIdx, int start, int end, const vector<int> &data)
    {
        if (start == end)
        {
            tree[treeIdx] = data[start];
            return;
        }

        int mid = start + (end - start) / 2;
        buildTree(2 * treeIdx + 1, start, mid, data);
        buildTree(2 * treeIdx + 2, mid + 1, end, data);

        tree[treeIdx] = max(tree[2 * treeIdx + 1], tree[2 * treeIdx + 2]);
    }

    /**
     * HELPER: The Descent Algorithm (Combined Query & Update).
     * @return true if a valid basket was found and allocated, false otherwise.
     */
    bool findAndReplaceLeftMost(int treeIdx, int start, int end, int val)
    {
        // Base Case 1: We reached a leaf node.
        if (start == end)
        {
            if (tree[treeIdx] < val)
            {
                return false;
            }
            else
            {
                tree[treeIdx] = 0; // "Remove" the basket
                return true;
            }
        }

        // PRUNING: The absolute maximum capacity in this entire sub-tree is too small.
        else if (tree[treeIdx] < val)
        {
            return false;
        }

        // RECURSIVE SEARCH: We have enough capacity *somewhere* in this sub-tree.
        else
        {
            int mid = start + (end - start) / 2;

            // PRIORITY 1: Always try the LEFT branch first for "leftmost".
            bool ret = findAndReplaceLeftMost(2 * treeIdx + 1, start, mid, val);

            if (ret)
            {
                tree[treeIdx] = max(tree[2 * treeIdx + 1], tree[2 * treeIdx + 2]);
                return true;
            }

            // PRIORITY 2: If the left branch failed, it MUST be in the RIGHT branch.
            ret = findAndReplaceLeftMost(2 * treeIdx + 2, mid + 1, end, val);

            if (ret)
            {
                tree[treeIdx] = max(tree[2 * treeIdx + 1], tree[2 * treeIdx + 2]);
                return true;
            }

            return false;
        }
    }

public:
    SegmentTree(int n, const vector<int> &data)
    {
        this->n = n;
        tree.assign(4 * n, 0);
        buildTree(0, 0, n - 1, data);
    }

    bool allocateLeftMost(int val)
    {
        return findAndReplaceLeftMost(0, 0, n - 1, val);
    }
};

class Solution
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        int n = fruits.size();
        SegmentTree segTree(n, baskets);
        int unallocated = 0;

        for (int f : fruits)
        {
            if (!segTree.allocateLeftMost(f))
            {
                ++unallocated;
            }
        }

        return unallocated;
    }
};

int main()
{

    return 0;
}