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

Constraints :
  1 <= N <= 10^5
  1 <= Value of Tree Node <= 10^9
  1 <= Value of Start Node <= 10^9

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

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
// 1. Title: Time To Burn Tree
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * TREE ALGORITHM: TIME TO BURN TREE (CLASS-LEVEL STATE)
 * ============================================================================
 * * [THE MENTAL MODEL]
 * Imagine the tree is a physical structure and you drop a match at the `start`
 * node. Fire doesn't just spread down to the children; it spreads UP to the
 * parent. To model this, we must upgrade our 1-way tree into a 2-way Graph.
 * The total time to burn the tree is simply the maximum "blast radius" of
 * a Breadth-First Search (BFS) starting from the origin of the fire.
 *
 * * [APPROACH]
 * 1. Convert to Graph (DFS): Traverse the tree to populate a `parentMap`
 *    that links every child to its parent, allowing us to traverse upwards.
 *    Simultaneously, capture the memory address of the `start` node.
 * 2. Simulate Fire (BFS): Push the `start` node into a queue and mark it
 *    as visited. Expand outward level by level (Left, Right, Up).
 * 3. Count Levels: Initialize `time = -1`. For every full level the queue
 *    processes, increment the time. When the queue is empty, return `time`.
 *
 * * [TIME COMPLEXITY]
 * O(N) -> We traverse the tree once (O(N)) to build the parent map. We then
 * perform a BFS that visits every node exactly once (O(N)). Total Time: O(N).
 *
 * * [SPACE COMPLEXITY]
 * O(N) -> The `parentMap` stores N-1 entries. The `visited` set and BFS
 * `queue` can hold up to N elements. The DFS recursion stack takes O(H) space
 * (worst case O(N)). Overall Space: O(N).
 * ============================================================================
 */
class Solution
{
private:
  // Class-level variables (Shared across the methods of this instance)
  unordered_map<BinaryTreeNode<int> *, BinaryTreeNode<int> *> parentMap;
  BinaryTreeNode<int> *target;

  // Helper function signature is now beautifully clean
  void buildParentMap(BinaryTreeNode<int> *node, int start)
  {

    // Locate the starting node and capture its pointer in our class variable
    if (node->data == start)
    {
      target = node;
    }

    if (node->left)
    {
      parentMap[node->left] = node;
      buildParentMap(node->left, start);
    }

    if (node->right)
    {
      parentMap[node->right] = node;
      buildParentMap(node->right, start);
    }
  }

public:
  int timeToBurnTree(BinaryTreeNode<int> *root, int start)
  {
    if (!root)
    {
      return 0;
    }

    // ==========================================
    // THE GOLDEN RULE FOR CLASS VARIABLES:
    // Always reset them before starting a new run!
    // ==========================================
    parentMap.clear();
    target = nullptr;

    // Phase 1: Build graph and find target
    buildParentMap(root, start);

    // Phase 2: Set up the BFS fire simulation
    unordered_set<BinaryTreeNode<int> *> visited;
    queue<BinaryTreeNode<int> *> q;

    q.push(target);
    visited.insert(target);

    int time = -1;

    while (!q.empty())
    {
      int qSize = q.size();

      ++time;

      while (qSize--)
      {
        BinaryTreeNode<int> *cur = q.front();
        q.pop();

        if (cur->left && visited.find(cur->left) == visited.end())
        {
          visited.insert(cur->left);
          q.push(cur->left);
        }

        if (cur->right && visited.find(cur->right) == visited.end())
        {
          visited.insert(cur->right);
          q.push(cur->right);
        }

        if (parentMap.find(cur) != parentMap.end() && visited.find(parentMap[cur]) == visited.end())
        {
          visited.insert(parentMap[cur]);
          q.push(parentMap[cur]);
        }
      }
    }

    return time;
  }
};

int main()
{
  return 0;
}
