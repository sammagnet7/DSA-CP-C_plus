#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/insertion-sort-algorithm/
https://takeuforward.org/arrays/recursive-insertion-sort-algorithm/
https://www.geeksforgeeks.org/problems/insertion-sort/0?category%5B%5D=Algorithms&page=1&query=category%5B%5DAlgorithmspage1&utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=insertion-sort

Problem statement:
Given an array, arr[]. Sort the array using Insertion sort algorithm.

Examples :

Input: arr[] = [4, 1, 3, 9, 7]
Output: [1, 3, 4, 7, 9]
Explanation: The sorted array will be [1, 3, 4, 7, 9].

Input: arr[] = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Explanation: The sorted array will be [1, 2, 3, 4, 5, 6, 7, 8, 9, 10].

Input: arr[] = [4, 1, 9]
Output: [1, 4, 9]
Explanation: The sorted array will be [1, 4, 9].

Constraints:
1 <= arr.size() <= 1000
1 <= arr[i] <= 1000

*/
class Solution
{
public:
    /**
     * Insertion Sort Algorithm
     * ------------------------
     * Idea:
     *  - Builds the sorted array one element at a time.
     *  - At iteration i, the subarray arr[0..i-1] is already sorted.
     *  - Insert arr[i] into its correct position within this sorted subarray
     *    by shifting/swapping larger elements to the right.
     *
     * Time Complexity:
     *  - Best Case: O(N)     (when array is already sorted → only 1 comparison per iteration, no swaps)
     *  - Average:   O(N^2)
     *  - Worst:     O(N^2)   (when array is reverse sorted → maximum shifts/swaps each time)
     *
     * Space Complexity:
     *  - O(1) (in-place, no extra data structures)
     *
     * Stability:
     *  - Stable (equal elements preserve relative order since swap only happens
     *    when arr[j] < arr[j-1], not when equal).
     */
    void insertionSort(vector<int> &arr)
    {
        int n = arr.size();

        // Outer loop: place each element arr[i] into sorted position
        for (int i = 0; i < n; i++)
        {
            // Inner loop: shift/swaps arr[i] backwards until it's in correct position
            for (int j = i; j > 0; j--)
            {
                // If current element is >= previous, it's already in right place → stop
                if (arr[j] >= arr[j - 1])
                    break;
                else
                    // Otherwise, swap current with previous (move smaller element left)
                    swap(arr[j], arr[j - 1]);
            }
        }
    }

    void recursive_insertionSort(vector<int> &arr, int i, int n)
    {
        if (i == n)
            return;

        for (int j = i; j > 0; j--)
        {
            if (arr[j] > arr[j - 1])
                break;
            else
                swap(arr[j], arr[j - 1]);
        }

        recursive_insertionSort(arr, ++i, n);
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
        // ob.insertionSort(arr);
        ob.recursive_insertionSort(arr, 0, arr.size());

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}