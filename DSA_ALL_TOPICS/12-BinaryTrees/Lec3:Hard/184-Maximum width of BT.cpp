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

1. Title: Maximum Width of BT

Links:
https://takeuforward.org/data-structure/maximum-width-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/maximum-width-of-bt?tab=editorial
https://leetcode.com/problems/maximum-width-of-binary-tree/


Problem statement:
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed integer.


Examples:
  Example 1:
  Input: root = [1,3,2,5,3,null,9]

            1
          /   \
        3       2
      / \       \
      5   3       9

  Output: 4
  Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

  Example 2:
  Input: root = [1,3,2,5,null,null,9,6,null,7]

            1
          /   \
        3       2
      /         \
      5           9
    /           /
    6           7

  Output: 7
  Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

  Example 3:
  Input: root = [1,3,2,5]

              1
            /   \
          3       2
        /
        5

  Output: 2
  Explanation: The maximum width exists in the second level with length 2 (3,2).


Constraints:
The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100


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
// 1. Title: Maximum Width of BT
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: MAXIMUM WIDTH OF BINARY TREE (OPTIMIZED INDEXING)
 * ============================================================================
 * * [THE INTUITION]
 * We use a Level-Order BFS and assign heap-style indices to the nodes.
 * The width of any level is `Rightmost_Index - Leftmost_Index + 1`.
 *
 * * [THE MECHANICS]
 * To completely avoid integer overflow on deeply skewed trees, we normalize
 * the indices. The very first node of every level acts as the "zero point"
 * (`lIdx`). Every other node on that level has its index calculated relative
 * to that zero point (`normIdx`).
 * ============================================================================
 */

using ll = long long;
using P = pair<TreeNode *, ll>;

class Solution
{
public:
  int widthOfBinaryTree(TreeNode *root)
  {
    queue<P> q;

    if (root)
    {
      q.push({root, 0});
    }

    int maxWidth = 0;

    while (!q.empty())
    {
      int qSize = q.size();

      int lIdx = 0;
      int rIdx = 0;

      for (int i = 0; i < qSize; ++i)
      {

        // Safely unpack by value
        auto [cur, idx] = q.front();
        q.pop();

        if (i == 0)
        {
          lIdx = idx;
        }
        if (i == qSize - 1)
        {
          rIdx = idx;
        }

        // Normalize index: the first node of every level becomes 0
        ll normIdx = idx - lIdx;

        if (cur->left)
        {
          q.push({cur->left, 2 * normIdx + 1});
        }

        if (cur->right)
        {
          q.push({cur->right, 2 * normIdx + 2});
        }
      }

      // Width is calculated based on the absolute indices of the level bounds.
      // Cast to int is safe because the problem limits width to 32-bit.
      maxWidth = max(maxWidth, (int)(rIdx - lIdx + 1));
    }

    return maxWidth;
  }
};

int main()
{
  return 0;
}
