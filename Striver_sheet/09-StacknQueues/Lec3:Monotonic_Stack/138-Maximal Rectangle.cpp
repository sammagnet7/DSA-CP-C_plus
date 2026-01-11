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

//=======================================================================
// 1. Title: Maximum Rectangle Area with all 1's
//=======================================================================

//------------------------------------------------------------------------
// Approach 1: DP + Monotonic Stack  [3 pass for finding pse+nse+maxArea]
//------------------------------------------------------------------------

class Solution
{
public:
    /*
     * METHOD: largestRectangleArea
     * ----------------------------
     * IDEA:
     * This helper function solves the "Largest Rectangle in Histogram" problem.
     * For a given row of heights, the largest rectangle is determined by the "limiting"
     * bar height. For any specific bar 'h', the widest rectangle using 'h' as the full
     * height extends to the left until it hits a smaller bar (Previous Smaller Element)
     * and to the right until it hits a smaller bar (Next Smaller Element).
     * * APPROACH:
     * 1. Monotonic Stack (2 Passes):
     * - Pass 1: Find Previous Smaller Element (PSE) index for every bar.
     * - Pass 2: Find Next Smaller (or Equal) Element (NSE) index for every bar.
     * 2. Calculate Area:
     * - Width = (Right Boundary - Left Boundary - 1)
     * - Area = Width * Height
     * * COMPLEXITY:
     * Time: O(N) - We traverse the histogram 3 times (PSE loop, NSE loop, Calculation loop).
     * Stack operations are amortized O(1).
     * Space: O(N) - Used for PSE array, NSE array, and Stack.
     */
    int largestRectangleArea(vector<int> &histogram)
    {

        int N = histogram.size();

        // PSIdx[i]: Index of the first element to the LEFT smaller than histogram[i]
        vector<int> PSIdx(N, -1); // Init to -1 (imaginary boundary before index 0)

        // NSEqIdx[i]: Index of the first element to the RIGHT smaller than histogram[i]
        vector<int> NSEqIdx(N, N); // Init to N (imaginary boundary after last index)

        stack<int> st; // Stores indices of the histogram bars

        // ---------------------------------------------------------
        // Step 1: Create the Previous Smaller Elements (PSE) array
        // ---------------------------------------------------------
        for (int i = 0; i < N; i++)
        {

            int cur = histogram[i];

            // Monotonic Stack Logic:
            // Remove elements from stack that are greater or equal to current('>=').
            // We want to find the first one strictly smaller to the left.
            while (!st.empty() && histogram[st.top()] >= cur)
            {
                st.pop();
            }

            if (!st.empty())
            {
                PSIdx[i] = st.top(); // Found the boundary on the left
            }
            // Else, PSIdx[i] remains -1 (default)

            st.push(i);
        }

        // Clear stack for reuse in next step
        while (!st.empty())
        {
            st.pop();
        }

        // ---------------------------------------------------------
        // Step 2: Create the Next Smaller Elements (NSE) array
        // ---------------------------------------------------------
        // We traverse from Right to Left to find the right boundary
        for (int j = N - 1; j >= 0; j--)
        {

            int cur = histogram[j];

            // Remove elements that are strictly greater('>').
            // Note: Handling duplicates carefully ensures we don't double count,
            // though exact strictness varies by implementation.
            while (!st.empty() && histogram[st.top()] > cur)
            {
                st.pop();
            }

            if (!st.empty())
            {
                NSEqIdx[j] = st.top(); // Found the boundary on the right
            }
            // Else, NSEqIdx[j] remains N (default)

            st.push(j);
        }

        int largestArea = 0;

        // ---------------------------------------------------------
        // Step 3: Calculate area for every bar to find the maximum
        // ---------------------------------------------------------
        for (int k = 0; k < N; k++)
        {

            // Optimization: If height is 0, it cannot form a rectangle
            if (histogram[k] == 0)
            {
                continue;
            }

            // Formula: Width = Right Boundary - Left Boundary - 1
            // Example: Limits are indices 1 and 5. Width is range [2,3,4], size 3.
            // Calculation: 5 - 1 - 1 = 3.
            int curLength = NSEqIdx[k] - PSIdx[k] - 1;
            int curHeight = histogram[k];

            int curArea = curLength * curHeight;

            largestArea = max(largestArea, curArea);
        }

        return largestArea;
    }

    /*
     * METHOD: maximalRectangle
     * ------------------------
     * IDEA:
     * We convert the 2D binary matrix into a series of 1D histograms.
     * We iterate through the matrix row by row. For each row, we treat it as
     * the "ground" and calculate the height of consecutive 1s above it.
     * Then we solve the "Largest Rectangle in Histogram" problem for that row.
     * * COMPLEXITY:
     * Time: O(Rows * Cols)
     * - We iterate every cell once to build histograms: O(Rows * Cols)
     * - We call largestRectangleArea (O(Cols)) for each Row: O(Rows * Cols)
     * Space: O(Cols)
     * - We only need one 1D array of size Cols to store the running heights.
     */
    int maximalRectangle(vector<vector<char>> &matrix)
    {

        if (matrix.empty())
            return 0;

        int M = matrix.size();
        int N = matrix[0].size();

        // Stores the height of consecutive 1s for the current row
        vector<int> histogram(N, 0);
        int maxRectangle = 0;

        // Traverse every row
        for (int i = 0; i < M; i++)
        {
            // Update the histogram for the current row
            for (int j = 0; j < N; j++)
            {

                if (matrix[i][j] == '0')
                {
                    // If current cell is 0, the continuous vertical strip breaks.
                    // Height becomes 0.
                    histogram[j] = 0;
                }
                else
                {
                    // If current cell is 1, we extend the height from the previous row.
                    histogram[j] = histogram[j] + 1;
                }
            }

            // For this updated histogram (representing the matrix up to row i),
            // find the largest rectangle.
            maxRectangle = max(maxRectangle, largestRectangleArea(histogram));
        }

        return maxRectangle;
    }
};

//------------------------------------------------------------------------
// Approach 2: DP + Monotonic Stack  [1 pass for finding pse+nse+maxArea]
//------------------------------------------------------------------------

class Solution
{
public:
    /*
     * METHOD: largestRectangleArea
     * ----------------------------
     * IDEA:
     * This method uses a SINGLE-PASS Monotonic Stack approach (optimized from the 2-pass version).
     * Instead of pre-calculating PSE (Previous Smaller) and NSE (Next Smaller) arrays separately,
     * we calculate the area *during* the traversal.
     * * * LOGIC:
     * 1. We maintain a stack of indices with increasing heights.
     * 2. When we encounter a bar (cur) smaller than the bar at stack.top(), it means we have found
     * the "Next Smaller Element" (Right Boundary) for the bar at stack.top().
     * 3. At that moment, we pop the top element. This popped element is the 'height'.
     * 4. The 'width' is determined by:
     * - Right Boundary: The current index 'i' (which triggered the pop).
     * - Left Boundary: The *new* stack.top() after popping (Previous Smaller Element).
     * * * COMPLEXITY:
     * Time: O(N) - Each element is pushed and popped exactly once.
     * Space: O(N) - For the stack in the worst case (ascending order input).
     */
    int largestRectangleArea(vector<int> &histogram)
    {

        int N = histogram.size();
        stack<int> st; // Stores indices of the histogram bars (strictly increasing order of height)
        int largestArea = 0;

        for (int i = 0; i <= N; i++)
        {
            // We iterate up to N.
            // The (i == n) case acts as a dummy '0' height bar
            // Forces the stack to empty at the end.
            // To avoid extra code block to empty the stack (commented out next)
            int cur = (i == N) ? 0 : histogram[i];

            // If current bar is smaller than stack top, the stack top's right boundary is found.
            // We must resolve (calculate area for) all bars in stack that are taller than 'cur'.
            while (!st.empty() && histogram[st.top()] >= cur)
            {

                int el = histogram[st.top()]; // The height of the bar we are processing
                st.pop();                     // Remove it to find its left boundary

                // Right Boundary (NSE): The current index 'i' triggered the pop
                int NSEqIdx = i;

                // Left Boundary (PSE): The element remaining below it in the stack.
                // If stack is empty, it means 'el' was the smallest so far, extending to index -1.
                int PSIdx = !st.empty() ? st.top() : -1;

                // Calculate Area for the popped bar
                int curLength = NSEqIdx - PSIdx - 1;
                int curHeight = el;
                int curArea = curLength * curHeight;

                largestArea = max(largestArea, curArea);
            }

            st.push(i); // Push current index to stack
        }

        // Commented out block to empty the stack
        /*
            // Processing remaining elements in the stack
            // These elements never found a "Next Smaller Element" on the right.
            // Therefore, their Right Boundary extends to the end of the array (Index N).
            while (!st.empty())
            {
                int el = histogram[st.top()];
                st.pop();

                int NSEqIdx = N;                         // Right boundary is the end of the array
                int PSIdx = !st.empty() ? st.top() : -1; // Left boundary is the element below

                int curLength = NSEqIdx - PSIdx - 1;
                int curHeight = el;
                int curArea = curLength * curHeight;

                largestArea = max(largestArea, curArea);
            }
        */

        return largestArea;
    }

    /*
     * METHOD: maximalRectangle
     * ------------------------
     * IDEA:
     * We convert the 2D binary matrix into a series of 1D histograms.
     * We iterate through the matrix row by row. For each row, we treat it as
     * the "ground" and calculate the height of consecutive 1s above it.
     * Then we solve the "Largest Rectangle in Histogram" problem for that row.
     * * COMPLEXITY:
     * Time: O(Rows * Cols)
     * - We iterate every cell once to build histograms: O(Rows * Cols)
     * - We call largestRectangleArea (O(Cols)) for each Row: O(Rows * Cols)
     * Space: O(Cols)
     * - We only need one 1D array of size Cols to store the running heights.
     */
    int maximalRectangle(vector<vector<char>> &matrix)
    {

        if (matrix.empty())
            return 0;

        int M = matrix.size();
        int N = matrix[0].size();

        // Stores the height of consecutive 1s for the current row
        vector<int> histogram(N, 0);
        int maxRectangle = 0;

        // Traverse every row
        for (int i = 0; i < M; i++)
        {
            // Update the histogram for the current row
            for (int j = 0; j < N; j++)
            {

                if (matrix[i][j] == '0')
                {
                    // If current cell is 0, the continuous vertical strip breaks.
                    // Height becomes 0.
                    histogram[j] = 0;
                }
                else
                {
                    // If current cell is 1, we extend the height from the previous row.
                    histogram[j] = histogram[j] + 1;
                }
            }

            // For this updated histogram (representing the matrix up to row i),
            // find the largest rectangle.
            maxRectangle = max(maxRectangle, largestRectangleArea(histogram));
        }

        return maxRectangle;
    }
};

int main()
{
    return 0;
}
