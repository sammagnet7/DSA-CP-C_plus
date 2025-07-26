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

1. Title: Lowest Common Ancestor in BST

Links:
https://takeuforward.org/plus/dsa/problems/lca-in-bst?tab=editorial
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/


Problem statement:
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”


Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [2,1], p = 2, q = 1
Output: 2


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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Lowest Common Ancestor in BST
  //-------------------------------------------------------------------------------
  /**
   * Function: lowestCommonAncestor
   * ------------------------------
   * Finds the Lowest Common Ancestor (LCA) of two given nodes `p` and `q` in a Binary Search Tree (BST).
   *
   * Approach:
   * - Utilizes the properties of BST:
   *     - All values in the left subtree are less than the node's value.
   *     - All values in the right subtree are greater than the node's value.
   * - The first node where `p` and `q` diverge (i.e., one is on the left, the other is on the right,
   *   or one is equal to the current node) is their LCA.
   *
   * Steps:
   * - If both `p` and `q` are less than the root, recurse left.
   * - If both `p` and `q` are greater than the root, recurse right.
   * - If the current node is between the values of `p` and `q` (inclusive), return current node as LCA.
   *
   * Time Complexity: O(H), where H is the height of the BST (O(log N) for balanced BST, O(N) for skewed).
   * Space Complexity: O(H) due to recursion stack.
   *
   * Parameters:
   * - root: Pointer to the root of the BST.
   * - p, q: Pointers to the two nodes for which the LCA is to be found.
   *
   * Returns:
   * - Pointer to the Lowest Common Ancestor node.
   */
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {
    if (root == NULL)
      return root;

    // Both p and q are smaller than current node → LCA must be in the left subtree
    if (p->val < root->val && q->val < root->val)
    {
      return lowestCommonAncestor(root->left, p, q);
    }
    // Both p and q are greater than current node → LCA must be in the right subtree
    else if (p->val > root->val && q->val > root->val)
    {
      return lowestCommonAncestor(root->right, p, q);
    }
    // Current node is the split point where p and q diverge → this is the LCA
    else
    {
      return root;
    }
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
