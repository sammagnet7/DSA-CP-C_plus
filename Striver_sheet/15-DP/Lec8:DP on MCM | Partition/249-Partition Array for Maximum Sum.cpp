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

1. Title: Partition Array for Maximum Sum | Front Partition : DP 54

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
0 <= arr[i] <= 109
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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Partition Array for Maximum Sum | Front Partition : DP 54
    //-------------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
