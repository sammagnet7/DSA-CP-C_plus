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
    int count(vector<int> &arr, int target)
    {
        int N= arr.size();
        int l = 0, r = N - 1;
        int start = -1, end = -1;

        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                start = mid;
                r = mid - 1;
            }
            else if (target < arr[mid])
            {
                r = mid - 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
        }

        if (start == -1)
            return 0;

        l = 0, r = N - 1;
        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            if (arr[mid] == target)
            {
                end = mid;
                l = mid + 1;
            }
            else if (target < arr[mid])
            {
                r = mid - 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
        }

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