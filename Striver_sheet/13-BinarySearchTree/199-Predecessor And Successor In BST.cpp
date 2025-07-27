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

1. Title: Predecessor And Successor In BST

Links:
https://takeuforward.org/plus/dsa/problems/inorder-successor-and-predecessor-in-bst?tab=editorial
https://www.naukri.com/code360/problems/predecessor-and-successor-in-bst_893049?leftPanelTabValue=PROBLEM


Problem statement:
You have been given a binary search tree of integers with ‘N’ nodes. You are also given 'KEY' which represents data of a node of this tree.
Your task is to return the predecessor and successor of the given node in the BST.

Note:
1. The predecessor of a node in BST is that node that will be visited just before the given node in the inorder traversal of the tree. If the given node is visited first in the inorder traversal, then its predecessor is NULL.
2. The successor of a node in BST is that node that will be visited immediately after the given node in the inorder traversal of the tree. If the given node is visited last in the inorder traversal, then its successor is NULL.
3. The node for which the predecessor and successor will not always be present. If not present, you can hypothetically assume it's position (Given that it is a BST) and accordingly find out the predecessor and successor.
4. A binary search tree (BST) is a binary tree data structure which has the following properties.
     • The left subtree of a node contains only nodes with data less than the node’s data.
     • The right subtree of a node contains only nodes with data greater than the node’s data.
     • Both the left and right subtrees must also be binary search trees.

Examples:
  15 10 20 8 12 16 25 -1 -1 -1 -1 -1 -1 -1 -1
  10
  Sample output 1:
  8 12
  The inorder traversal of this tree will be 8 10 12 15 16 20 25.
  Since the node with data 8 is on the immediate left of the node with data 10 in the inorder traversal, the node with data 8 is the predecessor.
  Since the node with data 12 is on the immediate right of the node with data 10 in the inorder traversal, the node with data 12 is the successor.

  Sample Input 2:
  10 5 -1 -1 -1
  5
  Sample output 2:
  -1 10

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
  // 1. Title: Predecessor And Successor In BST
  //-------------------------------------------------------------------------------

  /**
   * Function: findSuccessor
   * ------------------------
   * Finds the inorder successor of a given key in a Binary Search Tree (BST).
   *
   * Approach:
   * - Start at the root and traverse the BST.
   * - If current node?s value is greater than the key, it's a candidate for successor.
   *   - Save it and go left to try to find a smaller valid candidate.
   * - If current node?s value is less than or equal to the key, go right to look for a larger node.
   * - Continue until the node is NULL.
   *
   * Time Complexity: O(H) where H is the height of the tree.
   *     - O(log N) for balanced BST, O(N) in worst case (skewed tree).
   * Space Complexity: O(1) ? Iterative, constant space.
   */
  int findSuccessor(TreeNodeN<int> *root, int key)
  {
    int ans = INT_MAX;

    while (root)
    {
      if (root->data > key)
      {
        ans = min(ans, root->data);
        root = root->left; // Try to find a smaller candidate
      }
      else
      {
        root = root->right;
      }
    }

    return ans;
  }

  /**
   * Function: findPredecessor
   * --------------------------
   * Finds the inorder predecessor of a given key in a Binary Search Tree (BST).
   *
   * Approach:
   * - Start at the root and traverse the BST.
   * - If current node?s value is less than the key, it's a candidate for predecessor.
   *   - Save it and go right to try to find a larger valid candidate.
   * - If current node?s value is greater than or equal to the key, go left to look for a smaller node.
   * - Continue until the node is NULL.
   *
   * Time Complexity: O(H) where H is the height of the tree.
   *     - O(log N) for balanced BST, O(N) in worst case.
   * Space Complexity: O(1) ? Iterative, constant space.
   */
  int findPredecessor(TreeNodeN<int> *root, int key)
  {
    int ans = INT_MIN;

    while (root)
    {
      if (root->data < key)
      {
        ans = max(ans, root->data);
        root = root->right; // Try to find a larger candidate
      }
      else
      {
        root = root->left;
      }
    }

    return ans;
  }

  /**
   * Function: predecessorSuccessor
   * -------------------------------
   * Finds both the inorder predecessor and successor of a given key in a BST.
   *
   * Approach:
   * - Use helper functions `findPredecessor` and `findSuccessor`.
   * - If no valid predecessor or successor is found, replace result with -1.
   *
   * Time Complexity: O(H) + O(H) = O(H)
   *     - As both predecessor and successor searches take O(H).
   *     - O(log N) for balanced BST, O(N) for skewed.
   * Space Complexity: O(1)
   *
   * Returns:
   * - A pair {predecessor, successor}
   */
  pair<int, int> predecessorSuccessor(TreeNodeN<int> *root, int key)
  {
    if (root == NULL)
      return {-1, -1};

    int pre = findPredecessor(root, key);
    int suc = findSuccessor(root, key);

    if (pre == INT_MIN)
      pre = -1;
    if (suc == INT_MAX)
      suc = -1;

    return {pre, suc};
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
