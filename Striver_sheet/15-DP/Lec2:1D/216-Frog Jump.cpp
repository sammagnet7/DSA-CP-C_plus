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

1. Title: Frog Jump 1

Links:
https://takeuforward.org/data-structure/dynamic-programming-frog-jump-dp-3/
https://www.youtube.com/watch?v=EgG3jsGoPvQ
https://takeuforward.org/plus/dsa/problems/frog-jump?tab=editorial
https://www.naukri.com/code360/problems/frog-jump_3621012?leftPanelTabValue=PROBLEM


Problem statement:
There is a frog on the '1st' step of an 'N' stairs long staircase. The frog wants to reach the 'Nth' stair. 'HEIGHT[i]' is the height of the '(i+1)th' stair.If Frog jumps from 'ith' to 'jth' stair, the energy lost in the jump is given by absolute value of ( HEIGHT[i-1] - HEIGHT[j-1] ). If the Frog is on 'ith' staircase, he can jump either to '(i+1)th' stair or to '(i+2)th' stair. Your task is to find the minimum total energy used by the frog to reach from '1st' stair to 'Nth' stair.

For Example
If the given ‘HEIGHT’ array is [10,20,30,10], the answer 20 as the frog can jump from 1st stair to 2nd stair (|20-10| = 10 energy lost) and then a jump from 2nd stair to last stair (|10-20| = 10 energy lost). So, the total energy lost is 20.


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
  // 1. Title: Frog Jump 1
  //-------------------------------------------------------------------------------

  /**
   * Approach 1: Bottom-Up DP with Array (Tabulation)
   * ------------------------------------------------
   * We calculate the minimum energy required to reach the last stone starting from the end.
   * At each stone, the frog can jump either 1 or 2 steps ahead.
   *
   * dp[i] stores the minimum energy required to reach the end from stone i.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(N)
   */

  int frogJump(int n, vector<int> &heights)
  {
    // Edge case: Only one stone, no energy needed
    if (n == 1)
      return 0;

    // Edge case: Only two stones, single jump cost
    if (n == 2)
      return abs(heights[1] - heights[0]);

    vector<int> dp(n);

    // From last stone to itself: zero energy
    dp[n - 1] = 0;

    // From second last stone: cost to jump one step to last stone
    dp[n - 2] = abs(heights[n - 1] - heights[n - 2]);

    // Fill dp table in reverse
    for (int i = n - 3; i >= 0; i--)
    {
      int oneJump = abs(heights[i + 1] - heights[i]) + dp[i + 1];
      int twoJump = abs(heights[i + 2] - heights[i]) + dp[i + 2];
      dp[i] = min(oneJump, twoJump);
    }

    return dp[0]; // Minimum energy from stone 0 to end
  }

  /**
   * Approach 2: Space-Optimized DP
   * ------------------------------
   * Since we only need the next two values at any point, we optimize space by keeping two variables
   * instead of maintaining a full dp array.
   *
   * Time Complexity: O(N)
   * Space Complexity: O(1)
   */

  int frogJump(int n, vector<int> &heights)
  {
    if (n == 1)
      return 0;
    if (n == 2)
      return abs(heights[1] - heights[0]);

    int prev_prev = 0;                               // dp[i+2]
    int prev = abs(heights[n - 1] - heights[n - 2]); // dp[i+1]

    for (int i = n - 3; i >= 0; i--)
    {
      int oneJump = abs(heights[i + 1] - heights[i]) + prev;
      int twoJump = abs(heights[i + 2] - heights[i]) + prev_prev;

      // Update for next iteration
      prev_prev = prev;
      prev = min(oneJump, twoJump);
    }

    return prev; // Minimum energy from stone 0 to end
  }
};

int main()
{
  return 0;
}
