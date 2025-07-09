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

1. Title: Check if two trees are identical or not

Links:
https://takeuforward.org/data-structure/check-if-two-trees-are-identical/
https://www.youtube.com/watch?v=BhuvF_-PWS0&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=18
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/check-if-two-trees-are-identical-or-not
https://leetcode.com/problems/same-tree/description/


Problem statement:
Given the roots of two binary trees p and q, write a function to check if they are the same or not.
Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Examples:
  Example 1:
  Input: p = [1,2,3], q = [1,2,3]
  Output: true

  Example 2:
  Input: p = [1,2], q = [1,null,2]
  Output: false

  Example 3:
  Input: p = [1,2,1], q = [1,1,2]
  Output: false


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
  // 1. Title: Check if two trees are identical or not
  //-------------------------------------------------------------------------------
  //
  // Optimal approach
  // Time: O(N) because traversing each nodes ones
  // Space: O(h) i.e. aux stack space
  bool isSameTree(TreeNode *p, TreeNode *q)
  {

    if (p == NULL || q == NULL)
      return (p == q);

    if (p->val != q->val)
      return false;
    else
    {
      return (isSameTree(p->left, q->left) & isSameTree(p->right, q->right));
    }
  }
};

int main()
{
  return 0;
}
