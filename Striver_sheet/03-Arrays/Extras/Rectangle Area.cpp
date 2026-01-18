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
1. Title: Rectangle Overlap

https://leetcode.com/problems/rectangle-overlap/description/


Problem statement:
An axis-aligned rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) is the coordinate of its bottom-left corner, and (x2, y2) is the coordinate of its top-right corner. Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.

Two rectangles overlap if the area of their intersection is positive. To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two axis-aligned rectangles rec1 and rec2, return true if they overlap, otherwise return false.


Example 1:
Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true

Example 2:
Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false

Example 3:
Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
Output: false


Constraints:

rec1.length == 4
rec2.length == 4
-10^9 <= rec1[i], rec2[i] <= 10^9
rec1 and rec2 represent a valid rectangle with a non-zero area.

----------------------------------------------------------------------------------------------------

2. Title: Rectangle Area

Links:
https://leetcode.com/problems/rectangle-area/description/


Problem statement:
Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).


Example 1:
Rectangle Area
Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
Output: 45

Example 2:
Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
Output: 16


Constraints:
-104 <= ax1 <= ax2 <= 104
-104 <= ay1 <= ay2 <= 104
-104 <= bx1 <= bx2 <= 104
-104 <= by1 <= by2 <= 104


INPUT::::::


OUTPUT::::::


 */

#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------------------
// 1. Title: Rectangle Overlap
//-------------------------------------------------------------------------------
class Solution
{
public:
    /*
     * Method: isRectangleOverlap
     * --------------------------
     * Determines if two axis-aligned rectangles overlap.
     * The rectangles are defined as [x1, y1, x2, y2] (Bottom-Left to Top-Right).
     * * * Approach 1: Axis Separation (Inverse Logic)
     * Two rectangles do NOT overlap if they are completely separated on either the X-axis OR the Y-axis.
     * - They are separated on X if one is entirely to the left/right of the other.
     * - They are separated on Y if one is entirely above/below the other.
     * If neither separation exists, they must overlap.
     * * * Approach 2: Intersection Area (Positive Area Check)
     * We calculate the width and height of the intersection rectangle.
     * If both width > 0 and height > 0, an overlapping area exists.
     * * * Complexity (Both approaches):
     * - Time Complexity: O(1) -> Simple arithmetic operations.
     * - Space Complexity: O(1) -> No extra space used.
     */
    bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2)
    {

        // Extract coordinates for readability
        // Rect 1: [x1, y1] (bottom-left) to [x2, y2] (top-right)
        int a_x1 = rec1[0], a_y1 = rec1[1];
        int a_x2 = rec1[2], a_y2 = rec1[3];

        // Rect 2: [x1, y1] (bottom-left) to [x2, y2] (top-right)
        int b_x1 = rec2[0], b_y1 = rec2[1];
        int b_x2 = rec2[2], b_y2 = rec2[3];

        // ---------------------------------------------------------
        // Approach 1: Check for Separation (Axis Separation Logic)
        // ---------------------------------------------------------

        // Check X-axis separation:
        // Case 1: b_x2 <= a_x1 -> Rect B is completely to the LEFT of Rect A
        // Case 2: a_x2 <= b_x1 -> Rect A is completely to the LEFT of Rect B (Rect B is to the right)
        bool noOverlapAtX = (b_x2 <= a_x1 || a_x2 <= b_x1);

        // Check Y-axis separation:
        // Case 1: b_y2 <= a_y1 -> Rect B is completely BELOW Rect A
        // Case 2: a_y2 <= b_y1 -> Rect A is completely BELOW Rect B (Rect B is above)
        bool noOverlapAtY = (b_y2 <= a_y1 || a_y2 <= b_y1);

        // If separated on EITHER axis, they cannot overlap.
        if (noOverlapAtX || noOverlapAtY)
        {
            return false;
        }
        else
        {
            return true;
        }

        // ---------------------------------------------------------
        // Approach 2: Intersection Area (Commented Out)
        // ---------------------------------------------------------
        /*
        // 1. Calculate the Overlap Width (X dimension)
        // The start of the overlap is the max of the starts (rightmost start).
        // The end of the overlap is the min of the ends (leftmost end).
        // If (end - start) is negative, there is no overlap, so we bound it at 0.
        long long overlapX = max(0, min(a_x2, b_x2) - max(a_x1, b_x1));

        // 2. Calculate the Overlap Height (Y dimension)
        // Similar logic for Y coordinates.
        long long overlapY = max(0, min(a_y2, b_y2) - max(a_y1, b_y1));

        // 3. Check if Area is Positive
        // Overlap exists only if both dimensions are positive.
        // (Using long long prevents overflow, though inputs fit in int here).
        long long overlapArea = overlapX * overlapY;

        if(overlapArea == 0) return false;
        return true;
        */
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Rectangle Area
//-------------------------------------------------------------------------------

class Solution
{
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {

        int areaA = (ax2 - ax1) * (ay2 - ay1);
        int areaB = (bx2 - bx1) * (by2 - by1);

        int overlappedX = max(0, min(ax2, bx2) - max(ax1, bx1));
        int overlappedy = max(0, min(ay2, by2) - max(ay1, by1));

        int overlappedArea = overlappedX * overlappedy;

        return (areaA + areaB - overlappedArea);
    }
};

int main()
{

    return 0;
}