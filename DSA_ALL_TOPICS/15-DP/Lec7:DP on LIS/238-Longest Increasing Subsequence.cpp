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

1. Title: Longest Increasing Subsequence | (DP-41)

Links:
https://takeuforward.org/data-structure/longest-increasing-subsequence-dp-41/
https://www.youtube.com/watch?v=ekcwMsSIzVc
https://takeuforward.org/plus/dsa/problems/longest-increasing-subsequence?tab=editorial
https://leetcode.com/problems/longest-increasing-subsequence/description/


Problem statement:
Given an integer array nums, return the length of the longest strictly increasing subsequence.

Examples:
    Example 1:
    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

    Example 2:
    Input: nums = [0,1,0,3,2,3]
    Output: 4

    Example 3:
    Input: nums = [7,7,7,7,7,7,7]
    Output: 1

Constraints:
    1 <= nums.length <= 2500
    -104 <= nums[i] <= 104


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Longest Increasing Subsequence | Binary Search | (DP-43)

Links:
https://takeuforward.org/data-structure/longest-increasing-subsequence-binary-search-dp-43/
https://www.youtube.com/watch?v=on2hvxBXJH4
https://takeuforward.org/plus/dsa/problems/longest-increasing-subsequence?tab=editorial
https://leetcode.com/problems/longest-increasing-subsequence/description/


Problem statement:
Given an integer array nums, return the length of the longest strictly increasing subsequence.

Can you come up with an algorithm that runs in O(n log(n)) time complexity?

Examples:
    Example 1:
    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

    Example 2:
    Input: nums = [0,1,0,3,2,3]
    Output: 4

    Example 3:
    Input: nums = [7,7,7,7,7,7,7]
    Output: 1

Constraints:
    1 <= nums.length <= 2500
    -104 <= nums[i] <= 104


INPUT::::::

OUTPUT::::::


*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Longest Increasing Subsequence | (DP-41)

    // -----------------------------------------------------------------------------
    // Approach 1: Recursive + Memoization (Top-Down DP)
    // -----------------------------------------------------------------------------
    //
    // Function: recLIScount(curIdx, prevIdx, nums, n, dp)
    //
    // Idea:
    //   - At each index, we have two choices:
    //       1. Take the element (if strictly greater than the last chosen element).
    //       2. Skip the element.
    //   - Use recursion to explore both options and pick the max length.
    //   - Memoize results in a 2D DP table to avoid recomputation.
    //
    // dp[curIdx][prevIdx+1]:
    //   - Stores LIS length starting from index `curIdx`,
    //     when the previous chosen index is `prevIdx`.
    //   - Note: `prevIdx == -1` is mapped to `0` (shift by +1 in indexing).
    //
    // Base Case:
    //   - If curIdx == n → reached end of array → return 0.
    //
    // Time Complexity: O(n^2)
    //   - Each state defined by (curIdx, prevIdx) is computed once → O(n * n).
    // Space Complexity: O(n^2) for DP table + O(n) recursion stack → O(n^2).
    // -----------------------------------------------------------------------------

    int recLIScount(int curIdx, int prevIdx, vector<int> &nums, int n, vector<vector<int>> &dp)
    {
        if (curIdx == n)
            return 0;

        if (dp[curIdx][prevIdx + 1] != -1)
            return dp[curIdx][prevIdx + 1];

        int take = 0, notTake = 0;

        // Option 1: Take current element if valid
        if (prevIdx == -1 || nums[prevIdx] < nums[curIdx])
        {
            take = 1 + recLIScount(curIdx + 1, curIdx, nums, n, dp);
        }

        // Option 2: Skip current element
        notTake = recLIScount(curIdx + 1, prevIdx, nums, n, dp);

        return dp[curIdx][prevIdx + 1] = max(take, notTake);
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1)); // dp[curIdx][prevIdx+1]
        return recLIScount(0, -1, nums, n, dp);
    }

    // -----------------------------------------------------------------------------
    // Approach 2: Iterative DP (Bottom-Up Tabulation)
    // -----------------------------------------------------------------------------
    //
    // Idea:
    //   - Reverse the recursion: fill DP table starting from the end.
    //   - dp[curIdx][prevIdx+1] = LIS length starting from `curIdx`
    //     given last picked index `prevIdx`.
    //   - Iterate backwards to ensure future states are already computed.
    //
    // Transition:
    //   - If we "take" nums[curIdx], then move to curIdx+1 with prevIdx = curIdx.
    //   - If we "skip", then move to curIdx+1 keeping same prevIdx.
    //
    // Base Initialization:
    //   - dp[n][*] = 0 (if index is beyond array → LIS length = 0).
    //
    // Time Complexity: O(n^2)
    //   - Two nested loops over curIdx and prevIdx → O(n * n).
    // Space Complexity: O(n^2)
    //   - DP table of size (n+1) x (n+1).
    //   - Can be optimized to O(n) with space compression.
    // -----------------------------------------------------------------------------

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int curIdx = n - 1; curIdx >= 0; curIdx--)
        {
            for (int prevIdx = curIdx - 1; prevIdx >= -1; prevIdx--)
            {

                int take = 0, notTake = 0;

                // Option 1: Take current element
                if (prevIdx == -1 || nums[prevIdx] < nums[curIdx])
                {
                    take = 1 + dp[curIdx + 1][curIdx + (+1)];
                }

                // Option 2: Skip current element
                notTake = dp[curIdx + 1][prevIdx + (+1)];

                dp[curIdx][prevIdx + 1] = max(take, notTake);
            }
        }

        return dp[0][-1 + (+1)]; // starting at index 0 with prevIdx = -1 (mapped to 0)
    }

    // -----------------------------------------------------------------------------
    // Approach 3: Iterative DP (Tabulation)    [Needed for printing LIS]
    // Note: This approach
    //            - optimizes space
    //            - Best for Back tracing
    //            - So used for printing LIS
    // -----------------------------------------------------------------------------
    // ---------------------------------------------------------
    // Method: lengthOfLIS
    // Purpose: Finds the length of the Longest Increasing Subsequence (LIS)
    //          in the given array using a classic DP approach.
    //
    // Approach (Dynamic Programming - O(n^2)):
    // 1. Initialize a DP array `dp[n]` where dp[i] represents the length
    //    of the LIS ending at index i (with nums[i] as the last element).
    // 2. Base case: Each element alone forms a subsequence of length 1,
    //    so initialize dp[i] = 1 for all i.
    // 3. For each index `cur` (from 1 → n-1):
    //      - Check all previous indices `prev` (from 0 → cur-1).
    //      - If nums[prev] < nums[cur], then nums[cur] can extend
    //        the subsequence ending at nums[prev].
    //      - Update dp[cur] = max(dp[cur], dp[prev] + 1).
    // 4. The answer is the maximum value in dp[] because the LIS
    //    can end at any index.
    //
    // Example:
    //   nums = [10, 22, 9, 33, 21, 50]
    //   dp progression:
    //   Initially: [1, 1, 1, 1, 1, 1]
    //   After processing: [1, 2, 1, 3, 2, 4]
    //   Answer = 4 (LIS = [10, 22, 33, 50])
    //
    // Time Complexity: O(n^2)
    //   - For each element (n iterations), check all previous (up to n).
    //   - Total = n * n = O(n^2).
    //
    // Space Complexity: O(n)
    //   - Extra dp array of size n.
    //   - No additional recursion/stack overhead.
    // ---------------------------------------------------------

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);

        // Build LIS lengths
        for (int cur = 1; cur < n; cur++)
        {
            for (int prev = 0; prev < cur; prev++)
            {
                if (nums[prev] < nums[cur])
                {
                    // If nums[cur] can extend LIS ending at nums[prev]
                    dp[cur] = max(dp[cur], dp[prev] + 1);
                }
            }
        }

        // Result = max LIS length across all indices
        return *max_element(dp.begin(), dp.end());
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Longest Increasing Subsequence | Binary Search | (DP-43)
    //-------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------
    // Approach 4: Using Binary Search [OPTIMAL]
    // -----------------------------------------------------------------------------
    // Idea:
    // - Maintain a temporary array `temp` that helps track the smallest possible
    //   tail elements of increasing subsequences of different lengths.
    // - Iterate through `nums`:
    //   1. If current element is greater than the last element in `temp`,
    //      append it to `temp` (we extend the LIS).
    //   2. Otherwise, find the first element in `temp` which is >= current element
    //      (using binary search, i.e., `lower_bound`) and replace it.
    //      -> This ensures `temp` remains sorted and has the smallest possible
    //         values at each length, which is crucial for LIS length calculation.
    // - The size of `temp` at the end is the length of LIS.
    //
    // Note:
    // - `temp` does not store the actual LIS sequence but its length correctly.
    // - To reconstruct the LIS sequence, extra tracking arrays are required.
    //
    // Example: nums = [10, 9, 2, 5, 3, 7, 101, 18]
    //   Iterations:
    //     temp = [10]
    //     temp = [9]
    //     temp = [2]
    //     temp = [2, 5]
    //     temp = [2, 3]
    //     temp = [2, 3, 7]
    //     temp = [2, 3, 7, 101]
    //     temp = [2, 3, 7, 18]
    //   Answer = 4 (LIS length)
    //
    // Time Complexity: O(n log n)
    //   - For each of the n elements, we may do a binary search in `temp` (O(log n)).
    // Space Complexity: O(n)
    //   - In the worst case (strictly increasing input), `temp` can grow to size n.
    // -----------------------------------------------------------------------------
    
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();

        // `temp` will hold the "LIS candidate tails"
        vector<int> temp;
        temp.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > temp.back())
            {
                // Case 1: Current number extends LIS
                temp.push_back(nums[i]);
            }
            else
            {
                // Case 2: Replace the first element >= nums[i] to keep sequence optimal
                auto it = lower_bound(temp.begin(), temp.end(), nums[i]);
                *it = nums[i];
            }
        }

        return temp.size(); // LIS length
    }
};

int main()
{
    return 0;
}
