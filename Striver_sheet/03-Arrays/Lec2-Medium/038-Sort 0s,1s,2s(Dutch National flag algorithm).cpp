#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Sort an array of 0s, 1s and 2s
Dutch National flag algorithm

https://takeuforward.org/data-structure/sort-an-array-of-0s-1s-and-2s/
https://leetcode.com/problems/sort-colors/description/
https://www.naukri.com/code360/problems/631055?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: Given an array consisting of only 0s, 1s, and 2s. Write a program to in-place sort the array without using inbuilt sort functions. ( Expected: Single pass-O(N) and constant space)

Examples:
Input:
 nums = [2,0,2,1,1,0]
Output
: [0,0,1,1,2,2]

Input:
 nums = [2,0,1]
Output:
 [0,1,2]

Input:
 nums = [0]
Output:
 [0]


INPUT::::::
7
2 0 2 1 1 0
2 0 1
0
0 1 2 2 1 0
0 1 2 1 2 1 2
2 2 2 1 1 1 0
2 1 2 0 1 0

OUTPUT::::::

0 0 1 1 2 2
0 1 2
0
0 0 1 1 2 2
0 1 1 1 2 2 2
0 1 1 1 2 2 2
0 0 1 1 2 2

 */
class Solution
{
public:
    // Approach: Counting
    // Time: O(N)
    // Space: O(3)
    // void sortColors(vector<int> &arr)
    // {
    //     int c_0 = 0, c_1 = 0, c_2 = 0;

    //     for (int i = 0; i < arr.size(); i++)
    //     {
    //         if (arr[i] == 0)
    //             c_0++;
    //         if (arr[i] == 1)
    //             c_1++;
    //         if (arr[i] == 2)
    //             c_2++;
    //     }
    //     int i = 0;
    //     while (c_0--)
    //         arr[i++] = 0;
    //     while (c_1--)
    //         arr[i++] = 1;
    //     while (c_2--)
    //         arr[i++] = 2;
    // }

    /*
    Algorithm / Intuition
    This problem is a variation of the popular Dutch National flag algorithm.
    This algorithm contains 3 pointers i.e. low, mid, and high, and 3 main rules.  The rules are the following:

    arr[0….low-1] contains 0. [Extreme left part]
    arr[low….mid-1] contains 1.
    arr[high+1….n-1] contains 2. [Extreme right part], n = size of the array
    The middle part i.e. arr[mid….high] is the unsorted segment.


    First, we will run a loop that will continue until mid <= high.
    There can be three different values of mid pointer i.e. arr[mid]
    If arr[mid] == 0, we will swap arr[low] and arr[mid] and will increment both low and mid. Now the subarray from index 0 to (low-1) only contains 0.
    If arr[mid] == 1, we will just increment the mid pointer and then the index (mid-1) will point to 1 as it should according to the rules.
    If arr[mid] == 2, we will swap arr[mid] and arr[high] and will decrement high. Now the subarray from index high+1 to (n-1) only contains 2.
    In this step, we will do nothing to the mid-pointer as even after swapping, the subarray from mid to high(after decrementing high) might be unsorted. So, we will check the value of mid again in the next iteration.
    */
    // Approach: usint 3 Pointers: Dutch National flag algorithm
    // Time: O(N)
    // Space: O(3)
    void sortColors(vector<int> &arr)
    {
        int N = arr.size();
        int low = 0;      // 0s .. (0 to low-1)
        int mid = 0;      // 1s .. (low to mid-1) and
                          // unsorted .. (mid to high)
        int high = N - 1; // 2s .. (high+1 to N-1)

        while (mid <= high)
        {
            if (arr[mid] == 0)
            {
                swap(arr[low++], arr[mid++]);
            }
            else if (arr[mid] == 1)
            {
                mid++;
            }
            else if (arr[mid] == 2)
            {
                swap(arr[mid], arr[high--]);
            }
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

        ob.sortColors(arr);

        for (int e : arr)
        {
            cout << e << " ";
        }

        cout << endl;
    }
}