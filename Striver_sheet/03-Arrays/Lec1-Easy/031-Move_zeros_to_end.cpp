#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/move-all-zeros-to-the-end-of-the-array/
https://leetcode.com/problems/move-zeroes/description/
https://www.naukri.com/code360/problems/ninja-and-the-zero-s_6581958?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem Statement: Given an array, and an element num the task is to find if num is present in the given array or not. If present print the index of the element or print -1.


Example 1:
Input:
 1 ,0 ,2 ,3 ,0 ,4 ,0 ,1
Output:
 1 ,2 ,3 ,4 ,1 ,0 ,0 ,0
Explanation:
 All the zeros are moved to the end and non-negative integers are moved to front by maintaining order

Example 2:
Input:
 1,2,0,1,0,4,0
Output:
 1,2,1,4,0,0,0
Explanation:
 All the zeros are moved to the end and non-negative integers are moved to front by maintaining order

Expected time complexity:
 The expected time complexity is O(n).
Constraints:
1 ≤ n ≤ 10^6
0 ≤ arr[i] ≤ 10^9

INPUT::::::
5
1 0 2 3 0 4 0 1
1 2 0 1 0 4 0
0 1 0 3 12
0
4 3 0 3 2 0

OUTPUT::::::




1 2 3 4 1 0 0 0
1 2 1 4 0 0 0
1 3 12 0 0
0
4 3 3 2 0 0

 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    // Approach: Swap zero elements to the back
    // void moveZeroes(vector<int> &nums)
    // {
    //     int len = nums.size();
    //     int st_nz_idx = -1;

    //     // Loop for finding zeros
    //     for (int i = 0; i < len; i++)
    //     {
    //         if (nums[i] == 0)
    //         {
    //             if (st_nz_idx < i)
    //                 st_nz_idx = i;

    //             // Loop for finding non zeros
    //             for (int j = st_nz_idx; j < len; j++)
    //             {
    //                 if (nums[j] != 0)
    //                 {
    //                     swap(nums[i], nums[j]);
    //                     st_nz_idx = j;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }

    // Time: O(N)
    // Space: O(1)
    // Approach: Swap non zero elements to the front
    void moveZeroes(vector<int> &nums)
    {
        int N = nums.size();
        int nz = 0;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] != 0)
            {
                swap(nums[nz++], nums[i]);
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

        ob.moveZeroes(arr);

        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}