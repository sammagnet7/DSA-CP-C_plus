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

1. Title: Time To Burn Tree

Links:
https://takeuforward.org/plus/dsa/problems/minimum-time-taken-to-burn-the-bt-from-a-given-node?tab=editorial
https://www.naukri.com/code360/problems/time-to-burn-tree_1469067?leftPanelTabValue=PROBLEM


Problem statement:
You have a binary tree of 'N' unique nodes and a Start node from where the tree will start to burn. Given that the Start node will always exist in the tree, your task is to print the time (in minutes) that it will take to burn the whole tree.
It is given that it takes 1 minute for the fire to travel from the burning node to its adjacent node and burn down the adjacent node.

For Example :
For the given binary tree: [1, 2, 3, -1, -1, 4, 5, -1, -1, -1, -1]
Start Node: 3

    1
   / \
  2   3
     / \
    4   5

Output: 2
Explanation :
In the zeroth minute, Node 3 will start to burn.
After one minute, Nodes (1, 4, 5) that are adjacent to 3 will burn completely.
After two minutes, the only remaining Node 2 will be burnt and there will be no nodes remaining in the binary tree. 
So, the whole tree will burn in 2 minutes.


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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Time To Burn Tree
  //-------------------------------------------------------------------------------

  // -----------------------------------------------------------------------------
  // Method: createParentMap
  // Purpose: Builds a map that stores the parent of each node in the binary tree.
  //          For each child node, we store the mapping: child -> parent.
  //          Also finds and stores the pointer to the node with value `startVal`.
  //
  // Time Complexity: O(N)
  //     - Each node is visited once.
  // Space Complexity: O(N)
  //     - The map stores N-1 entries (excluding root).
  // -----------------------------------------------------------------------------
  void createParentMap(BinaryTreeNode<int> *node, unordered_map<int, BinaryTreeNode<int> *> &parentMap, int startVal, BinaryTreeNode<int> *&startNode)
  {
    if (node == NULL)
      return;

    if (node->data == startVal)
      startNode = node;

    if (node->left)
    {
      parentMap[node->left->data] = node;
      createParentMap(node->left, parentMap, startVal, startNode);
    }

    if (node->right)
    {
      parentMap[node->right->data] = node;
      createParentMap(node->right, parentMap, startVal, startNode);
    }
  }

  // -----------------------------------------------------------------------------
  // Method: heightOfBinaryTree
  // Purpose: Calculates the height (max depth) of the subtree rooted at `root`.
  //
  // Height is defined as the number of edges on the longest path from the node
  // to a leaf.
  //
  // Time Complexity: O(N)
  //     - Visits each node once.
  // Space Complexity: O(H)
  //     - Due to recursion stack, where H = height of tree.
  // -----------------------------------------------------------------------------
  int heightOfBinaryTree(BinaryTreeNode<int> *root)
  {
    if (root == NULL)
      return 0;

    int leftHeight = heightOfBinaryTree(root->left);
    int rightHeight = heightOfBinaryTree(root->right);

    return 1 + max(leftHeight, rightHeight);
  }

  // -----------------------------------------------------------------------------
  // Method: traverseLevelsAbove
  // Purpose: For each ancestor of the target node (moving upward), it performs a
  //          level-order traversal (BFS) to calculate the maximum downward
  //          distance from that ancestor node, ignoring already visited nodes.
  //
  // Time Complexity: O(N)
  //     - In worst case, all nodes may be visited through upward + downward traversal.
  // Space Complexity: O(N)
  //     - Due to the visited map and queue.
  // -----------------------------------------------------------------------------
  int traverseLevelsAbove(BinaryTreeNode<int> *node, unordered_map<int, BinaryTreeNode<int> *> parentMap)
  {
    unordered_map<int, int> visited; // Track visited nodes
    int dist_up = 0;                 // How far we’ve moved up
    int maxDist = 0;

    // Traverse upward until root (no parent)
    while (parentMap.find(node->data) != parentMap.end())
    {
      visited[node->data] = 1;      // Mark current node as visited
      node = parentMap[node->data]; // Move to parent
      dist_up++;                    // Upward distance increases

      // Start BFS from this ancestor downward
      queue<BinaryTreeNode<int> *> q;
      q.push(node);
      int dist_down = dist_up;

      while (!q.empty())
      {
        int qSize = q.size();

        for (int i = 0; i < qSize; i++)
        {
          auto *tmp = q.front();
          q.pop();

          // Push left child if not visited
          if (tmp->left && visited.find(tmp->left->data) == visited.end())
            q.push(tmp->left);

          // Push right child if not visited
          if (tmp->right && visited.find(tmp->right->data) == visited.end())
            q.push(tmp->right);
        }

        dist_down++; // Move one level deeper
      }

      dist_down--;                       // Adjust extra increment after exiting loop
      maxDist = max(maxDist, dist_down); // Track farthest burn time
    }

    return maxDist;
  }

  // -----------------------------------------------------------------------------
  // Method: timeToBurnTree
  // Purpose: Calculates minimum time required to burn the entire binary tree,
  //          starting from a target node `start`.
  //
  // Approach:
  //  - Step 1: Map each node to its parent.
  //  - Step 2: Calculate max depth below `start` node (fire spreads down).
  //  - Step 3: From each ancestor of `start`, calculate max depth not visited
  //            (fire spreads up, and then down again).
  //  - Result = max(time_downward, time_upward)
  //
  // Time Complexity: O(N)
  // Space Complexity: O(N)
  // -----------------------------------------------------------------------------
  int timeToBurnTree(BinaryTreeNode<int> *root, int start)
  {
    if (root == NULL)
      return 0;

    BinaryTreeNode<int> *startNode;
    unordered_map<int, BinaryTreeNode<int> *> parentMap;

    createParentMap(root, parentMap, start, startNode);

    int timeMaxAtBelow = heightOfBinaryTree(startNode) - 1;         // Fire spreads downward
    int timeMaxAtAbove = traverseLevelsAbove(startNode, parentMap); // Fire spreads upward and down from ancestors

    return max(timeMaxAtBelow, timeMaxAtAbove);
  }
  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
