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
1. Title: Non-overlapping Intervals

Links:
https://www.youtube.com/watch?v=HDHQ8lAWakY
https://takeuforward.org/plus/dsa/problems/non-overlapping-intervals?tab=editorial
https://leetcode.com/problems/non-overlapping-intervals/description/

Note: this is exact opposit problem of : [208-N meetings in one room]


Problem statement:
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

Examples:
  Example 1:
  Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
  Output: 1
  Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

  Example 2:
  Input: intervals = [[1,2],[1,2],[1,2]]
  Output: 2
  Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

  Example 3:
  Input: intervals = [[1,2],[2,3]]
  Output: 0
  Explanation: You don't need to remove any of the intervals since they're already non-overlapping.


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
  // 1. Title: Non-overlapping Intervals
  //-------------------------------------------------------------------------------

  /**
   * Function: eraseOverlapIntervals
   * --------------------------------
   * Purpose:
   *   To find the minimum number of intervals that need to be removed
   *   to make the rest of the intervals non-overlapping.
   *
   * Approach:
   *   1. Sort the intervals based on their end times (greedy strategy).
   *   2. Initialize a counter to track the maximum number of non-overlapping intervals.
   *   3. Traverse through intervals, selecting only those that do not overlap
   *      with the last selected interval.
   *   4. Subtract the count of non-overlapping intervals from total intervals
   *      to get the number of intervals to remove.
   *
   * Time Complexity: O(N log N) due to sorting.
   * Space Complexity: O(1) extra space.
   */

  int eraseOverlapIntervals(vector<vector<int>> &intervals)
  {

    // Sort intervals by their end time in ascending order
    sort(intervals.begin(), intervals.end(),
         [](const vector<int> &a, const vector<int> &b)
         {
           return a[1] < b[1];
         });

    int N = intervals.size();

    // At least one interval is non-overlapping (the first one)
    int maxNonOverlaps = 1;

    // Track the end time of the last selected non-overlapping interval
    int lastEndTime = intervals[0][1];

    // Start checking from the second interval
    for (int i = 1; i < N; i++)
    {
      // If current interval starts before last selected ends, it's overlapping
      if (intervals[i][0] < lastEndTime)
      {
        continue; // Skip this interval (it will need to be removed)
      }

      // No overlap, include this interval
      maxNonOverlaps++;
      lastEndTime = intervals[i][1]; // Update end time to current interval's end
    }

    // Total intervals - max non-overlapping gives number to remove
    return (N - maxNonOverlaps);
  }
};

int main()
{
  return 0;
}
