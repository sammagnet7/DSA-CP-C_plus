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

1. Title: Burst Balloons

Links:
https://takeuforward.org/data-structure/burst-balloons-partition-dp-dp-51/
https://www.youtube.com/watch?v=Yz4LlDSlkns
https://takeuforward.org/plus/dsa/problems/burst-balloons?tab=editorial
https://leetcode.com/problems/burst-balloons/description/



Problem statement:
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
Return the maximum coins you can collect by bursting the balloons wisely.

Examples:
    Example 1:
    Input: nums = [3,1,5,8]
    Output: 167
    Explanation:
    nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
    coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

    Example 2:
    Input: nums = [1,5]
    Output: 10


Constraints:
    n == nums.length
    1 <= n <= 300
    0 <= nums[i] <= 100



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
// 1. Title: Burst Balloons
//-------------------------------------------------------------------------------

class Solution
{
private:
    int INF = -(1e9 + 7);
    vector<vector<int>> dp;

    //-----------------------------------------------------
    // 🟢 Approach 1: Recursion + Memoization (Top-Down DP)
    //-----------------------------------------------------

    /**
     * @brief Recursive helper to compute the maximum coins for a specific interval.
     * * @details
     * --- THE PROBLEM WITH FORWARD THINKING ---
     * If we try to choose the FIRST balloon to burst, the array dynamically shrinks.
     * Balloons that were separated become adjacent (e.g., bursting B in [A, B, C]
     * makes A and C adjacent). This destroys the independence of subproblems because
     * the left and right halves now depend on each other's surviving elements.
     * * --- THE "REVERSE THINKING" PARADIGM ---
     * Instead of choosing the first balloon to burst, we choose the balloon 'k' that
     * will burst ABSOLUTELY LAST in the current interval.
     * Because 'k' survives until the very end, it acts as an impenetrable wall between
     * the left half and the right half. The left balloons can burst in any order, and
     * the right balloons can burst in any order, without ever interacting with each other!
     * * --- STATE DEFINITION (EXCLUSIVE BOUNDARIES) ---
     * @param l: The left boundary (exclusive).
     * @param r: The right boundary (exclusive).
     * The state represents: "What is the maximum coins we can get by bursting all
     * balloons STRICTLY BETWEEN index 'l' and index 'r'?"
     * * --- TRANSITION LOGIC ---
     * If balloon 'k' (where l < k < r) is the LAST balloon to burst between l and r,
     * every other balloon inside (l, r) is already gone.
     * Therefore, the immediate left neighbor of 'k' is strictly 'l', and the immediate
     * right neighbor of 'k' is strictly 'r'.
     * Coins for 'k' = nums[l] * nums[k] * nums[r].
     * Total = (Coins from left subproblem) + (Coins from right subproblem) + (Coins for 'k').
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N^3). There are O(N^2) unique (l, r) states. For each state,
     * we run a loop of size O(N) to test every possible 'k'.
     * Space Complexity : O(N^2) for the memoization table + O(N) auxiliary recursion stack.
     */
    int rec(int l, int r, vector<int> &nums)
    {

        // Base Case: If the boundaries are adjacent (or crossed), there are no
        // balloons strictly between them to burst. Return 0 coins.
        if (r - l <= 1)
        {
            return 0;
        }

        // Memoization Check: Return precomputed answer if available.
        if (dp[l][r] != -1)
        {
            return dp[l][r];
        }

        int maxCost = INF;

        // Try making every balloon 'k' strictly between 'l' and 'r' the last to burst.
        for (int k = l + 1; k < r; ++k)
        {

            // Cost of bursting 'k' last inside this specific interval
            int curCost = (nums[l] * nums[k] * nums[r]);

            // Add the completely independent optimal costs of the left and right halves
            curCost += (rec(l, k, nums) + rec(k, r, nums));

            // Track the absolute maximum cost found for this interval
            maxCost = max(maxCost, curCost);
        }

        // Cache and return
        return dp[l][r] = maxCost;
    }

public:
    /**
     * @brief Solves the Burst Balloons problem using Top-Down Memoization (O(N^3) Time, O(N^2) Space).
     * * @details
     * We pad the original array with 1s at both ends. This elegantly handles the edge
     * cases where bursting the first or last balloon requires multiplying by an
     * out-of-bounds 1.
     */
    int maxCoins1(vector<int> &nums)
    {

        int n = nums.size();

        // C++ Memory Optimization: Allocate a padded array of the exact size immediately,
        // avoiding the O(N) shift penalty of nums.insert(nums.begin(), 1).
        vector<int> paddedNums(n + 2, 1);
        for (int i = 0; i < n; ++i)
        {
            paddedNums[i + 1] = nums[i];
        }

        int paddedSize = paddedNums.size();

        // Initialize the DP table with -1 for memoization
        dp = vector<vector<int>>(paddedSize, vector<int>(paddedSize, -1));

        // Start the recursion. We want to burst all real balloons, which are located
        // strictly between index 0 (the left pad) and index paddedSize - 1 (the right pad).
        return rec(0, paddedSize - 1, paddedNums);
    }

    //-----------------------------------------
    // 🟢 Approach 2: Tabulation (Bottom-Up DP)
    //-----------------------------------------

    /**
     * @brief Solves the Burst Balloons problem using Bottom-Up Tabulation.
     * * @details
     *
     * --- TOPOLOGICAL MATRIX FILLING ORDER ---
     * In bottom-up DP, we must solve smaller subproblems before larger ones.
     * To calculate dp[l][r], we rely on dp[l][k] and dp[k][r] (where l < k < r).
     * 1. dp[k][r] requires row 'k', which is strictly GREATER than our current row 'l'.
     * Therefore, the outer loop for 'l' MUST iterate BACKWARDS (from n-1 down to 0).
     * 2. dp[l][k] requires column 'k', which is strictly LESS than our current column 'r'.
     * Therefore, the inner loop for 'r' MUST iterate FORWARDS (from l+2 up to n-1).
     * * --- COMPLEXITY ---
     * Time Complexity  : O(N^3). Three tightly nested loops. No recursive call stack overhead.
     * Space Complexity : O(N^2) to store the DP matrix.
     */
    int maxCoins(vector<int> &nums)
    {

        int n = nums.size();

        // Pad the array with 1s at boundaries
        vector<int> paddedNums(n + 2, 1);
        for (int i = 0; i < n; ++i)
        {
            paddedNums[i + 1] = nums[i];
        }

        int paddedSize = paddedNums.size();

        // Initialize DP table with 0. This implicitly handles our base case
        // (r - l <= 1 returns 0) without needing explicit checks.
        dp = vector<vector<int>>(paddedSize, vector<int>(paddedSize, 0));

        // 'l' loops strictly backwards to guarantee row 'k' (below 'l') is already computed.
        for (int l = paddedSize - 1; l >= 0; --l)
        {

            // 'r' loops strictly forwards. It starts at l + 2 because an interval
            // of length 1 or less has no balloons strictly inside it to burst.
            for (int r = l + 2; r < paddedSize; ++r)
            {

                int maxCost = INF;

                // Try every balloon 'k' strictly inside the (l, r) boundary as the last to burst
                for (int k = l + 1; k < r; ++k)
                {

                    // Cost calculation exactly mirrors the recursive transition
                    int curCost = (paddedNums[l] * paddedNums[k] * paddedNums[r]);
                    curCost += (dp[l][k] + dp[k][r]);

                    maxCost = max(maxCost, curCost);
                }

                // Store the optimal answer for this interval
                dp[l][r] = maxCost;
            }
        }

        // The final answer is the max coins gained by bursting everything strictly
        // between the first pad (index 0) and the last pad (index paddedSize - 1).
        return dp[0][paddedSize - 1];
    }
};
//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
