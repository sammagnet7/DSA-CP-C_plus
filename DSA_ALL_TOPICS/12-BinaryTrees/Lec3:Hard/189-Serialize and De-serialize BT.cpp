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

1. Title: Serialize and De-serialize BT

Links:
https://takeuforward.org/data-structure/serialize-and-deserialize-a-binary-tree/
https://takeuforward.org/plus/dsa/problems/serialize-and-de-serialize-bt?tab=editorial
https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/


Problem statement:
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Examples:
  Example 1:
  Input: root = [1,2,3,null,null,4,5]

        (1)
       /   \
     (2)   (3)
           / \
         (4) (5)

  Output: [1,2,3,null,null,4,5]

  Example 2:
  Input: root = []
  Output: []


Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000


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
// 1. Title: Serialize and De-serialize BT
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: SERIALIZE AND DESERIALIZE BINARY TREE (PREORDER DFS)
 * ============================================================================
 * * [THE INTUITION & MENTAL MODEL]
 * * 1. The Flattening (Serialization):
 * To convert a multidimensional tree into a 1D string, we need a traversal
 * method that is deterministic. Preorder (Root -> Left -> Right) is the most
 * natural choice because when we eventually decode the string from left to
 * right, the very first number we read will immediately be the Root node.
 * * However, just printing the numbers isn't enough (e.g., a tree with duplicate
 * values or missing branches becomes ambiguous). We MUST record the exact
 * structure by encoding the `null` leaves (using a marker like `#`). This
 * mathematically locks the shape of the tree into the string.
 * * 2. The Reconstruction (Deserialization):
 * Because we encoded using Preorder, decoding is just a direct translation.
 * We feed the string into a data stream and consume it token by token.
 * - Read a number? Create a node and recursively build its Left and Right children.
 * - Read a `#`? Return `nullptr`. This acts as a structural boundary, naturally
 * terminating the branch and forcing the recursion to step back up the stack.
 * ============================================================================
 */
class Codec
{
private:
  // Helper to traverse the tree and build the string via reference
  void recBuildPreorder(TreeNode *node, string &preOrderSerial)
  {

    // Base case: structural boundary hit. Encode the null marker.
    if (!node)
    {
      preOrderSerial += "#,";
      return;
    }

    // Process Root
    preOrderSerial += to_string(node->val) + ',';

    // Process Left, then Right
    recBuildPreorder(node->left, preOrderSerial);
    recBuildPreorder(node->right, preOrderSerial);
  }

  // Helper to dynamically consume the stream and build nodes
  TreeNode *recBuildTree(stringstream &ss)
  {

    string token;

    // Base case 1: End of stream reached unexpectedly
    if (!getline(ss, token, ','))
    {
      return nullptr;
    }
    // Base case 2: We hit a serialized null marker. Close this branch.
    else if (token == "#")
    {
      return nullptr;
    }
    // Build the current node, then recursively build its children
    else
    {
      int num = stoi(token);
      TreeNode *curN = new TreeNode(num);

      curN->left = recBuildTree(ss);
      curN->right = recBuildTree(ss);

      return curN;
    }
  }

public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root)
  {
    string preOrderSerial = "";

    if (!root)
    {
      return preOrderSerial;
    }

    recBuildPreorder(root, preOrderSerial);

    // Optional but clean: remove the very last trailing comma
    preOrderSerial.pop_back();

    return preOrderSerial;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data)
  {

    if (data.length() == 0)
    {
      return nullptr;
    }

    // Convert the raw string into a consumable stream
    stringstream ss(data);

    // Kick off the recursive reconstruction
    return recBuildTree(ss);
  }
};

int main()
{
  return 0;
}
