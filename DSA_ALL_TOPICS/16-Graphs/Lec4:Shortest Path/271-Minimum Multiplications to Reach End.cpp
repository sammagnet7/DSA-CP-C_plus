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
Given start, end and an array arr of n numbers. At each step, start is multiplied with any number in the array and then mod operation with 10^5 is done to get the new start.
Your task is to find the minimum steps in which end can be achieved starting from start. If it is not possible to reach end, then return -1.

Example 1:
    Input:
        arr[] = {2, 5, 7}
        start = 3, end = 30
    Output:
        2
    Explanation:
        Step 1: 3*2 = 6 % 10^5 = 6
        Step 2: 6*5 = 30 % 10^5 = 30

Example 2:
    Input:
        arr[] = {3, 4, 65}
        start = 7, end = 66175
    Output:
        4
    Explanation:
        Step 1: 7*3 = 21 % 10^5 = 21
        Step 2: 21*3 = 63 % 10^5 = 63
        Step 3: 63*65 = 4095 % 10^5 = 4095
        Step 4: 4095*65 = 266175 % 10^5 = 66175

Expected Time Complexity: O(10^5)
Expected Space Complexity: O(10^5)

Constraints:
    1 <= n <= 10^4
    1 <= arr[i] <= 10^4
    1 <= start, end < 10^5



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
// 1. Title: Minimum Multiplications to Reach End
//-------------------------------------------------------------------------------

class Solution
{
    const int MOD = 1e5;

public:
    //============================================================================
    // Approach 1 — Breadth-First Search (Shortest Path in an Implicit Graph)
    //============================================================================

    /**
     * @brief Finds the minimum number of multiplications to reach the `end` state.
     *
     * Idea & Intuition:
     * - Even though this looks like a math problem, it perfectly maps to a Graph Theory
     * problem! Every number between 0 and 99999 (due to modulo 1e5) represents a "Node".
     * - Multiplying a number by an element in `arr` represents traversing a directed "Edge".
     * - Because every multiplication takes exactly 1 step, this is an Unweighted Graph.
     * Therefore, Breadth-First Search (BFS) is mathematically guaranteed to find the
     * shortest path to the destination first.
     *
     * Understanding (The Modulo Graph Constraint):
     * - Without the modulo, the numbers would grow to infinity, meaning an infinite number
     * of nodes. Because of `% 100000`, we know our graph has exactly 100,000 possible
     * states. This allows us to use a fixed-size `steps` array acting as our visited map!
     *
     * Approach:
     * 1. Edge Case: If `start == end` right away, it takes 0 steps.
     * 2. Initialization:
     * - Create a `steps` array of size 100,000 initialized to `1e9` (infinity).
     * - Push the `start` node into the BFS queue and set `steps[start] = 0`.
     * 3. BFS Traversal:
     * - Pop `curN` from the queue.
     * - Iterate through every multiplier in `arr`.
     * - Calculate the next node: `newN = (curN * arr[i]) % MOD`. (Use `long long` to
     * prevent integer overflow during the multiplication!).
     * - EARLY EXIT: If `newN == end`, we have found our target. Immediately return
     * `steps[curN] + 1` to save massive amounts of CPU time.
     * - If `steps[newN]` is still `1e9` (unvisited), update its steps and push it
     * into the queue.
     * 4. Return -1 if the queue empties and we never found the target.
     *
     * Time Complexity:
     * - O(100,000 * N): Where N is the size of the `arr`. In the absolute worst case,
     * we visit all 100,000 possible states exactly once, and for each state, we loop
     * through the `arr` to find its neighbors.
     *
     * Space Complexity:
     * - O(100,000): The `steps` array is strictly bounded to 100,000 integers. The BFS
     * queue will also hold at most 100,000 elements.
     */
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {

        // --- STEP 1: Edge Case ---
        if (start == end)
        {
            return 0;
        }

        // --- STEP 2: Initialization ---
        // Array tracks both the visited state and the minimum steps to reach that state
        vector<int> steps(1e5, 1e9);
        queue<int> q;

        q.push(start);
        steps[start] = 0;

        // --- STEP 3: BFS Traversal ---
        while (!q.empty())
        {

            auto curN = q.front();
            q.pop();

            for (int i = 0; i < arr.size(); ++i)
            {

                // Calculate next state (cast to long long to prevent multiplication overflow)
                long long newN = ((long long)curN * arr[i]) % MOD;

                // EARLY EXIT OPTIMIZATION:
                // Stop the entire algorithm the exact second we calculate the target!
                if (newN == end)
                {
                    return steps[curN] + 1;
                }

                // If this state has not been visited yet
                if (steps[newN] == 1e9)
                {
                    steps[newN] = steps[curN] + 1;
                    q.push(newN);
                }
            }
        }

        // --- STEP 4: Target Unreachable ---
        return -1;
    }
};

int main()
{

    return 0;
}