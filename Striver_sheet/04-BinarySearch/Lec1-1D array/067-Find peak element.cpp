#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Peak element in Array

https://takeuforward.org/data-structure/peak-element-in-array/
https://leetcode.com/problems/find-peak-element/description/

Problem statement:
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.
You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

Examples:

Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

INPUT::::::
6
1 2 3 1
1 2 1 3 5 6 4
1
2 1
1 2
3 4 3 2 1

OUTPUT::::::
2
5
0
0
1
1

 */
class Solution
{
public:
    // Approach: optimal
    // time: O(Log N)
    // Space: O(1)
    int findPeakElement(vector<int> &arr)
    {
        int N = arr.size();

        // if (arr[0] != arr[1])
        //     return arr[0];
        // if (arr[N - 1] != arr[N - 2])
        //     return arr[N - 1];
        // int l=1, r=N-2;

        if (N == 1)
            return 0; // Handle edge case

        int l = 0, r = N - 1;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (mid == 0)
            { // edge case
                if (arr[mid] > arr[mid + 1])
                    return mid;
                else
                    l = mid + 1;
            }
            else if (mid == N - 1)
            { // edge case
                if (arr[mid - 1] < arr[mid])
                    return mid;
                else
                    r = mid - 1;
            }
            else if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
                return mid; // Bingo
            else if (arr[mid] < arr[mid + 1])
                l = mid + 1; // go right
            else if (arr[mid - 1] > arr[mid])
                r = mid - 1; // go left
        }
        return -1;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        // int target;
        // cin >> target;
        // cin.ignore();

        string input;
        getline(cin, input);

        vector<int> arr;
        stringstream ss(input);
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.findPeakElement(arr);
        cout << endl;
    }
    return 0;
}