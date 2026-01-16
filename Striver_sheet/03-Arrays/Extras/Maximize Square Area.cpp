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

2. Title: Maximum Square Area by Removing Fences From a Field

Links:
https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/description/?envType=daily-question&envId=2026-01-16


Problem statement:
There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.

Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).

Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.

Since the answer may be large, return it modulo 109 + 7.

Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.



Example 1:
Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
Output: 4
Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.

Example 2:
Input: m = 6, n = 7, hFences = [2], vFences = [4]
Output: -1
Explanation: It can be proved that there is no way to create a square field by removing fences.


Constraints:
3 <= m, n <= 109
1 <= hFences.length, vFences.length <= 600
1 < hFences[i] < m
1 < vFences[i] < n
hFences and vFences are unique.




INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Maximize Area of Square Hole in Grid
//-------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------
// 1. Title: Maximum Square Area by Removing Fences From a Field
//-------------------------------------------------------------------------------

class Solution
{

  int MOD = 1e9 + 7;

public:
  /*
   * METHOD: maximizeSquareArea
   * --------------------------
   * APPROACH:
   * The goal is to find the largest square field, which implies finding a gap 'k'
   * that exists between both horizontal fences AND vertical fences.
   * * ALGORITHM:
   * 1. Add Boundaries: The field edges (1, m) and (1, n) act as fences. Add them to the lists.
   * 2. Generate Horizontal Gaps:
   * - Iterate through every pair of horizontal fences.
   * - Calculate the distance between them (abs diff).
   * - Store these distances in a Hash Set (unordered_set) for O(1) fast lookup.
   * 3. Check Vertical Gaps:
   * - Iterate through every pair of vertical fences.
   * - Calculate the distance (width).
   * - Check if this 'width' exists in the 'heights' set.
   * - If it does, we found a valid square side. Update 'maxSide'.
   * 4. Calculate Area: Return (maxSide * maxSide) % MOD.
   *
   * COMPLEXITY:
   * Time Complexity: O(H^2 + V^2)
   * - We iterate through all pairs of horizontal fences: O(H^2).
   * - We iterate through all pairs of vertical fences: O(V^2).
   * - Set insertions and lookups are O(1) on average.
   * - Given constraints (len <= 600), H^2 is ~360,000 operations, which is very fast.
   * * Space Complexity: O(H^2)
   * - We store up to O(H^2) unique gap values in the unordered_set.
   */
  int maximizeSquareArea(int m, int n, vector<int> &hFences, vector<int> &vFences)
  {

    // Step 1: Treat field boundaries as fences
    // The problem states fences are at specific coordinates, but the field edges
    // (1 and m/n) also form valid boundaries for our square.
    hFences.push_back(1);
    hFences.push_back(m);
    vFences.push_back(1);
    vFences.push_back(n);

    // Use unordered_set for O(1) average time complexity for insertions and lookups.
    // We only need to store one dimension's gaps to check for intersection.
    unordered_set<int> heights;

    // Step 2: Calculate all possible vertical gaps (Heights)
    // Brute force all pairs (i, j)
    for (int i = 0; i < hFences.size(); i++)
    {
      for (int j = 0; j < i; j++)
      {
        // Store the distance between horizontal fence i and j
        heights.insert(abs(hFences[i] - hFences[j]));
      }
    }

    int maxSide = INT_MIN;

    // Step 3: Calculate all possible horizontal gaps (Widths)
    // and check for intersection on the fly.
    for (int i = 0; i < vFences.size(); i++)
    {
      for (int j = 0; j < i; j++)
      {

        int width = abs(vFences[i] - vFences[j]);

        // Key Logic: A square is formed if a vertical gap (width)
        // exactly matches a previously found horizontal gap (height).
        if (heights.find(width) != heights.end())
        {
          maxSide = max(maxSide, width);
        }
      }
    }

    // If maxSide wasn't updated, no common gap was found.
    if (maxSide == INT_MIN)
    {
      return -1;
    }

    // Step 4: Calculate final area with modulo arithmetic
    // Cast to long long to prevent overflow before modulo
    long long area = (long long)maxSide * maxSide;
    area = area % MOD;

    return area;
  }
};

int main()
{
  return 0;
}
