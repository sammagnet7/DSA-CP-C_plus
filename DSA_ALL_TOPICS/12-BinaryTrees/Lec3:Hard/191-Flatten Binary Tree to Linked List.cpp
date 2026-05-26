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

1. Title: Flatten Binary Tree to Linked List

Links:
https://takeuforward.org/data-structure/flatten-binary-tree-to-linked-list/
https://takeuforward.org/plus/dsa/problems/flatten-binary-tree-to-linked-list
https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/


Problem statement:
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.

Examples:
  Example 1:
  Input: root = [1,2,5,3,4,null,6]

              (1)
             /   \
           (2)   (5)
          /  \      \
        (3)  (4)    (6)

  Output: [1,null,2,null,3,null,4,null,5,null,6]

          (1) -> (2) -> (3) -> (4) -> (5) -> (6)


  Example 2:
  Input: root = []
  Output: []

  Example 3:
  Input: root = [0]
  Output: [0]


Constraints:
  The number of nodes in the tree is in the range [0, 2000].
  -100 <= Node.val <= 100

Follow up: Can you flatten the tree in-place (with O(1) extra space)?


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
// 1. Title: Flatten Binary Tree to Linked List
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: FLATTEN BINARY TREE (TAIL-RETURNING RECURSION)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * Instead of traversing all the way down the right side of a left subtree
 * to find where to attach the original right subtree, we can have our recursive
 * function return the exact "Tail" node of whatever subtree it just flattened!
 * * * [THE MECHANICS]
 * 1. Recursively flatten the Left and Right subtrees. Catch their Tail nodes.
 * 2. If a Left Subtree existed, we must splice it between the Root and the
 * Right Subtree.
 * - Connect the Left's Tail to the original Right Subtree.
 * - Swing the entire Left Subtree over to the right.
 * - Nullify the left pointer.
 * 3. Return the absolute Tail of the current branch so the parent frame
 * can use it. Priority: Right Tail > Left Tail > Current Node.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * The recursive function is called exactly once for every single node in
 * the tree. The splicing operations inside the function take strictly O(1)
 * constant time. Therefore, the overall time scales linearly with N.
 * * - SPACE COMPLEXITY: O(H) -> Worst Case O(N)
 * Because this is a Depth-First recursive approach, the memory overhead
 * comes from the call stack. The stack goes as deep as the height of the
 * tree (H).
 * - Best Case (Perfectly Balanced Tree): O(log N) stack space.
 * - Worst Case (Skewed "Chain" Tree): O(N) stack space.
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Flattens the subtree and returns the absolute last node (tail)
   * of the newly flattened linked list.
   */
  TreeNode *flattenAndGetTail(TreeNode *node)
  {

    // Base case: An empty node has no tail
    if (!node)
    {
      return nullptr;
    }

    // 1. Flatten both branches and capture their respective tails
    TreeNode *leftTail = flattenAndGetTail(node->left);
    TreeNode *rightTail = flattenAndGetTail(node->right);

    // 2. Splicing Phase: If there is a left subtree, wire it in
    if (node->left)
    {

      // Link the tail of the left subtree to the start of the right subtree
      // (Even if node->right is null, this safely links a nullptr)
      leftTail->right = node->right;

      // Swing the left branch over to the right
      node->right = node->left;

      // Clean up the left pointer
      node->left = nullptr;
    }

    // 3. Return the absolute tail of this newly merged chain
    // We cascade our checks: the rightmost node is the ultimate tail.
    if (rightTail)
    {
      return rightTail;
    }

    if (leftTail)
    {
      return leftTail;
    }

    // If it's a leaf node (no children), it is its own tail
    return node;
  }

public:
  void flatten(TreeNode *root)
  {
    // Kick off the recursive restructuring
    flattenAndGetTail(root);
  }
};

/**
 * ============================================================================
 * TREE ALGORITHM: FLATTEN BINARY TREE TO LINKED LIST (O(1) SPACE ITERATIVE)
 * ============================================================================
 * * [THE MENTAL MODEL: "IN-PLACE SPLICING"]
 * We use a Morris-inspired pointer manipulation strategy. In a flattened tree
 * (which follows Preorder sequence: Root -> Left -> Right), a node's original
 * right subtree must be executed immediately AFTER its entire left subtree.
 * Therefore, we can safely detach the right subtree and graft it directly onto
 * the absolute rightmost leaf (the inorder predecessor) of the left subtree.
 * * * [APPROACH / THE MECHANICS]
 * We use a single pointer `cur` to walk the tree.
 * 1. If `cur` has NO left child:
 * - The structure is already locally flat. Move right.
 * 2. If `cur` HAS a left child:
 * - Find `pred`, the rightmost node of the left subtree.
 * - Grafting: Attach `cur->right` to `pred->right`.
 * - Shifting: Swing the entire left branch over to `cur->right`.
 * - Cleaning: Save the new right branch to a `tmp` pointer, sever the
 * old `cur->left` connection, and precisely advance `cur` down to `tmp`.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * Even though there is a nested `while` loop, this does not degrade to O(N^2).
 * Every node is visited by `cur`. The inner loop traverses down the right
 * boundaries of left subtrees. Across the entire lifespan of the algorithm,
 * each edge in the tree is traversed a strictly bounded number of times (at
 * most twice). Therefore, the total operations scale linearly with N.
 * * - SPACE COMPLEXITY: O(1)
 * We strictly use three local pointers (`cur`, `pred`, `tmp`). All restructuring
 * happens entirely in-place by mutating existing memory addresses. There is
 * zero recursion overhead and no external data structures.
 * ============================================================================
 */
class Solution
{
public:
  void flatten(TreeNode *root)
  {
    TreeNode *cur = root;

    while (cur)
    {

      // Case 1: No left branch to flatten. Just keep moving right.
      if (cur->left == nullptr)
      {
        cur = cur->right;
      }
      // Case 2: Left branch exists. Restructure the pointers in-place.
      else
      {
        // Step 1: Find the absolute rightmost node of the left branch
        TreeNode *pred = cur->left;
        while (pred->right)
        {
          pred = pred->right;
        }

        // Step 2: Graft the current right branch to the predecessor's tail
        pred->right = cur->right;

        // Step 3: Swing the entire left branch over to the right side
        cur->right = cur->left;

        // Step 4: Clean up and elegantly advance the pointer
        // We use tmp to safely step down the newly formed right branch
        // while wiping out the old left connection.
        TreeNode *tmp = cur->left;
        cur->left = nullptr;
        cur = tmp;
      }
    }
  }
};

int main()
{
  return 0;
}
