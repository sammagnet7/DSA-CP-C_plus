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

Title: Pow(x,n) i.e x^n

Links:
https://takeuforward.org/data-structure/implement-powxn-x-raised-to-the-power-n/
https://leetcode.com/problems/powx-n/submissions/1664082255/

Problem statement:
Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

Example 1:
Input: x = 2.00000, n = 10
Output: 1024.0000

Example 2:
Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:
Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

Example 4:
x = 0.00001
n = 2147483647
output: 0.00000

Example 5: (**)
x = 1.00000
n = -2147483648
output = 1.00000


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    //-----------------------------------------------------------------------

    // Optimal approach: Recursive
    // Time: o(Log N)
    // Space: O(Log N) for recursion stack
    double myPow(double x, int n)
    {

        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        if (n == -1)
            return (1 / x); // Note for n=-ve

        double tmp;

        if (n % 2 == 0)
        {
            tmp = myPow(x, (n / 2)); // STore in a local var to avoid redundant calls
            return tmp * tmp;
        }
        else
        {
            return x * myPow(x, (n - 1));
        }
    }

    // Optimal approach: iterative
    // Time: O(Log N)
    // Space: O(1)
    double myPow(double x, int n)
    {

        if (x == 0 || x == 1)
            return x;
        if (n == 0)
            return 1;

        double base = n > 0 ? x : (1 / x);
        long exp_v = abs((long)n); // Note: This cast to long is necessary
                                   // because in case n=INT_MIN, it can not be converted to +ve int

        double ans = 1.0;

        while (exp_v)
        {

            if ((exp_v & 1) == 0)
            { // even
                base = base * base;
                exp_v = exp_v >> 1; // divided by 2
            }
            else
            {
                ans = ans * base;
                exp_v -= 1;
            }
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
