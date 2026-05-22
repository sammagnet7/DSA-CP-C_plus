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

1. Title: Check for symmetrical BTs

Links:
https://takeuforward.org/data-structure/check-for-symmetrical-binary-tree/
https://takeuforward.org/plus/dsa/problems/check-for-symmetrical-bts?tab=editorial
https://leetcode.com/problems/symmetric-tree/description/


Problem statement:
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Examples:
  Example 1:
  Input: root = [1,2,2,3,4,4,3]

               1
            /     \
           /   |   \
          2         2
         / \   |   / \
        /   \     /   \
       3     4 | 4     3

  Output: true

  Example 2:
  Input: root = [1,2,2,null,3,null,3]

           1
        /     \
       2         2
        \         \
         3         3

  Output: false


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

/**
 * ============================================================================
 * TREE ALGORITHM: SYMMETRIC TREE (MIRROR CHECK)
 * ============================================================================
 * * [THE INTUITION]
 * A binary tree is symmetric if its left and right subtrees are mirror images
 * of each other. To be a mirror image, two conditions must be met:
 * 1. The root values of both subtrees must be identical.
 * 2. The OUTER branches must be mirrors (Left's Left == Right's Right).
 * 3. The INNER branches must be mirrors (Left's Right == Right's Left).
 *
 * * [THE MECHANICS]
 * We use a simultaneous Pre-Order DFS to traverse down both sides of the tree
 * at the exact same time. The pointers `one` (left side) and `two` (right side)
 * move in opposite directions to verify the mirror property.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> In the worst case (a perfectly symmetric tree), we must visit
 * every single node once to verify symmetry.
 * Space: O(H) -> Where H is the height of the tree. This is the memory used
 * by the recursion call stack. In the worst case, it bounds to O(N).
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Recursively checks if two subtrees are exact mirror images.
   */
  bool checkSymRec(TreeNode *one, TreeNode *two)
  {

    // Base Case 1: Structural Check
    // If at least one of the nodes is NULL, they MUST both be NULL to be symmetric.
    // If one is NULL and the other is a Node, (one == two) evaluates to false.
    if (!one || !two)
      return one == two;

    // Base Case 2: Value Check
    // The nodes exist, but their values break the mirror property.
    if (one->val != two->val)
      return false;

    // Recursive Step 1: Check the OUTER edges
    // (Move 'one' to the far left, and 'two' to the far right)
    if (!checkSymRec(one->left, two->right))
      return false;

    // Recursive Step 2: Check the INNER edges
    // (Move 'one' inward to the right, and 'two' inward to the left)
    if (!checkSymRec(one->right, two->left))
      return false;

    // If no structural or value mismatches were found, these subtrees are symmetric
    return true;
  }

public:
  bool isSymmetric(TreeNode *root)
  {
    // An empty tree is perfectly symmetric
    if (!root)
      return true;

    // Split the tree down the middle and begin the simultaneous mirror traversal
    return checkSymRec(root->left, root->right);
  }
};

int main()
{
  return 0;
}
