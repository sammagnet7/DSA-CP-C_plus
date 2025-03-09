#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
http://takeuforward.org/data-structure/check-if-an-array-is-sorted/
https://www.naukri.com/code360/problems/ninja-and-the-sorted-check_6581957?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description/


Problem statement:
Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.
There may be duplicates in the original array.

Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.

Example 1:
Input: nums = [3,4,5,1,2]
Output: true
Explanation: [1,2,3,4,5] is the original sorted array.
You can rotate the array by x = 3 positions to begin on the element of value 3: [3,4,5,1,2].

Example 2:
Input: nums = [2,1,3,4]
Output: false
Explanation: There is no sorted array once rotated that can make nums.

Example 3:
Input: nums = [1,2,3]
Output: true
Explanation: [1,2,3] is the original sorted array.
You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.


INPUT::::::
6
3 4 5 1 2
2 1 3 4
1 2 3
0 0 0 1
4 5 4 4 4
6 10 6

OUTPUT::::::


Is Array Sorted? Ans: true
Is Array Sorted? Ans: false
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true
Is Array Sorted? Ans: true

 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    bool check(vector<int> &nums)
    {
        // Finds the first minimum element index from array
        int min_idx = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] < nums[min_idx])
                min_idx = i;
        }

        // If minimum value spans from last element to the firs element we need to handle such case
        // by taking the index from the tail side
        // example case: 6,10,6
        if (min_idx == 0 && nums[0] == nums[nums.size() - 1])
        {
            for (int i = nums.size() - 1; i >= 0; i--)
            {
                if (nums[0] == nums[i])
                    min_idx = i;
                else
                    break;
            }
        }

        // Finally the found index chack if array is in non-decreasing order
        int prev = nums[min_idx];
        for (int i = 1; i < nums.size(); i++)
        {
            if (prev > nums[(min_idx + i) % nums.size()])
                return false;
            prev = nums[(min_idx + i) % nums.size()];
        }
        return true;
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

        cout << boolalpha;
        cout << "Is Array Sorted? Ans: " << (bool)ob.check(arr);

        cout << endl;
    }
}