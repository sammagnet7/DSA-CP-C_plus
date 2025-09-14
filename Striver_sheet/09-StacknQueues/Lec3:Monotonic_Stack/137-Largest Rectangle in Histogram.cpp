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

// Approach: 1 : SUB-OPTIMAL

// Time: O(2N+2N+N) ~ O(5N)
// Space: O(N+N+N+N)~O(4    N): 2 vectors for smaller elements + 1 stack
/*
 * contriOfSubarrayMins(vector<int> &arr)
 *
 * Intuition
 * ---------
 * For each element arr[i], we want to know how many subarrays consider arr[i]
 * as their minimum element. This is a common monotonic stack problem.
 *
 * Key idea:
 * - Each element contributes to subarrays where it is the minimum.
 * - To count those subarrays, we need to know:
 *   * The nearest smaller (or smaller-equal) element to the left of i (PSE).
 *   * The nearest smaller element to the right of i (NSE).
 * - With PSE and NSE indices, we can calculate the range in which arr[i] is
 *   the smallest element.
 *
 * Idea
 * ----
 * - Use monotonic stacks to compute:
 *   * pseqe[i]: index of Previous Smaller-or-Equal element for arr[i].
 *   * nse[i]:   index of Next Smaller element for arr[i].
 * - Contribution range of arr[i]:
 *   leftRange  = i - pseqe[i]   (distance from arr[i] back to prev smaller-equal)
 *   rightRange = nse[i] - i     (distance from arr[i] forward to next smaller)
 *
 *   Thus arr[i] contributes to all subarrays that start anywhere in leftRange
 *   choices and end anywhere in rightRange choices.
 *
 * Note:
 * In this code, instead of the standard formula (leftRange * rightRange),
 * the contributionCount is computed using (leftRange + rightRange - 1).
 * This gives a different interpretation (perhaps simplified version or
 * debugging experiment). The typical subarray-minimum count formula uses
 * multiplication.
 *
 * Step-by-step approach
 * ---------------------
 * 1. Initialize arrays:
 *    - contri[i] to store contribution of each element.
 *    - pseqe[i] = -1 (default: no previous smaller-equal).
 *    - nse[i]   = N  (default: no next smaller).
 * 2. Compute pseqe (Previous Smaller-or-Equal index):
 *    - Traverse left-to-right with a monotonic increasing stack.
 *    - For each i, pop while arr[st.top()] > arr[i].
 *    - After popping, top of stack (if exists) is pseqe[i].
 *    - Push i.
 * 3. Clear stack.
 * 4. Compute nse (Next Smaller index):
 *    - Traverse right-to-left with a monotonic increasing stack.
 *    - For each i, pop while arr[st.top()] >= arr[i].
 *    - After popping, top of stack (if exists) is nse[i].
 *    - Push i.
 * 5. Compute contribution for each index i:
 *    - leftRange = i - pseqe[i]
 *    - rightRange = nse[i] - i
 *    - contributionCount = (leftRange + rightRange - 1)   // Note: '+' instead of '*'
 *    - contribution = arr[i] * contributionCount
 *    - store in contri[i].
 * 6. Return contri array.
 *
 * Complexity
 * ----------
 * - Time Complexity:
 *   * First monotonic stack pass (PSE): O(N) amortized.
 *   * Second pass (NSE): O(N) amortized.
 *   * Final contribution calculation: O(N).
 *   Total = O(N).
 *
 * - Space Complexity:
 *   * Extra arrays contri, pseqe, nse of size N each.
 *   * Stack of size up to N.
 *   Total = O(N).
 *
 * Notes
 * -----
 * - Standard "Sum of Subarray Minimums" problem uses multiplication
 *   (leftRange * rightRange) to count subarrays.
 * - This implementation instead uses (leftRange + rightRange - 1), which changes
 *   the interpretation of contribution. Ensure this matches the intended problem.
 */

vector<int> contriOfSubarrayMins(vector<int> &arr)
{
    int N = arr.size();
    vector<int> contri(N); // O(N)

    vector<int> pseqe(N, -1); // O(N): prev smaller-equal element
    vector<int> nse(N, N);    // O(N): next smaller element

    stack<int> st; // O(N): Stack storing indexes

    // Finds prev smaller-equal element using Monotonic stack concept
    //
    for (int i = 0; i < N; i++)
    { // O(2N)
        int cur = arr[i];

        while (!st.empty() && cur<arr[st.top()])
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
        while (!st.empty() && cur<=arr[st.top()])
        { // Note: '>=' because same value elements slope are already considered in pses, no need to consider again.
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

        int leftRange = i - pseqe[i];
        int rightRange = nse[i] - i;

        int contributionCount = (leftRange + rightRange - 1); // Note: the used formula here for contribution count using: '+' not '*'
        int contribution = (arr[i] * contributionCount);

        contri[i] = contribution;
    }

    return contri;
}

// Sub-Optimal approach: Using nse and pse, which takes extra time and space
// Time: O(6N)
// Space: O(4N)
int largestRectangleArea(vector<int> &heights)
{

    vector<int> contributions = contriOfSubarrayMins(heights);

    int maxContri = *max_element(contributions.begin(), contributions.end());

    return maxContri;
}

// -----------------------------------------------
// Approach: 2

// Optimal approach: Finding pse and nse in single pass
// Time: O(2N): stack loop + input array loop
// Space: O(N): stack
/*
 * largestRectangleArea(vector<int> &heights)
 *
 * Intuition
 * ---------
 * For every bar in the histogram, the largest rectangle that uses that bar's
 * height is bounded by the nearest smaller bar to its left (PSE = previous
 * smaller element) and the nearest smaller bar to its right (NSE = next
 * smaller element). If we know these two bounds for a bar at index `i`, the
 * maximum width that bar can span is (NSE - PSE - 1), and the area contributed
 * by that bar is height[i] * (NSE - PSE - 1).
 *
 * Idea
 * ----
 * Compute NSE and PSE for all bars using a single pass with a monotonic
 * increasing stack of indices:
 * - Maintain a stack of indices whose corresponding heights are in (non-strict)
 *   increasing order from bottom to top of the stack.
 * - When we see a new bar with height smaller than the bar at stack.top(), it
 *   means the new bar is the NSE for the top index. Pop the top index and
 *   compute area using the new bar's index as NSE and the new top of stack (if
 *   any) as PSE.
 * - Push the current index and continue.
 * - After the left-to-right pass, any indices remaining in the stack have NSE
 *   = N (end of array), so process them similarly.
 *
 * Step-by-step approach
 * ---------------------
 * 1. Let N = heights.size(), initialize maxi to track the maximum area.
 * 2. Use an empty stack `st` to store indices of bars in increasing height order.
 * 3. Iterate i from 0 to N-1:
 *    a. While stack not empty and heights[st.top()] > heights[i]:
 *       - popped = st.top(); st.pop();
 *       - nextSmaller = i;
 *       - prevSmaller = (st.empty() ? -1 : st.top());
 *       - width = nextSmaller - prevSmaller - 1;
 *       - area = heights[popped] * width; update maxi if area larger.
 *    b. Push current index i onto the stack.
 * 4. After the loop, while stack not empty:
 *    - popped = st.top(); st.pop();
 *    - nextSmaller = N;  // no smaller to the right
 *    - prevSmaller = (st.empty() ? -1 : st.top());
 *    - width = nextSmaller - prevSmaller - 1;
 *    - area = heights[popped] * width; update maxi.
 * 5. Return maxi.
 *
 * Correctness intuition
 * ---------------------
 * For any popped index `p`, all indices between prevSmaller+1 and nextSmaller-1
 * (inclusive) have heights >= heights[p], so a rectangle of height
 * heights[p] and width (nextSmaller - prevSmaller - 1) is valid and maximal
 * for that bar. By processing bars when we first discover their NSE we ensure
 * each bar's maximal span is considered exactly once.
 *
 * Complexity analysis
 * -------------------
 * - Time:
 *   Each index is pushed onto the stack exactly once and popped at most once.
 *   Each push/pop does O(1) work (constant-time arithmetic and comparisons).
 *   Therefore the algorithm performs O(N) stack operations overall (often
 *   described as O(2N) pushes/pops), giving an **amortized time complexity of O(N)**.
 *
 * - Space:
 *   The stack can hold up to N indices in the worst case (strictly increasing
 *   heights), so the extra space used is **O(N)**. Besides the stack, only a
 *   constant number of extra variables are used.
 *
 * Notes / Implementation details
 * ------------------------------
 * - The code uses a strict comparison `heights[st.top()] > heights[i]` so
 *   equal-height bars are not popped on encountering an equal height. Both
 *   strict and non-strict variants are valid; the difference only affects the
 *   tie-breaking semantics for equal heights but not correctness.
 * - If `heights` can be empty, consider initializing `maxi` to 0 and returning 0
 *   for the empty histogram case (current code initializes maxi to INT_MIN).
 */

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
