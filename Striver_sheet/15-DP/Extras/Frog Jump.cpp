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

1. Title: Frog Jump Leetcode

Links:
https://leetcode.com/problems/frog-jump/description/


Problem statement:
A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be 1 unit.

If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.


Example 1:
Input: stones = [0,1,3,5,6,8,12,17]
Output: true
Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.

Example 2:
Input: stones = [0,1,2,3,4,8,9,11]
Output: false
Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.


Constraints:
2 <= stones.length <= 2000
0 <= stones[i] <= 231 - 1
stones[0] == 0
stones is sorted in a strictly increasing order.

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Frog Jump (Leetcode Hard) - Top-Down DP approach
//-------------------------------------------------------------------------------

class Solution
{
public:
  /*
   * Recursive Helper Method: rec
   * ----------------------------
   * Solves the problem using Top-Down Dynamic Programming (Memoization).
   * * State:
   * - idx: The index of the current stone we are standing on.
   * - prevJump: The jump distance used to reach this current stone.
   * * Logic:
   * From the current state, try three possible next jumps:
   * 1. prevJump - 1
   * 2. prevJump
   * 3. prevJump + 1
   * * If any of these jumps land on a valid stone and eventually lead to the last stone, return true.
   */
  bool rec(int idx, int prevJump, vector<int> &stones, vector<vector<int>> &DP)
  {

    // Base Case: If we reached the last stone, we succeeded.
    if (idx == stones.size() - 1)
    {
      return true;
    }

    // Memoization Check: If this state is already computed, return it.
    if (DP[idx][prevJump] != -1)
    {
      return DP[idx][prevJump];
    }

    // Try all 3 possible adjustments to the jump size: k = -1, 0, 1
    for (int k = -1; k <= 1; k++)
    {

      int nextJump = prevJump + k;

      // Constraint: We can only jump forward (distance > 0)
      if (nextJump <= 0)
      {
        continue;
      }

      // Calculate the target position value
      int nextPos = stones[idx] + nextJump;

      // Search for the stone at 'nextPos'
      // Current Strategy: Binary Search using lower_bound.
      // Time Cost: O(log N) per transition.

      // ALTERNATIVE APPROACH NOTE:
      // Instead of O(log N) binary search here, we could have pre-processed the 'stones' array
      // into an unordered_map<int, int> (StoneValue -> Index) in the main function.
      // That would allow O(1) checking here, reducing total time complexity from O(N^2 log N) to O(N^2).
      auto it = lower_bound(stones.begin(), stones.end(), nextPos);

      // Check if the stone actually exists at the calculated position
      if (it != stones.end() && *it == nextPos)
      {

        // Convert iterator to index
        int newIdx = distance(stones.begin(), it);

        // Recurse to the next stone
        bool ret = rec(newIdx, nextJump, stones, DP);

        // If any path leads to victory, cache true and return
        if (ret)
        {
          return DP[idx][prevJump] = true;
        }
      }
    }

    // If no path works from here, mark as false (dead end)
    return DP[idx][prevJump] = false;
  }

  /*
   * Main Method: canCross
   * ---------------------
   *
   * * * CRITICAL NOTE ON DIRECTION:
   * This simple DP approach relies heavily on the problem statement:
   * "The frog can only jump in the forward direction."
   * * 1. Forward Constraint: This ensures that 'prevJump' is always positive (> 0).
   * Because 'prevJump' is positive, we can directly use it as an index in our
   * DP table `DP[idx][prevJump]`.
   * * 2. What if Backward Jumps were allowed?
   * If the frog could jump backwards (negative direction), 'prevJump' could be negative.
   * - A negative 'prevJump' cannot be used as a vector index directly. We would need
   * to handle this specially (e.g., adding an offset to the index like `DP[idx][jump + 2000]`
   * or using a Hash Map).
   * - Furthermore, backward jumps could create infinite cycles (A -> B -> A), turning
   * this from a Directed Acyclic Graph (DAG) problem into a General Graph cycle detection problem.
   * * * State:
   * - idx: The index of the current stone we are standing on.
   * - prevJump: The jump distance used to reach this current stone.
   *
   * Complexity Analysis:
   * * Time Complexity: O(N^2 * log N)
   * - There are N stones. In the worst case, we can reach a stone with up to N different jump sizes.
   * - Total DP states = O(N^2).
   * - Inside each state, we perform 3 binary searches (lower_bound), taking O(log N).
   * - Total: O(N^2 log N).
   * * Space Complexity: O(N^2)
   * - Used by the DP table of size N x N.
   * - (Recursion stack depth is at most O(N)).
   */
  bool canCross(vector<int> &stones)
  {

    int N = stones.size();

    // Edge Case: The first jump MUST be 1 unit.
    // If stone[1] is not at position 1, we can't start.
    if (stones[1] - stones[0] != 1)
    {
      return false;
    }

    // DP Initialization
    // DP[i][j] stores whether index 'i' is solvable given arrival jump 'j'.
    // Size: N x (N+1) because the max possible jump size to reach index i is roughly i (bounded by N).
    vector<vector<int>> DP(N, vector<int>(N + 1, -1));

    // Start recursion from Index 1, having arrived with a jump of size 1.
    int startIdx = 1;
    int jump = 1;

    return rec(startIdx, jump, stones, DP);
  }
};

int main()
{
  return 0;
}
