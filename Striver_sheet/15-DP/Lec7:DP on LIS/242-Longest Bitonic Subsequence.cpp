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

1. Title: Longest Bitonic Subsequence | (DP-46)

Links:
https://takeuforward.org/data-structure/longest-bitonic-subsequence-dp-46/
https://www.youtube.com/watch?v=y4vN0WNdrlg
https://takeuforward.org/plus/dsa/problems/longest-bitonic-subsequence?tab=editorial
https://www.naukri.com/code360/problems/longest-bitonic-sequence_1062688?leftPanelTabValue=PROBLEM

Problem statement:
A Bitonic Sequence is a sequence of numbers that is first strictly increasing and then strictly decreasing.
A strictly ascending order sequence is also considered bitonic, with the decreasing part as empty, and same for a strictly descending order sequence.

For example, the sequences [1, 3, 5, 3, 2], [1, 2, 3, 4] are bitonic, whereas the sequences [5, 4, 1, 4, 5] and [1, 2, 2, 3] are not.
You are given an array 'arr' consisting of 'n' positive integers.
Find the length of the longest bitonic subsequence of 'arr'.

Example :
Input: 'arr' = [1, 2, 1, 2, 1]
Output: 3
Explanation: The longest bitonic subsequence for this array will be [1, 2, 1]. Please note that [1, 2, 2, 1] is not a valid bitonic subsequence, because the consecutive 2's are neither strictly increasing, nor strictly decreasing.


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
    // 1. Title: Longest Bitonic Subsequence | (DP-46)

    /*
     Method: longestBitonicSubsequence
     ----------------------------------------
     Finds the length of the Longest Bitonic Subsequence (LBS) in an array.
     A bitonic subsequence first increases and then decreases.

     Parameters:
     - arr : reference to the input array
     - n   : size of the array

     Returns:
     - Length of the longest bitonic subsequence.

     Logic:
     1. Use a 2D dp array of size 2 x n:
        - dp[0][i] = length of longest increasing subsequence ending at index i
        - dp[1][i] = length of longest (increasing then->) decreasing subsequence ending at index i
     2. Iterate through each element cur from 1 to n-1:
         a) Compare with all previous elements pre (0 to cur-1)
         b) If arr[pre] < arr[cur], we can extend the increasing subsequence:
            dp[0][cur] = max(dp[0][cur], dp[0][pre]+1)
         c) If arr[pre] > arr[cur], we can extend a decreasing subsequence:
            dp[1][cur] = max(dp[1][cur], max(dp[0][pre]+1, dp[1][pre]+1))
            (We can start decreasing from an increasing sequence or continue decreasing)
     3. Finally, for each index i, the longest bitonic subsequence ending at i is:
        max(dp[0][i], dp[1][i])
     4. Return the maximum among all indices.

     Time Complexity: O(n^2)
         - Two nested loops: cur (1..n-1) and pre (0..cur-1)
     Space Complexity: O(2*n) ~ O(n)
         - dp array with two rows: increasing and decreasing
 */

    int longestBitonicSubsequence(vector<int> &arr, int n)
    {
        // dp[0][i] = LIS ending at i, dp[1][i] = LDS ending at i
        vector<vector<int>> dp(2, vector<int>(n, 1));

        for (int cur = 1; cur < n; cur++)
        {
            for (int pre = 0; pre < cur; pre++)
            {

                if (arr[pre] < arr[cur])
                { // Increasing case
                    int newCount_inc = dp[0][pre] + 1;
                    if (newCount_inc > dp[0][cur])
                    {
                        dp[0][cur] = newCount_inc;
                    }
                }
                else if (arr[pre] > arr[cur])
                { // Decreasing case
                    // Can start decreasing from an increasing sequence or continue decreasing
                    int newCount_dec = max(dp[0][pre] + 1, dp[1][pre] + 1);
                    if (newCount_dec > dp[1][cur])
                    {
                        dp[1][cur] = newCount_dec;
                    }
                }
            }
        }

        // Find the maximum among all dp values
        int maxLength = 0;
        for (int i = 0; i < n; i++)
        {
            maxLength = max(maxLength, max(dp[0][i], dp[1][i]));
        }

        return maxLength;
    }

    /*
        Method: longestBitonicSubsequence
        ----------------------------------------
        Computes the length of the Longest Bitonic Subsequence (LBS) in an array.
        A bitonic subsequence first increases and then decreases.

        Parameters:
        - arr : reference to the input array
        - n   : size of the array

        Returns:
        - Length of the longest bitonic subsequence.

        Logic:
        1. dp1[i] ? Length of Longest Increasing Subsequence (LIS) ending at index i
        2. dp2[i] ? Length of Longest Decreasing Subsequence (LDS) starting at index i

        Step 1: Compute LIS ending at each index
            - For each i from 0 to n-1
                - Compare with all previous indices prev_index (0 to i-1)
                - If arr[prev_index] < arr[i], arr[i] can extend LIS
                - Update: dp1[i] = max(dp1[i], 1 + dp1[prev_index])

        Step 2: Compute LDS starting at each index
            - For each i from n-1 down to 0
                - Compare with all later indices prev_index (n-1 down to i+1)
                - If arr[prev_index] < arr[i], arr[i] can start or extend decreasing subsequence
                - Update: dp2[i] = max(dp2[i], 1 + dp2[prev_index])

        Step 3: Compute maximum length of bitonic subsequence
            - For each index i, the length of bitonic subsequence passing through i is:
                dp1[i] + dp2[i] - 1
                (Subtract 1 because arr[i] is counted in both dp1 and dp2)
            - Take the maximum among all indices

        Time Complexity: O(n^2)
            - Two nested loops for computing dp1 and dp2
        Space Complexity: O(n)
            - Two arrays of size n: dp1 and dp2
    */

    int longestBitonicSubsequence(vector<int> &arr, int n)
    {
        // dp1[i] = LIS ending at i, dp2[i] = LDS starting at i
        vector<int> dp1(n, 1);
        vector<int> dp2(n, 1);

        // Compute LIS ending at each index
        for (int i = 0; i < n; i++)
        {
            for (int prev_index = 0; prev_index < i; prev_index++)
            {
                if (arr[prev_index] < arr[i])
                {
                    dp1[i] = max(dp1[i], 1 + dp1[prev_index]);
                }
            }
        }

        // Compute LDS starting at each index
        for (int i = n - 1; i >= 0; i--)
        {
            for (int prev_index = n - 1; prev_index > i; prev_index--)
            {
                if (arr[prev_index] < arr[i])
                {
                    dp2[i] = max(dp2[i], 1 + dp2[prev_index]);
                }
            }
        }

        // Compute maximum length of bitonic subsequence
        int maxi = -1;
        for (int i = 0; i < n; i++)
        {
            maxi = max(maxi, dp1[i] + dp2[i] - 1);
        }

        return maxi;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
