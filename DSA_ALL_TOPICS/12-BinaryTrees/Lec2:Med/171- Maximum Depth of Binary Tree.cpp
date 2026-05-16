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

1. Title: Height of a Binary Tree


Links:
https://takeuforward.org/data-structure/maximum-depth-of-a-binary-tree/
https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=14
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/maximum-depth-in-bt
https://leetcode.com/problems/maximum-depth-of-binary-tree/description/



Problem statement:
Given root of the binary tree, return its maximum depth.

A binary tree's maximum depth is number of nodes along the longest path from from root node down to the farthest node.

Examples:
  Input : root = [1, 2, 3, null, null, null , 6]
  Output : 3
  Explanation : The path from root node 1 to node with value 6 has maximum depth with 3 nodes along path.

  Input : root = [3, 9, 20, null, null, 15 , 7]
  Output : 3
  Explanation : The path from root node 3 to node with value 15 has maximum depth with 3 nodes along path.
  There exists other paths to reach the solution.



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
// 1. Title: Height of a Binary Tree
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * APPROACH 1: RECURSIVE DEPTH-FIRST SEARCH (BOTTOM-UP)
 * ============================================================================
 * Logic: We ask our left child its max depth, ask our right child its max depth,
 * take the larger of the two, and add 1 for ourselves. This bubbles up the
 * max depth from the leaves back to the root.
 *
 * Time Complexity: O(N)
 * -> We visit every single node in the tree exactly once.
 * Space Complexity: O(H) (Where H is the height of the tree)
 * -> This is the implicit memory used by the recursive call stack.
 * -> Best/Average case (Balanced Tree): O(log N)
 * -> Worst case (Skewed Tree / Linked List): O(N)
 * ============================================================================
 */
class Solution1
{
public:
  int maxDepth(TreeNode *root)
  {
    // Base Case: If we hit a null pointer, it contributes 0 to the depth.
    if (!root)
    {
      return 0;
    }

    // Recursive Step: 1 (current node) + max depth of subtrees
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
  }
};

/**
 * ============================================================================
 * APPROACH 2: ITERATIVE BREADTH-FIRST SEARCH (LEVEL-ORDER)
 * ============================================================================
 * Logic: We use a Queue to process the tree one horizontal level at a time.
 * By capturing the `size` of the queue at the start of each level, we know
 * exactly how many nodes belong to the current depth level. Every time we
 * process a full level, we increment our depth counter.
 *
 * Time Complexity: O(N)
 * -> Every node is pushed and popped from the queue exactly once.
 * Space Complexity: O(W) (Where W is the maximum width of the tree)
 * -> The queue holds at most one complete level of the tree at a time.
 * -> Worst case (Perfectly Balanced Tree): The bottom level holds roughly N/2
 *    nodes, making the space complexity O(N).
 * ============================================================================
 */
class Solution
{
public:
  int maxDepth(TreeNode *root)
  {
    int depth = 0;
    queue<TreeNode *> q;

    // Guard against an empty tree input
    if (root)
      q.push(root);

    // Continue until there are no more levels to process
    while (!q.empty())
    {
      // Capture the number of nodes at the current level
      int size = q.size();
      ++depth; // We are stepping into a new depth level

      // Process all nodes strictly belonging to this current level
      while (size--)
      {
        TreeNode *cur = q.front();
        q.pop();

        // Queue up the children for the NEXT level
        if (cur->left)
          q.push(cur->left);

        if (cur->right)
          q.push(cur->right);
      }
    }

    return depth;
  }
};

int main()
{
  return 0;
}
