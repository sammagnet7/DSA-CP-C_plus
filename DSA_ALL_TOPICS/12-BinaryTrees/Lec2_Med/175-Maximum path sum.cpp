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

1. Title: Maximum path sum

Links:
https://takeuforward.org/data-structure/maximum-sum-path-in-binary-tree/
https://takeuforward.org/plus/dsa/problems/zig-zag-or-spiral-traversal?tab=editorial
https://leetcode.com/problems/binary-tree-maximum-path-sum/description/


Problem statement:
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

Examples:
  Example 1:
  Input: root = [1,2,3]
  Output: 6
  Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

  Example 2:
  Input: root = [-10,9,20,null,null,15,7]
  Output: 42
  Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.

Constraints:
  The number of nodes in the tree is in the range [1, 3 * 104].
  -1000 <= Node.val <= 1000

  
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

//-------------------------------------------------------------------------------
// 1. Title: Maximum path sum
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: BOTTOM-UP EXPLICIT STATE DP (MAX PATH SUM)
 * ============================================================================
 * * [THE INTUITION]
 * At any given node in a binary tree, a valid path can take exactly one of
 * four combinatorial states:
 * 1. The node by itself (severing ties with both children).
 * 2. The node + the best path extending down its Left child. -> /
 * 3. The node + the best path extending down its Right child -> \
 * 4. The node acting as a "Peak" connecting the Left and Right paths together -> ⌒
 *
 * By explicitly calculating these 4 states at every node during a Post-Order
 * traversal, we guarantee that we evaluate every possible valid path in the tree.
 *
 * * [THE MECHANICS]
 * We separate what the node *calculates* (the 4 states used to update the global max)
 * from what it *returns* to its parent. A node cannot return a branching path
 * (State 4) to its parent, so it strictly returns a "straight line" downwards.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N) -> Every node is visited exactly once.
 * - Space Complexity: O(H) -> Recursion call stack depth. O(log N) average, O(N) worst.
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Computes the maximum "straight line" path extending downwards from
   *        the current node, while updating the global maximum path found so far.
   *
   * @param node   The current node we are evaluating.
   * @param maxSum Passed by reference to safely track the global max across all recursive frames.
   * @return int   The max sum of a non-branching path to pass up to the parent.
   */
  int rec_sum(TreeNode *node, int &maxSum)
  {
    // Base Case: Null nodes contribute 0 to the path sum.
    if (!node)
    {
      return 0;
    }

    // POST-ORDER: Ask children for their max straight-line paths first.
    int leftSum = rec_sum(node->left, maxSum);
    int rightSum = rec_sum(node->right, maxSum);
    int cur = node->val;

    // 1. UPDATE GLOBAL MAX (Evaluate all 4 combinatorial states)
    // State 1: cur
    // State 2 & 3: cur + max(leftSum, rightSum)  -> / or \
    // State 4: cur + leftSum + rightSum ->  ⌒
    maxSum = max({maxSum,
                  cur,
                  (cur + max(leftSum, rightSum)),
                  (cur + leftSum + rightSum)});

    // 2. RETURN STRAIGHT LINE TO PARENT -> / or \
    // We can only pass a continuous, non-forking line upwards.
    // Therefore, we return either the node by itself, or the node + its best child.
    // (This naturally prunes negative branches because if `cur + max(left, right)`
    // is worse than just `cur`, the `max` function safely drops the children!)
    return max({cur,
                (cur + max(leftSum, rightSum))});
  }

public:
  int maxPathSum(TreeNode *root)
  {
    // Initialize to INT_MIN. This safely handles edge cases where the
    // entire tree consists of strictly negative numbers.
    int maxSum = INT_MIN;

    if (!root)
    {
      return 0;
    }

    rec_sum(root, maxSum);

    return maxSum;
  }
};

int main()
{
  return 0;
}
