#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Search Element in a Rotated Sorted Array w/ or w/o duplicates

w/o duplicates:
https://takeuforward.org/data-structure/search-element-in-a-rotated-sorted-array/
https://leetcode.com/problems/search-in-rotated-sorted-array/description/

w/ duplicates:
https://takeuforward.org/arrays/search-element-in-rotated-sorted-array-ii/
https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/

Problem Statement: Given an integer array arr of size N, sorted in ascending order (with distinct values) and a target value k. Now the array is rotated at some pivot point unknown to you. Find the index at which k is present and if k is not present return -1.

Note:
There is an integer array arr sorted in ascending order (with distinct values).
Prior to being passed to your function, arr is possibly rotated at an unknown pivot index k (1 <= k < arr.length) such that the resulting array is [arr[k], arr[k+1], ..., arr[n-1], arr[0], arr[1], ..., arr[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array arr after the possible rotation and an integer target, return the index of target if it is in arr, or -1 if it is not in arr.
You must write an algorithm with O(log n) runtime complexity.

Examples:
w/o duplicate:

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1

w/ duplicate:
Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:
Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

INPUT::::::
9
0
4 5 6 7 0 1 2
3
4 5 6 7 0 1 2
0
1
3
2 3
1
3 1
0
2 5 6 0 0 1 2
3
2 5 6 0 0 1 2
0
1 0 1 1 1
2
1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1 1 1 1

OUTPUT::::::
4
-1
-1
1
1
3
-1
1
13


 */
class Solution
{
public:
    // Optimal approach
    //
    // Approach w/o duplicates: 
    // As the array is rotated, whichever index we take,
    // either side of it is sorted and the other side may not be sorted
    // Use Binary search on the sorted side.
    // If element is not found then 
    // in the other unsorted side, again try to find sorted half and Binary search on it.
    // Likewise continue
    //
    // Approach w/ duplicates:
    // Same approach + There can arise an edge case: arr[l]==arr[mid]==arr[r] != target
    // For this edger case We will eliminate the eliments from both edges making the array smaller
    // until getting out of this case.
    // Beacause anyway these elements are to be eliminated
    // Lines added with annotation [*Duplicate handle]
    //
    // Time: O(Log N) if array is free from duplicates
    //       O(N)     if array is full of duplicates
    // Space: O(1)
    int search(vector<int> &arr, int target)
    {
        int N = arr.size();
        int l = 0, r = N - 1;
        int res = -1;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                return mid;
            }

            // if true means left half is sorted and right half may not be sorted.
            bool dirL = arr[l] <= arr[mid];     // left side is sorted
            bool dirR = arr[mid] <= arr[r];     // right side is sorted
            bool edgeCase = (arr[l] == arr[mid]) && (arr[mid]==arr[r]);     //[*Duplicate handle]   // None of the sides are sorted

            if(edgeCase){   //[*Duplicate handle]
                // No BS
            }
            else if (dirL)
            { //  make BS on the left sorted side
                if (arr[l] <= target && target <= arr[mid])
                    res = doBinarySearch(arr, l, mid - 1, target);
            }
            else if(dirR)
            { //  make BS on the right sorted side
                if (arr[mid] <= target && target <= arr[r])
                    res = doBinarySearch(arr, mid + 1, r, target);
            }

            if (res != -1)
                return res; // already target is found
            else
            {
                if(edgeCase){   //[*Duplicate handle]
                    l++;
                    r--;
                }
                else if (dirL)
                { // target not found in sorted side, Focus on the other side
                    l = mid + 1;
                }
                else
                { // target not found in sorted side, Focus on the other side
                    r = mid - 1;
                }
            }
        }
        return res;
    }

    // O(Log N)
    int doBinarySearch(vector<int> &arr, int start, int end, int target)
    {

        int l = start;
        int r = end;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                return mid;
            }
            else if (target < arr[mid])
            {
                r = mid - 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
        }
        return -1;
    }

    // Same approach with diff code style
    // Time: O(Log N)
    // int search(vector<int> &arr, int k)
    // {
    //     int n = arr.size();
    //     int low = 0, high = n - 1;
    //     while (low <= high)
    //     {
    //         int mid = (low + high) / 2;

    //         // if mid points the target
    //         if (arr[mid] == k)
    //             return mid;

    //         // if left part is sorted:
    //         if (arr[low] <= arr[mid])
    //         {
    //             if (arr[low] <= k && k <= arr[mid])
    //             {
    //                 // element exists:
    //                 high = mid - 1;
    //             }
    //             else
    //             {
    //                 // element does not exist:
    //                 low = mid + 1;
    //             }
    //         }
    //         else
    //         { // if right part is sorted:
    //             if (arr[mid] <= k && k <= arr[high])
    //             {
    //                 // element exists:
    //                 low = mid + 1;
    //             }
    //             else
    //             {
    //                 // element does not exist:
    //                 high = mid - 1;
    //             }
    //         }
    //     }
    //     return -1;
    // }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int target;
        cin >> target;
        cin.ignore();

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

        cout << ob.search(arr, target);
        cout << endl;
    }
    return 0;
}