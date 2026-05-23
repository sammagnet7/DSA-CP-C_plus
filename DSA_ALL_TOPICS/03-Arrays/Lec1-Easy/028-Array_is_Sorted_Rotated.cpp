#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
Title: Check if Array Is Sorted and Rotated

Links:
http://takeuforward.org/data-structure/check-if-an-array-is-sorted/
https://www.naukri.com/code360/problems/ninja-and-the-sorted-check_6581957?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description/


Problem statement:
Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.

There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.

Examples:
    Example 1:
    Input: nums = [3,4,5,1,2]
    Output: true
    Explanation: [1,2,3,4,5] is the original sorted array.
    You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].

    Example 2:
    Input: nums = [2,1,3,4]
    Output: false
    Explanation: There is no sorted array once rotated that can make nums.

    Example 3:
    Input: nums = [1,2,3]
    Output: true
    Explanation: [1,2,3] is the original sorted array.
    You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.


Constraints:
    1 <= nums.length <= 100
    1 <= nums[i] <= 100


INPUT::::::
6
3 4 5 1 2
2 1 3 4
1 2 3
0 0 0 1
4 5 4 4 4
6 10 6

OUTPUT::::::


Is Array Sorted? Ans: true
Is Array Sorted? Ans: false
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true

 */

/**
 * ============================================================================
 * 1. Title: Check if Array Is Sorted and Rotated
 * ============================================================================
 */


// ============================================================================
// APPROACH 1: The "Drop Count" Method (Industry Standard) [RECOMMENDED]
// ============================================================================
// Intuition:
// A perfectly sorted array that is rotated will have AT MOST one point where
// a number is strictly greater than the next number (the "drop" or "seam").
// If we check the array circularly (comparing the last element back to the
// first), any count greater than 1 means the array is fundamentally broken.
//
// Time: O(N) | Space: O(1)
// ============================================================================
class Solution
{
public:
    bool check(vector<int> &nums)
    {
        int n = nums.size();
        int dropCount = 0;

        for (int i = 0; i < n; ++i)
        {

            // The modulo operator (i + 1) % n safely handles the wrap-around
            // check from the last index back to index 0.
            if (nums[i] > nums[(i + 1) % n])
            {
                dropCount++;
            }
        }

        return dropCount <= 1;
    }
};

// ============================================================================
// APPROACH 2: Prefix-Stripping Pivot Search (The User's Approach)
// ============================================================================
// Intuition:
// 1. Strip away identical elements at the start and end of the array. This
//    guarantees that if duplicate minimums exist, we won't accidentally
//    target a "false pivot".
// 2. Scan the remaining elements to find the exact index of the true minimum.
// 3. Do a circular validation starting from that true minimum to ensure
//    every subsequent number is strictly increasing or equal.
//
// Time: O(N) | Space: O(1)
// ============================================================================
class Solution
{
public:
    bool check(vector<int> &nums)
    {
        int n = nums.size();

        if (n <= 1)
            return true;

        int l = 0, r = n - 1;

        // STEP 1: Strip matching prefix/suffix values.
        // This is the genius step that prevents duplicates from tricking the
        // min-finding logic into grabbing the wrong pivot!
        while (nums[l] == nums[r] && l < r)
        {
            l++;
        }

        // STEP 2: Find the true pivot (minimum value) in the remaining window.
        int minIdx = 0;
        int minVal = INT_MAX;

        for (int i = l; i < n; ++i)
        {
            if (nums[i] < minVal)
            {
                minVal = nums[i];
                minIdx = i;
            }
        }

        // STEP 3: Circularly validate the array starting from the true pivot.
        l = minIdx;
        r = (minIdx + 1) % n;

        while (r != minIdx)
        {

            // If the next element drops below the current, it's invalid.
            if (nums[r] < nums[l])
            {
                return false;
            }

            // Move the window forward circularly.
            l = r;
            r = (r + 1) % n;
        }

        return true;
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

        cout << boolalpha;
        cout << "Is Array Sorted? Ans: " << (bool)ob.check(arr);

        cout << endl;
    }
}