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

1. Title: Maximum path sum

Links:
https://takeuforward.org/data-structure/maximum-sum-path-in-binary-tree/
https://takeuforward.org/plus/dsa/problems/zig-zag-or-spiral-traversal?tab=editorial
https://leetcode.com/problems/binary-tree-maximum-path-sum/description/


Problem statement:
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
The path sum of a path is the sum of the node's values in the path.
Given the root of a binary tree, return the maximum path sum of any non-empty path.

Examples:
  Example 1:
  Input: root = [1,2,3]
  Output: 6
  Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

  Example 2:
  Input: root = [-10,9,20,null,null,15,7]
  Output: 42
  Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.


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
  // 1. Title: Maximum path sum
  //-------------------------------------------------------------------------------

  // O(N)
  int _maxPathSum(TreeNode *root, int &maxPathSum)
  {

    if (root == NULL)
      return 0;

    int lPathSum = _maxPathSum(root->left, maxPathSum);
    int rPathSum = _maxPathSum(root->right, maxPathSum);

    int maxPathCurvingAtMe = lPathSum + root->val + rPathSum; // ⌒
    maxPathSum = max(maxPathSum, maxPathCurvingAtMe);

    int maxPathThroughMe = root->val + max(lPathSum, rPathSum); // / \

    return (maxPathThroughMe >= 0) ? maxPathThroughMe : 0;
  }

  
  // Optimal approach
  // Approach:

  //  Begin by defining a recursive function designed to calculate the maximum path sum for each subtree rooted at a given node. If the current node is null, return 0, as there is no valid path through a null node.
  //  Proceed by calculating the maximum path sum for both the left and right subtrees. If the path sum for either subtree is negative, it should be disregarded, as including it would decrease the overall sum. This can be achieved by taking the maximum of 0 and the calculated path sum for each subtree.
  //  For each node, compute the potential maximum path sum that passes through the node and its children. This sum includes the node itself and the maximum path sums from both subtrees. If this value exceeds the current global maximum sum, update the global maximum to reflect this new higher value.
  //  Finally, return the maximum path sum for the current node, considering only one of its subtrees. This step ensures that when the function backtracks up the tree, only the highest path sum from either the left or right subtree is propagated upward, maintaining the integrity of the overall maximum path sum calculation.
  // Time: O(N)
  // Space: O(h) Recursive Stack Auxiliary Space
  int maxPathSum(TreeNode *root)
  {

    int maxPathSum = INT_MIN;

    _maxPathSum(root, maxPathSum);

    return maxPathSum;
  }
};

int main()
{
  return 0;
}
