#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
1. Title: Find Minimum in Rotated Sorted Array

Links:
https://takeuforward.org/data-structure/minimum-in-rotated-sorted-array/
https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/


Problem Statement: Given an integer array arr of size N, sorted in ascending order (with distinct values). Now the array is rotated between 1 to N times which is unknown. Find the minimum element in the array.

Note:
Given array consists of unique elements.

Examples:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times.

INPUT::::::
3
3 4 5 1 2
4 5 6 7 0 1 2
11 13 15 17

OUTPUT::::::
1
0
11

-------------------------------------------------------------------------------
2. Title: Find Minimum in Rotated Sorted Array II


Links:
https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/


Problem statement:
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

[4,5,6,7,0,1,4] if it was rotated 4 times.
[0,1,4,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

You must decrease the overall operation steps as much as possible.



Example 1:
    Input: nums = [1,3,5]
    Output: 1

Example 2:
    Input: nums = [2,2,2,0,1]
    Output: 0


Constraints:
    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    nums is sorted and rotated between 1 and n times.


Follow up: This problem is similar to Find Minimum in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?




INPUT::::::


OUTPUT::::::



 */

//-------------------------------------------------------------------------------
// 1. Title: Find Minimum in Rotated Sorted Array
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * Approach: Binary Search (Sorted-Half Elimination)
 * ============================================================================
 * Intuition:
 * A rotated sorted array is always composed of two perfectly sorted sub-arrays.
 * By checking the middle element, we can always determine which half of our
 * current search space is perfectly sorted. The minimum element of any perfectly
 * sorted half is simply its leftmost element. We record that minimum, and then
 * throw that entire half away to search the other (unsorted) half.
 *
 * Approach:
 * 1. Maintain a global `minVal` tracking the smallest number seen so far.
 * 2. At each step, if the entire current window `[l, r]` is already sorted,
 *    the minimum is strictly at `l`. We record it and immediately break.
 * 3. Otherwise, find `mid`. Check if the left half `[l, mid]` is sorted.
 *    - If YES: The minimum of the left half is `nums[l]`. Record it, then
 *      discard the left half (`l = mid + 1`).
 *    - If NO: The right half `[mid, r]` must be sorted. The minimum of the
 *      right half is `nums[mid]`. Record it, then discard the right half
 *      (`r = mid - 1`).
 * ============================================================================
 * Complexity:
 * - Time: O(log N). We eliminate exactly half of the search space on every
 *   iteration, leading to logarithmic time complexity.
 * - Space: O(1). We only use a few primitive integer variables for pointers.
 * ============================================================================
 */
class Solution
{
public:
    int findMin(vector<int> &nums)
    {

        int n = nums.size();
        int minVal = INT_MAX; // Global tracker for the minimum value

        int l = 0;
        int r = n - 1;

        while (l <= r)
        {

            // EARLY EXIT (O(1) Check):
            // If the element at 'l' is <= the element at 'r', the current
            // sub-array is completely sorted. There is no rotation here.
            // The smallest element must be at the very beginning ('l').
            if (nums[l] < nums[r])
            {
                minVal = min(minVal, nums[l]);
                break; // Stop searching entirely to save CPU cycles
            }

            // Calculate mid safely to prevent integer overflow
            int mid = l + (r - l) / 2;

            // CONDITION 1: The Left Half is perfectly sorted.
            if (nums[l] <= nums[mid])
            {
                // The smallest value in this left half is guaranteed to be nums[l].
                minVal = min(minVal, nums[l]);

                // Since we've processed the left half, the absolute minimum
                // must be hiding in the unsorted right half.
                l = mid + 1;
            }
            // CONDITION 2: The Right Half is perfectly sorted.
            else
            {
                // The smallest value in this right half is guaranteed to be nums[mid].
                minVal = min(minVal, nums[mid]);

                // Since we've processed the right half, the absolute minimum
                // must be hiding in the unsorted left half.
                r = mid - 1;
            }
        }

        return minVal;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Find Minimum in Rotated Sorted Array II
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * Approach: Optimized Binary Search with Duplicate Resolution
 * ============================================================================
 * Intuition:
 * This algorithm finds the minimum element in a rotated sorted array that
 * contains duplicates. It combines three powerful optimizations:
 * 1. Global Minimum Tracking: We always record the middle element.
 * 2. Duplicate Patch: If the boundaries and mid are identical, we shrink
 *    the window to resolve the mathematical ambiguity.
 * 3. Early Exit: If the current window is perfectly sorted (no rotation),
 *    the minimum is simply the leftmost element.
 * ============================================================================
 * Complexity:
 * - Time: O(log N) average. O(N) worst-case (if the array is entirely
 *   identical duplicates, e.g., [2,2,2,2], forcing O(N) window shrinking).
 * - Space: O(1). No extra memory allocated.
 * ============================================================================
 */
class Solution
{
public:
    int findMin(vector<int> &nums)
    {

        int n = nums.size();
        int minVal = INT_MAX;

        int l = 0;
        int r = n - 1;

        while (l <= r)
        {

            // Safe mid calculation to prevent integer overflow
            int mid = l + (r - l) / 2;

            // Record mid immediately. This acts as a protective mechanism
            // before we potentially throw away boundaries in the duplicate patch.
            minVal = min(minVal, nums[mid]);

            // ================================================================
            // THE PATCH: Resolve Duplicate Ambiguity
            // If the boundaries and mid are identical, we cannot determine
            // which half is sorted. Shrink the window to clear the blind spot.
            // ================================================================
            if (nums[l] == nums[mid] && nums[mid] == nums[r])
            {
                ++l;
                --r;
                continue;
            }

            // ================================================================
            // EARLY EXIT: Fully Sorted Segment
            // If the sub-array has no rotation, the minimum is at 'l'.
            // ================================================================
            if (nums[l] < nums[r])
            {
                minVal = min(minVal, nums[l]);
                break;
            }
            // ================================================================
            // CONDITION 1: The Left Sub-Array is Perfectly Sorted
            // ================================================================
            else if (nums[l] <= nums[mid])
            {
                minVal = min(minVal, nums[l]);
                l = mid + 1; // Discard left, search right
            }
            // ================================================================
            // CONDITION 2: The Right Sub-Array is Perfectly Sorted
            // ================================================================
            else
            {
                minVal = min(minVal, nums[mid]);
                r = mid - 1; // Discard right, search left
            }
        }

        return minVal;
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

        cout << ob.findMin(arr);
        cout << endl;
    }
    return 0;
}