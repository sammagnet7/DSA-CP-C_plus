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

1. Title: Course Schedule I and II | Pre-requisite Tasks | Topological Sort: G-24


Links:
https://takeuforward.org/data-structure/course-schedule-i-and-ii-pre-requisite-tasks-topological-sort-g-24/
https://www.youtube.com/watch?v=WAOfKpxYHR8
https://takeuforward.org/plus/dsa/problems/course-schedule-ii?tab=editorial

Problem statement:
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.


    Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: true
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0. So it is possible.

    Example 2:
    Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
    Output: false
    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.


Constraints:
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title: Course Schedule II | Topological Sort: G-24


Links:
https://takeuforward.org/data-structure/course-schedule-i-and-ii-pre-requisite-tasks-topological-sort-g-24/
https://www.youtube.com/watch?v=WAOfKpxYHR8
https://takeuforward.org/plus/dsa/problems/course-schedule-ii?tab=editorial


Problem statement:
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

Examples:
    Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: [0,1]
    Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

    Example 2:
    Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    Output: [0,2,1,3]
    Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
    So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

    Example 3:
    Input: numCourses = 1, prerequisites = []
    Output: [0]


Constraints:
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    ai != bi
    All the pairs [ai, bi] are distinct.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Course Schedule I and II | Pre-requisite Tasks | Topological Sort: G-24
    //-------------------------------------------------------------------------------

    /**
     * @brief Determines if all courses can be finished given prerequisites
     *
     * Problem:
     * We are given `numCourses` and a list of prerequisite pairs where
     * [a, b] means "to take course a, you must first take course b".
     *
     * This forms a directed graph:
     *  - Each course is a vertex.
     *  - Each prerequisite [a, b] is a directed edge b → a.
     *
     * We need to check if the graph contains a cycle:
     *  - If there is a cycle, not all courses can be finished.
     *  - If it's a DAG (Directed Acyclic Graph), all courses can be scheduled.
     *
     * Approach: **Topological Sort using BFS (Kahn's Algorithm)**
     *  - Count indegree (number of incoming edges) for all nodes.
     *  - Start with nodes having indegree = 0 (no prerequisites).
     *  - Remove them from the graph, reduce indegree of their neighbors.
     *  - Continue until no nodes remain.
     *  - If we processed all nodes → no cycle → return true.
     *  - Else → cycle exists → return false.
     *
     * Time Complexity: O(V + E)
     *  - V = numCourses
     *  - E = number of prerequisites
     * Space Complexity: O(V + E)
     *  - Adjacency list: O(E)
     *  - Indegree array: O(V)
     *  - Queue: O(V)
     */

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        int V = numCourses;
        vector<vector<int>> &edges = prerequisites;

        // Step 1: Build adjacency list and indegree array
        // adjL[u] = list of nodes v such that u → v
        vector<vector<int>> adjL(V);
        vector<int> indegree(V, 0);

        for (auto &e : edges)
        {
            // e[0] depends on e[1], so edge e[1] → e[0]
            adjL[e[1]].push_back(e[0]);
            indegree[e[0]]++; // Increase indegree of dependent node
        }

        queue<int> q;    // Queue for BFS
        vector<int> ans; // Stores topological order

        // Step 2: Push all nodes with indegree 0 into the queue
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // Step 3: Process nodes using BFS
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);

            // Reduce indegree of neighbors
            for (int adj : adjL[node])
            {
                indegree[adj]--;
                if (indegree[adj] == 0)
                {
                    q.push(adj);
                }
            }
        }

        // If all courses are processed (ans.size() == V), no cycle exists → return true
        // Else, cycle exists → return false
        return (ans.size() == V);
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Course Schedule II | Topological Sort: G-24
    //-------------------------------------------------------------------------------

    /**
     * @brief Returns a valid course order if possible, otherwise an empty list.
     *
     * Problem:
     * - We are given `numCourses` and prerequisites as pairs [a, b], meaning
     *   "to take course a, you must first take course b".
     * - This forms a directed graph:
     *      Each course = vertex
     *      [a, b] = directed edge b → a (b must come before a)
     *
     * Goal:
     * - Return one possible ordering of courses such that all prerequisites
     *   are satisfied.
     * - If impossible (cycle exists), return an empty list.
     *
     * Approach: **Topological Sort using Kahn's Algorithm (BFS)**
     *
     * Key idea:
     * - A node can appear in the topological order only after all its prerequisites
     *   (incoming edges) are processed.
     * - Nodes with indegree = 0 (no prerequisites) can be taken first.
     *
     * Steps:
     * 1. Build adjacency list so that adjL[b] contains all courses dependent on b.
     *    This ensures the BFS traversal naturally produces the correct order.
     * 2. Compute indegree for each course (number of prerequisites).
     * 3. Initialize queue with all courses having indegree = 0.
     * 4. Process nodes in BFS manner:
     *    - Pop a node, add it to the answer list.
     *    - For each neighbor, decrement indegree. If indegree becomes 0, push neighbor.
     * 5. If all courses are processed (ans.size() == numCourses), return ans.
     *    Otherwise, return empty list (cycle detected).
     *
     * Advantages of this tweak:
     * - By building adjacency in reverse dependency order (b → a),
     *   the resulting BFS order is already valid topological order.
     * - No need to reverse the answer at the end.
     *
     * Time Complexity: O(V + E)
     * - V = numCourses, E = number of prerequisites
     * - Building adjacency list and indegree: O(E)
     * - BFS traversal: O(V + E)
     *
     * Space Complexity: O(V + E)
     * - Adjacency list: O(E)
     * - Indegree array: O(V)
     * - Queue: O(V)
     */

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        int V = numCourses;
        vector<vector<int>> &edges = prerequisites;

        // Step 1: Build adjacency list and indegree array
        // adjL[u] = list of courses that u depends on
        vector<vector<int>> adjL(V);
        vector<int> indegree(V, 0);

        for (auto &e : edges)
        {
            adjL[e[1]].push_back(e[0]); // Edge: b → a (a depends on b)
            indegree[e[0]]++;           // // Increment indegree of dependent course
        }

        queue<int> q;
        vector<int> ans;

        // Step 2: Push all nodes with indegree 0 into queue (courses with no prerequisites)
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // Step 3: Process nodes in BFS manner
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);

            // Reduce indegree of neighbors
            for (int adj : adjL[node])
            {
                indegree[adj]--;
                if (indegree[adj] == 0)
                {
                    q.push(adj);
                }
            }
        }

        // If all courses processed, return reversed order
        if (ans.size() != V)
        {
            return {}; // Cycle detected → no valid ordering
        }

        // reverse(ans.begin(), ans.end());  // Reverse because of dependency direction

        // No need to reverse, adjacency list ensures correct order
        return ans;
    }
};

int main()
{
    return 0;
}
