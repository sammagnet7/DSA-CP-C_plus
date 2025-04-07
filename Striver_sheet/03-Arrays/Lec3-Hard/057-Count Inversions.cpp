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
    // Approach: OPTIMAL: Follows mergeSort() algo
    // Intuition: If two sorted arrays are given then, finding inversionCount takes O(N) time.
    // because whenever we find leftSortedArray[i] > rightSortedArray[j], we know all the elements further right in the leftSortedArray also will be greater than rightSortedArray[j] element(as arrays are sorted)
    // So in that case we could easily compute inversionCount as (leftSortedArraySize - i).
    // And can find overall inversionCount in O(N)
    //
    // Now to utilize this we need to feed two sorted arrays, which is done by Divide-and-Conquer strategy in O(Log N) time
    //
    // Time: O(N Log N)
    // Space: O(N)
    int inversionCount(vector<int> &arr)
    {
        int N = arr.size();

        return mergeSort(arr, 0, N - 1);
    }

private:
    // O(N Log N)
    int mergeSort(vector<int> &arr, int start, int end)
    {
        if (start >= end)
            return 0;
        int inversionCount = 0;

        int mid = start - (start - end) / 2;

        inversionCount += mergeSort(arr, start, mid);
        inversionCount += mergeSort(arr, mid + 1, end);

        // inversionCount += countInversions(arr, start, end, mid);
        inversionCount += mergeAndCountInversions(arr, start, end, mid);

        return inversionCount;
    }

    // O(N)
    int mergeAndCountInversions(vector<int> &arr, int start, int end, int mid)
    {
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

        int l = 0;
        int r = 0;
        int c = start;
        int s1 = temp1.size();
        int s2 = temp2.size();

        while (l < s1 && r < s2)
        {
            if (temp1[l] <= temp2[r])
            {
                arr[c] = temp1[l];
                c++;
                l++;
            }
            else if (temp1[l] > temp2[r])
            {
                inversionCount += s1 - l; // Counting inversions when lsftArray element is greater than rightArray element
                arr[c] = temp2[r];
                c++;
                r++;
            }
        }
        while (l < s1)
        {
            arr[c] = temp1[l];
            c++;
            l++;
        }
        while (r < s2)
        {
            arr[c] = temp2[r];
            c++;
            r++;
        }

        return inversionCount;
    }

    // REVERSE PAIRs
    // This method will be used to 'Count Reverse Pairs': https://takeuforward.org/data-structure/count-reverse-pairs/
    // Reverse Pairs are those pairs where i<j and arr[i]>2*arr[j]
    // So inside merge algo we can not count Reverse pair. Because if temp1[l]>temp2[r] => we can not simply inversionCount++ => we do r++ => but there can be possible elements in temp1 where temp1[l++]>2*temp2[r], which we missed in merge algo
    // So we need this explicit method to return `inversionCount` and merge algo will return void
    // Time: O(N)
    // Space: O(1)
    int countInversions(vector<int> &arr, int start, int end, int mid){
        int inversions=0;
        int l=start, r=mid+1;

        while(l<=mid && r<=end){
            if((long long)arr[l] > (2*(long long)arr[r]) ){
                inversions += (mid-l+1);
                r++;
            }
            else {
                l++;
            }
        }

        return inversions;
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

        cout << ob.inversionCount(arr);
        cout << endl;
    }
    return 0;
}