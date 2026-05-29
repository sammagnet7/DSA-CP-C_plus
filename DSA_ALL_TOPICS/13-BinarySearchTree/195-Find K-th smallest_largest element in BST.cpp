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

1. Title: Find K-th smallest element in BST

Links:
https://takeuforward.org/data-structure/kth-largest-smallest-element-in-binary-search-tree/
https://takeuforward.org/plus/dsa/problems/kth-smallest-and-largest-element-in-bst?tab=editorial
https://leetcode.com/problems/kth-smallest-element-in-a-bst/


Problem statement:
Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

Examples:
  Example 1:
  Input: root = [3,1,4,null,2], k = 1

            (3)
          /   \
        (1)   (4)
          \
          (2)

  Output: 1

  Example 2:
  Input: root = [5,3,6,2,4,null,null,1], k = 3

            (5)
            /   \
          (3)   (6)
          / \
        (2) (4)
        /
      (1)

  Output: 3


Constraints:
  The number of nodes in the tree is n.
  1 <= k <= n <= 10^4
  0 <= Node.val <= 10^4

---

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?

Ans:
      Augmented BST Approach (Optimal)
      Idea:  Each node maintains a leftCount — the number of nodes in its left subtree.
      Node structure:

        struct AugTreeNode {
            int val;
            int leftCount;  // number of nodes in the left subtree
            AugTreeNode *left, *right;

            AugTreeNode(int x) : val(x), leftCount(0), left(NULL), right(NULL) {}
        };

      kth Smallest Query: O(log N)

      At each step, compare k with leftCount + 1.
        If k == leftCount + 1: current node is kth smallest.
        If k <= leftCount: move to left subtree.
        If k > leftCount + 1: move to right with k = k - leftCount - 1.

      Insert/Delete: O(log N)
        During insertion or deletion, update the leftCount accordingly while traversing.

      Benefits:
        kthSmallest(): O(log N) average time
        insert/delete: O(log N) with maintenance
        Efficient for dynamic BSTs with many modifications.

---

Follow-up :
  Try to do it in O(1) space.

  Ans: Here we can use Morris travarsal to do the Inorder travarsal in O(1).


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Find K-th largest element in BST

Links:
https://takeuforward.org/data-structure/kth-largest-smallest-element-in-binary-search-tree/
https://takeuforward.org/plus/dsa/problems/kth-smallest-and-largest-element-in-bst?tab=editorial
https://www.naukri.com/code360/problems/kth-largest-element-in-bst_4414080?leftPanelTabValue=PROBLEM


Problem statement:
Given the root node of a Binary Search Tree (BST), you have to return the Kth largest element in the BST.


Examples:
  Example1:
    If K is 4 and the tree is depicted by the following image then,

            (2)
          /   \
        (1)   (4)
              /
            (3)

    The 4th largest element in the given BST is 1. So the output will be 1.


  Example2:
    For the second case -

                     (2)
                    /   \
                  (1)   (7)
                        /
                      (3)
                        \
                        (4)

    K is 3 and the tree is depicted by the following image then,
    The 3rd largest element in the given BST is 3. So the output will be 3.



Constraints :
  1 <= T <= 100
  1 <= N <= 5 * 10^3
  1 <= K <= N
  0 <= X <= 10^9
  Where ‘X’ is the value at the node and ‘N’ is the no. of nodes in given BST.


---

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth largest frequently, how would you optimize?

Ans:  Using Augmented BST
      Idea: We augment each node to store the size of its subtree.
      How?
      We define a new node:
                struct Node {
                    int data;
                    int subtreeSize;
                    Node* left;
                    Node* right;

                    Node(int val) {
                        data = val;
                        subtreeSize = 1;
                        left = right = NULL;
                    }
                };

      Now whenever we insert/delete, we update subtreeSize of ancestors accordingly.

      Then, to find k-th smallest:

                int kthSmallest(Node* root, int k) {

                    int leftSize = (root->left) ? root->left->subtreeSize : 0;

                    if (k == leftSize + 1)
                        return root->data;
                    else if (k <= leftSize)
                        return kthSmallest(root->left, k);
                    else
                        return kthSmallest(root->right, k - leftSize - 1);
                }

      Then, to find k-th largest:

                int kthLargest(Node* root, int k) {

                    int rightSize = (root->right) ? root->right->subtreeSize : 0;

                    if (k == rightSize + 1)
                        return root->data;
                    else if (k <= rightSize)
                        return kthLargest(root->right, k);
                    else
                        return kthLargest(root->left, k - rightSize - 1);
                }

      Insert/Delete also becomes O(log N) with size updates. This assumes the tree is self-balancing.

---

Follow-up :
  Try to do it in O(1) space.

  Ans: Here we can use Morris travarsal to do the Inorder travarsal in O(1).


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------
// 1. Title: Find K-th smallest element in BST
//-------------------------------------------------------------------------------

// Definition for a binary tree node (assumed context)
struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
  // Helper function keeps state completely localized
  int inorderHelper(TreeNode *node, int &k)
  {

    // Base case: hit a leaf
    if (node == nullptr)
    {
      return -1;
    }

    // 1. Search the left subtree
    int leftResult = inorderHelper(node->left, k);
    if (leftResult != -1)
    {
      return leftResult; // Early exit: bubble the answer up!
    }

    // 2. Process the current node
    k--; // We found the next smallest element
    if (k == 0)
    {
      return node->val; // Jackpot!
    }

    // 3. Search the right subtree
    return inorderHelper(node->right, k);
  }

public:
  /**
   * ============================================================================
   * BST ALGORITHM: K-TH SMALLEST ELEMENT (RECURSIVE INORDER)
   * ============================================================================
   * * [THE MENTAL MODEL]
   * We perform an Inorder Traversal (Left -> Root -> Right). By passing `k`
   * by reference, we decrement it every time we "process" a root node.
   * The exact moment `k` hits 0, that node is our answer. We return it and
   * let it bubble straight up the call stack, ignoring the rest of the tree.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H + k) -> We traverse down the left spine O(H),
   * then process strictly k nodes. We early-exit before visiting O(N).
   * - SPACE COMPLEXITY: O(H) -> Recursion call stack overhead.
   * ============================================================================
   */
  int kthSmallest(TreeNode *root, int k)
  {
    // k is passed by reference, so it decrements globally across all frames
    return inorderHelper(root, k);
  }

  /**
   * ============================================================================
   * BST ALGORITHM: K-TH SMALLEST ELEMENT (ITERATIVE INORDER) [RECOMMENDED]
   * ============================================================================
   * * [THE MENTAL MODEL]
   * An Inorder Traversal of a BST visits nodes in strictly ascending order.
   * We use an explicit stack to simulate the traversal:
   * 1. Drill down the left side of the tree as far as possible (finding the mins).
   * 2. Pop a node, process it (decrement our k counter).
   * 3. If k hits 0, we found our target. Return immediately.
   * 4. Otherwise, step right and repeat.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H + k)
   * We traverse down to the smallest element (Height of tree, H), and then
   * process k elements. We do NOT traverse the entire O(N) tree unless k == N.
   * - SPACE COMPLEXITY: O(H)
   * The stack will hold at most the height of the tree at any given time.
   * ============================================================================
   */
  int kthSmallest(TreeNode *root, int k)
  {
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while (curr != nullptr || !st.empty())
    {

      // Step 1: Go as far left as mathematically possible
      while (curr != nullptr)
      {
        st.push(curr);
        curr = curr->left;
      }

      // Step 2: Pop the smallest available element
      curr = st.top();
      st.pop();

      // Step 3: Process the node
      k--;
      if (k == 0)
      {
        return curr->val; // Found it! Abort traversal.
      }

      // Step 4: Move to the right subtree to find the next slightly larger values
      curr = curr->right;
    }

    return -1; // Should not be reached if k is valid
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Find K-th largest element in BST
//-------------------------------------------------------------------------------

struct Node
{
  int data;
  Node *left;
  Node *right;

  Node(int data)
  {
    this->data = data;
    left = NULL;
    right = NULL;
  }

  ~Node()
  {
    if (left != NULL)
    {
      delete left;
    }
    if (right != NULL)
    {
      delete right;
    }
  }
};

class Solution
{
public:
  /**
   * ============================================================================
   * BST ALGORITHM: K-TH LARGEST ELEMENT (ITERATIVE REVERSE INORDER)
   * ============================================================================
   * * [THE MENTAL MODEL]
   * A standard Inorder Traversal (Left -> Root -> Right) yields elements in
   * ascending order. Therefore, a Reverse Inorder Traversal (Right -> Root -> Left)
   * yields elements in strictly descending order.
   * We use an explicit stack to simulate this traversal:
   * 1. Drill down the right side of the tree as far as mathematically possible
   * to find the absolute largest elements.
   * 2. Pop a node and process it (decrement our k counter).
   * 3. If k hits 0, we found our target! Return immediately to early-exit.
   * 4. Otherwise, step left to find the next slightly smaller values and repeat.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(H + K)
   * We traverse down to the largest element (which takes O(H) time, where H is
   * the height of the tree), and then we process exactly K elements. We do NOT
   * traverse the entire O(N) tree unless K == N.
   * - SPACE COMPLEXITY: O(H)
   * The stack will hold at most the height of the tree's worth of nodes at any
   * given time. (In a balanced tree, O(log N). In a skewed tree, O(N)).
   * ============================================================================
   */
  int KthLargest(Node *root, int k)
  {

    stack<Node *> st;
    Node *cur = root;

    // Traverse until we run out of nodes and the stack is empty
    while (cur != nullptr || !st.empty())
    {

      // Step 1: Go as far right as possible to find the maximums
      while (cur != nullptr)
      {
        st.push(cur);
        cur = cur->right;
      }

      // Step 2: Pop the largest available element from the stack
      cur = st.top();
      st.pop();

      // Step 3: Process the node
      --k;
      if (k == 0)
      {
        return cur->data; // Found it! Abort traversal and return.
      }

      // Step 4: Move to the left subtree to find slightly smaller values
      cur = cur->left;
    }

    // Should not be reached if K is valid (1 <= K <= N)
    return -1;
  }

  /**
   * ============================================================================
   * BST ALGORITHM: K-TH LARGEST ELEMENT (REVERSE MORRIS) [SPACE OPTIMIZED: O(1)]
   * ============================================================================
   * * [THE MENTAL MODEL]
   * We use a Reverse Morris Traversal (Right -> Root -> Left) to achieve O(1)
   * space without recursion. We build temporary bridges from the leftmost nodes
   * of the right subtrees back to the current nodes.
   * * * [COMPLEXITY ANALYSIS]
   * - TIME COMPLEXITY: O(N)
   * Because we must allow the traversal to finish completely to destroy all
   * temporary bridges, we traverse every edge at most 3 times.
   * - SPACE COMPLEXITY: O(1)
   * Zero stack memory used.
   * ============================================================================
   */
  int KthLargest(Node *root, int k)
  {

    int ans = -1;
    Node *cur = root;

    while (cur != nullptr)
    {

      // Case 1: No right child. Process and move left.
      if (cur->right == nullptr)
      {
        --k;
        if (k == 0)
        {
          ans = cur->data; // Record answer, but DO NOT return yet!
        }

        cur = cur->left;
      }

      // Case 2: Right child exists. Find successor and manage bridges.
      else
      {
        Node *tmp = cur->right;

        // BUG FIX 1: Use && (AND). Stop if we hit null OR the bridge.
        while (tmp->left != nullptr && tmp->left != cur)
        {
          tmp = tmp->left;
        }

        // Subcase A: Bridge doesn't exist. Build it and go right.
        if (tmp->left == nullptr)
        {
          tmp->left = cur;
          cur = cur->right;
        }

        // Subcase B: Bridge exists. Destroy it, process, and go left.
        else
        {
          // BUG FIX 2: Always destroy the bridge first!
          tmp->left = nullptr;

          --k;
          if (k == 0)
          {
            ans = cur->data; // Record answer, but let traversal finish
          }

          cur = cur->left;
        }
      }
    }

    return ans;
  }
};

int main()
{
  return 0;
}
