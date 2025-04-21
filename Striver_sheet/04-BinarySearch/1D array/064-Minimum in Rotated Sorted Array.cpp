#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find Minimum in Rotated Sorted Array

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

 */
class Solution
{
public:
    // Optimal approach: For any index, one side must be sorte, and the other might be unsorted. 
    // Time: O(logN)
    // Space: O(1)
    int findMin(vector<int>& arr) {
        int N=arr.size();

        int l=0, r=N-1;
        int minI=INT_MAX;

        while(l<=r){

            if(arr[l] <= arr[r]){     // search space is already sorte no further iteration is needed
                minI = min(minI, arr[l]);
                return minI;
            }

            int mid=l-(l-r)/2;

            //minI= min(arr[mid], minI);

            bool sortedL = arr[l]<=arr[mid]; // Left side is sorted
            bool sortedR = arr[mid]<=arr[r]; // Right side is sorted

            if(sortedL){
                minI= min(arr[l], minI);    // Take min from left
                l=mid+1;                    // Then go t right side
            }    
            else if(sortedR){
                minI= min(arr[mid], minI);  // Take min from the right side
                r=mid-1;                    // Then go to the left side
            }
        }
        return minI;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        //int target;
        //cin >> target;
        //cin.ignore();

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