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
    // Kadane's algorithm
    // Approach: The intuition of the algorithm is not to consider the subarray as a part of the answer if its sum is less than 0. A subarray with a sum less than 0 will always reduce our answer and so this type of subarray cannot be a part of the subarray with maximum sum.
    // Time: O(N)
    // Space: O(1)
    int maxSubArray(vector<int> &arr)
    {
        int sidx_temp = 0;
        int sidx = -1, eidx = -1; // Keeping subarray indices
        int sum = 0;
        int maxS = INT_MIN; // Take as 0 if given: sum of an empty subarray is 0
                            // Take INT_MIN otherwise

        for (int i = 0; i < arr.size(); i++)
        {
            if (sum == 0)
                sidx_temp = i;

            sum += arr[i];

            if (sum > maxS)
            {
                maxS = sum;
                sidx = sidx_temp;
                eidx = i;
            }

            if (sum < 0)
                sum = 0;
        }
        // cout << sidx << " " << eidx << " "; // Print Subarray indices
        return maxS;
    }

    // Approach: Easier: For each element if current element is greater than previous cumulative sum, then reset sum with current element.
    // Time: O(N)
    // Space: O(1)
    // int maxSubArray(vector<int> &arr)
    // {
    //     // Write your code here.
    //     long long maxSum = INT_MIN; // Take as 0 if given: sum of an empty subarray is 0
    //                                 // Take INT_MIN otherwise
    //     long long sum = 0;

    //     for (int i = 0; i < arr.size(); i++)
    //     {
    //         sum += arr[i];
    //         sum = max(sum, (long long)arr[i]);
    //         maxSum = max(maxSum, sum);
    //     }

    //     return maxSum;
    // }
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