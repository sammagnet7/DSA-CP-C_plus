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

1. Title: Walking Robot Simulation II


Links:
https://leetcode.com/problems/walking-robot-simulation-ii/description/


Problem statement:
A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1, height - 1). The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). A robot is initially at cell (0, 0) facing direction "East".

The robot can be instructed to move for a specific number of steps. For each step, it does the following.

Attempts to move forward one cell in the direction it is facing.
If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and retries the step.
After the robot finishes moving the number of steps required, it stops and awaits the next instruction.

Implement the Robot class:

Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
void step(int num) Instructs the robot to move forward num steps.
int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".


Example 1:

example-1
Input
["Robot", "step", "step", "getPos", "getDir", "step", "step", "step", "getPos", "getDir"]
[[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
Output
[null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]

Explanation
Robot robot = new Robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
robot.step(2);  // It moves two steps East to (2, 0), and faces East.
robot.step(2);  // It moves two steps East to (4, 0), and faces East.
robot.getPos(); // return [4, 0]
robot.getDir(); // return "East"
robot.step(2);  // It moves one step East to (5, 0), and faces East.
                // Moving the next step East would be out of bounds, so it turns and faces North.
                // Then, it moves one step North to (5, 1), and faces North.
robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                // Then, it moves four steps West to (1, 2), and faces West.
robot.getPos(); // return [1, 2]
robot.getDir(); // return "West"



Constraints:
2 <= width, height <= 100
1 <= num <= 10^5
At most 104 calls in total will be made to step, getPos, and getDir.


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
// 1. Title: Walking Robot Simulation II
//-------------------------------------------------------------------------------
/**
 * ============================================================================
 * Approach: Modulo Reduction + Raycasting Simulation
 * ============================================================================
 * * Concept:
 * 1. Modulo Reduction: The robot strictly walks the perimeter. We calculate
 * the total perimeter length once. For any large number of steps, we use
 * `num % perimeter` to skip thousands of redundant laps in O(1) time.
 * 2. The Zero-Trap Fix: If `num` is a perfect multiple of the perimeter, the
 * modulo evaluates to 0. We force exactly 1 lap (steps = perimeter) so the
 * robot physically traverses the corners and updates its direction.
 * 3. Raycasting: Instead of walking 1 step at a time, we calculate the exact
 * distance to the next wall, fast-forward the robot to that wall, subtract
 * the distance from our remaining steps, and turn.
 * * ============================================================================
 * Complexity:
 * - Time:
 * - Constructor: O(1)
 * - step(num): O(1). Because of the raycasting, the while loop executes a
 * maximum of 4 times (once per wall), regardless of `num`.
 * - getPos() / getDir(): O(1)
 * - Space: O(1) overall, as we only store a few integer tracking variables.
 * ============================================================================
 */

#include <vector>
#include <string>

using namespace std;

class Robot
{
private:
    int m, n, x, y, dir, perimeter;

    // Direction mapping: 0=East, 1=North, 2=West, 3=South
    vector<string> direction = {"East", "North", "West", "South"};

    // Cartesian coordinate vectors mapped to the direction array
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

public:
    /**
     * Initializes the robot grid and calculates the perimeter.
     * @param width The maximum X dimension (n).
     * @param height The maximum Y dimension (m).
     */
    Robot(int width, int height)
    {
        m = height;
        n = width;
        x = 0;
        y = 0;
        dir = 0;

        // Calculate the total number of steps required to complete one full lap
        perimeter = 2 * (width - 1) + 2 * (height - 1);
    }

    /**
     * Moves the robot forward by `num` steps using optimized raycasting.
     * @param num The total number of steps to move.
     */
    void step(int num)
    {

        // Phase 1: Modulo Optimization
        // Fast-forward through redundant full laps around the grid.
        int steps = num % perimeter;

        // Defensive Guard Clause:
        // If the user actually commanded > 0 steps, but the modulo wiped them out,
        // it means the robot completed perfect laps. We force exactly 1 lap
        // to ensure it updates its final direction (e.g., from East to South).
        if (num != 0 && steps == 0)
        {
            steps = perimeter;
        }

        // Phase 2: Raycasting Loop (Max 4 iterations guaranteed)
        while (steps)
        {
            // Project the robot forward by the remaining steps
            int nx = x + steps * dx[dir];
            int ny = y + steps * dy[dir];

            // If the projected position hits or crosses a boundary wall
            if (nx < 0 || ny < 0 || nx >= n || ny >= m)
            {

                int dsteps = 0;

                // Calculate the exact number of valid steps to reach the wall
                if (nx < 0)
                {
                    dsteps = x;
                    x = 0;
                }
                else if (ny < 0)
                {
                    dsteps = y;
                    y = 0;
                }
                else if (nx >= n)
                {
                    dsteps = n - 1 - x;
                    x = n - 1;
                }
                else if (ny >= m)
                {
                    dsteps = m - 1 - y;
                    y = m - 1;
                }

                // Fast-forward to the wall, consume those steps, and turn left
                steps -= dsteps;
                dir = (dir + 1) % 4;
            }
            else
            {
                // Path is completely clear. Teleport directly to the final coordinate.
                x = nx;
                y = ny;
                steps = 0; // Movement complete
            }
        }
    }

    /**
     * Returns the current (x, y) coordinates of the robot.
     */
    vector<int> getPos()
    {
        return {x, y};
    }

    /**
     * Returns the current string representation of the robot's direction.
     */
    string getDir()
    {
        return direction[dir];
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
