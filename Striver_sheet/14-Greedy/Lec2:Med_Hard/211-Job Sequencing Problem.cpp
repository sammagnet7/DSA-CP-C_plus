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
1. Title: Job Sequencing Problem

Links:
https://takeuforward.org/data-structure/job-sequencing-problem/
https://takeuforward.org/plus/dsa/problems/job-sequencing-problem?tab=editorial
https://www.naukri.com/code360/problems/job-sequencing-problem_1169460?leftPanelTabValue=PROBLEM


Problem statement:
You are given a 'Nx3' 2-D array 'Jobs' describing 'N' jobs where 'Jobs[i][0]' denotes the id of 'i-th' job, 'Jobs[i][1]' denotes the deadline of 'i-th' job, and 'Jobs[i][2]' denotes the profit associated with 'i-th job'.
You will make a particular profit if you complete the job within the deadline associated with it. Each job takes 1 unit of time to be completed, and you can schedule only one job at a particular time.
Return the number of jobs to be done to get maximum profit.
Note :
If a particular job has a deadline 'x', it means that it needs to be completed at any time before 'x'.
Assume that the start time is 0.

Example :
  'N' = 3, Jobs = [[1, 1, 30], [2, 3, 40], [3, 2, 10]].
  All the jobs have different deadlines. So we can complete all the jobs.
  At time 0-1, Job 1 will complete.
  At time 1-2, Job 3 will complete.
  At time 2-3, Job 2 will complete.
  So our answer is [3 80].

  Sample Input 1 :
  4
  1 2 30
  2 2 40
  3 1 10
  4 1 10
  Sample Output 1 :
  2 70
  Explanation For Sample Input 1 :
  At time 0-1, Job 1 will complete.

  At time 1-2, Job 2 will complete.

  The first and second jobs can be completed within the deadlines, and we earn a profit of 70 by doing so.
  Sample Input 2 :
  3
  1 1 40
  2 1 50
  3 1 60
  Sample Output 2 :
  1 60


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
  // 1. Title: Job Sequencing Problem
  //-------------------------------------------------------------------------------

  /*
    Problem: Job Scheduling (with Deadline and Profit)

    Goal:
    - Schedule jobs such that each job is completed before its deadline.
    - Only one job can be scheduled at a given time.
    - Maximize total profit and return the number of jobs done and total profit.

    Input: jobs[i] = {jobId, deadline, profit}
    Output: {number_of_jobs_done, total_profit}

    Approach:
    1. Sort jobs in descending order of profit.
    2. Initialize a time slot array up to the maximum deadline.
    3. For each job, try to assign it to the latest available time slot before or at its deadline.
    4. If a slot is found, assign the job and add its profit.
    5. Return total jobs done and accumulated profit.

    Time Complexity: O(N log N + N * M)
        - N log N for sorting
        - For each job (N), in worst case we may scan M time slots (M = maxDeadline)
    Space Complexity: O(M) for deadline slot tracking
*/

  vector<int> jobScheduling(vector<vector<int>> &jobs)
  {
    vector<int> ans;

    // Step 1: Sort jobs by profit descending (greedy approach)
    sort(jobs.begin(), jobs.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[2] > b[2]; });

    // Step 2: Find the maximum deadline to determine size of slot array
    int maxDeadL = 0;
    for (auto el : jobs)
    {
      maxDeadL = max(maxDeadL, el[1]);
    }

    // Step 3: Create a time slot array to track occupied slots (1-based indexing)
    vector<int> deadline(maxDeadL + 1, -1); // -1 indicates slot is free

    int profit = 0; // Total profit earned
    int count = 0;  // Number of jobs scheduled

    // Step 4: Try to place each job in the latest free slot before its deadline
    for (auto el : jobs)
    {
      int deadL = el[1]; // Deadline for current job

      // Scan backwards to find a free time slot
      while (deadL >= 1)
      {
        if (deadline[deadL] == -1)
        {
          // Slot is available ? schedule job
          deadline[deadL] = el[0]; // Assign job ID (not used here, but can track)
          profit += el[2];         // Add profit
          count++;                 // Increment job count
          break;                   // Move to next job
        }
        deadL--; // Try earlier slot
      }
    }

    return {count, profit};
  }
};

int main()
{
  return 0;
}
