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

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Insert Interval
  //-------------------------------------------------------------------------------

  /**
   * Inserts a new interval into a list of non-overlapping, sorted intervals and merges if necessary.
   *
   * @param intervals A list of sorted non-overlapping intervals.
   * @param newInterval The interval to insert and potentially merge.
   * @return A new list of merged intervals after inserting newInterval.
   *
   * Time Complexity: O(n), where n is the number of intervals.
   * Space Complexity: O(n), for storing the result in the output vector.
   */
  vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
  {
    vector<vector<int>> ans;
    int i = 0;
    int n = intervals.size();

    // Step 1: Add all intervals that end before newInterval starts (no overlap)
    while (i < n && intervals[i][1] < newInterval[0])
    {
      ans.push_back(intervals[i]);
      i++;
    }

    // Step 2: Merge all overlapping intervals with newInterval
    while (i < n && intervals[i][0] <= newInterval[1])
    {
      newInterval[0] = min(newInterval[0], intervals[i][0]); // Expand start
      newInterval[1] = max(newInterval[1], intervals[i][1]); // Expand end
      i++;
    }
    ans.push_back(newInterval); // Add the merged interval

    // Step 3: Add the remaining intervals that start after newInterval ends
    while (i < n)
    {
      ans.push_back(intervals[i]);
      i++;
    }

    return ans;
  }
};

int main()
{
  return 0;
}
