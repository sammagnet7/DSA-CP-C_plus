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

1. Title: Insert into a Binary Search Tree

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/medium/insert-a-given-node-in-bst?tab=editorial
https://leetcode.com/problems/insert-into-a-binary-search-tree/description/


Problem statement:
You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

Examples:
  Example 1:
  Input: root = [4,2,7,1,3], val = 5
  Output: [4,2,7,1,3,5]
  Explanation: Another accepted tree is:

  Example 2:
  Input: root = [40,20,60,10,30,50,70], val = 25
  Output: [40,20,60,10,30,50,70,null,null,25]

  Example 3:
  Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
  Output: [4,2,7,1,3,5]


Constraints:
  The number of nodes in the tree will be in the range [0, 104].
  -108 <= Node.val <= 108
  All the values Node.val are unique.
  -108 <= val <= 108
  It's guaranteed that val does not exist in the original BST.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Delete Node in a BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/medium/delete-a-node-in-bst?tab=editorial
https://leetcode.com/problems/delete-node-in-a-bst/description/

Problem statement:
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.


Example 1:
  Input: root = [5,3,6,2,4,null,7], key = 3
  Output: [5,4,6,2,null,null,7]
  Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
  One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
  Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

  Example 2:
  Input: root = [5,3,6,2,4,null,7], key = 0
  Output: [5,3,6,2,4,null,7]
  Explanation: The tree does not contain a node with value = 0.

  Example 3:
  Input: root = [], key = 0
  Output: []


Constraints:
  The number of nodes in the tree is in the range [0, 104].
  -105 <= Node.val <= 105
  Each node has a unique value.
  root is a valid binary search tree.
  -105 <= key <= 105


Follow up: Could you solve it with time complexity O(height of tree)?

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
  // 1. Title: Insert into a Binary Search Tree
  //-------------------------------------------------------------------------------

  // Optimal
  // Time: O(Log N)
  // Space: O(Log N)
  TreeNode *insertIntoBST(TreeNode *root, int val)
  {

    TreeNode *newN = new TreeNode(val);

    if (root == NULL)
      return newN;

    TreeNode *tmp = root;
    TreeNode *prev;

    while (tmp)
    {
      prev = tmp;
      if (val < tmp->val)
      {
        tmp = tmp->left;
      }
      else if (tmp->val < val)
      {
        tmp = tmp->right;
      }
    }

    if (val < prev->val)
      prev->left = newN;
    else
      prev->right = newN;

    return root;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Delete Node in a BST
  //-------------------------------------------------------------------------------

  class Solution1
  {
  public:
    /**
     * Method: deleteNode
     * ------------------
     * Deletes a node with the given key from the BST and returns the updated root.
     *
     * Approach:
     * - Traverse the tree iteratively to find the node with the given key.
     * - Maintain a pointer to the parent (`prev`) for reconnection after deletion.
     * - If the target node has:
     *     - No children: simply remove it.
     *     - One child: replace it with its only child.
     *     - Two children: attach its right subtree to the rightmost node in its left subtree.
     * - Special handling if the node to delete is the root itself.
     *
     * Time Complexity: O(H)
     *     - In worst case (skewed tree), H = N
     *     - In balanced tree, H = log(N)
     * Space Complexity: O(1)
     *     - Iterative approach uses constant extra space.
     */
    TreeNode *deleteNode(TreeNode *root, int key)
    {
      if (root == NULL)
        return NULL;

      TreeNode *tmp = root;
      TreeNode *prev = NULL;
      TreeNode *targetN = NULL;

      // Step 1: Search for the target node and track its parent
      while (tmp)
      {
        if (tmp->val == key)
        {
          targetN = tmp;
          break;
        }
        else if (key < tmp->val)
        {
          prev = tmp;
          tmp = tmp->left;
        }
        else
        {
          prev = tmp;
          tmp = tmp->right;
        }
      }

      if (targetN == NULL)
        return root; // Node with key not found; no changes

      // Step 2: If target node is the root of the tree
      if (targetN == root)
      {
        return deleteRoot(targetN); // Replace root with proper child/subtree
      }

      // Step 3: Delete the target node and get its replacement subtree
      TreeNode *replacement = deleteRoot(targetN);

      // Step 4: Reconnect the replacement node with the parent
      if (prev->left == targetN)
        prev->left = replacement;
      else
        prev->right = replacement;

      return root;
    }

  private:
    /**
     * Method: deleteRoot
     * ------------------
     * Deletes a node and returns the new subtree root.
     * Used when the target node is either the actual root or treated as the root of its subtree.
     *
     * Approach:
     * - If the node has no children: return NULL.
     * - If the node has one child: return that child as the new root.
     * - If the node has two children:
     *     - Find the rightmost node in the left subtree.
     *     - Attach the right subtree of the node to be deleted to this rightmost node.
     *     - Return the left subtree as the new root.
     *
     * Time Complexity: O(H)
     *     - Finding rightmost node may take height of tree.
     * Space Complexity: O(1)
     *     - Constant space used.
     */
    TreeNode *deleteRoot(TreeNode *node)
    {
      // Case 1: No children
      if (node->left == NULL && node->right == NULL)
        return NULL;

      // Case 2: Only right child
      if (node->left == NULL)
        return node->right;

      // Case 3: Only left child
      if (node->right == NULL)
        return node->left;

      // Case 4: Two children
      TreeNode *tmp = node->left;

      // Find rightmost node in the left subtree
      while (tmp->right)
        tmp = tmp->right;

      // Attach the right subtree to the rightmost node
      tmp->right = node->right;

      // Return left subtree as new root
      return node->left;
    }
  };
};

int main()
{
  return 0;
}
