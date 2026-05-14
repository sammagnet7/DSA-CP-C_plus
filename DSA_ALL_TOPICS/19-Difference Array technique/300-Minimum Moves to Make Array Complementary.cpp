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

1. Title: Minimum Moves to Make Array Complementary


Links:
https://leetcode.com/problems/minimum-moves-to-make-array-complementary/description/


Problem statement:
You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.

The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.

Return the minimum number of moves required to make nums complementary.


Example 1:
    Input: nums = [1,2,4,3], limit = 4
    Output: 1
    Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
    nums[0] + nums[3] = 1 + 3 = 4.
    nums[1] + nums[2] = 2 + 2 = 4.
    nums[2] + nums[1] = 2 + 2 = 4.
    nums[3] + nums[0] = 3 + 1 = 4.
    Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.

Example 2:
    Input: nums = [1,2,2,1], limit = 2
    Output: 2
    Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.

Example 3:
    Input: nums = [1,2,1,2], limit = 2
    Output: 0
    Explanation: nums is already complementary.


Constraints:
    n == nums.length
    2 <= n <= 105
    1 <= nums[i] <= limit <= 10^5
    n is even.



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

/**
 * ============================================================================
 * Approach: Full Simulation (Iterating all targets) [SLOW]
 * ============================================================================
 * Intuition:
 * The target sum for the complementary array must fall between 2 (1+1) and
 * 2 * limit. To find the optimal target, we can literally test every single
 * possible target sum and count how many total moves it would take for all
 * pairs to reach that specific sum.
 *
 * Approach:
 * 1. Loop through all possible target sums `T` from 2 to 2 * limit.
 * 2. For each `T`, loop through all pairs (a, b) in the array.
 * 3. For each pair, determine the cost to reach `T`:
 *    - 0 moves: The pair already sums to `T`.
 *    - 1 move:  `T` falls within the reachable range by changing only one
 *               number. The smallest possible sum with 1 move is min(a,b) + 1.
 *               The largest is max(a,b) + limit.
 *    - 2 moves: `T` is outside the 1-move bounds; both numbers must change.
 * 4. Keep track of the minimum total moves seen across all targets.
 * ============================================================================
 * Complexity:
 * - Time: O(Limit * N). For each of the (2 * limit) targets, we do an O(N)
 *   pass over all pairs. Given constraints (10^5), this requires ~10^10
 *   operations and will trigger a Time Limit Exceeded (TLE).
 * - Space: O(1). No extra memory is allocated.
 * ============================================================================
 */
class SolutionBrute
{
public:
    int minMoves(vector<int> &nums, int limit)
    {

        int n = nums.size();
        int minMoves = INT_MAX;

        for (int target = 2; target <= 2 * limit; ++target)
        {

            int moves = 0;

            for (int i = 0; i < n / 2; ++i)
            {

                int curMove = 1;

                int a = nums[i];
                int b = nums[n - 1 - i];

                // The minimum/maximum possible sums if we change exactly ONE number
                int lRange = min(a, b) + 1;
                int rRange = max(a, b) + limit;

                if (a + b == target)
                {
                    curMove = 0; // Already matches target
                }
                else if (lRange <= target && target <= rRange)
                {
                    curMove = 1; // Target is reachable by changing one element
                }
                else
                {
                    curMove = 2; // Target requires changing both elements
                }

                moves += curMove;
            }

            minMoves = min(minMoves, moves);
        }

        return minMoves;
    }
};

/**
 * ============================================================================
 * Approach: Difference Array (Sweep Line) [OPTIMAL]
 * ============================================================================
 * Intuition:
 * Instead of asking "How many moves does target T require?", we invert the
 * problem: "How does the pair (a, b) affect the cost of ALL possible targets?"
 * Every pair establishes intervals of costs. We can use a difference array
 * to record the boundaries of these intervals in O(1) time per pair, and then
 * compute the actual costs for all targets in a single sweep at the end.
 *
 * Approach:
 * 1. Assume every pair requires 2 moves (the worst case) for all targets.
 * 2. Apply "discounts" using a difference array:
 *    - In the interval [min(a,b)+1, max(a,b)+limit], we only need 1 move.
 *      So, apply a -1 discount at the start, and remove it at the end.
 *    - Exactly at the point (a+b), we need 0 moves.
 *      So, apply another -1 discount exactly at (a+b), and remove it at (a+b+1).
 * 3. Sweep through the difference array calculating the running prefix sum.
 *    This running sum represents the exact moves needed for each target.
 * ============================================================================
 * Complexity:
 * - Time: O(N + Limit). We iterate through N/2 pairs once, doing O(1) math.
 *   Then we iterate through the difference array of size 2 * Limit once.
 * - Space: O(Limit). We allocate an array of size 2 * Limit + 2.
 * ============================================================================
 */
class Solution
{
public:
    int minMoves(vector<int> &nums, int limit)
    {

        int n = nums.size();
        int minMoves = INT_MAX;

        // Size is 2 * limit + 2 to handle targets up to 2*limit, plus padding
        // to safely remove discounts at (boundary + 1) without out-of-bounds errors.
        vector<int> diffArray(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; ++i)
        {

            int a = nums[i];
            int b = nums[n - 1 - i];

            // The bounds where target is reachable with exactly 1 move
            int lRange = min(a, b) + 1;
            int rRange = max(a, b) + limit;

            // BASELINE: Every target sum starting from 2 requires 2 moves.
            diffArray[2] += 2;

            // We only care about targets up to 2 * limit. This reverses the baseline
            // after the valid range, keeping the sweep mathematically clean.
            diffArray[2 * limit + 1] -= 2;

            // DISCOUNT 1: From lRange to rRange, the cost drops from 2 to 1.
            diffArray[lRange] += (-1);
            if (rRange + 1 < diffArray.size())
            {
                diffArray[rRange + 1] -= (-1); // Remove discount after rRange
            }

            // DISCOUNT 2: Exactly at target (a+b), the cost drops from 1 to 0.
            diffArray[a + b] += (-1);
            if (a + b + 1 < diffArray.size())
            {
                diffArray[a + b + 1] -= (-1); // Remove discount immediately after
            }
        }

        int moves = 0;

        // Sweep the array to accumulate the changes and find the actual costs
        for (int target = 2; target <= 2 * limit; ++target)
        {
            moves += diffArray[target];
            minMoves = min(minMoves, moves);
        }

        return minMoves;
    }
};

int main()
{
    return 0;
}
