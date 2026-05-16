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

/**
 * ============================================================================
 * 1. Title: Search in Rotated Sorted Array without Duplicate
 * ============================================================================
 * Intuition:
 * We use binary search to locate the target. Because the array is rotated,
 * we must first determine which half of our current window is perfectly sorted.
 * Once we know the sorted half, we can check if the target falls within its
 * minimum and maximum boundaries. If it does, we search that half. If it
 * doesn't, the target must be hiding in the other (unsorted) half.
 *
 * Optimization:
 * If the current search space [l, r] is perfectly sorted (nums[l] < nums[r]),
 * the rotation is no longer a factor. We can completely bypass the boundary
 * logic and fall back to a standard, ultra-fast binary search.
 * ============================================================================
 * Complexity:
 * - Time: O(log N). We discard exactly half the search space per iteration.
 * - Space: O(1). Only a few primitive integer pointers are used.
 * ============================================================================
 */
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {

        int n = nums.size();
        int l = 0;
        int r = n - 1;

        while (l <= r)
        {

            // Calculate mid safely to prevent integer overflow
            int mid = l + (r - l) / 2;

            // ================================================================
            // TARGET FOUND
            // ================================================================
            if (nums[mid] == target)
            {
                return mid;
            }

            // ================================================================
            // OPTIMIZATION: Fully Sorted Segment
            // NOTE: This block is mathematically redundant! If the array is
            // perfectly sorted, `nums[l] <= nums[mid]` will inherently trigger
            // the next block anyway, which routes the pointers to the exact
            // same destination. Deleting this block saves an `if` evaluation.
            // ================================================================
            if (nums[l] < nums[r])
            {
                if (target < nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            // ================================================================
            // CONDITION 1: The Left Sub-Array is Perfectly Sorted
            // ================================================================
            else if (nums[l] <= nums[mid])
            {

                // BOUNDARY CHECK: Is the target strictly within this sorted half?
                // Note: `target <= nums[mid]` is safe, but technically `target < nums[mid]`
                // is sufficient since we already checked `nums[mid] == target` above.
                if (nums[l] <= target && target <= nums[mid])
                {
                    r = mid - 1; // It is here. Discard the right half.
                }
                else
                {
                    l = mid + 1; // It is not here. Discard the left half.
                }
            }
            // ================================================================
            // CONDITION 2: The Right Sub-Array is Perfectly Sorted
            // ================================================================
            else
            {

                // BOUNDARY CHECK: Is the target strictly within this sorted half?
                if (nums[mid] <= target && target <= nums[r])
                {
                    l = mid + 1; // It is here. Discard the left half.
                }
                else
                {
                    r = mid - 1; // It is not here. Discard the right half.
                }
            }
        }

        // Exhausted the search space; the target does not exist.
        return -1;
    }
};

/**
 * ============================================================================
 * 2. Title: Search in Rotated Sorted Array with Duplicates
 * ============================================================================
 * Intuition:
 * This is a variation of the Rotated Sorted Array search where duplicates are
 * allowed. Duplicates introduce a critical flaw: if the left, middle, and
 * right pointers all point to the exact same value, it becomes mathematically
 * impossible to determine which half of the array is perfectly sorted.
 *
 * Approach:
 * 1. Calculate `mid` and check if it's the target.
 * 2. THE PATCH: If we hit the duplicate blind spot (nums[l] == nums[mid] == nums[r]),
 *    we know `nums[mid]` is NOT the target. Thus, the elements at `l` and `r`
 *    are also safely NOT the target. We simply shrink the window inwards
 *    (`++l`, `--r`) to clear the ambiguity and recalculate `mid`.
 * 3. Once ambiguity is cleared, check if the segment is fully sorted. If so,
 *    do a standard binary search.
 * 4. Otherwise, determine which half is perfectly sorted and do a strict
 *    boundary check to see if the target lies inside it. Discard halves accordingly.
 * ============================================================================
 * Complexity:
 * - Time: O(log N) on average. However, in the worst-case scenario where the
 *   array is densely packed with duplicates (e.g., [1, 1, 1, 1, 1] searching for 2),
 *   the pointers only shrink by 1 each iteration, degrading to O(N).
 * - Space: O(1). Only primitive integer pointers are allocated.
 * ============================================================================
 */
class Solution
{
public:
    bool search(vector<int> &nums, int target)
    {

        int n = nums.size();
        int l = 0;
        int r = n - 1;

        while (l <= r)
        {

            // Prevent integer overflow during mid calculation
            int mid = l + (r - l) / 2;

            // Target successfully found
            if (nums[mid] == target)
            {
                return true;
            }

            // ================================================================
            // THE PATCH: Resolve Duplicate Ambiguity
            // If boundaries and mid are identical, we cannot guarantee which
            // half is sorted. Since nums[mid] != target, we can safely discard
            // the boundaries and shrink the search space.
            // ================================================================
            if (nums[l] == nums[mid] && nums[mid] == nums[r])
            {
                ++l;
                --r;
                continue; // Recalculate mid with the new, narrower window
            }

            // ================================================================
            // OPTIMIZATION: Fully Sorted Segment
            // If the current window has no rotation, use standard Binary Search.
            // BUT REDUNDANT
            // ================================================================
            if (nums[l] < nums[r])
            {
                if (target < nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            // ================================================================
            // CONDITION 1: The Left Sub-Array is Perfectly Sorted
            // ================================================================
            else if (nums[l] <= nums[mid])
            {

                // BOUNDARY CHECK: Is the target strictly within this sorted half?
                if (nums[l] <= target && target < nums[mid])
                {
                    r = mid - 1; // Target is here. Discard the right half.
                }
                else
                {
                    l = mid + 1; // Target is missing. Discard the left half.
                }
            }
            // ================================================================
            // CONDITION 2: The Right Sub-Array is Perfectly Sorted
            // ================================================================
            else
            {

                // BOUNDARY CHECK: Is the target strictly within this sorted half?
                if (nums[mid] < target && target <= nums[r])
                {
                    l = mid + 1; // Target is here. Discard the left half.
                }
                else
                {
                    r = mid - 1; // Target is missing. Discard the right half.
                }
            }
        }

        // Exhausted the search space; the target does not exist.
        return false;
    }
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