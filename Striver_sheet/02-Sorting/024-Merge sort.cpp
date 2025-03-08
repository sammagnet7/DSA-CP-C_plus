#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/merge-sort-algorithm/

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
*/
class Solution
{
public:
    // Time: O(N)
    // Space: O(N)
    void merge(vector<int> &arr, int low, int mid, int high)
    {
        vector<int> temp;
        int l = low, r = mid + 1;

        while (l <= mid && r <= high)
        {
            if (arr[l] <= arr[r])
                temp.push_back(arr[l++]);
            else
                temp.push_back(arr[r++]);
        }

        while (l <= mid)
        {
            temp.push_back(arr[l++]);
        }

        while (r <= high)
        {
            temp.push_back(arr[r++]);
        }

        for (int i = 0; i <= (high - low); i++)
        {
            arr[low + i] = temp[i];
        }
    }

    // Time: O(N Log N)
    // Space: O(N)
    void mergeSort(vector<int> &arr, int low, int high)
    {

        if (low >= high)
            return;

        int mid = low - (low - high) / 2; // Trick to avoid integer overflow

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

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