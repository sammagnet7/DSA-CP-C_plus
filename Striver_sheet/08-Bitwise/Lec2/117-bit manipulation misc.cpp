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

using namespace std;

/*

1. Title: Count number of bits to be flipped to convert A to B

Links:
https://www.youtube.com/watch?v=OOdrmcfZXd8
https://leetcode.com/problems/minimum-bit-flips-to-convert-number/description/


Problem statement:
A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from either 0 to 1 or 1 to 0.

For example, for x = 7, the binary representation is 111 and we may choose any bit (including any leading zeros not shown) and flip it. We can flip the first bit from the right to get 110, flip the second bit from the right to get 101, flip the fifth bit from the right (a leading zero) to get 10111, etc.
Given two integers start and goal, return the minimum number of bit flips to convert start to goal.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // Title: Count number of bits to be flipped to convert A to B

    // Optimal approach: First do XOR, then count number of set bits in the xored value
    // Time: O(1 + Log (start XOR goal) )
    // Space: O(1)
    int minBitFlips(int start, int goal)
    {

        int xoredN = start ^ goal;

        int ans = 0;

        while (xoredN)
        {

            if (xoredN & 1) // check LSB 1 or not
                ans++;

            xoredN = xoredN >> 1; // divide by 2
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
