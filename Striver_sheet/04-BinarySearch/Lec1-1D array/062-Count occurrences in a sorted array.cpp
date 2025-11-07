#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Count occurrences of a number in a sorted array with duplicates

https://takeuforward.org/data-structure/count-occurrences-in-sorted-array/
https://www.naukri.com/code360/problems/occurrence-of-x-in-a-sorted-array_630456?leftPanelTabValue=PROBLEM

Problem Statement: You are given a sorted array containing N integers and a number target, you have to find the occurrences of target in the given array.

Examples:

Example 1:
Input: N = 7,  target = 3 , array[] = {2, 2 , 3 , 3 , 3 , 3 , 4}
Output: 4
Explanation: 3 is occurring 4 times in
the given array so it is our answer.

Example 2:
Input: N = 8,  target = 2 , array[] = {1, 1, 2, 2, 2, 2, 2, 3}
Output: 5
Explanation: 2 is occurring 5 times in the given array so it is our answer.



INPUT::::::
2
3
1 1 1 2 2 3 3
6
1 2 4 4 5

OUTPUT::::::
2
0

 */
class Solution
{
public:
    /*
    count(arr, target)
    ------------------
    Problem:
        - Given a sorted array `arr` and a target value, return how many times
          the target appears in the array.

    Intuition / Approach:
        - In a sorted array, duplicates of `target` appear consecutively.
        - So if we can find:
            * `start` = index of the **first occurrence** of target
            * `end`   = index of the **last occurrence** of target
          then count = end - start + 1.
        - Both can be found using binary search in O(log N):
            * To find `start`, when we see target at mid, we move left (r = mid - 1)
              to check if an earlier occurrence exists.
            * To find `end`, when we see target at mid, we move right (l = mid + 1)
              to check if a later occurrence exists.
        - If `target` is not found, return 0.

    Complexity:
        - Time: O(log N) + O(log N) = O(log N)
          (two binary searches).
        - Space: O(1).

    Edge cases handled:
        - Target not in array → returns 0.
        - Target occurs once → returns 1.
        - Multiple occurrences → returns correct count.
*/
    int count(vector<int> &arr, int target)
    {
        int N = arr.size();
        int l = 0, r = N - 1;
        int start = -1, end = -1;

        // First binary search: find the first occurrence (leftmost index)
        while (l <= r)
        {
            int mid = l + (r - l) / 2; // safer midpoint calculation

            if (arr[mid] == target)
            {
                start = mid; // possible candidate for first occurrence
                r = mid - 1; // but keep searching left side
            }
            else if (target < arr[mid])
            {
                r = mid - 1; // target is smaller → search left
            }
            else
            {
                l = mid + 1; // target is larger → search right
            }
        }

        // If start is still -1, target not present
        if (start == -1)
            return 0;

        // Second binary search: find the last occurrence (rightmost index)
        l = 0, r = N - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (arr[mid] == target)
            {
                end = mid;   // possible candidate for last occurrence
                l = mid + 1; // but keep searching right side
            }
            else if (target < arr[mid])
            {
                r = mid - 1; // target is smaller → search left
            }
            else
            {
                l = mid + 1; // target is larger → search right
            }
        }

        // Both start and end found → return count
        return (end - start + 1);
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

        cout << ob.count(arr, target);
        cout << endl;
    }
    return 0;
}