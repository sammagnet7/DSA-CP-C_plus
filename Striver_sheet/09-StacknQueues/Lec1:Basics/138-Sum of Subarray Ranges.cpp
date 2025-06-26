#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_set>
#include <stack>
#include <string.h>

using namespace std;

/*

1. Title: Sum of Subarray Ranges

Links:
https://www.youtube.com/watch?v=gIrMptNPf5M&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=10
https://leetcode.com/problems/sum-of-subarray-ranges/description/


Problem statement:
You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
Return the sum of all subarray ranges of nums.
A subarray is a contiguous non-empty sequence of elements within an array.


Examples:
    Example 1:
    Input: nums = [1,2,3]
    Output: 4
    Explanation: The 6 subarrays of nums are the following:
    [1], range = largest - smallest = 1 - 1 = 0
    [2], range = 2 - 2 = 0
    [3], range = 3 - 3 = 0
    [1,2], range = 2 - 1 = 1
    [2,3], range = 3 - 2 = 1
    [1,2,3], range = 3 - 1 = 2
    So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.

    Example 2:
    Input: nums = [1,3,3]
    Output: 4
    Explanation: The 6 subarrays of nums are the following:
    [1], range = largest - smallest = 1 - 1 = 0
    [3], range = 3 - 3 = 0
    [3], range = 3 - 3 = 0
    [1,3], range = 3 - 1 = 2
    [3,3], range = 3 - 3 = 0
    [1,3,3], range = 3 - 1 = 2
    So the sum of all ranges is 0 + 0 + 0 + 2 + 0 + 2 = 4.

    Example 3:
    Input: nums = [4,-2,-3,4,1]
    Output: 59
    Explanation: The sum of all subarray ranges of nums is 59.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Sum of Subarray Ranges
//

// Time: O(2N+2N+N) ~ O(5N)
// Space: O(N+N+N)~O(3N): 2 vectors for smaller elements + 1 stack
long long sumSubarrayMins(vector<int> &arr)
{
    long long ans = 0;

    int N = arr.size();
    vector<int> pseqe(N, -1); // O(N): prev smaller-equal element
    vector<int> nse(N, N);    // O(N): next smaller element

    stack<int> st; // O(N): Stack storing indexes

    // Finds prev smaller-equal element using Monotonic stack concept
    //
    for (int i = 0; i < N; i++)
    { // O(2N)
        int cur = arr[i];
        while (!st.empty() && arr[st.top()] > cur)
        {             // Note: '>'
            st.pop(); // storing prev smaller equal elems
        }
        if (!st.empty())
        {
            pseqe[i] = st.top();
        }
        st.push(i); // pushes index
    }

    while (!st.empty())
    { // clearing the left out stack
        st.pop();
    }

    // Finds next smaller element using Monotonic stack concept
    //
    for (int i = N - 1; i >= 0; i--)
    { // O(2N)
        int cur = arr[i];
        while (!st.empty() && arr[st.top()] >= cur)
        { // Note: '>='
            st.pop();
        }
        if (!st.empty())
        {
            nse[i] = st.top();
        }
        st.push(i); // pushes index
    }

    for (int i = 0; i < N; i++)
    { // O(N)

        long long leftRange = i - pseqe[i];
        long long rightRange = nse[i] - i;

        long long contributionCount = ((long long)leftRange * rightRange);
        long long contribution = (arr[i] * contributionCount);

        ans = (ans + contribution);
    }

    return ans;
}

// Time: O(2N+2N+N) ~ O(5N)
// Space: O(N+N+N)~O(3N): 2 vectors for smaller elements + 1 stack
long long sumSubarrayMaxs(vector<int> &arr)
{
    long long ans = 0;

    int N = arr.size();
    vector<int> pgeqe(N, -1); // O(N): prev greater-equal element
    vector<int> nge(N, N);    // O(N): next greater element

    stack<int> st; // O(N): Stack storing indexes

    // Finds prev greater-equal element using Monotonic stack concept
    //
    for (int i = 0; i < N; i++)
    { // O(2N)
        int cur = arr[i];
        while (!st.empty() && arr[st.top()] < cur)
        {             // Note: '<'
            st.pop(); // storing prev smaller equal elems
        }
        if (!st.empty())
        {
            pgeqe[i] = st.top();
        }
        st.push(i); // pushes index
    }

    while (!st.empty())
    { // clearing the left out stack
        st.pop();
    }

    // Finds next smaller element using Monotonic stack concept
    //
    for (int i = N - 1; i >= 0; i--)
    { // O(2N)
        int cur = arr[i];
        while (!st.empty() && arr[st.top()] <= cur)
        { // Note: '>='
            st.pop();
        }
        if (!st.empty())
        {
            nge[i] = st.top();
        }
        st.push(i); // pushes index
    }

    for (int i = 0; i < N; i++)
    { // O(N)

        long long leftRange = i - pgeqe[i];
        long long rightRange = nge[i] - i;

        long long contributionCount = ((long long)leftRange * rightRange);
        long long contribution = (arr[i] * contributionCount);

        ans = (ans + contribution);
    }

    return ans;
}

// Optmial approach: sumSubarrayMaxs - sumSubarrayMins : Uses monotonic stack
// As the sum of all subarray ranges = sum of all subarray max - sum of all subarray min
//
// Time: O(10N)
// Space: O(6N)
long long subArrayRanges(vector<int> &nums)
{

    long long sumOfSubarrayMaxs = sumSubarrayMaxs(nums);
    long long sumOfSubarrayMins = sumSubarrayMins(nums);

    return (sumOfSubarrayMaxs - sumOfSubarrayMins);
}

int main()
{
    return 0;
}
