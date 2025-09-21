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
    /**
     * Max Sum of Two Consecutive Elements
     * ----------------------------------
     * Problem:
     *  - Find the maximum sum of any two consecutive elements in the array.
     *
     * Approach (expected / intuitive):
     *  - If there exists an optimal pair (x, y) giving the maximum sum, then
     *    x and y must be adjacent in the array.
     *  - Proof sketch:
     *      * Suppose x and y are not adjacent. Let the segment between them
     *        contain one or more elements. If there is exactly one element z
     *        between them, then max(x,y) + z >= x + y, so a neighboring pair
     *        that includes z gives an equal or larger sum.
     *      * If there are multiple elements between them, by considering adjacent
     *        pairs inside that gap we can show some adjacent pair gives a sum
     *        at least x + y. Hence an optimal pair can always be found among
     *        adjacent elements.
     *  - Therefore it suffices to scan the array and take the maximum of arr[i] + arr[i+1].
     *
     * Complexity:
     *  - Time:  O(n)   (single pass comparing adjacent pairs)
     *  - Space: O(1)   (constant extra space)
     *
     * Notes:
     *  - If the array length is < 2 there is no valid pair; this implementation
     *    returns INT_MIN as a sentinel. Change this sentinel if you prefer another behavior.
     */
    int pairWithMaxSum(vector<int> &arr)
    {
        int n = arr.size();

        // Guard: no valid pair if fewer than 2 elements
        if (n < 2)
            return INT_MIN;

        int best = INT_MIN;

        // Check every adjacent pair and keep the maximum sum
        for (int i = 0; i + 1 < n; ++i)
        {
            // sum of the pair arr[i] and arr[i+1]
            int s = arr[i] + arr[i + 1];
            if (s > best)
                best = s;
        }

        return best;
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