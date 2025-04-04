#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/bubble-sort-algorithm/
https://takeuforward.org/arrays/recursive-bubble-sort-algorithm/
https://www.geeksforgeeks.org/problems/bubble-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=bubble-sort


Problem statement:
Given an array, arr[]. Sort the array using bubble sort algorithm.

Examples :

Input: arr[] = [4, 1, 3, 9, 7]
Output: [1, 3, 4, 7, 9]

Input: arr[] = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

Input: arr[] = [1, 2, 3, 4, 5]
Output: [1, 2, 3, 4, 5]
Explanation: An array that is already sorted should remain unchanged after applying bubble sort.

Constraints:
1 <= arr.size() <= 103
1 <= arr[i] <= 103

*/
class Solution
{
public:
    // Time: Best case: O(N) when array is already sorted,
    // Avg and worst case: O(N^2)
    void bubbleSort(vector<int> &arr)
    {

        for (int i = 0, j = arr.size(); i < j; j--)
        {

            bool isSwaped = false;

            for (int k = 0; k < j - 1; k++)
            {

                if (arr[k] > arr[k + 1])
                {
                    swap(arr[k], arr[k + 1]);
                    isSwaped = true;
                }
            }

            if (!isSwaped)
                return;
        }
    }

    void recursive_bubbleSort(vector<int> &arr, int n)
    {
        // Base Case: range == 1.
        if (n == 1)
            return;

        int didSwap = 0;
        for (int j = 0; j <= n - 2; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                didSwap = 1;
            }
        }

        // if no swapping happens.
        if (didSwap == 0)
            return;

        // Range reduced after recursion:
        recursive_bubbleSort(arr, n - 1);
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
        // ob.bubbleSort(arr);

        ob.recursive_bubbleSort(arr, arr.size());

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}