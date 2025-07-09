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

1. Title: Height of a Binary Tree


Links:
https://takeuforward.org/data-structure/maximum-depth-of-a-binary-tree/
https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=14
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/maximum-depth-in-bt
https://leetcode.com/problems/maximum-depth-of-binary-tree/description/



Problem statement:
Given root of the binary tree, return its maximum depth.

A binary tree's maximum depth is number of nodes along the longest path from from root node down to the farthest node.

Examples:
  Input : root = [1, 2, 3, null, null, null , 6]
  Output : 3
  Explanation : The path from root node 1 to node with value 6 has maximum depth with 3 nodes along path.

  Input : root = [3, 9, 20, null, null, 15 , 7]
  Output : 3
  Explanation : The path from root node 3 to node with value 15 has maximum depth with 3 nodes along path.
  There exists other paths to reach the solution.



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
  // 1. Title: Height of a Binary Tree
  //-------------------------------------------------------------------------------
  // Approach1:

  // Optimal approach: using recursion
  // Time: O(N)
  // Space: O(h) i.e. auxiliary stack space
  int maxDepth(TreeNode *root)
  {

    if (root == NULL)
      return 0;

    int lLen = maxDepth(root->left);
    int rLen = maxDepth(root->right);

    return (1 + max(lLen, rLen));
  }

  // Approach2:

  // // Optimal approach: using iteration
  // // Time: O(N)
  // // Space: O(N/2) because at last level N/2 leaf nodes stays
  // int maxDepth(TreeNode* root) {

  //     if (root == NULL)
  //         return 0;

  //     int ans = 0;

  //     queue<TreeNode *> q;    // O(N/2)
  //     q.push(root);

  //     while (!q.empty())
  //     {
  //         ans++;

  //         int preLvlSize = q.size();

  //         for (int i = 0; i < preLvlSize; i++)
  //         {
  //             TreeNode *node = q.front();
  //             q.pop();

  //             if (node->left != NULL)
  //                 q.push(node->left);
  //             if (node->right != NULL)
  //                 q.push(node->right);
  //         }
  //     }

  //     return ans;
  // }
};

int main()
{
  return 0;
}
