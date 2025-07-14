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

1. Title: Check if the Binary tree is height-balanced or not

Links:
https://takeuforward.org/data-structure/check-if-the-binary-tree-is-balanced-binary-tree/
https://www.youtube.com/watch?v=Yt50Jfbd8Po&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=15
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/check-for-balanced-binary-tree
https://leetcode.com/problems/balanced-binary-tree/description/


Problem statement:
Given a binary tree root, find if it is height-balanced or not.

A tree is height-balanced if the difference between the heights of left and right subtrees is not more than one for all nodes of the tree.

Examples:
  Input : [3, 9, 20, null, null, 15, 7]
  Output : Yes

  Input : [1, 2, null, null, 3]
  Output : No


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
  // 1. Title: Check if the Binary tree is height-balanced or not
  //-------------------------------------------------------------------------------

  // Approach1:

  // // Optimal approach: Using int reference
  // // Time: O(N)
  // // Space: O(h)
  // bool checkBalance(TreeNode* root, int &depth){

  //     if(root == NULL){
  //         depth = 0;
  //         return true;
  //     }

  //     int lTreeDepth = 0;
  //     int rTreeDepth = 0;

  //     bool isLBalanced = checkBalance(root->left, lTreeDepth);
  //     bool isRBalanced = checkBalance(root->right, rTreeDepth);

  //     if(!isLBalanced || !isRBalanced)
  //         return false;

  //     if(abs(lTreeDepth-rTreeDepth)>1)
  //         return false;

  //     depth = 1+ max(lTreeDepth, rTreeDepth);

  //     return true;
  // }

  // Approach2:

  // Optimal approach: Using -1 as false
  // Time: O(N)
  // Space: O(h)
  int checkBalance(TreeNode *root)
  {

    if (root == NULL)
    {
      return 0;
    }

    int lDepth = checkBalance(root->left);
    int rDepth = checkBalance(root->right);

    if (lDepth == -1 || rDepth == -1)
      return -1;

    if (abs(lDepth - rDepth) > 1)
      return -1;

    return (1 + max(lDepth, rDepth));
  }

  bool isBalanced(TreeNode *root)
  {
    if (root == NULL)
      return true;

    // int x = 0;
    // return checkBalance(root, x);

    if (checkBalance(root) == -1)
      return false;
    else
      return true;
  }
};

int main()
{
  return 0;
}
