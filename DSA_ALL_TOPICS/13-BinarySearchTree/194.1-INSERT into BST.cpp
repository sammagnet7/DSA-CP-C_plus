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

1. Title: Insert into a Binary Search Tree

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/medium/insert-a-given-node-in-bst?tab=editorial
https://leetcode.com/problems/insert-into-a-binary-search-tree/description/


Problem statement:
You are given the root node of a binary search tree (BST) and a value to insert into the tree. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

Examples:
  Example 1:
  Input: root = [4,2,7,1,3], val = 5

    Original Tree:
               (4)
              /   \
            (2)   (7)
            / \
          (1) (3)

    After Insertion of (5):
               (4)
              /   \
            (2)   (7)
            / \   /
          (1) (3)(5)

  Output: [4,2,7,1,3,5]
  Explanation: Another accepted tree is:

               (5)
              /   \
            (2)   (7)
            / \
          (1) (3)
                \
                (4)

  Example 2:
  Input: root = [40,20,60,10,30,50,70], val = 25
  Output: [40,20,60,10,30,50,70,null,null,25]

  Example 3:
  Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
  Output: [4,2,7,1,3,5]


Constraints:
  The number of nodes in the tree will be in the range [0, 10^4].
  -10^8 <= Node.val <= 10^8
  All the values Node.val are unique.
  -10^8 <= val <= 10^8
  It's guaranteed that val does not exist in the original BST.


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
// 1. Title: Insert into a Binary Search Tree
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * BST ALGORITHM: INSERT NODE (ITERATIVE)
 * ============================================================================
 * * [THE MENTAL MODEL: "THE TRAILING PARENT"]
 * We use two pointers to walk down the tree: `curr` to explore, and `parent`
 * to trail exactly one step behind. We let `curr` follow the strict BST
 * routing rules (Left if smaller, Right if larger) until it falls completely
 * off the tree (`curr == nullptr`). Because `parent` was trailing behind, it
 * is now sitting precisely on the leaf node where the new value belongs!
 * We then just compare the new value to the `parent` to know which side
 * to attach it to.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * We traverse exactly one path from the root down to the bottom.
 * - SPACE COMPLEXITY: O(1)
 * We strictly use two tracking pointers. Zero recursion call stack overhead.
 * ============================================================================
 */
class Solution
{
public:
  TreeNode *insertIntoBST(TreeNode *root, int val)
  {

    TreeNode *newNode = new TreeNode(val);

    // Base Case: If the tree is completely empty, the new node is the root
    if (!root)
    {
      return newNode;
    }

    TreeNode *curr = root;
    TreeNode *parent = nullptr;

    // Step 1: Traverse down until `curr` falls off the edge
    while (curr != nullptr)
    {
      parent = curr; // Trail exactly one step behind

      if (val < curr->val)
      {
        curr = curr->left;
      }
      else
      {
        curr = curr->right;
      }
    }

    // Step 2: Attach the new node to the correct side of the trailing parent
    if (val < parent->val)
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }

    return root;
  }

  /**
   * ============================================================================
   * BST ALGORITHM: INSERT NODE (RECURSIVE)
   * ============================================================================
   * * [THE MENTAL MODEL]
   * We recursively drill down the tree. The base case is hitting a `null` spot.
   * When we hit null, we create the new node and return it. The previous frame
   * on the call stack catches this new node and binds it to its left or right pointer.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
   * - SPACE COMPLEXITY: O(H) -> Recursion call stack overhead.
   * ============================================================================
   */

  TreeNode *insertIntoBST(TreeNode *root, int val)
  {

    // Base Case: We found the empty spot! Create and return the new node.
    if (root == nullptr)
    {
      return new TreeNode(val);
    }

    // If the value is smaller, delegate insertion to the left subtree
    // (And catch whatever it returns, which will either be the existing left
    // child, or the newly created node if the left child was null).
    if (val < root->val)
    {
      root->left = insertIntoBST(root->left, val);
    }

    // If the value is larger, delegate insertion to the right subtree
    else
    {
      root->right = insertIntoBST(root->right, val);
    }

    // Return the current root so the parent above us stays properly linked
    return root;
  }
};

int main()
{
  return 0;
}
