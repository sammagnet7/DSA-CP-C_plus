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

/**
 * ============================================================================
 * BST ALGORITHM: BALANCE A BINARY SEARCH TREE
 * ============================================================================
 * * [THE MENTAL MODEL]
 * 1. Unspool: Perform an Inorder Traversal to extract all node pointers
 * into a dynamically sized array. This gives us a perfectly sorted list.
 * 2. Rewind: Recursively pick the exact median of the array (or subarray)
 * to act as the root. Wire the left half of the array to the left pointer,
 * and the right half to the right pointer.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * The Inorder Traversal takes O(N) to visit every node. The Divide and
 * Conquer construction also visits every node exactly once, resulting in
 * an overall O(N) linear time limit.
 * - SPACE COMPLEXITY: O(N)
 * We use an array of size N to hold the pointers to the existing nodes.
 * (Note: There is an advanced algorithm called Day-Stout-Warren (DSW) that
 * can do this in O(1) space using tree rotations, but it is generally
 * considered out-of-scope for a standard 45-minute interview).
 * ============================================================================
 */
class Solution
{
private:
  // Step 1: Extract existing nodes in sorted order
  void inorderFlatten(TreeNode *root, vector<TreeNode *> &sortedNodes)
  {
    if (root == nullptr)
    {
      return;
    }

    inorderFlatten(root->left, sortedNodes);
    sortedNodes.push_back(root); // Store the POINTER, not just the value
    inorderFlatten(root->right, sortedNodes);
  }

  // Step 2: Reconstruct the tree from the median out
  TreeNode *buildBalanced(int left, int right, const vector<TreeNode *> &sortedNodes)
  {

    // Base case: The subarray is empty
    if (left > right)
    {
      return nullptr;
    }

    // Find the exact middle of the current subarray
    int mid = left + (right - left) / 2;

    // Grab the existing node to be our new local root
    TreeNode *currentRoot = sortedNodes[mid];

    // Recursively build and attach the left and right subtrees
    currentRoot->left = buildBalanced(left, mid - 1, sortedNodes);
    currentRoot->right = buildBalanced(mid + 1, right, sortedNodes);

    return currentRoot;
  }

public:
  TreeNode *balanceBST(TreeNode *root)
  {
    vector<TreeNode *> sortedNodes;

    // Unspool the tree
    inorderFlatten(root, sortedNodes);

    // Rewind the tree
    return buildBalanced(0, sortedNodes.size() - 1, sortedNodes);
  }
};

int main()
{
  return 0;
}
