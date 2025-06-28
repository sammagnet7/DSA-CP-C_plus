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

1. Title: Trapping Rain Water

Links:
https://takeuforward.org/data-structure/trapping-rainwater/
https://www.youtube.com/watch?v=1_5VuquLbXg&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=8
https://leetcode.com/problems/trapping-rain-water/

Problem statement:
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9


INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Trapping Rain Water
//

// // Approach1:
// //
// // sub-optimal approach: as using extra spaces
// // Time: O(3N)
// // Space: O(2N)
// int trap(vector<int>& height) {

//     int ans = 0;
//     int N = height.size();

//     vector<int> maxPeakRight(N); // O(N)
//     vector<int> maxPeakLeft(N); // O(N)

//     int m1 = INT_MIN;
//     int m2 = INT_MIN;

//     for(int i=0; i<N; i++){ // O(N)

//         m1 = max(m1,height[i]);
//         maxPeakLeft[i] = m1;

//         int revIdx = (N-1-i);
//         m2 = max(m2,height[revIdx]);
//         maxPeakRight[revIdx] = m2;
//     }

//     for(int i=0; i<N; i++){ // O(N)
//         int maxWaterLvl = min(maxPeakLeft[i], maxPeakRight[i]);
//         ans += (maxWaterLvl-height[i]);
//     }

//     return ans;
// }

// // Approach2:
// //
// Optimal approach: Using 2 pointers
// Traversing left pointer from left to right and right pointer from right tot left
// In each iteration keepig the till now Max values from left and right
// adding the water level possible at the smaller side
// and traverse the smaller side between left and right pointers
//
// Time: O(N)
// Space: O(1)
int trap(vector<int> &height)
{

    int N = height.size();
    int ans = 0;

    int l = 0;
    int r = N - 1;
    int lMax = INT_MIN;
    int rMax = INT_MIN;

    while (l <= r)
    { // O(N)

        lMax = max(lMax, height[l]);
        rMax = max(rMax, height[r]);

        int maxWaterLvl = min(lMax, rMax); // beacuse the max height of water can be the minimum of both sides picks

        int lPlus = max(0, (maxWaterLvl - height[l]));
        int rPlus = max(0, (maxWaterLvl - height[r]));

        ans += (lPlus + rPlus);

        if (lMax <= rMax)
        { // traverse left pointer if left is smaller
            l++;
        }
        else
        { // traverse right pointer if right is smaller
            r--;
        }
    }

    return ans;
}

int main()
{
    return 0;
}
