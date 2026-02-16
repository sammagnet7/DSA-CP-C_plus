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
  int leastInterval(vector<char> &tasks, int n)
  {
    vector<int> freq(26, 0); // O(26)

    for (char task : tasks) // O(N)) where k is #tasks
    {
      freq[task - 'A']++;
    }

    priority_queue<int> pq; // Max heap

    for (int f : freq)
    {
      if (f > 0)
      {
        pq.push(f); // O(26 Log 26)
      }
    }

    int time = 0;

    while (!pq.empty())
    { // O(N)

      int gap = 0;
      vector<int> tmp_store; // O(N)

      while (gap <= n && (!pq.empty() || !tmp_store.empty()))
      { // either interval still not reached or atleast one task left processing

        if (!pq.empty())
        {
          if (pq.top() > 1)
            tmp_store.push_back(pq.top() - 1); // O(1)
          pq.pop();
        }

        time++;
        gap++;
      }

      for (int tmp : tmp_store)
      { // O(26 Log 26)
        pq.push(tmp);
      }
    }

    return time;
  }

  /**
   * @brief Calculates the minimum number of CPU intervals using a simulation approach.
   *
   * This method simulates the CPU's behavior round-by-round.
   * 1. A "round" consists of `n + 1` time intervals (one slot for a task,
   * and `n` slots for cooldown).
   * 2. It uses a max-heap (`priority_queue`) to always greedily pick the
   * most frequent task available.
   * 3. It processes one "round" at a time, pulling up to `n + 1` tasks from
   * the heap, decrementing their counts, and adding them to a temporary list.
   * 4. After the round, any tasks that still have remaining counts are
   * added back to the heap for the next round.
   *
   * Time Complexity: O(N + max_freq * n) where:
   * - N is the total number of tasks.
   * - max_freq is the frequency of the most frequent task.
   * - n is the cooldown period.
   *
   * - O(N) to count frequencies.
   * - O(U log U) to build the heap, where U is unique tasks (max 26, so O(1)).
   * - The 'while' loop runs `max_freq` times (once for each instance of the
   * most frequent task).
   * - Inside the 'while' loop, the 'for' loop runs `n+1` times.
   * - Each heap operation (push/pop) is O(log U), which is O(1).
   * - Total loop time: O(max_freq * (n * log U)) = O(max_freq * n).
   * - The final complexity is dominated by O(N + max_freq * n).
   * - In the worst case, `max_freq` can be `N`, leading to O(N*n).
   *
   * Space Complexity: O(n)
   * - `freq` array: O(26) = O(1).
   * - `pq` (priority queue): Stores at most U (26) frequencies = O(1).
   * - `curRoundProcessed` vector: Stores at most `n+1` tasks in a round.
   * - Therefore, the dominant space is O(n).
   *
   * @param tasks A vector of characters representing the tasks.
   * @param n The non-negative cooldown period.
   * @return The minimum number of intervals.
   */
  int leastInterval(vector<char> &tasks, int n)
  {

    // 1. Count the frequency of each task.
    vector<int> freq(26, 0);
    for (char c : tasks)
    {
      freq[c - 'A']++;
    }

    // 2. Build a max-heap (priority queue) of task frequencies.
    // This allows us to always pick the most frequent task.
    priority_queue<int> pq;
    for (int i : freq)
    {
      if (i > 0)
      { // Only add tasks that actually exist
        pq.push(i);
      }
    }

    // 3. Initialize total time.
    int time = 0;

    // 4. Simulate the CPU rounds as long as tasks remain.
    while (!pq.empty())
    {

      // This vector is a temporary holding bay for tasks
      // processed in the *current* round. We can't add them
      // back to the 'pq' until the round is over (to respect cooldown).
      vector<int> curRoundProcessed;

      // 5. Simulate one "round" of (n+1) time slots.
      // This loop represents one task + its 'n' cooldown period.
      for (int intervals = 0; intervals <= n; intervals++)
      {

        time++; // Increment the total time for every slot

        // If tasks are available, process the most frequent one
        if (!pq.empty())
        {
          int curTaskFreq = pq.top();
          pq.pop();

          curTaskFreq--; // "Process" the task

          // If the task still needs more processing,
          // add it to the holding bay for the next round.
          if (curTaskFreq > 0)
          {
            curRoundProcessed.push_back(curTaskFreq);
          }
        }

        // 6. Early exit check:
        // If the main queue is empty (no more tasks to pick
        // this round) AND the holding bay is empty (no tasks
        // are left for *future* rounds), we are completely done.
        // This 'break' is crucial to avoid adding extra idle
        // time at the very end.
        if (pq.empty() && curRoundProcessed.size() == 0)
        {
          break;
        }
      }

      // 7. After the (n+1) round is over, add all tasks
      // from the holding bay back into the max-heap.
      // They are now available to be scheduled again.
      for (int frq : curRoundProcessed)
      {
        pq.push(frq);
      }
    }

    // The total time ticked is the answer.
    return time;
  }
};

int main()
{
  return 0;
}
