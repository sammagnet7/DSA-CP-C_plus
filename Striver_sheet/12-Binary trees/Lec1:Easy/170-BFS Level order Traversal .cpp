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

1. Title: Level order Traversal i.e. BFS

Links:
https://takeuforward.org/plus/dsa/binary-trees/theory-and-traversals/level-order-traversal?tab=editorial
https://takeuforward.org/data-structure/level-order-traversal-of-a-binary-tree/
https://www.youtube.com/watch?v=EoAsWbO7sqg&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=8
https://leetcode.com/problems/binary-tree-level-order-traversal/description/


Problem statement:
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).



Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
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
  // 1. Title: Level order Traversal i.e. BFS
  //-------------------------------------------------------------------------------

  /**
   * Approach1: Level Order Traversal using two queues (q1 and q2).
   *
   * At each level, one queue holds the current level nodes, and the other is used to queue up the next level nodes.
   * After processing all nodes in one queue, we switch to the other for the next level.
   *
   * Time Complexity: O(N)
   *     - Every node is visited exactly once.
   *
   * Space Complexity: O(N)
   *     - In the worst case, the last level of the tree may contain up to N/2 nodes (for a complete binary tree),
   *       which will all be stored in the queue. Additionally, output vector uses O(N) space.
   */
  // vector<vector<int>> levelOrder(TreeNode *root)
  // {

  //   vector<vector<int>> ans;

  //   if (root == NULL)
  //     return ans;

  //   queue<TreeNode *> q1, q2;

  //   q1.push(root);

  //   while (true)
  //   {
  //     if (q1.empty() && q2.empty())
  //       break;

  //     vector<int> tmp;

  //     if (!q1.empty())
  //     {
  //       while (!q1.empty())
  //       {
  //         tmp.push_back(q1.front()->val);

  //         if (q1.front()->left != NULL)
  //           q2.push(q1.front()->left);
  //         if (q1.front()->right != NULL)
  //           q2.push(q1.front()->right);

  //         q1.pop();
  //       }
  //     }
  //     else
  //     {
  //       while (!q2.empty())
  //       {
  //         tmp.push_back(q2.front()->val);

  //         if (q2.front()->left != NULL)
  //           q1.push(q2.front()->left);
  //         if (q2.front()->right != NULL)
  //           q1.push(q2.front()->right);

  //         q2.pop();
  //       }
  //     }

  //     ans.push_back(tmp);
  //   }
  //   return ans;
  // }

  /**
   * Approach2: Level Order Traversal using a single queue.
   *
   * At each iteration, we process all nodes in the current level by tracking the queue size (number of nodes in current level),
   * and for each node, we push its children into the queue to be processed in the next iteration (next level).
   *
   * Time Complexity: O(N)
   *     - Every node is visited exactly once.
   *
   * Space Complexity: O(N)
   *     - At worst, we store an entire level of the tree in the queue and output vector.
   */
  vector<vector<int>> levelOrder(TreeNode *root)
  {

    vector<vector<int>> ans;

    if (root == NULL)
      return ans;

    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {

      vector<int> tmp;

      int size = q.size();

      for (int i = 0; i < size; i++)
      {

        TreeNode *node = q.front();
        q.pop();

        tmp.push_back(node->val);

        if (node->left != NULL)
          q.push(node->left);
        if (node->right != NULL)
          q.push(node->right);
      }

      ans.push_back(tmp);
    }
    return ans;
  }
};

int main()
{
  return 0;
}
