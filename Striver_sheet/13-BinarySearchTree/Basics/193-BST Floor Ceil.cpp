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

1. Title: Floor in BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/floor-and-ceil-in-a-bst?tab=editorial
https://www.naukri.com/code360/problems/floor-from-bst_920457?leftPanelTabValue=PROBLEM



Problem statement:
You are given a BST (Binary search tree) with’ N’ number of nodes and a value ‘X’. Your task is to find the greatest value node of the BST which is smaller than or equal to ‘X’.
Note :‘X’ is not smaller than the smallest node of BST .

For example:
In the above example, For the given BST  and X = 7, the greatest value node of the BST  which is smaller than or equal to  7 is 6.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Ceil in BST

Links:
https://takeuforward.org/plus/dsa/binary-search-trees/theory-and-basics/floor-and-ceil-in-a-bst?tab=editorial
https://www.naukri.com/code360/problems/ceil-from-bst_920464?leftPanelTabValue=PROBLEM


Problem statement:
Ninja is given a binary search tree and an integer. Now he is given a particular key in the tree and returns its ceil value. Can you help Ninja solve the problem?

Note:
Ceil of an integer is the closest integer greater than or equal to a given number.
For example:
arr[] = {1, 2, 5, 7, 8, 9}, key = 3.
The closest integer greater than 3 in the given array is 5. So, its ceil value in the given array is 5.

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
  // 1. Title: Floor in BST
  //-------------------------------------------------------------------------------

  // Recursive approach
  // Time: O(log N)
  // Space: O(Log N) i.e. aux stack space
  int floorInBST(BinaryTreeNode<int> *node, int x)
  {
    // Write your code here.
    if (node == NULL)
      return -1;

    if (node->data == x)
    {
      return x;
    }

    else if (node->data < x)
    {
      int poss = node->data;
      int ret = floorInBST(node->right, x);
      if (ret == -1)
        return poss;
      else
        return max(poss, ret);
    }

    else if (node->data > x)
    {
      return floorInBST(node->left, x);
    }
  }

  //-------------------------------------------
  // Iterative approach
  // Time: O(Log N)
  // Space: O(1)
  int floorInBST(BinaryTreeNode<int> *node, int x)
  {
    int floor = -1;

    while (node)
    {
      if (node->data == x)
        return x;
      else if (node->data < x)
      {
        floor = node->data;
        node = node->right;
      }
      else if (node->data > x)
      {
        node = node->left;
      }
    }

    return floor;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Ceil in BST
  //-------------------------------------------------------------------------------
  // Recursive approach
  // Time: O(log N)
  // Space: O(Log N) i.e. aux stack space
  int findCeil(BinaryTreeNode<int> *node, int x)
  {
    // Write your code here.
    if (node == NULL)
      return -1;

    if (node->data == x)
    {
      return x;
    }

    else if (node->data < x)
    {
      return findCeil(node->right, x);
    }

    else if (node->data > x)
    {
      int poss = node->data;
      int ret = findCeil(node->left, x);
      if (ret == -1)
        return poss;
      else
        return min(poss, ret);
    }
  }

  //-------------------------------------------
  // Iterative approach
  // Time: O(Log N)
  // Space: O(1)
  int findCeil(BinaryTreeNode<int> *node, int x)
  {
    int ceil = -1;

    while (node)
    {
      if (node->data == x)
        return x;
      else if (node->data > x)
      {
        ceil = node->data;
        node = node->left;
      }
      else if (node->data < x)
      {
        node = node->right;
      }
    }

    return ceil;
  }
};

int main()
{
  return 0;
}
