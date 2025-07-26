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

1. Title: Construct a BST from a preorder traversal

Links:
https://takeuforward.org/plus/dsa/problems/construct-a-bst-from-a-preorder-traversal?tab=editorial
https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/


Problem statement:
Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.
It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.
A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.
A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.



Example 1:
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Example 2:
Input: preorder = [1,3]
Output: [1,null,3]

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
  // 1. Title: Construct a BST from a preorder traversal
  //-------------------------------------------------------------------------------

  /**
   * Function: makeBst
   * -----------------
   * Constructs a Binary Search Tree (BST) from a preorder traversal array.
   *
   * Approach:
   * - Leverages the properties of BST and preorder traversal:
   *     - Preorder = [root, left subtree, right subtree]
   *     - In BST, all nodes in the left subtree are < root, and all in the right are > root.
   * - Uses a recursive approach with a reference index and an upper bound to ensure valid node placement.
   * - While traversing preorder:
   *     - If current element is greater than the allowed `upBound`, it's not a part of this subtree.
   *     - Otherwise, create a node and recursively build its left and right subtrees.
   *
   * Time Complexity: O(N)
   *     - Each node is visited once. O(3N) is a loose upper bound considering value comparisons and recursive calls.
   * Space Complexity: O(H)
   *     - No extra space except recursion stack; H is the height of the tree (O(log N) for balanced BST, O(N) worst case).
   *
   * Parameters:
   * - preorder: Vector containing preorder traversal of BST.
   * - idx: Reference index to current element in preorder.
   * - upBound: Maximum valid value allowed for the current subtree.
   *
   * Returns:
   * - Pointer to the root of the constructed BST.
   */
  TreeNode *makeBst(vector<int> &preorder, int &idx, int upBound)
  {

    if (idx == preorder.size()) // Base case: all nodes are processed
      return NULL;

    TreeNode *node = NULL;

    // If current value exceeds the allowed upper bound for this subtree, it doesn’t belong here
    if (preorder[idx] > upBound)
      return node;

    // Construct current node and advance index
    node = new TreeNode(preorder[idx++]);

    // All left children must be < current node's value
    node->left = makeBst(preorder, idx, node->val);

    // All right children must be < upper bound but > current node's value
    node->right = makeBst(preorder, idx, upBound);

    return node;
  }

  /**
   * Function: bstFromPreorder
   * -------------------------
   * Initiates the construction of BST from a given preorder traversal.
   *
   * Parameters:
   * - preorder: Vector containing the preorder traversal.
   *
   * Returns:
   * - Pointer to the root of the constructed BST.
   */
  TreeNode *bstFromPreorder(vector<int> &preorder)
  {
    if (preorder.empty())
      return NULL;

    int sIdx = 0;                            // Start index for preorder array
    return makeBst(preorder, sIdx, INT_MAX); // Use INT_MAX as upper bound for the root
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
