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

1. Title: Predecessor And Successor In BST

Links:
https://takeuforward.org/plus/dsa/problems/inorder-successor-and-predecessor-in-bst?tab=editorial
https://www.naukri.com/code360/problems/predecessor-and-successor-in-bst_893049?leftPanelTabValue=PROBLEM


Problem statement:
You have been given a binary search tree of integers with ‘N’ nodes. You are also given 'KEY' which represents data of a node of this tree.
Your task is to return the predecessor and successor of the given node in the BST.

Note:
1. The predecessor of a node in BST is that node that will be visited just before the given node in the inorder traversal of the tree. If the given node is visited first in the inorder traversal, then its predecessor is NULL.
2. The successor of a node in BST is that node that will be visited immediately after the given node in the inorder traversal of the tree. If the given node is visited last in the inorder traversal, then its successor is NULL.
3. The node for which the predecessor and successor we are serching, will not always be present. If not present, you can hypothetically assume it's position (Given that it is a BST) and accordingly find out the predecessor and successor.
4. A binary search tree (BST) is a binary tree data structure which has the following properties.
     • The left subtree of a node contains only nodes with data less than the node’s data.
     • The right subtree of a node contains only nodes with data greater than the node’s data.
     • Both the left and right subtrees must also be binary search trees.


Examples:
  Input: 15 10 20 8 12 16 25 -1 -1 -1 -1 -1 -1 -1 -1

             (15)
            /    \
         (10)    (20)
         /  \    /  \
       (8) (12)(16)(25)

  Key: 10
  Sample output 1:  8 12
  Explanation:
    The inorder traversal of this tree will be 8 10 12 15 16 20 25.
    Since the node with data 8 is on the immediate left of the node with data 10 in the inorder traversal, the node with data 8 is the predecessor.
    Since the node with data 12 is on the immediate right of the node with data 10 in the inorder traversal, the node with data 12 is the successor.


  Input:  10 5 -1 -1 -1

             (10)
            /
         (5)

  Key: 5
  Output:  -1 10


Constraint :
  1 <= N <= 10^4
  1 <= data <= 10^7


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

class TreeNode
{
public:
  int data;
  TreeNode *left, *right;
  TreeNode() : data(0), left(NULL), right(NULL) {}
  TreeNode(int x) : data(x), left(NULL), right(NULL) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

//-------------------------------------------------------------------------------
// 1. Title: Predecessor And Successor In BST
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * BST ALGORITHM: PREDECESSOR AND SUCCESSOR (ITERATIVE BOUNDS)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * We find the Inorder Predecessor and Successor by treating them as two
 * independent binary searches looking for the tightest upper and lower bounds.
 * * * [THE MIN/MAX REDUNDANCY (CRITICAL INTERVIEW INSIGHT)]
 * We do NOT need to use `max()` when updating the predecessor, nor `min()`
 * when updating the successor. The BST's structure does the math for us:
 * - Predecessor: When we find a valid candidate (< key), we step RIGHT.
 * This guarantees that any future candidate we find will be strictly LARGER
 * than our current one. The candidates strictly increase, making the final
 * one the absolute maximum.
 * - Successor: When we find a valid candidate (> key), we step LEFT.
 * This guarantees that any future candidate we find will be strictly SMALLER
 * than our current one. The candidates strictly decrease, making the final
 * one the absolute minimum.
 * * * [COMPLEXITY ANALYSIS]
 * - TIME COMPLEXITY: O(H) -> Best/Avg O(log N), Worst Case O(N)
 * We perform exactly two root-to-leaf paths down the tree.
 * - SPACE COMPLEXITY: O(1)
 * We strictly use a single tracking pointer (`tmp`). Zero memory overhead.
 * ============================================================================
 */
pair<int, int> predecessorSuccessor(TreeNode *root, int key)
{

  int pred = -1;
  int succ = -1;

  // STEP 1: Find the Predecessor (Largest value strictly < key)
  TreeNode *tmp = root;
  while (tmp != nullptr)
  {
    if (tmp->data < key)
    {
      // Because we step right immediately after this, any future
      // valid candidate is guaranteed to be larger than this one.
      // Therefore, a simple overwrite is perfectly safe!
      pred = tmp->data;
      tmp = tmp->right;
    }
    else
    {
      tmp = tmp->left;
    }
  }

  // STEP 2: Find the Successor (Smallest value strictly > key)
  tmp = root;
  while (tmp != nullptr)
  {
    if (key < tmp->data)
    {
      // Because we step left immediately after this, any future
      // valid candidate is guaranteed to be smaller than this one.
      // Therefore, a simple overwrite is perfectly safe!
      succ = tmp->data;
      tmp = tmp->left;
    }
    else
    {
      tmp = tmp->right;
    }
  }

  return {pred, succ};
}

int main()
{
  return 0;
}
