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

1. Title: Morris Inorder Traversal

Definition:
Morris Traversal is a tree traversal algorithm that visits every node in a binary tree in `O(N)` time while strictly using `O(1)` constant extra space.
Unlike standard Depth-First Search (DFS) which relies on a recursion call stack or a manual `std::stack` to remember how to return to parent nodes, Morris Traversal bypasses external memory entirely by temporarily modifying the tree itself.


Links:
https://takeuforward.org/data-structure/morris-inorder-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/morris-inorder-traversal-?tab=editorial
https://leetcode.com/problems/binary-tree-inorder-traversal/

Problem statement:
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Examples:
  Example 1:
  Input: root = [1,null,2,3]

             (1)
                \
                (2)
                /
              (3)

  Output: [1,3,2]

  Example 2:
  Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

              (1)
             /   \
           (2)   (3)
          /  \      \
        (4)  (5)    (8)
             / \    /
           (6) (7)(9)

  Output: [4,2,6,5,7,1,3,9,8]

  Example 3:
  Input: root = []
  Output: []

  Example 4:
  Input: root = [1]
  Output: [1]


Constraints:
  The number of nodes in the tree is in the range [0, 100].
  -100 <= Node.val <= 100


Note: Do it with in O(1) space complexity.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Morris Preorder Traversal

Links:
https://takeuforward.org/data-structure/morris-preorder-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/morris-preorder-traversal-?tab=editorial
https://leetcode.com/problems/binary-tree-preorder-traversal/description/


Problem statement:
Given the root of a binary tree, return the preorder traversal of its nodes' values.

Examples:
  Example 1:
  Input: root = [1,null,2,3]
  Output: [1,2,3]

  Example 2:
  Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
  Output: [1,2,4,5,6,7,3,8,9]

  Example 3:
  Input: root = []
  Output: []

  Example 4:
  Input: root = [1]
  Output: [1]

Constraints:
  The number of nodes in the tree is in the range [0, 100].
  -100 <= Node.val <= 100


Note: Do it with in O(1) space complexity.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

3. Title: Morris Postorder Traversal

Links:
https://leetcode.com/problems/binary-tree-postorder-traversal/


Problem statement:
Given the root of a binary tree, return the postorder traversal of its nodes' values.


Example 1:
  Input: root = [1,null,2,3]
  Output: [3,2,1]
  Explanation:


Example 2:
  Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
  Output: [4,6,7,5,2,9,8,3,1]
  Explanation:

Example 3:
  Input: root = []
  Output: []

Example 4:
  Input: root = [1]
  Output: [1]


Constraints:
  The number of the nodes in the tree is in the range [0, 100].
  -100 <= Node.val <= 100


Note: Do it with in O(1) space complexity.


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
// 1. Title: Morris Inorder Traversal IN Order
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: MORRIS INORDER TRAVERSAL (O(1) SPACE)
 * ============================================================================
 * * [THE MENTAL MODEL: "TEMPORARY BRIDGES"]
 * Standard traversals use an O(H) stack (or recursion) to remember how to
 * return to a parent node after visiting its left subtree. Morris Traversal
 * eliminates this by using the tree's own empty leaf pointers.
 * It temporarily builds a "bridge" (a thread) from the deepest rightmost node
 * of a left subtree (the predecessor) straight back up to the parent. Once
 * the left subtree is fully explored, it crosses the bridge back to the parent,
 * destroys the bridge to restore the original tree, and moves to the right subtree.
 * * [APPROACH / ALGORITHM DESIGN]
 * Initialize `curr` at the root.
 * 1. If `curr` has NO left child:
 * - We can't go left. Process/print `curr`, and move right (`curr = curr->right`).
 * 2. If `curr` HAS a left child:
 * - Find the Inorder Predecessor (go left once, then all the way right).
 * - Case A (Bridge doesn't exist): The predecessor's right pointer is null.
 * Link it to `curr` to create our return path. Safely move left (`curr = curr->left`).
 * - Case B (Bridge already exists): The predecessor's right pointer points
 * to `curr`. This means we just returned from the left side! Break the
 * link (set to null), process `curr`, and move right (`curr = curr->right`).
 * * [COMPLEXITY ANALYSIS]
 * - SPACE COMPLEXITY: O(1)
 * We strictly use two pointers (`curr` and `pred`) regardless of the tree's
 * size or shape. No recursive call stack or external memory is used.
 * * - TIME COMPLEXITY: O(N)
 * [Why isn't it O(N^2) due to the nested while loop?]
 * A tree with N nodes has exactly N-1 edges. In Morris Traversal, every
 * single edge in the tree is traversed a maximum of THREE times:
 * 1. Once when `curr` naturally traverses down it.
 * 2. Once when `pred` traverses down it to build the bridge.
 * 3. Once when `pred` traverses down it to destroy the bridge.
 * Since the maximum number of edge traversals is bounded by 3 * (N - 1),
 * the work scales linearly, making it strictly O(N) time.
 * ============================================================================
 */
class Solution
{
public:
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> inorder;
    TreeNode *curr = root;

    while (curr)
    {

      // Case 1: No left child. Process current node and move right.
      if (curr->left == nullptr)
      {
        inorder.push_back(curr->val);
        curr = curr->right;
      }
      // Case 2: Left child exists. We must build or cross a bridge.
      else
      {
        // Step A: Find the inorder predecessor of 'curr'
        TreeNode *pred = curr->left;

        // Go as far right as possible.
        // Stop if we hit a null (end of leaf) OR if we hit 'curr'
        // (meaning our temporary bridge already exists).
        while (pred->right != nullptr && pred->right != curr)
        {
          pred = pred->right;
        }

        // Step B: Build the bridge
        if (pred->right == nullptr)
        {
          pred->right = curr; // Create temporary thread back to parent
          curr = curr->left;  // Safely traverse down the left side
        }
        // Step C: Cross and destroy the bridge
        else
        {
          pred->right = nullptr;        // Restore tree structure
          inorder.push_back(curr->val); // Left is done, process parent
          curr = curr->right;           // Move to right subtree
        }
      }
    }

    return inorder;
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Morris Preorder Traversal PRE Order
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * TREE ALGORITHM: MORRIS PREORDER TRAVERSAL (O(1) SPACE)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * Preorder visits the Root *before* its children. Therefore, in Morris Traversal,
 * we must process the current node the very first time we see it, which is
 * right before we step down into its left subtree (when we build the bridge).
 * * * [APPROACH]
 * 1. If no left child: Process current node, move right.
 * 2. If left child exists: Find the Inorder Predecessor.
 * - Case A (Bridge doesn't exist): Process the current node FIRST (Preorder rule).
 * Then build the bridge to guarantee a return path, and move left.
 * - Case B (Bridge already exists): We are returning from the left subtree.
 * Do NOT process the node again. Just destroy the bridge to restore
 * the tree structure, and move right.
 * * * [COMPLEXITY]
 * Time: O(N) -> Every edge is traversed at most 3 times.
 * Space: O(1) -> Only uses two pointers, no recursion stack.
 * ============================================================================
 */
class Solution
{
public:
  vector<int> preorderTraversal(TreeNode *root)
  {

    vector<int> preorder;
    TreeNode *cur = root;

    while (cur)
    {

      // Case 1: No left child. Process Root, move Right.
      if (cur->left == nullptr)
      {
        preorder.push_back(cur->val);
        cur = cur->right;
      }
      // Case 2: Left child exists. Handle the predecessor bridge.
      else
      {
        TreeNode *pred = cur->left;

        // Find the rightmost node in the left subtree
        while (pred->right && pred->right != cur)
        {
          pred = pred->right;
        }

        // Subcase A: First time visiting this root.
        // Process it BEFORE going left!
        if (pred->right == nullptr)
        {
          preorder.push_back(cur->val); // <-- Preorder magic happens here
          pred->right = cur;            // Build the bridge
          cur = cur->left;              // Step down into left subtree
        }
        // Subcase B: Returning from the left subtree.
        else
        {
          pred->right = nullptr; // Destroy the bridge
          cur = cur->right;      // Move to right subtree
        }
      }
    }

    return preorder;
  }
};

//-------------------------------------------------------------------------------
// 3. Title: Morris Preorder Traversal POST order   [NOT UNDERSTOOD]
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: MORRIS POSTORDER TRAVERSAL (O(1) SPACE)
 * ============================================================================
 * * [THE INTUITION]
 * Postorder requires Left -> Right -> Root. To print the right boundary of a
 * left subtree bottom-up without using an O(H) memory stack, we temporarily
 * reverse the `right` pointers of that boundary (like reversing a singly
 * linked list), record the values, and then reverse them back to restore
 * the tree structure.
 * * * [APPROACH]
 * 1. Introduce a `dummy` node where `dummy->left = root` so the final right
 * boundary of the true root gets harvested naturally.
 * 2. When a bridge is crossed (`pred->right == curr`), before moving right,
 * reverse the path from `curr->left` to `pred`.
 * 3. Collect the node values from `pred` back up to `curr->left`.
 * 4. Reverse the path a second time to perfectly restore the tree.
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Reverses the 'right' pointers of a chain from 'start' to 'end'
   * (Standard in-place singly linked list reversal)
   */
  void reversePath(TreeNode *start, TreeNode *end)
  {
    if (start == end)
      return;

    TreeNode *prev = start;
    TreeNode *curr = start->right;
    TreeNode *nextNode = nullptr;

    while (prev != end)
    {
      nextNode = curr->right;
      curr->right = prev; // Flip the pointer backward
      prev = curr;
      curr = nextNode;
    }
  }

  /**
   * @brief Reverses a boundary segment, extracts its values sequentially,
   * and immediately restores it back to its original state.
   */
  void processPath(TreeNode *start, TreeNode *end, vector<int> &postorder)
  {
    // Step 1: Flip pointers so 'end' becomes the accessible head
    reversePath(start, end);

    // Step 2: Traverse from the bottom node back up to the top node
    TreeNode *curr = end;
    while (true)
    {
      postorder.push_back(curr->val);
      if (curr == start)
        break;
      curr = curr->right;
    }

    // Step 3: Flip pointers back to fully restore tree integrity
    reversePath(end, start);
  }

public:
  vector<int> postorderTraversal(TreeNode *root)
  {
    vector<int> postorder;
    if (!root)
      return postorder;

    // Create a temporary dummy frame to catch the main root's right boundary
    TreeNode *dummy = new TreeNode(0);
    dummy->left = root;
    TreeNode *curr = dummy;

    while (curr != nullptr)
    {
      // Case 1: No left child, drift to the right branch
      if (curr->left == nullptr)
      {
        curr = curr->right;
      }
      // Case 2: Left child exists. Manage the bridge.
      else
      {
        TreeNode *pred = curr->left;
        while (pred->right != nullptr && pred->right != curr)
        {
          pred = pred->right;
        }

        // Subcase A: First time seeing this subtree. Build the bridge.
        if (pred->right == nullptr)
        {
          pred->right = curr;
          curr = curr->left;
        }
        // Subcase B: Returning via an existing bridge!
        else
        {
          // Harvest the right boundary of this completed left subtree in reverse
          processPath(curr->left, pred, postorder);

          pred->right = nullptr; // Destroy the bridge
          curr = curr->right;    // Move to right subtree
        }
      }
    }

    // Clean up heap allocation for the dummy node
    delete dummy;
    return postorder;
  }
};

int main()
{
  return 0;
}
