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

1. Title: Search in a Binary Search Tree

Links:
https://takeuforward.org/data-structure/search-in-a-binary-search-tree-2/
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/search-in-bst
https://leetcode.com/problems/search-in-a-binary-search-tree/description/


Problem statement:
You are given the root of a binary search tree (BST) and an integer val.
Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

Examples:
  Example 1:
  Input: root = [4,2,7,1,3], val = 2
  Output: [2,1,3]

  Example 2:
  Input: root = [4,2,7,1,3], val = 5
  Output: []

Constraints:
  The number of nodes in the tree is in the range [1, 5000].
  1 <= Node.val <= 107
  root is a binary search tree.
  1 <= val <= 107


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Min/Max in BST

Links:
https://www.naukri.com/code360/problems/minimum-element-in-bst_8160462?leftPanelTabValue=PROBLEM

Problem statement:
You are given a Binary Search Tree.
Find the minimum value in it.

Note:
All the values in the given binary search tree are unique.

Examples:
  Input : 6 4 7 2 5 N N
  Output: 2
  Explanation:
  For the given input BST is:

        6
      / \
    4    7
    / \
  2   5
  Minimum value in this tree is ‘2’.


  Sample Input 1:
  8 5 N 3 6
  Sample Output 1:
  3

  Explanation of sample output 1:
  BST for the given input looks like following:
      8
    /
    5
  / \
  3   6
  Thus the minimum value in this BST is ‘3’.

  Sample Input 2:
  5 3 6 2 4 N N
  Sample Output 2:
  2

Expected Time Complexity:
Try to do this in O(n), where 'n' is the number of nodes in the binary search tree.

Constraints:
0 <= ‘n’ <= 10^5
Time Limit: 1 sec

Where 'n' is the number of nodes in the binary tree.

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
  // 1. Title: Search in a Binary Search Tree
  //-------------------------------------------------------------------------------

  TreeNode *searchBST(TreeNode *root, int val)
  {
    if (root == NULL)
      return NULL;
    if (root->val == val)
      return root;
    else if (root->val > val)
      return searchBST(root->left, val);
    else if (root->val < val)
      return searchBST(root->right, val);

    return NULL;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Min/Max in BST
  //-------------------------------------------------------------------------------
  int minVal(TreeNodeN<int> *root)
  {
    // Write your code here.

    if (root == NULL)
      return -1;

    while (root->left)
    {
      root = root->left;
    }

    return root->data;
  }
};

int main()
{
  return 0;
}
