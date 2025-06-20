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

1. Title: Divide Two Integers

Links:
https://www.youtube.com/watch?v=pBD4B1tzgVc
https://leetcode.com/problems/divide-two-integers/

Problem statement:
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
Return the quotient after dividing dividend by divisor.
Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    //-----------------------------------------------------------------------
    // 1. Title: Divide Two Integers

    // Brute force approach: substarct divisor from dividend multiple times
    // gives **TLE**
    // Time: O(dividend)
    // Space: O(1)
    // int divide(int dividend, int divisor)
    // {
    //     // edge cases checks
    //     if (dividend == divisor)
    //         return 1;

    //     long long ans = 0;
    //     bool sign = true;

    //     long long _dividend = dividend;
    //     long long _divisor = divisor;

    //     if ((_divisor < 0 && _dividend >= 0) || (_divisor >= 0 && _dividend < 0))
    //         sign = false;

    //     _dividend = abs(_dividend);
    //     _divisor = abs(_divisor);

    //     while (_dividend > 0)
    //     {
    //         _dividend = _dividend - _divisor;
    //         ans++;
    //     }

    //     if (_dividend < 0)
    //         ans--; // to get floor of quotient

    //     if (ans > INT_MAX && sign)
    //         return INT_MAX; // for +ve
    //     if (ans > INT_MAX && !sign)
    //         return INT_MIN; // for -ve

    //     if (!sign)
    //         ans = (-1) * ans; // else if -ve

    //     return ans;
    // }

    // optimal approach: Using Bitwise operator
    // 1. Each number can be represented as sum of power of 2s, so as quotient.
    // 2. So at each step we try to find what is the (highest power of 2 * divisor) that can be substracted from dividend.
    // 3. and we sums these (highest power of 2) at each step
    // 3. repeating this at each step we are left with smaller dividend
    // 4. repeat this until dividen becomes lesser than divisor
    // 5. Finally the sum of power of 2s becomes the quotent logically. And we return
    //
    // Time: O( (Log (dividend))^2 ) Becasue two ehile loops one inside another, divides dividend by 2, each time
    // Space: O(1)
    int divide(int dividend, int divisor)
    {
        // edge cases checks
        if (dividend == divisor)
            return 1;

        bool sign = true;
        long long ans = 0;

        long long _dividend = dividend;
        long long _divisor = divisor;

        if ((_divisor < 0 && _dividend >= 0) || (_divisor >= 0 && _dividend < 0))
            sign = false;

        _dividend = abs(_dividend);
        _divisor = abs(_divisor);

        // O( Log (_dividend) * Log (_dividend))
        while (_dividend >= _divisor)
        {
            long long powerOfTwo = 0;

            // O( Log (_dividend))
            while (_dividend >= (_divisor << (powerOfTwo + 1)))
            { // to remove mul op, equivalent to expr:
              // ( _divisor * ( 1<<(powerOfTwo+1) ) )
                powerOfTwo++;
            }

            ans += ((long long)1 << powerOfTwo);    // cast to long is needed, otherwise overflow
            _dividend -= ((_divisor << (powerOfTwo)));
        }

        if (ans > INT_MAX && sign)
            return INT_MAX; // for +ve
        if (ans > INT_MAX && !sign)
            return INT_MIN; // for -ve

        ans = sign ? ans : (-1) * ans; // else if -ve

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
