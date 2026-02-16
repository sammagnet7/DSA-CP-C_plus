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

//------------------------------------------------------------------------
// Approach 1: Monotonic Stack  [3 pass for finding pse+nse+maxArea]
//------------------------------------------------------------------------

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

// ------------------------------------------------------------------
// Approach 2: Monotonic Stack  [1 pass for finding pse+nse+maxArea]
//-------------------------------------------------------------------

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

int main()
{
    return 0;
}

/*
Note:

    Topic: Handling Duplicates in Monotonic Stacks
    
    Array: [1, 2, 3, 2, 4, 0]
    Focus: The duplicate value 2 at Index 1 and Index 3.

    1. The Conflict: "Who owns the Subarray?"
    Both 2s (at Index 1 and 3) are capable of being the minimum for the subarray [2, 3, 2].
    If both claim it, we double count.
    If neither claims it, we miss it.
    
    2. Scenario A: Using <= (Loose) on Both Sides
    Logic: "I extend past equal values."
    Left 2 (Index 1): Looks right, sees the other 2. Since 2 <= 2, it goes past it. It claims the whole range [2, 3, 2, 4].
    Right 2 (Index 3): Looks left, sees the other 2. Since 2 <= 2, it goes past it. It also claims the whole range [2, 3, 2, 4].
    Result: The subarray is counted TWICE.
    
    3. Scenario B: Asymmetric (< Left, <= Right)
    Logic: "Left side is strict (stops at equal). Right side is loose (extends past equal)."
    Left 2 (Index 1):
    Right (<=): Sees the other 2. Goes past it.
    Claim: "I own the whole range [2, 3, 2, 4]." (Winner)
    Right 2 (Index 3):
    Left (<): Sees the other 2. STOPS immediately.
    Claim: "I only own [2, 4]. I cannot expand left past index 1."
    Result: The large subarray is counted exactly ONCE (by the left 2).
    
    Code Template Rule:
    When pushing to stack:
    PSE Loop (Left): while (!st.empty() && arr[st.top()] > cur) (Strict >)
    NSE Loop (Right): while (!st.empty() && arr[st.top()] >= cur) (Loose >=)

*/