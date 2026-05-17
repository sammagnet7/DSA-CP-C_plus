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

1. Title: Zig Zag or Spiral Traversal

Links:
https://takeuforward.org/data-structure/zig-zag-traversal-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/zig-zag-or-spiral-traversal?tab=editorial
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/


Problem statement:
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

Examples:
  Example 1:
  Input: root = [3,9,20,null,null,15,7]
  Output: [[3],[20,9],[15,7]]

  Example 2:
  Input: root = [1]
  Output: [[1]]

  Example 3:
  Input: root = []
  Output: []

Constraints:
  The number of nodes in the tree is in the range [0, 2000].
  -100 <= Node.val <= 100


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
// 1. Title: Zig Zag or Spiral Traversal
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: BREADTH-FIRST SEARCH (ZIGZAG LEVEL ORDER)
 * ============================================================================
 * * [THE INTUITION]
 * We process the tree level by level using a Queue (BFS).
 * To achieve the zigzag effect, we decouple the TRAVERSAL order from the
 * STORAGE order.
 * - Traversal: Always Left to Right (push left child, then right child).
 * - Storage: Controlled by a boolean flag `leftToRight`. If false, we populate
 *   our level array from the back to the front.
 *
 * * [THE MECHANICS]
 * By capturing `q.size()` at the start of the while loop, we isolate exactly
 * which nodes belong to the current depth level. We pre-allocate a vector for
 * this level and use a calculated index `(leftToRight ? i : size - 1 - i)`
 * to instantly place the node value in its correct zigzag position.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N) -> Every node is pushed and popped exactly once.
 * - Space Complexity: O(W) -> Where W is the max width of the tree. The queue
 *   holds at most N/2 nodes (the bottom level of a perfectly balanced tree).
 * ============================================================================
 */
class Solution
{
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root)
  {
    vector<vector<int>> ans;

    // Edge case: Empty tree
    if (!root)
    {
      return ans;
    }

    queue<TreeNode *> q;
    q.push(root);

    // Flag to dictate storage direction for the current level
    bool leftToRight = true;

    while (!q.empty())
    {
      int size = q.size();

      // Pre-allocate the vector to the exact size of the current level
      vector<int> currentLevel(size);

      for (int i = 0; i < size; ++i)
      {
        TreeNode *node = q.front();
        q.pop();

        // Determine the correct index based on the zigzag flag
        int index = leftToRight ? i : (size - 1 - i);
        currentLevel[index] = node->val;

        // Queue up the next level (ALWAYS left child first, then right)
        if (node->left)
        {
          q.push(node->left);
        }
        if (node->right)
        {
          q.push(node->right);
        }
      }

      // Flip the flag for the next depth level
      leftToRight = !leftToRight;

      ans.push_back(currentLevel);
    }

    return ans;
  }
};

// =========================
// Approach 2: use Dequeue
// =========================

/*
    // Inside the while loop...
    deque<int> lvl; // Using a deque instead of a vector

    for(int i = 0; i < size; i++) {
        TreeNode* cur = q.front(); q.pop();

        if (turn) {
            lvl.push_back(cur->val);  // O(1) insert at the end
        } else {
            lvl.push_front(cur->val); // O(1) insert at the beginning (reversing it!)
        }
        // ... push children left and right to standard queue ...
    }
    ans.push_back(vector<int>(lvl.begin(), lvl.end()));
*/

int main()
{
  return 0;
}
