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

        (1)
       /   \
     (2)   (3)
     / \   /
   (4) (5)(6)

Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1


Constraints:
  The number of nodes in the tree is in the range [0, 5 * 104].
  0 <= Node.val <= 5 * 104
  The tree is guaranteed to be complete.


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
// 1. Title: Count total nodes in a complete BT
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: COUNT COMPLETE TREE NODES (< O(N) OPTIMIZATION)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * A naive traversal (DFS/BFS) counts every single node, taking O(N) time.
 * But this tree is "Complete"—meaning it's perfectly filled from left to right.
 * If we check the extreme left path and the extreme right path of any subtree,
 * and they are the exact same length, that subtree is a "Perfect" Binary Tree.
 * We don't need to count its nodes one by one! We can just use the mathematical
 * formula: Nodes = (2^height) - 1.
 *
 * * [APPROACH]
 * 1. At the current node, calculate the height of its extreme left boundary
 *    and extreme right boundary.
 * 2. If Left Height == Right Height, this is a perfectly full triangle.
 *    Instantly return `(2^height) - 1` using bit-shifting `(1 << height) - 1`.
 * 3. If they don't match, the tree is missing some nodes on the bottom right.
 *    We must recursively ask the Left child and Right child for their counts,
 *    and add 1 for the current node.
 *
 * * [TIME COMPLEXITY]
 * O((log N)^2) -> Finding the height takes O(log N) time. In the worst case,
 * we do this at every level of the tree, and there are O(log N) levels.
 * O((log N)^2) is astronomically faster than O(N). For a tree of 50,000 nodes,
 * O(N) takes 50,000 operations, while O((log N)^2) takes roughly 256.
 *
 * * [SPACE COMPLEXITY]
 * O(log N) -> The recursion stack will go as deep as the tree's height.
 * ============================================================================
 */
class Solution
{
private:
  // Recursively calculates the depth strictly down the left edge
  int leftBorderHeight(TreeNode *node)
  {
    if (node->left)
    {
      return 1 + leftBorderHeight(node->left);
    }
    return 1;
  }

  // Recursively calculates the depth strictly down the right edge
  int rightBorderHeight(TreeNode *node)
  {
    if (node->right)
    {
      return 1 + rightBorderHeight(node->right);
    }
    return 1;
  }

public:
  int countNodes(TreeNode *root)
  {
    // Base case: empty tree
    if (!root)
    {
      return 0;
    }

    // Calculate extreme boundary heights
    int lH = leftBorderHeight(root);
    int rH = rightBorderHeight(root);

    // If the left and right boundaries match, it's a Perfect Binary Tree.
    // Use bit-shifting to calculate (2^lH) - 1 in O(1) time.
    if (lH == rH)
    {
      return (1 << lH) - 1;
    }

    // If not perfect, the missing nodes are at the bottom level.
    // Recursively count both subtrees and add 1 for the current root.
    else
    {
      return countNodes(root->left) + 1 + countNodes(root->right);
    }
  }
};

int main()
{
  return 0;
}
