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

using P = pair<int, int>;

class Solution
{
private:
  vector<P> robo_dist;
  vector<int> sorted_walls;
  int r;
  vector<vector<int>> dp;

  /**
   * ============================================================================
   * Method: brokenWallsCountInRange
   * ============================================================================
   * Intuition: Since walls are sorted, finding the number of walls in a range
   * is equivalent to finding the difference between their index boundaries.
   * * Logic: Uses std::lower_bound to find the first wall >= left_range, and
   * std::upper_bound to find the first wall > right_range. Subtracting the
   * iterators gives the exact count of walls inside [left_range, right_range].
   * * Time: O(log W) per call.
   * Space: O(1).
   * ============================================================================
   */
  int brokenWallsCountInRange(int left_range, int right_range)
  {
    auto left_point = lower_bound(sorted_walls.begin(), sorted_walls.end(), left_range);
    auto right_point = upper_bound(sorted_walls.begin(), sorted_walls.end(), right_range);

    return right_point - left_point;
  }

  /**
   * ============================================================================
   * Method: solve (Recursive State Machine)
   * ============================================================================
   * Intuition:
   * The core realization is that bullets stop when they hit other robots.
   * This means the infinite number line can be chunked into isolated segments
   * between adjacent robots. If we dynamically cap the bullet range of the
   * current robot so it never crosses the physical position (or the bullet path)
   * of the previous/next robot, we guarantee that no wall is ever double-counted.
   * * Logic:
   * 1. Check the memoization table `dp` for the state [roboidx][prev_fired_right].
   * 2. Calculate `cur_left_range`:
   * - If the previous robot fired Right, our Left bullet must start strictly
   * after where the previous bullet stopped.
   * - If it fired Left, the space is clear, so our Left bullet just stops
   * at the previous robot's physical body.
   * 3. Calculate `cur_right_range`:
   * - Our Right bullet travels its full distance, but stops exactly 1 unit
   * before hitting the next robot's physical body.
   * 4. Use Binary Search (`brokenWallsCountInRange`) to count the walls destroyed
   * in both scenarios (firing Left vs. firing Right).
   * 5. Recursively compute the best future outcome for both choices and return
   * the maximum.
   * * Time Complexity: O(R * log W)
   * There are R robots and 2 possible states for `prev_fired_right`, leading
   * to exactly 2*R unique DP states. For each state, we perform an O(log W)
   * binary search to count walls.
   * * Space Complexity: O(R)
   * The recursive call stack goes up to maximum depth R.
   * ============================================================================
   */
  int solve(int roboidx, bool prev_fired_right)
  {

    if (roboidx == r)
    {
      return 0;
    }

    if (dp[roboidx][prev_fired_right] != -1)
    {
      return dp[roboidx][prev_fired_right];
    }

    auto [cur_robo_pos, cur_fire_dist] = robo_dist[roboidx];

    int cur_left_range = cur_robo_pos;
    int cur_right_range = cur_robo_pos;

    // --- Left Boundary Calculation ---
    if (prev_fired_right)
    {
      int prev_robo_pos = robo_dist[roboidx - 1].first;
      int prev_fire_dist = robo_dist[roboidx - 1].second;
      int prev_right_range = min(prev_robo_pos + prev_fire_dist, cur_robo_pos - 1);

      cur_left_range = max(cur_robo_pos - cur_fire_dist, prev_right_range + 1);
    }
    else
    {
      int prev_robo_pos = 0;
      if (roboidx != 0)
      {
        prev_robo_pos = robo_dist[roboidx - 1].first;
      }
      cur_left_range = max(prev_robo_pos + 1, cur_robo_pos - cur_fire_dist);
    }

    // --- Right Boundary Calculation ---
    if (roboidx < r - 1)
    {
      int next_robo_pos = robo_dist[roboidx + 1].first;
      cur_right_range = min(cur_robo_pos + cur_fire_dist, next_robo_pos - 1);
    }
    else
    {
      cur_right_range = cur_robo_pos + cur_fire_dist;
    }

    // --- State Transitions ---
    int fire_left = brokenWallsCountInRange(cur_left_range, cur_robo_pos) + solve(roboidx + 1, false);

    int fire_right = brokenWallsCountInRange(cur_robo_pos, cur_right_range) + solve(roboidx + 1, true);

    return dp[roboidx][prev_fired_right] = max(fire_left, fire_right);
  }

public:
  /**
   * ============================================================================
   * Method: maxWalls
   * ============================================================================
   * Intuition:
   * To process the robots from left to right, we must first sort them by their
   * physical coordinates on the 1D line. Sorting the walls allows us to use
   * lightning-fast binary searches to count destroyed walls within any range.
   * * Logic:
   * 1. Bundle `robots[i]` and `distance[i]` into pairs so their distances move
   * with them when sorted by position.
   * 2. Sort the robots array and the walls array in ascending order.
   * 3. Initialize the DP table with dimensions (R + 1) x 2, filled with -1.
   * 4. Trigger the recursive `solve` function starting at the 0th robot.
   * * Time Complexity: O(R log R + W log W)
   * Sorting the robots takes O(R log R) and sorting the walls takes O(W log W).
   * Combined with the solve() method, the total Time Complexity is
   * O(R log R + W log W + R log W).
   * * Space Complexity: O(R + W)
   * We allocate O(R) space for the `robo_dist` pairs and `dp` table, and
   * O(W) space for the `sorted_walls` copy.
   * ============================================================================
   */
  int maxWalls(vector<int> &robots, vector<int> &distance, vector<int> &walls)
  {

    r = robots.size();

    for (int i = 0; i < r; ++i)
    {
      robo_dist.push_back({robots[i], distance[i]});
    }

    sorted_walls = walls;

    sort(robo_dist.begin(), robo_dist.end());
    sort(sorted_walls.begin(), sorted_walls.end());

    dp.assign(r + 1, vector<int>(2, -1));

    return solve(0, false);
  }
};

int main()
{
  return 0;
}
