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

============================================================================--------------------
============================================================================--------------------

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

//============================================================================
// 1. Title: DFS: Pre_In_Post order traversal :: Recursive approach
//============================================================================

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
  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N). Worst case: O(N)
  vector<int> preorderTraversal(TreeNode *root)
  {
    vector<int> ans;

    // recursion call
    preorderTraversal_rec(root, ans);

    return ans;
  }

  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N). Worst case: O(N)
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> ans;

    // recursion call
    inorderTraversal_rec(root, ans);

    return ans;
  }

  // Optimal solution
  // Time: O(3N) where N is total number of nodes in the tree
  // Space: O(h) where h is the height of the tree ~ O(Log N). Worst case: O(N)
  vector<int> postorderTraversal(TreeNode *root)
  {
    vector<int> ans;

    // recursion call
    postorderTraversal_rec(root, ans);

    return ans;
  }
};

//============================================================================
// 2. Title: DFS: Pre_In_Post order traversal :: Iterative approach
//============================================================================

class Solution_Iter
{
public:
  /**
   * ---------------------------------------------
   * 1. PRE-ORDER TRAVERSAL (Root -> Left -> Right)
   * ---------------------------------------------
   * Logic: Standard Stack Approach.
   * Since a stack is LIFO (Last In, First Out), we must push the RIGHT child
   * first, then the LEFT child. This ensures the Left child is popped and
   * processed before the Right child.
   *
   * Time: O(N)  -> Every node is pushed and popped exactly once.
   * Space: O(H) -> Where H is tree height. O(log N) average, O(N) worst-case.
   */
  vector<int> preorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    stack<TreeNode *> st;

    if (root)
    {
      st.push(root);
    }

    while (!st.empty())
    {
      TreeNode *cur = st.top();
      st.pop();

      ans.push_back(cur->val); // Process Root

      // Push Right first, so Left sits on top of the stack
      if (cur->right)
        st.push(cur->right);
      if (cur->left)
        st.push(cur->left);
    }

    return ans;
  }

  /**
   * ---------------------------------------------
   * 2. IN-ORDER TRAVERSAL (Left -> Root -> Right)
   * ---------------------------------------------
   * Logic: Call-Stack Simulation (State Machine).
   * We use an integer `term` to represent the CPU instruction pointer:
   * - State 1: We just arrived at this node. Push it to state 2, and go Left.
   * - State 2: We returned from the Left child. Process this node, and go Right.
   *
   * Time: O(N)  -> We visit each node twice (State 1 and State 2).
   * Space: O(H) -> Maximum call stack depth. O(log N) avg, O(N) worst-case.
   */
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    stack<pair<TreeNode *, int>> st;

    if (root)
    {
      st.push({root, 1}); // Start in State 1
    }

    while (!st.empty())
    {
      auto [cur, term] = st.top();
      st.pop();

      if (term == 1)
      {
        // State 1: Prepare to visit left. Upgrade self to State 2.
        st.push({cur, 2});

        if (cur->left)
        {
          st.push({cur->left, 1});
        }
      }
      else if (term == 2)
      {
        // State 2: Left subtree is done. Process current node.
        ans.push_back(cur->val);

        // Prepare to visit right subtree.
        if (cur->right)
        {
          st.push({cur->right, 1});
        }
      }
    }

    return ans;
  }

  /**
   * -----------------------------------------------
   * 3. POST-ORDER TRAVERSAL (Left -> Right -> Root)
   * -----------------------------------------------
   * Logic: Call-Stack Simulation (State Machine).
   * Exact same logic as In-Order, but we add a 3rd state because the Root is
   * processed LAST, after returning from the Right child.
   * - State 1: Arrive, upgrade to State 2, go Left.
   * - State 2: Return from Left, upgrade to State 3, go Right.
   * - State 3: Return from Right, PROCESS NODE.
   *
   * Time: O(N)  -> We visit each node three times. Constant multiplier, still O(N).
   * Space: O(H) -> O(log N) average, O(N) worst-case.
   */
  vector<int> postorderTraversal(TreeNode *root)
  {
    vector<int> ans;
    stack<pair<TreeNode *, int>> st;

    if (root)
    {
      st.push({root, 1});
    }

    while (!st.empty())
    {
      auto [cur, term] = st.top();
      st.pop();

      if (term == 1)
      {
        // State 1: Go Left
        st.push({cur, 2});
        if (cur->left)
          st.push({cur->left, 1});
      }
      else if (term == 2)
      {
        // State 2: Go Right
        st.push({cur, 3});
        if (cur->right)
          st.push({cur->right, 1});
      }
      else if (term == 3)
      {
        // State 3: Process Node
        ans.push_back(cur->val);
      }
    }

    return ans;
  }

  /**
   * ------------------------------------------------------
   * 4. POST-ORDER TRAVERSAL (The "Reverse Pre-Order" Hack)
   * ------------------------------------------------------
   * Logic: Standard Stack + Array Reversal.
   * Post-order is (Left -> Right -> Root).
   * If we do a modified Pre-order of (Root -> Right -> Left), we can simply
   * reverse the final array to get (Left -> Right -> Root).
   *
   * Time: O(N)  -> O(N) for traversal + O(N) for reversal.
   * Space: O(H) -> For the stack.
   */
  vector<int> postorderTraversal_rev(TreeNode *root)
  {
    vector<int> ans;
    stack<TreeNode *> st;

    // BUG FIX: Must return 'ans' (vector), not a void return.
    if (root == nullptr)
      return ans;

    st.push(root);

    while (!st.empty())
    {
      TreeNode *cur = st.top();
      st.pop();

      ans.push_back(cur->val); // Process Root

      // Push Left first, so Right sits on top (Root -> Right -> Left)
      if (cur->left != nullptr)
        st.push(cur->left);
      if (cur->right != nullptr)
        st.push(cur->right);
    }

    // Reverse to get Post-order (Left -> Right -> Root)
    reverse(ans.begin(), ans.end());

    return ans;
  }
};

int main()
{
  return 0;
}
