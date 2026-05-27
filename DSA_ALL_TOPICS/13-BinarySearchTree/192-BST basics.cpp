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

1. Title: Search in a Binary Search Tree

Links:
https://takeuforward.org/data-structure/search-in-a-binary-search-tree-2/
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/search-in-bst
https://leetcode.com/problems/search-in-a-binary-search-tree/description/


Problem statement:
You are given the root of a binary search tree (BST) and an integer val.
Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

Examples:
  Example 1:
  Input: root = [4,2,7,1,3], val = 2

                   (4)
                  /   \
                (2)   (7)
                / \
              (1) (3)

  Output: [2,1,3]

  Example 2:
  Input: root = [4,2,7,1,3], val = 5

                   (4)
                  /   \
                (2)   (7)
                / \
              (1) (3)

  Output: []

Constraints:
  The number of nodes in the tree is in the range [1, 5000].
  1 <= Node.val <= 107
  root is a binary search tree.
  1 <= val <= 107


Constraints:
  The number of nodes in the tree is in the range [1, 5000].
  1 <= Node.val <= 10^7
  root is a binary search tree.
  1 <= val <= 10^7


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Min/Max in BST

Links:
https://www.naukri.com/code360/problems/minimum-element-in-bst_8160462


Problem statement:
You are given a Binary Search Tree.
Find the minimum value in it.

Note:
All the values in the given binary search tree are unique.

Examples:
  Input : 6 4 7 2 5 N N

                 6
                / \
              4    7
              / \
            2   5

  Output: 2

  Sample Input 1: 8 5 N 3 6

                       8
                      /
                      5
                    / \
                    3   6

  Sample Output 1:  3


  Sample Input 2: 5 3 6 2 4 N N
  Sample Output 2:

Expected Time Complexity:
Try to do this in O(n), where 'n' is the number of nodes in the binary search tree.

Constraints:
0 <= ‘n’ <= 10^5
Time Limit: 1 sec

Where 'n' is the number of nodes in the binary tree.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Search in a Binary Search Tree
//-------------------------------------------------------------------------------
// Definition for a binary tree node (assumed context)
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * ============================================================================
 * TREE ALGORITHM: SEARCH IN A BINARY SEARCH TREE
 * ============================================================================
 * * [BST THEORY & CORE PROPERTIES]
 * A Binary Search Tree is a node-based binary tree with strict sorting rules:
 * 1. The left subtree of a node contains ONLY nodes with values STRICTLY LESS
 * than the node's value.
 * 2. The right subtree of a node contains ONLY nodes with values STRICTLY
 * GREATER than the node's value.
 * 3. Both the left and right subtrees must also be valid binary search trees.
 * 4. (The Secret Weapon): Performing a standard INORDER traversal
 * (Left -> Root -> Right) on a valid BST will ALWAYS yield a perfectly
 * sorted array in strictly ascending order.
 * * * [THE MENTAL MODEL: "THE HIGH-LOW GAME"]
 * Because of the strict sorting rules, we do not need to search the entire tree
 * (DFS/BFS). We treat it like a binary search algorithm. At every node:
 * - If target == root, we are done.
 * - If target < root, the target is mathematically impossible to find on the
 * right side. We discard the entire right subtree and move Left.
 * - If target > root, we discard the entire left subtree and move Right.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H)
 * - Best/Average Case: O(log N). If the tree is balanced, every step halves
 * the remaining search space, just like searching a sorted array.
 * - Worst Case: O(N). If the tree is perfectly skewed (a single chain of nodes),
 * we are essentially just traversing a linked list.
 * - SPACE COMPLEXITY: O(1)
 * By using a `while` loop instead of recursion, we require exactly zero extra
 * frames on the call stack. The space complexity is strictly constant.
 * ============================================================================
 */
class Solution
{
public:
  /**
   * ============================================================================
   * BST ALGORITHM: SEARCH (ITERATIVE)
   * ============================================================================
   * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H) -> Best/Avg Case O(log N), Worst Case O(N)
   * We only visit one node per level of the tree. If the tree is balanced, it
   * takes logarithmic time. If it is a skewed chain, it takes linear time.
   * - SPACE COMPLEXITY: O(1)
   * We only use a single pointer to traverse downwards. No stack memory used.
   * ============================================================================
   */
  TreeNode *searchBST(TreeNode *root, int val)
  {
    // Continue drilling down until we fall off the tree, or find the value
    while (root != nullptr && root->val != val)
    {
      // Ternary operator for clean branching logic
      root = (val < root->val) ? root->left : root->right;
    }

    // If we found it, root is the node. If we fell off, root is naturally nullptr.
    return root;
  }

  /**
   * ============================================================================
   * BST ALGORITHM: SEARCH (RECURSIVE)
   * ============================================================================
   * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H)
   * - SPACE COMPLEXITY: O(H) -> Stack memory is used for every downward step.
   * ============================================================================
   */
  TreeNode *searchBST(TreeNode *root, int val)
  {
    // Base case: If the tree is empty or we found the target
    if (root == nullptr || root->val == val)
    {
      return root;
    }

    // Let the recursive calls do the routing
    return (val < root->val) ? searchBST(root->left, val) : searchBST(root->right, val);
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Min/Max in BST
//-------------------------------------------------------------------------------

// Definition for a binary tree node (assumed context for this problem type)
struct Node
{
  int data;
  Node *left;
  Node *right;
  Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

/**
 * ============================================================================
 * BST ALGORITHM: FIND MINIMUM VALUE
 * ============================================================================
 * * [THE MENTAL MODEL]
 * In a valid BST, smaller values are always routed to the left. Therefore,
 * the globally minimum value will always sit at the absolute bottom-left
 * corner of the tree structure.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * We only visit exactly one node per level. If the tree is perfectly balanced,
 * it takes logarithmic time. If the tree is a skewed chain leaning left, it
 * takes linear time.
 * - SPACE COMPLEXITY: O(1)
 * We traverse downward using a `while` loop, completely avoiding the
 * recursion call stack memory overhead.
 * ============================================================================
 */
class Solution
{
public:
  int minValue(Node *root)
  {
    // Edge case: If the tree is completely empty
    if (root == nullptr)
    {
      return -1;
    }

    // Walk down the left edge of the tree until we hit a leaf node
    while (root->left != nullptr)
    {
      root = root->left;
    }

    // The node with no left child holds the minimum value
    return root->data;
  }
};

int main()
{
  return 0;
}
