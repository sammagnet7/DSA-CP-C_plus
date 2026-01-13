#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*

Separate Squares I

https://leetcode.com/problems/separate-squares-i/description/?envType=daily-question&envId=2026-01-13


Problem statement:
You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted multiple times.


Example 1:
Input: squares = [[0,0,1],[2,2,1]]
Output: 1.00000
Explanation:
Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.

Example 2:
Input: squares = [[0,0,2],[1,1,1]]
Output: 1.16667

Explanation:
The areas are:
Below the line: 7/6 * 2 (Red) + 1/6 (Blue) = 15/6 = 2.5.
Above the line: 5/6 * 2 (Red) + 5/6 (Blue) = 15/6 = 2.5.
Since the areas above and below the line are equal, the output is 7/6 = 1.16667.


Constraints:
1 <= squares.length <= 5 * 104
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 109
1 <= li <= 109
The total area of all the squares will not exceed 1012.

 */

//--------------------------------------
// Approach 1: Binary search [OPTIMAL]
//--------------------------------------

class Solution
{
public:
    /*
     * METHOD: separateSquares
     * -----------------------
     * PROBLEM:
     * Find the horizontal line y = Y that divides the total area of the squares into two equal halves.
     *
     * APPROACH:
     * Binary Search on Answer (Geometric Binary Search).
     * 1. Calculate the total area of all squares and determine the search range [minY, maxY].
     * 2. Use Binary Search to find the Y-coordinate. For a given candidate 'mid':
     * - Calculate the total area of squares strictly below 'mid'.
     * - If Area_Below >= Total_Area / 2, our line is too high (or just right); search lower.
     * - Otherwise, search higher.
     * 3. Optimization: Sort squares by their bottom Y-coordinate to allow early breaking
     * in the area calculation loop.
     *
     * COMPLEXITY:
     * Time Complexity: O(N log N + K * N)
     * - O(N log N) to sort the squares.
     * - O(N) per iteration of binary search to calculate area.
     * - K iterations (here K=60). So effective complexity is O(N log N).
     * Space Complexity: O(1)
     * - Auxiliary space is constant (ignoring recursion stack for sorting).
     */
    double separateSquares(vector<vector<int>> &squares)
    {

        int N = squares.size();

        // Step 1: Sort squares based on their starting Y-coordinate.
        // This optimization allows us to 'break' early in the inner loop
        // once we pass the 'mid' line.
        sort(squares.begin(), squares.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });

        double ans = 0.0;
        int minY = INT_MAX;
        int maxY = INT_MIN;
        double toalArea = 0;

        // Step 2: Calculate bounds and total area
        for (int i = 0; i < N; i++)
        {
            minY = min(minY, squares[i][1]);
            // Search range must extend to the TOP of the highest square
            maxY = max(maxY, squares[i][1] + squares[i][2]);

            // Cast to double before multiplication to prevent integer overflow
            // (10^9 * 10^9 = 10^18, which overflows 32-bit int)
            toalArea += ((double)squares[i][2] * squares[i][2]);
        }

        double halfArea = toalArea / 2.0;

        double l = (double)minY;
        double r = (double)maxY;

        /* * BINARY SEARCH LOOP STRATEGY:
         * ----------------------------
         * Why 'for(int k=0; k<60; k++)' instead of 'while(r - l > 1e-6)'?
         * * 1. Stability: Floating point binary searches can sometimes result in infinite loops
         * if the gap (r-l) becomes smaller than machine precision (epsilon) but the condition
         * still holds. A fixed loop avoids this completely.
         * * 2. Precision: Running 60 iterations reduces the search space by a factor of 2^60.
         * Even with a massive range (e.g., 10^9), the error margin becomes negligible
         * (~10^-9), which is sufficient for this problem.
         * * 3. Predictability: We know exactly how many operations will run regardless of input.
         */
        for (int k = 0; k < 60; k++)
        {

            double mid = l + (r - l) / 2;
            double belowArea = 0;

            // Step 3: Calculate area strictly below the 'mid' line
            for (int i = 0; i < N; i++)
            {

                int curStartY = squares[i][1];
                int curEndY = squares[i][1] + squares[i][2];

                // Optimization: Since squares are sorted by Y, if the current square
                // starts above our line, ALL subsequent squares also start above.
                if (mid <= curStartY)
                {
                    break;
                }
                // Case A: Square is completely below the line
                else if (curEndY <= mid)
                {
                    belowArea += ((double)squares[i][2] * squares[i][2]);
                }
                // Case B: Square is cut by the line (Partial Area)
                // We take width * (height from bottom to mid)
                else
                {
                    belowArea += (squares[i][2] * (mid - curStartY));
                }
            }

            // Step 4: Adjust binary search bounds
            if (halfArea <= belowArea)
            {
                ans = mid; // Possible answer found, try to find a smaller (lower) Y
                r = mid;
            }
            else
            {
                l = mid; // Not enough area below, move line up
            }
        }

        return ans;
    }
};

//---------------------------------------
// Approach 2: Sweep-Line algo [OPTIMAL]
//---------------------------------------

class Solution
{
public:
    /*
     * METHOD: separateSquares (Sweep-Line Approach)
     * ---------------------------------------------
     * ALGORITHM:
     * 1. Coordinate Compression / Events:
     * We map every Y-coordinate to a change in the "active width" (effectiveXLen).
     * - Bottom of square (y): Width increases (+l).
     * - Top of square (y+l): Width decreases (-l).
     * * 2. Sweep:
     * We iterate through sorted Y-coordinates.
     * - Calculate area of the strip we just passed: (curY - prevY) * current_width.
     * - Add to cumulative area.
     * - If cumulative area >= Target, we found the strip containing the answer.
     * * 3. Interpolation (The "Step Back" Logic):
     * If we exceed the target area, it means the cut line is somewhere strictly
     * inside the current strip.
     * - Answer = curY - (Amount_We_Overshot / Width_Of_This_Strip).
     *
     * COMPLEXITY:
     * Time: O(N log N) - Inserting into the map sorts the coordinates.
     * Space: O(N) - Storing 2 events per square.
     */
    double separateSquares(vector<vector<int>> &squares)
    {

        int N = squares.size();

        // Map stores events sorted by Y-coordinate.
        // Key: Y-coordinate, Value: Change in horizontal width at this Y.
        map<int, long> events;

        double totalArea = 0;

        // Step 1: Build the Events Map
        for (auto &s : squares)
        {
            int y = s[1];
            int l = s[2];

            // At the bottom edge, width increases
            events[y] += l;
            // At the top edge, width decreases
            events[y + l] -= l;

            // Calculate total area carefully using double to avoid integer overflow
            totalArea += (double)l * l;
        }

        double targetArea = (double)totalArea / 2.0;

        // 'prevY' tracks the bottom of the current strip.
        // Initializing to 0 works because 'effectiveXLen' starts at 0.
        // Even if the first square starts at Y=5, the area calculated from 0 to 5 will be 0.
        int prevY = 0;

        // Tracks the sum of widths of all currently active squares (overlapping counts)
        long long effectiveXLen = 0;
        double cumulativeArea = 0;

        // Step 2: Sweep Line Process
        for (auto it = events.begin(); it != events.end(); it++)
        {

            int curY = it->first;             // Top of the current strip
            long long deltaXLen = it->second; // Change in width happening at curY

            // Calculate area of the strip defined by [prevY, curY]
            // Note: effectiveXLen is the width valid FOR this strip (set in previous iteration)
            double curArea = (double)effectiveXLen * (curY - prevY);

            cumulativeArea += curArea;

            // Step 3: Check Intersection
            if (cumulativeArea >= targetArea)
            {

                // Case A: Exact Match (Line is exactly at curY)
                if (cumulativeArea == targetArea)
                {
                    return curY;
                }
                // Case B: Overshot (Line is inside the strip [prevY, curY])
                else
                {
                    // How much area did we accumulate beyond the target?
                    double extraArea = cumulativeArea - targetArea;

                    // Height = Area / Width
                    // We need to move DOWN from curY by this height to remove the excess area.
                    double deltaHeight = (double)extraArea / (double)effectiveXLen;

                    return (double)curY - deltaHeight;
                }
            }

            // Prepare for the NEXT strip:
            // Apply the width change that happens at curY
            effectiveXLen += deltaXLen;
            prevY = curY;
        }

        return 0.0; // Should not reach here given valid constraints
    }
};

int main()
{

    return 0;
}