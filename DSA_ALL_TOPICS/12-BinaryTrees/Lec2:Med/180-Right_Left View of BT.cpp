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

1. Title: Left View of BT

Links:
https://takeuforward.org/data-structure/right-left-view-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/right-left-view-of-bt?tab=editorial
https://www.naukri.com/code360/problems/left-view-of-a-binary-tree_920519?leftPanelTabValue=PROBLEM


Problem statement:
You have been given a binary tree of integers. You are supposed to find the left view of the binary tree. The left view of a binary tree is the set of all nodes that are visible when the binary tree is viewed from the left side.

Example:
  Sample Input 1:
  2
  3 4 -1 -1 -1
  2 8 7 -1 5 -1 -1 1 -1 -1 -1
  Sample Output 1:
  3 4
  2 8 5 1
  Explanation of Sample Input 1:
  For the first test case, node 3 and node 4 are visible when the binary tree is viewed from the left.

  For the second test case, nodes 2, 8, 5, 1 are visible when the binary tree is viewed from the left.
  Sample Input 2:
  2
  1 3 5 12 -1 8 -1 -1 -1 -1 -1
  9 6 3 -1 -1 4 8 -1 -1 -1 -1
  Sample Output 2:
  1 3 12
  9 6 4
  Explanation of Sample Input 2:
  For the first test case, nodes 1, 3, 12 are visible when the binary tree is viewed from the left.

  For the second test case, nodes 9, 6, 4 are visible when the binary tree is viewed from the left.


INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------


2. Title: Right View of BT

Links:
https://takeuforward.org/data-structure/right-left-view-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/right-left-view-of-bt?tab=editorial

https://leetcode.com/problems/binary-tree-right-side-view/description/
https://www.naukri.com/code360/problems/right-view_764605


Problem statement:
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Examples:
  Example 1:
  Input: root = [1,2,3,null,5,null,4]
  Output: [1,3,4]

  Example 2:
  Input: root = [1,2,3,4,null,null,null,5]
  Output: [1,3,4,5]

  Example 3:
  Input: root = [1,null,3]
  Output: [1,3]

  Example 4:
  Input: root = []
  Output: []



INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------



*/
template <typename T>
class TreeNode
{
public:
  T data;
  TreeNode<T> *left;
  TreeNode<T> *right;

  TreeNode(T data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }
};

//-------------------------------------------------------------------------------
// 1. Title: Left View of BT
//-------------------------------------------------------------------------------
class Solution
{
public:
  /**
   * ============================================================================
   * APPROACH 1: ITERATIVE BREADTH-FIRST SEARCH (BFS / LEVEL-ORDER) [RECOMMENDED]
   * ============================================================================
   * * [THE INTUITION]
   * The "Left View" of a tree is simply the very first node you see at every
   * depth level when looking from left to right. By doing a standard Level-Order
   * traversal, we can isolate each level and grab the first element.
   *
   * * [THE MECHANICS]
   * We use a Queue to traverse level-by-level. At the start of a new level
   * iteration, the node sitting at `q.front()` is guaranteed to be the
   * leftmost node of that level. We push it to our answer array, and then
   * process the rest of the row normally.
   *
   * * [COMPLEXITY]
   * Time: O(N) -> We visit every node exactly once.
   * Space: O(W) -> Where W is the maximum width of the tree. In the worst case
   * (a perfectly balanced tree), the queue holds N/2 nodes at the leaf level.
   * ============================================================================
   */
  vector<int> getLeftView(TreeNode<int> *root)
  {
    queue<TreeNode<int> *> q;

    // Safety check for empty tree
    if (root)
      q.push(root);

    vector<int> ans;

    while (!q.empty())
    {
      // Snapshot the number of nodes at the current depth level
      int qSize = q.size();

      // The first node in the queue at the start of a level iteration
      // is strictly the leftmost node of this row.
      ans.push_back(q.front()->data);

      // Process all nodes in the current row
      while (qSize--)
      {
        // Note: auto instead of auto& since q.front() returns a reference
        // but we pop immediately after. Copying the pointer is safer.
        auto cur = q.front();
        q.pop();

        // Push children for the next row (Left first, then Right)
        if (cur->left)
          q.push(cur->left);

        if (cur->right)
          q.push(cur->right);
      }
    }

    return ans;
  }

  /**
   * ============================================================================
   * APPROACH 2: RECURSIVE DEPTH-FIRST SEARCH (DFS)
   * ============================================================================
   * * [THE INTUITION]
   * Instead of going level-by-level, we can dive deep down the left side of
   * the tree first using a Pre-Order DFS (Root -> Left -> Right).
   *
   * * [THE MECHANICS - "THE VECTOR SIZE TRICK"]
   * We pass the current depth (`lvl`) into our recursion.
   * Because we ALWAYS visit the left child before the right child, the VERY
   * FIRST time we reach a new depth level, it will be the leftmost node.
   * How do we know if it's the first time visiting a depth?
   * If `ans.size() == lvl`, we know the vector doesn't have an entry for this
   * depth yet!
   *
   * * [COMPLEXITY]
   * Time: O(N) -> We visit every node exactly once.
   * Space: O(H) -> Where H is the height of the tree. This is for the recursive
   * call stack. In a skewed tree, worst case space is O(N).
   * ============================================================================
   */
  void dfs(TreeNode<int> *node, int lvl, vector<int> &ans)
  {
    // Base case: hit a dead end
    if (node == NULL)
      return;

    // If the size of the answer array equals the current depth level,
    // it means we are seeing this depth level for the very first time.
    // Since we traverse left branches first, this is the leftmost node.
    if (ans.size() == lvl)
      ans.push_back(node->data);

    // Traverse Left branch first (Priority for Left View)
    if (node->left != NULL)
      dfs(node->left, lvl + 1, ans);

    // Traverse Right branch (Only acts as a fallback if the left branch
    // ends early but the right branch continues deeper)
    if (node->right != NULL)
      dfs(node->right, lvl + 1, ans);
  }

  vector<int> getLeftView(TreeNode<int> *root)
  {
    vector<int> ans;

    // Safety check for empty tree
    if (root == NULL)
      return ans;

    // Start DFS at depth level 0
    dfs(root, 0, ans);

    return ans;
  }
};

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
    BinaryTreeNode<int> *
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Right View of BT
//-------------------------------------------------------------------------------
class Solution
{
public:
  /**
   * ============================================================================
   * APPROACH 1: ITERATIVE BREADTH-FIRST SEARCH (BFS / LEVEL-ORDER)
   * ============================================================================
   * * [THE INTUITION]
   * The "Right View" of a tree consists of the very last node you see at every
   * depth level when scanning from left to right. Using a standard level-order
   * traversal, we can isolate each level and capture the final node processed.
   *
   * * [THE MECHANICS]
   * We use a Queue to traverse level-by-level. During the inner `while(qSize--)`
   * loop, we constantly overwrite a `last` pointer with the current node.
   * When the inner loop finishes, `last` will naturally hold the rightmost
   * node of that level. We then append its value to our answer array.
   *
   * * [COMPLEXITY]
   * Time: O(N) -> We process every node exactly once.
   * Space: O(W) -> Where W is the maximum width of the tree. The queue holds
   * at most one entire level of nodes.
   * ============================================================================
   */
  vector<int> printRightView(BinaryTreeNode<int> *root)
  {
    queue<BinaryTreeNode<int> *> q;
    vector<int> ans;

    if (root)
      q.push(root);

    while (!q.empty())
    {
      // Snapshot the number of nodes at the current depth level
      int qSize = q.size();

      // Pointer to keep track of the last node seen in this level
      BinaryTreeNode<int> *last = nullptr;

      // Process the entire current row
      while (qSize--)
      {
        BinaryTreeNode<int> *cur = q.front();
        q.pop();

        // Queue children for the next row
        if (cur->left)
          q.push(cur->left);

        if (cur->right)
          q.push(cur->right);

        // Continuously update 'last'. When the loop ends, this will
        // hold the rightmost node of the current level.
        last = cur;
      }

      // Append the strictly rightmost node of this level
      if (last)
        ans.push_back(last->data);
    }

    return ans;
  }

  /**
   * ============================================================================
   * APPROACH 2: RECURSIVE DEPTH-FIRST SEARCH (DFS)
   * ============================================================================
   * * [THE INTUITION]
   * Instead of a level-by-level sweep, we can use a modified Pre-Order DFS.
   * By artificially prioritizing the RIGHT branch over the left branch
   * (Root -> Right -> Left), the very first time we reach a new depth level,
   * we are guaranteed to be looking at the rightmost node.
   *
   * * [THE MECHANICS - "THE REVERSE VECTOR SIZE TRICK"]
   * We track the current depth (`lvl`). Because we visit `node->right` before
   * `node->left`, the condition `ans.size() == lvl` will strictly trigger
   * on the rightmost node of any given level. The left branches only serve
   * as a fallback in case the right side of the tree is shorter than the left.
   *
   * * [COMPLEXITY]
   * Time: O(N) -> We visit every node exactly once.
   * Space: O(H) -> Where H is the height of the tree (recursion stack memory).
   * Highly optimal compared to BFS for deep, narrow trees.
   * ============================================================================
   */
  void dfs(BinaryTreeNode<int> *node, int lvl, vector<int> &ans)
  {
    // Base case: hit a dead end
    if (node == NULL)
      return;

    // If the size of the answer array equals the current depth level,
    // it means we are seeing this depth level for the very first time.
    // Because we traverse RIGHT first, this is the rightmost node.
    if (ans.size() == lvl)
      ans.push_back(node->data);

    // Traverse RIGHT branch first (Priority for Right View)
    if (node->right != NULL)
      dfs(node->right, lvl + 1, ans);

    // Traverse LEFT branch second (Fallback if right branch ends early)
    if (node->left != NULL)
      dfs(node->left, lvl + 1, ans);
  }

  vector<int> rightSideView(BinaryTreeNode<int> *root)
  {
    vector<int> ans;

    // Safety check for empty tree
    if (root == NULL)
      return ans;

    // Start modified DFS at depth level 0
    dfs(root, 0, ans);

    return ans;
  }
};

int main()
{
  return 0;
}
