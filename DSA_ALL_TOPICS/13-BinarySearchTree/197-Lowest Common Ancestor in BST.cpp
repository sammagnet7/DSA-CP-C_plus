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

1. Title: Lowest Common Ancestor in BST   [Note: This problem is different from BT LCA]

Links:
https://takeuforward.org/plus/dsa/problems/lca-in-bst?tab=editorial
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/


Problem statement:
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”


Example 1:
  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8

               (6)
              /   \
            (2)   (8)
            / \    / \
          (0) (4)(7) (9)
              / \
            (3) (5)

  Output: 6
  Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4

               (6)
              /   \
            (2)   (8)
            / \    / \
          (0) (4)(7) (9)
              / \
            (3) (5)

  Output: 2
  Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:
  Input: root = [2,1], p = 2, q = 1
  Output: 2

Constraints:
  The number of nodes in the tree is in the range [2, 10^5].
  -10^9 <= Node.val <= 10^9
  All Node.val are unique.
  p != q
  p and q will exist in the BST.


Follow up: Can you do it in less than O(N) Time for BST?


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

//-------------------------------------------------------------------------------
// 1. Title: Lowest Common Ancestor in BST
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * BST ALGORITHM: LOWEST COMMON ANCESTOR (RECURSIVE SPLIT POINT)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * Because of the strict sorting rules of a BST, the Lowest Common Ancestor
 * is simply the first node where the paths to `p` and `q` diverge.
 * 1. If both `p` and `q` are strictly smaller than the current node, they
 * are both in the left subtree. We recurse Left.
 * 2. If both `p` and `q` are strictly larger than the current node, they
 * are both in the right subtree. We recurse Right.
 * 3. Otherwise (one is smaller and one is larger, OR one is exactly equal
 * to the current node), the paths have split! The current node is the LCA.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * We only travel down one single path from the root, discarding half of
 * the remaining tree at every step (in a balanced BST).
 * - SPACE COMPLEXITY: O(H)
 * The recursive call stack uses memory proportional to the height of the tree.
 * ============================================================================
 */
class Solution
{
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {

    // Base case: Fell off the tree (shouldn't happen if p and q are guaranteed to exist)
    if (!root)
    {
      return nullptr;
    }

    // Case 1: Both targets are in the left subtree
    if ((p->val < root->val) && (q->val < root->val))
    {
      return lowestCommonAncestor(root->left, p, q);
    }
    // Case 2: Both targets are in the right subtree
    else if ((root->val < p->val) && (root->val < q->val))
    {
      return lowestCommonAncestor(root->right, p, q);
    }

    // Case 3: We found the split point (or one target equals the root)
    return root;
  }

  /**
   * ============================================================================
   * BST ALGORITHM: LOWEST COMMON ANCESTOR (ITERATIVE SPLIT POINT) [RECOMMENDED]
   * ============================================================================
   * * [THE MENTAL MODEL]
   * We walk down the tree from the root. The LCA is the exact node where the
   * paths to `p` and `q` diverge.
   * - If both values are smaller than the current node, the LCA must be on the left.
   * - If both values are larger, the LCA must be on the right.
   * - Otherwise (one is smaller, one is larger, or one equals the current node),
   * we have found the divergence point! That node is the LCA.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
   * We traverse exactly one path from the root downwards. We stop the moment we
   * find the split point, so we may not even need to reach the leaves.
   * - SPACE COMPLEXITY: O(1)
   * We strictly use a single pointer to traverse downwards. Zero extra memory.
   * ============================================================================
   */
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {

    TreeNode *curr = root;

    while (curr != nullptr)
    {

      // Both p and q are greater than the current node -> Route Right
      if (p->val > curr->val && q->val > curr->val)
      {
        curr = curr->right;
      }
      // Both p and q are less than the current node -> Route Left
      else if (p->val < curr->val && q->val < curr->val)
      {
        curr = curr->left;
      }
      // A split occurs, or one target exactly matches the current node
      else
      {
        return curr;
      }
    }

    // Constraints guarantee p and q exist, so this will never be reached
    return nullptr;
  }
};

int main()
{
  return 0;
}
