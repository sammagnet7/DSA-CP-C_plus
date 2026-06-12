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

1. Title: Two sum in BST

Links:
https://takeuforward.org/plus/dsa/problems/two-sum-in-bst?tab=editorial
https://leetcode.com/problems/two-sum-iv-input-is-a-bst/


Problem statement:
Given the root of a Binary Search Tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

Examples:
  Example 1:
  Input: root = [5,3,6,2,4,null,7], k = 9

            (5)
           /   \
         (3)   (6)
         / \     \
       (2) (4)   (7)

  Output: true

  Example 2:
  Input: root = [5,3,6,2,4,null,7], k = 28

            (5)
           /   \
         (3)   (6)
         / \     \
       (2) (4)   (7)

  Output: false

Constraints:
  The number of nodes in the tree is in the range [1, 10^4].
  -10^4 <= Node.val <= 10^4
  root is guaranteed to be a valid Binary Search Tree.
  -10^5 <= k <= 10^5


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
// 1. Title: Two sum in BST
//-------------------------------------------------------------------------------

/**
 * =============================================================================
 * Approach 1: HASH SET APPROACH  [SUB-OPTIMAL] [O(N) space -> optimize to O(H)]
 * =============================================================================
 * * [THE MENTAL MODEL]
 * We traverse the tree (in any order) while maintaining a Hash Set of all
 * previously visited values. For every node, we check if its mathematical
 * complement (`target - node->val`) already exists in the set.
 * * NOTE: While this works perfectly, it ignores the sorted property of a BST.
 * This is the optimal approach for an UNSORTED Binary Tree, but for a strict
 * BST, the O(h) space Dual Iterator approach is vastly preferred.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * We visit each node at most once. Set insertions and lookups are O(1).
 * - SPACE COMPLEXITY: O(N)
 * In the worst-case scenario (no valid pair exists), every single node's
 * value will be stored in the `unordered_set`.
 * ============================================================================
 */
class Solution
{
private:
  bool checkTarget(TreeNode *node, int target, unordered_set<int> &st)
  {

    // Base case: We fell off the tree
    if (!node)
    {
      return false;
    }

    // Check if we have already seen the complement needed to hit the target
    if (st.find(target - node->val) != st.end())
    {
      return true;
    }

    // Add the current node to our set of "seen" values
    st.insert(node->val);

    // Recursively search the left branch. If it finds the pair, short-circuit and return true.
    if (checkTarget(node->left, target, st))
    {
      return true;
    }

    // Recursively search the right branch.
    return checkTarget(node->right, target, st);
  }

public:
  bool findTarget(TreeNode *root, int k)
  {
    unordered_set<int> st;
    return checkTarget(root, k, st);
  }
};

/**
 * ============================================================================
 * Approach 2: Using BST ITERATORS  [OPTIMAL] [O(H) space]
 * ============================================================================
 * * [THE MENTAL MODEL]
 * To find if two nodes sum to a target 'k', we simulate the classic Two-Pointer
 * approach used on sorted arrays. We start one pointer at the absolute minimum
 * (Forward Iterator) and one at the absolute maximum (Backward Iterator).
 * If the sum is too small, we advance the Forward Iterator. If the sum is too
 * large, we advance the Backward Iterator, squeezing them together until they
 * cross paths.
 * * * [HOW WE ACHIEVED O(H) SPACE INSTEAD OF O(N)]
 * The brute-force way to do this is to run a full Inorder Traversal, flatten
 * the tree into an array, and run the Two-Pointer logic on the array. However,
 * an array stores EVERY node simultaneously, requiring O(N) memory.
 * * Instead, this `BstIterator` creates a "Paused Traversal". It uses a stack
 * to traverse the tree dynamically, pausing at each node. Because the stack
 * only needs to remember the ancestry path from the root down to the current
 * node (a single "spine" of the tree), the stack size never exceeds the maximum
 * depth of the tree. Therefore, memory usage drops from O(N) to O(h).
 * * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(N)
 * Every node is pushed and popped from a stack at most once.
 * - SPACE COMPLEXITY: O(h)
 * Where 'h' is the height of the tree. Two stacks are used, each bounded by O(h).
 * ============================================================================
 */

class BstIterator
{
private:
  stack<TreeNode *> st;
  bool isFwd; // True = Ascending (Left-to-Right), False = Descending (Right-to-Left)

public:
  // Constructor: Initializes the stack by diving down the appropriate extreme edge
  BstIterator(TreeNode *root, bool fwd) : isFwd(fwd)
  {
    if (isFwd)
    {
      // Forward Iterator: Dive down the left spine to find the absolute minimum
      while (root != nullptr)
      {
        st.push(root);
        root = root->left;
      }
    }
    else
    {
      // Backward Iterator: Dive down the right spine to find the absolute maximum
      while (root != nullptr)
      {
        st.push(root);
        root = root->right;
      }
    }
  }

  bool hasNext()
  {
    return !st.empty();
  }

  // Returns the next sequential node in the paused traversal
  TreeNode *next()
  {
    TreeNode *ret = st.top();
    st.pop();

    if (isFwd)
    {
      // If moving forward, explore the right subtree by diving down its left spine
      TreeNode *tmp = ret->right;
      while (tmp != nullptr)
      {
        st.push(tmp);
        tmp = tmp->left;
      }
    }
    else
    {
      // If moving backward, explore the left subtree by diving down its right spine
      TreeNode *tmp = ret->left;
      while (tmp != nullptr)
      {
        st.push(tmp);
        tmp = tmp->right;
      }
    }

    return ret;
  }
};

class Solution
{
public:
  bool findTarget(TreeNode *root, int k)
  {

    // Spin up the two paused-traversals.
    // Allocated on the stack (not heap) to automatically prevent memory leaks.
    BstIterator f(root, true);  // Finds minimums
    BstIterator b(root, false); // Finds maximums

    // Grab the absolute smallest and largest nodes in the BST
    TreeNode *l = f.next();
    TreeNode *r = b.next();

    // Squeeze the pointers together.
    // Because we returned actual pointers, we can verify they crossed paths
    // by simply checking if they point to the exact same memory address!
    while (l != r)
    {

      int sum = l->val + r->val;

      if (sum == k)
      {
        return true; // Target match found
      }
      else if (sum > k)
      {
        // The sum is too large. We need a smaller number.
        // Advance the backward iterator (which yields smaller maximums).
        if (b.hasNext())
        {
          r = b.next();
        }
        else
        {
          break; // Exhausted the tree
        }
      }
      else
      {
        // The sum is too small. We need a larger number.
        // Advance the forward iterator (which yields larger minimums).
        if (f.hasNext())
        {
          l = f.next();
        }
        else
        {
          break; // Exhausted the tree
        }
      }
    }

    return false;
  }
};

int main()
{
  return 0;
}
