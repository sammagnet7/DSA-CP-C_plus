#include <iostream>
#include <vector>
#include <climits>
#include <sstream>
#include <cmath>

using namespace std;

/*
Note: https://takeuforward.org/data-structure/merge-two-sorted-arrays-without-extra-space/ (See the 'Optimal approach:2')

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
    /**
     * Shell Sort Algorithm
     * --------------------
     * Idea:
     *  - Shell sort is a generalization of Insertion Sort.
     *  - It improves efficiency by comparing elements far apart (gap) and reducing the gap each pass.
     *  - The idea is to first "pre-sort" the array with large gaps, which reduces the total shifts/swaps needed later.
     *  - Finally, when gap = 1, it essentially runs a standard insertion sort, but the array is already almost sorted.
     *
     * Approach:
     *  - Start with an initial gap (usually N/2).
     *  - Perform a gapped insertion sort for this gap size.
     *  - Keep reducing the gap (commonly halved each time) until gap = 1.
     *
     * Time Complexity:
     *  - Depends on gap sequence used.
     *  - Average: Between O(N log N) and O(N^(3/2)) depending on gap sequence.
     *  - Worst: O(N^2)
     *
     * Space Complexity:
     *  - O(1) (in-place sorting).
     *
     * Stability:
     *  - Not stable (relative order of equal elements may be changed due to gapped swaps).
     *
     * Practical Note:
     *  - Performs better than Bubble Sort and Insertion Sort on medium-sized arrays.
     *  - Not as fast as O(N log N) algorithms like Merge Sort or Quick Sort.
     */
    void shellSort(vector<int> &arr)
    {
        int N = arr.size();

        // Start with a large gap, then reduce gap each iteration
        for (int gap = N / 2; gap > 0; gap /= 2) // approx O(log N) iterations
        {
            // Perform a gapped insertion sort for this gap size
            for (int i = gap; i < N; i++) // For each element from index 'gap' onwards
            {
                int temp = arr[i]; // Save current element
                int j = i;

                // Shift elements that are greater than temp to the right by 'gap'
                while (j >= gap && arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }

                // Place temp at its correct position within this gapped subsequence
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
