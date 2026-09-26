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

1. Title: Construct a BT from Preorder and Inorder

Links:
https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/
https://takeuforward.org/plus/dsa/problems/construct-a-bt-from-preorder-and-inorder?tab=editorial
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

Problem statement:
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

Examples:
  Example 1:

        (3)
       /   \
     (9)  (20)
           / \
        (15) (7)

  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
  Output: [3,9,20,null,null,15,7]

  Example 2:
  Input: preorder = [-1], inorder = [-1]
  Output: [-1]


Constraints:
  1 <= preorder.length <= 3000
  inorder.length == preorder.length
  -3000 <= preorder[i], inorder[i] <= 3000
  preorder and inorder consist of unique values.
  Each value of inorder also appears in preorder.
  preorder is guaranteed to be the preorder traversal of the tree.
  inorder is guaranteed to be the inorder traversal of the tree.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Construct a BT from Postorder and Inorder

Links:
https://takeuforward.org/data-structure/construct-a-binary-tree-from-inorder-and-preorder-traversal/
https://takeuforward.org/plus/dsa/problems/construct-a-bt-from-postorder-and-inorder?tab=editorial
https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/


Problem statement:
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

Examples:
  Example 1:

        (3)
       /   \
     (9)  (20)
           / \
        (15) (7)

  Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
  Output: [3,9,20,null,null,15,7]

  Example 2:
  Input: inorder = [-1], postorder = [-1]
  Output: [-1]

Constraints:
  1 <= inorder.length <= 3000
  postorder.length == inorder.length
  -3000 <= inorder[i], postorder[i] <= 3000
  inorder and postorder consist of unique values.
  Each value of postorder also appears in inorder.
  inorder is guaranteed to be the inorder traversal of the tree.
  postorder is guaranteed to be the postorder traversal of the tree.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------
// 1. Title: Construct a BT from Preorder and Inorder
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * TREE ALGORITHM: CONSTRUCT BINARY TREE FROM PREORDER & INORDER TRAVERSAL
 * ============================================================================
 * * [APPROACH SUMMARY]
 * 1. Preorder sequence tells us the sequential order of ROOTS.
 * 2. Inorder sequence tells us the structural boundaries of SUBTREES.
 * 3. We use a hash map to map each Node Value to its Index in the inorder array.
 * 4. We recursively slice both arrays into Left Subtree segments and Right
 * Subtree segments, tracking boundaries with 4 index pointers.
 * * * [TIME COMPLEXITY]
 * O(N) -> Populating the map takes O(N) time. The recursive function builds
 * exactly one node per call, executing a total of N calls. Each call
 * does O(1) work due to the constant-time hash map index lookups.
 * * * [SPACE COMPLEXITY]
 * O(N) -> The hash map stores N elements, consuming linear space. The
 * recursive call stack scales with the height of the tree, which is
 * O(log N) for a balanced tree and O(N) in the worst-case skewed tree.
 * ============================================================================
 */
class Solution
{
private:
  // Maps Node Value -> Index location in the Inorder array
  unordered_map<int, int> inorderIdxMap;

  /**
   * @brief Recursive helper that isolates subarrays to build nodes bottom-up.
   * * @param pStart Starting index of the current subtree in the preorder array
   * @param pEnd Ending index of the current subtree in the preorder array
   * @param iStart Starting index of the current subtree in the inorder array
   * @param iEnd Ending index of the current subtree in the inorder array
   */
  TreeNode *recBuild(int pStart, int pEnd, int iStart, int iEnd,
                     vector<int> &preorder, vector<int> &inorder)
  {

    // Base case: If boundaries cross, the current subtree is empty (null child)
    if (pStart > pEnd || iStart > iEnd)
    {
      return nullptr;
    }

    // 1. Preorder rule: The first element of the current range is always the Root
    int curVal = preorder[pStart];
    TreeNode *curN = new TreeNode(curVal);

    // 2. Look up where this root splits the inorder sequence in O(1) time
    int inIdx = inorderIdxMap[curVal];

    // 3. Count how many nodes belong specifically to the left subtree
    int inLeftCount = inIdx - iStart;

    // 4. Divide and Conquer: Slice boundaries for the children
    // Left Subtree:
    // - Preorder range: skips current root (+1) up to the size of the left pool
    // - Inorder range: starts at current boundary up to just before the root divider
    TreeNode *leftN = recBuild(pStart + 1, pStart + inLeftCount, iStart, inIdx - 1, preorder, inorder);

    // Right Subtree:
    // - Preorder range: starts immediately after the left pool up to the end of the range
    // - Inorder range: starts just after the root divider up to the current right boundary
    TreeNode *rightN = recBuild(pStart + inLeftCount + 1, pEnd, inIdx + 1, iEnd, preorder, inorder);

    // 5. Establish structural pointers bottom-up
    curN->left = leftN;
    curN->right = rightN;

    // Return current constructed root to its parent frame
    return curN;
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
  {
    int n = preorder.size();

    // Step 1: Pre-process inorder array to enable O(1) index searches
    for (int i = 0; i < n; ++i)
    {
      inorderIdxMap[inorder[i]] = i;
    }

    // Step 2: Trigger the recursive divide-and-conquer builder across the entire range
    return recBuild(0, n - 1, 0, n - 1, preorder, inorder);
  }
};

//-------------------------------------------------------------------------------
// 2. Title: Construct a BT from Postorder and Inorder
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * TREE ALGORITHM: CONSTRUCT BINARY TREE FROM INORDER & POSTORDER TRAVERSAL
 * ============================================================================
 * * [APPROACH SUMMARY]
 * 1. Postorder sequence tells us the sequential order of ROOTS (always at the end).
 * 2. Inorder sequence tells us the structural boundaries of SUBTREES.
 * 3. We use a hash map to map each Node Value to its Index in the inorder array
 * for O(1) lookups.
 * 4. We recursively slice both arrays. Because it is Postorder, the current root
 * is at `pEnd`. The left subtree comes first, followed by the right subtree.
 * * * [TIME COMPLEXITY]
 * O(N) -> Populating the map takes O(N). Building the tree takes N recursive
 * calls, doing O(1) mathematical slicing at each step.
 * * * [SPACE COMPLEXITY]
 * O(N) -> The hash map requires linear space. The recursion stack uses O(H)
 * space, which degrades to O(N) in a perfectly skewed tree.
 * ============================================================================
 */
class Solution
{
private:
  // Maps Node Value -> Index location in the Inorder array
  unordered_map<int, int> inorderIdxMap;

  /**
   * @brief Recursive helper that isolates subarrays to build nodes bottom-up.
   * @param pStart Starting index of the current subtree in the postorder array
   * @param pEnd Ending index of the current subtree in the postorder array
   * @param iStart Starting index of the current subtree in the inorder array
   * @param iEnd Ending index of the current subtree in the inorder array
   */
  TreeNode *recBuild(int pStart, int pEnd, int iStart, int iEnd,
                     vector<int> &postorder, vector<int> &inorder)
  {

    // Base case: Boundaries cross, meaning this child doesn't exist
    if (pStart > pEnd || iStart > iEnd)
    {
      return nullptr;
    }

    // 1. Postorder rule: The LAST element of the current range is the Root
    int curVal = postorder[pEnd];
    TreeNode *curN = new TreeNode(curVal);

    // 2. Look up the root's position in the inorder sequence in O(1) time
    int inIdx = inorderIdxMap[curVal];

    // 3. Calculate exactly how many elements belong to the Left Subtree
    int inLeftCount = inIdx - iStart;

    // 4. Divide and Conquer: Slice boundaries for the children

    // Left Subtree:
    // - Postorder: starts at pStart, spans exactly `inLeftCount` elements
    // - Inorder: everything up to just before the root
    TreeNode *leftN = recBuild(pStart, pStart + inLeftCount - 1, iStart, inIdx - 1, postorder, inorder);

    // Right Subtree:
    // - Postorder: starts immediately after the left pool, ends right before current root
    // - Inorder: everything right after the root
    TreeNode *rightN = recBuild(pStart + inLeftCount, pEnd - 1, inIdx + 1, iEnd, postorder, inorder);

    // 5. Build the connections
    curN->left = leftN;
    curN->right = rightN;

    return curN;
  }

public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
  {
    int n = postorder.size();

    // Step 1: Pre-process inorder array to enable O(1) index searches
    for (int i = 0; i < n; ++i)
    {
      inorderIdxMap[inorder[i]] = i;
    }

    // Step 2: Trigger the recursive builder across the entire range
    return recBuild(0, n - 1, 0, n - 1, postorder, inorder);
  }
};

int main()
{
  return 0;
}
