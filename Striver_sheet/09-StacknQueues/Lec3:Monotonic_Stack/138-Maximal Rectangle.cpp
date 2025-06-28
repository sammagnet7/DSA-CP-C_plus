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

Links:
https://youtu.be/ttVu6G7Ayik?si=VBosejklFJNgK3FH
https://takeuforward.org/plus/dsa/problems/maximum-rectangles?tab=editorial
https://leetcode.com/problems/maximal-rectangle/description/


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
//

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
