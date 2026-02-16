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

1. Title: Lowest Common Ancestor of Deepest Leaves

Links:
https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/
https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description/?envType=daily-question&envId=2026-01-09


Problem statement:
Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:

The node of a binary tree is a leaf if and only if it has no children
The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every node in S is in the subtree with root A.


Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest leaf-nodes of the tree.
Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.

Example 2:
Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree, and it's the lca of itself.

Example 3:
Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.


Constraints:
The number of nodes in the tree will be in the range [1, 1000].
0 <= Node.val <= 1000
The values of the nodes in the tree are unique.



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

//--------------------------------------------
// Approach 1 : Double pass
//-------------------------------------------
// class Solution {
// public:
//     /**
//      * Helper Function 1: Calculate Tree Height
//      * Standard recursive function to find the maximum depth of the tree.
//      * Time: O(N)
//      */
//     int getDepth(TreeNode* node){
//         if(!node){
//             return 0;
//         }
//         return 1 + max(getDepth(node->left), getDepth(node->right));
//     }

//     /**
//      * Helper Function 2: Find LCA of Deepest Nodes
//      * * Approach:
//      * This recursive function searches for nodes that are located at 'maxDepth'.
//      * It uses a "Bubble Up" strategy similar to the standard LCA algorithm.
//      * * Logic:
//      * 1. If a node is a leaf and is at 'maxDepth', it returns itself (it's a target).
//      * 2. If a node receives non-null returns from BOTH left and right children,
//      * it means this node is the Lowest Common Ancestor of two deepest nodes.
//      * 3. If a node receives a non-null return from only ONE child, it bubbles that result up.
//      * * @param node Current node being visited
//      * @param curDepth Depth of the current node (0-indexed from root call)
//      * @param maxDepth The target depth we calculated in Pass 1
//      */
//     TreeNode* rec(TreeNode* node, int curDepth, int maxDepth){

//         // Base Case: Leaf Node Check
//         // Deepest nodes are by definition leaves (or else their children would be deeper).
//         if(!node->left && !node->right){
//             // Check if this leaf is at the deepest level
//             // Note: Using 1+curDepth to match the 1-based height from getDepth
//             if(1 + curDepth == maxDepth){
//                 return node; // Found a deepest node
//             }
//             else{
//                 return nullptr; // This leaf is not deep enough
//             }
//         }

//         TreeNode* left = nullptr;
//         TreeNode* right = nullptr;

//         // Recursive Step: Check children
//         if(node->left){
//             left = rec(node->left, curDepth + 1, maxDepth);
//         }
//         if(node->right){
//             right = rec(node->right, curDepth + 1, maxDepth);
//         }

//         // Decision Step (The LCA Logic):

//         // Case 1: Both sides returned a node.
//         // This implies there are deepest nodes in the left subtree AND the right subtree.
//         // Therefore, CURRENT node is the Lowest Common Ancestor.
//         if(left && right){
//             return node;
//         }
//         // Case 2: Only one side returned a node (or neither).
//         // Bubble up the non-null result (or null if neither found anything).
//         else {
//             return left == nullptr ? right : left;
//         }
//     }

//     /**
//      * Main Function
//      * * Approach: Two-Pass DFS
//      * 1. First Pass: Calculate the global maximum depth of the tree.
//      * 2. Second Pass: Find the subtree that contains all nodes at that depth.
//      * * Complexity Analysis:
//      * - Time Complexity: O(N). We traverse the tree twice (once for depth, once for LCA). O(2N) -> O(N).
//      * - Space Complexity: O(H). Recursion stack depth depends on tree height.
//      */
//     TreeNode* lcaDeepestLeaves(TreeNode* root) {

//         if(!root){
//             return root;
//         }

//         // Pass 1: Get the target depth
//         int maxDepth = getDepth(root);

//         // Pass 2: Find the LCA for nodes at that depth
//         return rec(root, 0, maxDepth);
//     }
//};

//--------------------------------------------
// Approach 2 : Single pass
//-------------------------------------------
class Solution
{
public:
  /**
   * Helper Function: Depth First Search (Post-Order)
   * * Approach:
   * This function traverses the tree bottom-up to find two things simultaneously for every subtree:
   * 1. The Maximum Depth (Height) of that subtree.
   * 2. The 'Candidate Node' (LCA) that roots the smallest subtree containing all deepest nodes found so far.
   * * * Logic:
   * - If left subtree is deeper: The deepest nodes are on the left. The LCA must be in the left child's result.
   * - If right subtree is deeper: The deepest nodes are on the right. The LCA must be in the right child's result.
   * - If depths are EQUAL: This current node is the split point where paths to the deepest nodes diverge.
   * Therefore, THIS node is the new Lowest Common Ancestor.
   * * * Return Pair: {Subtree Height, Candidate Node}
   */
  pair<int, TreeNode *> dfs(TreeNode *root)
  {
    // Base Case: An empty node has height 0 and no LCA.
    if (!root)
    {
      return {0, nullptr};
    }

    // Recursive Step: Get {height, LCA} from left and right children
    pair<int, TreeNode *> left = dfs(root->left);
    pair<int, TreeNode *> right = dfs(root->right);

    int leftHeight = left.first;
    int rightHeight = right.first;

    // Decision Logic
    if (leftHeight == rightHeight)
    {
      // Case 1: Balanced. Deepest nodes exist on both sides.
      // This 'root' is the lowest node connecting them.
      return {leftHeight + 1, root};
    }
    else if (leftHeight > rightHeight)
    {
      // Case 2: Left is deeper.
      // The answer is already determined inside the left subtree. Pass it up.
      return {leftHeight + 1, left.second};
    }
    else
    {
      // Case 3: Right is deeper.
      // The answer is already determined inside the right subtree. Pass it up.
      return {rightHeight + 1, right.second};
    }
  }

  /**
   * Main Function
   * * Problem: Find smallest subtree containing all deepest nodes.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * We visit every node exactly once using a standard DFS traversal.
   * - Space Complexity: O(H) where H is the height of the tree.
   * This is used by the recursion stack. In worst case (skewed tree), O(N).
   */
  TreeNode *lcaDeepestLeaves(TreeNode *root)
  {
    // The second element of the pair is our answer node
    return dfs(root).second;
  }
};

int main()
{
  return 0;
}
