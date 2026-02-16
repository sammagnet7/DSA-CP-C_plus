#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/longest-subarray-with-given-sum-k/
https://www.naukri.com/code360/problems/longest-subarray-with-sum-k_6682399?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_Arrayproblems&leftPanelTabValue=SUBMISSION

https://takeuforward.org/arrays/longest-subarray-with-sum-k-postives-and-negatives/
https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=longest-sub-array-with-sum-k


Problem Statement:
Given an array arr[] containing integers and an integer k, your task is to find the length of the longest subarray where the sum of its elements is equal to the given value k. If there is no subarray with sum equal to k, return 0.

Examples:

Input: arr[] = [10, 5, 2, 7, 1, -10], k = 15
Output: 6
Explanation: Subarrays with sum = 15 are [5, 2, 7, 1], [10, 5] and [10, 5, 2, 7, 1, -10]. The length of the longest subarray with a sum of 15 is 6.

Input: arr[] = [-5, 8, -14, 2, 4, 12], k = -5
Output: 5
Explanation: Only subarray with sum = -5 is [-5, 8, -14, 2, 4] of length 5.

Input: arr[] = [10, -10, 20, 30], k = 5
Output: 0
Explanation: No subarray with sum = 5 is present in arr[].


INPUT::::::
6
3
1 2 3 1 1 1 1
2
1 2 1 3
2
2 2 4 1 2
15
10 5 2 7 1 -10
-5
-5 8 -14 2 4 12
5
10 -10 20 30

OUTPUT::::::

3
1
1
6
5
0

 */
class Solution
{
public:
    // Approach: Sliding Window / Two Pointers
    // ---------------------------------------
    // This approach works ONLY if all elements are non-negative.
    // Why? Because with negatives, shrinking the window when sum > k would not be valid.
    //
    // Idea:
    //   - Maintain a sliding window [l..r] with two pointers.
    //   - Expand the window by moving `r` and keep a running `sum`.
    //   - If sum == k, update max length.
    //   - If sum > k, shrink from left (`l++`) until sum <= k, checking again for equality.
    //   - Continue until r traverses the array.
    //
    // Time Complexity: O(2N) in worst case
    //   - Each element is added once (r++) and removed at most once (l++).
    //   - So overall linear time.
    // Space Complexity: O(1)
    //   - Only variables used; no extra storage.
    //
    // Parameters:
    //   arr : vector of non-negative integers
    //   k   : target sum
    // Returns:
    //   maxL : length of the longest subarray with sum exactly equal to k
    //
    int longestSubarray_WO_Negetives(vector<int> &arr, int k)
    {
        int l = 0, r = 0; // Two pointers (left and right)
        int sum = 0;      // Current window sum
        int len = arr.size();
        int maxL = 0; // Track maximum subarray length found

        while (r < len)
        {
            // Expand the window to include arr[r]
            sum += arr[r];

            // Check if current window [l..r] sum equals k
            if (sum == k)
            {
                int countL = r - l + 1; // current window length
                maxL = (countL > maxL) ? countL : maxL;
            }

            // If sum > k, shrink the window from the left until sum <= k
            while (sum > k && l <= r)
            {
                sum -= arr[l]; // remove arr[l] from sum

                // After shrinking, check again for equality
                if (sum == k)
                {
                    int countL = r - l; // new window length
                    maxL = (countL > maxL) ? countL : maxL;
                }

                l++; // move left pointer
            }

            // Move right pointer forward (expand window)
            r++;
        }

        return maxL;
    }

    // Approach: Prefix Sum + Hash Map
    // --------------------------------
    // Unlike the sliding-window approach (which only works for non-negative arrays),
    // this method works for arrays containing negatives as well.
    //
    // Idea:
    //   - Maintain a running prefix sum as we traverse the array.
    //   - If prefixSum == k, then the subarray [0..i] has sum k → candidate length = i+1.
    //   - Otherwise, check if there exists a prefixSum_req = prefixSum - k in the map.
    //       • If yes, then the subarray (prefixSum_index_map[prefixSum_req] + 1 .. i) has sum k.
    //       • Its length = i - prefixSum_index_map[prefixSum_req].
    //   - To maximize length, we want the leftmost occurrence of each prefix sum, so
    //     insert prefixSum into the map only if it doesn’t already exist.
    //   - Update max length whenever we find a valid subarray.
    //
    // Time Complexity:
    //   • O(N) if using unordered_map (average case)
    //   • O(N log N) if using map (because insert/find is O(log N))
    //   • Worst-case unordered_map can degrade to O(N^2), but rare.
    // Space Complexity: O(N) for storing prefix sums in the map.
    //
    // Parameters:
    //   arr : vector of integers (can contain positive, negative, zero)
    //   k   : target sum
    // Returns:
    //   maxL : length of the longest subarray whose sum is exactly k
    //
    int longestSubarray_WITH_Negetives(vector<int> &arr, int k)
    {
        int maxL = 0;                      // store maximum length found
        map<int, int> prefixSum_index_map; // map: prefixSum → earliest index
        int prefixSum = 0;                 // running cumulative sum

        // Traverse the array
        for (int i = 0; i < arr.size(); i++)
        {
            prefixSum += arr[i]; // update running prefix sum

            // Store this prefix sum only if it's not already in the map
            // (we want to preserve the leftmost index for max length calculation)
            if (prefixSum_index_map.find(prefixSum) == prefixSum_index_map.end())
            {
                prefixSum_index_map[prefixSum] = i;
            }

            // Case 1: If the subarray [0..i] itself has sum k
            if (prefixSum == k)
            {
                maxL = i + 1; // length = i - 0 + 1
                continue;
            }

            // Case 2: Look for a prefix sum that would form a subarray sum k
            int prefixSum_req = prefixSum - k;

            // If prefixSum_req exists, then subarray after its index to i has sum k
            if (prefixSum_index_map.find(prefixSum_req) != prefixSum_index_map.end())
            {
                int subArrLen = (i - prefixSum_index_map[prefixSum_req]);
                maxL = subArrLen > maxL ? subArrLen : maxL;
            }
        }

        return maxL;
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
        int k;
        cin >> k;
        cin.ignore();

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

        // cout << ob.longestSubarray_WO_Negetives(arr, k);

        cout << ob.longestSubarray_WITH_Negetives(arr, k);

        cout << endl;
    }
}