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
// Need to undersrtand this.
Separate Squares II

https://leetcode.com/problems/separate-squares-ii/description/?envType=daily-question&envId=2026-01-14


Problem statement:
You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
Answers within 10-5 of the actual answer will be accepted.
Note: Squares may overlap. Overlapping areas should be counted only once in this version.


Example 1:
Input: squares = [[0,0,1],[2,2,1]]
Output: 1.00000
Explanation:
Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.

Example 2:
Input: squares = [[0,0,2],[1,1,1]]
Output: 1.00000
Explanation:
Since the blue square overlaps with the red square, it will not be counted again. Thus, the line y = 1 splits the squares into two equal parts.



Constraints:
1 <= squares.length <= 5 * 104
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 109
1 <= li <= 109
The total area of all the squares will not exceed 1015.

 */

//-------------------------------------------
// Approach: Segment tree + Sweep-Line algo
//-------------------------------------------

class Solution
{
    // Arrays for Segment Tree
    // count: tracks overlapping squares covering a node
    // length: tracks the active union length covered by a node
    vector<int> count;
    vector<double> length;
    vector<double> x_coords; // Unique sorted X-coordinates

    // Update the Segment Tree
    // node: current tree node index
    // start, end: range of indices in x_coords this node covers
    // l, r: range of indices we want to update
    // val: +1 (add square) or -1 (remove square)
    void update(int node, int start, int end, int l, int r, int val)
    {
        if (l >= r)
            return;

        if (l == start && r == end)
        {
            count[node] += val;
        }
        else
        {
            int mid = start + (end - start) / 2;
            update(2 * node, start, mid, l, min(r, mid), val);
            update(2 * node + 1, mid, end, max(l, mid), r, val);
        }

        // Calculate length for the current node
        if (count[node] > 0)
        {
            // If this node is fully covered by at least one square,
            // its active length is the full physical width it represents.
            length[node] = x_coords[end] - x_coords[start];
        }
        else
        {
            // If not fully covered, the length is the sum of children's lengths.
            // (Leaf nodes have no children, so length becomes 0)
            if (end - start == 1)
            {
                length[node] = 0;
            }
            else
            {
                length[node] = length[2 * node] + length[2 * node + 1];
            }
        }
    }

public:
    double separateSquares(vector<vector<int>> &squares)
    {
        // Step 1: Coordinate Compression for X-axis
        // Collect all unique X-coordinates (start and end of every square)
        for (const auto &sq : squares)
        {
            x_coords.push_back(sq[0]);
            x_coords.push_back((double)sq[0] + sq[2]);
        }
        sort(x_coords.begin(), x_coords.end());
        x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());

        // Map X-coordinates to their compressed index
        auto getXIndex = [&](double x)
        {
            return lower_bound(x_coords.begin(), x_coords.end(), x) - x_coords.begin();
        };

        // Step 2: Create Y-Events
        // Tuple: {y_coord, type (+1/-1), x_start_idx, x_end_idx}
        struct Event
        {
            int y;
            int type;
            int x_start;
            int x_end;

            // Sort by Y. Process starts (+1) before ends (-1) if Y is same,
            // though for area calculation strictly strictly < or <= handles it.
            bool operator<(const Event &other) const
            {
                return y < other.y;
            }
        };

        vector<Event> events;
        for (const auto &sq : squares)
        {
            int x_s = getXIndex(sq[0]);
            int x_e = getXIndex((double)sq[0] + sq[2]);
            events.push_back({sq[1], 1, x_s, x_e});
            events.push_back({sq[1] + sq[2], -1, x_s, x_e});
        }
        sort(events.begin(), events.end());

        // Step 3: Initialize Segment Tree
        int m = x_coords.size();
        count.assign(4 * m, 0);
        length.assign(4 * m, 0.0);

        // Step 4: First Sweep - Calculate Total Union Area
        double totalUnionArea = 0;
        double prevY = events[0].y;

        // We need to store area history to avoid re-running the sweep
        // Pairs of {Y_coordinate, Area_Accumulated_Up_To_This_Y}
        vector<pair<double, double>> areaHistory;
        areaHistory.push_back({prevY, 0.0});

        for (const auto &ev : events)
        {
            double currY = ev.y;
            // Area added by the active union width over the height (currY - prevY)
            // length[1] is the root of the tree, representing total active width
            double stepArea = length[1] * (currY - prevY);
            totalUnionArea += stepArea;

            if (currY > prevY)
            {
                areaHistory.push_back({currY, totalUnionArea});
            }

            // Update the interval in Segment Tree
            update(1, 0, m - 1, ev.x_start, ev.x_end, ev.type);
            prevY = currY;
        }

        // Step 5: Second Phase - Find the exact Split Line
        double targetArea = totalUnionArea / 2.0;

        // Find the specific strip where the target area falls
        for (size_t i = 1; i < areaHistory.size(); ++i)
        {
            double y_prev = areaHistory[i - 1].first;
            double area_prev = areaHistory[i - 1].second;

            double y_curr = areaHistory[i].first;
            double area_curr = areaHistory[i].second;

            if (area_curr >= targetArea)
            {
                // The answer is inside this strip [y_prev, y_curr]
                double missingArea = targetArea - area_prev;

                // We need the width of the union in this strip.
                // We can derive it: Area = Width * Height -> Width = Area / Height
                double stripWidth = (area_curr - area_prev) / (y_curr - y_prev);

                // If width is 0 (gap), return start.
                if (stripWidth == 0)
                    return y_prev;

                return y_prev + (missingArea / stripWidth);
            }
        }

        return prevY;
    }
};

int main()
{

    return 0;
}