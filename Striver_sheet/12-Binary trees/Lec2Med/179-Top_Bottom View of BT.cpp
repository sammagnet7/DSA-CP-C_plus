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

1. Title: Top View of BT

Links:
https://takeuforward.org/data-structure/top-view-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/top-view-of-bt?tab=editorial
https://www.naukri.com/code360/problems/top-view-of-binary-tree_799401?leftPanelTabValue=PROBLEM


Problem statement:
You are given a Binary Tree of 'n' nodes.
The Top view of the binary tree is the set of nodes visible when we see the tree from the top.
Find the top view of the given binary tree, from left to right.

Examples:
  Example :
  Input: Let the binary tree be:
  Output: [10, 4, 2, 1, 3, 6]
  Explanation: Consider the vertical lines in the figure. The top view contains the topmost node from each vertical line.

  Sample Input 1:
  1 2 3 4 5 -1 6 -1 7 -1 -1 8 -1 9 -1 -1 11 10 -1 -1 -1 -1 -1
  Sample Output 1:
  10 4 2 1 3 6
  Explanation of Sample Output 1:
  The binary tree is:
  Consider the vertical lines in the figure. The top view contains the topmost node from each vertical line.
  In test case 1,

  Sample Input 2:
  1 2 3 4 5 6 7 8 9 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
  Sample Output 2:
  8 4 2 1 3 7
  Explanation of Sample Output 2:
  The binary tree is:
  From left to right, the top view of the tree will be [8,4,2,1,3,7], where 9, 5 and 6 will be hidden when we see from the top of the tree.


Expected time complexity :
The expected time complexity is O(n * log(n)).


INPUT::::::


OUTPUT::::::

------------------------------------------------------------------------------------------------------------------------------------------------
1. Title: Bottom view of BT

Links:
https://takeuforward.org/data-structure/bottom-view-of-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/bottom-view-of-bt?tab=editorial
https://www.naukri.com/code360/problems/bottom-view-of-binary-tree_893110?leftPanelTabValue=PROBLEM


Problem statement:
You are given a 'Binary Tree'.
Return the bottom view of the binary tree.

Note :
1. A node will be in the bottom-view if it is the bottom-most node at its horizontal distance from the root.
2. The horizontal distance of the root from itself is 0. The horizontal distance of the right child of the root node is 1 and the horizontal distance of the left child of the root node is -1.
3. The horizontal distance of node 'n' from root = horizontal distance of its parent from root + 1, if node 'n' is the right child of its parent.
4. The horizontal distance of node 'n' from root = horizontal distance of its parent from the root - 1, if node 'n' is the left child of its parent.
5. If more than one node is at the same horizontal distance and is the bottom-most node for that horizontal distance, including the one which is more towards the right.


Examples:
  Input: Consider the given Binary Tree:
  Output: 4 2 6 3 7
  Explanation:
  Below is the bottom view of the binary tree.
    1 is the root node, so its horizontal distance = 0.
    Since 2 lies to the left of 0, its horizontal distance = 0-1= -1
    3 lies to the right of 0, its horizontal distance = 0+1 = 1
    Similarly, horizontal distance of 4 = Horizontal distance of 2 - 1= -1-1=-2
    Horizontal distance of 5 = Horizontal distance of 2 + 1=  -1+1 = 0
    Horizontal distance of 6 = 1-1 =0
    Horizontal distance of 7 = 1+1 = 2

    The bottom-most node at a horizontal distance of -2 is 4.
    The bottom-most node at a horizontal distance of -1 is 2.
    The bottom-most node at a horizontal distance of 0 is 5 and 6. However, 6 is more towards the right, so 6 is included.
    The bottom-most node at a horizontal distance of 1 is 3.
    The bottom-most node at a horizontal distance of 2 is 7.
    Hence, the bottom view would be 4 2 6 3 7


  Sample input 1 :
  1 2 3 -1 -1 5 6 7 8 -1 -1 -1 -1 -1 -1
  Sample output 1 :
  7 5 8 6
  Explanation of sample input 1 :
  Test case 1:
    1 is the root node, so its horizontal distance = 0.
    Since 2 lies to the left of 0, its horizontal distance = 0-1= -1
    3 lies to the right of 0, its horizontal distance = 0+1 = 1
    Similarly, horizontal distance of 5 = Horizontal distance of 3 - 1= 1-1= 0
    Horizontal distance of 6 = Horizontal distance of 3 + 1=  1+1 = 2
    Horizontal distance of 7 = 0-1 =-1
    Horizontal distance of 8 = 0+1 = 1

    The bottom-most node at a horizontal distance of -1 is 7.
    The bottom-most node at a horizontal distance of 0 is 5.
    The bottom-most node at a horizontal distance of 1 is 8.
    The bottom-most node at a horizontal distance of 2 is 6.
    Hence, the bottom view would be 7 5 8 6.
  Sample input 2 :
  1 2 3 4 -1 6 7 -1 -1 -1 8 -1 -1 -1 -1
  Sample output 2 :
  4 2 6 8 7

Expected Time Complexity:
Try to do this in O(n*log(n)).


INPUT::::::


OUTPUT::::::



*/
template <typename T>
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
  // 1. Title: Top View of BT
  //-------------------------------------------------------------------------------

  // Optmal approach: Using level order traversal
  //
  // Time: O(N)
  // Space: O(N)
  vector<int> getTopView(TreeNode<int> *root)
  {
    // Write your code here.

    queue<pair<TreeNode<int> *, int>> q; // <node,col>
    map<int, int> mp;                    // <col,val>

    q.push({root, 0});

    while (!q.empty())
    { // O(N)
      int qSize = q.size();

      for (int i = 0; i < qSize; i++)
      {
        auto cur = q.front();
        TreeNode<int> *curNode = cur.first;
        int curCol = cur.second;

        q.pop();

        if (mp.find(curCol) == mp.end())
        { // col not encountered
          mp[curCol] = curNode->data;
        }

        if (curNode->left != NULL)
          q.push({curNode->left, curCol - 1});
        if (curNode->right != NULL)
          q.push({curNode->right, curCol + 1});
      }
    }

    vector<int> ans;

    for (auto it : mp)
    { // O(#cols)
      ans.push_back(it.second);
    }

    return ans;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Top View of BT
  //-------------------------------------------------------------------------------

  // Optmal approach: Using level order traversal (Exactly same as Top view excep one line)
  //
  // Time: O(N)
  // Space: O(N)
  vector<int> bottomView(TreeNode<int> *root)
  {
    // Write your code here.
    queue<pair<TreeNode<int> *, int>> q; // <node,col>
    map<int, int> mp;                    // <col,val>

    q.push({root, 0});

    while (!q.empty())
    { // O(N)
      int qSize = q.size();

      for (int i = 0; i < qSize; i++)
      {
        auto cur = q.front();
        TreeNode<int> *curNode = cur.first;
        int curCol = cur.second;

        q.pop();

        mp[curCol] = curNode->data; // Note: update with bottom most value for the column (Only change from Top view)

        if (curNode->left != NULL)
          q.push({curNode->left, curCol - 1});
        if (curNode->right != NULL)
          q.push({curNode->right, curCol + 1});
      }
    }

    vector<int> ans;

    for (auto it : mp)
    { // O(#cols)
      ans.push_back(it.second);
    }

    return ans;
  }
};

int main()
{
  return 0;
}
