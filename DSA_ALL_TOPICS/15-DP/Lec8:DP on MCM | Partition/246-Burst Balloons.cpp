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

1. Title: Burst Balloons | Partition DP | DP 51

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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Burst Balloons | Partition DP | DP 51
    //-------------------------------------------------------------------------------

    //-----------------------------------------
    // 🟢 Approach 1: Recursion + Memoization (Top-Down DP)
    //-----------------------------------------

    /*
    🔹 Intuition:
    - When solving interval DP problems, we consider which balloon to burst last.
    - Bursting k last in [i..j] splits the problem into two independent subproblems: [i..k-1] and [k+1..j].
    - Combine these with coins from bursting k itself: nums[i-1] * nums[k] * nums[j+1].

    ⏱ Time Complexity: O(n³)
    - There are O(n²) states (i,j).
    - For each state, we try O(n) possible last balloons.

    💾 Space Complexity: O(n²)
    - DP memoization table + recursion stack O(n).
    */

    // Recursive helper with memoization
    int recPart(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
    {

        // Base case: no balloons in the range
        if (i > j)
        {
            return 0;
        }

        // If already computed, return cached value
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        int maxCoins = INT_MIN;

        // Try bursting each balloon `k` as the last one in the range [i..j]
        for (int k = i; k <= j; k++)
        {

            // If we burst balloon k last, its neighbors are nums[i-1] and nums[j+1]
            int curCoins = nums[i - 1] * nums[k] * nums[j + 1];

            // Solve left and right subproblems recursively
            int leftPartCoins = recPart(i, k - 1, nums, dp);
            int rightPartCoins = recPart(k + 1, j, nums, dp);

            // Update maximum coins
            maxCoins = max(maxCoins, (curCoins + leftPartCoins + rightPartCoins));
        }

        // Memoize and return
        return dp[i][j] = maxCoins;
    }

    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();

        // Add virtual balloons with value 1 at both ends
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        // DP table initialized with -1
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        // Solve for the range [1..n]
        return recPart(1, n, nums, dp);
    }

    //-----------------------------------------
    // 🟢 Approach 2: Tabulation (Bottom-Up DP)
    //-----------------------------------------

    /*
    🔹 Intuition:
    - Same recurrence as recursion, but computed iteratively.
    - Build the solution for smaller subarrays first, then expand to larger ones.
    - Iterate i from n → 1 and j from i → n so smaller ranges are solved first.

    ⏱ Time Complexity: O(n³)
    - Triple loop over (i,j,k).

    💾 Space Complexity: O(n²)
    - 2D DP table only. No recursion stack.
    */

    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();

        // Add virtual balloons with value 1 at both ends
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        // DP table initialized with 0
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        // Fill DP bottom-up
        // i goes from n down to 1 (small intervals first)
        for (int i = n; i >= 1; i--)
        {
            for (int j = i; j <= n; j++)
            {

                int maxCoins = INT_MIN;

                // Try each balloon `k` as the last one in [i..j]
                for (int k = i; k <= j; k++)
                {

                    int curCoins = nums[i - 1] * nums[k] * nums[j + 1];
                    int leftPartCoins = dp[i][k - 1];
                    int rightPartCoins = dp[k + 1][j];

                    maxCoins = max(maxCoins, (curCoins + leftPartCoins + rightPartCoins));
                }

                dp[i][j] = maxCoins;
            }
        }

        // Answer is the interval [1..n]
        return dp[1][n];
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
