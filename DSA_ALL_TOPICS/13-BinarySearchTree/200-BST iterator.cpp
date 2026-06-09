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

1. Title: BST iterator

Links:
https://takeuforward.org/plus/dsa/problems/bst-iterator?tab=editorial
https://leetcode.com/problems/binary-search-tree-iterator/description/


Problem statement:
Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

Example 1:
  Input:
    ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
    [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]

           (7)
         /   \
       (3)   (15)
             /  \
           (9)  (20)

  Output:   [null, 3, 7, true, 9, true, 15, true, 20, false]

  Explanation
  BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
  bSTIterator.next();    // return 3
  bSTIterator.next();    // return 7
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 9
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 15
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 20
  bSTIterator.hasNext(); // return False


Constraints:
  The number of nodes in the tree is in the range [1, 10^5].
  0 <= Node.val <= 10^6
  At most 10^5 calls will be made to hasNext, and next.


Follow up:
Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?


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
// 1. Title: BST iterator
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * BST ALGORITHM: BINARY SEARCH TREE ITERATOR (O(h) SPACE)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * We simulate a "Paused" Inorder Traversal (Left -> Root -> Right).
 * We maintain a stack that holds the strict "left spine" of the current
 * traversal path.
 * 1. Constructor: Initialize by pushing the root and its entire left lineage.
 * 2. next(): Pop and return the top node. If that node has a right child,
 * we push that right child and its entire left lineage onto the stack.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY:
 * - `hasNext()`: O(1) -> Just checking if the stack is empty.
 * - `next()`: Amortized O(1) -> While there is a `while` loop inside, across
 * the entire lifecycle of the iterator, every node in the tree is pushed
 * exactly once and popped exactly once.
 * - SPACE COMPLEXITY: O(h)
 * - The stack only stores nodes along a single path from root to leaf,
 * meaning the memory footprint never exceeds the height of the tree.
 * ============================================================================
 */
class BSTIterator
{
private:
  stack<TreeNode *> st;

public:
  BSTIterator(TreeNode *root)
  {
    // Initialize by diving all the way down the left spine
    while (root != nullptr)
    {
      st.push(root);
      root = root->left;
    }
  }

  int next()
  {
    // Pop the absolute smallest available element
    TreeNode *cur = st.top();
    st.pop();

    // If this node has a right subtree, we must explore it.
    // We step right, then dive all the way down its left spine.
    TreeNode *tmp = cur->right;
    while (tmp != nullptr)
    {
      st.push(tmp);
      tmp = tmp->left;
    }

    return cur->val;
  }

  bool hasNext()
  {
    // If the stack has elements, the traversal is not finished
    return !st.empty();
  }
};

int main()
{

  /**
   * Your BSTIterator object will be instantiated and called as such:
   * BSTIterator* obj = new BSTIterator(root);
   * int param_1 = obj->next();
   * bool param_2 = obj->hasNext();
   */
  return 0;
}
