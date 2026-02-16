#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/merge-sort-algorithm/
https://www.geeksforgeeks.org/problems/merge-sort/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=merge-sort


Problem:  Given an array of size n, sort the array using Merge Sort.

Examples:

Example 1:
Input: N=5, arr[]={4,2,1,6,7}
Output: 1,2,4,6,7,

Example 2:
Input: N=7,arr[]={3,2,8,5,1,4,23}
Output: 1,2,3,4,5,8,23


Intuition:

Merge Sort is a divide and conquers algorithm, it divides the given array into equal parts and then merges the 2 sorted parts.
There are 2 main functions :
merge(): This function is used to merge the 2 halves of the array. It assumes that both parts of the array are sorted and merges both of them.
mergeSort(): This function divides the array into 2 parts. low to mid and mid+1 to high where,

 low = leftmost index of the array
 high = rightmost index of the array
 mid = Middle index of the array


INPUT::::::
2
4 2 1 6 7
3 2 8 5 1 4 23

OUTPUT::::::

1 2 4 6 7
1 2 3 4 5 8 23

*/
class Solution
{
public:
    // // Time: O(N)
    // // Space: O(N)
    // void merge(vector<int> &arr, int low, int mid, int high)
    // {
    //     vector<int> temp;
    //     int l = low, r = mid + 1;

    //     while (l <= mid && r <= high)
    //     {
    //         if (arr[l] <= arr[r])
    //             temp.push_back(arr[l++]);
    //         else
    //             temp.push_back(arr[r++]);
    //     }

    //     while (l <= mid)
    //     {
    //         temp.push_back(arr[l++]);
    //     }

    //     while (r <= high)
    //     {
    //         temp.push_back(arr[r++]);
    //     }

    //     for (int i = 0; i <= (high - low); i++)
    //     {
    //         arr[low + i] = temp[i];
    //     }
    // }

    /**
     * Merge Function
     * --------------
     * Purpose:
     *  - Merge two sorted halves of the array (arr[start..mid] and arr[mid+1..end])
     *    into a single sorted subarray in arr[start..end].
     *
     * Time Complexity: O(N)   [each element in the range is processed once]
     * Space Complexity: O(N)  [temporary arrays for left and right halves]
     */
    void merge(vector<int> &arr, int start, int mid, int end)
    {
        // Create temporary arrays to hold left and right halves
        vector<int> temp1(mid - start + 1), temp2(end - mid);

        // Copy elements from arr[start..mid] into temp1
        for (int i = start; i <= mid; i++)
        {
            temp1[i - start] = arr[i];
        }

        // Copy elements from arr[mid+1..end] into temp2
        for (int i = mid + 1; i <= end; i++)
        {
            temp2[i - mid - 1] = arr[i];
        }

        // Merge temp1[] and temp2[] back into arr[]
        int l = 0;     // pointer for temp1
        int r = 0;     // pointer for temp2
        int c = start; // pointer for arr
        int s1 = temp1.size();
        int s2 = temp2.size();

        // Compare elements from both temp arrays and insert the smaller one into arr
        while (l < s1 && r < s2)
        {
            if (temp1[l] <= temp2[r])
            {
                arr[c++] = temp1[l++];
            }
            else
            {
                arr[c++] = temp2[r++];
            }
        }

        // Copy any remaining elements from temp1
        while (l < s1)
        {
            arr[c++] = temp1[l++];
        }

        // Copy any remaining elements from temp2
        while (r < s2)
        {
            arr[c++] = temp2[r++];
        }
    }

    /**
     * Merge Sort Algorithm
     * --------------------
     * Idea:
     *  - Divide the array into two halves.
     *  - Recursively sort each half.
     *  - Merge the two sorted halves.
     *
     * Time Complexity:
     *  - O(N log N) for all cases (divide: log N levels, merge: O(N) per level)
     *
     * Space Complexity:
     *  - O(N) extra space for temporary arrays used during merging
     *
     * Stability:
     *  - Stable (preserves relative order of equal elements).
     */
    void mergeSort(vector<int> &arr, int low, int high)
    {
        // Base case: if array has 1 or 0 elements, it's already sorted
        if (low >= high)
            return;

        // Compute mid-point carefully to avoid overflow
        int mid = low + (high - low) / 2;

        // Recursively sort left half
        mergeSort(arr, low, mid);

        // Recursively sort right half
        mergeSort(arr, mid + 1, high);

        // Merge the two sorted halves
        merge(arr, low, mid, high);
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
        ob.mergeSort(arr, 0, arr.size() - 1);

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}