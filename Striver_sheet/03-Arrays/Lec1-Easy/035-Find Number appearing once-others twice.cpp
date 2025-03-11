#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/arrays/find-the-number-that-appears-once-and-the-other-numbers-twice/
https://www.naukri.com/code360/problems/find-the-single-element_6680465?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/single-number/description/

Problem Statement:
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples:

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1


INPUT::::::
4
3 0 1
0 1
9 6 4 2 3 5 7 0 1
1

OUTPUT::::::

1
4
1
2
10
3

 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    // Approach: Using XOR
    int singleNumber(vector<int> &nums)
    {
        int xori = 0;

        for (int e : nums)
        {
            xori ^= e;
        }
        return xori;
    }

    // Time Complexity: O(N)
    // Space Complexity: O(1)
    // If given Array is in SORTED order then Better approach to follow:
    // int singleNumber(vector<int> &arr)
    // {
    //     int n = arr.size();
    //     int ans;

    //     // Traversing through the array.
    //     for (int i = 0; i < n; ++i)
    //     {

    //         // Checking if 'Arr[i]' is neither equal to 'Arr[i - 1]' and 'Arr[i + 1]'.
    //         if ((i == 0 || arr[i] != arr[i - 1]) && (i == n - 1 || arr[i] != arr[i + 1]))
    //         {
    //             ans = arr[i];
    //             break;
    //         }
    //     }
    //     return ans;
    // }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
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

        cout << ob.singleNumber(arr);
        cout << endl;
    }
}