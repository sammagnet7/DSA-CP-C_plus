#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <climits>
#include<algorithm>

using namespace std;

/*
https://leetcode.com/problems/frequency-of-the-most-frequent-element/description/
https://leetcode.com/problems/frequency-of-the-most-frequent-element/solutions/4173577/frequency-of-the-most-frequent-element

Problem Statement:
Maximum possible frequency of an element after performing at most k operations

The frequency of an element is the number of times it occurs in an array.
You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and **increment** the element at that index by 1.
Return the maximum possible frequency of an element after performing at most k operations.

Example 1:
Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.

Example 2:
Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.

Example 3:
Input: nums = [3,9,6], k = 2
Output: 1

Constraints:
1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 105
*/
class Solution
{
public:
    /**
     * Approach:
     * --------
     * - Sort the array first.
     * - Use a sliding window [l..r] to represent the current subarray.
     * - For each right pointer `r`, we try to make all elements in the window equal to nums[r].
     * - The number of operations needed = (nums[r] * window_size) - window_sum.
     * - If this required operations <= k, it's valid; update max length.
     * - Otherwise, shrink the window from the left until it becomes valid again.
     *
     * Algorithm:
     * ----------
     * 1. Sort nums.
     * 2. Initialize two pointers (l = 0, r = 0), window sum = 0, max_Len = 1.
     * 3. Iterate with r from 0..n-1:
     *      - Add nums[r] to window sum.
     *      - While condition is invalid (needed operations > k), move l forward and update sum.
     *      - Update answer with max window size.
     * 4. Return max_Len.
     *
     * Complexity:
     * -----------
     * - Time: O(n log n)   [due to sorting + linear sliding window]
     * - Space: O(1)        [in-place sorting, constant extra space]
     */
    int maxFrequency(vector<int> &nums, int k)
    {

        // Step 1: Sort the array
        // Because we want to make numbers equal to a bigger number (nums[r]),
        // sorting ensures nums[r] is always the largest in the current window.
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int l = 0;         // left pointer of sliding window
        int r = 0;         // right pointer of sliding window
        long long sum = 0; // sum of elements in current window
        int max_Len = 1;   // answer (at least one element can always be equal)

        // Step 2: Expand the window with right pointer
        while (r < n)
        {
            int win_len = r - l + 1; // current window length
            int target = nums[r];    // we want to make all nums[l..r] equal to nums[r]
            sum += target;           // add nums[r] to current window sum

            // Step 3: Check if possible to make all elements in [l..r] = nums[r]
            // Required increments = target * win_len - sum
            if ((long long)win_len * target - sum <= k)
            {
                // If we can do it within k operations,
                // update max frequency
                max_Len = max(max_Len, win_len);
                r++; // expand window
            }
            else
            {
                // Otherwise, shrink window from left until condition holds
                while ((long long)win_len * target - sum > k)
                {
                    sum -= nums[l++];    // remove nums[l] from sum
                    win_len = r - l + 1; // update window size
                }
                r++; // after shrinking, move right pointer again
            }
        }

        // Step 4: Return the maximum window length found
        return max_Len;
    }

    // Good approach: Binary search
    int maxFrequency(vector<int> &nums, int k)
    {
    }

    // Brute force approach Time: O(N^2)
    int maxFrequency(vector<int> &nums, int k)
    {
        map<int, int> freq; // taking map as, map is sorted by key and here key is the numbers

        for (int i : nums)
        { // O(N Log N)
            freq[i]++;
        }

        for (auto itr = freq.rbegin(); itr != freq.rend(); itr++)
        { // Reverse iterator
            int temp = k;
            auto left_itr = itr; // Reverse iterator
            int left_freq = 0;
            left_itr++;

            while (temp > 0 && left_itr != freq.rend())
            { // O((Unique elements)^2) ~ O(N^2)
                if (left_freq == 0)
                { // that means left_itr has moved to new left element
                    left_freq = left_itr->second;
                }
                if ((itr->first - left_itr->first) <= temp)
                {
                    (itr->second)++;
                }
                temp -= (itr->first - left_itr->first);

                left_freq--;
                if (left_freq == 0)
                {
                    left_itr++;
                }
            }
        }

        int maxi = 0;
        int maxFreq = 0;

        for (auto i : freq)
        {
            if (i.second > maxFreq)
            {
                maxFreq = i.second;
                maxi = i.first;
            }
        }

        return maxFreq;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore();

    cout << endl;
    while (t--)
    {
        int k;
        cin >> k;
        cin.ignore();

        string inStr;
        getline(cin, inStr);
        stringstream ss(inStr);

        vector<int> input;
        int inNum;
        while (ss >> inNum)
        {
            input.push_back(inNum);
        }

        Solution ob;
        cout << ob.maxFrequency(input, k) << endl;

        cout << "----" << endl;
    }

    return 0;
}
