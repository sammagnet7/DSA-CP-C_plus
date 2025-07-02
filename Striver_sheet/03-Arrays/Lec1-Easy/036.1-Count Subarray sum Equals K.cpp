#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <sstream>
#include<unordered_map>

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
    // Approach: If elements are>0, approach: 2 pointer method
    //  Note: if elements = 0 or elements<0 exists, then fails.
    //  Time: O(N);
    //  Space: O(1)
    //  int subarraySum(vector<int>& arr, int k) {
    //      int N=arr.size();
    //      int left=0,right=0;
    //      long long sum=0;
    //      int count=0;

    //     while(right<N){
    //         sum+=arr[right];

    //         while(sum>k && left<right){
    //             sum-=arr[left];
    //             left++;
    //         }

    //         if(sum==k) count++; // should be performed after greater than check

    //         right++;
    //     }
    //     return count;
    // }

    // Approach: If elements are<0 also: approach prefix sum.
    //  Time: Avg(N) or O(N^2)
    //  Space: O(N)
    int subarraySum(vector<int> &arr, int k)
    {
        int N = arr.size();
        long long sum = 0;
        int count = 0;

        unordered_map<long long, int> prefixSum; // O(N)

        for (int e : arr)
        {
            sum += e;

            if (sum == k)
                count++;

            int req = sum - k; // Because (sum-req)==k
            if (prefixSum.find(req) != prefixSum.end())
            {
                count += prefixSum[req];
            }

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