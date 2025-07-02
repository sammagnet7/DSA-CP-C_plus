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

**
NOTE: 
    WHENEVER COUNT OF SUB-ARRAYS EQUALS K is there, 
    USE APPROACH: count_equals_(k) = count_less_equal_(k)-count_less_equal_(k-1)
**

1. Title: Binary Subarrays With Sum equals K

Links:
https://takeuforward.org/plus/dsa/problems/binary-subarrays-with-sum?tab=editorial
https://www.youtube.com/watch?v=XnMdNUkX6VM&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=9
https://leetcode.com/problems/binary-subarrays-with-sum/description/


Problem statement:
Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

Examples:
    Example 1:
    Input: nums = [1,0,1,0,1], goal = 2
    Output: 4
    Explanation: The 4 subarrays are bolded and underlined below:
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]
    [1,0,1,0,1]

    Example 2:
    Input: nums = [0,0,0,0,0], goal = 0
    Output: 15


INPUT::::::


OUTPUT::::::

------------------------------------------------------------------------

2. Title: Count Number of Nice Subarrays

Links:
https://www.youtube.com/watch?v=j_QOv9OT9Og&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=10
https://takeuforward.org/plus/dsa/problems/count-number-of-nice-subarrays?tab=editorial
https://leetcode.com/problems/count-number-of-nice-subarrays/description/

Problem statement:
Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.


Examples:
    Example 1:
    Input: nums = [1,1,2,1,1], k = 3
    Output: 2
    Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

    Example 2:
    Input: nums = [2,4,6], k = 1
    Output: 0
    Explanation: There are no odd numbers in the array.

    Example 3:
    Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
    Output: 16


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //------------------------------------------------------------------------
    // 1. Binary Subarrays With Sum equals K
    //

    // Approach1:
    //

    // // Sub-optimal approach: Prefix sum
    // // Time: O(N) ~ O(N^2) due to using map
    // // Space: O(N)
    // int numSubarraysWithSum(vector<int>& nums, int goal) {

    //     int N = nums.size();
    //     int ans=0;

    //     unordered_map<int,int> mp; // O(N): <prefix sum, freq>
    //     mp[0] = 1;  // For considering the sum of array from starting

    //     long long prefix_sum = 0;

    //     for(int i=0; i<N; i++){
    //         prefix_sum += nums[i];
    //         int req_pre_sum = prefix_sum - goal;

    //         ans += (mp[req_pre_sum]);
    //         mp[prefix_sum]++;
    //     }

    //     return ans;
    // }

    // -------------------------------------
    // Approach2:
    //

    // O(2N)
    int numSubarraysWith_lessEqual_Sum(vector<int> &nums, int goal)
    {

        if (goal < 0)
            return 0;
        int N = nums.size();
        int ans = 0;

        int l = 0;
        int r = 0;
        int sum = 0;

        while (r < N)
        { // O(N)
            int cur = nums[r];
            sum += cur;

            if (sum <= goal)
            { // less equal
                int less_equal_count = r - l + 1;
                ans += less_equal_count;
            }

            while (sum > goal && l <= r)
            { // O(N)
                sum -= nums[l];
                l++;
                if (sum <= goal)
                { // less equal
                    int less_equal_count = r - l + 1;
                    ans += less_equal_count;
                }
            }

            r++;
        }

        return ans;
    }

    // Optimal approach: Two pointer
    // Note: Basic two pointer approach for sum works iff element>0
    // Here as 0 exists, we have to handle the scenarios for considering 0s
    // numSubarraysWith_equal_Sum = numSubarraysWith_lessEqual_Sum - numSubarraysWith_lessEqual_(Sum-1)
    //
    // Time: O(4N)
    // Space: O(1)
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {

        int val1 = numSubarraysWith_lessEqual_Sum(nums, goal);       // O(2N)
        int val2 = numSubarraysWith_lessEqual_Sum(nums, (goal - 1)); // O(2N)

        return (val1 - val2);
    }
};

//------------------------------------------------------------------------
// 2. Count Number of Nice Subarrays
//

class Solution
{
public:
    // O(2N)
    int numberOfSubarrays_less_equals(vector<int> &nums, int k)
    {

        int N = nums.size();
        int ans = 0;

        int l = 0;
        int r = 0;
        int oddCount = 0;

        while (r < N)
        { // O(N)
            if (nums[r] % 2)
            {
                oddCount++;
            }
            if (oddCount <= k)
            {
                ans += (r - l + 1);
            }
            while (oddCount > k)
            { // O(N)
                if (nums[l] % 2)
                {
                    oddCount--;
                }
                l++;

                if (oddCount <= k)
                {
                    ans += (r - l + 1);
                }
            }

            r++;
        }

        return ans;
    }

    // Optimal approach: Two pointer: count_equals_(k) = count_less_equal_(k)-count_less_equal_(k-1)
    //
    // Time: O(4N)
    // Space: O(1)
    int numberOfSubarrays(vector<int> &nums, int k)
    {

        return numberOfSubarrays_less_equals(nums, k) - numberOfSubarrays_less_equals(nums, k - 1);
    }
};

int main()
{
    return 0;
}
