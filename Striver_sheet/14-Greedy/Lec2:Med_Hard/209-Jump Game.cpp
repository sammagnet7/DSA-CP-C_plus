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
1. Title: Jump Game 1

Links:
https://takeuforward.org/Greedy/jump-game-i
https://takeuforward.org/plus/dsa/problems/jump-game---i?tab=editorial
https://leetcode.com/problems/jump-game/description/


Problem statement:
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.

Examples:
  Example 1:
  Input: nums = [2,3,1,1,4]
  Output: true
  Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

  Example 2:
  Input: nums = [3,2,1,0,4]
  Output: false
  Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Jump Game 1
  //-------------------------------------------------------------------------------

  /*
        Problem: Jump Game (Leetcode #55)

        * Intuition:
        - At each index `i`, the value `nums[i]` tells us the maximum number of steps we can jump ahead.
        - We need to keep track of the farthest index we can reach while traversing the array from left to right.
        - If we reach an index that is **beyond** the current `reached` limit, then it's **not possible** to move further.
        - If at any point, the `reached` value becomes greater than or equal to the last index, we can conclude that the end is reachable.

        * Approach:
        - Initialize `reached = 0` to represent the farthest reachable index.
        - Traverse the array from index `0` to `n-1`, stopping early if `reached < i` (i.e., the current index is not reachable).
        - At each step, update `reached` to the maximum of current `reached` and `i + nums[i]`.
        - If `reached` >= last index at any point, return true.
        - If loop ends without reaching the last index, return false.

        * Time Complexity: O(n) — where n is the size of the array.
        * Space Complexity: O(1) — constant space used.
    */

  bool canJump(vector<int> &nums)
  {
    int reached = 0; // Tracks the farthest index that can be reached

    for (int i = 0; i < nums.size() && reached >= i; i++)
    {
      reached = max(reached, i + nums[i]); // Update the farthest reachable index
      if (reached >= nums.size() - 1)      // If we can reach or pass the last index
        return true;
    }

    return false; // If we exited the loop without reaching the end
  }
};

int main()
{
  return 0;
}
