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

1. Title: Single Number I:

Links:
https://www.youtube.com/watch?v=sFBCAl8yBfE
https://leetcode.com/problems/single-number/description/


Problem statement:
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples:

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

2. Title: Single Number II:

Links:
https://takeuforward.org/bit-manipulation/single-number-ii
https://www.youtube.com/watch?v=5Bb2nqA40JY&t=77s (Optimal approach is discussed in vedio only)
https://leetcode.com/problems/single-number-ii/description/

Problem statement:
Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Single Number III:

Links:
https://www.youtube.com/watch?v=UA5JnV1J2sI
https://leetcode.com/problems/single-number-iii/description/

Problem statement:
Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Example 1:
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Example 2:
Input: nums = [-1,0]
Output: [-1,0]

Example 3:
Input: nums = [0,1]
Output: [1,0]


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ----------------------------------------------------------------
    // 1. Title: Single Number I:

    // // Optimal approach: Do Xor of all the numbers.
    // // Duplicates will be cancelled out
    // // Final XOR value will give the left out int
    // //
    // // Time: O(N) where N is length of nums array
    // // Space: O(1)
    // int singleNumberONE(vector<int> &nums)
    // {

    //     int xori = 0;

    //     for (int e : nums)
    //     {
    //         xori ^= e;
    //     }

    //     return xori;
    // }

    // // ------------------------------------------------------------------------------
    // // Title: Single Number II : Approach 1

    // // Primary approach: If we count 0/1 for each bits of all the numbers
    // // if count of bit value==1 divides by 3 then the lone number's digit must be the opposit i.e. 0
    // //
    // // Time: O(N * 32)
    // // SPace: O(1)
    // int singleNumberTWO(vector<int> &nums)
    // {

    //     int ans = 0;

    //     // O(32)
    //     for (int i = 0; i < 32; i++)
    //     { // iterating over bits of a int from 0 to 31

    //         int ansIthBit;
    //         int ithSetBitsCount = 0;

    //         // O(N)
    //         for (int j = 0; j < nums.size(); j++)
    //         { // iterating over given numbers

    //             int cur = nums[j];
    //             int ithBit = cur & (1 << i);

    //             if (ithBit)
    //                 ithSetBitsCount++;
    //         }

    //         if ((ithSetBitsCount % 3) == 0)
    //             ansIthBit = 0; // because count of 1s at ith bit position is in 3's multiple.
    //                            // So the lone number's ith bit is not 1
    //         else
    //             ansIthBit = 1;

    //         ans += (ansIthBit * 1 << i);
    //     }

    //     return ans;
    // }

    // ------------------------------------
    // Title: Single Number II : Approach 2

    // // Better approach: Sort the vector and then count occurences of numbers
    // // Here as elements appeares 3 times,
    // // while counting we jump 3 elements at a time for optimizing time
    // //
    // // Time: O(N Log N + N/3)
    // // SPace: O(1)
    // int singleNumberTWO(vector<int> &nums)
    // {

    //     sort(nums.begin(), nums.end());

    //     int N = nums.size();

    //     for (int i = 0; i < N - 1; i += 3)
    //     { // O(N/3)
    //         if (nums[i] != nums[i + 1])
    //             return nums[i];
    //     }

    //     return nums[N - 1];
    // }

    // ------------------------------------
    // Title: Single Number II : Approach 3

    // Optimal approach:
    // Time:
    // Space: 
    int singleNumberTWO(vector<int> &nums)
    {
        
    }

    // ------------------------------------------------------------------------------
    // 3. Title: Single Number III

    // Optimal approach: Based on a differentiating bit, segregate all the numbers between two buckets
    // The bucket specific xor will return each numbers
    // Time: O(2N)
    // Space: O(1)
    vector<int> singleNumberTHREE(vector<int> &nums)
    {

        long aXorb = 0;

        for (int i = 0; i < nums.size(); i++)
        { // O(N)
            aXorb ^= nums[i];
        }

        // Now from aXorb I have to find the right most set bit
        // i.e. the bit where a and b differs
        // for that

        // 1. we first unset the right most set bit
        int rightSetBitUnset = aXorb & (aXorb - 1);

        // 2. do xor with the original so that
        // we can get a number like : ...000100..
        // i.e. only the right most diffrentiating bit as set
        int diffBit = aXorb ^ rightSetBitUnset;

        // 3. If we perform AND of each numbers with `diffBit`
        // we can segregate nubers between 2 buckets based upon the diff bit
        int bucketOne = 0;
        int bucketTwo = 0;

        for (int i = 0; i < nums.size(); i++)
        { // O(N)

            int cur = nums[i];

            if (cur & diffBit)
                bucketOne ^= cur; // store in bucket doing xor
            else
                bucketTwo ^= cur;
        }

        // Finally each bucket will represent the distinct lone numers
        return {bucketOne, bucketTwo};
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
