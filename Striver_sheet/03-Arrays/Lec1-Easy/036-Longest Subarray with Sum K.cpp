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
    // Approach: Two pointer approach. Applicable only when elements are zero or positive only.
    // Time: O(2N)
    // Space: O(1)
    int longestSubarray_WO_Negetives(vector<int> &arr, int k)
    {
        // code here
        int l = 0, r = 0, sum = 0;
        int len = arr.size();
        int maxL = 0;

        while (r < len)
        {
            sum += arr[r];

            if (sum == k)
            {
                int countL = r - l + 1;
                maxL = (countL > maxL) ? countL : maxL;
            }

            while (sum > k && l <= r)
            {
                sum -= arr[l];

                if (sum == k)
                {
                    int countL = r - l;
                    maxL = (countL > maxL) ? countL : maxL;
                }

                l++;
            }
            r++;
        }

        return maxL;
    }

    // Approach applicable for all kinds of arrays
    // In this approach, we are using the concept of the prefix sum to solve this problem. Here, the prefix sum of a subarray ending at index i, simply means the sum of all the elements of that subarray.
    // we will keep track of the prefix sum of the subarrays generated at every index using a map data structure.
    // In the map, we will store every prefix sum calculated, with the index(where the subarray with that prefix sum ends)
    // to maximize the calculated length, we will consider only the first or the leftmost index where the subarray with sum x-k ends.
    // So, we will check the map before inserting the prefix sum. If it already exists in the map, we will not update it but if it is not present, we will insert it for the first time.
    int longestSubarray_WITH_Negetives(vector<int> &arr, int k)
    {
        int maxL = 0;
        map<int, int> prefixSum_index_map;
        int prefixSum = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            prefixSum += arr[i];

            // Maintaining cumulative sum with left most index possible
            if (prefixSum_index_map.find(prefixSum) == prefixSum_index_map.end())
            {
                prefixSum_index_map[prefixSum] = i;
            }

            // If current prefixSum matches then, this must be the longest subarray till now
            if (prefixSum == k)
            {
                maxL = i + 1;
                continue;
            }

            // else
            int prefixSum_req = prefixSum - k;

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