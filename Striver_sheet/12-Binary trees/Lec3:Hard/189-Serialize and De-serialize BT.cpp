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

1. Title: Serialize and De-serialize BT

Links:
https://takeuforward.org/data-structure/serialize-and-deserialize-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/serialize-and-de-serialize-bt?tab=editorial
https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/


Problem statement:
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Examples:
  Example 1:
  Input: root = [1,2,3,null,null,4,5]
  Output: [1,2,3,null,null,4,5]

  Example 2:
  Input: root = []
  Output: []


Constraints:
The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000


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

template <typename T>
class BinaryTreeNode
{
public:
  T data;
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;

  BinaryTreeNode(T data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Serialize and De-serialize BT
  //-------------------------------------------------------------------------------

  /**
   * Method: serialize
   * -----------------
   * Serializes a binary tree into a single string using level-order traversal (BFS).
   *
   * Approach:
   * - Perform BFS starting from root.
   * - For each node:
   *    - Add its value to the result string.
   *    - If the node has left/right children, enqueue them and add their values.
   *    - If a child is null, append a special marker "#" to denote null.
   *
   * Output Format:
   * - Values separated by commas.
   * - Nulls represented using "#".
   *
   * Example:
   * For tree:      1
   *               / \
   *              2   3
   *                 / \
   *                4   5
   * Serialized string: "1,2,3,#,#,4,5,#,#,#,#"
   *
   * Time Complexity: O(N) — each node visited once.
   * Space Complexity: O(N) — queue for BFS and result string size.
   */
  string serialize(TreeNode *root)
  {
    if (root == NULL)
      return "";

    // Start result with root value
    string ret = to_string(root->val);

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
      int s = q.size();

      for (int i = 0; i < s; i++)
      {
        TreeNode *cur = q.front();
        q.pop();

        // Process left child
        if (cur->left)
        {
          q.push(cur->left);
          ret.append("," + to_string(cur->left->val));
        }
        else
        {
          ret.append(",#"); // null marker
        }

        // Process right child
        if (cur->right)
        {
          q.push(cur->right);
          ret.append("," + to_string(cur->right->val));
        }
        else
        {
          ret.append(",#");
        }
      }
    }

    // Optional debug print
    cout << ret;
    return ret;
  }

  /**
   * Method: deserialize
   * -------------------
   * Deserializes a string back into a binary tree using BFS.
   *
   * Approach:
   * - Use a stringstream to split values by ','.
   * - First value is root.
   * - Use a queue to keep track of nodes to attach left/right children to.
   * - For each node, read next two values:
   *    - If not "#", create left/right node and enqueue it.
   *
   * Time Complexity: O(N) — each node created once.
   * Space Complexity: O(N) — queue + tree nodes.
   */
  TreeNode *deserialize(string data)
  {
    if (data.empty())
      return NULL;

    stringstream ss(data);
    string s;

    // First value is the root node
    getline(ss, s, ',');
    TreeNode *root = new TreeNode(stoi(s));

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
      TreeNode *cur = q.front();
      q.pop();

      // Process left child
      if (getline(ss, s, ',') && s != "#")
      {
        TreeNode *node = new TreeNode(stoi(s));
        cur->left = node;
        q.push(node);
      }

      // Process right child
      if (getline(ss, s, ',') && s != "#")
      {
        TreeNode *node = new TreeNode(stoi(s));
        cur->right = node;
        q.push(node);
      }
    }

    return root;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Construct a BT from Postorder and Inorder
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
