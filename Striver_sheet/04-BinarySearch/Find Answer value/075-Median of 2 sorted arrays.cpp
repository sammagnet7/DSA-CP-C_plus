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

using namespace std;

/*
Median of Two Sorted Arrays of different sizes

https://takeuforward.org/data-structure/median-of-two-sorted-arrays-of-different-sizes/
https://leetcode.com/problems/median-of-two-sorted-arrays/


Problem statement:
Given two sorted arrays arr1 and arr2 of size m and n respectively, return the median of the two sorted arrays. The median is defined as the middle value of a sorted list of numbers. In case the length of the list is even, the median is the average of the two middle elements.

The overall run time complexity should be O(log (m+n)).

Examples:

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.



INPUT::::::
2
1 3
2
1 2
3 4

OUTPUT::::::
1
3.5

 */
class Solution
{
public:
    // // ---------------------------------------------------------------------
    // // Brute force
    // // Time: O(m+n)
    // // Space: O(m+n)
    // double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    // {
    //     int m = nums1.size();
    //     int n = nums2.size();

    //     int N = m + n;

    //     vector<int> merged;

    //     int l = 0, r = 0;

    //     while (l < m && r < n)
    //     {
    //         if (nums1[l] <= nums2[r])
    //         {
    //             merged.push_back(nums1[l++]);
    //         }
    //         else
    //             merged.push_back(nums2[r++]);
    //     }

    //     while (l < m)
    //     {
    //         merged.push_back(nums1[l++]);
    //     }
    //     while (r < n)
    //     {
    //         merged.push_back(nums2[r++]);
    //     }

    //     int midL = N / 2 - 1;
    //     int midR = N / 2;

    //     double ans = -1;

    //     if (N % 2 == 0)
    //     { // Even so do avg
    //         ans = (double)(merged[midL] + merged[midR]) / 2;
    //     }
    //     else
    //         ans = merged[midR];

    //     return ans;
    // }

    // // ---------------------------------------------------------------------
    // // Better approach: Saves the extra space of merged array
    // // Time: O(m+n)
    // // Space: O(1)
    // double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    // {
    //     int m = nums1.size();
    //     int n = nums2.size();

    //     int N = m + n;

    //     int midL = N / 2 - 1;
    //     int midR = N / 2;

    //     int midLVal = -1;
    //     int midRVal = -1;

    //     double ans = -1;

    //     int l = 0, r = 0;

    //     int mergedIdx = 0;

    //     while (l < m && r < n)
    //     {
    //         int val = -1;
    //         if (nums1[l] <= nums2[r])
    //         {
    //             val = nums1[l++];
    //         }
    //         else
    //         {
    //             val = nums2[r++];
    //         }

    //         if (mergedIdx == midL)
    //             midLVal = val;
    //         else if (mergedIdx == midR)
    //             midRVal = val;

    //         mergedIdx++;
    //     }

    //     while (l < m)
    //     {
    //         int val = nums1[l++];
    //         if (mergedIdx == midL)
    //             midLVal = val;
    //         else if (mergedIdx == midR)
    //             midRVal = val;
    //         mergedIdx++;
    //     }
    //     while (r < n)
    //     {
    //         int val = nums2[r++];
    //         if (mergedIdx == midL)
    //             midLVal = val;
    //         else if (mergedIdx == midR)
    //             midRVal = val;

    //         mergedIdx++;
    //     }

    //     if (N % 2 == 0)
    //     { // Even so do avg
    //         ans = (double)(midLVal + midRVal) / 2;
    //     }
    //     else
    //         ans = midRVal;

    //     return ans;
    // }

    // ---------------------------------------------------------------------
    // Optimal approach
    // Time: O(Log min(m+n))
    // Space: O(1)
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        if (n < m)
            return findMedianSortedArrays(nums2, nums1); // Great Idea! to swap arrays recursively

        int N = m + n; // Length of merged array
        int mergedLeftHalf = ceil((double)N / 2);

        int l = 0; // starting of the range
        int r = m; // ending of the range

        while (l <= r)
        {
            int mid = l + (r - l) / 2; // (l+r)/2

            int nums1_L = mid;                  // nums1 size belongs to left half of merged array
            int nums2_L = mergedLeftHalf - mid; // nums2 size belongs to left half of merged array

            int l1 = nums1_L == 0 ? INT_MIN : nums1[nums1_L - 1];   // Handles the case when nums1 left part is empty
            int l2 = nums2_L == 0 ? INT_MIN : nums2[nums2_L - 1];   // Handles the case when nums2 left part is empty
            int r1 = nums1_L >= m ? INT_MAX : nums1[nums1_L];       // Handles the case when nums1 right part is empty
            int r2 = nums2_L >= n ? INT_MAX : nums2[nums2_L];       // Handles the case when nums1 right part is empty

            if ((l1 <= r2) && (l2 <= r1))
            {
                if (N % 2 == 0) // Even
                {
                    int medL = max(l1, l2); // Left median
                    int medR = min(r1, r2); // Right median

                    return (double)(medL + medR) / 2.0;
                }
                else // Odd
                    return max(l1, l2);
            }
            else if (l1 > r2)
            {
                r = mid - 1;
            }
            else if (l2 > r1)
            {
                l = mid + 1;
            }
        }

        return -1; // Unreachable
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        // int n;
        // cin >> n;
        // cin.ignore();

        string input1;
        string input2;
        getline(cin, input1);
        getline(cin, input2);

        vector<int> arr1;
        stringstream ss1(input1);
        int num1;
        while (ss1 >> num1)
        {
            arr1.push_back(num1);
        }

        vector<int> arr2;
        stringstream ss2(input2);
        int num2;
        while (ss2 >> num2)
        {
            arr2.push_back(num2);
        }

        Solution ob;

        cout << ob.findMedianSortedArrays(arr1, arr2);
        cout << endl;
    }
    return 0;
}