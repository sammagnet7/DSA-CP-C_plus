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

1. Title: Check if a tree is a BST or not

Links:
https://takeuforward.org/plus/dsa/problems/check-if-a-tree-is-a-bst-or-not?tab=editorial
https://leetcode.com/problems/validate-binary-search-tree/description/


Problem statement:
Given the root of a binary tree, determine if it is a valid binary search tree (BST).
A valid BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.


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
  // 1. Title: Check if a tree is a BST or not
  //-------------------------------------------------------------------------------

  /**
   * Function: checkBSTValidity
   * --------------------------
   * Recursively checks whether the binary tree rooted at `node` is a valid Binary Search Tree (BST).
   *
   * Approach:
   * - Uses range-based validation: Each node must lie in a valid range (leftRange, rightRange).
   * - For a valid BST:
   *     - All nodes in the left subtree should be strictly less than the current node's value.
   *     - All nodes in the right subtree should be strictly greater than the current node's value.
   * - The valid range narrows as we move down the tree.
   *
   * Parameters:
   * - node: Current node to validate.
   * - leftRange: Minimum allowable value (exclusive) for the current node.
   * - rightRange: Maximum allowable value (exclusive) for the current node.
   *
   * Returns:
   * - true if the subtree rooted at `node` is a valid BST, false otherwise.
   *
   * Time Complexity: O(N), where N is the number of nodes.
   * Space Complexity: O(H), where H is the height of the tree (due to recursion stack).
   */
  bool checkBSTValidity(TreeNode *node, long long leftRange, long long rightRange)
  {
    if (node == NULL)
      return true;

    // The current node's value must be within the (leftRange, rightRange) exclusive range
    if (node->val <= leftRange || node->val >= rightRange)
      return false;

    // Validate the left subtree
    if (!checkBSTValidity(node->left, leftRange, node->val))
      return false;

    // Validate the right subtree
    if (!checkBSTValidity(node->right, node->val, rightRange))
      return false;

    // If all checks pass, the subtree is valid
    return true;
  }

  /**
   * Function: isValidBST
   * --------------------
   * Validates whether the given binary tree is a valid Binary Search Tree.
   *
   * Approach:
   * - Starts the recursive check with full valid range from LONG_MIN to LONG_MAX.
   * - Delegates the actual checking to the helper function `checkBSTValidity`.
   *
   * Parameters:
   * - root: Pointer to the root of the binary tree.
   *
   * Returns:
   * - true if the binary tree is a valid BST, false otherwise.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(H)
   */
  bool isValidBST(TreeNode *root)
  {
    if (root == NULL)
      return true;

    return checkBSTValidity(root, LONG_MIN, LONG_MAX);
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
