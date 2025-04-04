#include <iostream>
#include <vector>
#include <climits>
#include <sstream>
#include <cmath>

using namespace std;

/*
https://takeuforward.org/data-structure/merge-two-sorted-arrays-without-extra-space/ (See the 'Optimal approach:2')
https://leetcode.com/problems/sort-an-array/description/

Problem:  Given an array of n integers, sort the array using the ShellSort method.

Examples:

Example 1:
Input: N=5, arr[]={4,2,1,6,7}
Output: 1,2,4,6,7,

Example 2:
Input: N=7,arr[]={3,2,8,5,1,4,23}
Output: 1,2,3,4,5,8,23


INPUT::::::
2
4 2 1 6 7
3 2 8 5 1 4 23

OUTPUT::::::



*/
class Solution
{
public:
    // Approach: Follows `SHELL SORT` inplace sorting algorithm based upon `GAP`
    // Time: Avg(N Log N); O(N^2)
    // Space: O(1)
    // Not stable sort
    // Better than Bubble and Insertion sort for medium sized array
    void shellSort(vector<int> &arr)
    {
        int N = arr.size();
        for (int gap = N / 2; gap > 0; gap /= 2) // O(log N)
        {
            for (int i = gap; i < N; i++) // O(N)
            {
                int temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
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
        ob.shellSort(arr);

        for (auto i : arr)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}