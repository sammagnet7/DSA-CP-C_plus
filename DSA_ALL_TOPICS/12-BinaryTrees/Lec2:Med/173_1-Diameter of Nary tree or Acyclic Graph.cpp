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
You are given a tree consisting of n nodes. The diameter of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the tree.

Example
Input: 5 1 2 1 3 3 4 3 5
Output: 3
Explanation: The diameter corresponds to the path 2 → 1 → 3 → 5.

Input Format
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n. Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Constraints
1  n  2.105 1  a,b  n

Output Format
Print one integer: the diameter of the tree.

Sample Input 0
2
1 2

Sample Output 0
1


INPUT::::::


OUTPUT::::::


*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
  Purpose:
    - Compute the longest distance (diameter measured in edges) in an undirected tree
      (or in the connected component reachable from node 1) using a single DFS.

  High-level intuition:
    - For every node `u`, the longest path that passes through `u` equals the sum of
      the two largest depths among its children (maxDepth + secMaxDepth).
    - While doing a DFS we compute for each node the maximum depth from that node down
      to any leaf in its DFS subtree (returned as height = maxDepth + 1).
    - We maintain a global `maxDist` (passed by reference) and update it at each node
      with (largest depth + second largest depth). After the DFS completes, `maxDist`
      is the diameter of the tree (maximum number of edges on any path).
    - This is the standard tree-diameter computation that runs in O(n) time.

  Assumptions and notes:
    - The input graph should be a tree (connected and acyclic) or at least connected.
      If the graph has multiple disconnected components, this program only explores
      the component reachable from node 1. If the graph contains cycles, the algorithm
      still avoids revisiting nodes because of the `vis` array, but the "diameter"
      semantics are correct only for trees / forests (for general graphs the problem
      is different).
    - Input format expected: a sequence of edge pairs (u v). The code reads pairs
      until EOF and constructs an undirected adjacency list.
    - The recursion depth equals the tree height; for very deep trees you may hit the
      recursion limit / stack overflow. Consider iterative methods for extreme depths.
    - `maxDist` is initialized in main to a very negative value; it will be updated
      during traversal. Using 0 would also be fine when graph has >= 1 node.

  Complexity:
    - Time: O(n) where n is the number of nodes visited (each edge is explored once).
    - Space: O(n) for adjacency list + O(depth) recursion stack (worst-case O(n)).
*/

#include <bits/stdc++.h>
using namespace std;

/*
  findMaxDist (DFS helper)

  Parameters:
    - cur    : current node being visited
    - adjL   : adjacency list (1-indexed)
    - vis    : visitation array, vis[x] != 0 means x is already visited
    - maxDist: reference to global maximum distance (updated in-place)

  Returns:
    - the maximum depth (height) from `cur` down to any leaf in its DFS subtree
      measured in number of edges; i.e., returns maxDepth + 1 where maxDepth is
      the largest child depth.

  Behavior and details:
    - Mark `cur` visited to avoid revisiting parent/ancestors.
    - Iterate through all neighbors; for every unvisited neighbor compute its depth
      recursively.
    - Maintain the two largest depths seen among children (maxDepth and secMaxDepth).
    - Use these two values to update `maxDist` with the longest path that passes
      through `cur` (which is maxDepth + secMaxDepth).
    - Finally return maxDepth + 1 (to include the edge from `cur` to its child).
*/
int findMaxDist(int cur, vector<vector<int>> &adjL, vector<int> &vis, int &maxDist)
{
  /* mark current node visited */
  vis[cur] = 1;

  /* keep track of the top two maximum child depths (in edges) */
  int maxDepth = 0;    // largest child depth
  int secMaxDepth = 0; // second largest child depth

  /* explore all neighbors (children in DFS tree) */
  for (int adjN : adjL[cur])
  {
    /* skip already visited nodes (this avoids going back to parent) */
    if (vis[adjN] != 0)
      continue;

    /* recursively compute depth for child subtree */
    int depth = findMaxDist(adjN, adjL, vis, maxDist);

    /* update the two largest depths seen so far */
    if (depth > maxDepth)
    {
      secMaxDepth = maxDepth;
      maxDepth = depth;
    }
    else if (depth > secMaxDepth)
    {
      secMaxDepth = depth;
    }
  }

  /* The longest path that goes through `cur` equals sum of the two largest child depths.
     Update global maximum distance (measured in edges). */
  maxDist = max(maxDist, (maxDepth + secMaxDepth));

  /* Return the depth of this node to its parent: the largest child depth + 1 (edge to child) */
  return (maxDepth + 1);
}

int main()
{
  /* Read undirected graph from stdin as a list of edge pairs until EOF.
     Expected input: pairs of integers "u v" (1-indexed nodes). */

  int n;
  cin >> n; /* number of nodes (used to size adjacency list) */

  /* adjacency list and visited array (1-indexed) */
  vector<vector<int>> adjL(n + 1);
  vector<int> vis(n + 1, 0);

  int u, v;
  /* Read remaining integers as edge pairs until EOF. For each pair (u,v) add
     undirected edge between u and v. This loop requires the input to contain
     pairs of numbers. If an odd number of ints remain, the last read may be undefined. */
  while (cin >> u)
  {
    cin >> v;
    adjL[u].push_back(v);
    adjL[v].push_back(u);
  }

  /* maxDist holds the diameter (maximum number of edges on any path).
     Initialize to a very small value so first computed path sets it. */
  int maxDist = -1000000000;

  /* Run DFS starting from node 1. This computes depths and updates maxDist. */
  findMaxDist(1, adjL, vis, maxDist);

  /* Print the result (diameter in edges) */
  cout << maxDist << endl;

  return 0;
}
