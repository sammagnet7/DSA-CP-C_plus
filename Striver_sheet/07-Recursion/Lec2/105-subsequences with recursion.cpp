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

using namespace std;

/*

Subset Sum Equal To K exists?

https://www.naukri.com/code360/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.

Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

For Example :
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.

Follow-up:
Can you use dynamic programming and use the previously calculated result to calculate the new result?

INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------

Count Subsets with Sum K:

https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532?leftPanelTabValue=PROBLEM

Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.


Problem statement
You are given an array 'arr' of size 'n' containing positive integers and a target sum 'k'.
Find the number of ways of selecting the elements from the array such that the sum of chosen elements is equal to the target 'k'.
Since the number of ways can be very large, print it modulo 10 ^ 9 + 7.

Example:
Input: 'arr' = [1, 1, 4, 5]
Output: 3
Explanation: The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.

Follow-up:
The expected time complexity is O('n' * 'k').
Optimize it with DP.

INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------
    // Subset Sum Equal To K exists?

    // O(2^N) : w/o DP, so non-optimal
    bool recFindExists(vector<int> &arr, int index, int target, int prevSum)
    {

        if (index == arr.size() || prevSum > target)
            return false;

        int cur = arr[index];

        bool ret = false;
        if ((prevSum + cur) == target)
            return true;

        ret = recFindExists(arr, (index + 1), target, (prevSum + cur));
        if (ret)
            return true;

        ret = recFindExists(arr, (index + 1), target, prevSum);
        if (ret)
            return true;

        return false;
    }

    // NON-optimal approach: Recursion  w/o DP
    // Time: O(2^N) due to binary stack tree
    // Space: O(N) due to stack space
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        return recFindExists(arr, 0, k, 0);
    }

    // ---------------------------------------------
    // Count Subsets with Sum K:
    // ---------------------------------------------

    // -----------
    // APPROACH: 1
    // w/o DP

    int static const moduler = (1e9 + 7);

    // O(2^N) : w/o DP, so non-optimal
    int recCountSum(vector<int> &arr, int index, int target, int prevSum)
    {

        if (index == arr.size() || prevSum > target)
            return 0;

        int cur = arr[index];

        int ret = 0;
        if ((prevSum + cur) == target)
            ret = 1;

        ret += recCountSum(arr, (index + 1), target, (prevSum + cur));
        ret += recCountSum(arr, (index + 1), target, prevSum);

        return (ret % moduler);
    }

    // NON-optimal approach: Recursion  w/o DP
    // Time: O(2^N) due to binary stack tree
    // Space: O(N) due to stack space
    // For DP Refer: 223-subsequences with recursion.cpp
    int findWays(vector<int> &arr, int k)
    {
        return recCountSum(arr, 0, k, 0);
    }

    // -----------
    // APPROACH: 2
    // with DP
    // Links:
    // https://takeuforward.org/data-structure/count-subsets-with-sum-k-dp-17/
    // https://www.youtube.com/watch?v=ZHyb-A2Mte4
    // https://takeuforward.org/plus/dsa/problems/count-subsets-with-sum-k?tab=editorial

    // ---------------------------------------------
    // Count Subsets with Sum K
    // Problem: Given an array `arr` and a target sum `k`,
    // count the number of subsets whose elements sum up to exactly `k`.
    //
    // Approach: Recursive Backtracking with Memoization (Top-Down DP)
    //
    // Time Complexity: O(N * K)
    //   - N: number of elements in the array
    //   - K: target sum
    //   - Each unique state (index, prevSum) is computed only once
    //
    // Space Complexity: O(N * K) for the DP table + O(N) recursion stack
    // ---------------------------------------------

    // Modulo constant to handle large result values
    int static const moduler = (1e9 + 7);

    // Recursive function to count the number of valid subsets
    // Parameters:
    // - arr: input array
    // - dp: memoization table to store result for each (index, prevSum)
    // - index: current index in array
    // - target: the target subset sum we are aiming for
    // - prevSum: current accumulated sum so far
    int recFind(vector<int> &arr, vector<vector<int>> &dp, int index, int target, int prevSum)
    {

        // Base case 1: Reached end of array — no more elements to pick
        // Base case 2: Current sum exceeds target — can't proceed further
        if (index == arr.size() || prevSum > target)
            return 0;

        // If result for this state is already computed, return it
        if (dp[index][prevSum] != -1)
            return dp[index][prevSum];

        int cur = arr[index]; // Current element
        int ret = 0;          // Number of valid subsets from this state

        // If adding current element gives exactly the target, count this subset
        if ((prevSum + cur) == target)
            ret = 1;

        // Include the current element in subset
        ret += recFind(arr, dp, index + 1, target, prevSum + cur);

        // Exclude the current element from subset
        ret += recFind(arr, dp, index + 1, target, prevSum);

        // Memoize the result and return it modulo 1e9+7
        return dp[index][prevSum] = (ret % moduler);
    }

    // Main function to initialize DP table and start recursion
    // Parameters:
    // - arr: input array
    // - k: target sum
    // Returns: number of subsets with sum equal to k
    int findWays(vector<int> &arr, int k)
    {
        int N = arr.size();

        // Initialize DP table with -1 (uncomputed states)
        // dp[i][j] will store number of ways to get sum 'j' starting from index 'i'
        vector<vector<int>> dp(N, vector<int>(k + 1, -1));

        // Start recursion from index 0 and sum 0
        return recFind(arr, dp, 0, k, 0);
    }

    /*
    ---------------------------------------------
    Time Complexity:
    - O(N * K) where:
      N = size of input array
      K = target sum
    - Each state (index, prevSum) is computed only once.

    Space Complexity:
    - O(N * K) for the memoization table (dp)
    - O(N) recursion stack in worst case
    ---------------------------------------------
    */
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
