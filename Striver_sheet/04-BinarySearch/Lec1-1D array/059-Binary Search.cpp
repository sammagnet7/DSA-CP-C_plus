#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Binary Search to find X in sorted array

https://takeuforward.org/data-structure/binary-search-explained/
https://leetcode.com/problems/binary-search/

Problem statement:
Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.


Examples:

Example 1:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:
Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1


INPUT::::::
2
-1 0 3 5 9 12
-1 0 3 5 9 12

OUTPUT::::::
4
-1

 */
class Solution
{
public:

    int search(vector<int> &arr, int target)
    {
        int N = arr.size();

        return myBinarySearch(arr, target, 0, N - 1);
    }

private:
    // // Approach: Recursive
    // // Time: O(Log N)
    // // Space: O(1)
    // int myBinarySearch(vector<int>& arr, int target, int l, int r){

    //     if(l>r) return -1;  // Base case

    //     int mid = l - (l-r)/2;

    //     if(arr[mid]==target) return mid;
    //     else if(arr[mid]<target) l=mid+1;
    //     else if(target<arr[mid]) r=mid-1;

    //     return myBinarySearch(arr,target,l,r);
    // }

    // Approach: Iterative
    // Time: O(Log N)
    // Space: O(1)
    int myBinarySearch(vector<int> &arr, int target, int l, int r)
    {

        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
                return mid;
            else if (arr[mid] < target)
                l = mid + 1;
            else if (target < arr[mid])
                r = mid - 1;
        }
        return -1;
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