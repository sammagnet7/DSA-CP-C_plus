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

1. Title: All Nodes Distance K in Binary Tree

Links:
https://takeuforward.org/plus/dsa/problems/print-all-nodes-at-a-distance-of-k-in-bt?tab=editorial
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/


Problem statement:
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
You can return the answer in any order.

Examples:
  Example 1:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2

           (3)
          /   \
        (5)   (1)
       /  \   / \
     (6)  (2)(0)(8)
          / \
        (7) (4)

  Output: [7,4,1]
  Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

  Example 2:
  Input: root = [1], target = 1, k = 3
  Output: []

Constraints:
  The number of nodes in the tree is in the range [1, 500].
  0 <= Node.val <= 500
  All the values Node.val are unique.
  target is the value of one of the nodes in the tree.
  0 <= k <= 1000


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
 * TREE ALGORITHM: ALL NODES DISTANCE K (GRAPH CONVERSION + BFS)
 * ============================================================================
 * * [THE MENTAL MODEL: "THE POND RIPPLE"]
 * Standard binary trees are one-way streets (you can only go down). To find
 * nodes at distance K, we must be able to go UP as well.
 *
 * Phase 1: We convert the tree into an Undirected Graph by mapping every
 *          child to its parent using a Hash Map.
 * Phase 2: We drop a "stone" at the target node and let a Breadth-First Search
 *          (BFS) ripple outward in all three directions (Left, Right, Up).
 *          The K-th ripple contains our answer.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> Phase 1 visits every node once. Phase 2 (BFS) visits every
 *               node at most once.
 * Space: O(N) -> The parent map, visited set, and BFS queue all scale
 *                linearly with the number of nodes in the tree.
 * ============================================================================
 */
class Solution
{
  // Global map for the instance to store [Child -> Parent] relationships
  unordered_map<TreeNode *, TreeNode *> parentMap;

private:
  /**
   * @brief Phase 1: DFS to map every node to its parent.
   * Note: Uses guarded checks (if node->left) before recursing to save
   * unnecessary stack frames.
   */
  void buildParentMap(TreeNode *node)
  {
    if (!node)
    {
      return;
    }

    if (node->left)
    {
      parentMap[node->left] = node;
      buildParentMap(node->left);
    }

    if (node->right)
    {
      parentMap[node->right] = node;
      buildParentMap(node->right);
    }
  }

public:
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
  {
    vector<int> ans;

    // Base case: Safety check
    if (!root)
    {
      return ans;
    }

    // Phase 1: Build the graph connections (Upward pointers)
    buildParentMap(root);

    // Phase 2: BFS outward from the target node
    queue<TreeNode *> q;
    unordered_set<TreeNode *> visited; // Crucial to prevent Parent <-> Child infinite loops

    q.push(target);
    visited.insert(target);

    // Start at -1 because we pre-increment `dist` at the start of the outer while loop.
    // When the queue processes the target node, dist will correctly become 0.
    int dist = -1;

    while (!q.empty())
    {

      // Snapshot the current ripple (level) size
      int qSize = q.size();
      ++dist;

      // Process the entire ripple boundary
      while (qSize--)
      {
        TreeNode *cur = q.front();
        q.pop();

        // HARVESTING PHASE
        // If we reached the target distance, collect the node.
        // Notice there is no `else if` for children here. This means
        // we stop queuing new nodes, allowing the queue to naturally
        // empty and terminate the outer while loop!
        if (dist == k)
        {
          ans.push_back(cur->val);
        }
        // EXPANSION PHASE
        // We haven't reached K yet, keep expanding the ripple.
        else
        {
          // 1. Expand Down-Left
          if (cur->left && visited.find(cur->left) == visited.end())
          {
            q.push(cur->left);
            visited.insert(cur->left);
          }

          // 2. Expand Down-Right
          if (cur->right && visited.find(cur->right) == visited.end())
          {
            q.push(cur->right);
            visited.insert(cur->right);
          }

          // 3. Expand UP (Using our graph parent map)
          if (parentMap.find(cur) != parentMap.end() && visited.find(parentMap[cur]) == visited.end())
          {
            q.push(parentMap[cur]);
            visited.insert(parentMap[cur]);
          }
        }
      }
    }

    return ans;
  }
};

int main()
{
  return 0;
}
