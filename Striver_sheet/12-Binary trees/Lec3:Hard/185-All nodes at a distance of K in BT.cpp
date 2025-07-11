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

1. Title: All nodes at a distance of K in BT

Links:



Problem statement:



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:
https://takeuforward.org/plus/dsa/problems/print-all-nodes-at-a-distance-of-k-in-bt?tab=editorial
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/


Problem statement:
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
You can return the answer in any order.

Examples:
  Example 1:
  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
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

template <typename T = int>
struct TreeNodeN
{
  int data;
  TreeNodeN *left;
  TreeNodeN *right;
  TreeNodeN() : data(0), left(nullptr), right(nullptr) {}
  TreeNodeN(int x) : data(x), left(nullptr), right(nullptr) {}
  TreeNodeN(int x, TreeNodeN *left, TreeNodeN *right) : data(x), left(left), right(right) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: All nodes at a distance of K in BT
  //-------------------------------------------------------------------------------

  // -----------------------------------------------------------------------------
  // Method: createParentMap
  // Purpose: Builds a map that stores the parent of each node in the binary tree.
  //          For each child node, we store the mapping: child → parent.
  //
  // Parameters:
  // - node: current TreeNode* to process.
  // - parentMap: unordered_map to store the mapping from child to parent.
  //
  // Time Complexity: O(N)
  //     - Each node in the tree is visited exactly once.
  // Space Complexity: O(N)
  //     - In the worst case, the map stores N-1 entries (excluding root).
  // -----------------------------------------------------------------------------
  void createParentMap(TreeNode *node, unordered_map<TreeNode *, TreeNode *> &parentMap)
  {
    if (node == NULL)
      return;

    if (node->left)
    {
      parentMap[node->left] = node;           // Store left child's parent
      createParentMap(node->left, parentMap); // Recursively process left subtree
    }

    if (node->right)
    {
      parentMap[node->right] = node;           // Store right child's parent
      createParentMap(node->right, parentMap); // Recursively process right subtree
    }
  }

  // -----------------------------------------------------------------------------
  // Method: traverseKLevelsBelow
  // Purpose: Performs a BFS (level-order traversal) starting from a given node,
  //          and collects all nodes that are exactly K levels below it.
  //
  // Parameters:
  // - node: starting node (TreeNode*) from which distance is measured.
  // - k: the distance/level to search for.
  // - ans: vector<int> to store values of nodes found at distance k.
  //
  // Time Complexity: O(N)
  //     - In the worst case, if k is large, the entire subtree may be traversed.
  //     - But practically, we only traverse nodes up to level k, so the complexity
  //       is proportional to the number of nodes up to that level.
  //
  // Space Complexity: O(W)
  //     - Where W is the maximum width of the tree (nodes in the queue at any level).
  //     - In the worst case (balanced binary tree), W = N/2.
  // -----------------------------------------------------------------------------
  void traverseKLevelsBelow(TreeNode *node, int k, vector<int> &ans)
  {
    queue<TreeNode *> q;
    q.push(node); // Start from given node
    int dist = 0; // Current level from the source node

    while (!q.empty())
    {
      int qSize = q.size(); // Number of nodes in the current level

      // If we've reached the desired level
      if (dist == k)
      {
        for (int i = 0; i < qSize; i++)
        {
          ans.push_back(q.front()->val); // Collect all node values at level k
          q.pop();
        }
        return; // No need to process further levels
      }

      // Traverse all nodes at the current level and enqueue their children
      for (int i = 0; i < qSize; i++)
      {
        auto *tmp = q.front();

        if (tmp->left)
          q.push(tmp->left);

        if (tmp->right)
          q.push(tmp->right);

        q.pop();
      }

      dist++; // Move to the next level
    }
  }

  // -----------------------------------------------------------------------------
  // Method: traverseKLevelsAbove
  // Purpose: Traverses upward from the target node to its ancestors, and for each
  //          ancestor node, performs BFS to find nodes that are at remaining
  //          distance down the subtree rooted at that ancestor (excluding visited nodes).
  //
  // Parameters:
  // - node: TreeNode* from which we start going upward (i.e., target node).
  // - k: Target distance to find nodes at.
  // - ans: vector<int> to collect the results.
  // - parentMap: unordered_map mapping each node to its parent.
  //
  // Time Complexity: O(N)
  //     - In the worst case, we may visit all nodes in the tree.
  //     - For each ancestor, we may do a BFS into part of the tree, which can
  //       cumulatively cover all nodes.
  //
  // Space Complexity: O(N)
  //     - For the visited map and the queue used in BFS.
  // -----------------------------------------------------------------------------
  void traverseKLevelsAbove(TreeNode *node, int k, vector<int> &ans, unordered_map<TreeNode *, TreeNode *> parentMap)
  {
    unordered_map<TreeNode *, int> visited; // Keeps track of visited nodes to avoid duplicates
    int dist_up = 0;                        // Distance moved upward from the target node

    // Traverse ancestors using parent map
    while (parentMap.find(node) != parentMap.end())
    {
      visited[node]++;        // Mark current node as visited
      node = parentMap[node]; // Move to parent
      dist_up++;              // Increase upward distance

      // BFS from current ancestor to find nodes at distance = k - dist_up (downward)
      queue<TreeNode *> q;
      q.push(node);
      int dist_down = dist_up;

      while (!q.empty())
      {
        int qSize = q.size();

        // If current distance from original target is k, collect nodes at this level
        if (dist_down == k)
        {
          for (int i = 0; i < qSize; i++)
          {
            ans.push_back(q.front()->val);
            q.pop();
          }
          continue; // We've collected this level, skip processing children
        }

        // Normal level-order traversal with visited check
        for (int i = 0; i < qSize; i++)
        {
          auto *tmp = q.front();
          if (tmp->left && visited.find(tmp->left) == visited.end())
            q.push(tmp->left);
          if (tmp->right && visited.find(tmp->right) == visited.end())
            q.push(tmp->right);
          q.pop();
        }

        dist_down++; // Move to the next level
      }
    }
  }

  // -----------------------------------------------------------------------------
  // Method: distanceK
  // Purpose: Finds all nodes at distance K from a given target node in a binary tree.
  //          Combines:
  //          - BFS downward traversal from the target node.
  //          - BFS downward traversal from each ancestor going upward using parent map.
  //
  // Parameters:
  // - root: TreeNode* root of the binary tree.
  // - target: TreeNode* target node from which distance is measured.
  // - k: integer distance to find nodes at.
  //
  // Returns:
  // - A vector of integers representing the values of all nodes at distance k.
  //
  // Time Complexity: O(N)
  //     - Each node is visited at most once during upward/downward traversals.
  // Space Complexity: O(N)
  //     - For parentMap, visited map, queues, and the result vector.
  // -----------------------------------------------------------------------------
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
  {
    vector<int> ans;
    if (root == NULL)
      return ans;
    if (k == 0)
      return {target->val}; // Distance 0 → return target node's value

    unordered_map<TreeNode *, TreeNode *> parentMap; // Stores child → parent

    createParentMap(root, parentMap);                // O(N)
    traverseKLevelsBelow(target, k, ans);            // O(N)
    traverseKLevelsAbove(target, k, ans, parentMap); // O(N)

    return ans;
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
