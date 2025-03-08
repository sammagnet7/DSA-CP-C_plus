#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/find-the-largest-element-in-an-array/
https://www.geeksforgeeks.org/problems/largest-element-in-array4009/0?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=largest-element-in-array
https://www.naukri.com/code360/problems/largest-element-in-the-array-largest-element-in-the-array_5026279?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem:  Given an array, we have to find the largest element in the array.


Examples:

Example 1:
Input:
 arr[] = {2,5,1,3,0};
Output:
 5
Explanation:
 5 is the largest element in the array.

Example2:
Input:
 arr[] = {8,10,5,7,9};
Output:
 10
Explanation:
 10 is the largest element in the array.


Intuition:


*/
class Solution
{
public:
    // Time: O(N)
    // Space: O(N)
    // Taking Last element as Pivot
    int doPartition(vector<int> &arr, int start, int end)
    {

        int pivot = arr[end];
        int pivotidx = end;
        int partitionIdx = -1;
        int l = start, r = end;

        while (l < r)
        {
            while (arr[l] <= pivot && l < r)
                l++;
            while (arr[r] >= pivot && l < r)
                r--;

            if (l < r)
                swap(arr[l], arr[r]);
        }

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

    // Time: O(N Log N)
    // Space: O(N)
    void quickSort(vector<int> &arr, int start, int end)
    {

        if (start >= end)
            return;

        int partition = 0;

        partition = doPartition(arr, start, end);

        quickSort(arr, start, partition - 1);
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