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

1. Title: Longest Divisible Subset | (DP-44)

Links:
https://takeuforward.org/data-structure/longest-divisible-subset-dp-44/
https://www.youtube.com/watch?v=gDuZwBW9VvM
https://takeuforward.org/plus/dsa/problems/largest-divisible-subset?tab=editorial
https://leetcode.com/problems/largest-divisible-subset/description/

Problem statement:
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:

answer[i] % answer[j] == 0, or
answer[j] % answer[i] == 0
If there are multiple solutions, return any of them.

Examples:
    Example 1:
    Input: nums = [1,2,3]
    Output: [1,2]
    Explanation: [1,3] is also accepted.

    Example 2:
    Input: nums = [1,2,4,8]
    Output: [1,2,4,8]


Constraints:
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 109
    All the integers in nums are unique.

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
    // 1. Title: Longest Divisible Subset | (DP-44)

    /* -------------------------------------------------------------------------
       Problem: Largest Divisible Subset
       Idea:
       - Find the largest subset where every pair (a, b) satisfies a % b == 0 or b % a == 0.
       - Sort the array for easier divisibility checks.
       - dp[i] stores the length of the largest divisible subset ending at index i.
       - prev[i] stores the previous index in the subset chain.
       - Update dp[curI] if nums[curI] can extend a previous divisible subset.
       - Reconstruct the subset using prev[].
       Time Complexity: O(n^2)
       Space Complexity: O(n)
   ------------------------------------------------------------------------- */

    vector<int> largestDivisibleSubset(vector<int> &nums)
    {

        int n = nums.size();

        /* Step 1: Sort the array to simplify divisibility checking */
        sort(nums.begin(), nums.end());

        /* dp[i] = length of largest divisible subset ending at i */
        vector<int> dp(n, 1);

        /* prev[i] = index of previous element in chain ending at i */
        vector<int> prev(n, -1);

        /* Step 2: Build dp table by checking all previous elements */
        for (int curI = 1; curI < n; curI++)
        {
            for (int preI = 0; preI < curI; preI++)
            {
                /* Check divisibility condition */
                if (nums[curI] % nums[preI] == 0)
                {
                    int newCount = dp[preI] + 1;
                    if (newCount > dp[curI])
                    {
                        dp[curI] = newCount;
                        prev[curI] = preI; /* Link current element to previous in subset */
                    }
                }
            }
        }

        /* Step 3: Find the index of maximum subset length */
        int maxLen = 0, maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (dp[i] > maxLen)
            {
                maxLen = dp[i];
                maxIndex = i;
            }
        }

        /* Step 4: Reconstruct subset by backtracking prev[] */
        vector<int> ans;
        int idx = maxIndex;
        while (idx != -1)
        {
            ans.push_back(nums[idx]);
            idx = prev[idx];
        }

        /* Optional: reverse(ans.begin(), ans.end()); to get increasing order */
        return ans;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
