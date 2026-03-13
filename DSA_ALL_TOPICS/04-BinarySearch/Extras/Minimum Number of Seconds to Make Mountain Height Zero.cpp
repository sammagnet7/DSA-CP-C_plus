#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*

Title: 3296. Minimum Number of Seconds to Make Mountain Height Zero

Linke:
https://www.youtube.com/watch?v=TUfk43zbdwI
https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/


Problem statement:
You are given an integer mountainHeight denoting the height of a mountain.

You are also given an integer array workerTimes representing the work time of workers in seconds.

The workers work simultaneously to reduce the height of the mountain. For worker i:

To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.


Example 1:
Input: mountainHeight = 4, workerTimes = [2,1,1]
Output: 3
Explanation:
One way the height of the mountain can be reduced to 0 is:
Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2 = 3 seconds.
Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3 seconds.

Example 2:
Input: mountainHeight = 10, workerTimes = [3,2,2,4]
Output: 12
Explanation:
Worker 0 reduces the height by 2, taking workerTimes[0] + workerTimes[0] * 2 = 9 seconds.
Worker 1 reduces the height by 3, taking workerTimes[1] + workerTimes[1] * 2 + workerTimes[1] * 3 = 12 seconds.
Worker 2 reduces the height by 3, taking workerTimes[2] + workerTimes[2] * 2 + workerTimes[2] * 3 = 12 seconds.
Worker 3 reduces the height by 2, taking workerTimes[3] + workerTimes[3] * 2 = 12 seconds.
The number of seconds needed is max(9, 12, 12, 12) = 12 seconds.

Example 3:
Input: mountainHeight = 5, workerTimes = [1]
Output: 15

Explanation:
There is only one worker in this example, so the answer is workerTimes[0] + workerTimes[0] * 2 + workerTimes[0] * 3 + workerTimes[0] * 4 + workerTimes[0] * 5 = 15.



Constraints:
1 <= mountainHeight <= 105
1 <= workerTimes.length <= 104
1 <= workerTimes[i] <= 106

 */

//--------------------------------------
// Approach 1: Binary search [OPTIMAL]
//--------------------------------------

/*
 * ============================================================================
 * APPROACH: Binary Search on Answer + O(1) Math Derivation
 * ============================================================================
 * * --- THE MATHEMATICAL DERIVATION (O(1) Worker Capacity) ---
 *
 *
 * We need to figure out exactly how much height (x) a single worker can reduce
 * in a given total time (T).
 *
 * * 1. The Arithmetic Series:
 * A worker with a base time of 't' takes 't' seconds for the first unit,
 * '2t' for the second, '3t' for the third, and so on.
 * The total time T to reduce 'x' units is the sum of an arithmetic progression:
 * T = t + 2t + 3t + ... + xt
 * T = t * (1 + 2 + 3 + ... + x)
 * T = t * (x * (x + 1)) / 2
 *
 * * 2. Isolating x:
 * We need to find the maximum integer 'x' that satisfies:
 * t * (x * (x + 1)) / 2 <= T
 * First, multiply both sides by (2 / t):
 * x^2 + x <= (2 * T) / t
 *
 * * 3. Completing the Square:
 * To solve for 'x', we complete the square by adding 0.25 to both sides:
 * x^2 + x + 0.25 <= ((2 * T) / t) + 0.25
 * (x + 0.5)^2 <= ((2 * T) / t) + 0.25
 *
 * * 4. The Final Formula:
 * Take the square root of both sides and subtract 0.5:
 * x + 0.5 <= sqrt(((2 * T) / t) + 0.25)
 * x <= sqrt(((2 * T) / t) + 0.25) - 0.5
 *
 * * Because 'x' must be a whole number of units, casting this resulting
 * floating-point value down to an integer gives us the exact maximum work
 * the worker can complete!
 *
 *
 * * --- COMPLEXITY ANALYSIS ---
 * Time Complexity: O(N * log(MaxTime))
 * - N is the number of workers.
 * - The maximum possible time is around 5 * 10^15.
 * - The binary search takes ~log2(5 * 10^15) approx 53 iterations.
 * - In each of those 53 iterations, we do an O(N) loop over the workers.
 * - Evaluating the quadratic formula takes O(1) time.
 * - Total operations approx 53 * 10^4, which executes in roughly ~1 ms.
 * * Space Complexity: O(1)
 * - We only use primitive variables (l, r, mid, workdone) for the search
 * space. No extra arrays or dynamically allocated data structures.
 * ============================================================================
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;

class Solution
{

private:
    /**
     * Validation Function:
     * Determines if all workers combined can reduce the mountain height by at
     * least 'm' within exactly 't' seconds.
     */
    bool check(ll t, int m, vector<int> &wTimes)
    {

        ll workdone = 0; // Accumulates total units of height reduced by all workers

        for (int i = 0; i < wTimes.size(); ++i)
        {

            // Apply the derived quadratic formula: x = sqrt((2*T)/t + 0.25) - 0.5
            // 1. Use 'long double' (128-bit or 80-bit precision depending on the compiler).
            // 2. Multiply by 2.0L to force the compiler to evaluate the numerator as a
            //    high-precision float before dividing, preventing integer truncation.
            long double curWorkDouble = sqrtl((2.0L * t) / wTimes[i] + 0.25L) - 0.5L;

            // Cast the floating-point result down to the nearest whole integer.
            // This represents the maximum completed units this specific worker can handle.
            ll curWork = (ll)curWorkDouble;

            workdone += curWork;

            // Early exit: If we have already cleared the mountain, no need to calculate
            // the remaining workers. This saves unnecessary CPU cycles.
            if (workdone >= m)
            {
                return true;
            }
        }

        // If all workers finish and the combined total is less than 'm', 't' is too short.
        return false;
    }

public:
    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes)
    {

        ll n = workerTimes.size();
        ll m = mountainHeight;

        // --- DEFINE THE BINARY SEARCH BOUNDARIES ---

        // Find the fastest worker. Assuming the fastest worker does the entire job
        // alone gives us the tightest and safest possible worst-case upper bound.
        ll minWorkTime = *min_element(workerTimes.begin(), workerTimes.end());

        // Calculate maxTime using the arithmetic sum formula: t * (m * (m + 1)) / 2
        ll maxTime = minWorkTime * (m * (m + 1)) / 2;

        ll l = 1;       // Minimum possible time (1 second)
        ll r = maxTime; // Maximum possible time

        // Track the absolute minimum valid time found so far.
        // Initialized to maxTime to ensure we start with a guaranteed valid baseline.
        ll minTime = maxTime;

        // --- EXECUTE BINARY SEARCH ---

        // Using l <= r ensures we don't prematurely exit and miss checking the final convergence point.
        while (l <= r)
        {

            // Calculate mid-point safely to prevent integer overflow
            ll mid = l + (r - l) / 2;

            if (check(mid, m, workerTimes))
            {
                // 'mid' seconds is enough time to clear the mountain!
                // Record this as our best answer so far...
                minTime = mid;
                // ...and shrink the right bound to see if we can do it even faster.
                r = mid - 1;
            }
            else
            {
                // 'mid' seconds is NOT enough time.
                // We must increase our time allowance by moving the left bound up.
                l = mid + 1;
            }
        }

        return minTime;
    }
};

//---------------------------------------
// Approach 2: Min heap
//---------------------------------------

#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;
using ll = long long;

/**
 * Idea: Greedy Simulation using a Min-Heap (Priority Queue)
 * * Concept:
 * We need to reduce the mountain height by exactly `m` units. To minimize the overall
 * time, we should greedily assign each unit of work to the worker who will complete
 * their next unit at the earliest possible TOTAL accumulated time.
 * A Min-Heap perfectly serves this purpose by keeping the worker with the lowest
 * projected future time at the top.
 * * Tuple State Definition: <totalWorkerTime, round, wokerIdx>
 * - totalWorkerTime: The absolute time (in seconds) this worker will reach once
 * they finish their currently assigned next unit of work.
 * - round: The specific unit of work (1st, 2nd, 3rd...) this worker is about to start.
 * - wokerIdx: The original index of the worker in the `workerTimes` array so we
 * can look up their base speed.
 * * Complexity:
 * - Time: O(M * log(N)), where M = mountainHeight and N = workerTimes.size().
 * We initialize a heap of size N (O(N log N)), and then perform M pops/pushes
 * (each taking O(log N) time).
 * - Space: O(N) to store exactly one state per worker in the priority queue.
 */
class Solution
{
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes)
    {

        int n = workerTimes.size();
        int m = mountainHeight;

        // Min-heap ordered by the first element of the tuple (totalWorkerTime)
        // Using greater<> ensures the smallest time bubbles up to the top.
        priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> minpq;

        // Initialize the heap with the first round of work for every single worker.
        // For round 1, the total time is simply their base multiplier time.
        for (int i = 0; i < n; ++i)
        {
            minpq.push({workerTimes[i], 1, i});
        }

        // Tracks the maximum time any individual worker takes across all assigned units.
        // Since workers operate simultaneously, the overall time is bottlenecked by the slowest total worker.
        ll minTime = 0;

        // Assign exactly 'm' units of mountain height to be reduced.
        while (m--)
        {

            // 1. Unpack the state of the worker who will finish their next unit the soonest.
            auto [totalWorkerTime, round, wokerIdx] = minpq.top();

            // Remove this current state from the heap as we are committing to this assignment.
            minpq.pop();

            // 2. Commit the work: The overall project time must be at least the time
            // this specific worker took to finish this unit.
            minTime = max(minTime, totalWorkerTime);

            // 3. Prepare this worker for their next potential assignment.
            ++round; // Increment the round multiplier (e.g., from 1 to 2)

            // Calculate what their total accumulated time WOULD be if we give them one more unit.
            // Critical Safety: (ll) cast prevents 32-bit integer overflow when base time
            // (up to 10^6) multiplies against round (up to 10^5).
            totalWorkerTime = totalWorkerTime + ((ll)workerTimes[wokerIdx] * round);

            // 4. Push this worker's future state back into the heap to compete for the remaining work.
            minpq.push({totalWorkerTime, round, wokerIdx});
        }

        // Return the global maximum time recorded after all 'm' units have been distributed.
        return minTime;
    }
};

int main()
{

    return 0;
}