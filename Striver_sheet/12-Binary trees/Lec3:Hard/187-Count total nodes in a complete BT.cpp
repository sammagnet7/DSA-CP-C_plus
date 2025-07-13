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

1. Title: Count total nodes in a complete BT

Links:
https://takeuforward.org/binary-tree/count-number-of-nodes-in-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/count-total-nodes-in-a-complete-bt?tab=editorial
https://leetcode.com/problems/count-complete-tree-nodes/


Problem statement:
Given the root of a complete binary tree, return the number of the nodes in the tree.
According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
Design an algorithm that runs in less than O(n) time complexity.

Example 1:
Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1


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
  // 1. Title: Count total nodes in a complete BT
  //-------------------------------------------------------------------------------

  // O(log n)
  int leftBorderHeight(TreeNode *node)
  {
    int count = 0;
    while (node)
    {
      count++;
      node = node->left;
    }
    return count;
  }

  // O(log n)
  int rightBorderHeight(TreeNode *node)
  {
    int count = 0;
    while (node)
    {
      count++;
      node = node->right;
    }
    return count;
  }

  // Optimal approach:
  // If the heights of the left and right borders are equal => last level is filled.
  // If they differ => recursive approach is used to calculate left,right subtrees=>sum
  //
  //  Time: O( (Log N)^2 )
  //  Space: O(Log N)
  int countNodes(TreeNode *root)
  {

    if (root == NULL)
      return 0;

    int lBH = leftBorderHeight(root);
    int rBH = rightBorderHeight(root);

    if (lBH == rBH)
    {
      return ((1 << lBH) - 1); // Note
    }
    else
    {
      return (countNodes(root->left) + 1 + countNodes(root->right));
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
