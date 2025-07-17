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
  Output: 1

  Example 2:
  Input: root = [5,3,6,2,4,null,null,1], k = 3
  Output: 3

Constraints:
  The number of nodes in the tree is n.
  1 <= k <= n <= 104
  0 <= Node.val <= 104


Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
Ans:
  ✅ Augmented BST Approach (Optimal)
  🧠 Idea:  Each node maintains a leftCount — the number of nodes in its left subtree.
  📦 Node structure:
    struct AugTreeNode {
        int val;
        int leftCount;  // number of nodes in the left subtree
        AugTreeNode *left, *right;
        AugTreeNode(int x) : val(x), leftCount(0), left(NULL), right(NULL) {}
    };

  🔍 kth Smallest Query: O(log N)

  At each step, compare k with leftCount + 1.
    If k == leftCount + 1: current node is kth smallest.
    If k <= leftCount: move to left subtree.
    If k > leftCount + 1: move to right with k = k - leftCount - 1.

  🧩 Insert/Delete: O(log N)
    During insertion or deletion, update the leftCount accordingly while traversing.

  🔁 Benefits:
    kthSmallest(): O(log N) average time
    insert/delete: O(log N) with maintenance
    Efficient for dynamic BSTs with many modifications.

Follow up:  Try to do it in O(1) space without using recursion.
Ans: Code below

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

Example:
  Sample Input 1 :
  2
  2 1 4 -1 -1 3 -1 -1 -1
  4
  2 1 7 -1 -1 3 -1 -1 4 -1 -1
  3
  Sample Output 1 :
  1
  3
  Explanation For Sample Input 1 :
  For First Case - Same as explained in above example.

  For the second case -
  K is 3 and the tree is depicted by the following image then,

  The 3rd largest element in the given BST is 3. So the output will be 3.
  Sample Input 2 :
  2
  4 3 -1 2 -1 1 -1 -1 -1
  1
  3 1 8 -1 2 -1 -1 -1 -1
  3
  Sample Output 2 :
  4
  2

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth largest frequently, how would you optimize?
Ans:  Using Augmented BST
      🎯 Idea: We augment each node to store the size of its subtree.
      ✨ How?
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

      To get k-th largest, convert k-th largest = (total - k + 1)-th smallest.
      🔁 Insert/Delete also becomes O(log N) with size updates.


Follow-up :
 Try to do it in O(1) space without using recursion.


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
  // 1. Title: Find K-th smallest element in BST
  //-------------------------------------------------------------------------------

  /**
   * Method: inTrav (Helper)
   * ------------------------
   * Performs an inorder traversal to find the kth smallest element in a BST.
   *
   * Since an inorder traversal of a BST yields sorted elements in ascending order,
   * this traversal helps to track the number of nodes visited so far (`count`)
   * and returns the node's value when `count == k`.
   *
   * Parameters:
   * - root: current TreeNode to process.
   * - k: the target position of the smallest element to find.
   * - count: passed by reference to track the current inorder position globally.
   *
   * Returns:
   * - Value of the kth smallest node when found.
   * - -1 if traversal completes without finding it (edge cases).
   *
   * Time Complexity: O(H + k)
   *     - In the worst case, we may traverse down to the kth node.
   *     - In a balanced BST, H = log(N); worst case: O(N) in skewed trees.
   *
   * Space Complexity: O(H)
   *     - Due to recursion stack, where H is height of the tree.
   */
  int inTrav(TreeNode *root, int k, int &count)
  {
    int ret = -1; // Default invalid value

    if (root == NULL)
      return ret;

    // Traverse left subtree first (inorder: left → root → right)
    if (root->left)
      ret = inTrav(root->left, k, count);

    // If kth element already found in left subtree, return early
    if (count == k)
      return ret;

    // Visit current node
    count++;

    if (count == k)
      return root->val;

    // Traverse right subtree
    if (root->right)
      ret = inTrav(root->right, k, count);

    return ret;
  }

  /**
   * Method: kthSmallest
   * -------------------
   * Finds the kth smallest element in a Binary Search Tree.
   *
   * Parameters:
   * - root: pointer to the root of the BST.
   * - k: the position (1-based) of the element to find in sorted order.
   *
   * Returns:
   * - The value of the kth smallest node.
   *
   * Time Complexity: O(H + k), where H is the height of the tree.
   * Space Complexity: O(H) due to recursion.
   */
  int kthSmallest(TreeNode *root, int k)
  {
    int count = 0;
    return inTrav(root, k, count);
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Find K-th largest element in BST
//-------------------------------------------------------------------------------

class Solution1
{
public:
  // ---------------------------- Approach1 -------------------------------------------------
  // Method: reverseInorder
  // -----------------------
  // Performs Reverse Inorder Traversal (Right ? Node ? Left) to find the Kth
  // largest element in a BST.
  //
  // Approach:
  //   - Traverse right subtree first (higher values).
  //   - Keep a count of how many nodes we've visited.
  //   - When count == K, store the current node value.
  //   - Traverse left subtree only if required.
  //
  // Time Complexity: O(H + K)
  //   - Worst case: O(N), but often stops early when Kth largest is found.
  //   - H = height of BST (log N for balanced, N for skewed).
  //
  // Space Complexity: O(H)
  //   - Recursion stack based on height of the tree.
  // -----------------------------------------------------------------------------
  void reverseInorder(TreeNodeN<int> *root, int k, int &count, int &result)
  {
    if (root == nullptr || count >= k)
      return;

    // Visit right subtree first for larger values
    reverseInorder(root->right, k, count, result);

    count++;
    if (count == k)
    {
      result = root->data;
      return;
    }

    // Visit left subtree
    reverseInorder(root->left, k, count, result);
  }

  // ------------------------------------------
  // Method: KthLargest
  // ------------------
  // Returns the Kth largest element from a BST.
  //
  // Parameters:
  // - root: root node of BST
  // - k: Kth largest element to find
  //
  // Time: O(H + K)
  // Space: O(H)
  // ----------------------------------------
  int KthLargest(TreeNodeN<int> *root, int k)
  {
    int count = 0;
    int result = -1;

    reverseInorder(root, k, count, result);

    return result;
  }

  // ---------------------------- Approach2 (with space: O(1))-------------------------------------------------
  /**
   * Method: KthLargest using Morris
   * -------------------------------
   * Finds the k-th largest element in a Binary Search Tree using **reverse Morris Inorder Traversal**.
   *
   * ? Approach:
   * - In a BST, the **inorder traversal** (Left ? Root ? Right) gives elements in ascending order.
   * - To get the **k-th largest**, we perform **reverse inorder traversal** (Right ? Root ? Left),
   *   which gives elements in descending order.
   *
   * ? Optimization:
   * - Uses **Morris Traversal** which allows inorder traversal **without recursion or a stack**.
   * - It temporarily modifies the tree to create **threads (temporary links)** and restores it after use.
   *
   * ? Logic:
   * - Traverse the tree using reverse inorder (right ? root ? left).
   * - Maintain a counter to track how many nodes we've visited.
   * - When the counter equals `k`, we've found our k-th largest element.
   *
   * ? Time Complexity: O(N)
   *    - Each edge is visited at most twice (once to create a thread, once to remove it).
   *
   * ? Space Complexity: O(1)
   *    - No recursion stack or auxiliary data structures used.
   *
   * @param root: Root of the Binary Search Tree
   * @param k: The k-th largest element to find
   * @return The k-th largest element value
   */
  int KthLargest(TreeNodeN<int> *root, int k)
  {
    TreeNodeN<int> *cur = root; // Start from the root node
    int count = 0;              // To keep track of how many nodes we've visited
    int result = -1;            // To store the final result

    // Perform reverse Morris inorder traversal
    while (cur)
    {
      if (cur->right == NULL)
      {
        // Case 1: No right child ? visit current node and go to left
        count++;
        if (count == k)
          result = cur->data;
        cur = cur->left;
      }
      else
      {
        // Case 2: Has a right child ? find its inorder predecessor
        TreeNodeN<int> *tmp = cur->right;
        while (tmp->left && tmp->left != cur)
        {
          tmp = tmp->left;
        }

        if (tmp->left == NULL)
        {
          // First time visiting tmp ? create a thread back to current
          tmp->left = cur;
          cur = cur->right;
        }
        else
        {
          // Thread already exists ? remove it, visit current, go left
          tmp->left = NULL;
          count++;
          if (count == k)
            result = cur->data;
          cur = cur->left;
        }
      }
    }

    return result;
  }
};

int main()
{
  return 0;
}
