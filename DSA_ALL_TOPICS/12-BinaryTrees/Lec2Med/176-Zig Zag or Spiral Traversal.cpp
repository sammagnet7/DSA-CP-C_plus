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

1. Title: Zig Zag or Spiral Traversal

Links:
https://takeuforward.org/data-structure/zig-zag-traversal-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/zig-zag-or-spiral-traversal?tab=editorial
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/


Problem statement:
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

Examples:
  Example 1:
  Input: root = [3,9,20,null,null,15,7]
  Output: [[3],[20,9],[15,7]]

  Example 2:
  Input: root = [1]
  Output: [[1]]

  Example 3:
  Input: root = []
  Output: []



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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Zig Zag or Spiral Traversal
  //-------------------------------------------------------------------------------

  // Optimal approach:
  // create a leftToRight flag to track the traversal direction. When leftToRight is true, nodes are inserted into the level vector from left to right; when false, they are inserted from right to left.
  //
  // Time: O(N)
  // Space: O(N), last level could at most hold N/2 nodes
  vector<vector<int>> zigzagLevelOrder(TreeNode *root)
  {

    vector<vector<int>> ans;

    if (root == NULL)
      return ans;

    queue<TreeNode *> q;

    q.push(root);

    bool isLtoR = true;

    while (!q.empty())
    {

      int q_size = q.size();
      vector<int> tmp(q_size);

      for (int i = 0; i < q_size; i++)
      {

        TreeNode *cur = q.front();
        q.pop();

        if (isLtoR)
        {
          tmp[i] = cur->val;
        }
        else
        {
          tmp[q_size - i - 1] = cur->val; // push in reverse order
        }

        if (cur->left != NULL)
          q.push(cur->left);
        if (cur->right != NULL)
          q.push(cur->right);
      }

      ans.push_back(tmp);
      isLtoR = !isLtoR;
    }

    return ans;
  }
};

int main()
{
  return 0;
}
