#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Count inversions in an array

https://takeuforward.org/data-structure/count-inversions-in-an-array/
https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=inversion-of-array
https://www.naukri.com/code360/problems/number-of-inversions_6840276?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_Arrayproblems


Problem statement:
Given an array of N integers, count the inversion of the array

Note: What is an inversion of an array? Definition: for all i & j < size of array, if i < j then you have to find pair (A[i],A[j]) such that A[j] < A[i].

Examples:

Example 1:
Input Format: N = 5, array[] = {1,2,3,4,5}
Result: 0
Explanation: we have a sorted array and the sorted array has 0 inversions as for i < j you will never find a pair such that A[j] < A[i]. More clear example: 2 has index 1 and 5 has index 4 now 1 < 5 but 2 < 5 so this is not an inversion.

Example 2:
Input Format: N = 5, array[] = {5,4,3,2,1}
Result: 10
Explanation: we have a reverse sorted array and we will get the maximum inversions as for i < j we will always find a pair such that A[j] < A[i]. Example: 5 has index 0 and 3 has index 2 now (5,3) pair is inversion as 0 < 2 and 5 > 3 which will satisfy out conditions and for reverse sorted array we will get maximum inversions and that is (n)*(n-1) / 2.For above given array there is 4 + 3 + 2 + 1 = 10 inversions.

Example 3:
Input Format: N = 5, array[] = {5,3,2,1,4}
Result: 7
Explanation: There are 7 pairs (5,1), (5,3), (5,2), (5,4),(3,2), (3,1), (2,1) and we have left 2 pairs (2,4) and (1,4) as both are not satisfy our condition.


INPUT::::::
3
1 2 3 4 5
5 4 3 2 1
5 3 2 1 4

OUTPUT::::::
0
10
7

 */
class Solution
{
public:
    /*
        Problem:
            - Given an array arr[0..n-1].
            - Count the number of inversions in the array.
            - An inversion is a pair (i, j) such that i < j and arr[i] > arr[j].

        Approach:
            - Use modified merge sort.
            - During the merge step, whenever we take an element from the right half
            before one from the left half, it means all remaining elements in the left
            half form inversions with that right element.
            - Merge sort splits array recursively (O(log n) levels),
            and each merge operation scans its subarrays linearly (O(n) per level).
            - Total time complexity = O(n log n).

        Key intuition:
            - Brute force: O(n^2) checking all pairs.
            - Optimized: Merge sort naturally compares left and right halves.
            - When left[l] > right[r]:
                * Because both halves are sorted, all elements left[l..end] are also > right[r].
                * So we can count all those inversions in O(1).
            - This reduces repeated comparisons.

        Functions:
            1. mergeAndCountInversions:
                - Merges two sorted halves arr[start..mid] and arr[mid+1..end].
                - While merging:
                    * If left[l] <= right[r], copy left[l].
                    * Else left[l] > right[r], so (mid - l + 1) inversions exist.
                    * Copy right[r].
                - Returns number of inversions during merge.

            2. mergeSort:
                - Standard recursive merge sort.
                - Splits array, recursively sorts left and right.
                - Counts inversions in left, right, and across them using mergeAndCountInversions.

            3. numberOfInversions:
                - Wrapper function that makes a copy of arr to avoid modifying the input.
                - Calls mergeSort and returns the inversion count.

        Complexity:
            - mergeAndCountInversions: O(n) per merge.
            - mergeSort: O(n log n) overall.
            - Space: O(n) auxiliary for temporary arrays.
    */

    // Merge step: merges two sorted halves and counts inversions
    int mergeAndCountInversions(vector<int> &arr, int start, int end, int mid)
    {
        // Copy left and right halves into temp arrays
        vector<int> temp1(mid - start + 1), temp2(end - mid);
        for (int i = start; i <= mid; i++)
        {
            temp1[i - start] = arr[i];
        }
        for (int i = mid + 1; i <= end; i++)
        {
            temp2[i - mid - 1] = arr[i];
        }

        int inversionCount = 0;
        int l = 0, r = 0, c = start;
        int s1 = temp1.size(), s2 = temp2.size();

        // Merge while counting inversions
        while (l < s1 && r < s2)
        {
            if (temp1[l] <= temp2[r])
            {
                arr[c++] = temp1[l++];
            }
            else
            {
                // temp1[l] > temp2[r] ⇒ all remaining elements in temp1[l..end] are > temp2[r]
                inversionCount += (s1 - l);
                arr[c++] = temp2[r++];
            }
        }

        // Copy leftovers
        while (l < s1)
            arr[c++] = temp1[l++];
        while (r < s2)
            arr[c++] = temp2[r++];

        return inversionCount;
    }

    // Recursive merge sort with inversion count
    int mergeSort(vector<int> &arr, int start, int end)
    {
        if (start >= end)
            return 0;

        int inversionCount = 0;
        int mid = start + (end - start) / 2;

        // Count inversions in left half
        inversionCount += mergeSort(arr, start, mid);

        // Count inversions in right half
        inversionCount += mergeSort(arr, mid + 1, end);

        // Count inversions across halves
        inversionCount += mergeAndCountInversions(arr, start, end, mid);

        return inversionCount;
    }

    // Wrapper to count inversions in the array
    int numberOfInversions(vector<int> &arr, int n)
    {
        vector<int> workArr(arr.begin(), arr.end()); // copy to avoid modifying original
        return mergeSort(workArr, 0, n - 1);
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        string input;
        getline(cin, input);

        vector<int> arr;
        stringstream ss(input);
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.numberOfInversions(arr, arr.size());
        cout << endl;
    }
    return 0;
}