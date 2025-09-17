#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/sorting/selection-sort-algorithm/
https://www.geeksforgeeks.org/problems/selection-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=selection-sort

Problem statement:
Given an array arr, use selection sort to sort arr[] in increasing order.

Examples :

Input: arr[] = [4, 1, 3, 9, 7]
Output: [1, 3, 4, 7, 9]
Explanation: Maintain sorted (in bold) and unsorted subarrays. Select 1. Array becomes 1 4 3 9 7. Select 3. Array becomes 1 3 4 9 7. Select 4. Array becomes 1 3 4 9 7. Select 7. Array becomes 1 3 4 7 9. Select 9. Array becomes 1 3 4 7 9.

Input: arr[] = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Input: arr[] = [38, 31, 20, 14, 30]
Output: [14, 20, 30, 31, 38]

Constraints:
1 ≤ arr.size() ≤ 103
1 ≤ arr[i] ≤ 106

*/
class Solution
{
public:
    /**
     * Selection Sort Algorithm
     * ------------------------
     * Idea:
     *  - Iterate through the array.
     *  - For each position `i`, find the smallest element in the subarray [i..n-1].
     *  - Swap that smallest element with arr[i].
     *  - After i iterations, the first i elements are already sorted.
     *
     * Time Complexity:
     *  - Best Case:  O(N^2)   (still scans entire array for min every time)
     *  - Average:   O(N^2)
     *  - Worst:     O(N^2)
     *
     * Space Complexity:
     *  - O(1) (in-place, no extra data structures)
     *
     * Stability:
     *  - Not stable by default (equal elements can be swapped and change relative order).
     */
    void selectionSort(vector<int> &arr)
    {
        int n = arr.size();

        // Outer loop goes from 0 to n-1
        for (int i = 0; i < n; i++)
        {
            int mini = -1;      // index of minimum element in current pass
            int minv = INT_MAX; // value of minimum element

            // Inner loop: find the smallest element in arr[i..n-1]
            for (int j = i; j < n; j++)
            {
                if (arr[j] < minv)
                {
                    mini = j;
                    minv = arr[j];
                }
            }

            // Swap the found minimum element with the element at index i
            swap(arr[i], arr[mini]);
        }
    }
};

int main()
{

    int t;
    cin >> t;
    cin.ignore();
    cout << endl;

    while (t--)
    {
        string input;

        getline(cin, input);
        stringstream ss(input);

        vector<int> arr;
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;
        ob.selectionSort(arr);

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}