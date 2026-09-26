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

                          3 (0,0)
                      /         \
              (1,-1) 9          20 (1,1)
                                /   \
                      (2,0)  15     7  (2,2)

    Output: [[9],[3,15],[20],[7]]
    Explanation:
    Column -1: Only node 9 is in this column.
    Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
    Column 1: Only node 20 is in this column.
    Column 2: Only node 7 is in this column.

  Example 2:
    Input: root = [1,2,3,4,5,6,7]

                      1 (0,0)
                  /           \
          (1,-1)  2             3  (1,1)
                /   \         /   \
        (2,-2) 4     5       6     7 (2,2)
                  (2,0)   (2,0)


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

                        1 (0,0)
                    /           \
            (1,-1)  2             3  (1,1)
                  /   \         /   \
          (2,-2) 4     6       5     7 (2,2)
                    (2,0)   (2,0)


    Output: [[4],[2],[1,5,6],[3],[7]]
    Explanation:
    This case is the exact same as example 2, but with nodes 5 and 6 swapped.
    Note that the solution remains the same since 5 and 6 are in the same location and should be ordered by their values.

Constraints:
  The number of nodes in the tree is in the range [1, 1000].
  0 <= Node.val <= 1000


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

//-------------------------------------------------------------------------------
// 1. Title: Vertical Order Traversal
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: VERTICAL ORDER TRAVERSAL [SLOW]
 * ============================================================================
 * * [THE INTUITION]
 * We treat the tree as a 2D grid. We use standard BFS to traverse the tree
 * level by level, assigning a (row, col) coordinate to every node.
 *
 * * [THE MECHANICS]
 * We use `map<int, map<int, multiset<int>>>` to store the nodes.
 * - The outer map automatically sorts the Columns from left to right.
 * - The inner map automatically sorts the Rows from top to bottom.
 * - The multiset automatically sorts overlapping node values in ascending order.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N log N) -> BFS takes O(N). Inserting into the map and
 *   multiset takes O(log N) time per insertion.
 * - Space Complexity: O(N) -> The map and the queue store all N nodes.
 * ============================================================================
 */
class Solution
{
public:
  vector<vector<int>> verticalTraversal(TreeNode *root)
  {
    // DS to store nodes: map<col, map<row, multiset<values>>>
    map<int, map<int, multiset<int>>> nodes;

    // Queue for BFS: holds pairs of {Node, {row, col}}
    queue<pair<TreeNode *, pair<int, int>>> q;

    if (root)
    {
      // Root is exactly at row 0, col 0
      q.push({root, {0, 0}});
    }

    while (!q.empty())
    {
      auto current = q.front();
      q.pop();

      TreeNode *node = current.first;
      int row = current.second.first;
      int col = current.second.second;

      // Insert the node's value into our grid mapping
      nodes[col][row].insert(node->val);

      // Traverse Left: go down one row, go left one col
      if (node->left)
      {
        q.push({node->left, {row + 1, col - 1}});
      }

      // Traverse Right: go down one row, go right one col
      if (node->right)
      {
        q.push({node->right, {row + 1, col + 1}});
      }
    }

    // Construct the final answer from our fully sorted map
    vector<vector<int>> ans;
    for (auto &[col, row_map] : nodes)
    {
      vector<int> current_col;
      for (auto &[row, values] : row_map)
      {
        // Append all sorted values at this exact (row, col) intersection
        for (int val : values)
        {
          current_col.push_back(val);
        }
      }
      ans.push_back(current_col);
    }

    return ans;
  }
};

/**
 * ================================================================================
 * TREE ALGORITHM: VERTICAL ORDER TRAVERSAL (OPTIMIZED BFS) [OPTIMAL] [RECOMMENDED]
 * ================================================================================
 * * [APPROACH SUMMARY]
 * The problem requires sorting nodes by Column (Left->Right), then by
 * Row (Top->Bottom), and finally by Value (if Row & Col are identical).
 *
 * Instead of storing (Row, Col) for every node, we use a Level-Order BFS:
 * 1. Column is tracked explicitly via the queue (Col - 1 for Left, Col + 1 for Right).
 * 2. Row is tracked IMPLICITLY. Because we process the queue level-by-level,
 *    every node processed in the inner `while(qSize--)` loop is guaranteed
 *    to be on the exact same Row.
 * 3. We use a temporary map for the current Row to catch any nodes that land
 *    in the same Column. We sort these collisions by value, then append them
 *    to the global map.
 *
 * * [COMPLEXITY]
 * Time: O(N log N) - Map operations and sorting overlapping nodes.
 * Space: O(N) - Queue, temporary map, and global map scale linearly with N.
 * ============================================================================
 */
class Solution
{
public:
  vector<vector<int>> verticalTraversal(TreeNode *root)
  {
    // Global map stores the final vertical layout.
    // Key: Column Index (e.g., -2, -1, 0, 1, 2).
    // Value: List of node values in that column, ordered Top-to-Bottom.
    // * std::map automatically keeps the column keys sorted from left to right.
    map<int, vector<int>> mp;

    // Queue for Level-Order BFS.
    // Stores pairs of {Current_Node, Column_Index}.
    queue<pair<TreeNode *, int>> q;

    if (root)
      q.push({root, 0}); // The root is conceptually at column 0.

    while (!q.empty())
    {
      // Snapshot the number of nodes at the current depth level (Row).
      int qSize = q.size();

      // Temporary map specifically for the CURRENT ROW.
      // Key: Column Index. Value: Nodes found at this exact (Row, Col).
      map<int, vector<int>> mp_tmp;

      // Process all nodes strictly on the current Row
      while (qSize--)
      {
        // Structured binding to extract the node and its column
        auto [cur, col] = q.front();
        q.pop();

        // Record the node's value in its respective column for this Row
        mp_tmp[col].push_back(cur->val);

        // Queue children for the NEXT Row.
        // Moving Left -> Column decreases by 1
        if (cur->left)
        {
          q.push({cur->left, col - 1});
        }
        // Moving Right -> Column increases by 1
        if (cur->right)
        {
          q.push({cur->right, col + 1});
        }
      }

      // At this point, the current Row is fully processed.
      // Now, we resolve any overlaps and add them to the global map.
      for (auto &[key, values] : mp_tmp)
      {
        // PROBLEM RULE: "There may be multiple nodes in the same row and same column.
        // In such a case, sort these nodes by their values."
        if (values.size() > 1)
        {
          sort(values.begin(), values.end());
        }

        // Append the safely sorted nodes to the bottom of the global column list.
        // std::vector::insert appends elements from 'values' into 'mp[key]'.
        mp[key].insert(mp[key].end(), values.begin(), values.end());
      }
    }

    // Construct the final 2D array format required by LeetCode.
    vector<vector<int>> ans;

    // Because 'mp' is a std::map, iterating through it guarantees we are
    // reading the columns strictly from Left to Right.
    for (auto &[key, values] : mp)
    {
      ans.push_back(values);
    }

    return ans;
  }
};

int main()
{
  return 0;
}
