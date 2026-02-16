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
https://leetcode.com/problems/powx-n/submissions/1664082255/

Problem statement:
Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

Example 1:
Input: x = 2.00000, n = 10
Output: 1024.00000

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

Example 5:
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

    // Optimal approach
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
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
