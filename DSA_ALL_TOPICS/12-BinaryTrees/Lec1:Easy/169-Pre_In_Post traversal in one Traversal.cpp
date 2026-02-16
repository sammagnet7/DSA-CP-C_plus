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

1. Title: Preorder Inorder Postorder Traversals in One Traversal

Links:
https://takeuforward.org/data-structure/preorder-inorder-postorder-traversals-in-one-traversal/
https://www.youtube.com/watch?v=ySp2epYvgTE&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=13
https://www.naukri.com/code360/problems/tree-traversal_981269?leftPanelTabValue=PROBLEM

Problem statement:
Given the root of a Binary Tree, return the preorder, inorder and postorder traversal sequence of the given tree by making just one traversal.

Examples:
  Sample Input 1 :
  1 2 3 -1 -1 -1  6 -1 -1
  Sample Output 1 :
  2 1 3 6
  1 2 3 6
  2 6 3 1
  Explanation of Sample Output 1 :
  The given binary tree is shown below:

  Inorder traversal of given tree = [2, 1, 3, 6]
  Preorder traversal of given tree = [1, 2, 3, 6]
  Postorder traversal of given tree = [2, 6, 3, 1]
  Sample Input 2 :
  1 2 4 5 3 -1 -1 -1 -1 -1 -1
  Sample Output 2 :
  5 2 3 1 4
  1 2 5 3 4
  5 3 2 4 1
  Explanation of Sample Output 2 :
  The given binary tree is shown below:

  Inorder traversal of given tree = [5, 2, 3, 1, 4]
  Preorder traversal of given tree = [1, 2, 5, 3, 4]
  Postorder traversal of given tree = [5, 3, 2, 4, 1]


INPUT::::::


OUTPUT::::::


*/
struct TreeNode
{
  int data;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : data(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Preorder Inorder Postorder Traversals in One Traversal
  //-------------------------------------------------------------------------------

  void traverse_rec(TreeNode *root, vector<int> &in, vector<int> &pre, vector<int> &post)
  {

    if (root == NULL)
      return;

    pre.push_back(root->data);

    traverse_rec(root->left, in, pre, post);

    in.push_back(root->data);

    traverse_rec(root->right, in, pre, post);

    post.push_back(root->data);
  }

  /**
   * Approach:
   * - This function performs all three tree traversals (Preorder, Inorder, Postorder)
   *   in a single iterative pass using a stack.
   * - It simulates the recursive traversal by using a visit count to decide which
   *   traversal phase (pre/in/post) the node is in.
   *
   * Time Complexity: O(N) ? Each node is visited exactly three times.
   * Space Complexity: O(H) ? Stack holds nodes up to the height of the tree (H = logN for balanced tree, N for skewed).
   */
  void traverse_itr(TreeNode *root, vector<int> &in, vector<int> &pre, vector<int> &post)
  {

    // Base case: if the root is null, nothing to traverse
    if (root == NULL)
      return;

    // Stack stores a pair: (node pointer, visit count)
    stack<pair<TreeNode *, int>> st;

    // Start with root, with visit count = 1
    st.push({root, 1});

    while (!st.empty())
    {

      // Get current node and visit count
      pair<TreeNode *, int> cur = st.top();
      st.pop();

      if (cur.second == 1)
      {
        // -------- First time visiting this node --------

        // Preorder: Node is visited first (N-L-R)
        pre.push_back(cur.first->data);

        // Increase visit count for the node and push it back
        cur.second++;
        st.push(cur);

        // Go left if exists
        if (cur.first->left != NULL)
          st.push({cur.first->left, 1});
      }

      else if (cur.second == 2)
      {
        // -------- Second time visiting this node --------

        // Inorder: Left is done, now process Node (L-N-R)
        in.push_back(cur.first->data);

        // Increase visit count for the node and push it back
        cur.second++;
        st.push(cur);

        // Go right if exists
        if (cur.first->right != NULL)
          st.push({cur.first->right, 1});
      }

      else
      {
        // -------- Third time visiting this node --------

        // Postorder: Left and Right are done, now process Node (L-R-N)
        post.push_back(cur.first->data);
      }
    }
  }

  vector<vector<int>> getTreeTraversal(TreeNode *root)
  {
    // Write your code here.
    vector<int> in, pre, post;

    // traverse_rec(root, in, pre, post);

    traverse_itr(root, in, pre, post);

    return {in, pre, post};
  }
};

int main()
{
  return 0;
}
