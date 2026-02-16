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

1. Title: Two sum in BST

Links:
https://takeuforward.org/plus/dsa/problems/two-sum-in-bst?tab=editorial
https://leetcode.com/problems/two-sum-iv-input-is-a-bst/


Problem statement:
Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

Examples:
  Example 1:
  Input: root = [5,3,6,2,4,null,7], k = 9
  Output: true

  Example 2:
  Input: root = [5,3,6,2,4,null,7], k = 28
  Output: false

Constraints:
  The number of nodes in the tree is in the range [1, 104].
  -104 <= Node.val <= 104
  root is guaranteed to be a valid binary search tree.
  -105 <= k <= 105


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

//-------------------------------------------------------------------------------
// 1. Title: Two sum in BST
//-------------------------------------------------------------------------------

/**
 * Class: BSTIterator
 * -------------------
 * Implements an iterator for in-order or reverse in-order traversal on a BST.
 * It uses a stack to simulate the traversal iteratively.
 *
 * isReverse = false → Normal in-order (ascending)
 * isReverse = true  → Reverse in-order (descending)
 *
 * Time Complexity (next, hasNext): O(1) amortized
 * Space Complexity: O(H), where H is the height of the tree
 */
class BSTIterator
{
public:
  stack<TreeNode *> st; // Stack to simulate recursive traversal
  bool isReverse;       // Flag to determine direction of traversal

  // Constructor for in-order (ascending) traversal
  BSTIterator(TreeNode *root) : isReverse(false)
  {
    while (root)
    {
      st.push(root);
      root = root->left; // Go as left as possible
    }
  }

  // Constructor for general use (in-order or reverse in-order)
  BSTIterator(TreeNode *root, bool rev) : isReverse(rev)
  {
    pushAll(root);
  }

  // Returns the next node in traversal
  int next()
  {
    TreeNode *el = st.top();
    st.pop();
    int ret = el->val;

    // For reverse traversal, go to left subtree
    // For in-order traversal, go to right subtree
    if (isReverse)
    {
      pushAll(el->left);
    }
    else
    {
      pushAll(el->right);
    }

    return ret;
  }

  // Checks if more elements are left in traversal
  bool hasNext()
  {
    return !st.empty();
  }

private:
  /**
   * Utility to push a path of nodes into the stack depending on traversal type.
   * For in-order → go leftwards.
   * For reverse in-order → go rightwards.
   */
  void pushAll(TreeNode *node)
  {
    while (node)
    {
      st.push(node);
      if (isReverse)
        node = node->right;
      else
        node = node->left;
    }
  }
};

/**
 * Method: findTarget
 * -------------------
 * Given a BST and an integer k, determines whether there exists two elements
 * in the BST such that their sum is equal to k.
 *
 * Uses two iterators (one in-order and one reverse in-order) to simulate the
 * two-pointer technique on sorted data.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(H) + O(H) = O(H)  // For both iterators
 */
class Solution
{
public:
  bool findTarget(TreeNode *root, int k)
  {
    if (root == NULL)
      return false;

    // Create two BST iterators
    BSTIterator *forw = new BSTIterator(root);        // In-order
    BSTIterator *backw = new BSTIterator(root, true); // Reverse in-order

    int l = forw->next();  // smallest value
    int r = backw->next(); // largest value

    // Use two-pointer technique to search for target sum
    while (l < r)
    {
      int sum = l + r;
      if (sum == k)
        return true;
      else if (sum > k)
      {
        // Decrease the larger value
        if (backw->hasNext())
          r = backw->next();
        else
          break;
      }
      else
      {
        // Increase the smaller value
        if (forw->hasNext())
          l = forw->next();
        else
          break;
      }
    }

    return false;
  }
};

int main()
{
  return 0;
}
