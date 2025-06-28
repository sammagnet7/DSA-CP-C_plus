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

1. Title: Largest Rectangle in Histogram

Links:
https://takeuforward.org/data-structure/area-of-largest-rectangle-in-histogram/
https://www.youtube.com/watch?v=Bzat9vgD0fs&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=12
https://takeuforward.org/plus/dsa/problems/largest-rectangle-in-a-histogram?tab=editorial
https://leetcode.com/problems/largest-rectangle-in-histogram/description/


Problem statement:
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Examples:
    Example 1:
    Input: heights = [2,1,5,6,2,3]
    Output: 10
    Explanation: The above is a histogram where width of each bar is 1.
    The largest rectangle is shown in the red area, which has an area = 10 units.

    Example 2:
    Input: heights = [2,4]
    Output: 4


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Title: Largest Rectangle in Histogram
// Approach: 1

// // Time: O(2N+2N+N) ~ O(5N)
// // Space: O(N+N+N+N)~O(4    N): 2 vectors for smaller elements + 1 stack
// vector<int> contriOfSubarrayMins(vector<int> &arr)
// {
//     int N = arr.size();
//     vector<int> contri(N);  // O(N)

//     vector<int> pseqe(N, -1); // O(N): prev smaller-equal element
//     vector<int> nse(N, N);    // O(N): next smaller element

//     stack<int> st; // O(N): Stack storing indexes

//     // Finds prev smaller-equal element using Monotonic stack concept
//     //
//     for (int i = 0; i < N; i++)
//     { // O(2N)
//         int cur = arr[i];
//         while (!st.empty() && arr[st.top()] > cur)
//         {             // Note: '>'
//             st.pop(); // storing prev smaller equal elems
//         }
//         if (!st.empty())
//         {
//             pseqe[i] = st.top();
//         }
//         st.push(i); // pushes index
//     }

//     while (!st.empty())
//     { // clearing the left out stack
//         st.pop();
//     }

//     // Finds next smaller element using Monotonic stack concept
//     //
//     for (int i = N - 1; i >= 0; i--)
//     { // O(2N)
//         int cur = arr[i];
//         while (!st.empty() && arr[st.top()] >= cur)
//         { // Note: '>='
//             st.pop();
//         }
//         if (!st.empty())
//         {
//             nse[i] = st.top();
//         }
//         st.push(i); // pushes index
//     }

//     for (int i = 0; i < N; i++)
//     { // O(N)

//         int leftRange = i - pseqe[i];
//         int rightRange = nse[i] - i;

//         int contributionCount = (leftRange + rightRange - 1);   // Note: the used formula here for contribution count using: '+' not '*'
//         int contribution = (arr[i] * contributionCount);

//         contri[i] =  contribution;
//     }

//     return contri;
// }

// // Sub-Optimal approach: Using nse and pse, which takes extra time and space
// // Time: O(6N)
// // Space: O(4N)
// int largestRectangleArea(vector<int>& heights) {

//     vector<int> contributions = contriOfSubarrayMins(heights);

//     int maxContri = *max_element(contributions.begin(), contributions.end());

//     return maxContri;
// }

// -----------------------------------------------
// Approach: 2

// Optimal approach: Finding pse and nse in single pass
// Time: O(2N): stack loop + input array loop
// Space: O(N): stack
int largestRectangleArea(vector<int> &heights)
{

    int N = heights.size();
    int maxi = INT_MIN;

    // vector<int> pse(N); // O(N): stores pse's indexes // not needed as computing on-d-fly
    stack<int> st; // O(N): stores indexes of prev elements

    for (int i = 0; i < N; i++)
    { // O(N)

        while (!st.empty() && heights[st.top()] > heights[i])
        { // O(N): Amortized for N loops

            int pge_id = st.top(); // prev-greater element's index
            st.pop();

            int pge_nse = i; // pge's next-smaller-element is current element
            // int pge_pse = pse[pge_id];  // pge's prev-smaller-element
            int pge_pse = st.empty() ? -1 : st.top(); // the next in stack is  pge's prev-smaller-element

            int range = pge_nse - pge_pse - 1;
            int contri = heights[pge_id] * range;

            maxi = max(maxi, contri);
        }

        // pse[i] = st.empty() ? -1 : st.top(); // not needed as computing on-d-fly
        st.push(i);
    }

    while (!st.empty())
    { // Added as part of prev stack traverse in O(N). N extra time

        int pge_id = st.top(); // prev-greater-equal element's index
        st.pop();

        int pge_nse = N; // prev-greater-equal element's next-smaller-index
        // int pge_pse = pse[pge_id];  // prev-greater-equal element's prev-smaller-index
        int pge_pse = st.empty() ? -1 : st.top();

        int range = pge_nse - pge_pse - 1;
        int contri = heights[pge_id] * range;

        maxi = max(maxi, contri);
    }

    return maxi;
}

int main()
{
    return 0;
}
