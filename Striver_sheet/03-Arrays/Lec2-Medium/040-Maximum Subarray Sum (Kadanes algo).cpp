#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Kadane's Algorithm : Maximum Subarray Sum in an Array

https://takeuforward.org/data-structure/kadanes-algorithm-maximum-subarray-sum-in-an-array/
https://leetcode.com/problems/maximum-subarray/description/
https://www.naukri.com/code360/problems/630526?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: Given an integer array nums, find the subarray with the largest sum, and return its sum.

Note: A subarray is a contiguous segment of an array. In other words, a subarray can be formed by removing 0 or more integers from the beginning and 0 or more integers from the end of an array.
Find the sum of the subarray (including empty subarray) having maximum sum among all subarrays.
The sum of an empty subarray is 0.

Examples:

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Example 2:
Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.

Example 3:
Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.


INPUT::::::
6
-2,1,-3,4,-1,2,1,-5,4
1
5,4,-1,7,8
1, 2, 7, -4, 3, 2, -10, 9, 1
10 20 -30 40 -50 60
-3 -5 -6

OUTPUT::::::

6
1
23
11
60
-3


Follow up: ??
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
 */
class Solution
{
public:
    /**
     * Maximum Subarray Sum (Kadane's Algorithm with Indices)
     * ------------------------------------------------------
     * Problem:
     *   - Find the contiguous subarray with the largest sum.
     *   - Also keep track of the indices of the maximum sum subarray.
     *
     * Algorithm / Intuition:
     *   - Maintain a running sum of the current subarray.
     *   - If sum becomes negative, reset it to 0 (since a negative prefix
     *     would only reduce future subarray sums).
     *   - Update the maximum sum whenever a better subarray is found,
     *     recording its start and end indices.
     *
     * Key Points:
     *   - Left pointer `l` = potential start of current subarray.
     *   - Right pointer `r` = current element being processed.
     *   - If sum < 0 → reset sum = 0 and move `l` to `r` (new start).
     *
     * Complexity:
     *   - Time: O(N)  (each element processed once).
     *   - Space: O(1) (only variables, no extra arrays).
     *
     * Variants:
     *   - If empty subarray is allowed → initialize maxSum = 0.
     *   - Otherwise (classic Kadane) → initialize maxSum = INT_MIN.
     */
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();

        int l = 0, r = 0;     // window boundaries
        int sum = 0;          // running sum
        int maxSum = INT_MIN; // best sum found so far; Take as 0 if given: sum of an empty subarray is 0
        int maxSumArrayStartIdx = -1;
        int maxSumArrayEndIdx = -1;

        // Expand window with right pointer
        while (r < n)
        {
            sum += nums[r];

            // If new sum is better → update best result
            if (sum > maxSum)
            {
                maxSum = sum;
                maxSumArrayStartIdx = l;
                maxSumArrayEndIdx = r;
            }

            r++; // move right pointer

            // If running sum becomes negative, reset window
            if (sum < 0)
            {
                sum = 0;
                l = r; // next element becomes new start
            }
        }

        // Print subarray indices (optional for debugging)
        cout << maxSumArrayStartIdx << " " << maxSumArrayEndIdx << " ";

        return maxSum;
    }

    /**
     * Kadane's Algorithm (Maximum Subarray Sum)
     * -----------------------------------------
     * Intuition:
     *   - If the running subarray sum becomes smaller than the current element,
     *     it's better to start a new subarray from the current element.
     *   - Keep updating the maximum sum found so far.
     *
     * Approach:
     *   - Maintain `sum` = running sum of the current subarray.
     *   - At each step:
     *       sum = max(arr[i], sum + arr[i])
     *       → either extend previous subarray or start fresh at arr[i].
     *   - Keep updating `maxSum` with the maximum value of `sum`.
     *
     * Initialization:
     *   - maxSum = INT_MIN if empty subarray is NOT allowed.
     *   - maxSum = 0 if the problem defines empty subarray sum = 0.
     *
     * Time Complexity:  O(N)  [single pass over array]
     * Space Complexity: O(1)  [only a few variables]
     */
    int maxSubArray(vector<int> &arr)
    {
        long long maxSum = INT_MIN; // stores maximum subarray sum found so far
        long long sum = 0;          // running sum of current subarray

        for (int i = 0; i < arr.size(); i++)
        {
            sum += arr[i];                     // extend current subarray
            sum = max(sum, (long long)arr[i]); // or start a new subarray from arr[i]
            maxSum = max(maxSum, sum);         // update global maximum
        }

        return maxSum;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
        // int k;
        // cin >> k;
        // cin.ignore();

        string input;
        getline(cin, input);
        stringstream ss(input);

        vector<int> arr;
        int num;
        while (ss >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.maxSubArray(arr);

        cout << endl;
    }
}