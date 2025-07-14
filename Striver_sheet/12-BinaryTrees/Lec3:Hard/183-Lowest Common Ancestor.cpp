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

1. Title: Lowest Common Ancestor

Links:
https://takeuforward.org/data-structure/lowest-common-ancestor-for-two-given-nodes/
https://takeuforward.org/plus/dsa/problems/lca-in-bt?tab=editorial
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/


Problem statement:
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Examples:
  Example 1:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
  Output: 3
  Explanation: The LCA of nodes 5 and 1 is 3.

  Example 2:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
  Output: 5
  Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

  Example 3:
  Input: root = [1,2], p = 1, q = 2
  Output: 1
 
Constraints:
  The number of nodes in the tree is in the range [2, 105].
  -109 <= Node.val <= 109
  All Node.val are unique.
  p != q
  p and q will exist in the tree.


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
  // 1. Title: Lowest Common Ancestor
  //-------------------------------------------------------------------------------
  // Approach1: check the other approach i.e. simpler

  // // O(N)
  // TreeNode *traverse(TreeNode *node, int pVal, int qVal, unordered_map<int, int> &mp, int seen)
  // {

  //   if (node->val == pVal || node->val == qVal)
  //   {
  //     seen++;
  //     mp[node->val]++;
  //   }

  //   if (mp[node->val] == 2)
  //     return node;

  //   if (seen == 2)
  //     return NULL;

  //   TreeNode *tmp = NULL;

  //   if (node->left != NULL)
  //   {
  //     tmp = traverse(node->left, pVal, qVal, mp, seen);
  //     mp[node->val] += mp[node->left->val];
  //   }

  //   if (tmp != NULL)
  //   {
  //     return tmp;
  //   }
  //   if (mp[node->val] == 2)
  //     return node;

  //   if (node->right != NULL)
  //   {
  //     tmp = traverse(node->right, pVal, qVal, mp, seen);
  //     mp[node->val] += mp[node->right->val];
  //   }

  //   if (tmp != NULL)
  //   {
  //     return tmp;
  //   }
  //   if (mp[node->val] == 2)
  //     return node;
  //   else
  //     return NULL;
  // }

  // //
  // //
  // // Time: O(N)
  // // Space: O(N)
  // TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  // {
  //   if (root == NULL)
  //     return NULL;

  //   unordered_map<int, int> mp;
  //   int seen = 0;

  //   return traverse(root, p->val, q->val, mp, seen);
  // }

  //---------------------------
  // Approach2: Optimal

  // Optimal approach:
  //
  // Time: O(N)
  // Space: O(h) i.e. for auxiliary stack space
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {

    if (root == NULL || root->val == p->val || root->val == q->val)
    { // If find any match then no need to go deeper
      // because deeper match's lca will be cur node only
      return root;
    }

    TreeNode *left = NULL;
    TreeNode *right = NULL;

    if (root->left != NULL)
    {
      left = lowestCommonAncestor(root->left, p, q);
    }

    if (root->right != NULL)
    {
      right = lowestCommonAncestor(root->right, p, q);
    }

    if (left != NULL && right != NULL)
    { // This means two values reside in left and right subtree each, so cur is lca
      return root;
    }
    else if (left != NULL) // if coming from one hand only, then that is the most possible alternative, so return that
      return left;
    else
      return right;
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
