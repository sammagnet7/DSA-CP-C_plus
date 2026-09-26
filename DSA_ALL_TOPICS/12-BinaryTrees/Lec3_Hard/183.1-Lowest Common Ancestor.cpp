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

           (3)
          /   \
        (5)   (1)
       /  \   / \
     (6)  (2)(0)(8)
          / \
        (7) (4)

  Output: 3
  Explanation: The LCA of nodes 5 and 1 is 3.

  Example 2:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4

           (3)
          /   \
        (5)   (1)
       /  \   / \
     (6)  (2)(0)(8)
          / \
        (7) (4)

  Output: 5
  Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

  Example 3:
  Input: root = [1,2], p = 1, q = 2
  Output: 1

Constraints:
  The number of nodes in the tree is in the range [2, 10^5].
  -10^9 <= Node.val <= 10^9
  All Node.val are unique.
  p != q
  p and q will exist in the tree.


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
// 1. Title: Lowest Common Ancestor
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: LOWEST COMMON ANCESTOR (BOTTOM-UP DFS)
 * ============================================================================
 * * [THE INTUITION]
 * We use a Post-Order traversal. We go all the way down to the leaves, and as
 * we return (bubble up), we carry information about whether we found `p` or `q`.
 * The very first node that receives a non-null result from BOTH its left and
 * right children is guaranteed to be the Lowest Common Ancestor.
 *
 * * [THE MECHANICS]
 * - If the current node is `p` or `q`, return the current node immediately.
 * - Search the left subtree.
 * - Search the right subtree.
 * - If both searches return a node, the current node is the LCA.
 * - If only one search returns a node, bubble that node further up the tree.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> In the worst case, we visit every node exactly once.
 * Space: O(H) -> Where H is the tree height, corresponding to the recursion stack.
 * ============================================================================
 */
class Solution
{
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
  {
    // Base case 1: We hit a dead end
    if (!root)
    {
      return nullptr;
    }

    // Base case 2: We found one of our targets!
    // We return it immediately to bubble it up.
    // (If the other target is a descendant of this one, returning this
    // node satisfies the rule: "a node can be a descendant of itself").
    if (root == p || root == q)
    {
      return root;
    }

    // Send a search party down the left and right branches
    TreeNode *leftResult = lowestCommonAncestor(root->left, p, q);
    TreeNode *rightResult = lowestCommonAncestor(root->right, p, q);

    // --- PROCESSING THE RESULTS (BOTTOM-UP) ---

    // Case 1: Both branches found a target. This node is the split point!
    if (leftResult != nullptr && rightResult != nullptr)
    {
      return root;
    }

    // Case 2: Only the left branch found a target. Bubble it up.
    if (leftResult != nullptr)
    {
      return leftResult;
    }

    // Case 3: Only the right branch found a target. Bubble it up.
    // (If both were null, this naturally returns null, handling Case 4).
    return rightResult;
  }
};

int main()
{
  return 0;
}
