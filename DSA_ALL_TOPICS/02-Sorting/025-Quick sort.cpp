#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/quick-sort-algorithm/
https://www.geeksforgeeks.org/problems/quick-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=quick-sort

Problem:  Given an array of n integers, sort the array using the Quicksort method.

Examples:

Example 1:
Input: N=5, arr[]={4,2,1,6,7}
Output: 1,2,4,6,7,

Example 2:
Input: N=7,arr[]={3,2,8,5,1,4,23}
Output: 1,2,3,4,5,8,23


Intuition:

Quick Sort is a divide-and-conquer algorithm like the Merge Sort. But unlike Merge sort, this algorithm does not use any extra array for sorting(though it uses an auxiliary stack space). So, from that perspective, Quick sort is slightly better than Merge sort.
This algorithm is basically a repetition of two simple steps that are the following:

Pick a pivot and place it in its correct place in the sorted array.
Shift smaller elements(i.e. Smaller than the pivot) on the left of the pivot and larger ones to the right.
Now, let’s discuss the steps in detail considering the array {4,6,2,5,7,9,1,3}:

Step 1: The first thing is to choose the pivot. A pivot is basically a chosen element of the given array. The element or the pivot can be chosen by our choice. So, in an array a pivot can be any of the following:
a. The first element of the array
b. The last element of the array
c. Median of array
d. Any Random element of the array
After choosing the pivot(i.e. the element), we should place it in its correct position(i.e. The place it should be after the array gets sorted) in the array. For example, if the given array is {4,6,2,5,7,9,1,3}, the correct position of 4 will be the 4th position.

Note: Here in this tutorial, we have chosen the last element as our pivot. You can choose any element as per your choice.

Step 2: In step 2, we will shift the smaller elements(i.e. Smaller than the pivot) to the left of the pivot and the larger ones to the right of the pivot. In the example, if the chosen pivot is 4, after performing step 2 the array will look like: {3, 2, 1, 4, 6, 5, 7, 9}.
From the explanation, we can see that after completing the steps, pivot 4 is in its correct position with the left and right subarray unsorted. Now we will apply these two steps on the left subarray and the right subarray recursively. And we will continue this process until the size of the unsorted part becomes 1(as an array with a single element is always sorted).

*/
class Solution
{
public:
    /**
     * Partition Function (Lomuto/Hoare style hybrid)
     * ----------------------------------------------
     * Purpose:
     *  - Rearrange the elements in arr[start..end] around a pivot (chosen as last element).
     *  - After partition:
     *      * Elements <= pivot are on the left side
     *      * Elements >= pivot are on the right side
     *      * Returns the final index of the pivot
     *
     * Time Complexity: O(N)   [single pass over the subarray]
     * Space Complexity: O(1)  [in-place swaps]
     */
    int doPartition(vector<int> &arr, int start, int end)
    {
        int pivot = arr[end];  // Choosing last element as pivot
        int pivotidx = end;    // Store pivot index
        int partitionIdx = -1; // Final position of pivot
        int l = start, r = end;

        // Move pointers inward until they cross
        while (l < r)
        {
            // Move left pointer forward while arr[l] <= pivot
            while (arr[l] <= pivot && l < r)
                l++;

            // Move right pointer backward while arr[r] >= pivot
            while (arr[r] >= pivot && l < r)
                r--;

            // If still valid, swap out-of-place elements
            if (l < r)
                swap(arr[l], arr[r]);
        }

        // Place pivot in its correct position
        swap(arr[r], arr[pivotidx]);
        partitionIdx = r;

        return partitionIdx;
    }

    // Time: O(N)
    // Space: O(N)
    // Taking First element as Pivot
    // int doPartition(vector<int> &arr, int start, int end)
    // {

    //     int pivot = arr[start];
    //     int pivotidx = start;
    //     int partitionIdx = -1;
    //     int l = start, r = end;

    //     while (l < r)
    //     {
    //         while (arr[l] <= pivot && l < r)
    //             l++;
    //         while (arr[r] >= pivot && l <= r)
    //             r--;

    //         if (l < r)
    //             swap(arr[l], arr[r]);
    //     }

    //     swap(arr[r], arr[pivotidx]);

    //     partitionIdx = r;

    //     return partitionIdx;
    // }

    /**
     * Quick Sort Algorithm
     * --------------------
     * Idea:
     *  - Choose a pivot element (here: last element of subarray).
     *  - Partition array into two halves: elements <= pivot on left, >= pivot on right.
     *  - Recursively apply quickSort to the two halves.
     *
     * Time Complexity:
     *  - Best Case: O(N log N)   [balanced partition every time]
     *  - Average:  O(N log N)
     *  - Worst:    O(N^2)        [already sorted/reverse sorted input with bad pivot choice]
     *
     * Space Complexity:
     *  - O(log N) due to recursion stack (average)
     *  - O(N) in worst case recursion depth (if always unbalanced partitions)
     *
     * Stability:
     *  - Not stable (relative order of equal elements may change).
     */
    void quickSort(vector<int> &arr, int start, int end)
    {
        // Base case: subarray of size 0 or 1
        if (start >= end)
            return;

        // Partition array and get pivot index
        int partition = doPartition(arr, start, end);

        // Recursively sort left half
        quickSort(arr, start, partition - 1);

        // Recursively sort right half
        quickSort(arr, partition + 1, end);
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
        ob.quickSort(arr, 0, arr.size() - 1);

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}