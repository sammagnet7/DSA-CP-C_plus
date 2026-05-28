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

1. Title: Delete Node in a BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/medium/delete-a-node-in-bst?tab=editorial
https://leetcode.com/problems/delete-node-in-a-bst/description/


Problem statement:
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:
  Search for a node to remove.
  If the node is found, delete the node.


Example 1:
  Input: root = [5,3,6,2,4,null,7], key = 3
  Output: [5,4,6,2,null,null,7]

            5                                 5
          /   \                             /   \
        3       6           ===>          4       6
       / \       \                       /         \
      2   4       7                     2           7

  Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
  One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
  Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

  Example 2:
    Input: root = [5,3,6,2,4,null,7], key = 0
    Output: [5,3,6,2,4,null,7]

                            5
                          /   \
                        2       6
                        \       \
                          4       7

    Explanation: The tree does not contain a node with value = 0.

  Example 3:
    Input: root = [], key = 0
    Output: []


Constraints:
  The number of nodes in the tree is in the range [0, 10^4].
  -10^5 <= Node.val <= 10^5
  Each node has a unique value.
  root is a valid binary search tree.
  -10^5 <= key <= 10^5


Follow up: Could you solve it with time complexity O(height of tree)?


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
// 1. Title: Delete Node in a BST
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * BST ALGORITHM: DELETE NODE (EXPLICIT 3-SCENARIO RECURSION)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * We recursively search for the target. Once found, we explicitly handle
 * the 3 distinct architectural scenarios:
 * 1. Leaf Node (0 Children): Safely delete the node and return null.
 * 2. Single Child (1 Child): Bypass the target. Delete it and return the
 * surviving child (left or right) to connect to the parent above.
 * 3. Full House (2 Children): We perform a "Predecessor Shift". We find the
 * absolute maximum value in the left subtree. We wire the original
 * right subtree to this predecessor's right pointer. Finally, we delete
 * the target and return the left subtree to take over.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst O(N)
 * - SPACE COMPLEXITY: O(H) -> Recursion call stack overhead.
 * ============================================================================
 */
class Solution
{
public:
  TreeNode *deleteNode(TreeNode *root, int key)
  {

    // Base case: Fell off the tree, key does not exist
    if (!root)
    {
      return nullptr;
    }

    // Stage 1: SEARCH PHASE
    if (key > root->val)
    {
      root->right = deleteNode(root->right, key);
      return root;
    }
    else if (key < root->val)
    {
      root->left = deleteNode(root->left, key);
      return root;
    }

    // Stage 2: DELETION PHASE (Key found!)
    else
    {

      // Scenario 1: LEAF NODE (0 Children)
      // It has no dependents. We can just wipe it out.
      if (!root->left && !root->right)
      {
        delete root;
        return nullptr;
      }

      // Scenario 2a: MISSING RIGHT CHILD (Left-child only)
      // Save the left child, delete target, return the left child.
      else if (!root->right)
      {
        TreeNode *tmp = root->left;
        delete root;
        return tmp;
      }

      // Scenario 2b: MISSING LEFT CHILD (Right-child only)
      // Save the right child, delete target, return the right child.
      else if (!root->left)
      {
        TreeNode *tmp = root->right;
        delete root;
        return tmp;
      }

      // Scenario 3: BOTH CHILDREN EXIST (Predecessor Shift)
      else
      {
        // Find the absolute rightmost node of the left subtree
        TreeNode *pred = root->left;
        while (pred->right)
        {
          pred = pred->right;
        }

        // Splice the original right branch to the predecessor's right
        pred->right = root->right;

        // Save the left branch to bubble it up
        TreeNode *tmp = root->left;

        // Erase the target node
        delete root;

        // The left branch moves up to take the deleted node's exact place
        return tmp;
      }
    }
  }
};

int main()
{
  return 0;
}
