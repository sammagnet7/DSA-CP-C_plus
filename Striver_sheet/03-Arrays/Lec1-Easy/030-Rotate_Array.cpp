#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/rotate-array-by-k-elements/
https://www.naukri.com/code360/problems/left-rotate-an-array-by-one_5026278?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/rotate-array/submissions/1567978125/


Problem Statement: Given an array of integers, rotating array of elements by k elements either left or right.

Example 1:
Input: N = 7, array[] = {1,2,3,4,5,6,7} , k=2 , right
Output: 6 7 1 2 3 4 5
Explanation: array is rotated to right by 2 position .

Example 2:
Input: N = 6, array[] = {3,7,8,9,10,11} , k=3 , left
Output: 9 10 11 3 7 8
Explanation: Array is rotated to right by 3 position.


Follow up:
Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Approach 1: Using a "temp" array
For Rotating the Elements to right
Step 1: Copy the last k elements into the temp array.
Step 2: Shift n-k elements from the beginning by k position to the right
Step 3: Copy the elements into the main array from the temp array.

Approach 2: Using ” Reversal Algorithm “
A) For Rotating Elements to Right:
Step 1: Reverse the last k elements of the array
Step 2: Reverse the first n-k elements of the array.
Step 3: Reverse the whole array.

B) For Rotating the Elements to Left:
Step 1: Reverse the first k elements of the array
Step 2: Reverse the last n-k elements of the array.
Step 3: Reverse the whole array.

INPUT::::::
5
1 2 3 4 5
1 2 3 4 5 6 7
-1 -100 3 99
5
4 0 3 2 5

OUTPUT::::::



Rotated by 1 position: 5 1 2 3 4
Rotated by 2 position: 4 5 1 2 3
Rotated by 3 position: 3 4 5 1 2
----------------
Rotated by 1 position: 7 1 2 3 4 5 6
Rotated by 2 position: 6 7 1 2 3 4 5
Rotated by 3 position: 5 6 7 1 2 3 4
----------------
Rotated by 1 position: 99 -1 -100 3
Rotated by 2 position: 3 99 -1 -100
Rotated by 3 position: -100 3 99 -1
----------------
Rotated by 1 position: 5
Rotated by 2 position: 5
Rotated by 3 position: 5
----------------
Rotated by 1 position: 5 4 0 3 2
Rotated by 2 position: 2 5 4 0 3
Rotated by 3 position: 3 2 5 4 0
----------------



 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(N)
    // void rotate(vector<int> &nums, int k)
    // {
    //     int len = nums.size();
    //     vector<int> temp(len);
    //     int tmpidx = 0;

    //     k = k % len; // This line is Important to get rid of edge cases
    //     int rotate_start_idx = len - k;

    //     for (int i = rotate_start_idx; i < len; i++)
    //     {
    //         temp[tmpidx++] = nums[i];
    //     }
    //     for (int i = 0; i < rotate_start_idx; i++)
    //     {
    //         temp[tmpidx++] = nums[i];
    //     }

    //     for (int i = 0; i < len; i++)
    //     {
    //         nums[i] = temp[i];
    //     }
    // }

    // Time: O(N)
    // Space: O(1)
    void rotate(vector<int> &nums, int k)
    {
        int len = nums.size();
        k = k % len; // This line is Important to get rid of edge cas
        int rotate_start_idx = len - k;

        for (int i = rotate_start_idx, j = len - 1; i < j; i++, j--)
        {
            swap(nums[i], nums[j]);
        }
        for (int i = 0, j = rotate_start_idx - 1; i < j; i++, j--)
        {
            swap(nums[i], nums[j]);
        }
        for (int i = 0, j = len - 1; i < j; i++, j--)
        {
            swap(nums[i], nums[j]);
        }
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

        vector<int> req = arr;
        ob.rotate(req, 1);
        cout << "Rotated by 1 position: ";
        for (int i = 0; i < req.size(); i++)
        {
            cout << req[i] << " ";
        }
        cout << endl;

        vector<int> req2 = arr;
        ob.rotate(req2, 2);
        cout << "Rotated by 2 position: ";
        for (int i = 0; i < req2.size(); i++)
        {
            cout << req2[i] << " ";
        }
        cout << endl;

        vector<int> req3 = arr;
        ob.rotate(req3, 3);
        cout << "Rotated by 3 position: ";
        for (int i = 0; i < req3.size(); i++)
        {
            cout << req3[i] << " ";
        }
        cout << endl;

        cout << "----------------" << endl;
    }
}