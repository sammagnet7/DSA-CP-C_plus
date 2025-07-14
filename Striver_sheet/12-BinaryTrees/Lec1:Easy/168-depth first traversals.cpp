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

1. Title: DFS: Pre_In_Post order traversal :: Recursive approach

Links:
https://takeuforward.org/data-structure/preorder-traversal-of-binary-tree/
https://takeuforward.org/data-structure/inorder-traversal-of-binary-tree/
https://takeuforward.org/data-structure/post-order-traversal-of-binary-tree/

https://leetcode.com/problems/binary-tree-preorder-traversal/description/
https://leetcode.com/problems/binary-tree-inorder-traversal/description/
https://leetcode.com/problems/binary-tree-postorder-traversal/description/

Problem statement:
Given the root of a binary tree, return the preorder, inorder, postorder traversal of its nodes' values.
Note: User Recursive approach


INPUT::::::


OUTPUT::::::

---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------

2. Title: DFS: Pre_In_Post order traversal :: Iterative approach

Links:
Pre:
https://takeuforward.org/data-structure/iterative-preorder-traversal-of-binary-tree
https://www.youtube.com/watch?v=Bfqd8BsPVuw&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=9
https://leetcode.com/problems/binary-tree-preorder-traversal/description/

In:
https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=10
https://leetcode.com/problems/binary-tree-inorder-traversal/description/

Post:
https://takeuforward.org/plus/dsa/binary-trees/theory-and-traversals/postorder-traversal?tab=editorial (reverse method and 1 stack)
https://takeuforward.org/data-structure/iterative-postorder-traversal-of-binary-tree-using-2-stack (2 stack) (same as reverse)
https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=11  (2 stack) (same as reverse)
https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=12 (single stack)
https://leetcode.com/problems/binary-tree-postorder-traversal/description/

Problem statement:
Given the root of a binary tree, return the preorder, inorder, postorder traversal of its nodes' values.
Note: User Iterative approach


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
// 1. Title: DFS: Pre_In_Post order traversal :: Recursive approach
//-------------------------------------------------------------------------------

class Solution_Rec
{
private:
  //----------
  // Pre-order
  //----------

  void preorderTraversal_rec(TreeNode *root, vector<int> &ans)
  {
    if (root == NULL)
      return;

    ans.push_back(root->val);
    preorderTraversal_rec(root->left, ans);
    preorderTraversal_rec(root->right, ans);
  }

  //----------
  // In-order
  //----------
  void inorderTraversal_rec(TreeNode *root, vector<int> &ans)
  {
    if (root == NULL)
      return;

    inorderTraversal_rec(root->left, ans);
    ans.push_back(root->val);
    inorderTraversal_rec(root->right, ans);
  }

  //------------
  // Post-order
  //------------
  void postorderTraversal_rec(TreeNode *root, vector<int> &ans)
  {
    if (root == NULL)
      return;

    postorderTraversal_rec(root->left, ans);
    postorderTraversal_rec(root->right, ans);
    ans.push_back(root->val);
  }

public:
  //
  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> preorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    preorderTraversal_rec(root, ans);
    return ans;
  }

  //
  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    inorderTraversal_rec(root, ans);
    return ans;
  }

  //
  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> postorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    postorderTraversal_rec(root, ans);
    return ans;
  }
};

//-------------------------------------------------------------------------------
// 2. Title: DFS: Pre_In_Post order traversal :: Iterative approach
//-------------------------------------------------------------------------------

class Solution_Iter
{
private:
  //----------
  // Pre-order
  //----------

  // O(N)
  void preorderTraversal_iter(TreeNode *root, vector<int> &ans)
  {

    stack<TreeNode *> st;

    // Edge case: empty tree
    if (root == nullptr)
      return;

    // Start with the root node
    st.push(root);

    while (!st.empty())
    {
      // Visit the current node (Node → Left → Right)
      TreeNode *cur = st.top();
      st.pop();

      ans.push_back(cur->val); // Process current node

      // Push right child first so that left is processed before right
      if (cur->right != NULL)
        st.push(cur->right);
      if (cur->left != NULL)
        st.push(cur->left);
    }
  }

  //----------
  // In-order
  //----------

  // O(N)
  void inorderTraversal_iter(TreeNode *root, vector<int> &ans)
  {

    stack<TreeNode *> st; // Stack to simulate recursion
    TreeNode *tmp = root; // Temporary pointer used for traversal

    // Loop continues until we've processed all nodes
    while (true)
    {

      if (tmp != NULL)
      {
        // Go as left as possible and push all nodes along the path
        st.push(tmp);
        tmp = tmp->left;
      }
      else
      {
        // If we've reached null, we backtrack using the stack
        if (st.empty())
          break; // If the stack is empty, we're done

        // Process the top node (the leftmost unprocessed node)
        TreeNode *prevN = st.top();
        st.pop();

        ans.push_back(prevN->val); // Visit the node (inorder: Left -> Node -> Right)

        // Now, traverse the right subtree of the processed node
        tmp = prevN->right;
      }
    }
  }

  //------------
  // Post-order
  //------------

  // Approach: Using single stack and reverse method
  // Postorder Traversal (Left → Right → Node)
  // To simulate this using a single stack:
  // You process in reverse: Node → Right → Left
  // Then reverse the result at the end
  //
  // Time: O(2N)  for traversing all node + reversing ans
  // Space: O(h) for stack
  void postorderTraversal_iter_rev(TreeNode *root, vector<int> &ans)
  {

    stack<TreeNode *> st;

    // Edge case: empty tree
    if (root == nullptr)
      return;

    // Start with the root node
    st.push(root);

    while (!st.empty())
    {
      // Visit the current node (Node → Right → Left)
      TreeNode *cur = st.top();
      st.pop();

      ans.push_back(cur->val); // Process current node

      // Push left child first so that right is processed before left
      if (cur->left != NULL)
        st.push(cur->left);
      if (cur->right != NULL)
        st.push(cur->right);
    }

    // Finally reverse the ans to get post order traversal
    reverse(ans.begin(), ans.end());
  }

  // Same approach as reversing pre-order using extra stack
  // O(N)
  // O(2N)
  void postorderTraversal_iter_2stack(TreeNode *root, vector<int> &ans)
  {
    stack<TreeNode *> st, st2;

    // Edge case: empty tree
    if (root == nullptr)
      return;

    // Start with the root node
    st.push(root);

    while (!st.empty())
    {
      // Visit the current node (Node → Right → Left)
      TreeNode *cur = st.top();
      st.pop();

      st2.push(cur); // Process current node

      // Push left child first so that right is processed before left
      if (cur->left != NULL)
        st.push(cur->left);
      if (cur->right != NULL)
        st.push(cur->right);
    }

    while (!st2.empty())
    {
      ans.push_back(st2.top()->val);
      st2.pop();
    }
  }

public:
  //
  // Optimal solution
  // Time: O(N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> preorderTraversal(TreeNode *root)
  {

    vector<int> ans;

    if (root == NULL)
      return ans;

    preorderTraversal_iter(root, ans);
    return ans;
  }

  //
  // Optimal solution
  // Time: O(N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    if (root == NULL)
      return ans;

    inorderTraversal_iter(root, ans);

    return ans;
  }

  //
  // Optimal solution
  // Time: O(N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N)
  vector<int> postorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    postorderTraversal_iter_rev(root, ans);
    postorderTraversal_iter_2stack(root, ans);
    return ans;
  }
};

int main()
{
  return 0;
}
