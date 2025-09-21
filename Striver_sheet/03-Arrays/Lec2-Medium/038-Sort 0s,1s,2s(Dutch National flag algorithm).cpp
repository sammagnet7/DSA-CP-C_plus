#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Sort an array of 0s, 1s and 2s
Dutch National flag algorithm

https://takeuforward.org/data-structure/sort-an-array-of-0s-1s-and-2s/
https://leetcode.com/problems/sort-colors/description/
https://www.naukri.com/code360/problems/631055?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: Given an array consisting of only 0s, 1s, and 2s. Write a program to in-place sort the array without using inbuilt sort functions. ( Expected: Single pass-O(N) and constant space)

Examples:
Input:
 nums = [2,0,2,1,1,0]
Output
: [0,0,1,1,2,2]

Input:
 nums = [2,0,1]
Output:
 [0,1,2]

Input:
 nums = [0]
Output:
 [0]


INPUT::::::
7
2 0 2 1 1 0
2 0 1
0
0 1 2 2 1 0
0 1 2 1 2 1 2
2 2 2 1 1 1 0
2 1 2 0 1 0

OUTPUT::::::

0 0 1 1 2 2
0 1 2
0
0 0 1 1 2 2
0 1 1 1 2 2 2
0 1 1 1 2 2 2
0 0 1 1 2 2

 */
class Solution
{
public:
    /**
     * Sort Colors (LeetCode 75) — Counting Approach
     * ---------------------------------------------
     * Problem:
     *  - Given an array containing only 0s, 1s, and 2s,
     *    sort them in-place so that same numbers are adjacent and in the order [0,1,2].
     *
     * Approach:
     *  - Count occurrences of 0, 1, and 2 in the array.
     *  - Overwrite the array: first all 0s, then all 1s, then all 2s.
     *
     * Time Complexity:
     *  - O(2N) = O(N)
     *    (one pass to count, one pass to overwrite).
     *
     * Space Complexity:
     *  - O(1) (constant extra space: just three counters).
     *
     * Stability:
     *  - Not stable (order of equal elements does not matter in this problem anyway).
     *
     * Notes:
     *  - Very simple and clean, but requires two passes over the array.
     *  - More optimal one-pass solution exists (Dutch National Flag algorithm).
     */

    void sortColors_count(vector<int> &arr)
    {
        // Counters for each color
        int c_0 = 0, c_1 = 0, c_2 = 0;

        // First pass: count the number of 0s, 1s, and 2s
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == 0)
                c_0++;
            if (arr[i] == 1)
                c_1++;
            if (arr[i] == 2)
                c_2++;
        }

        // Second pass: overwrite array with the counted values
        int i = 0;

        // Fill in 0s
        while (c_0--)
        {
            arr[i++] = 0;
        }

        // Fill in 1s
        while (c_1--)
        {
            arr[i++] = 1;
        }

        // Fill in 2s
        while (c_2--)
        {
            arr[i++] = 2;
        }
    }

    /**
     * Sort Colors (LeetCode 75) — Dutch National Flag Algorithm
     * ---------------------------------------------------------
     * Problem:
     *   - Given an array containing only 0s, 1s, and 2s, sort them in-place so that
     *     elements of the same color are adjacent and in the order [0,1,2].
     *
     * Algorithm / Intuition:
     *   - This is a direct application of the Dutch National Flag algorithm.
     *   - Maintain three pointers: low, mid, high.
     *   - Invariants:
     *       arr[0 .. low-1]    → contains only 0s
     *       arr[low .. mid-1]  → contains only 1s
     *       arr[mid .. high]   → unknown / unsorted part
     *       arr[high+1 .. N-1] → contains only 2s
     *
     *   - Process continues until mid > high (no unsorted elements left).
     *
     *   Rules:
     *   1. If arr[mid] == 0:
     *        swap(arr[low], arr[mid]); increment both low and mid
     *        → ensures the left side grows with 0.
     *   2. If arr[mid] == 1:
     *        just increment mid
     *        → element already in correct "middle" section.
     *   3. If arr[mid] == 2:
     *        swap(arr[mid], arr[high]); decrement high
     *        → places 2 at the right section, but do NOT increment mid yet
     *          since the new element at mid could be 0,1,2 (must re-check).
     *
     * Time Complexity:
     *   - O(N): each element is processed at most once.
     *
     * Space Complexity:
     *   - O(1): in-place, only a few extra pointers.
     *
     * Stability:
     *   - Not stable (relative order of equal elements may change),
     *     but stability is not required for this problem.
     */
    void sortColors_dutch1(vector<int> &arr)
    {
        int N = arr.size();

        int low = 0;      // boundary for 0s → [0 .. low-1] are all 0
        int mid = 0;      // current index being inspected
        int high = N - 1; // boundary for 2s → [high+1 .. N-1] are all 2

        // Process elements until mid crosses high
        while (mid <= high)
        {
            if (arr[mid] == 0)
            {
                // Place 0 in the left section
                swap(arr[low++], arr[mid++]);
            }
            else if (arr[mid] == 1)
            {
                // 1 is already in the middle section → just move mid
                mid++;
            }
            else // arr[mid] == 2
            {
                // Place 2 in the right section
                // Do not increment mid yet, must re-check swapped element
                swap(arr[mid], arr[high--]);
            }
        }
    }

    /**
     * Sort Colors (LeetCode 75) — Dutch National Flag (Alternate Style)
     * -----------------------------------------------------------------
     * Problem:
     *   - Sort an array containing only {0,1,2} in-place so that
     *     elements are grouped as [0s, then 1s, then 2s].
     *
     * Algorithm / Intuition:
     *   - This version also uses the Dutch National Flag algorithm
     *     but with a slightly different pointer style:
     *
     *   Pointers meaning:
     *     zero = last position of 0 in the array (initially -1, none placed yet)
     *     one  = current index being processed
     *     two  = first position of 2 beyond the array (initially n)
     *
     *   Invariants:
     *     [0 .. zero]      → all 0s
     *     [zero+1 .. one-1] → all 1s
     *     [one .. two-1]    → unprocessed region
     *     [two .. n-1]      → all 2s
     *
     *   Process:
     *     - While one < two:
     *         * If nums[one] == 1 → correct middle region → just move one++
     *         * If nums[one] == 2 → move 2 into right region:
     *                               swap(nums[one], nums[--two]), do not increment one
     *                               (since new element at "one" must be checked)
     *         * If nums[one] == 0 → move 0 into left region:
     *                               swap(nums[one], nums[++zero]), then one++
     *
     * Time Complexity:
     *   - O(N): Each element is examined at most once.
     *
     * Space Complexity:
     *   - O(1): In-place, only three integer pointers.
     *
     * Stability:
     *   - Not stable (relative order of equal elements may change).
     *
     * Difference from "low-mid-high" style:
     *   - This variant starts zero at -1 and two at n, which simplifies conditions.
     *   - Shorter and slightly more elegant, often seen in competitive programming.
     */
    void sortColors_dutch2(vector<int> &nums)
    {
        int n = nums.size();

        int zero = -1; // boundary: last placed 0
        int one = 0;   // current index to check
        int two = n;   // boundary: first position of 2 from the end

        while (one < two)
        {
            if (nums[one] == 1)
            {
                // Already in the correct middle section → move on
                one++;
            }
            else if (nums[one] == 2)
            {
                // Put 2 into the right section
                // Decrement 'two' first, then swap (since [two..n-1] is reserved for 2s)
                swap(nums[one], nums[--two]);
                // Do not increment 'one', because swapped element may be 0/1/2
            }
            else
            { // nums[one] == 0
                // Put 0 into the left section
                // Increment 'zero' first, then swap
                swap(nums[one], nums[++zero]);
                one++;
            }
        }
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

        ob.sortColors_count(arr);
        ob.sortColors_dutch1(arr);
        ob.sortColors_dutch2(arr);

        for (int e : arr)
        {
            cout << e << " ";
        }

        cout << endl;
    }
}