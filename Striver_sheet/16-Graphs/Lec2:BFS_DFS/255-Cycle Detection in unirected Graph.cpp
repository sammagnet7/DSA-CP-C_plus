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

1. Title: Detect Cycle in an Undirected Graph (using BFS / DFS)


Links:
https://takeuforward.org/data-structure/detect-cycle-in-an-undirected-graph-using-bfs/
https://www.youtube.com/watch?v=BPlrALf1LDU
https://takeuforward.org/data-structure/detect-cycle-in-an-undirected-graph-using-dfs/
https://www.youtube.com/watch?v=zQ3zgFypzX4
https://takeuforward.org/plus/dsa/problems/detect-a-cycle-in-an-undirected-graph?tab=editorial
https://www.naukri.com/code360/problems/cycle-detection-in-undirected-graph_1062670?leftPanelTabValue=PROBLEM



Problem statement:
You have been given an undirected graph with 'N' vertices and 'M' edges. The vertices are labelled from 1 to 'N'.
Your task is to find if the graph contains a cycle or not.
A path that starts from a given vertex and ends at the same vertex traversing the edges only once is called a cycle.

Note:
    1. There are no parallel edges between two vertices.
    2. There are no self-loops(an edge connecting the vertex to itself) in the graph.
    3. The graph can be disconnected.

Example :
    In the below graph, there exists a cycle between vertex 1, 2 and 3.
    Input: N = 3 , Edges =  [[1, 2], [2, 3], [1, 3]].
    Output: Yes
    Explanation : There are a total of 3 vertices in the graph. There is an edge between vertex 1 and 2, vertex 2 and 3 and vertex 1 and 3. So, there exists a cycle in the graph.


Constraints:
    1 <= T <= 10
    1 <= N <= 5000
    0 <= M <= min(5000, (N * (N - 1)) / 2)
    1 <= edges[i][0] <= N
    1 <= edges[i][1] <= N


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
    // 1. Title: Detect Cycle in an Undirected Graph (using BFS / DFS)
    //-------------------------------------------------------------------------------

    //---------------------------------------------------------
    //               Approach1: using DFS
    //--------------------------------------------------------

    /**
     * Helper Function: isCyclicDFS
     * Detects if there is a cycle in an undirected graph using DFS.
     *
     * @param cur     Current node being visited.
     * @param parent  The node from which 'cur' was reached (to avoid false cycle detection).
     * @param adjL    Adjacency list representation of the graph.
     * @param vis     Visited array to track visited nodes.
     *
     * Approach:
     *  - Mark the current node as visited.
     *  - For each adjacent node:
     *      - If the node is not visited, recursively call DFS.
     *      - If the node is visited and it is not the parent, then a cycle exists.
     *
     * @return true if a cycle is found, false otherwise.
     *
     * Time Complexity: O(N + E), where N = number of vertices, E = number of edges.
     * Space Complexity: O(N) for visited array + O(N) recursion stack in the worst case.
     */
    bool isCyclicDFS(int cur, int parent, vector<vector<int>> &adjL, vector<int> &vis)
    {
        vis[cur] = 1; // Mark current node as visited

        // Explore all adjacent nodes
        for (int node : adjL[cur])
        {
            if (!vis[node])
            {
                // Recurse for the unvisited neighbor
                bool ret = isCyclicDFS(node, cur, adjL, vis);
                if (ret)
                {
                    return true; // Cycle found in deeper DFS
                }
            }
            // If neighbor is visited and it's not the parent, we found a cycle
            else if (node != parent)
            {
                return true;
            }
        }

        return false; // No cycle found from this node
    }

    //---------------------------------------------------------
    //               Approach2: using BFS
    //--------------------------------------------------------

    /**
     * Helper Function: isCyclicBFS
     * Detects if there is a cycle in an undirected graph using BFS traversal.
     *
     * @param cur     Starting node for BFS traversal.
     * @param adjL    Adjacency list representation of the graph.
     * @param vis     Visited array to keep track of visited nodes.
     *
     * Approach:
     *  - Use BFS with a queue that stores (node, parent) pairs.
     *  - Start from 'cur' and mark it as visited.
     *  - For each node in the queue:
     *      - Explore all adjacent nodes:
     *          - If the adjacent node is not visited, mark it visited and push into the queue with the current node as its parent.
     *          - If the adjacent node is visited and it is NOT the parent of the current node, then a cycle exists.
     *  - Continue until the queue is empty.
     *  - If no violation is found, the component has no cycle.
     *
     * Time Complexity: O(N + E), where N = number of vertices, E = number of edges.
     *                  - Each node is visited once, and each edge is checked at most twice.
     * Space Complexity: O(N) for visited array + O(N) for queue in worst case.
     *
     * @return true if a cycle is detected in the connected component, false otherwise.
     */
    bool isCyclicBFS(int cur, vector<vector<int>> &adjL, vector<int> &vis)
    {

        // Queue stores pairs: (node, parent)
        queue<pair<int, int>> q;

        q.push({cur, -1}); // Start BFS from 'cur', with parent as -1 (no parent)
        vis[cur] = 1;      // Mark starting node as visited

        // BFS traversal
        while (!q.empty())
        {
            auto node = q.front().first;    // Current node
            auto parent = q.front().second; // Parent of the current node
            q.pop();

            // Traverse all adjacent nodes
            for (auto e : adjL[node])
            {
                if (!vis[e])
                {
                    // If neighbor is unvisited, mark it visited and push to queue
                    vis[e] = 1;
                    q.push({e, node});
                }
                // If neighbor is visited and is NOT the parent, cycle detected
                else if (e != parent)
                {
                    return true;
                }
            }
        }

        // No cycle found in this connected component
        return false;
    }

    /**
     * Main Function: cycleDetection
     * Detects whether an undirected graph contains a cycle.
     *
     * @param edges  List of edges where each edge is a pair [u, v].
     * @param n      Number of vertices in the graph.
     * @param m      Number of edges in the graph.
     *
     * Approach:
     *  - Build an adjacency list from the edge list.
     *  - Handle the special case where an edge is a self-loop (immediate cycle).
     *  - Perform DFS on each unvisited node to check for a cycle using isCyclicDFS.
     *
     * Time Complexity: O(N + E) for building adjacency list and DFS traversal.
     * Space Complexity: O(N + E) for adjacency list + O(N) for visited array + recursion stack.
     *
     * @return "Yes" if the graph contains a cycle, otherwise "No".
     */
    string cycleDetection(vector<vector<int>> &edges, int n, int m)
    {

        // Create adjacency list for the graph
        vector<vector<int>> adjL(n + 1);
        vector<int> vis(n + 1, 0); // Visited array initialized to 0

        // Build the adjacency list from edge list
        for (auto e : edges)
        {
            // Check for self-loop (cycle)
            if (e[0] == e[1])
                return "Yes";

            // Since the graph is undirected, add both connections
            adjL[e[0]].push_back(e[1]);
            adjL[e[1]].push_back(e[0]);
        }

        // Traverse all nodes to handle disconnected components
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            { // If node is not visited, start DFS

                // Approach 1:
                // bool ret = isCyclicDFS(i, -1, adjL, vis);

                // Approach2:
                bool ret = isCyclicBFS(i, adjL, vis);

                if (ret)
                    return "Yes"; // Cycle detected
            }
        }

        return "No"; // No cycle detected in any component
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
