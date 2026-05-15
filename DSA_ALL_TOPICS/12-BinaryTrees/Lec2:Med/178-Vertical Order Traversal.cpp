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

1. Title: Vertical Order Traversal

Links:
https://takeuforward.org/data-structure/vertical-order-traversal-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/vertical-order-traversal?tab=editorial
https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/


Problem statement:
Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
Return the vertical order traversal of the binary tree.

Examples:
  Example 1:
  Input: root = [3,9,20,null,null,15,7]
  Output: [[9],[3,15],[20],[7]]
  Explanation:
  Column -1: Only node 9 is in this column.
  Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
  Column 1: Only node 20 is in this column.
  Column 2: Only node 7 is in this column.

  Example 2:
  Input: root = [1,2,3,4,5,6,7]
  Output: [[4],[2],[1,5,6],[3],[7]]
  Explanation:
  Column -2: Only node 4 is in this column.
  Column -1: Only node 2 is in this column.
  Column 0: Nodes 1, 5, and 6 are in this column.
            1 is at the top, so it comes first.
            5 and 6 are at the same position (2, 0), so we order them by their value, 5 before 6.
  Column 1: Only node 3 is in this column.
  Column 2: Only node 7 is in this column.

  Example 3:
  Input: root = [1,2,3,4,6,5,7]
  Output: [[4],[2],[1,5,6],[3],[7]]
  Explanation:
  This case is the exact same as example 2, but with nodes 5 and 6 swapped.
  Note that the solution remains the same since 5 and 6 are in the same location and should be ordered by their values.



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
  // 1. Title: Vertical Order Traversal
  //-------------------------------------------------------------------------------
  // O(N)
  void traverse(TreeNode *node, map<int, vector<pair<int, int>>> &mp, int rowLvl, int colLvl)
  {
    if (node == NULL)
      return;

    mp[colLvl].push_back({rowLvl, node->val});

    if (node->left != NULL)
    {
      traverse(node->left, mp, rowLvl + 1, colLvl - 1);
    }
    if (node->right != NULL)
    {
      traverse(node->right, mp, rowLvl + 1, colLvl + 1);
    }
  }

  // Optmal approach: Using Pre-order traversal
  //
  //  Time: O(N)
  //  Space: O(N)
  vector<vector<int>> verticalTraversal(TreeNode *root)
  {
    map<int, vector<pair<int, int>>> mp; // <col, <row, val> >

    vector<vector<int>> ans;

    if (root == NULL)
      return ans;

    traverse(root, mp, 0, 0); // Do the traversal

    // Saving the ans to vector
    for (auto it = mp.begin(); it != mp.end(); it++)
    { // O(N)

      vector<pair<int, int>> l = it->second;

      sort(l.begin(), l.end());

      vector<int> tmp;

      for (auto i : l)
      {
        tmp.push_back(i.second);
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
