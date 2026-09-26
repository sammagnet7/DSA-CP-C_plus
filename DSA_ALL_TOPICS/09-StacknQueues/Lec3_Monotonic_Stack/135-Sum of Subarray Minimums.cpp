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

1. Title: Sum of Subarray Minimums

Links:
https://takeuforward.org/data-structure/trapping-rainwater/
https://takeuforward.org/plus/dsa/problems/sum-of-subarray-minimums?tab=editorial
https://leetcode.com/problems/sum-of-subarray-minimums/description/

Problem statement:
Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:
    Input: arr = [3,1,2,4]
    Output: 17
    Explanation:
    Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
    Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
    Sum is 17.

Example 2:
    Input: arr = [11,81,94,43,3]
    Output: 444

Example 3: **edge case check for duplcate range considering
    Input: arr = [71,55,82,55]
    Output: 593



INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Sum of Subarray Minimums
//

// Optimal approach:
// Approach:
// For each element in the array, find the index of the next smaller element(NSE) to the right. Use a stack to efficiently track these indices.
// For each element in the array, find the index of the previous smaller or equal element(PSEE) to the left. Use a stack to efficiently track these indices.
// For each element in the array, calculate its contribution to the sum of subarray minimums based on its frequency as the minimum in the subarrays. Use the indices from NSE and PSEE to determine the count of subarrays where the current element is the minimum.
// Multiply the frequency obtained by the element's value to get its contribution and add this to the total sum.
//
// Note: here instead of prev-smaller we used **prev smaller-equals** to ignore considering same array twice while duplicate mins are there
//
// Time: O(2N+2N+N) ~ O(5N)
// Space: O(N+N+N)~O(3N): 2 vectors for smaller elements + 1 stack
int sumSubarrayMins(vector<int> &arr)
{
    int ans = 0;
    int moduler = 1e9 + 7;

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

        int leftRange = i - pseqe[i]; // # possible subarray starting points including arr[i]
        int rightRange = nse[i] - i;  // # possible subarray ending points  including arr[i]

        long long contributionCount = ((long long)leftRange * rightRange); // # possible subarrays including arr[i]
        long long contribution = (arr[i] * contributionCount);

        ans = (ans + contribution) % moduler;
    }

    return ans;
}

// Approach: in one loop
int sumSubarrayMins(vector<int> &arr)
{

    int N = arr.size();
    int ans = 0;
    int modulo = 1e9 + 7;

    vector<int> pse(N, -1);
    vector<int> nse(N, N);

    // step 1: previous smaller equals
    stack<pair<int, int>> st; // <value, index>

    // O(N)
    for (int i = 0; i < N; i++)
    {

        if (st.empty())
        {
            st.push({arr[i], i});
            continue;
        }

        while (!st.empty() && st.top().first > arr[i])
        {
            nse[st.top().second] = i;
            st.pop();
        }

        if (!st.empty())
        { // added for pse
            pse[i] = st.top().second;
        }

        st.push({arr[i], i});
    }

    for (int i = 0; i < N; i++)
    {

        int leftRange = i - pse[i];  // # possible subarray starting points including arr[i]
        int rightRange = nse[i] - i; // # possible subarray ending points  including arr[i]

        // cout<<leftRange<< " "<< rightRange<<endl;

        int effectiveRange = leftRange * rightRange; // # possible subarrays including arr[i]

        int contribution = ((long long)effectiveRange * arr[i]) % modulo;

        ans = ((long long)ans + contribution) % modulo;
    }

    return ans;
}

int main()
{
    return 0;
}
