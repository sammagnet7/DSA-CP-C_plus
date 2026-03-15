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

1. Title: Partition Array for Maximum Sum

Links:
https://takeuforward.org/data-structure/partition-array-for-maximum-sum-front-partition-dp-54/
https://www.youtube.com/watch?v=PhWWJmaKfMc
https://leetcode.com/problems/partition-array-for-maximum-sum/description/


Problem statement:
Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.
Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

Examples:
    Example 1:
    Input: arr = [1,15,7,9,2,5,10], k = 3
    Output: 84
    Explanation: arr becomes [15,15,15,9,10,10,10]

    Example 2:
    Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
    Output: 83

    Example 3:
    Input: arr = [1], k = 1
    Output: 1


Constraints:
1 <= arr.length <= 500
0 <= arr[i] <= 10^9
1 <= k <= arr.length



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/
//-------------------------------------------------------------------------------
// 1. Title: Partition Array for Maximum Sum | Front Partition
//-------------------------------------------------------------------------------
class Solution
{
public:
    //---------------------------------------------
    // Approach 1: Top-down [OPTIMAL] [Recommended]
    //---------------------------------------------

    /*
        Function: maxPartSum
        ------------------------------------
        This recursive function returns the maximum sum obtainable by partitioning
        the array starting from index `start` into subarrays of size at most `k`.

        Parameters:
        - start : Current index from which we are partitioning
        - arr   : The input array
        - k     : Maximum allowed partition size
        - n     : Length of the array
        - dp    : Memoization table (dp[i] stores max sum starting from index i)

        Approach:
        - At each index `start`, we try all possible partitions of size 1 to k (or until end of array).
        - For each partition, we find:
            1. maxEl = maximum element in the current partition
            2. curPartMaxSum = maxEl * size_of_partition
        - Then recursively calculate the best sum for the remaining array starting from i+1.
        - Take the maximum of all such options.

        Time Complexity:
        - There are `n` states (start ranges from 0 to n-1).
        - For each state, we try at most `k` partitions.
        - Inside the loop, maxEl is updated in O(1), so no extra nested loop.
        - Total: O(n * k)

        Space Complexity:
        - O(n) for the dp array.
        - O(n) for recursion stack in the worst case.
    */
    int maxPartSum(int start, vector<int> &arr, int k, int n, vector<int> &dp)
    {

        // Base Case: If we have crossed the last index, no sum can be added
        if (start >= n)
            return 0;

        // If already computed, return memoized result
        if (dp[start] != -1)
            return dp[start];

        int maxPsum = INT_MIN; // To track max sum possible from this index
        int maxEl = INT_MIN;   // To track max element in the current partition

        // Try all partitions starting at `start` with length up to `k`
        for (int i = start; i < start + k && i < n; i++)
        {

            // Update max element in the current partition
            maxEl = max(maxEl, arr[i]);

            // Current partition sum = max element * size of partition
            int curPartMaxSum = maxEl * (i - start + 1);

            // Total sum = current partition sum + best sum for remaining part
            int curSum = curPartMaxSum + maxPartSum(i + 1, arr, k, n, dp);

            // Update the maximum partition sum
            maxPsum = max(maxPsum, curSum);
        }

        // Memoize and return the result
        return dp[start] = maxPsum;
    }

    /*
        Wrapper function: maxSumAfterPartitioning
        ------------------------------------
        Initializes DP and starts the recursion.

        Time Complexity: O(n * k)
        Space Complexity: O(n) for DP + O(n) recursion stack
    */
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        vector<int> dp(n, -1);

        return maxPartSum(0, arr, k, n, dp);
    }
};

//---------------------------------
// Approach 2: Bottom up [OPTIMAL]
//---------------------------------

class Solution
{

public:
    /**
     * @brief Computes the largest sum of the array after partitioning into subarrays of length at most k.
     * * * * --- THE CORE IDEA: 1D PARTITION DP (FIXED COST) ---
     * We are avoiding the O(N^3) Matrix Chain Multiplication (MCM) trap!
     * When we split the array at index 'p', the cost of the left chunk (arr[start...p])
     * is completely known and FIXED: it's simply the maximum element in that chunk
     * multiplied by the chunk's length. We lock in this 'leftSum' and immediately
     * add it to the pre-computed optimal 'rightSum' of the remaining suffix.
     * * * * --- 1D STATE DEFINITION & TOPOLOGICAL ORDER ---
     * dp[start]: The maximum sum we can achieve for the suffix arr[start...n-1].
     * Topological Order: To calculate dp[start], we rely on dp[p+1] (which is to the right).
     * Therefore, the outer loop MUST iterate backwards from n-1 down to 0.
     * * * * --- COMPLEXITY ---
     * Time Complexity  : O(N * K). For each of the N elements, the inner loop runs at most
     * K times. By tracking the maximum value on the fly ('tillnowMax'), we avoid any
     * redundant iterations.
     * Space Complexity : O(N) auxiliary space for the 1D DP array.
     */
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {

        int n = arr.size();

        // dp array of size n + 1 to easily handle the out-of-bounds base case (dp[n] = 0).
        vector<int> dp(n + 1, 0);

        // Loop backwards to solve smaller right-side suffixes first
        for (int start = n - 1; start >= 0; --start)
        {

            // Track the maximum value seen in the current left chunk
            int tillnowMax = -1e9;

            // Track the absolute best partition sum for the suffix starting at 'start'
            int curMaxSum = -1e9;

            // Try placing a cut after index 'p'.
            // Constraint 1: The chunk length (p - start + 1) cannot exceed 'k'.
            // Constraint 2: 'p' cannot go out of bounds (p < n).
            for (int p = start; p <= start + k - 1 && p < n; ++p)
            {

                // Dynamically update the maximum value as our chunk expands to the right
                tillnowMax = max(tillnowMax, arr[p]);

                // --- THE "FIXED COST" MATH ---
                // 1. The left chunk is locked in. Its value is max_element * length.
                int leftSum = tillnowMax * (p - start + 1);

                // 2. The right suffix is already optimally solved in our DP array!
                int rightSum = dp[p + 1];

                // Combine them for the total sum of this specific partition split
                int curSum = leftSum + rightSum;

                // Keep the maximum result across all valid cuts 'p'
                curMaxSum = max(curMaxSum, curSum);
            }

            // Store the optimal answer for this specific 'start' index
            dp[start] = curMaxSum;
        }

        // The final answer is the maximum sum for the entire array starting at index 0
        return dp[0];
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
