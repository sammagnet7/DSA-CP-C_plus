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

1. Title: Floor in BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/floor-and-ceil-in-a-bst?tab=editorial
https://www.naukri.com/code360/problems/floor-from-bst_920457?leftPanelTabValue=PROBLEM



Problem statement:
You are given a BST (Binary search tree) with’ N’ number of nodes and a value ‘X’. Your task is to find the greatest value node of the BST which is smaller than or equal to ‘X’.
Note :‘X’ is not smaller than the smallest node of BST .

For example:

         (10)
         /  \
       (5) (15)
       / \
     (2) (6)

In the above example, For the given BST  and X = 7, the greatest value node of the BST  which is smaller than or equal to  7 is 6.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Ceil in BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/floor-and-ceil-in-a-bst?tab=editorial
https://www.naukri.com/code360/problems/ceil-from-bst_920464?leftPanelTabValue=PROBLEM


Problem statement:
Ninja is given a binary search tree and an integer. Now he is given a particular key in the tree and returns its ceil value. Can you help Ninja solve the problem?

Note:
Ceil of an integer is the closest integer greater than or equal to a given number.


For example:
arr[] = {1, 2, 5, 7, 8, 9}, key = 3.
The closest integer greater than 3 in the given array is 5. So, its ceil value in the given array is 5.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Floor in BST
//-------------------------------------------------------------------------------

// Definition for a binary tree node (assumed context)
template <typename T>
struct TreeNode
{
  T val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * ============================================================================
 * BST ALGORITHM: FIND FLOOR VALUE (RECURSIVE)
 * ============================================================================
 * * [THE MENTAL MODEL: "BUBBLING UP THE BEST CANDIDATE"]
 * The "Floor" is the greatest value in the BST that is <= X.
 * Because this is recursive, we rely on the call stack to bubble the correct
 * answer back up to the top.
 * 1. If `root->val == X`, we hit the jackpot. Return it immediately.
 * 2. If `root->val > X`, this node is too big. We delegate the entire search
 * to the left subtree.
 * 3. If `root->val < X`, this node is a valid candidate. However, there might
 * be a tighter (larger) floor hidden in the right subtree. We recursively
 * check the right side. If the right side finds a valid floor, we return
 * that. If it finds nothing (returns -1), we return our current node.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * We only make one recursive call per level of the tree, slicing the search
 * space in half at each step (if balanced).
 * - SPACE COMPLEXITY: O(H)
 * Unlike the iterative approach, every step downward adds a frame to the
 * recursion call stack. In a perfectly balanced tree, this is O(log N).
 * In a skewed tree, this degrades to O(N) memory.
 * ============================================================================
 */
int floorInBST(TreeNode<int> *root, int X)
{

  // Base Case: We fell off the tree. Return -1 to indicate "no floor found".
  if (root == nullptr)
  {
    return -1;
  }

  // Exact match found. It doesn't get better than this.
  if (root->val == X)
  {
    return root->val;
  }

  // Current node is too large. The floor mathematically MUST be on the left.
  if (root->val > X)
  {
    return floorInBST(root->left, X);
  }

  // Current node is smaller than X. It's a valid candidate!
  // But we must check the right subtree to see if there is an even closer match.
  int rightFloor = floorInBST(root->right, X);

  // If the right subtree found a valid floor, pass it up.
  // Otherwise, our current node is the absolute best we can do.
  return (rightFloor != -1) ? rightFloor : root->val;
}

/**
 * ============================================================================
 * BST ALGORITHM: FIND FLOOR VALUE (ITERATIVE)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * The "Floor" is the greatest value in the BST that is <= X.
 * As we traverse the BST:
 * 1. If `node->val == X`, we found the exact match. That is the ultimate floor.
 * 2. If `node->val > X`, this node is too big. The floor MUST be in the left subtree.
 * 3. If `node->val < X`, this node is a VALID floor candidate! We record it,
 * but there might be a tighter (larger) floor further down the right subtree.
 * So we save it and step right.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * - SPACE COMPLEXITY: O(1) -> Pure pointer traversal, no stack memory.
 * ============================================================================
 */
int floorInBST(TreeNode<int> *root, int X)
{

  TreeNode<int> *node = root;
  int floorCandidate = -1;

  while (node != nullptr)
  {

    // Exact match found. It doesn't get better than this.
    if (node->val == X)
    {
      return X;
    }
    // Current node is smaller than X. It's a valid candidate!
    // Record it, and search the right subtree for an even closer match.
    else if (node->val < X)
    {
      floorCandidate = node->val; // No need for max(), BST guarantees it's larger
      node = node->right;
    }
    // Current node is too large. We must find smaller values.
    else
    {
      node = node->left;
    }
  }

  return floorCandidate;
}

//-------------------------------------------------------------------------------
// 2. Title: Ceil in BST
//-------------------------------------------------------------------------------

template <typename T>
class BinaryTreeNode
{
public:
  T data;
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;

  BinaryTreeNode(T data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }
};

class Solution
{
public:
  /**
   * ============================================================================
   * BST ALGORITHM: FIND CEILING VALUE (RECURSIVE)
   * ============================================================================
   * * [THE MENTAL MODEL: "BUBBLING UP THE CEILING"]
   * The "Ceiling" is the smallest value in the BST that is >= x.
   * 1. If `node->data == x`, return it immediately (it's a perfect match).
   * 2. If `node->data < x`, this node is too small. The ceiling MUST exist
   * somewhere in the right subtree. Delegate the search to the right.
   * 3. If `node->data > x`, this node is a VALID ceiling! However, there might
   * be an even tighter (smaller) valid ceiling in the left subtree. We
   * recursively check the left side. If the left side returns a valid
   * ceiling, we use that. If it returns -1 (meaning no ceiling exists down
   * there), our current node remains the absolute best ceiling.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
   * We only traverse one path from the root downwards, making exactly one
   * recursive call per level of the tree.
   * - SPACE COMPLEXITY: O(H)
   * Because it is recursive, every downward step adds a frame to the call
   * stack. In a perfectly balanced tree, this uses O(log N) memory. In a
   * skewed tree (a single chain), it degrades to O(N) memory.
   * ============================================================================
   */
  int findCeil(BinaryTreeNode<int> *node, int x)
  {

    // Base Case: We fell off the tree. No ceiling exists on this path.
    if (node == nullptr)
    {
      return -1;
    }

    // Case 1: Exact match found. It doesn't get better than this.
    if (node->data == x)
    {
      return x;
    }

    // Case 2: Node is too large. It is a valid candidate!
    // Check if there is an even smaller valid candidate on the left.
    else if (node->data > x)
    {
      int leftCeil = findCeil(node->left, x);

      // If the left subtree found a valid ceiling, bubble it up.
      // If it returned -1, our current node is the best answer.
      return (leftCeil != -1) ? leftCeil : node->data;
    }

    // Case 3: Node is too small. The ceiling MUST be on the right side.
    else
    {
      return findCeil(node->right, x);
    }
  }

  /**
   * ============================================================================
   * BST ALGORITHM: FIND CEILING VALUE (ITERATIVE)
   * ============================================================================
   * * [THE MENTAL MODEL: "THE TIGHTENING NOOSE"]
   * The "Ceiling" is the smallest value in the BST that is >= x.
   * Because of the strict sorting rules of a BST, we can simply walk down the
   * tree and constantly update our "best guess" (the ceiling candidate).
   * 1. If `node->data == x`, we hit the jackpot. Return it immediately.
   * 2. If `node->data < x`, this node is too small. The ceiling MUST be on
   * the right side. We step right.
   * 3. If `node->data > x`, this node is a VALID ceiling candidate! We record
   * it as our current best answer. However, there might be an even tighter
   * (smaller) ceiling further down the left subtree. We step left.
   * (Note: Because it's a BST, every time we step left, the new candidate is
   * mathematically guaranteed to be smaller than our current one, so we just
   * overwrite it without needing a `min()` function).
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
   * We traverse exactly one path from the root down toward the leaves,
   * discarding half the tree at every step (in a balanced BST).
   * - SPACE COMPLEXITY: O(1)
   * We strictly use a single traversal pointer and one integer to track the
   * candidate. Zero recursion call stack overhead is used.
   * ============================================================================
   */
  int findCeil(BinaryTreeNode<int> *node, int x)
  {

    // Start with -1 to indicate "no ceiling found" in case x is larger
    // than every single node in the tree.
    int ceilCandidate = -1;

    while (node != nullptr)
    {

      // Case 1: Exact match found. Return immediately.
      if (node->data == x)
      {
        return x;
      }

      // Case 2: Current node is larger than x. It's a valid candidate!
      // Record it, and search the left subtree for an even tighter match.
      else if (node->data > x)
      {
        ceilCandidate = node->data; // Naturally overwrites with smaller valid values
        node = node->left;
      }

      // Case 3: Current node is too small. We must find larger values on the right.
      else
      {
        node = node->right;
      }
    }

    return ceilCandidate;
  }
};

int main()
{
  return 0;
}
