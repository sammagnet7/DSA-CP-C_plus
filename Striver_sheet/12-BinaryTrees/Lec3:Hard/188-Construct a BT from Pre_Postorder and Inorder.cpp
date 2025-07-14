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

1. Title: Construct a BT from Preorder and Inorder

Links:
https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/
https://takeuforward.org/plus/dsa/problems/construct-a-bt-from-preorder-and-inorder?tab=editorial
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

Problem statement:
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

Examples:
  Example 1:
  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
  Output: [3,9,20,null,null,15,7]

  Example 2:
  Input: preorder = [-1], inorder = [-1]
  Output: [-1]


Constraints:
  1 <= preorder.length <= 3000
  inorder.length == preorder.length
  -3000 <= preorder[i], inorder[i] <= 3000
  preorder and inorder consist of unique values.
  Each value of inorder also appears in preorder.
  preorder is guaranteed to be the preorder traversal of the tree.
  inorder is guaranteed to be the inorder traversal of the tree.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Construct a BT from Postorder and Inorder

Links:
https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/
https://takeuforward.org/plus/dsa/problems/construct-a-bt-from-postorder-and-inorder?tab=editorial
https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/


Problem statement:
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

Examples:
  Example 1:
  Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
  Output: [3,9,20,null,null,15,7]

  Example 2:
  Input: inorder = [-1], postorder = [-1]
  Output: [-1]

Constraints:
  1 <= inorder.length <= 3000
  postorder.length == inorder.length
  -3000 <= inorder[i], postorder[i] <= 3000
  inorder and postorder consist of unique values.
  Each value of postorder also appears in inorder.
  inorder is guaranteed to be the inorder traversal of the tree.
  postorder is guaranteed to be the postorder traversal of the tree.

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
  // 1. Title: Construct a BT from Preorder and Inorder
  //-------------------------------------------------------------------------------

  /**
   * Method: buildFromPreOrder
   * -------------------------
   * Recursively builds the binary tree from preorder and inorder traversal arrays.
   *
   * Approach:
   * - The first element of the preorder list is the root of the current subtree.
   * - Using a map for inorder values, we find the index of the root in inorder array.
   * - This index helps divide the inorder array into left and right subtrees.
   * - Similarly, we compute bounds for the left and right subtrees in preorder array.
   * - Recursive calls build left and right subtrees accordingly.
   *
   * Time Complexity: O(N)
   * - Each node is created exactly once.
   * - Lookup in map is O(1), done N times.
   *
   * Space Complexity: O(N)
   * - Map takes O(N) space.
   * - Recursion stack in worst case (skewed tree) takes O(N) space.
   */
  TreeNode *buildFromPreOrder(vector<int> &preorder, vector<int> &inorder, int pStart, int pEnd, int iStart, int iEnd, unordered_map<int, int> &mp)
  {
    // Base case: no elements to construct subtree
    if (pStart > pEnd || iStart > iEnd)
      return NULL;

    // Root node is the first element in current preorder range
    TreeNode *me = new TreeNode(preorder[pStart]);

    // Find index of root in inorder array
    int in_root_idx = mp[me->val];

    // Count of nodes in left subtree
    int leftNumsCount = in_root_idx - iStart;

    // Recursively build left subtree
    TreeNode *left = buildFromPreOrder(
        preorder, inorder,
        pStart + 1,             // left subtree starts right after root in preorder
        pStart + leftNumsCount, // end of left subtree in preorder
        iStart,                 // left subtree in inorder
        in_root_idx - 1,        // just before root in inorder
        mp);

    // Recursively build right subtree
    TreeNode *right = buildFromPreOrder(
        preorder, inorder,
        pStart + leftNumsCount + 1, // start of right subtree in preorder
        pEnd,                       // end of preorder
        in_root_idx + 1,            // right subtree in inorder starts after root
        iEnd,                       // end of inorder
        mp);

    // Attach left and right subtrees
    me->left = left;
    me->right = right;

    return me;
  }

  /**
   * Method: buildTree
   * -----------------
   * Initiates the tree construction using preorder and inorder traversal arrays.
   *
   * Time Complexity: O(N)
   * - Preprocesses map of inorder indices in O(N).
   * - buildFromPreOrder runs in O(N).
   *
   * Space Complexity: O(N)
   * - Map storage and recursion stack.
   */
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
  {
    int pN = preorder.size();
    int iN = inorder.size();

    // Build map for quick lookup of root index in inorder
    unordered_map<int, int> mp;
    for (int i = 0; i < iN; i++)
    {
      mp[inorder[i]] = i;
    }

    // Start building tree
    return buildFromPreOrder(preorder, inorder, 0, pN - 1, 0, iN - 1, mp);
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Construct a BT from Postorder and Inorder
  //-------------------------------------------------------------------------------

  /**
   * Method: buildFromPostorder
   * --------------------------
   * Recursively builds the binary tree from postorder and inorder traversal arrays.
   *
   * Approach:
   * - In postorder traversal, the last element is the root of the current subtree.
   * - Using a hashmap for inorder, find the index of the root.
   * - The inorder array is split into left and right subtrees using the root index.
   * - Calculate number of nodes in left and right subtree to determine the correct
   *   ranges in postorder array for recursive calls.
   * - Recursively build left and right subtrees.
   *
   * Time Complexity: O(N)
   * - Each node is processed once.
   * - Hash map lookups are O(1).
   *
   * Space Complexity: O(N)
   * - Hash map and recursion stack in the worst case (skewed tree).
   */
  TreeNode *buildFrompostorder(vector<int> &postorder, vector<int> &inorder, int pStart, int pEnd, int iStart, int iEnd, unordered_map<int, int> &mp)
  {

    // Base case: no nodes to construct
    if (pStart > pEnd || iStart > iEnd)
      return NULL;

    // Last element in postorder is the root of current subtree
    TreeNode *me = new TreeNode(postorder[pEnd]);

    // Find root index in inorder array
    int in_root_idx = mp[me->val];

    // Count nodes in left and right subtrees
    int leftNumsCount = in_root_idx - iStart;
    int rightNumsCount = iEnd - in_root_idx;

    // Recursively build left subtree
    TreeNode *left = buildFrompostorder(
        postorder, inorder,
        pStart,                     // start of left subtree in postorder
        pStart + leftNumsCount - 1, // end of left subtree
        iStart,                     // start in inorder
        in_root_idx - 1,            // end in inorder
        mp);

    // Recursively build right subtree
    TreeNode *right = buildFrompostorder(
        postorder, inorder,
        pEnd - rightNumsCount, // start of right subtree in postorder
        pEnd - 1,              // end (before root)
        in_root_idx + 1,       // right subtree in inorder
        iEnd,
        mp);

    // Attach left and right subtrees
    me->left = left;
    me->right = right;

    return me;
  }

  /**
   * Method: buildTree
   * -----------------
   * Initiates tree construction from inorder and postorder traversal arrays.
   *
   * Time Complexity: O(N)
   * - Builds hashmap in O(N)
   * - Recursive build in O(N)
   *
   * Space Complexity: O(N)
   * - Map and recursion stack
   */
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
  {
    int pN = postorder.size();
    int iN = inorder.size();

    // Hash map to quickly find index of root in inorder
    unordered_map<int, int> mp;
    for (int i = 0; i < iN; i++)
    {
      mp[inorder[i]] = i;
    }

    // Start recursive construction
    return buildFrompostorder(postorder, inorder, 0, pN - 1, 0, iN - 1, mp);
  }
};

int main()
{
  return 0;
}
