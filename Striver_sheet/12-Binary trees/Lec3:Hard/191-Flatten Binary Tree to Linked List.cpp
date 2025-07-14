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

1. Title: Flatten Binary Tree to Linked List

Links:
https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/
https://takeuforward.org/plus/dsa/problems/flatten-binary-tree-to-linked-list
https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/


Problem statement:
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 
Examples:
  Example 1:
  Input: root = [1,2,5,3,4,null,6]
  Output: [1,null,2,null,3,null,4,null,5,null,6]

  Example 2:
  Input: root = []
  Output: []

  Example 3:
  Input: root = [0]
  Output: [0]
 

Constraints:
  The number of nodes in the tree is in the range [0, 2000].
  -100 <= Node.val <= 100
 
Follow up: Can you flatten the tree in-place (with O(1) extra space)?


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:


Problem statement:


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

template <typename T = int>
struct TreeNodeN
{
  int data;
  TreeNodeN *left;
  TreeNodeN *right;
  TreeNodeN() : data(0), left(nullptr), right(nullptr) {}
  TreeNodeN(int x) : data(x), left(nullptr), right(nullptr) {}
  TreeNodeN(int x, TreeNodeN *left, TreeNodeN *right) : data(x), left(left), right(right) {}
};

template <typename T>
class BinaryTreeNode
{
public:
  T data;
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;

  BinaryTreeNode(T data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Morris Inorder Traversal
  //-------------------------------------------------------------------------------

  /**
   * Method: preOrder
   * ----------------
   * Recursively flattens a binary tree into a linked list **in-place** following preorder traversal.
   *
   * Approach:
   * - Recursively process the left subtree, attaching it to the right of the current node.
   * - Then, attach the right subtree to the tail of the newly added right subtree.
   * - Return the tail of the flattened subtree rooted at the current node.
   *
   * The flattened tree follows the structure:
   *      Node → Left → Right   → becomes → Node → Right (flattened left first)
   *
   * Example:
   * Before:      1
   *            /   \
   *           2     5
   *          / \     \
   *         3   4     6
   *
   * After: 1 → 2 → 3 → 4 → 5 → 6
   *
   * Time Complexity: O(N)
   *     - Each node is visited once.
   * Space Complexity: O(H)
   *     - Due to recursive call stack, where H = height of tree.
   *
   * Parameters:
   * - node: Pointer to the current root node of the subtree.
   *
   * Returns:
   * - The tail node (last node in the flattened structure starting at this node).
   */
  TreeNode *preOrder(TreeNode *node)
  {
    TreeNode *prevLeft = node->left;
    TreeNode *prevRight = node->right;

    TreeNode *tail = node;

    if (prevLeft != NULL)
    {
      node->right = prevLeft;
      node->left = NULL;
      tail = preOrder(prevLeft); // Flatten left subtree and get its tail
    }

    if (prevRight != NULL)
    {
      tail->right = prevRight;    // Connect original right subtree after left's tail
      tail = preOrder(prevRight); // Flatten right subtree and update tail
    }

    return tail;
  }

  /**
   * Method: preOrder_Morris
   * -----------------------
   * Flattens the binary tree into a linked list using **Morris Preorder Traversal** in-place.
   *
   * This approach avoids recursion and stack, modifying the tree during traversal.
   * It threads the rightmost node of the left subtree to the current node's right child,
   * effectively weaving the tree into a preorder-linked list without extra space.
   *
   * Approach:
   * - For each node:
   *     - If left child exists:
   *         - Find the rightmost node in the left subtree.
   *         - Attach the current node’s right subtree to this rightmost node.
   *         - Move the left subtree to the right and nullify the left.
   *     - Move to the right child (which is the next node in flattened form).
   *
   * Time Complexity: O(N)
   *     - Each node and each edge is processed at most once.
   * Space Complexity: O(1)
   *     - No recursion or stack used; tree is modified in-place.
   *
   * Parameters:
   * - node: Pointer to the root of the binary tree.
   */
  void preOrder_Morris(TreeNode *node)
  {
    TreeNode *cur = node;

    while (cur)
    {
      if (cur->left == NULL)
      {
        // No left child, move to right
        cur = cur->right;
      }
      else
      {
        TreeNode *prevLeft = cur->left;
        TreeNode *prevRight = cur->right;

        // Find rightmost node in left subtree
        TreeNode *tmp = cur->left;
        while (tmp->right)
        {
          tmp = tmp->right;
        }

        // Connect right subtree to rightmost node
        tmp->right = prevRight;

        // Move left subtree to right
        cur->left = NULL;
        cur->right = prevLeft;

        cur = cur->right;
      }
    }
  }

  /**
   * Method: flatten
   * ---------------
   * Public API to flatten a binary tree to a linked list in-place.
   *
   * You may choose between:
   * - `preOrder()`  → Recursive solution using O(H) space.
   * - `preOrder_Morris()` → Optimized Morris traversal using O(1) space.
   *
   * Parameters:
   * - root: Pointer to the root of the binary tree.
   */
  void flatten(TreeNode *root)
  {
    if (root == NULL)
      return;

    // Option 1: Recursive (uncomment to use)
    // preOrder(root);

    // Option 2: Morris traversal (iterative and space-efficient)
    preOrder_Morris(root);
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
