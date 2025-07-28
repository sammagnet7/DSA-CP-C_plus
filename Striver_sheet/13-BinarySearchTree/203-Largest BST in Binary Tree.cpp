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

1. Title: Largest BST in Binary Tree

Links:
https://takeuforward.org/plus/dsa/problems/largest-bst-in-binary-tree?tab=editorial
https://www.naukri.com/code360/problems/size-of-largest-bst-in-binary-tree_893103


Problem statement:
You have been given a Binary Tree of 'N' nodes, where the nodes have integer values. Your task is to return the size of the largest subtree of the binary tree which is also a BST.

A binary search tree (BST) is a binary tree data structure which has the following properties.

• The left subtree of a node contains only nodes with data less than the node’s data.
• The right subtree of a node contains only nodes with data greater than the node’s data.
• Both the left and right subtrees must also be binary search trees.


Examples:
  Sample Input 1 :
  2 1 3 -1 -1 -1 -1
  Sample Output 1:
  3
  Explanation for Sample 1:
  In the given binary tree, subtree rooted at 2 is a BST and its size is 3.

  Sample Input 2 :
  50 -1 20 -1 30 -1 40 -1 50 -1 -1
  Sample Output 2:
  4

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
// 1. Title: Largest BST in Binary Tree
//-------------------------------------------------------------------------------

// Helper class to store information about each subtree during traversal
class DTO
{
public:
  int minV;  // Minimum value in the subtree
  int maxV;  // Maximum value in the subtree
  int count; // Number of nodes in the largest BST subtree

  DTO()
  {
    minV = INT_MAX; // Initialize to extremes for comparison
    maxV = INT_MIN;
    count = 0;
  }
};

class Solution
{
public:
  /**
   * Recursively traverses the tree in postorder to find the largest BST.
   *
   * Approach:
   * - For each node, check if its left and right subtrees form a BST.
   * - Use postorder traversal so we get data from children first.
   * - If current node satisfies BST property with its left and right, update current min/max/count.
   * - If not, propagate max count from either left or right subtree.
   *
   * Time Complexity: O(N) ? each node is visited once.
   * Space Complexity: O(H) ? due to recursion stack, H = height of tree.
   */
  DTO traverseBST(TreeNodeN<int> *node)
  {
    // Base case: NULL node is a valid BST of size 0
    if (node == NULL)
      return DTO();

    // Postorder traversal: left and right subtrees first
    DTO leftDTO = traverseBST(node->left);
    DTO rightDTO = traverseBST(node->right);

    DTO curr;

    // Check if current subtree rooted at `node` is a BST
    if (leftDTO.maxV < node->data && node->data < rightDTO.minV)
    {
      // Valid BST at this node
      curr.minV = min(leftDTO.minV, node->data);
      curr.maxV = max(rightDTO.maxV, node->data);
      curr.count = leftDTO.count + 1 + rightDTO.count;
    }
    else
    {
      // Not a valid BST, propagate largest BST found so far
      curr.minV = INT_MIN; // Mark invalid
      curr.maxV = INT_MAX;
      curr.count = max(leftDTO.count, rightDTO.count);
    }

    return curr;
  }

  /**
   * Main function to find size of largest BST subtree in a Binary Tree.
   *
   * Time: O(N)
   * Space: O(H) due to recursion stack
   */
  int largestBST(TreeNodeN<int> *root)
  {
    if (root == NULL)
      return 0;

    return traverseBST(root).count;
  }
};

int main()
{
  return 0;
}
