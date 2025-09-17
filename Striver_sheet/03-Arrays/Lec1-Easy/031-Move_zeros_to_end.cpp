#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/move-all-zeros-to-the-end-of-the-array/
https://leetcode.com/problems/move-zeroes/description/
https://www.naukri.com/code360/problems/ninja-and-the-zero-s_6581958?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem Statement: Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
Note that you must do this in-place without making a copy of the array.

Examples:
    Example 1:
    Input: nums = [0,1,0,3,12]
    Output: [1,3,12,0,0]

    Example 2:
    Input: nums = [0]
    Output: [0]


Constraints:
1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1


Follow up: Could you minimize the total number of operations done?


INPUT::::::
5
1 0 2 3 0 4 0 1
1 2 0 1 0 4 0
0 1 0 3 12
0
4 3 0 3 2 0

OUTPUT::::::

1 2 3 4 1 0 0 0
1 2 1 4 0 0 0
1 3 12 0 0
0
4 3 3 2 0 0

 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    // Approach: Swap zero elements to the back
    // void moveZeroes(vector<int> &nums)
    // {
    //     int len = nums.size();
    //     int st_nz_idx = -1;

    //     // Loop for finding zeros
    //     for (int i = 0; i < len; i++)
    //     {
    //         if (nums[i] == 0)
    //         {
    //             if (st_nz_idx < i)
    //                 st_nz_idx = i;

    //             // Loop for finding non zeros
    //             for (int j = st_nz_idx; j < len; j++)
    //             {
    //                 if (nums[j] != 0)
    //                 {
    //                     swap(nums[i], nums[j]);
    //                     st_nz_idx = j;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }

    // Approach 1: Two-Pass with Explicit Zero Detection
    // -------------------------------------------------
    // Idea:
    //   1. Find the first zero in the array (index i).
    //   2. For every subsequent non-zero element (from j), swap it forward into position i.
    //   3. Increment i as we place non-zero elements, keeping all zeros pushed to the right.
    //
    // Time Complexity: O(N)  (single pass to find first zero + one pass to rearrange)
    // Space Complexity: O(1)  (in-place swaps)
    //
    // Note: Slightly less clean compared to Approach 2, since it first "breaks" at a zero
    //       and then uses another loop to continue rearrangement.
    void moveZeroes(vector<int> &nums)
    {
        int n = nums.size();

        int i = 0;
        // Step 1: Find the index of the first zero
        for (i; i < n; i++)
        {
            if (nums[i] == 0)
                break; // Stop at the first zero
        }

        // Step 2: From the next index onwards, shift non-zeros forward
        for (int j = 1; j < n; j++)
        {
            if (j <= i)
            {
                // Ignore all elements before or at i, since we already handled them
                continue;
            }
            if (nums[j] != 0)
            {
                // Place the non-zero element into the earliest zero position
                swap(nums[i++], nums[j]);
            }
        }
    }
    // Approach 2: Optimal One-Pass Swap
    // ---------------------------------
    // Idea:
    //   Use a pointer `nz` (non-zero index) to track the position where the next non-zero
    //   element should be placed. Iterate through the array:
    //     - If nums[i] is non-zero, swap it into position `nz`, then increment `nz`.
    //   This ensures non-zero elements maintain relative order, and all zeros shift right.
    //
    // Time Complexity: O(N)  (single pass over array)
    // Space Complexity: O(1)  (in-place swaps)
    //
    // Note: Cleaner and more efficient than Approach 1 — no need to first detect zeros.
    void moveZeroes(vector<int> &nums)
    {
        int N = nums.size();
        int nz = 0; // Position where next non-zero should go

        for (int i = 0; i < N; i++)
        {
            if (nums[i] != 0)
            {
                // Swap current non-zero element into the 'nz' position
                swap(nums[nz++], nums[i]);
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

        ob.moveZeroes(arr);

        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}