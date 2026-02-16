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

1. Title: Diameter of Binary Tree

Links:
https://takeuforward.org/data-structure/calculate-the-diameter-of-a-binary-tree/
https://www.youtube.com/watch?v=Rezetez59Nk&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=16
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/diameter-of-binary-tree
https://leetcode.com/problems/diameter-of-binary-tree/description/


Problem statement:
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them.

Examples:
  Example 1:
  Input: root = [1,2,3,4,5]
  Output: 3
  Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

  Example 2:
  Input: root = [1,2]
  Output: 1



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
  // 1. Title: Diameter of Binary Tree
  //-------------------------------------------------------------------------------
  // O(N)
  int maxDepth(TreeNode *root, int &longestPath)
  {

    if (root == NULL)
      return 0;

    int lLen = maxDepth(root->left, longestPath);
    int rLen = maxDepth(root->right, longestPath);

    longestPath = max(longestPath, (lLen + rLen));

    return (1 + max(lLen, rLen));
  }

  //
  // Optimal approach
  // Time: O(N) because traversing each nodes ones
  // Space: O(h) i.e. aux stack space
  int diameterOfBinaryTree(TreeNode *root)
  {

    int longestPath = 0;

    maxDepth(root, longestPath);

    return longestPath;
  }
};

int main()
{
  return 0;
}
