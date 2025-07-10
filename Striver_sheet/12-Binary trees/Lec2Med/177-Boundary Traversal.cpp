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

1. Title: Boundary Traversal

Links:
https://takeuforward.org/data-structure/boundary-traversal-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/boundary-traversal?tab=editorial
https://www.naukri.com/code360/problems/boundary-traversal-of-binary-tree_790725?leftPanelTabValue=PROBLEM


Problem statement:
You are given a binary tree having 'n' nodes.
The boundary nodes of a binary tree include the nodes from the left and right boundaries and the leaf nodes, each node considered once.
Figure out the boundary nodes of this binary tree in an Anti-Clockwise direction starting from the root node.

Examples:
  Input: Consider the binary tree A as shown in the figure:
  Output: [10, 5, 3, 7, 18, 25, 20]
  Explanation: As shown in the figure
  The nodes on the left boundary are [10, 5, 3]
  The nodes on the right boundary are [10, 20, 25]
  The leaf nodes are [3, 7, 18, 25].
  Please note that nodes 3 and 25 appear in two places but are considered once.

  Sample Input 1:
  10 5 20 3 8 18 25 -1 -1 7 -1 -1 -1 -1 -1 -1 -1
  Sample Output 1:
  10 5 3 7 18 25 20
  Explanation of Sample Input 1:
  The nodes on the left boundary are [10, 5, 3]
  The nodes on the right boundary are [10, 20, 25]
  The leaf nodes are [3, 7, 18, 25].
  Please note that nodes 3 and 25 appear in two places but are considered once.

  Sample Input 2:
  100 50 150 25 75 140 200 -1 30 70 80 -1 -1 -1 -1 -1 35 -1 -1 -1 -1 -1 -1
  Sample Output 2:
  100 50 25 30 35 70 80 140 200 150



INPUT::::::


OUTPUT::::::


*/
template <typename T>
struct TreeNode
{
  T data;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : data(0), left(nullptr), right(nullptr) {}
  TreeNode(T x) : data(x), left(nullptr), right(nullptr) {}
  TreeNode(T x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Boundary Traversal
  //-------------------------------------------------------------------------------

  // Approach1: ------------------------

  // void leftBoundary(TreeNode<int> *node, vector<int> &ans, unordered_set<TreeNode<int> *> &seen){

  //     if(node == NULL)
  //         return;

  //     if(node->left==NULL && node->right==NULL)
  //         return;

  //     // Save to ans
  //     if (seen.find(node) == seen.end()) {
  //         ans.push_back(node->data);  // maintain order
  //         seen.insert(node);       // ensure uniqueness
  //     }

  //     if(node->left != NULL){
  //         leftBoundary(node->left, ans, seen);
  //     }
  //     else if(node->right != NULL){
  //         leftBoundary(node->right, ans, seen);
  //     }
  //     else{
  //         return;
  //     }
  // }

  // void traverseLeaf(TreeNode<int> *node, vector<int> &ans, unordered_set<TreeNode<int> *> &seen){

  //     if(node == NULL)
  //         return;

  //     if(node->left==NULL && node->right==NULL){

  //         if (seen.find(node) == seen.end()) {
  //             ans.push_back(node->data);  // maintain order
  //             seen.insert(node);       // ensure uniqueness
  //         }
  //         return;
  //     }

  //     if(node->left!=NULL){
  //         traverseLeaf(node->left, ans, seen);
  //     }
  //     if(node->right != NULL){
  //         traverseLeaf(node->right, ans, seen);
  //     }

  // }

  // void rightBoundary(TreeNode<int> *node, vector<int> &ans, unordered_set<TreeNode<int> *> &seen){

  //     if(node == NULL)
  //         return;

  //     if(node->right != NULL){
  //         rightBoundary(node->right, ans, seen);
  //     }
  //     else if(node->left != NULL){
  //         rightBoundary(node->left, ans, seen);
  //     }
  //     else{
  //         return;
  //     }

  //     if(node->left==NULL && node->right==NULL)
  //         return;

  //     if (seen.find(node) == seen.end()) {
  //         ans.push_back(node->data);  // maintain order
  //         seen.insert(node);       // ensure uniqueness
  //     }
  // }

  // //
  // //  Time: O(N)
  // //  Space: O(N)
  // vector<int> traverseBoundary(TreeNode<int> *root)
  // {
  //     // Write your code here.
  //     vector<int> ans;
  //     unordered_set<TreeNode<int> *> seen;

  //     if(root==NULL)
  //         return {};

  //     seen.insert(root);
  //     ans.push_back(root->data);

  //     leftBoundary(root->left,ans, seen);

  //     traverseLeaf(root,ans,seen);

  //     rightBoundary(root->right,ans, seen);

  //     return ans;
  // }

  // Approach2: ----------------------------------

  // void leftBoundary(TreeNode<int> *node, vector<int> &ans){

  //     if(node == NULL)
  //         return;

  //     // Ignore leaf nodes
  //     if(node->left==NULL && node->right==NULL)
  //         return;

  //     // Otherwise save to ans
  //     ans.push_back(node->data);

  //     if(node->left != NULL){
  //         leftBoundary(node->left, ans);
  //     }
  //     else if(node->right != NULL){
  //         leftBoundary(node->right, ans);
  //     }
  // }

  // void traverseLeaf(TreeNode<int> *node, vector<int> &ans){

  //     if(node == NULL)
  //         return;

  //     if(node->left==NULL && node->right==NULL){
  //         // save to ans
  //         ans.push_back(node->data);
  //         return;
  //     }

  //     if(node->left!=NULL){
  //         traverseLeaf(node->left, ans);
  //     }
  //     if(node->right != NULL){
  //         traverseLeaf(node->right, ans);
  //     }

  // }

  // void rightBoundary(TreeNode<int> *node, vector<int> &ans){

  //     if(node == NULL)
  //         return;

  //     // Ignore leaf nodes
  //     if(node->left==NULL && node->right==NULL)
  //         return;

  //     if(node->right != NULL){
  //         rightBoundary(node->right, ans);
  //     }
  //     else if(node->left != NULL){
  //         rightBoundary(node->left, ans);
  //     }

  //     // Otherwise save to ans
  //     ans.push_back(node->data);
  // }

  // //
  // // Optimal approach
  // // Time: O(N)
  // // Space: O(N)
  // vector<int> traverseBoundary(TreeNode<int> *root)
  // {
  // 	// Write your code here.
  //     vector<int> ans;

  //     if(root==NULL)
  //         return {};

  //     ans.push_back(root->data);

  //     leftBoundary(root->left,ans);

  //     traverseLeaf(root,ans);

  //     rightBoundary(root->right,ans);

  //     return ans;
  // }

  // Approach3: -----------------------------------

  // Function to check if a node is a leaf
  bool isLeaf(TreeNode<int> *root)
  {
    return !root->left && !root->right;
  }

  // Function to add the left boundary of the tree
  void addLeftBoundary(TreeNode<int> *root, vector<int> &res)
  {
    TreeNode<int> *curr = root->left;
    while (curr)
    {
      if (!isLeaf(curr))
      {
        res.push_back(curr->data);
      }
      if (curr->left)
      {
        curr = curr->left;
      }
      else
      {
        curr = curr->right;
      }
    }
  }

  // Function to add the right boundary of the tree
  void addRightBoundary(TreeNode<int> *root, vector<int> &res)
  {
    TreeNode<int> *curr = root->right;
    vector<int> temp;
    while (curr)
    {
      if (!isLeaf(curr))
      {
        temp.push_back(curr->data);
      }
      if (curr->right)
      {
        curr = curr->right;
      }
      else
      {
        curr = curr->left;
      }
    }
    for (int i = temp.size() - 1; i >= 0; --i)
    {
      res.push_back(temp[i]);
    }
  }

  // Function to add the leaves of the tree
  void addLeaves(TreeNode<int> *root, vector<int> &res)
  {
    if (isLeaf(root))
    {
      res.push_back(root->data);
      return;
    }
    if (root->left)
    {
      addLeaves(root->left, res);
    }
    if (root->right)
    {
      addLeaves(root->right, res);
    }
  }

  // Main function to perform the boundary traversal of the binary tree
  vector<int> traverseBoundary(TreeNode<int> *root)
  {
    vector<int> res;
    if (!root)
    {
      return res;
    }
    if (!isLeaf(root))
    {
      res.push_back(root->data);
    }

    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);

    return res;
  }
};

int main()
{
  return 0;
}
