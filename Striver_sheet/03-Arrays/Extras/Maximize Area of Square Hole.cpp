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

1. Title: Maximize Area of Square Hole in Grid

Links:
https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/description/?envType=daily-question&envId=2026-01-15


Problem statement:

You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.

You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.

Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).



Example 1:
Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
Output: 4
Explanation:
The left image shows the initial grid formed by the bars. The horizontal bars are [1,2,3,4], and the vertical bars are [1,2,3].
One way to get the maximum square-shaped hole is by removing horizontal bar 2 and vertical bar 2.

Example 2:
Input: n = 1, m = 1, hBars = [2], vBars = [2]
Output: 4
Explanation:
To get the maximum square-shaped hole, we remove horizontal bar 2 and vertical bar 2.

Example 3:
Input: n = 2, m = 3, hBars = [2,3], vBars = [2,4]
Output: 4
Explanation:
One way to get the maximum square-shaped hole is by removing horizontal bar 3, and vertical bar 4.



Constraints:

1 <= n <= 109
1 <= m <= 109
1 <= hBars.length <= 100
2 <= hBars[i] <= n + 1
1 <= vBars.length <= 100
2 <= vBars[i] <= m + 1
All values in hBars are distinct.
All values in vBars are distinct.


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

private:
  /*
   * HELPER: getMaxGap
   * -----------------
   * Returns the maximum gap size achievable.
   * Logic: Length of longest consecutive sequence + 1.
   */
  int getMaxGap(vector<int> &bars)
  {

    // Sort to easily detect consecutive sequences (e.g., 2, 3, 4)
    sort(bars.begin(), bars.end());

    int maxConsecutive = 1;     // Longest sequence found so far
    int currentConsecutive = 1; // Current running sequence length

    for (int i = 1; i < bars.size(); i++)
    {
      // Check if the current bar is exactly 1 greater than the previous bar
      if (bars[i] == bars[i - 1] + 1)
      {
        currentConsecutive++;
      }
      else
      {
        // Sequence is broken; reset count to 1 (the current bar itself)
        currentConsecutive = 1;
      }
      // Update the global maximum
      maxConsecutive = max(maxConsecutive, currentConsecutive);
    }

    // The gap size is always (Consecutive Bars) + 1.
    // E.g., Removing 1 bar creates a gap of 2. Removing 2 bars creates a gap of 3.
    return maxConsecutive + 1;
  }

public:
  //-------------------------------------------------------------------------------
  // 1. Title: Maximize Area of Square Hole in Grid
  //-------------------------------------------------------------------------------

  /*
   * METHOD: maximizeSquareHoleArea
   * ------------------------------
   * IDEA:
   * The problem asks for the largest square hole we can form by removing bars.
   * The key insight is understanding how removing bars affects the gap size.
   * * LOGIC:
   * 1. The grid starts with 1x1 cells.
   * 2. If we remove a single bar (e.g., bar 2), the cells on its left and right merge.
   * The gap becomes 2 units wide (from bar 1 to bar 3).
   * 3. If we remove 'k' CONSECUTIVE bars (e.g., bars 2, 3, 4), the gap stretches continuously.
   * The resulting gap size is always (Number of consecutive bars removed) + 1.
   * * ALGORITHM:
   * 1. Find the longest sequence of consecutive integers in 'hBars'.
   * Let this length be L_h. The max height we can get is L_h + 1.
   * 2. Find the longest sequence of consecutive integers in 'vBars'.
   * Let this length be L_v. The max width we can get is L_v + 1.
   * 3. Since we need a SQUARE, the side length is limited by the smaller of the two dimensions.
   * Side = min(MaxHeight, MaxWidth).
   * 4. Return Side * Side.
   * * COMPLEXITY:
   * Time: O(H log H + V log V) due to sorting the bar arrays (where H, V <= 100).
   * Space: O(1) or O(log N) for the sorting stack.
   */
  int maximizeSquareHoleArea(int n, int m, vector<int> &hBars, vector<int> &vBars)
  {

    // Step 1: Calculate the maximum continuous vertical gap (height)
    // by finding the longest sequence of consecutive horizontal bars to remove.
    int maxHeight = getMaxGap(hBars);

    // Step 2: Calculate the maximum continuous horizontal gap (width)
    // by finding the longest sequence of consecutive vertical bars to remove.
    int maxWidth = getMaxGap(vBars);

    // Step 3: The largest square is constrained by the smaller dimension.
    int side = min(maxHeight, maxWidth);

    return side * side;
  }
};

int main()
{
  return 0;
}
