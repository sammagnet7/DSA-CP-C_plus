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

1. Title: Diameter of N-ary tree or Acyclic Graph

Links:
https://takeuforward.org/data-structure/calculate-the-diameter-of-a-binary-tree/
https://www.youtube.com/watch?v=Rezetez59Nk&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=16
https://takeuforward.org/plus/dsa/binary-trees/medium-problems/diameter-of-binary-tree
https://www.hackerrank.com/contests/mock-test-2-1758395674/challenges/tree-diameter-6/problem


Problem statement:
There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [u_i, v_i] indicates that there is an undirected edge between nodes u_i and v_i in the tree.

The diameter of a tree is defined as the maximum length of a path between any two nodes in the tree. The length of a path is measured by the number of edges between the nodes, not the number of nodes.

Return the diameter of the tree.

Example 1:
          1
        / \
        2   3
          / \
          4   5
  Input: n = 5, edges = [[1,2], [1,3], [3,4], [3,5]]
  Output: 3
  Explanation: The longest path in the tree is between node 2 and node 5. The path is 2 -> 1 -> 3 -> 5, which contains exactly 3 edges. Another valid longest path is 2 -> 1 -> 3 -> 4.

Example 2:
        1 --- 2
  Input: n = 2, edges = [[1,2]]
  Output: 1
  Explanation: The longest path is between node 1 and node 2, which contains 1 edge.

Example 3:
  Input: 5 1 2 1 3 3 4 3 5
  Output: 3
  Explanation: The diameter corresponds to the path 2 → 1 → 3 → 5.

Constraints:
  1 <= n <= 2 * 10^5
  edges.length == n - 1
  edges[i].length == 2
  1 <= u_i, v_i <= n
  It is guaranteed that the given input forms a valid, connected tree.



INPUT::::::


OUTPUT::::::


*/

/**
 * ============================================================================
 * N-ARY TREE ALGORITHM: POST-ORDER DFS (DP ON TREES)
 * ============================================================================
 * * [THE INTUITION]
 * Problem: Find the longest path (diameter) in an undirected, unrooted N-ary tree.
 *
 * Imagine picking any node and lifting the tree by that node. For that specific
 * node (acting as a "peak"), the longest path that passes through it is formed by
 * connecting its deepest subtree to its second-deepest subtree.
 *
 * Therefore, for every node, local diameter = (Max Child Depth) + (Second Max Child Depth).
 * The global diameter of the tree is simply the maximum local diameter found across all nodes.
 *
 * * [THE MECHANICS]
 * 1. Graph Construction: Convert the edge list into an adjacency list for O(1)
 *    neighbor lookups.
 * 2. Bottom-Up DFS: We arbitrarily root the tree at node 1. We traverse down to
 *    the leaves and bubble up the "max depth".
 * 3. Two-Max Tracking: At each node, as children report their depths, we maintain
 *    the top 2 largest depths (`max_depth_1` and `max_depth_2`).
 * 4. Parent Pointer Hack: Because a tree has no cycles, we don't need a `visited`
 *    array. We just pass `parent` into the DFS and `continue` if neighbor == parent.
 *
 * * [COMPLEXITY ANALYSIS]
 * - Time Complexity: O(N)
 *   -> We build the graph in O(N) and visit every node exactly once during DFS.
 * - Space Complexity: O(N)
 *   -> O(N) to store the adjacency list.
 *   -> O(H) for the recursive call stack (Worst-case O(N) for a skewed tree).
 * ============================================================================
 */
class Solution
{
private:
  /**
   * @brief Recursively calculates the depth of a subtree while updating the global diameter.
   *
   * @param curr     The current node we are evaluating.
   * @param parent   The node we came from (used to prevent moving backwards).
   * @param adj      The adjacency list representing our tree.
   * @param max_dia  Passed by reference to track the maximum diameter found so far.
   * @return int     The maximum depth (number of edges) from `curr` down to its deepest leaf.
   */
  int dfs(int curr, int parent, const vector<vector<int>> &adj, int &max_dia)
  {
    int max_depth_1 = 0; // Largest depth from any child branch
    int max_depth_2 = 0; // Second largest depth from any child branch

    // Check all adjacent nodes (children in our DFS visualization)
    for (int neighbor : adj[curr])
    {
      // Skip the node we came from to avoid infinite loops
      if (neighbor == parent)
      {
        continue;
      }

      // Ask the child for its maximum depth
      int depth = dfs(neighbor, curr, adj, max_dia);

      // Update the top 2 maximum depths
      if (depth > max_depth_1)
      {
        max_depth_2 = max_depth_1; // Old max becomes second max
        max_depth_1 = depth;       // New depth becomes max
      }
      else if (depth > max_depth_2)
      {
        max_depth_2 = depth; // New depth sneaks into second place
      }
    }

    // INTERCEPT & UPDATE: The longest path curving at 'curr'
    max_dia = max(max_dia, max_depth_1 + max_depth_2);

    // RETURN HEIGHT: The depth to return to the parent is the deepest child + 1
    // (The +1 accounts for the edge connecting 'curr' to that child)
    return max_depth_1 + 1;
  }

public:
  int treeDiameter(int n, vector<vector<int>> &edges)
  {
    // Base case: A tree with 0 or 1 node has no edges, thus diameter is 0
    if (n <= 1)
      return 0;

    // Step 1: Build the Adjacency List (1-indexed based on problem constraints)
    vector<vector<int>> adj(n + 1);
    for (const auto &edge : edges)
    {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    int max_dia = 0;

    // Step 2: Start DFS from an arbitrary root (node 1).
    // Parent is passed as 0 since node 1 has no parent.
    dfs(1, 0, adj, max_dia);

    return max_dia;
  }
};

/**
 * ============================================================================
 * DRIVER CODE (LOCAL TESTING)
 * ============================================================================
 * This main method simulates the testing environment. It sets up the N-ary
 * tree inputs exactly as they would be passed into the LeetCode method signature
 * and prints the resulting diameter.
 * ============================================================================
 */
int main()
{
  // Fast I/O (Optional, but good practice for competitive programming)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Solution sol;

  // ---------------------------------------------------------
  // TEST CASE 1: Standard Multi-branch Tree
  // ---------------------------------------------------------
  /*
          1
         / \
        2   3
           / \
          4   5
  */
  int n1 = 5;
  vector<vector<int>> edges1 = {
      {1, 2},
      {1, 3},
      {3, 4},
      {3, 5}};

  cout << "Test Case 1:" << "\n";
  cout << "Expected Output: 3" << "\n";
  cout << "Actual Output:   " << sol.treeDiameter(n1, edges1) << "\n\n";

  // ---------------------------------------------------------
  // TEST CASE 2: Linear Tree (Linked List shape)
  // ---------------------------------------------------------
  /*
        1 --- 2 --- 3 --- 4 --- 5
  */
  int n2 = 5;
  vector<vector<int>> edges2 = {
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 5}};

  cout << "Test Case 2:" << "\n";
  cout << "Expected Output: 4" << "\n";
  cout << "Actual Output:   " << sol.treeDiameter(n2, edges2) << "\n\n";

  // ---------------------------------------------------------
  // TEST CASE 3: Base Case (Single Node)
  // ---------------------------------------------------------
  int n3 = 1;
  vector<vector<int>> edges3 = {}; // No edges for a single node

  cout << "Test Case 3 (Single Node):" << "\n";
  cout << "Expected Output: 0" << "\n";
  cout << "Actual Output:   " << sol.treeDiameter(n3, edges3) << "\n\n";

  return 0;
}
