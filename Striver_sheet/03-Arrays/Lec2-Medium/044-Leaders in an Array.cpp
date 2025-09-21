#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Title : Leaders in an Array problem

https://takeuforward.org/data-structure/leaders-in-an-array/
https://www.naukri.com/code360/problems/superior-elements_6783446?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse&leftPanelTabValue=SUBMISSION
https://www.geeksforgeeks.org/problems/leaders-in-an-array-1587115620/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=leaders-in-an-array

Problem statement:
Given an integer array nums, return a list of all the leaders in the array.

A leader in an array is an element whose value is strictly greater than all elements to its right in the given array. The rightmost element is always a leader. The elements in the leader array must appear in the order they appear in the nums array.

Examples:
    Input: nums = [1, 2, 5, 3, 1, 2]
    Output: [5, 3, 2]
    Explanation:
    2 is the rightmost element, 3 is the largest element in the index range [3, 5], 5 is the largest element in the index range [2, 5]

    Input: nums = [-3, 4, 5, 1, -4, -5]
    Output: [5, 1, -4, -5]
    Explanation:
    -5 is the rightmost element, -4 is the largest element in the index range [4, 5], 1 is the largest element in the index range [3, 5] and 5 is the largest element in the range [2, 5]

    Example 1:
    Input:
    arr = [4, 7, 1, 0]
    Output:
    7 1 0
    Explanation:
    Rightmost element is always a leader. 7 and 1 are greater than the elements in their right side.

    Example 2:
    Input:
    arr = [10, 22, 12, 3, 0, 6]
    Output:
    22 12 6
    Explanation:
    6 is a leader. In addition to that, 12 is greater than all the elements in its right side (3, 0, 6), also 22 is greater than 12, 3, 0, 6


INPUT::::::
7
1 2 3
2 3 1 4 5
1 2
3 1 2
1 3 2
3 2 1
1 1 5

OUTPUT::::::

1 3 2
2 3 1 5 4
2 1
3 2 1
2 1 3
1 2 3
1 5 1
 */

class Solution
{
public:
    // Time: O(N)
    // Space: O(N)
    // approach: To be a leader that element must be greater than the maxelement found till now while traversing backwards
    vector<int> leaders(vector<int> &arr)
    {
        // Code here
        vector<int> res;

        int maxe = INT_MIN;

        for (int i = arr.size() - 1; i >= 0; i--)
        {

            if (arr[i] > maxe)
            {
                res.push_back(arr[i]);
                maxe = arr[i];
            }
        }

        reverse(res.begin(), res.end());
        return res;
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
        // int k;
        // cin >> k;
        // cin.ignore();

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
        vector<int> res;
        res = ob.leaders(arr);

        for (int e : res)
        {
            cout << e << " ";
        }

        cout << endl;
    }
}