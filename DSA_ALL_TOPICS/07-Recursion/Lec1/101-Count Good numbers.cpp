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
https://leetcode.com/problems/count-good-numbers/submissions/1664652704/

Problem statement:
A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.


Examples:

Example 1:
Input: n = 1
Output: 5
Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".

Example 2:
Input: n = 4
Output: 400

Example 3:
Input: n = 50
Output: 564908303


Constraints:
1 <= n <= 1015


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // -------------------------------------------------------------
    // Find number of good numbers:

    // Time: O(Log N)
    // Space: O(Log N) for recursion stack
    long long myPow(long long x, long long n, long long moduler)
    {

        if (n == 0)
            return 1;
        if (n == 1)
            return x;

        long long tmp;

        if (n % 2 == 0)
        {
            tmp = myPow(x, (n / 2), moduler); // STore in a local var to avoid redundant calls

            tmp = tmp % moduler;
            return (tmp * tmp) % moduler;
        }
        else
        {
            return (x * myPow(x, (n - 1), moduler)) % moduler;
        }
    }

    // Optimal approach: Uses Binary exponentian to find power(x,n)
    // Time: O(Log N) where N is length of the integer string
    // Space: O(Log N) due to stack space
    int countGoodNumbers(long long n)
    {

        long long ans = 1;
        long long moduler = 1e9 + 7;

        // This approach will take O(N)
        // for(int i = 0; i<n; i++){
        //     if(i%2 == 0){
        //         ans = (ans * 5) % moduler;
        //     }
        //     else{
        //         ans = (ans * 4) % moduler;
        //     }
        // }

        long long evenCount = ceil((double)n / 2); // or (n+1)/2
        long long primeCount = n / 2;

        ans = myPow(5, evenCount, moduler);
        ans = (myPow(4, primeCount, moduler) * ans) % moduler;

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
