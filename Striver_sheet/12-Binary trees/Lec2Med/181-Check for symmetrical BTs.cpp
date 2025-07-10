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

1. Title: Check for symmetrical BTs

Links:
https://takeuforward.org/data-structure/check-for-symmetrical-binary-tree/
https://takeuforward.org/plus/dsa/problems/check-for-symmetrical-bts?tab=editorial
https://leetcode.com/problems/symmetric-tree/description/


Problem statement:
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Examples:
  Example 1:
  Input: root = [1,2,2,3,4,4,3]
  Output: true

  Example 2:
  Input: root = [1,2,2,null,3,null,3]
  Output: false


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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Check for symmetrical BTs
  //-------------------------------------------------------------------------------

  // O(N/2)
  bool checkSym(TreeNode *node1, TreeNode *node2)
  {

    if (node1 == NULL || node2 == NULL)
      return (node1 == node2);

    if (node1->val != node2->val)
      return false;

    // Compare opposit hands
    bool isLeftTreeSym = checkSym(node1->left, node2->right);
    bool isRightTreeSym = checkSym(node1->right, node2->left);

    return (isLeftTreeSym & isRightTreeSym);
  }

  //
  // Optimal approach: Using recursion
  // Time: O(N/2)
  // Space: O(h)
  bool isSymmetric(TreeNode *root)
  {
    if (root == NULL)
      return true;

    return checkSym(root->left, root->right);
  }
};

int main()
{
  return 0;
}
