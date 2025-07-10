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

2. Title:

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
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template <typename T=int>
struct TreeNodeN
{
  int data;
  TreeNodeN *left;
  TreeNodeN *right;
  TreeNodeN() : data(0), left(nullptr), right(nullptr) {}
  TreeNodeN(int x) : data(x), left(nullptr), right(nullptr) {}
  TreeNodeN(int x, TreeNodeN *left, TreeNodeN *right) : data(x), left(left), right(right) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Path In A Tree
  //-------------------------------------------------------------------------------
  int traverse(TreeNodeN<int> *node, int x, vector<int> &v)
  {
    if (node == NULL)
      return 0;

    if (node->data == x)
    {
      v.push_back(x);
      return 1;
    }

    if (traverse(node->left, x, v) == 1)
    {
      v.push_back(node->data);
      return 1;
    }

    if (traverse(node->right, x, v) == 1)
    {
      v.push_back(node->data);
      return 1;
    }

    return 0;
  }

  vector<int> pathInATree(TreeNodeN<int> *root, int x)
  {
    // Write your code here.
    vector<int> ans;

    traverse(root, x, ans);

    reverse(ans.begin(), ans.end());
    return ans;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Binary Tree Paths
  //-------------------------------------------------------------------------------

  void traverse(TreeNode *node, string &s, vector<string> &ans)
  {

    int prevSize = s.size();

    string num = to_string(node->val);
    s.append(num);

    if (node->left == NULL && node->right == NULL)
    {
      ans.push_back(s);
      s.resize(prevSize);
      return;
    }

    s.append("->");

    if (node->left != NULL)
      traverse(node->left, s, ans);

    if (node->right != NULL)
      traverse(node->right, s, ans);

    s.resize(prevSize);
  }

  vector<string> binaryTreePaths(TreeNode *root)
  {
    vector<string> ans;
    if (root == NULL)
      return ans;

    string tmp = "";
    traverse(root, tmp, ans);

    return ans;
  }
};

int main()
{
  return 0;
}
