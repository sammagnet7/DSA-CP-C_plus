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

1. Title: Maximum Walls Destroyed by Robots


Links:
https://leetcode.com/problems/maximum-walls-destroyed-by-robots/description/


Problem statement:
There is an endless straight line populated with some robots and walls. You are given integer arrays robots, distance, and walls:
robots[i] is the position of the ith robot.
distance[i] is the maximum distance the ith robot's bullet can travel.
walls[j] is the position of the jth wall.
Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it immediately stops at that robot and cannot continue.

Return the maximum number of unique walls that can be destroyed by the robots.

Notes:
A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
Robots are not destroyed by bullets.


Example 1:
  Input: robots = [4], distance = [3], walls = [1,10]
  Output: 1
  Explanation:
  robots[0] = 4 fires left with distance[0] = 3, covering [1, 4] and destroys walls[0] = 1.
  Thus, the answer is 1.

Example 2:
  Input: robots = [10,2], distance = [5,1], walls = [5,2,7]
  Output: 3
  Explanation:
  robots[0] = 10 fires left with distance[0] = 5, covering [5, 10] and destroys walls[0] = 5 and walls[2] = 7.
  robots[1] = 2 fires left with distance[1] = 1, covering [1, 2] and destroys walls[1] = 2.
  Thus, the answer is 3.

Example 3:
  Input: robots = [1,2], distance = [100,1], walls = [10]
  Output: 0
  Explanation:
  In this example, only robots[0] can reach the wall, but its shot to the right is blocked by robots[1]; thus the answer is 0.



Constraints:
  1 <= robots.length == distance.length <= 10^5
  1 <= walls.length <= 10^5
  1 <= robots[i], walls[j] <= 10^9
  1 <= distance[i] <= 10^5
  All values in robots are unique
  All values in walls are unique



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
// 1. Title: Maximum Walls Destroyed by Robots
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * Approach: Top-Down DP (State Machine) + Binary Search + Range Pre-computation
 * ============================================================================
 * Concept:
 * Break the problem down into two clean phases:
 * 1. Pre-computation: We calculate the absolute maximum boundary `[L, R]` each
 * robot's bullet can reach before it is blocked by adjacent robots.
 * 2. State Machine DP: We iterate through the robots. For each robot, we decide
 * whether to fire Left or Right. We use the previous robot's decision
 * (`prevDir`) to dynamically adjust the current robot's Left bound, ensuring
 * we never double-count a wall.
 * ============================================================================
 * Complexity:
 * - Time: O(N log N + W log W + N * log W). Sorting the robots and walls takes
 * N log N and W log W. The DP visits N states exactly once (since prevDir
 * only has 2 states), and each state does an O(log W) binary search.
 * - Space: O(N) for the memoization table, range array, and recursion stack.
 * ============================================================================
 */

using P = pair<int, int>;

class Solution
{
public:
  // Memoization table: t[robot_index][previous_robot_direction]
  vector<vector<int>> t;

  // Helper: O(log W) query to count walls strictly within the interval [l, r]
  int countWalls(vector<int> &walls, int l, int r)
  {
    auto left = lower_bound(walls.begin(), walls.end(), l);
    auto right = upper_bound(walls.begin(), walls.end(), r);

    // The distance between the upper and lower iterators is exactly
    // the number of elements falling within the inclusive range.
    return right - left;
  }

  int solve(vector<int> &walls, vector<P> &roboDist, vector<P> &range, int i, int prevDir)
  {

    // Base Case: We have evaluated every robot
    if (i == roboDist.size())
      return 0;

    // Return cached result if this state was already computed
    if (t[i][prevDir] != -1)
      return t[i][prevDir];

    // Retrieve the pre-computed maximum leftward reach for this robot
    int leftStart = range[i].first;

    // --------------------------------------------------------
    // CRITICAL OVERLAP PREVENTION:
    // --------------------------------------------------------
    // If the previous robot fired Right (prevDir == 1), its bullet destroyed
    // everything up to `range[i-1].second`. To prevent double-counting
    // those walls, we must restrict our current Left bullet to start strictly
    // after the previous bullet's stopping point (+1).
    if (prevDir == 1)
    {
      leftStart = max(leftStart, range[i - 1].second + 1);
    }

    // Option A: Fire Left
    // Count walls destroyed to the left, then move to the next robot.
    // Pass `0` to signal the next robot that we fired Left.
    int leftTake = countWalls(walls, leftStart, roboDist[i].first) + solve(walls, roboDist, range, i + 1, 0);

    // Option B: Fire Right
    // Count walls destroyed to the right, then move to the next robot.
    // Pass `1` to signal the next robot that we fired Right.
    int rightTake = countWalls(walls, roboDist[i].first, range[i].second) + solve(walls, roboDist, range, i + 1, 1);

    // Cache and return the best choice
    return t[i][prevDir] = max(leftTake, rightTake);
  }

  int maxWalls(vector<int> &robots, vector<int> &distance, vector<int> &walls)
  {

    int n = robots.size();

    // Pair each robot's position with its bullet distance so they move
    // together when we sort by position.
    vector<P> roboDist(n);
    for (int i = 0; i < n; i++)
    {
      roboDist[i] = {robots[i], distance[i]};
    }

    sort(begin(roboDist), end(roboDist));
    sort(begin(walls), end(walls));

    // --------------------------------------------------------
    // Phase 1: Prepare the maximum physical ranges
    // --------------------------------------------------------
    vector<P> range(n);

    for (int i = 0; i < n; i++)
    {
      int pos = roboDist[i].first;
      int d = roboDist[i].second;

      // Determine the physical coordinates of the adjacent robots.
      // If there is no robot to the left/right, use the problem's constraints.
      int leftLimit = (i == 0) ? 1 : roboDist[i - 1].first + 1;
      int rightLimit = (i == n - 1) ? 1e9 : roboDist[i + 1].first - 1;

      // A bullet stops at either its max distance `d`, or when it hits
      // the adjacent robot's limit boundary.
      int L = max(pos - d, leftLimit);
      int R = min(pos + d, rightLimit);

      range[i] = {L, R};
    }

    // Initialize memoization table: N states, 2 possible previous directions
    t.assign(n + 1, vector<int>(2, -1));

    // Start recursion: At index 0, the "previous" direction doesn't matter
    // because there is no previous robot to overlap with. Passing 0 is safe.
    return solve(walls, roboDist, range, 0, 0);
  }
};

int main()
{
  return 0;
}
