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

2. Title: Meeting Rooms II


Links:
https://www.geeksforgeeks.org/problems/attend-all-meetings-ii/1

Problem statement:
Given two arrays start[] and end[] such that start[i] is the starting time of ith meeting and end[i] is the ending time of ith meeting. Return the minimum number of rooms required to attend all meetings.

Note: A person can also attend a meeting if it's starting time is same as the previous meeting's ending time.

Examples:
  Input: start[] = [1, 10, 7], end[] = [4, 15, 10]
  Output: 1
  Explanation: Since all the meetings are held at different times, it is possible to attend all the meetings in a single room.
  Input: start[] = [2, 9, 6], end[] = [4, 12, 10]
  Output: 2
  Explanation: 1st and 2nd meetings at one room but for 3rd meeting one another room required.


Constraints:
1 ≤ start.size() = end.size() ≤ 105
0 ≤ start[i] < end[i] ≤ 106


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------
3. Title: Meeting Rooms III


Links:
https://leetcode.com/problems/meeting-rooms-iii/description/
https://www.geeksforgeeks.org/problems/meeting-rooms-iii/1


Problem statement:
You are given an integer n. There are n rooms numbered from 0 to n - 1.

You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.

Meetings are allocated to rooms in the following manner:

Each meeting will take place in the unused room with the lowest number.
If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
When a room becomes unused, meetings that have an earlier original start time should be given the room.
Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.

A half-closed interval [a, b) is the interval between a and b including a and not including b.



Example 1:

Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0.
Example 2:

Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1.


Constraints:

1 <= n <= 100
1 <= meetings.length <= 105
meetings[i].length == 2
0 <= starti < endi <= 5 * 105
All the values of starti are unique.


INPUT::::::


OUTPUT::::::



*/

//-------------------------------------------------------------------------------
// 1. Title: N meetings in one room
//-------------------------------------------------------------------------------
class Solution
{
public:
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

//-------------------------------------------------------------------------------
// 2. Title: Meeting Rooms II
//-------------------------------------------------------------------------------

class Solution
{
public:
  int minMeetingRooms(vector<int> &start, vector<int> &end)
  {
    // code here

    int N = start.size();
    vector<pair<int, int>> meetings; // {startTime, endTime}

    for (int i = 0; i < N; i++)
    {
      meetings.push_back({start[i], end[i]});
    }

    sort(meetings.begin(), meetings.end());

    priority_queue<int, vector<int>, greater<int>> rooms; // min heap of : {endTime}

    int minRooms = 1;

    rooms.push(meetings[0].second);

    for (int i = 1; i < N; i++)
    {

      if (rooms.top() <= meetings[i].first)
      {
        rooms.pop();
        rooms.push(meetings[i].second);
      }
      else
      {
        minRooms++;
        rooms.push(meetings[i].second);
      }
    }

    return minRooms;
  }
};

//-------------------------------------------------------------------------------
// 3. Title: Meeting Rooms III
//-------------------------------------------------------------------------------

class Solution
{
public:
  /*
   * Method: mostBooked
   * ------------------
   * Finds the meeting room that held the most meetings.
   *
   * Approach: Simulation with Two Heaps (Greedy)
   * 1. Timeline Simulation: We process meetings chronologically by sorting them based on start times.
   * 2. Resource Management: We use two Priority Queues (Min-Heaps) to manage room states:
   * - `busy_rooms`: Stores {endTime, roomIndex}. efficient for finding the earliest finishing room.
   * - `free_rooms`: Stores {roomIndex}. Efficient for finding the lowest indexed available room.
   * 3. Allocation Logic:
   * - Before processing a meeting, move all rooms that have finished by `start_time` from `busy` to `free`.
   * - If rooms are free, pick the lowest index (top of `free_rooms`).
   * - If NO rooms are free, force a wait: pick the room finishing earliest (top of `busy_rooms`) and delay the meeting.
   *
   * Complexity Analysis:
   * - Time Complexity: O(M * log M + M * log N)
   * - O(M log M) to sort the meetings.
   * - O(M log N) for heap operations (each meeting triggers push/pop operations on heaps of size N).
   * - Space Complexity: O(N)
   * - To store room states in the heaps and the counting array.
   */
  int mostBooked(int n, vector<vector<int>> &meetings)
  {
    int M = meetings.size();

    // 1. Sort meetings chronologically to simulate the timeline
    sort(meetings.begin(), meetings.end());

    vector<int> meetingsHeld(n, 0);

    // Min heap: {endTime, roomIndex} -> Tracks busy rooms (ordered by finish time)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy_rooms;

    // Min heap: {roomIndex} -> Tracks available rooms (ordered by lowest index)
    priority_queue<int, vector<int>, greater<int>> free_rooms;

    // Initialization: Treat all rooms as busy ending at time 0.
    // This allows the logic inside the loop to naturally move them to 'free_rooms' on the first run.
    for (int i = 0; i < n; i++)
    {
      free_rooms.push(i);
    }

    for (int i = 0; i < M; i++)
    {
      long long start = meetings[i][0];
      long long duration = meetings[i][1] - meetings[i][0];

      // Step 2: Release rooms that have finished before the current meeting starts
      while (!busy_rooms.empty() && busy_rooms.top().first <= start)
      {
        free_rooms.push(busy_rooms.top().second);
        busy_rooms.pop();
      }

      int roomIdx = -1;
      long long roomFreeTime = -1;

      // Step 3: If no rooms are free, wait for the next one to finish
      if (free_rooms.empty())
      {
        // The room with the earliest finish time becomes the candidate
        roomIdx = busy_rooms.top().second;
        roomFreeTime = busy_rooms.top().first;

        busy_rooms.pop();
      }
      else
      {
        // Otherwise take the the min indexed room from free rooms
        roomIdx = free_rooms.top();
        roomFreeTime = start;

        free_rooms.pop();
      }

      meetingsHeld[roomIdx]++;

      // Step 5: Calculate new finish time (handling potential delay)
      long long curMeetingStartTime = max(roomFreeTime, start);
      long long curMeetingEndTime = curMeetingStartTime + duration;

      // Mark room as busy until the new end time
      busy_rooms.push({curMeetingEndTime, roomIdx});
    }

    // Find the room with the maximum meetings (break ties with lower index)
    int maxMeets = INT_MIN;
    int ans = -1;

    for (int i = 0; i < n; i++)
    {
      if (meetingsHeld[i] > maxMeets)
      {
        maxMeets = meetingsHeld[i];
        ans = i;
      }
    }

    return ans;
  }
};

int main()
{
  return 0;
}
