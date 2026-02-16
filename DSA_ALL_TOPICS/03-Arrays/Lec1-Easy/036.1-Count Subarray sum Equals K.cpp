#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <sstream>
#include <unordered_map>

using namespace std;

/*

Title: Count Subarray sum Equals K

Links:
https://takeuforward.org/data-structure/longest-subarray-with-given-sum-k/
https://www.youtube.com/watch?v=xvNwoz-ufXA
https://leetcode.com/problems/subarray-sum-equals-k/


Problem Statement:
Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

A subarray is a contiguous non-empty sequence of elements within an array.


Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2



INPUT::::::
2
2
1 1 1
3
1 2 3


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
    // Works only if all elements are strictly positive (>0).
    // Why? Because with non-positive (0 or negative) values, shrinking the window
    // when sum > k is not guaranteed to reduce the sum in a consistent way.
    //
    // Idea:
    //   - Maintain a window [left..right] with two pointers.
    //   - Expand window by moving `right` and add arr[right] to running sum.
    //   - If sum > k, shrink from the left until sum <= k.
    //   - If sum == k, increment the count (found a subarray with required sum).
    //   - Continue until right traverses the array.
    //
    // Time Complexity: O(N)
    //   - Each element is added once (right++) and removed at most once (left++).
    // Space Complexity: O(1)
    //   - Only constant variables used.
    //
    // Parameters:
    //   arr : vector of strictly positive integers
    //   k   : target sum
    // Returns:
    //   count : number of subarrays whose sum is exactly k
    //
    int subarraySum(vector<int> &arr, int k)
    {
        int N = arr.size();
        int left = 0, right = 0; // sliding window pointers
        long long sum = 0;       // running window sum
        int count = 0;           // number of subarrays with sum == k

        while (right < N)
        {
            // Expand the window by adding current element
            sum += arr[right];

            // Shrink from the left if sum exceeds target
            // (valid only because arr elements > 0)
            while (sum > k && left < right)
            {
                sum -= arr[left];
                left++;
            }

            // If current window sum equals k, increment result
            if (sum == k)
            {
                count++;
            }

            // Expand window by moving right pointer
            right++;
        }

        return count;
    }

    // Approach: Prefix Sum + Hash Map
    // --------------------------------
    // Works for arrays containing positive, zero, or negative values.
    // Sliding window fails when elements can be <= 0, but prefix sum allows handling all cases.
    //
    // Idea:
    //   - Maintain a running prefix sum while traversing.
    //   - If prefixSum == k, that means subarray [0..i] itself has sum k → count++.
    //   - Otherwise, to find a subarray ending at i with sum k:
    //       Let prefixSum[i] = current sum up to index i.
    //       We want: prefixSum[i] - prefixSum[j] = k  ⇒  prefixSum[j] = prefixSum[i] - k.
    //     So if (prefixSum - k) exists in the map, all subarrays ending at i and starting
    //     after any such prefix contribute to the count.
    //   - Insert/update prefixSum in map: prefixSum → frequency of occurrences.
    //   - Multiple occurrences of the same prefixSum mean multiple valid subarrays.
    //
    // Time Complexity:
    //   • O(N) on average with unordered_map (hash lookups avg O(1))
    //   • Worst-case can degrade to O(N^2) if many hash collisions occur.
    // Space Complexity: O(N) for the prefix sum hashmap.
    //
    // Parameters:
    //   arr : vector of integers (can be +, 0, -)
    //   k   : target sum
    // Returns:
    //   count : number of subarrays whose sum is exactly k
    //
    int subarraySum(vector<int> &arr, int k)
    {
        int N = arr.size();
        long long sum = 0; // running prefix sum
        int count = 0;     // total subarrays with sum == k

        // Map to store frequency of prefix sums encountered
        unordered_map<long long, int> prefixSum;

        // Traverse the array
        for (int e : arr)
        {
            sum += e; // update running sum

            // Case 1: If subarray [0..i] has sum == k
            if (sum == k)
                count++;

            // Case 2: Look for earlier prefixSum[j] = sum - k
            // If found, then subarray (j+1..i) has sum == k
            long long req = sum - k;
            if (prefixSum.find(req) != prefixSum.end())
            {
                // Add all such subarrays (count by frequency of prefixSum[j])
                count += prefixSum[req];
            }

            // Store/update current prefixSum frequency
            prefixSum[sum]++;
        }

        return count;
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

        cout << ob.subarraySum(arr, k);

        cout << endl;
    }
}