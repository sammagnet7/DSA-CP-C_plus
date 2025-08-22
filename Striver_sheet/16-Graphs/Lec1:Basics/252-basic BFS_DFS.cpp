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

1. Title:

Links:
https://takeuforward.org/graph/breadth-first-search-bfs-level-order-traversal/
https://www.youtube.com/watch?v=-tgVpUgsQ5k
https://takeuforward.org/plus/dsa/problems/traversal-techniques?tab=editorial
https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1



Problem statement:
Given a connected undirected graph containing V vertices, represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Breadth First Search (BFS) traversal starting from vertex 0, visiting vertices from left to right according to the given adjacency list, and return a list containing the BFS traversal of the graph.
Note: Do traverse in the same order as they are in the given adjacency list.

Examples:
    Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
    Output: [0, 2, 3, 1, 4]
    Explanation: Starting from 0, the BFS traversal will follow these steps: 
    Visit 0 → Output: 0 
    Visit 2 (first neighbor of 0) → Output: 0, 2 
    Visit 3 (next neighbor of 0) → Output: 0, 2, 3 
    Visit 1 (next neighbor of 0) → Output: 0, 2, 3, 
    Visit 4 (neighbor of 2) → Final Output: 0, 2, 3, 1, 4

    Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
    Output: [0, 1, 2, 3, 4]
    Explanation: Starting from 0, the BFS traversal proceeds as follows: 
    Visit 0 → Output: 0 
    Visit 1 (the first neighbor of 0) → Output: 0, 1 
    Visit 2 (the next neighbor of 0) → Output: 0, 1, 2 
    Visit 3 (the first neighbor of 2 that hasn't been visited yet) → Output: 0, 1, 2, 3 
    Visit 4 (the next neighbor of 2) → Final Output: 0, 1, 2, 3, 4

Constraints:
    1 ≤ V = adj.size() ≤ 104
    1 ≤ adj[i][j] ≤ 104



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title:

Links:
https://takeuforward.org/data-structure/depth-first-search-dfs/
https://www.youtube.com/watch?v=Qzf1a--rhp8
https://takeuforward.org/plus/dsa/problems/traversal-techniques?tab=editorial
https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1


Problem statement:
Given a connected undirected graph containing V vertices represented by a 2-d adjacency list adj[][], where each adj[i] represents the list of vertices connected to vertex i. Perform a Depth First Search (DFS) traversal starting from vertex 0, visiting vertices from left to right as per the given adjacency list, and return a list containing the DFS traversal of the graph.
Note: Do traverse in the same order as they are in the given adjacency list.

Examples:
    Input: adj[][] = [[2, 3, 1], [0], [0, 4], [0], [2]]
    Output: [0, 2, 4, 3, 1]
    Explanation: Starting from 0, the DFS traversal proceeds as follows:
    Visit 0 → Output: 0 
    Visit 2 (the first neighbor of 0) → Output: 0, 2 
    Visit 4 (the first neighbor of 2) → Output: 0, 2, 4 
    Backtrack to 2, then backtrack to 0, and visit 3 → Output: 0, 2, 4, 3 
    Finally, backtrack to 0 and visit 1 → Final Output: 0, 2, 4, 3, 1

    Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3, 4], [2], [2]]
    Output: [0, 1, 2, 3, 4]
    Explanation: Starting from 0, the DFS traversal proceeds as follows: 
    Visit 0 → Output: 0 
    Visit 1 (the first neighbor of 0) → Output: 0, 1 
    Visit 2 (the first neighbor of 1) → Output: 0, 1, 2 
    Visit 3 (the first neighbor of 2) → Output: 0, 1, 2, 3 
    Backtrack to 2 and visit 4 → Final Output: 0, 1, 2, 3, 4

Constraints:
    1 ≤ V = adj.size() ≤ 104
    1 ≤ adj[i][j] ≤ 104


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: BFS
    //-------------------------------------------------------------------------------
    /*
    Function: bfs
    --------------------------------------
    Performs Breadth-First Search (BFS) traversal on a given graph represented as an adjacency list.

    Time Complexity:
    - O(N) for visiting all nodes.
    - O(2E) for traversing adjacency lists of all nodes (each edge is considered twice in an undirected graph).
    - Overall: O(N + 2E) ≈ O(N + E).

    Space Complexity:
    - O(N) for 'visited' array.
    - O(N) for 'bfs' result array.
    - O(N) for the queue in the worst case (when all nodes are in queue).
    - Overall: O(3N) ≈ O(N).

    Steps:
    1. Start BFS from node 0 (assuming graph is connected).
    2. Use a queue to process nodes level by level.
    3. Maintain a visited array to avoid revisiting nodes.
    4. For each node, push its unvisited neighbors into the queue.
*/
    vector<int> bfs(vector<vector<int>> &adjL)
    {

        int n = adjL.size(); // Total number of nodes

        vector<int> bfs;           // Stores BFS traversal order
        vector<int> visited(n, 0); // Marks visited nodes
        queue<int> q;              // Queue for BFS

        // Start BFS from node 0
        visited[0] = 1;
        q.push(0);

        // Process nodes in BFS manner
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            bfs.push_back(cur); // Add current node to result

            // Traverse all adjacent nodes of 'cur'
            for (auto e : adjL[cur])
            { // Loop runs for all edges → O(E) overall
                if (!visited[e])
                {
                    visited[e] = 1; // Mark as visited upon first encounter
                    q.push(e);      // Push neighbor into queue
                }
            }
        }

        return bfs; // Return BFS traversal order
    }

    //-------------------------------------------------------------------------------
    // 2. Title: DFS
    //-------------------------------------------------------------------------------

    /*
    Function: traversDFS (Helper Function)
    --------------------------------------
    Performs Depth-First Search (DFS) recursively starting from the current node.

    Parameters:
    - cur: Current node to process.
    - adjL: Graph represented as adjacency list.
    - visited: Array to keep track of visited nodes.
    - dfs: Stores DFS traversal order.

    Time Complexity:
    - Each node is visited exactly once → O(N)
    - Each edge is traversed exactly once → O(2E) for undirected graph
    - Overall: O(N + 2E) ≈ O(N + E)

    Space Complexity:
    - O(N) for visited array
    - O(N) for dfs result array
    - O(N) for recursion stack (worst case skewed tree)
    - Overall: O(3N) ≈ O(N)

    Steps:
    1. Mark the current node as visited.
    2. Add the node to DFS result.
    3. Recursively call DFS for all unvisited neighbors.
*/
    void traversDFS(int cur, vector<vector<int>> &adjL, vector<int> &visited, vector<int> &dfs)
    {

        visited[cur] = 1;   // Mark current node as visited
        dfs.push_back(cur); // Process current node

        // Explore all adjacent nodes of 'cur'
        for (auto e : adjL[cur])
        { // Iterates for all neighbors (degree of the node)
            if (!visited[e])
            {
                traversDFS(e, adjL, visited, dfs); // Recursive DFS call
            }
        }
    }

    /*
        Function: dfs
        --------------------------------------
        Wrapper function to perform DFS traversal on the graph.

        Assumes the graph is connected and starts traversal from node 0.

        Time Complexity:
        - O(N + E) for processing all nodes and edges.

        Space Complexity:
        - O(N) visited array + O(N) dfs result + O(N) recursion stack = O(3N) ≈ O(N)
    */
    vector<int> dfs(vector<vector<int>> &adjL)
    {

        int n = adjL.size();       // Number of nodes
        vector<int> visited(n, 0); // Visited array
        vector<int> dfs;           // Stores DFS traversal order

        traversDFS(0, adjL, visited, dfs); // Start DFS from node 0

        return dfs;
    }
};

int main()
{
    return 0;
}
