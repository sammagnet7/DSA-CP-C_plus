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

1. Title: Connected Components | Logic Explanation

Links:
https://takeuforward.org/graph/connected-components-in-graphs/
https://www.youtube.com/watch?v=lea-Wl_uWXY
https://takeuforward.org/plus/dsa/problems/connected-components?tab=editorial
https://www.geeksforgeeks.org/problems/connected-components-in-an-undirected-graph/1    (Uses adjacency list as input)
https://www.naukri.com/code360/problems/dfs-traversal_630462?leftPanelTabValue=PROBLEM  (Uses adjacency list as input)

Similar problems:   
    Number of Provinces / Connected Components Problem in Matrix:
    https://takeuforward.org/data-structure/number-of-provinces/
    https://www.youtube.com/watch?v=ACzkVtewUYA
    https://leetcode.com/problems/number-of-provinces/description/   (Uses adjacency matrix as input)




Problem statement:
Given an undirected graph with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where each entry edges[i] = [u, v] denotes an edge between vertices u and v.
Your task is to return a list of all connected components. Each connected component should be represented as a list of its vertices, with all components returned in a collection where each component is listed separately.

Note: You can return the components in any order, driver code will print the components in sorted order.

Examples :
    Input: V = 5, edges[][] = [[0, 1], [2, 1], [3, 4]]
    Output: [[0, 1, 2], [3, 4]]
    Explanation:

    Input: V = 7, edges[][] = [[0, 1], [6, 0], [2, 4], [2, 3], [3, 4]]
    Output: [[0, 1, 6], [2, 3, 4], [5]]
    Explanation:

Constraints:
    1 ≤ V ≤ 105
    1 ≤ edges.size() ≤ 105
    0 <= edges[i][0], edges[i][1] < V


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title:

Links:


Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Connected Components
    //-------------------------------------------------------------------------------
    /*
           Function: traversDFS
           --------------------
           Recursive DFS traversal to explore all nodes in the same connected component.

           Parameters:
           - cur: Current node being processed.
           - adjL: Graph represented as adjacency list.
           - visited: Keeps track of visited nodes to avoid revisiting.
           - dfs: Stores nodes of the current connected component.

           Steps:
           1. Mark the current node as visited.
           2. Add the current node to the component list.
           3. Recursively explore all unvisited neighbors.

           Time Complexity:
           - Each node is visited exactly once → O(V)
           - Each edge is traversed exactly once → O(2E) for undirected graph
           - Overall: O(V + E)

           Space Complexity:
           - O(V) for visited array
           - O(V) for current component storage
           - O(V) for recursion stack (worst case skewed graph)
           - Overall: O(3V) ≈ O(V)
       */
    void traversDFS(int cur, vector<vector<int>> &adjL, vector<int> &visited, vector<int> &dfs)
    {
        visited[cur] = 1;   // Mark current node as visited
        dfs.push_back(cur); // Add current node to the component

        // Explore all neighbors of the current node
        for (auto e : adjL[cur])
        {
            if (!visited[e])
            {
                traversDFS(e, adjL, visited, dfs); // Recursive DFS call
            }
        }
    }

    /*
        Function: getComponents
        ------------------------
        Finds all connected components of an undirected graph using DFS.

        Parameters:
        - V: Number of vertices in the graph.
        - edges: List of edges where each edge is represented as {u, v}.

        Approach:
        1. Build an adjacency list from the given edges.
        2. Initialize a visited array to keep track of visited nodes.
        3. For each unvisited node, perform DFS to find its connected component.
        4. Collect all components into a result list.

        Time Complexity:
        - Building adjacency list: O(E)
        - DFS traversal for all nodes and edges: O(V + E)
        - Overall: O(V + E)

        Space Complexity:
        - Adjacency list: O(V + E)
        - Visited array: O(V)
        - DFS recursion stack and components: O(V)
        - Overall: O(V + E)
    */
    vector<vector<int>> getComponents(int V, vector<vector<int>> &edges)
    {
        int n = V;

        // Step 1: Build adjacency list
        vector<vector<int>> adj_list(n);
        for (int i = 0; i < edges.size(); i++)
        {
            int n1 = edges[i][0];
            int n2 = edges[i][1];

            adj_list[n1].push_back(n2);
            adj_list[n2].push_back(n1); // Because graph is undirected
        }

        vector<vector<int>> graph; // Stores all connected components
        vector<int> visited(n, 0); // Visited array

        // Step 2: Explore all nodes and find components
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> component; // Stores current component
                traversDFS(i, adj_list, visited, component);

                if (!component.empty())
                {
                    graph.push_back(component);
                }
            }
        }

        return graph;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
