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

1. Title: Right View of BT

Links:
https://takeuforward.org/data-structure/right-left-view-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/right-left-view-of-bt?tab=editorial
https://leetcode.com/problems/binary-tree-right-side-view/description/
https://www.naukri.com/code360/problems/left-view-of-a-binary-tree_920519?leftPanelTabValue=PROBLEM


Problem statement:
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Examples:
  Example 1:
  Input: root = [1,2,3,null,5,null,4]
  Output: [1,3,4]

  Example 2:
  Input: root = [1,2,3,4,null,null,null,5]
  Output: [1,3,4,5]

  Example 3:
  Input: root = [1,null,3]
  Output: [1,3]

  Example 4:
  Input: root = []
  Output: []



INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------

2. Title: Left View of BT

Links:
https://takeuforward.org/data-structure/right-left-view-of-binary-tree/
https://takeuforward.org/plus/dsa/problems/right-left-view-of-bt?tab=editorial
https://www.naukri.com/code360/problems/left-view-of-a-binary-tree_920519?leftPanelTabValue=PROBLEM


Problem statement:
You have been given a binary tree of integers. You are supposed to find the left view of the binary tree. The left view of a binary tree is the set of all nodes that are visible when the binary tree is viewed from the left side.

Example:
  Sample Input 1:
  2
  3 4 -1 -1 -1
  2 8 7 -1 5 -1 -1 1 -1 -1 -1
  Sample Output 1:
  3 4
  2 8 5 1
  Explanation of Sample Input 1:
  For the first test case, node 3 and node 4 are visible when the binary tree is viewed from the left.

  For the second test case, nodes 2, 8, 5, 1 are visible when the binary tree is viewed from the left.
  Sample Input 2:
  2
  1 3 5 12 -1 8 -1 -1 -1 -1 -1
  9 6 3 -1 -1 4 8 -1 -1 -1 -1
  Sample Output 2:
  1 3 12
  9 6 4
  Explanation of Sample Input 2:
  For the first test case, nodes 1, 3, 12 are visible when the binary tree is viewed from the left.

  For the second test case, nodes 9, 6, 4 are visible when the binary tree is viewed from the left.


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

template <typename T>
class TreeNodeT
{
  public:
    int data;
    TreeNodeT *left;
    TreeNodeT *right;
    TreeNodeT() : data(0), left(nullptr), right(nullptr) {}
    TreeNodeT(int x) : data(x), left(nullptr), right(nullptr) {}
    TreeNodeT(int x, TreeNodeT *left, TreeNodeT *right) : data(x), left(left), right(right) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Right View of BT
  //-------------------------------------------------------------------------------
  // Approach1: using map
  //

  // // O(N)
  // void dfs(TreeNode* root, map<int,int> &mp, int lvl){

  //     if(root==NULL)
  //         return;

  //     mp[lvl] = root->val;

  //     if(root->left != NULL)
  //         dfs(root->left, mp, lvl+1);

  //     if(root->right != NULL)
  //         dfs(root->right, mp, lvl+1);

  // }

  // // approach: recursive using map
  // //
  // // Time: O(N)
  // // Time: O(h + h) as recursive + map
  // vector<int> rightSideView(TreeNode* root) {

  //     vector<int> ans;
  //     if(root==NULL)
  //         return ans;

  //     map<int,int> mp; // <lvl,val>

  //     dfs(root, mp, 0);

  //     for(auto v: mp){    // O(h)
  //         ans.push_back(v.second);
  //     }

  //     return ans;
  // }

  // Approach2: without map, only recursion, simpler
  //

  // O(N)
  void dfs(TreeNode *node, int lvl, vector<int> &ans)
  {

    if (node == NULL)
      return;

    if (ans.size() == lvl)
      ans.push_back(node->val);

    if (node->right != NULL)
      dfs(node->right, lvl + 1, ans);

    if (node->left != NULL)
      dfs(node->left, lvl + 1, ans);
  }

  // approach: recursive using map
  //
  // Time: O(N)
  // Time: O(h) as recursive
  vector<int> rightSideView(TreeNode *root)
  {

    vector<int> ans;
    if (root == NULL)
      return ans;

    dfs(root, 0, ans);

    return ans;
  }
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 2. Title: Left View of BT
  //-------------------------------------------------------------------------------
  // Approach1: using map
  //

  // // O(N)
  // void dfs(TreeNodeT<int>* root, map<int,int> &mp, int lvl){

  //     if(root==NULL)
  //         return;

  //     if(mp.find(lvl) == mp.end())
  //         mp[lvl] = root->data;

  //     if(root->left != NULL)
  //         dfs(root->left, mp, lvl+1);

  //     if(root->right != NULL)
  //         dfs(root->right, mp, lvl+1);

  // }

  // // approach: recursive using map
  // //
  // // Time: O(N)
  // // Time: O(h + h ) as recursive + map
  // vector<int> getLeftView(TreeNodeT<int> *root)
  // {
  //     //    Write your code here
  //     vector<int> ans;
  //     if(root==NULL)
  //         return ans;

  //     map<int,int> mp; // <lvl,val>

  //     dfs(root, mp, 0);   // Traverse

  //     for(auto v: mp){    // O(h): Adding to ans
  //         ans.push_back(v.second);
  //     }

  //     return ans;
  // }

  // Approach2:
  //

  // O(N)
  void dfs(TreeNodeT<int> *node, int lvl, vector<int> &ans)
  {

    if (node == NULL)
      return;

    if (ans.size() == lvl)
      ans.push_back(node->data);

    if (node->left != NULL)
      dfs(node->left, lvl + 1, ans);

    if (node->right != NULL)
      dfs(node->right, lvl + 1, ans);
  }

  // approach: recursive using map
  //
  // Time: O(N)
  // Time: O(h) as recursive
  vector<int> getLeftView(TreeNodeT<int> *root)
  {
    //    Write your code here
    vector<int> ans;
    if (root == NULL)
      return ans;

    dfs(root, 0, ans);

    return ans;
  }
};

int main()
{
  return 0;
}
