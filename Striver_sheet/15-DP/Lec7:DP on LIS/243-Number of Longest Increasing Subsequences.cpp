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

1. Title: Number of Longest Increasing Subsequences | (DP-47)

Links:
https://takeuforward.org/data-structure/number-of-longest-increasing-subsequences-dp-47/
https://www.youtube.com/watch?v=cKVl1TFdNXg
https://takeuforward.org/plus/dsa/problems/number-of-longest-increasing-subsequences?tab=editorial
https://leetcode.com/problems/number-of-longest-increasing-subsequence/


Problem statement:
Given an integer array nums, return the number of longest increasing subsequences.
Notice that the sequence has to be strictly increasing.

Examples:
    Example 1:
    Input: nums = [1,3,5,4,7]
    Output: 2
    Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

    Example 2:
    Input: nums = [2,2,2,2,2]
    Output: 5
    Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.

Constraints:
    1 <= nums.length <= 2000
    -106 <= nums[i] <= 106
    The answer is guaranteed to fit inside a 32-bit integer.



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
    // 1. Title: Number of Longest Increasing Subsequences | (DP-47)

    /*
    Method: findNumberOfLIS
    -----------------------
    Finds the number of Longest Increasing Subsequences (LIS) in the given array.

    Parameters:
    - nums : reference to input array

    Returns:
    - Total number of LIS in the array.

    Logic:
    1. Use dynamic programming to keep track of:
        - dp[i]    : Length of LIS ending at index i
        - count[i] : Number of LIS of length dp[i] ending at index i

    2. For each element at cur index:
        - Compare with all previous indices (pre) from 0 to cur-1
        - If nums[pre] < nums[cur], nums[cur] can extend the subsequence
        - Update dp[cur] and count[cur] accordingly:
            a) If dp[cur] < dp[pre] + 1, update dp[cur] = dp[pre] + 1 and reset count[cur] = count[pre]
            b) If dp[cur] == dp[pre] + 1, increment count[cur] by count[pre] (another LIS of same length found)

    3. Find the maximum LIS length (maxe) from dp array.

    4. Sum all counts[i] where dp[i] == maxe to get total number of LIS.

    Time Complexity: O(n^2)
        - Two nested loops for each pair of indices
    Space Complexity: O(n)
        - Two arrays of size n: dp and count
*/

    int findNumberOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<int> dp(n, 1);    // Length of LIS ending at index i
        vector<int> count(n, 1); // Number of LIS ending at index i

        // Build dp and count arrays
        for (int cur = 1; cur < n; cur++)
        {
            for (int pre = 0; pre < cur; pre++)
            {

                if (nums[pre] < nums[cur])
                {
                    if (dp[cur] < dp[pre] + 1)
                    {
                        dp[cur] = dp[pre] + 1;   // Found longer LIS ending at cur
                        count[cur] = count[pre]; // Inherit count from pre
                    }
                    else if (dp[cur] == dp[pre] + 1)
                    {
                        count[cur] += count[pre]; // Another LIS of same length found
                    }
                }
            }
        }

        // Find length of longest LIS
        int maxLength = 0;
        for (int i = 0; i < n; i++)
        {
            maxLength = max(maxLength, dp[i]);
        }

        // Count total number of LIS of maximum length
        int totalLIS = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i] == maxLength)
            {
                totalLIS += count[i];
            }
        }

        return totalLIS;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
