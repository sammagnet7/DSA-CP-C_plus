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

             (8)
            /   \
          (5)   (10)
          / \      \
        (1) (7)    (12)

  Output: [8,5,10,1,7,null,12]

Example 2:
  Input: preorder = [1,3]
  Output: [1,null,3]


Constraints:
  1 <= preorder.length <= 100
  1 <= preorder[i] <= 1000
  All the values of preorder are unique.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

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
// 1. Title: Construct a BST from a preorder traversal
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * BST ALGORITHM: CONSTRUCT BST FROM PREORDER (BOUNDING BOX APPROACH)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * Preorder traversal follows the sequence: Root -> Left -> Right.
 * We can reconstruct the tree in O(N) time by passing down limits and consuming
 * the array sequentially using a globally tracked index (`idx`).
 * * * [THE LOWER LIMIT REDUNDANCY (IMPORTANT INTERVIEW NOTE)]
 * While this code uses both a `lowerLimit` and an `upperLimit`, in a sequential
 * Preorder construction, the `lowerLimit` is strictly redundant.
 * Why? Because we process the array left-to-right. Any value small enough to
 * violate a `lowerLimit` would have ALREADY been swallowed up by the recursive
 * calls building the left subtrees! By the time we attempt to build a right
 * subtree, the only thing we need to check is if the current value exceeds
 * the `upperLimit`. If it does, we know it belongs to a different branch
 * higher up the tree.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * We visit each element in the preorder array exactly once.
 * - SPACE COMPLEXITY: O(H)
 * The recursive call stack uses memory proportional to the height of the tree.
 * ============================================================================
 */
class Solution
{
private:
  TreeNode *recBstFromPre(vector<int> &preorder, int lowerLimit, int upperLimit, int &idx)
  {

    // Base Case: We have consumed every element in the array
    if (idx == preorder.size())
    {
      return nullptr;
    }

    // Check if the current element fits within our valid bounding box for this subtree.
    // NOTE: The `lowerLimit <= preorder[idx]` check here is mathematically redundant
    // for the reasons explained in the class header.
    if (lowerLimit <= preorder[idx] && preorder[idx] <= upperLimit)
    {

      // The element is valid! Create the node and advance the array index.
      TreeNode *cur = new TreeNode(preorder[idx]);
      ++idx;

      // Build the left subtree.
      // The current node's value becomes the new strict upper limit.
      // (NOTE: Passing `lowerLimit` down here is redundant).
      cur->left = recBstFromPre(preorder, lowerLimit, cur->val, idx);

      // Build the right subtree.
      // The current node's value becomes the new strict lower limit.
      // (NOTE: Passing `cur->val` as the new lower limit is redundant).
      cur->right = recBstFromPre(preorder, cur->val, upperLimit, idx);

      return cur;
    }
    else
    {
      // The element violates the bounds. It does not belong in this subtree.
      // Return nullptr so the recursion unwinds back up the tree.
      return nullptr;
    }
  }

public:
  TreeNode *bstFromPreorder(vector<int> &preorder)
  {

    // Pass the index by reference so it acts as a continuous conveyor belt
    // across all recursive calls.
    int idx = 0;

    // Start the root node with the absolute widest possible integer range
    return recBstFromPre(preorder, INT_MIN, INT_MAX, idx);
  }
};

//-----------------------------------------------------------------------------------
// 2. Title: Build BST from Post order  [Same: Just traverse from end to start index]
//-----------------------------------------------------------------------------------
class Solution
{
public:
  TreeNode *recBstFromPost(const vector<int> &post, int &idx, int lowLimit)
  {
    if (idx < 0)
      return nullptr;

    // If current value is < lowLimit then it does not belong here
    if (post[idx] < lowLimit)
      return nullptr;

    TreeNode *cur = new TreeNode(post[idx]);
    --idx;

    // IMPORTANT: process right subtree first (because we're going backwards)
    cur->right = recBstFromPost(post, idx, cur->val);
    cur->left = recBstFromPost(post, idx, lowLimit);

    return cur;
  }

  TreeNode *bstFromPostorder(const vector<int> &post)
  {
    int idx = (int)post.size() - 1;
    return recBstFromPost(post, idx, INT_MIN);
  }
};

int main()
{
  return 0;
}
