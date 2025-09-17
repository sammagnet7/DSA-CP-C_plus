#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/linear-search-in-c/
https://www.geeksforgeeks.org/problems/who-will-win-1587115621/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=who-will-win


Problem Statement: Given an array, arr[] sorted in ascending order and an integer k. Return true if k is present in the array, otherwise, false.

Examples:

Input: arr[] = [1, 2, 3, 4, 6], k = 6
Output: true
Exlpanation: Since, 6 is present in the array at index 4 (0-based indexing), output is true.

Input: arr[] = [1, 2, 4, 5, 6], k = 3
Output: false
Exlpanation: Since, 3 is not present in the array, output is false.

Input: arr[] = [2, 3, 5, 6], k = 1
Output: false

INPUT::::::
3
6
1, 2, 3, 4, 6
3
1, 2, 4, 5, 6
1
2, 3, 5, 6

OUTPUT::::::

true
false
false

 */
class Solution
{
public:
    // Linear search
    bool searchInSorted(vector<int> &arr, int k)
    {

        // Your code here
        int len = arr.size();
        for (int i = 0; i < len; i++)
        {
            if (arr[i] == k)
                return true;
        }
        return false;
    }

    // Binary search
    bool searchInSorted(vector<int> &arr, int k)
    {

        // Your code here
        int len = arr.size();

        return binarySearch(arr, 0, len, k);
    }

    bool binarySearch(vector<int> &arr, int l, int r, int k)
    {

        if (l > r)
            return false;

        int mid = l + (r - l) / 2;

        if (arr[mid] == k)
            return true;
        else if (k < arr[mid])
            binarySearch(arr, l, mid - 1, k);
        else if (arr[mid] < k)
            binarySearch(arr, mid + 1, r, k);
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
        int k = -1;
        cin >> k;
        cin.ignore();

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

        cout << boolalpha;
        cout << ob.searchInSorted(arr, k);

        cout << endl;
    }
}