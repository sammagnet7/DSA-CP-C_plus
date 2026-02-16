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

1. Title: Print all Divisors of a given Number

Links:
https://takeuforward.org/data-structure/print-all-divisors-of-a-given-number/
https://www.naukri.com/code360/problems/print-all-divisors-of-a-number_1164188?leftPanelTabValue=SUBMISSION


Problem statement:
Given an integer N, return all divisors of N.

A divisor of an integer N is a positive integer that divides N without leaving a remainder. In other words, if N is divisible by another integer without any remainder, then that integer is considered a divisor of N.

Examples
                Example 1:
                Input:N = 36

                Output:[1, 2, 3, 4, 6, 9, 12, 18, 36]

                Explanation: The divisors of 36 are 1, 2, 3, 4, 6, 9, 12, 18, 36.

                Example 2:
                Input:N =12

                Output: [1, 2, 3, 4, 6, 12]

                Explanation: The divisors of 12 are 1, 2, 3, 4, 6, 12.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // Title: All Divisors of a given Number

    // Optimal approach: Iterate till sqrtN and save both divisors at each iter
    //
    // Time: O(sqrt N)
    // Space: O(1) ignoring O(N) space needed for `ans`
    vector<int> printDivisors(int n)
    {

        vector<int> ans;

        for (int i = 1; i * i <= n; i++)
        { // O(sqrt N)

            if (n % i == 0)
            {
                ans.push_back(i);

                if (n / i != i) // Note: if 2*14 = 28, then add 2 and 14 both
                    ans.push_back(n / i);
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
