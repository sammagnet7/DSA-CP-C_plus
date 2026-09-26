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

1. Title: Lowest Common Ancestor of Deepest Leaves

Links:
https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/

Duplicate:  https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description


Problem statement:
Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:
The node of a binary tree is a leaf if and only if it has no children.
The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.

Examples:
  Example 1:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4]

                3
              /   \
            5       1
           / |     | \
          6  2     0  8
            / \
           7   4

  Output: [2,7,4]
  Explanation: We return the node with value 2, colored in yellow in the diagram.
  The nodes coloured in blue are the deepest leaf-nodes of the tree.
  Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.

  Example 2:
  Input: root = [1]
  Output: [1]
  Explanation: The root is the deepest node in the tree, and it's the lca of itself.

  Example 3:
  Input: root = [0,1,3,null,2]
  Output: [2]
  Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.


Constraints:
  The number of nodes in the tree will be in the range [1, 1000].
  0 <= Node.val <= 1000
  The values of the nodes in the tree are unique.



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
 * TApproach 1 :: LCA OF DEEPEST LEAVES (TWO-PASS REDUCTION)
 * ============================================================================
 * * [THE INTUITION]
 * Instead of calculating depth and LCA simultaneously, we can break the problem
 * into two distinct, easy-to-manage phases:
 * 1. Find the absolute maximum depth of the tree.
 * 2. Run a standard Lowest Common Ancestor (LCA) search, where our "target"
 *    is ANY node that sits at that maximum depth.
 *
 * * [THE MECHANICS]
 * - Phase 1 is a standard DFS to find tree height.
 * - Phase 2 is our standard Bottom-Up LCA algorithm. If a node discovers it
 *   is at `maxDepth`, it acts as a target and bubbles itself upwards. The
 *   first node to receive a valid target from both left and right is the LCA.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> We traverse the tree exactly twice. Asymptotically still O(N).
 * Space: O(H) -> Where H is the tree height. (Recursion stack memory).
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Phase 1: Calculates the maximum depth of the tree.
   */
  int findDepth(TreeNode *node)
  {
    if (!node)
    {
      return 0;
    }

    int left = 0, right = 0;

    if (node->left)
    {
      left = findDepth(node->left);
    }
    if (node->right)
    {
      right = findDepth(node->right);
    }

    return 1 + max(left, right);
  }

  /**
   * @brief Phase 2: Standard LCA bubbling, targeting nodes at maxDepth.
   * Note: 'curDepth' is passed by value, so we don't need to backtrack it.
   */
  TreeNode *findDeepestLCA(TreeNode *node, int curDepth, int maxDepth)
  {
    if (!node)
      return nullptr;

    // Step down into the current depth level
    ++curDepth;

    // Base Case: We hit our target depth! Bubble this node up.
    if (curDepth == maxDepth)
    {
      return node;
    }

    TreeNode *left = nullptr, *right = nullptr;

    // Send search parties down both branches (Guarded to save stack frames)
    if (node->left)
    {
      left = findDeepestLCA(node->left, curDepth, maxDepth);
    }
    if (node->right)
    {
      right = findDeepestLCA(node->right, curDepth, maxDepth);
    }

    // --- PROCESSING THE RESULTS ---

    // Case 1: Both sides found deepest leaves. This node is the split point!
    if (left && right)
    {
      return node;
    }

    // Case 2 & 3: Only one side found a deepest leaf. Bubble it up.
    if (left)
    {
      return left;
    }
    if (right)
    {
      return right;
    }

    // Case 4: Neither side found anything.
    return nullptr;
  }

public:
  TreeNode *lcaDeepestLeaves(TreeNode *root)
  {
    // Phase 1: Establish the target depth
    int maxDepth = findDepth(root);

    // Phase 2: Find the LCA of all nodes at that target depth
    return findDeepestLCA(root, 0, maxDepth);
  }
};

//--------------------------------------------
// Approach 2 : Single pass [RECOMMENDED]
//-------------------------------------------
class Solution
{
public:
  /**
   * Helper Function: Depth First Search (Post-Order)
   * * Approach:
   * This function traverses the tree bottom-up to find two things simultaneously for every subtree:
   * 1. The Maximum Depth (Height) of that subtree.
   * 2. The 'Candidate Node' (LCA) that roots the smallest subtree containing all deepest nodes found so far.
   * * * Logic:
   * - If left subtree is deeper: The deepest nodes are on the left. The LCA must be in the left child's result.
   * - If right subtree is deeper: The deepest nodes are on the right. The LCA must be in the right child's result.
   * - If depths are EQUAL: This current node is the split point where paths to the deepest nodes diverge.
   * Therefore, THIS node is the new Lowest Common Ancestor.
   * * * Return Pair: {Subtree Height, Candidate Node}
   */
  pair<int, TreeNode *> dfs(TreeNode *root)
  {
    // Base Case: An empty node has height 0 and no LCA.
    if (!root)
    {
      return {0, nullptr};
    }

    // Recursive Step: Get {height, LCA} from left and right children
    pair<int, TreeNode *> left = dfs(root->left);
    pair<int, TreeNode *> right = dfs(root->right);

    int leftHeight = left.first;
    int rightHeight = right.first;

    // Decision Logic
    if (leftHeight == rightHeight)
    {
      // Case 1: Balanced. Deepest nodes exist on both sides.
      // This 'root' is the lowest node connecting them.
      return {leftHeight + 1, root};
    }
    else if (leftHeight > rightHeight)
    {
      // Case 2: Left is deeper.
      // The answer is already determined inside the left subtree. Pass it up.
      return {leftHeight + 1, left.second};
    }
    else
    {
      // Case 3: Right is deeper.
      // The answer is already determined inside the right subtree. Pass it up.
      return {rightHeight + 1, right.second};
    }
  }

  /**
   * Main Function
   * * Problem: Find smallest subtree containing all deepest nodes.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * We visit every node exactly once using a standard DFS traversal.
   * - Space Complexity: O(H) where H is the height of the tree.
   * This is used by the recursion stack. In worst case (skewed tree), O(N).
   */
  TreeNode *lcaDeepestLeaves(TreeNode *root)
  {
    // The second element of the pair is our answer node
    return dfs(root).second;
  }
};

int main()
{
  return 0;
}
