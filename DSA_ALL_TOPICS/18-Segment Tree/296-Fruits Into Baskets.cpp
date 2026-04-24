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

*/

//-------------------------------------------
// Approach: Segment tree + Binary search
//-------------------------------------------

/*
 * Problem: Fruits Into Baskets III (LeetCode 3479)
 * ------------------------------------------------
 * Goal: Place each fruit into the *leftmost* available basket with capacity >= fruit size.
 * Count how many fruits cannot be placed.
 *
 * Approach: Segment Tree (Range Maximum Query)
 * --------------------------------------------
 * Why Segment Tree?
 * A brute force search for each fruit would be O(N^2).
 * A Segment Tree allows us to:
 * 1. Quickly check if a range [L, R] has ANY basket capable of holding the fruit (Max Query).
 * 2. Find the *leftmost* such basket in O(log N).
 * 3. Mark that basket as "used" (Update value to 0) in the same pass.
 *
 * Time Complexity: O(N log N)
 * - Building the tree: O(N)
 * - Processing N fruits: Each fruit triggers one tree traversal taking O(log N).
 * Total: N * log N.
 *
 * Space Complexity: O(4 * N)
 * - Standard space required for the Segment Tree array.
 */
class Solution
{
private:
    // Segment Tree Array
    // segT[i] stores the MAXIMUM capacity available in the range covered by node 'i'.
    vector<int> segT;
    int N;

    /*
     * Method: buildTree
     * -----------------
     * Constructs the Segment Tree from the initial baskets array.
     * Each internal node stores the max(left_child, right_child).
     *
     * Complexity: O(N) - Visits every node once.
     */
    void buildTree(int l, int r, int segI, vector<int> &baskets)
    {

        // Base Case: Leaf Node
        // Represents a single basket at index 'l'.
        if (l == r)
        {
            segT[segI] = baskets[l];
            return;
        }

        int mid = l + (r - l) / 2;

        // Recursively build children
        buildTree(l, mid, 2 * segI + 1, baskets);
        buildTree(mid + 1, r, 2 * segI + 2, baskets);

        // Current node stores the Maximum capacity of its children
        segT[segI] = max(segT[2 * segI + 1], segT[2 * segI + 2]);
    }

    /*
     * Method: placedFruit
     * -------------------
     * The Core Logic: Finds the leftmost valid basket, places the fruit, and updates the tree.
     * * Logic:
     * 1. Check Root: If segT[node] < fruit, this entire range is useless. Return false.
     * 2. Leaf Node: If we reach a leaf, we found the basket! Set capacity to 0 (used).
     * 3. Internal Node:
     * - Prefer LEFT child: If left child's max capacity >= fruit, go Left.
     * (This satisfies the "leftmost" requirement).
     * - Otherwise: Go Right.
     * 4. Update: After returning from child, update current node's max value.
     *
     * Complexity: O(log N) - Traverses height of the tree.
     */
    bool placedFruit(int l, int r, int segI, int fruit, vector<int> &baskets)
    {

        // PRUNING / OPTIMIZATION
        // If the max capacity in this current range is less than the fruit size,
        // it is impossible to place the fruit here. Prune this branch immediately.
        if (segT[segI] < fruit)
        {
            return false;
        }

        // BASE CASE: Leaf Node Found
        // Since we passed the check above, we know baskets[l] >= fruit.
        if (l == r)
        {
            segT[segI] = 0; // Mark basket as "Used" (capacity 0)
            return true;
        }

        int mid = l + (r - l) / 2;

        int leftSegI = 2 * segI + 1;
        int rightSegI = 2 * segI + 2;

        bool placed = false;

        // GREEDY SEARCH STRATEGY
        // We want the *leftmost* basket.
        // Always check the Left Child first.
        // If the left subtree has a basket capable of holding the fruit (Max >= fruit),
        // we MUST search there first.
        if (segT[leftSegI] >= fruit)
        {
            placed = placedFruit(l, mid, leftSegI, fruit, baskets);
        }
        else
        {
            // Only search Right if Left is impossible
            placed = placedFruit(mid + 1, r, rightSegI, fruit, baskets);
        }

        // UPDATE / BACKTRACKING
        // Since one basket capacity changed to 0, we must update the max value
        // of the current node to reflect the new state of the range.
        segT[segI] = max(segT[leftSegI], segT[rightSegI]);

        return placed;
    }

public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {

        N = fruits.size();

        // Allocate Segment Tree size (4*N is safe upper bound)
        segT.resize(4 * N);

        // O(N) Build step
        buildTree(0, N - 1, 0, baskets);

        int unplacedCount = 0;

        // O(N) Loop
        for (int i = 0; i < N; i++)
        {
            int fruit = fruits[i];

            // O(log N) Search & Update per fruit
            // If placedFruit returns false, it means no basket was found.
            if (!placedFruit(0, N - 1, 0, fruit, baskets))
            {
                unplacedCount++;
            }
        }

        return unplacedCount;
    }
};

int main()
{

    return 0;
}