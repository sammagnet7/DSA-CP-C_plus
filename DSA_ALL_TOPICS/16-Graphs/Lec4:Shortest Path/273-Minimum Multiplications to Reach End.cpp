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

1. Title: Minimum steps to reach end from start by performing multiplication and mod operations with array elements

Links:
https://takeuforward.org/graph/g-39-minimum-multiplications-to-reach-end/
https://www.youtube.com/watch?v=_-0mx0SmYxA
https://takeuforward.org/plus/dsa/problems/minimum-multiplications-to-reach-end?tab=editorial
https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1


Problem statement:
Given start, end and an array arr of n numbers. At each step, start is multiplied with any number in the array and then mod operation with 100000 is done to get the new start.
Your task is to find the minimum steps in which end can be achieved starting from start. If it is not possible to reach end, then return -1.

Example:
    Input:
    arr[] = {2, 5, 7}
    start = 3, end = 30
    Output:
    2
    Explanation:
    Step 1: 3*2 = 6 % 100000 = 6
    Step 2: 6*5 = 30 % 100000 = 30
    Example 2:

    Input:
    arr[] = {3, 4, 65}
    start = 7, end = 66175
    Output:
    4
    Explanation:
    Step 1: 7*3 = 21 % 100000 = 21
    Step 2: 21*3 = 63 % 100000 = 63
    Step 3: 63*65 = 4095 % 100000 = 4095
    Step 4: 4095*65 = 266175 % 100000 = 66175

Expected Time Complexity: O(105)
Expected Space Complexity: O(105)

Constraints:
    1 <= n <= 104
    1 <= arr[i] <= 104
    1 <= start, end < 105



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

//-------------------------------------------------------------------------------
// 1. Title: G-39: Minimum Multiplications to Reach End
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    /*
     * Method: minimumMultiplications
     * ------------------------------
     * This method finds the minimum number of multiplications to transform a `start` number
     * into an `end` number, using a given set of multipliers in `arr`, with all operations
     * performed modulo 100000.
     *
     * **Intuition:**
     * The problem can be modeled as a shortest path problem on an unweighted graph. Each number
     * from 0 to 99999 represents a node in the graph. An edge exists from node 'u' to 'v'
     * if 'v' can be reached from 'u' by a single multiplication with a factor from `arr`
     * (i.e., `v = (u * x) % 100000`). Since each multiplication is a single step, all edge
     * weights are implicitly 1. Breadth-First Search (BFS) is the optimal algorithm for
     * finding the shortest path in an unweighted graph, as it explores all nodes at a given
     * distance from the source before moving to the next distance level.
     *
     * **Algorithm:**
     * 1. **Initialization**:
     * - A `minDist` array of size 100000 is used to store the minimum number of multiplications
     * to reach each number, initialized to infinity.
     * - A queue for BFS is created to store pairs `{distance, node}`.
     * - The starting node `start` is initialized with a distance of 0 and pushed into the queue.
     * 2. **BFS Traversal**:
     * - The loop continues as long as the queue is not empty.
     * - In each iteration, the node `u` with the smallest distance `d` is dequeued.
     * - For each multiplier `mul` in `arr`, a new number `v` is calculated: `v = (u * mul) % 100000`.
     * - If the new distance to `v` (`d + 1`) is less than the current `minDist[v]`, it means
     * we've found a shorter path. We update `minDist[v]`, and if `v` is the `end` node,
     * we can return `d + 1` immediately, as BFS guarantees the shortest path is found first.
     * - The new state `{d + 1, v}` is enqueued for future exploration.
     * 3. **Termination**:
     * - The function returns the minimum multiplications if the `end` node is reached.
     * - If the queue becomes empty and the `end` node has not been reached, it signifies
     * that `end` is unreachable from `start`. In this case, -1 is returned.
     *
     * **Complexity:**
     * - **Time**: O(100000 * N), where N is the size of the `arr` array. In the worst case, we might visit every number from 0 to 99999, and for each number, we iterate through all `N` multipliers.
     * - **Space**: O(100000), dominated by the `minDist` array and the queue, which can hold up to 100000 elements in the worst case.
     */
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        // Edge case: if start and end are the same, no multiplications are needed.
        if (start == end)
            return 0;

        // `minDist` array to store the minimum number of multiplications to reach each number.
        // Initialized with INT_MAX to represent unvisited nodes. The size is 100000 because
        // all numbers are modulo 100000, ranging from 0 to 99999.
        vector<int> minDist(100000, INT_MAX);

        // Queue for BFS. It stores pairs of `{number_of_multiplications, current_number}`.
        queue<pair<int, int>> q;

        // Initialize the starting node. The distance to itself is 0.
        minDist[start] = 0;
        q.push({0, start});

        // Modulo value is 100000 as per the problem constraints.
        int mod = 100000;

        // Begin the BFS traversal.
        while (!q.empty())
        {
            // Get the number of multiplications (distance) and the current number (node).
            int d = q.front().first;
            int u = q.front().second;
            q.pop();

            // Iterate through all the multiplication factors provided in `arr`.
            for (int mul : arr)
            {

                // Calculate the next number by applying the multiplication and modulo.
                // Using `1LL` ensures the multiplication doesn't overflow a 32-bit integer before the modulo.
                int v = (1LL * u * mul) % mod;

                // Check if the path through the current node 'u' to 'v' is shorter
                // than any previously found path.
                if (d + 1 < minDist[v])
                {
                    // Update the minimum distance to the new number 'v'.
                    minDist[v] = d + 1;

                    // Optimization: If we've reached the target 'end' node, we can return immediately
                    // because BFS guarantees the first time we reach a node, it's via a shortest path.
                    if (v == end)
                    {
                        return d + 1;
                    }

                    // Push the new number and its distance to the queue for further exploration.
                    q.push({d + 1, v});
                }
            }
        }

        // If the queue becomes empty and the 'end' node was never reached, it's unreachable.
        return -1;
    }
};

int main()
{

    return 0;
}