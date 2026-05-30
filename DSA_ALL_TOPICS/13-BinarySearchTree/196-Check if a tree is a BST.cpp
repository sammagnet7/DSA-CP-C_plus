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

1. Title: Check if a tree is a BST or not

Links:
https://takeuforward.org/plus/dsa/problems/check-if-a-tree-is-a-bst-or-not?tab=editorial
https://leetcode.com/problems/validate-binary-search-tree/description/


Problem statement:
Given the root of a binary tree, determine if it is a valid binary search tree (BST).
A valid BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
  Input: root = [2,1,3]

           (2)
          /   \
        (1)   (3)

  Output: true


Example 2:
  Input: root = [5,1,4,null,null,3,6]

             (5)
            /   \
          (1)   (4)
              /   \
            (3)   (6)

  Output: false
  Explanation: The root node's value is 5 but its right child's value is 4.

Constraints:
  The number of nodes in the tree is in the range [1, 10^4].
  -2^31 <= Node.val <= 2^31 - 1


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
// 1. Title: Check if a tree is a BST or not
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * BST ALGORITHM: VALIDATE BINARY SEARCH TREE (TOP-DOWN BOUNDARIES)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * We validate the tree by enforcing a strict (min, max) bounding box on every
 * single node. As we traverse downwards, the boundaries shrink.
 * By using `long long` limits (LONG_MIN, LONG_MAX), we safely bypass the
 * edge case where a valid node contains exactly INT_MAX or INT_MIN.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * We visit every node at most once. The explicit short-circuiting
 * (`if (!checkBSTValidity...)`) ensures we abort early on invalid trees.
 * - SPACE COMPLEXITY: O(H)
 * The recursive call stack uses memory proportional to the height of the tree.
 * ============================================================================
 */
class Solution1
{
private:
  /**
   * Function: checkBSTValidity
   * --------------------------
   * Recursively checks whether the binary tree rooted at `node` is a valid BST.
   *
   * Approach:
   * - Uses range-based validation: Each node must lie in (leftRange, rightRange).
   * - The valid range narrows as we move down the tree.
   */
  bool checkBSTValidity(TreeNode *node, long long leftRange, long long rightRange)
  {

    // Base case: A null node is mathematically valid
    if (node == nullptr)
    {
      return true;
    }

    // The current node's value must be strictly within the exclusive range
    if (node->val <= leftRange || node->val >= rightRange)
    {
      return false;
    }

    // Validate the left subtree (Current node becomes the new maximum limit)
    if (!checkBSTValidity(node->left, leftRange, node->val))
    {
      return false;
    }

    // Validate the right subtree (Current node becomes the new minimum limit)
    if (!checkBSTValidity(node->right, node->val, rightRange))
    {
      return false;
    }

    // If all checks pass, the subtree is valid
    return true;
  }

public:
  bool isValidBST(TreeNode *root)
  {
    // Start the recursive check with the absolute widest possible integer range
    return checkBSTValidity(root, LONG_MIN, LONG_MAX);
  }
};

/**
 * ================================================================================
 * BST ALGORITHM: VALIDATE BINARY SEARCH TREE (BOTTOM-UP POST-ORDER)  [RECOMMENDED]
 * ================================================================================
 * * [THE MENTAL MODEL]
 * Instead of passing strict boundaries down, we bubble subtree boundaries UP.
 * For any given node to be a valid BST root:
 * 1. Its left subtree must be valid, AND its value must be strictly GREATER
 * than the absolute MAXIMUM value hidden anywhere in that left subtree.
 * 2. Its right subtree must be valid, AND its value must be strictly LESS
 * than the absolute MINIMUM value hidden anywhere in that right subtree.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * We visit every node exactly once, processing them from the bottom up.
 * - SPACE COMPLEXITY: O(H)
 * The recursion call stack uses memory proportional to the height of the tree.
 * ============================================================================
 */
// Define an elegant alias for our return type: <isValid, min_in_subtree, max_in_subtree>
using T = tuple<bool, int, int>;

class Solution2
{
private:
  T recCheck(TreeNode *node)
  {

    // Edge Case: Completely empty tree passed as root
    if (!node)
    {
      return {true, INT_MAX, INT_MIN};
    }

    int curMax = node->val;
    int curMin = node->val;

    // Step 1: Validate the left branch and bubble up its extremes
    if (node->left)
    {
      auto [valid, minV, maxV] = recCheck(node->left);

      // Left subtree must be valid AND its biggest value must be < current node
      if (!valid || !(maxV < node->val))
      {
        return {false, -1, -1}; // Subtree bounds don't matter if it's invalid
      }

      // Expand our current minimum boundary to include the left branch
      curMin = min(curMin, minV);
    }

    // Step 2: Validate the right branch and bubble up its extremes
    if (node->right)
    {
      auto [valid, minV, maxV] = recCheck(node->right);

      // Right subtree must be valid AND its smallest value must be > current node
      if (!valid || !(node->val < minV))
      {
        return {false, -1, -1};
      }

      // Expand our current maximum boundary to include the right branch
      curMax = max(curMax, maxV);
    }

    // Step 3: Current node is valid! Bubble our new boundaries up to the parent
    return {true, curMin, curMax};
  }

public:
  bool isValidBST(TreeNode *root)
  {
    // We only care about the boolean validity flag at the very top
    return get<0>(recCheck(root));
  }
};

int main()
{
  return 0;
}
