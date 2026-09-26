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

1. Title:  Path In A Tree

Links:
https://takeuforward.org/data-structure/print-root-to-node-path-in-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/print-root-to-note-path-in-bt?tab=editorial
https://www.naukri.com/code360/problems/path-in-a-tree_3843990?leftPanelTabValue=PROBLEM


Problem statement:
You are given a binary tree with ‘N’ number of nodes and a node ‘X’. Your task is to print the path from the root node to the given node ‘X’.
A binary tree is a hierarchical data structure in which each node has at most two children.

Examples:
  Sample Input 1 :
  2
  1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
  7
  3 2 1 -1 -1 -1 -1
  1
  Sample output 1 :
  1 3 7
  3 1
  Explanation For Sample Output 1:
  For the first test case, the tree will be:

  Here, for ‘X ’= 7, the output will be 1 3 7.

  For the second test case, the tree will be:

  Here, for ‘X ’= 1, the output will be 3 1.
  Sample Input 2 :
  2
  1 3 -1 -1 4 2 -1 -1 -1
  1
  4 -1 1 2 -1 -1 3 -1 -1
  1
  Sample output 2 :
  1
  4 1


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Binary Tree Paths

Links:
https://takeuforward.org/data-structure/print-root-to-node-path-in-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/print-root-to-note-path-in-bt?tab=editorial
https://leetcode.com/problems/binary-tree-paths/


Problem statement:
Given the root of a binary tree, return all root-to-leaf paths in any order.
A leaf is a node with no children.

Example 1:
Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]

Example 2:
Input: root = [1]
Output: ["1"]



INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Path In A Tree
//-------------------------------------------------------------------------------

template <typename T = int>
struct TreeNodeN
{
  int data;
  TreeNodeN *left;
  TreeNodeN *right;
  TreeNodeN() : data(0), left(nullptr), right(nullptr) {}
  TreeNodeN(int x) : data(x), left(nullptr), right(nullptr) {}
  TreeNodeN(int x, TreeNodeN *left, TreeNodeN *right) : data(x), left(left), right(right) {}
};

/**
 * ============================================================================
 * TREE ALGORITHM: PATH TO GIVEN NODE (EXPLICIT SHORT-CIRCUIT DFS)
 * ============================================================================
 * * [THE INTUITION]
 * We use Pre-Order DFS to hunt for the target node 'x'. By returning a boolean
 * from our recursion, we can "catch" the success signal the moment the node
 * is found and immediately halt all further exploration.
 *
 * * [THE MECHANICS]
 * We push every visited node into our path array. We use an explicit boolean
 * `ret` to capture the result of the left branch. If it's true, we instantly
 * return it up the chain. If false, we check the right branch. If both fail,
 * we pop the current node (backtrack) and return false.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> Visits every node at most once. Halts early if target is found.
 * Space: O(H) -> Where H is the tree height. Avoids unnecessary stack frames
 * by checking if children exist before recursing.
 * ============================================================================
 */
class Solution
{
private:
  bool rec(TreeNodeN<int> *node, vector<int> &path, int x)
  {
    // Base case: Safety check for empty tree
    if (!node)
    {
      return false;
    }

    // Add the current node to our tentative path
    path.push_back(node->data);

    // Target found! Trigger the short-circuit
    if (node->data == x)
    {
      return true;
    }

    bool ret = false;

    // Traverse Left: Guarded check saves a recursion stack frame
    if (node->left)
    {
      ret = rec(node->left, path, x);
    }

    // Short-circuit: If found in the left subtree, stop immediately
    if (ret)
    {
      return ret;
    }

    // Traverse Right: Guarded check
    if (node->right)
    {
      ret = rec(node->right, path, x);
    }

    // Short-circuit: If found in the right subtree, stop immediately
    if (ret)
    {
      return ret;
    }

    // BACKTRACK: 'x' is not in this branch. Remove node and report failure.
    path.pop_back();
    return false;
  }

public:
  vector<int> pathInATree(TreeNodeN<int> *root, int x)
  {
    vector<int> path;

    // Kick off the optimized DFS
    rec(root, path, x);

    return path;
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Binary Tree Paths
//-------------------------------------------------------------------------------

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * ============================================================================
 * TREE ALGORITHM: ROOT-TO-LEAF PATHS (OPTIMIZED BACKTRACKING)
 * ============================================================================
 * * [THE INTUITION]
 * To find all paths, we use a Pre-Order DFS. However, instead of passing the
 * path string by value (which creates expensive copies at every node), we pass
 * a single string BY REFERENCE. As we travel down, we append to it. As we
 * travel back up, we "backtrack" by shrinking the string back to its previous size.
 *
 * * [THE MECHANICS]
 * C++ `string.resize()` is incredibly fast when shrinking because it merely
 * moves the null-terminator. By saving the length of the string before we
 * append a number or an arrow, we know exactly where to truncate the string
 * when we are done exploring that branch.
 *
 * * [COMPLEXITY]
 * Time: O(N) -> We visit every node exactly once. String operations are O(1).
 * Space: O(H) -> Where H is the height of the tree. The single path string
 * and the recursive call stack both scale linearly with tree depth.
 * ============================================================================
 */
class Solution
{
private:
  void rec(TreeNode *node, vector<string> &ans, string &path)
  {
    // Base case: Safety check
    if (!node)
    {
      return;
    }

    // Snapshot the current length of the string before adding this node
    int preLen = path.length();

    // Add the current node's value to our shared path
    path += to_string(node->val);

    // If we hit a leaf, record the completed path into our answer array
    if (!node->left && !node->right)
    {
      ans.push_back(path);
    }

    // Traverse Left
    if (node->left)
    {
      // Snapshot before adding the arrow
      int tmpLen = path.length();
      path += "->";

      // Explore the left branch
      rec(node->left, ans, path);

      // BACKTRACK: Remove the arrow before trying the right branch
      path.resize(tmpLen);
    }

    // Traverse Right
    if (node->right)
    {
      // Snapshot before adding the arrow
      int tmpLen = path.length();
      path += "->";

      // Explore the right branch
      rec(node->right, ans, path);

      // BACKTRACK: Remove the arrow
      path.resize(tmpLen);
    }

    // BACKTRACK: Remove the current node's value before returning to parent
    path.resize(preLen);
  }

public:
  vector<string> binaryTreePaths(TreeNode *root)
  {
    vector<string> ans;
    string path; // Shared memory buffer for the entire traversal

    // Kick off the optimized DFS
    rec(root, ans, path);

    return ans;
  }
};

int main()
{
  return 0;
}
