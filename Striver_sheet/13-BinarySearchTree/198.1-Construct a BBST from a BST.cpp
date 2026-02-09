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

1. Title: Balance a Binary Search Tree

Links:
https://leetcode.com/problems/balance-a-binary-search-tree/description/


Problem statement:
Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.



Example 1:
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:
Input: root = [2,1,3]
Output: [2,1,3]


Constraints:
The number of nodes in the tree is in the range [1, 104].
1 <= Node.val <= 105

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
  /**
   * Helper Function: Inorder Traversal
   * ----------------------------------
   * Purpose: Extracts values from the BST in sorted order.
   * Idea: Inorder traversal (Left -> Root -> Right) of ANY Binary Search Tree
   * always yields elements in non-decreasing sorted order.
   * * @param node Current node being traversed.
   * @param arr  Reference to the vector where values will be stored.
   */
  void inorder(TreeNode *node, vector<int> &arr)
  {
    // Base case: If node is null, return to previous caller
    if (!node)
    {
      return;
    }

    // 1. Visit Left Subtree
    inorder(node->left, arr);

    // 2. Visit Root (Store value)
    arr.push_back(node->val);

    // 3. Visit Right Subtree
    inorder(node->right, arr);
  }

  /**
   * Helper Function: Build Balanced BST
   * -----------------------------------
   * Purpose: Recursively constructs a height-balanced BST from a sorted array.
   * Idea: To ensure balance, we pick the middle element of the current range
   * to be the root. This ensures roughly equal number of nodes on left and right.
   * * @param arr The sorted vector of values.
   * @param l   Left boundary index of the current range.
   * @param r   Right boundary index of the current range.
   * @return    Pointer to the newly created subtree root.
   */
  TreeNode *buildBBST(vector<int> &arr, int l, int r)
  {

    // Base case: If left index exceeds right, the range is empty (leaf's child)
    if (l > r)
    {
      return nullptr;
    }

    // Find the middle element to be the root.
    // Using l + (r-l)/2 avoids integer overflow for very large indices.
    int mid = l + (r - l) / 2;

    // Create the root node for this subtree
    TreeNode *node = new TreeNode(arr[mid]);

    // Recursively build the left subtree using the left half of the range
    node->left = buildBBST(arr, l, mid - 1);

    // Recursively build the right subtree using the right half of the range
    node->right = buildBBST(arr, mid + 1, r);

    return node;
  }

  /**
   * Main Function: Balance BST
   * --------------------------
   * Approach:
   * 1. Traverse the input BST to get a sorted list of values.
   * 2. Construct a new balanced BST from that sorted list.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * - Inorder traversal visits every node once: O(N).
   * - Building the tree visits every element once: O(N).
   * - Space Complexity: O(N)
   * - O(N) to store the 'sorted' vector.
   * - O(log N) stack space for recursion (in the new balanced tree).
   */
  TreeNode *balanceBST(TreeNode *root)
  {

    // Step 1: Create a sorted array from the tree
    vector<int> sorted;
    inorder(root, sorted);

    // Step 2: Rebuild the tree from the sorted array
    // We pass the full range of indices [0, size-1]
    TreeNode *newRoot = buildBBST(sorted, 0, sorted.size() - 1);

    return newRoot;
  }
};

int main()
{
  return 0;
}
