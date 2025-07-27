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

1. Title: BST iterator

Links:
https://takeuforward.org/plus/dsa/problems/bst-iterator?tab=editorial
https://leetcode.com/problems/binary-search-tree-iterator/description/


Problem statement:
Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

Example 1:
  Input
  ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
  [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
  Output
  [null, 3, 7, true, 9, true, 15, true, 20, false]

  Explanation
  BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
  bSTIterator.next();    // return 3
  bSTIterator.next();    // return 7
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 9
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 15
  bSTIterator.hasNext(); // return True
  bSTIterator.next();    // return 20
  bSTIterator.hasNext(); // return False


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


//-------------------------------------------------------------------------------
// 1. Title: BST iterator
//-------------------------------------------------------------------------------

class BSTIterator {
public:
    // Stack to store the path to the next smallest node (left spine of the tree/subtree)
    stack<TreeNode*> st;

    /**
     * Constructor
     * ------------
     * Initializes the iterator to the smallest element in the BST by traversing to the 
     * leftmost node and pushing all encountered nodes on the stack.
     *
     * @param root: Root node of the BST.
     */
    BSTIterator(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->left; // Go as left as possible
        }
    }

    /**
     * next()
     * -------
     * Returns the next smallest number in the BST.
     * - Pops the top node from the stack (which is the current smallest).
     * - If that node has a right subtree, push all left children of that subtree.
     *
     * @return: Value of the next smallest node.
     */
    int next() {
        TreeNode* el = st.top(); // Current smallest
        st.pop();
        int ret = el->val;

        // If right child exists, push all left children of right subtree
        if (el->right) {
            el = el->right;
            while (el) {
                st.push(el);
                el = el->left;
            }
        }

        return ret;
    }

    /**
     * hasNext()
     * ----------
     * Returns true if there is a next smallest number to be returned (i.e., stack is not empty).
     *
     * @return: Boolean indicating if another element exists in the iteration.
     */
    bool hasNext() {
        return !st.empty();
    }
};

int main()
{
  return 0;
}
