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

1. Title: Diameter of Binary Tree

Links:
https://takeuforward.org/data-structure/calculate-the-diameter-of-a-binary-tree/
https://www.youtube.com/watch?v=Rezetez59Nk&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=16
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/diameter-of-binary-tree
https://leetcode.com/problems/diameter-of-binary-tree/description/


Problem statement:
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Examples:
  Example 1:
  Input: root = [1,2,3,4,5]
  Output: 3
  Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

  Example 2:
  Input: root = [1,2]
  Output: 1



INPUT::::::


OUTPUT::::::


*/
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//-------------------------------------------------------------------------------
// 1. Title: Diameter of Binary Tree
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: POST-ORDER DFS (BOTTOM-UP DP ON TREES)
 * ============================================================================
 * * [THE INTUITION]
 * Problem: Find the longest path (diameter) between ANY two nodes in the tree.
 * The longest path does not necessarily pass through the root. However, every
 * path must have a "highest" node (the peak where it curves from left to right).
 *
 * If we treat a specific node as the "peak", the longest path passing through
 * it is exactly: (Height of its Left Subtree) + (Height of its Right Subtree).
 *
 * * [THE MECHANICS]
 * A naive approach would calculate the height for every single node, resulting
 * in O(N^2) time. We avoid this by computing the height "Bottom-Up" (Post-Order).
 * As each child calculates its height to return to its parent, we intercept
 * those values, calculate the local diameter, and update a running maximum.
 * This allows us to find the max diameter while calculating heights in a
 * single O(N) pass.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N) -> We visit every node exactly once.
 * - Space Complexity: O(H) -> O(log N) average, O(N) worst-case. This is the
 *   memory consumed by the recursive call stack.
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Helper function that returns the height of the tree while
   * simultaneously updating the maximum diameter found so far.
   *
   * @param node   The current node we are evaluating.
   * @param maxDia Passed by reference to act as a thread-safe global accumulator.
   * @return int   The height of the subtree rooted at `node`.
   */
  int rec_height(TreeNode *node, int &maxDia)
  {
    int lh = 0, rh = 0;

    // POST-ORDER TRAVERSAL: Ask children for their heights first
    if (node->left)
    {
      lh = rec_height(node->left, maxDia);
    }

    if (node->right)
    {
      rh = rec_height(node->right, maxDia);
    }

    // INTERCEPT & UPDATE: Calculate the diameter passing through THIS node
    // (Length of path is the sum of edges from left and right heights)
    int dia = lh + rh;
    maxDia = max(maxDia, dia);

    // RETURN HEIGHT: The height of THIS node is 1 + the tallest child
    return 1 + max(lh, rh);
  }

public:
  int diameterOfBinaryTree(TreeNode *root)
  {
    // Base case: An empty tree has a diameter of 0
    if (!root)
      return 0;

    int maxDia = 0;

    // Kick off the bottom-up DFS
    rec_height(root, maxDia);

    return maxDia;
  }
};

int main()
{
  return 0;
}
