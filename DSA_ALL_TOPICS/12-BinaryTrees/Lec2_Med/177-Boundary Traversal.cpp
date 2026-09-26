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

1. Title: Boundary Traversal

Links:
https://takeuforward.org/data-structure/boundary-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/boundary-traversal?tab=editorial
https://www.naukri.com/code360/problems/boundary-traversal-of-binary-tree_790725?leftPanelTabValue=PROBLEM


Problem statement:
You are given a binary tree having 'n' nodes.
The boundary nodes of a binary tree include the nodes from the left and right boundaries and the leaf nodes, each node considered once.
Figure out the boundary nodes of this binary tree in an Anti-Clockwise direction starting from the root node.

Examples:
  Example1:
    Input: 10 5 20 3 8 18 25 -1 -1 7 -1 -1 -1 -1 -1 -1 -1

             (10)
            /    \
          (5)    (20)
         /   \   /   \
       (3)   (8)(18) (25)
             /
           (7)

    Output: 10 5 3 7 18 25 20
    Explanation:
    The nodes on the left boundary are [10, 5, 3]
    The nodes on the right boundary are [10, 20, 25]
    The leaf nodes are [3, 7, 18, 25].
    Please note that nodes 3 and 25 appear in two places but are considered once.

  Example2:
    Input: 100 50 150 25 75 140 200 -1 30 70 80 -1 -1 -1 -1 -1 35 -1 -1 -1 -1 -1 -1

                 (100)
                /     \
             (50)     (150)
            /    \    /   \
         (25)   (75)(140) (200)
           \    /  \
           (30)(70)(80)
             \
             (35)

    Output: 100 50 25 30 35 70 80 140 200 150


Constraints:
  1 <= n <= 10000
  Where 'n' is the total number of nodes in the binary tree.


INPUT::::::


OUTPUT::::::


*/
template <typename T>
struct TreeNode
{
  T data;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : data(0), left(nullptr), right(nullptr) {}
  TreeNode(T x) : data(x), left(nullptr), right(nullptr) {}
  TreeNode(T x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

//-------------------------------------------------------------------------------
// 1. Title: Boundary Traversal
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: BOUNDARY TRAVERSAL (3-PART DECOMPOSITION)
 * ============================================================================
 * * [GRAPH THEORY DEFINITION OF A BOUNDARY]
 * In computer science, a tree's boundary is NOT its visual silhouette. It is
 * defined as a strict topological perimeter consisting of three parts:
 *
 * 1. Left Boundary: A continuous, unbroken edge path starting from `root->left`.
 *    Rule: Must travel to the Left Child. If (and ONLY if) no left child
 *    exists, it travels to the Right Child. Stops upon hitting a leaf.
 * 2. Right Boundary: A continuous, unbroken edge path starting from `root->right`.
 *    Rule: Must travel to the Right Child. If (and ONLY if) no right child
 *    exists, it travels to the Left Child. Stops upon hitting a leaf.
 * 3. Leaves: All nodes with zero children, read from left to right.
 *
 * * [THE "INNER NODE" TRAP]
 * Because boundaries are unbroken paths, if a left-boundary node has both a
 * left and right child, the algorithm MUST go left. The entire right branch
 * is permanently bypassed and becomes "internal" to the tree, even if nodes
 * inside it visually stick out further to the left.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N) -> Every node is visited a constant number of times.
 * - Space Complexity: O(H) -> Where H is the height of the tree (due to the
 *   recursion stack for leaves and temporary vectors for boundaries).
 * ============================================================================
 */

class Solution
{
private:
  /**
   * @brief Safely checks if a node is a leaf node.
   * Includes a guard clause against null pointers to prevent SegFaults.
   */
  bool isLeaf(TreeNode<int> *node)
  {
    if (!node)
    {
      return false;
    }
    return !node->left && !node->right;
  }

  /**
   * @brief Standard Pre-Order DFS to collect all leaf nodes from Left to Right.
   */
  void traverseLeaves(TreeNode<int> *node, vector<int> &leaves)
  {
    if (isLeaf(node))
    {
      leaves.push_back(node->data);
      return;
    }

    // We check left and right independently to ensure no leaves are missed.
    if (node->left)
    {
      traverseLeaves(node->left, leaves);
    }
    if (node->right)
    {
      traverseLeaves(node->right, leaves);
    }
  }

public:
  vector<int> traverseBoundary(TreeNode<int> *root)
  {
    vector<int> ans, left, leaves, right;
    TreeNode<int> *tmp;

    // [SAFETY CHECK 1] Empty tree
    if (!root)
      return ans;

    // [SAFETY CHECK 2] Single node tree (prevents duplicate root later)
    if (isLeaf(root))
    {
      return {root->data};
    }

    // Add root to answer independently to prevent left/right boundary crossover
    ans.push_back(root->data);

    // ==========================================
    // PART 1: LEFT BOUNDARY
    // ==========================================
    // Must start strictly at root->left
    tmp = root->left;

    while (tmp)
    {
      // Only add if it is NOT a leaf (leaves are handled in Part 2)
      if (!isLeaf(tmp))
        left.push_back(tmp->data);

      // Follow the strict left-boundary topological path rule
      if (tmp->left)
      {
        tmp = tmp->left;
      }
      else if (tmp->right)
      {
        tmp = tmp->right;
      }
      else
      {
        tmp = nullptr;
      }
    }

    // ==========================================
    // PART 2: LEAVES
    // ==========================================
    // Sweeps the bottom of the tree from left to right
    traverseLeaves(root, leaves);

    // ==========================================
    // PART 3: RIGHT BOUNDARY
    // ==========================================
    // Must start strictly at root->right
    tmp = root->right;

    while (tmp)
    {
      // Only add if it is NOT a leaf
      if (!isLeaf(tmp))
        right.push_back(tmp->data);

      // Follow the strict right-boundary topological path rule
      if (tmp->right)
      {
        tmp = tmp->right;
      }
      else if (tmp->left)
      {
        tmp = tmp->left;
      }
      else
      {
        tmp = nullptr;
      }
    }

    // Reverse the right boundary so it reads anti-clockwise (bottom-up)
    reverse(right.begin(), right.end());

    // ==========================================
    // MERGE RESULTS
    // ==========================================
    ans.insert(ans.end(), left.begin(), left.end());
    ans.insert(ans.end(), leaves.begin(), leaves.end());
    ans.insert(ans.end(), right.begin(), right.end());

    return ans;
  }
};

int main()
{
  return 0;
}
