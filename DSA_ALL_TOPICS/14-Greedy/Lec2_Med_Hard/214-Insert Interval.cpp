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
1. Title: Insert Interval

Links:
https://takeuforward.org/plus/dsa/problems/insert-interval?tab=editorial
https://leetcode.com/problems/insert-interval/description/?source=submission-noac


Problem statement:
You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
Return intervals after the insertion.
Note that you don't need to modify intervals in-place. You can make a new array and return it.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].


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
// 1. Title: Insert Interval
//-------------------------------------------------------------------------------
class Solution
{
public:
  /*
   * Method: insert
   * --------------
   * Inserts a new interval into a sorted list of non-overlapping intervals, merging if necessary.
   * * Approach: Linear Scan (Three Phases)
   * 1. Add all intervals that come strictly BEFORE the new interval.
   * 2. Merge all intervals that OVERLAP with the new interval.
   * 3. Add the merged interval, followed by all remaining intervals.
   * * Complexity Analysis:
   * - Time Complexity: O(N)
   * We iterate through the 'intervals' vector exactly once.
   * - Space Complexity: O(N)
   * We create a new vector 'result' to store the output.
   * (O(1) auxiliary space if we ignore the return container).
   */
  vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
  {

    vector<vector<int>> result;
    int i = 0;
    int n = intervals.size();

    // Phase 1: Add intervals that end before the new interval starts.
    // Condition: current_end < new_start
    // These are strictly to the left and unaffected.
    while (i < n && intervals[i][1] < newInterval[0])
    {
      result.push_back(intervals[i]);
      i++;
    }

    // Phase 2: Merge overlapping intervals.
    // Condition: current_start <= new_end
    // (Since Phase 1 handled everything ending before, any interval reaching here
    //  that starts <= new_end MUST overlap).
    while (i < n && intervals[i][0] <= newInterval[1])
    {
      // Expand the newInterval to encompass the current overlapping interval
      newInterval[0] = min(newInterval[0], intervals[i][0]); // Min Start
      newInterval[1] = max(newInterval[1], intervals[i][1]); // Max End
      i++;
    }

    // Push the fully merged 'newInterval' into the result
    result.push_back(newInterval);

    // Phase 3: Add remaining intervals.
    // These start after the new interval ends, so they are strictly to the right.
    while (i < n)
    {
      result.push_back(intervals[i]);
      i++;
    }

    return result;
  }
};

int main()
{
  return 0;
}
