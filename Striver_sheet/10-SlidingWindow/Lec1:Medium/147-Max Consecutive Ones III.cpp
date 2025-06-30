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

1. Title: Max Consecutive Ones III

Links:
https://takeuforward.org/plus/dsa/problems/max-consecutive-ones-iii
https://leetcode.com/problems/max-consecutive-ones-iii/description/


Problem statement:
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

Examples:

Example 1:
    Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
    Output: 6
    Explanation: [1,1,1,0,0,1,1,1,1,1,1]
    Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

    Example 2:
    Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
    Output: 10
    Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
    Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Approach1:
//

// // Better approach: Sliding window.
// // Time: O(2N)
// // Space: O(1)
// int longestOnes(vector<int>& nums, int k) {

//     int ans = 0;

//     int N = nums.size();
//     int l=0;
//     int r=0;

//     while(l<N && r<N){

//         int cur=nums[r];

//         if(cur==0){
//             k--;
//         }

//         while(k<0){
//             if(nums[l]==0){
//                 k++;
//             }
//             l++;
//         }

//         int len = (r-l+1);
//         ans = max(ans,len);
//         r++;
//     }

//     return ans;
// }

//--------------------------------------------------------
// Approach2:

// Optimal approach: Sliding window optimized to single pass
// Time: O(N)
// Space: O(1)
int longestOnes(vector<int> &nums, int k)
{

    int ans = 0;

    int N = nums.size();
    int l = 0;
    int r = 0;

    while (l < N && r < N)
    {

        int cur = nums[r];

        if (cur == 0)
        {
            k--;
        }

        if (k < 0)
        { // removed the while loop to optimize
            if (nums[l] == 0)
            {
                k++;
            }
            l++;
        }

        if (k >= 0)
        { // Added extra check here for the optimization
            int len = (r - l + 1);
            ans = max(ans, len);
        }

        r++;
    }

    return ans;
}

int main()
{
    return 0;
}
