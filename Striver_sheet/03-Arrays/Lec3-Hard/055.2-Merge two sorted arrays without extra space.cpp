#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Merge two Sorted Arrays Without Extra Space -> into arr1 only

https://takeuforward.org/data-structure/merge-two-sorted-arrays-without-extra-space/
https://leetcode.com/problems/merge-sorted-array/description/

Problem statement:
You are given two integer arrays arr1 and arr2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in arr1 and arr2 respectively.
Merge arr1 and arr2 into a single array sorted in non-decreasing order.
The final sorted array should not be returned by the function, but instead be stored inside the array arr1. To accommodate this, arr1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. arr2 has a length of n.


Examples:

Example 1:
    Input: arr1 = [1,2,3,0,0,0], m = 3, arr2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]
    Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
    The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from arr1.

Example 2:
    Input: arr1 = [1], m = 1, arr2 = [], n = 0
    Output: [1]
    Explanation: The arrays we are merging are [1] and [].
    The result of the merge is [1].

Example 3:
    Input: arr1 = [0], m = 0, arr2 = [1], n = 1
    Output: [1]
    Explanation: The arrays we are merging are [] and [1].
    The result of the merge is [1].
    Note that because m = 0, there are no elements in arr1. The 0 is only there to ensure the merge result can fit in arr1.

INPUT::::::
6
4 3
1 4 8 10 0 0 0
2 3 9
4 5
1 3 5 7 0 0 0
0 2 6 8 9

OUTPUT::::::
[ 1 2 3 4 8 9 10 ]
[ 0 1 2 3 5 6 7 8 9 ]


 */
class Solution
{
public:
    // Approach: Optimal
    // Right Shift the arr1 by n positions.
    // Then compare two arrays and fill arr1
    // Time: O(N)
    // Space: O(1)
    void merge(vector<long long> &arr1, int m, vector<long long> &arr2, int n)
    {
        int t = m + n;

        for (int i = m - 1, j = 0; i >= 0; i--, j++)
        {
            arr1[t - 1 - j] = arr1[i];
        }

        int i = n, j = 0, k = 0;
        while (i < t && j < n)
        {
            if (arr1[i] <= arr2[j])
            {
                arr1[k] = arr1[i];
                k++;
                i++;
            }
            else
            {
                arr1[k] = arr2[j];
                k++;
                j++;
            }
        }
        while (i < t)
        {
            arr1[k] = arr1[i];
            k++;
            i++;
        }
        while (j < n)
        {
            arr1[k] = arr2[j];
            k++;
            j++;
        }
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int m, n;
        cin >> m >> n;
        cin.ignore();

        string line1, line2;
        getline(cin, line1);
        getline(cin, line2);

        vector<long long> arr1, arr2;

        stringstream ss1(line1);
        stringstream ss2(line2);

        long long num;

        while (ss1 >> num)
        {
            arr1.push_back(num);
        }
        while (ss2 >> num)
        {
            arr2.push_back(num);
        }

        Solution ob;
        ob.merge(arr1, m, arr2, n);

        cout << "[ ";
        for (long long i = 0; i < m + n; i++)
        {
            cout << arr1[i] << " ";
        }
        cout << "]";
        cout << endl;
    }
    return 0;
}