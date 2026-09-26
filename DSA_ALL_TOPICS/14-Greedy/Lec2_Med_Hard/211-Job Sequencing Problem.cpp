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
1. Title: Job Sequencing Problem  [Greedy]

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

2. Title: Maximum Profit in Job Scheduling [with Fixed Start & End Times] [DP]

Links:
https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/


Problem statement:
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.



Example 1:
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job.
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

Example 2:
Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.

Example 3:
Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6


Constraints:
1 <= startTime.length == endTime.length == profit.length <= 5 * 104
1 <= startTime[i] < endTime[i] <= 109
1 <= profit[i] <= 104


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Job Sequencing Problem [Greedy]
//-------------------------------------------------------------------------------
class Solution
{
public:
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

    Why DP or Recursion is NOT needed here
      The core reason Greedy works (and DP is overkill) is due to two specific constraints in this problem:
      Uniform Duration: Every job takes exactly 1 unit of time.
      Flexible Start Time: A job with deadline d can be done at any time slot 1, 2, ..., d. It doesn't have a fixed "Start Time".

    When WOULD you need DP? (The Variations)
      You need Dynamic Programming when the "Greedy Choice" (picking the highest profit immediately) might mistakenly block a better combination of future jobs. This happens in two main scenarios:

        Scenario A: Variable Durations (Knapsack Variation)
          If jobs take different amounts of time to complete (e.g., Job A takes 3 hours, Job B takes 1 hour).

        Scenario B: Fixed Start & End Times (Weighted Interval Scheduling)
          If jobs have specific windows (e.g., "9:00 to 11:00") rather than just a flexible deadline.


    Time Complexity: O(N log N + N * M)
        - N log N for sorting
        - For each job (N), in worst case we may scan M time slots (M = maxDeadline)
    Space Complexity: O(M) for deadline slot tracking
*/

  vector<int> jobScheduling(vector<vector<int>> &jobs)
  {

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

//----------------------------------------------------------------------------------
// 2. Title: Maximum Profit in Job Scheduling [with Fixed Start & End Times] [DP]
//--------------------------------------------------------------------------------

//-----------------------------------------------
// Approach1: Normal DP won't work [TLE]
//-----------------------------------------------
/*
class Solution {
public:

    // Approach:
    //
    // as (idx*prevIdx) will create DP table of size: >10^8
    // DP table can be created upto size 10^7
    //
    int rec(int idx, int prevIdx, vector<vector<int>> jobs){

        if(idx==jobs.size()){
            return 0;
        }

        int curStartTime = jobs[idx][0];
        int curEndTime = jobs[idx][1];
        int curProfit = jobs[idx][2];

        int prevEndTime = prevIdx==-1 ? 0:jobs[prevIdx][1];

        int curMaxProfit = INT_MIN;

        // Take
        if(prevEndTime<=curStartTime){
            curMaxProfit = max(curMaxProfit, curProfit+rec(idx+1, idx, jobs));
        }

        // Not take
        curMaxProfit = max(curMaxProfit, rec(idx+1, prevIdx, jobs));

        return curMaxProfit;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {

        int N = startTime.size();
        vector<vector<int>> jobs(N, vector<int>(3));    // {startTime, endTime, profit}

        for(int i=0; i<N; i++){
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }

        sort(jobs.begin(), jobs.end());

        return rec(0, -1, jobs);
    }

};
*/

//-----------------------------------------------
// Approach1: DP + BS
//-----------------------------------------------

class Solution
{
public:
  /*
   * -------------------------------------------------------------------------
   * Helper Method: nextAvailableIdx
   * -------------------------------------------------------------------------
   * Goal:
   * Find the index of the first job that starts AFTER or AT the same time
   * the current job ends.
   *
   * Params:
   * - idx: The index of the current job we just took.
   * - jobs: Reference to the sorted list of jobs.
   *
   * Returns:
   * - Index of the next compatible job, or -1 if no such job exists.
   */
  int nextAvailableIdx(int idx, vector<vector<int>> &jobs)
  {

    int curEndTime = jobs[idx][1]; // The time the current job finishes
    int avlIdx = -1;               // Default: No valid next job found

    int l = idx + 1;
    int r = jobs.size() - 1;

    while (l <= r)
    {
      int mid = l + (r - l) / 2;

      // Check if job[mid] starts after or when the current job ends
      if (jobs[mid][0] >= curEndTime)
      {
        avlIdx = mid; // Found a candidate job
        r = mid - 1;  // Try to find an earlier valid job (minimize the gap)
      }
      else
      {
        // job[mid] starts too early (overlaps), look in the right half
        l = mid + 1;
      }
    }

    return avlIdx;
  }

  /*
   * -------------------------------------------------------------------------
   * Recursive Method: rec (Top-Down Dynamic Programming)
   * -------------------------------------------------------------------------
   * Logic:
   * Standard "Take or Skip" Knapsack-style decision tree.
   * 1. SKIP: Move to idx + 1.
   * 2. TAKE: Add profit, then jump to the next NON-OVERLAPPING job index.
   */
  int rec(int idx, vector<vector<int>> &jobs, vector<int> &DP)
  {

    // Base Case: No more jobs left to process
    if (idx == jobs.size())
    {
      return 0;
    }

    if (DP[idx] != -1)
    {
      return DP[idx];
    }

    int curProfit = jobs[idx][2];

    // Option 1: SKIP current job
    int notTake = rec(idx + 1, jobs, DP);

    // Option 2: TAKE current job
    // We use Binary Search to find the next valid job index.
    int avlIdx = nextAvailableIdx(idx, jobs);

    int take = 0;
    if (avlIdx != -1)
    {
      take = curProfit + rec(avlIdx, jobs, DP);
    }
    else
    {
      take = curProfit;
    }

    return DP[idx] = max(take, notTake);
  }

  /*
   * -------------------------------------------------------------------------
   * Main Method: jobScheduling
   * -------------------------------------------------------------------------
   * * Why the "General DP" approach fails here:
   * -----------------------------------------
   * 1. Time-Based DP (dp[time]):
   * - Logic: dp[t] = max profit at time 't'.
   * - Failure: Time coordinates go up to 10^9. We cannot create an array
   * of size 10^9 (Memory Limit Exceeded) nor iterate it (Time Limit Exceeded).
   * * 2. Standard LIS-style DP (dp[i] = max profit ending at job i):
   * - Logic: For every job 'i', loop back through all jobs 'j' < 'i'
   * to find the best compatible previous job.
   * - Failure: This nested loop approach is O(N^2).
   * With N = 50,000, N^2 = 2.5 Billion operations. This results in TLE.
   * * How we arrive at the Binary Search Approach:
   * --------------------------------------------
   * To fix the O(N^2) issue, we need to optimize the "search for compatible job" step.
   * Instead of scanning linearly (O(N)) to find the next job, we can use
   * Binary Search (O(log N)) IF the jobs are sorted.
   * * 1. Sort jobs by Start Time.
   * 2. For a job ending at time 'E', use Binary Search to find the
   * first job that starts at time >= 'E'.
   * * Complexity Analysis:
   * --------------------
   * Time Complexity: O(N log N)
   * - Sorting: O(N log N)
   * - DP States: N states.
   * - Transitions: Each state performs one Binary Search O(log N).
   * - Total: O(N log N).
   * * Space Complexity: O(N)
   * - Storing the 'jobs' vector and the 'DP' array.
   */
  int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
  {

    int N = startTime.size();

    // 1. Data Prep
    vector<vector<int>> jobs(N, vector<int>(3));

    for (int i = 0; i < N; i++)
    {
      jobs[i] = {startTime[i], endTime[i], profit[i]};
    }

    // 2. Sort by Start Time to enable Binary Search
    sort(jobs.begin(), jobs.end());

    // 3. Initialize DP array
    vector<int> DP(N, -1);

    return rec(0, jobs, DP);
  }
};

int main()
{
  return 0;
}
