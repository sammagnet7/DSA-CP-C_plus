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
1. Title: N meetings in one room

Links:
https://takeuforward.org/data-structure/n-meetings-in-one-room/
https://takeuforward.org/plus/dsa/problems/n-meetings-in-one-room?tab=editorial
https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

Note: Its exact opposit problem: [214-Non-overlapping Intervals]


Problem statement:
You are given timings of n meetings in the form of (start[i], end[i]) where start[i] is the start time of meeting i and end[i] is the finish time of meeting i. Return the maximum number of meetings that can be accommodated in a single meeting room, when only one meeting can be held in the meeting room at a particular time.

Note: The start time of one chosen meeting can't be equal to the end time of the other chosen meeting.

Examples :

Input: start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)
Input: start[] = [10, 12, 20], end[] = [20, 25, 30]
Output: 1
Explanation: Only one meetings can be held with given start and end timings.
Input: start[] = [1, 2], end[] = [100, 99]
Output: 1


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
  // 1. Title: N meetings in one room
  //-------------------------------------------------------------------------------

  /**
   * Function: maxMeetings
   * Purpose: To find the maximum number of non-overlapping meetings that can be scheduled.
   *
   * Approach:
   * - Each meeting is represented by its start and end time.
   * - We pair up (end, start) for all meetings to sort them by earliest ending time.
   * - This is a classic **Greedy Algorithm** approach where we:
   *   - Always pick the meeting that ends the earliest (to leave room for others).
   *   - Only pick a meeting if its start time is **after** the last selected meeting's end time.
   *
   * Time Complexity: O(N log N) — due to sorting the meetings
   * Space Complexity: O(N) — for storing pairs of meetings
   */

  int maxMeetings(vector<int> &start, vector<int> &end)
  {
    vector<pair<int, int>> store;

    // Step 1: Store all meetings as (endTime, startTime) pairs
    for (int i = 0; i < start.size(); i++)
    {
      store.push_back({end[i], start[i]});
    }

    // Step 2: Sort meetings by their ending time (greedy criteria)
    sort(store.begin(), store.end());

    int ans = 0;
    int lastEndTime = -1; // Keeps track of the end time of the last selected meeting

    // Step 3: Iterate through all sorted meetings
    for (int i = 0; i < store.size(); i++)
    {
      // If the current meeting starts after the last selected one ends
      if (store[i].second > lastEndTime)
      {
        ans++;                        // Count this meeting
        lastEndTime = store[i].first; // Update the end time
      }
    }

    return ans;
  }
};

int main()
{
  return 0;
}
