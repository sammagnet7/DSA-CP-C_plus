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

1. Title: Correct BST with two nodes swapped

Links:
https://takeuforward.org/plus/dsa/problems/correct-bst-with-two-nodes-swapped?tab=editorial
https://leetcode.com/problems/recover-binary-search-tree/description/


Problem statement:
You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Eamples:
  Example 1:
  Input: root = [1,3,null,null,2]
  Output: [3,1,null,null,2]
  Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
  Example 2:
  Input: root = [3,1,4,null,null,2]
  Output: [2,1,4,null,null,3]
  Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

Constraints:
The number of nodes in the tree is in the range [2, 1000].
-231 <= Node.val <= 231 - 1

Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?


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
// 1. Title: Correct BST with two nodes swapped
//-------------------------------------------------------------------------------
class Solution
{
public:
  /**
   * Recovers a Binary Search Tree (BST) where two nodes are mistakenly swapped.
   *
   * Approach:
   * - Perform an in-order traversal of the tree (which should be sorted for BST).
   * - Keep track of:
   *     - prev: last visited node in inorder
   *     - first: first node where prev > current
   *     - middle: current node when first violation is found
   *     - last: current node if second violation is found later
   * - Swap first <-> last if two violations (non-adjacent swap),
   *   else swap first <-> middle (adjacent swap).
   *
   * Time: O(N)
   * Space: O(H) for recursion (H = height of tree)
   */
  void inorder(TreeNode *node, vector<TreeNode *> &v, bool &done)
  {
    if (node == NULL || done)
      return;

    inorder(node->left, v, done);
    if (done)
      return;

    TreeNode *cur = node;
    TreeNode *prev = v[0]; // v[0] is prev

    // Detect violation in BST inorder property
    if (prev && prev->val > cur->val)
    {
      if (v[1] == NULL)
      {
        // First violation
        v[1] = prev; // first
        v[2] = cur;  // middle
      }
      else if (v[3] == NULL)
      {
        // Second violation
        v[3] = cur;  // last
        done = true; // early exit optimization
        return;
      }
    }

    v[0] = cur; // Update prev
    inorder(node->right, v, done);
  }

  /**
   * Main function to fix the BST.
   *
   * v[0]: prev node
   * v[1]: first node in violation
   * v[2]: middle node for first violation
   * v[3]: last node if second violation occurs
   *
   * Time: O(N)
   * Space: O(H) for recursion (H = height of tree)
   * Note: Here we can use Morris Inorder traversal to get rid of the extra stack space
   */
  void recoverTree(TreeNode *root)
  {
    bool done = false;
    vector<TreeNode *> v(4, NULL); // [0]=prev, [1]=first, [2]=middle, [3]=last

    inorder(root, v, done);

    if (v[3])
    {
      // Non-adjacent swap
      swap(v[1]->val, v[3]->val);
    }
    else if (v[2])
    {
      // Adjacent swap
      swap(v[1]->val, v[2]->val);
    }
  }
};

int main()
{
  return 0;
}
