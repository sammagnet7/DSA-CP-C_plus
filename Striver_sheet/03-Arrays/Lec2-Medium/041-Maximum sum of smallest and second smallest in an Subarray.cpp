#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Maximum sum of smallest and second smallest in an Subarray

https://www.geeksforgeeks.org/maximum-sum-of-smallest-and-second-smallest-in-an-array/
https://www.geeksforgeeks.org/problems/max-sum-in-sub-arrays0824/0?category&utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=max-sum-in-sub-arrays

Problem Statement: Given an array arr[] of size n, the task is to find the maximum sum of the smallest and second smallest elements among all possible subarrays of size greater than equals to two.

Note: A subarray is a contiguous segment of an array. In other words, a subarray can be formed by removing 0 or more integers from the beginning and 0 or more integers from the end of an array.
Find the sum of the subarray (including empty subarray) having maximum sum among all subarrays.
The sum of an empty subarray is 0.

Examples:

Example 1:
Input : arr[] = [4, 3, 1, 5, 6]
Output : 11
Explanation : Subarrays with smallest and second smallest are:- [4, 3] smallest = 3,second smallest = 4
[4, 3, 1] smallest = 1, second smallest = 3
[4, 3, 1, 5] smallest = 1, second smallest = 3
[4, 3, 1, 5, 6] smallest = 1, second smallest = 3
[3, 1] smallest = 1, second smallest = 3
[3, 1, 5] smallest = 1, second smallest = 3
[3, 1, 5, 6] smallest = 1, second smallest = 3
[1, 5] smallest = 1, second smallest = 5
[1, 5, 6] smallest = 1, second smallest = 5
[5, 6] smallest = 5, second smallest = 6
Maximum sum among all above choices is, 5 + 6 = 11.


INPUT::::::
2
4 3 1 5 6
5 4 3 1 6

OUTPUT::::::

11
9
 */
class Solution
{
public:
    /*
    [Expected Approach] By maximizing consecutive element sum – O(n) time and O(1) auxiliary space
    An efficient solution is based on the observation that this problem reduces to finding a maximum sum of two consecutive elements in array. If (x,y) is the pair such that (x+y) is the answer, then x and y must be consecutive elements in the array.

    For a subarray with 2 elements, 1st and 2nd smallest elements are those 2 elements. Now, x and y are present in some subarray such that they are the endpoints. Now, x, y must be the smallest 2 elements of that subarray. If there are other elements Z1 , Z2, ……., ZK  between x and y, they are greater than or equal to x and y,

    Case1 :
    If there is one element z between x and y, then the smaller subarray with the elements max(x,y) and z , should be the answer, because max(x,y) + z >= x + y
    Case2:
    If there are more than one elements between x and y, then the subarray within x and y will have all consecutive elements  (Zi + Zi+1) >= (x+y),  so (x,y) pair can’t be the answer.
So, by contradictions, x and y must be consecutive elements in the array.
    */
    int pairWithMaxSum(vector<int> &arr)
    {
        // Your code goes here

        int maxi = 0;

        for (int i = 0; i < arr.size() - 1; i++)
        {

            if (arr[i] + arr[i + 1] > maxi)
                maxi = arr[i] + arr[i + 1];
        }
        return maxi;
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
        // int k;
        // cin >> k;
        // cin.ignore();

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

        cout << ob.pairWithMaxSum(arr);

        cout << endl;
    }
}