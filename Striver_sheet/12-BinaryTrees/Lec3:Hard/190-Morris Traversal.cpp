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

1. Title: Morris Inorder Traversal

Links:
https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/morris-inorder-traversal-?tab=editorial
https://leetcode.com/problems/binary-tree-inorder-traversal/submissions/1697272849/


Problem statement:
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Examples:
  Example 1:
  Input: root = [1,null,2,3]
  Output: [1,3,2]

  Example 2:
  Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
  Output: [4,2,6,5,7,1,3,9,8]

  Example 3:
  Input: root = []
  Output: []

  Example 4:
  Input: root = [1]
  Output: [1]


Constraints:
  The number of nodes in the tree is in the range [0, 100].
  -100 <= Node.val <= 100


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Morris Preorder Traversal

Links:
https://takeuforward.org/data-structure/morris-preorder-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/morris-preorder-traversal-?tab=editorial
https://leetcode.com/problems/binary-tree-preorder-traversal/description/


Problem statement:
Given the root of a binary tree, return the preorder traversal of its nodes' values.

Examples:
  Example 1:
  Input: root = [1,null,2,3]
  Output: [1,2,3]

  Example 2:
  Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
  Output: [1,2,4,5,6,7,3,8,9]

  Example 3:
  Input: root = []
  Output: []

  Example 4:
  Input: root = [1]
  Output: [1]

Constraints:
  The number of nodes in the tree is in the range [0, 100].
  -100 <= Node.val <= 100

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
   * Method: inorderTraversal_Moris
   * ------------------------------
   * Performs Morris Inorder Traversal on a binary tree and stores the result in `ans`.
   *
   * Morris Traversal is a way to do an inorder traversal of a binary tree **without recursion**
   * and **without using a stack**. It temporarily modifies the tree structure by creating
   * threaded links to predecessors (rightmost nodes in the left subtree).
   *
   * Approach:
   * - Start from the root node.
   * - For each node:
   *     - If it has no left child, add its value to the result and move to the right.
   *     - Else, find its inorder predecessor in the left subtree.
   *         - If the predecessor's right is NULL, set it to the current node (thread) and go left.
   *         - If the predecessor's right is current (thread exists), remove it, add current's value,
   *           and go right.
   *
   * This method ensures that each node is visited exactly as required by inorder traversal
   * (left-root-right) and no extra space is used (stack or recursion).
   *
   * Time Complexity: O(2N) ~ amortized
   *     - Each edge is visited at most twice (once to create the thread, once to remove it).
   * Space Complexity: O(1)
   *     - No stack or recursion; uses constant space.
   *
   * Parameters:
   * - root: Pointer to the root of the binary tree.
   * - ans: Vector to store the result of inorder traversal.
   */
  void inorderTraversal_Morris(TreeNode *root, vector<int> &ans)
  {
    TreeNode *cur = root;

    while (cur)
    { // O(N)
      if (cur->left == NULL)
      {
        // No left child, visit node and move to right
        ans.push_back(cur->val);
        cur = cur->right;
      }
      else
      {
        // Find the inorder predecessor (rightmost node in left subtree)
        TreeNode *tmp = cur->left;

        while (tmp->right && tmp->right != cur)
        { // Note: amortized to O(N) after whole traversal
          tmp = tmp->right;
        }

        if (tmp->right == cur)
        {
          // Thread exists -> remove it, visit node, and move to right
          tmp->right = NULL;
          ans.push_back(cur->val);
          cur = cur->right;
        }
        else
        {
          // Create a temporary thread to the current node and move left
          tmp->right = cur;
          cur = cur->left;
        }
      }
    }
  }

public:
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    if (root == NULL)
      return ans;

    inorderTraversal_Morris(root, ans);

    return ans;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Morris Preorder Traversal
  //-------------------------------------------------------------------------------
  /**
   * Method: preorderTraversal_Morris
   * --------------------------------
   * Performs Morris Preorder Traversal on a binary tree and stores the result in `ans`.
   *
   * Morris Traversal avoids using recursion or a stack. It temporarily modifies the tree
   * by creating threads (temporary right pointers) to predecessors.
   *
   * Approach:
   * - Start from the root.
   * - For each node:
   *     - If left child is NULL: Visit the node, move to right.
   *     - Else:
   *         - Find the inorder predecessor (rightmost node in left subtree).
   *         - If the predecessor's right is NULL:
   *             - Create a thread to current node and visit current.
   *             - Move to left child.
   *         - Else:
   *             - Thread exists → remove it, and move to right child.
   *
   * Time Complexity: O(2N) : amortized
   *     - Each node is visited at most twice (creating and removing threads).
   * Space Complexity: O(1)
   *     - No extra space (stack or recursion).
   *
   * Parameters:
   * - root: Pointer to the root of the binary tree.
   * - ans: Vector to store the result of preorder traversal.
   */
  void preorderTraversal_Morris(TreeNode *root, vector<int> &ans)
  {
    TreeNode *cur = root;

    while (cur)
    {
      if (cur->left == NULL)
      {
        // No left child, visit node and move to right
        ans.push_back(cur->val);
        cur = cur->right;
      }
      else
      {
        // Find the inorder predecessor (rightmost node in left subtree)
        TreeNode *tmp = cur->left;

        while (tmp->right && tmp->right != cur)
        { // Note amortized to O(N) after whole traversal
          tmp = tmp->right;
        }

        if (tmp->right == cur)
        {
          // Thread exists -> remove it and move to right
          tmp->right = NULL;
          cur = cur->right;
        }
        else
        {
          // Create thread to return here later, visit current before going left
          ans.push_back(cur->val); // Note: moved here because pre-order
          tmp->right = cur;
          cur = cur->left;
        }
      }
    }
  }

public:
  vector<int> preorderTraversal(TreeNode *root)
  {

    vector<int> ans;

    if (root == NULL)
      return ans;

    preorderTraversal_Morris(root, ans);

    return ans;
  }
};

int main()
{
  return 0;
}
