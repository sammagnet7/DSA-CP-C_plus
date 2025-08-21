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

1. Title: Maximal Rectangle
        Maximum Rectangle Area with all 1's | DP on Rectangles: DP 55

Links:
https://youtu.be/ttVu6G7Ayik?si=VBosejklFJNgK3FH
https://takeuforward.org/plus/dsa/problems/maximum-rectangles?tab=editorial
https://leetcode.com/problems/maximal-rectangle/description/

DP : https://www.youtube.com/watch?v=tOylVCugy9k
     https://takeuforward.org/data-structure/maximum-rectangle-area-with-all-1s-dp-on-rectangles-dp-55/


Problem statement:
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Examples:
    Example 1:
    Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
    Output: 6
    Explanation: The maximal rectangle is shown in the above picture.

    Example 2:
    Input: matrix = [["0"]]
    Output: 0

    Example 3:
    Input: matrix = [["1"]]
    Output: 1


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Title: Maximal Rectangle
//           Maximum Rectangle Area with all 1's | DP on Rectangles: DP 55
//------------------------------------------------------------------------

/*
        Function: largestRectangleArea
        --------------------------------------
        Problem:
        Given an array `heights` representing the heights of bars in a histogram,
        return the area of the largest rectangle that can be formed within the histogram.

        Approach:
        - Use a **monotonic increasing stack** to store indices of bars.
        - For each bar:
            1. While the current bar is smaller than the bar at the stack's top:
                - Pop from the stack (this means we found the **next smaller element** for that bar).
                - Calculate the width using the current index as NSE (next smaller element)
                and the new stack top as PSE (previous smaller element).
                - Compute area = height of popped bar * width, update max.
            2. Push the current index into the stack.
        - After iterating through all bars, clear the stack by assuming NSE = N (array end).

        Time Complexity:
        - O(2N) → Each element is pushed and popped at most once.
        - First pass: O(N)
        - Second pass (clearing stack): O(N)

        Space Complexity:
        - O(N) for stack.

        Why O(2N) and not O(N²)?
        - Each index is processed twice at most (push + pop), so total operations = 2N.

    */

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

/*
        Function: maximalRectangle
        --------------------------------------
        Problem:
        Given a binary matrix (M x N), find the area of the largest rectangle containing only 1's.

        Approach:
        - Convert the matrix into a histogram for each row:
            - For each cell (i, j), if matrix[i][j] = 1:
                hist[i][j] = hist[i-1][j] + 1 (stacking the height from the previous row).
            else:
                hist[i][j] = 0.
        - For each row's histogram, compute the largest rectangle using
        the `largestRectangleArea()` function (same as Histogram problem).
        - Take the maximum area across all rows.

        Time Complexity:
        - O(M * N) for building histograms
        - O(M * 2N) for computing largest rectangle for each row
        - Total = O(M * (N + 2N)) = O(M * N)

        Space Complexity:
        - O(M * N) for histogram matrix
        - O(N) for stack used in largestRectangleArea()
    */
// Optimal approach: Uses the method of finding largest area of histograms
//
// Time: O(M*N + M*2N)  where M is #Rows and N is #Cols
// Space: (M*N + N)
int maximalRectangle(vector<vector<char>> &matrix)
{

    int maxArea = INT_MIN;
    int M = matrix.size();    // m rows
    int N = matrix[0].size(); // n cols

    vector<vector<int>> histograms(M, vector<int>(N));

    for (int i = 0; i < M; i++)
    { // O(M*N)
        for (int j = 0; j < N; j++)
        {

            int cur = (matrix[i][j] - '0');

            if (i == 0)
            {
                histograms[i][j] = cur;
            }
            else
            {
                histograms[i][j] = cur == 0 ? 0 : (histograms[i - 1][j] + cur);
            }
        }
    }

    for (auto histRow : histograms)
    {                                                          // O(M)
        maxArea = max(maxArea, largestRectangleArea(histRow)); // O(2N)
    }

    return maxArea;
}

int main()
{
    return 0;
}
