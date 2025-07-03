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

1. Title: Binary Subarrays With Sum

Links:
https://takeuforward.org/plus/dsa/problems/count-number-of-nice-subarrays?tab=editorial


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


*/

class Solution
{
public:
    //------------------------------------------------------------------------
    // 1. Binary Subarrays With Sum
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

    // --------------------------------------------------------------------
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

int main()
{
    return 0;
}
