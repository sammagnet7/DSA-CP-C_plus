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

1. Title: Maximum Width of BT

Links:
https://takeuforward.org/data-structure/maximum-width-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/maximum-width-of-bt?tab=editorial
https://leetcode.com/problems/maximum-width-of-binary-tree/


Problem statement:
Given the root of a binary tree, return the maximum width of the given tree.
The maximum width of a tree is the maximum width among all levels.
The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
It is guaranteed that the answer will in the range of a 32-bit signed integer.

Examples:
  Example 1:
  Input: root = [1,3,2,5,3,null,9]
  Output: 4
  Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

  Example 2:
  Input: root = [1,3,2,5,null,null,9,6,null,7]
  Output: 7
  Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

  Example 3:
  Input: root = [1,3,2,5]
  Output: 2
  Explanation: The maximum width exists in the second level with length 2 (3,2).

Constraints:
The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:


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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Maximum Width of BT
  //-------------------------------------------------------------------------------
  // Optimal approach: Use noremalised indexing to count nodes per level including missing in between nodes
  //
  // Time: O(N)
  // Space: O(N/2)
  int widthOfBinaryTree(TreeNode *root)
  {
    if (root == NULL)
      return 0;

    queue<pair<TreeNode *, int>> q; // O(N/2):  <Node* , normalised-index>
    q.push({root, 0});

    int maxWidth = 1;

    while (!q.empty()) // O(N)
    {
      // maxWidth = max(maxWidth, curWidth);
      int q_size = q.size();
      int min_lvlIdx = INT_MAX;
      int max_lvlIdx = INT_MIN;

      for (int i = 0; i < q_size; i++)
      {
        TreeNode *curN = q.front().first;
        int cur_id = q.front().second;
        q.pop();

        min_lvlIdx = min(min_lvlIdx, cur_id);
        max_lvlIdx = max(max_lvlIdx, cur_id);

        // int norm_cur_id = (cur_id-min_lvlIdx);

        long long norm_cur_id = cur_id - min_lvlIdx;

        if (curN->left)
        {
          q.push({curN->left, (2 * norm_cur_id + 1)});
        }
        if (curN->right)
        {
          q.push({curN->right, (2 * norm_cur_id + 2)});
        }
      }

      int lvlWidth = (max_lvlIdx - min_lvlIdx + 1);
      maxWidth = max(maxWidth, lvlWidth);
    }

    return maxWidth;
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
