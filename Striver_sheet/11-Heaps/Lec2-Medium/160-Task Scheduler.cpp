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

1. Title: Task Scheduler

Links:
https://leetcode.com/problems/task-scheduler/description/


Problem statement:
You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n. Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
Return the minimum number of CPU intervals required to complete all tasks.

Examples:
  Example 1:
  Input: tasks = ["A","A","A","B","B","B"], n = 2
  Output: 8
  Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
  After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th interval, you can do A again as 2 intervals have passed.

  Example 2:
  Input: tasks = ["A","C","A","B","D","B"], n = 1
  Output: 6
  Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.
  With a cooling interval of 1, you can repeat a task after just one other task.

  Example 3:
  Input: tasks = ["A","A","A", "B","B","B"], n = 3
  Output: 10
  Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.
  There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice between repetitions of these tasks.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Task Scheduler
  //-------------------------------------------------------------------------------

  // -------------------------------
  // Approach1: Optimal1
  //

  // Optimal1 approach : using Soring
  // time: O(N+gap)
  // Space: O(26)
  int leastInterval(vector<char> &tasks, int n)
  {

  vector<int> freq(26, 0); // O(26)

  for (char task : tasks) // O(k)
  {
      freq[task - 'A']++;
  }

  sort(freq.begin(), freq.end(), greater<int>()); // O(26 Log k)=122 sort desc

  int ans = 0;

  while (freq[0] > 0) // O(N)
  {

      int gap = 0;
      int idx = 0;

      while (gap <= n && freq[0] > 0) // O(gap)
      {

      if (idx < freq.size())
      {
          freq[idx]--;

          if (freq[idx] == 0)
          {
          freq.erase(freq.begin() + idx); // O(k)
          }
          else
          {
          idx++;
          }
      }

      ans++;
      gap++;
      }

      sort(freq.begin(), freq.end(), greater<int>()); // O(26 Log k)=122 Re-sort for next batch
  }

  return ans;
  }

  // -------------------------------
  // Approach2: Optimal2
  //

  // // Optimal approach: Usinf MAX heap priority queue
  // // Time: O(N)
  // // Space: O(26)
  // int leastInterval(vector<char> &tasks, int n)
  // {
  //   vector<int> freq(26, 0); // O(26)

  //   for (char task : tasks) // O(N)) where k is #tasks
  //   {
  //     freq[task - 'A']++;
  //   }

  //   priority_queue<int> pq; // Max heap

  //   for (int f : freq)
  //   {
  //     if (f > 0)
  //     {
  //       pq.push(f); // O(26 Log 26)
  //     }
  //   }

  //   int time = 0;

  //   while (!pq.empty())
  //   { // O(N)

  //     int gap = 0;
  //     vector<int> tmp_store; // O(N)

  //     while (gap <= n && (!pq.empty() || !tmp_store.empty()))
  //     { // either interval still not reached or atleast one task left processing

  //       if (!pq.empty())
  //       {
  //         if (pq.top() > 1)
  //           tmp_store.push_back(pq.top() - 1); // O(1)
  //         pq.pop();
  //       }

  //       time++;
  //       gap++;
  //     }

  //     for (int tmp : tmp_store)
  //     { // O(26 Log 26)
  //       pq.push(tmp);
  //     }
  //   }

  //   return time;
  // }
};

int main()
{
  return 0;
}
