#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find Floor and ceil of target element from sorted array

https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1?track=DSASP-Searching&amp%253BbatchId=154&utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=floor-in-a-sorted-array

Problem statement:
Given a sorted array of N integers and an integer x, write a program to find the Floor and Ceil of x.

Note:

What is Floor?
Floor of `target` is the largest element (or largest index) in arr[] which is <= `target`.
In case of multiple occurrences of Floor of `target`, return the index of the last occurrence.
Floor of `target` doesn’t exist if `target` is smaller than smallest element of arr[].

What is Ceil?
Ceil of `target` is the smallest element (or smallest index) in arr[] which is >= `target`.
In case of multiple occurrences of Ceil of `target`, return the index of the first occurrence.
Ceil of`target` doesn’t exist if `target` is smaller than smallest element of arr[].


Examples:

Example 1:
Input: arr[] = [1, 2, 8, 10, 10, 12, 19], x = 5
Output: 1
Explanation: Largest number less than or equal to 5 is 2, whose index is 1.

Example 2:
Input: arr[] = [1, 2, 8, 10, 10, 12, 19], x = 11
Output: 4
Explanation: Largest Number less than or equal to 11 is 10, whose indices are 3 and 4. The index of last occurrence is 4.

Example 3:
Input: arr[] = [1, 2, 8, 10, 10, 12, 19], x = 0
Output: -1
Explanation: No element less than or equal to 0 is found. So, output is -1.


INPUT::::::
10
2
1 2 2 3
9
3 5 8 9 15 19
4
1 2 2 3
7
1 4 7 8 10
10
1 2 5 6 10
5
1 5 5 7 7 9 10
5
1 2 8 10 10 12 19
11
1 2 8 10 10 12 19
0
1 2 8 10 10 12 19
10
1 2 8 10 10 12 19

OUTPUT::::::
Floor index: 2 Ceil index: 1
Floor index: 3 Ceil index: 3
Floor index: 3 Ceil index: -1
Floor index: 2 Ceil index: 2
Floor index: 4 Ceil index: 4
Floor index: 2 Ceil index: 1
Floor index: 1 Ceil index: 2
Floor index: 4 Ceil index: 5
Floor index: -1 Ceil index: 0
Floor index: 4 Ceil index: 3


 */
class Solution
{
public:
    // Approach: optimal :: Binary search
    // Floor of `target` is the largest element (or largest index) in arr[] which is <= `target`
    // In case of multiple occurrences of Floor of `target`, return the index of the last occurrence.
    // Floor of `target` doesn’t exist if `target` is smaller than smallest element of arr[]
    //
    // Always focus on the condition in which the array element can be a possible ans, here i.e. arr[i]<=target
    // Time: O(Log N)
    // Space: O(1)
    int findFloor(vector<int> &arr, int target)
    {

        int N = arr.size();

        int l = 0, r = N - 1;
        int ans = -1;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                ans = mid;
                l = mid + 1;
            }
            else if (arr[mid] < target)
            {
                ans = mid;
                l = mid + 1;
            }
            else if (target < arr[mid])
            {
                r = mid - 1;
            }
        }

        return ans;
    }

    // Approach: optimal :: Binary search
    // Ceil of `target` is the smallest element (or smallest index) in arr[] which is >= `target`.
    // In case of multiple occurrences of Ceil of `target`, return the index of the first occurrence.
    // Ceil of`target` doesn’t exist if `target` is smaller than smallest element of arr[]
    //
    // Always focus on the condition in which the array element can be a possible ans, here i.e. arr[i]>=target 
    // Time: O(Log N)
    // Space: O(1)
    int findCeil(vector<int> &arr, int target)
    {

        int N = arr.size();

        int l = 0, r = N - 1;
        int ans = -1;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                ans = mid;
                r = mid - 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
            else if (target < arr[mid])
            {
                ans = mid;
                r = mid - 1;
            }
        }

        return ans;
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

        cout << "Floor index: " << ob.findFloor(arr, target) << " Ceil index: " << ob.findCeil(arr, target);
        cout << endl;
    }
    return 0;
}