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

1. Title: Check prime or not

Links:
https://takeuforward.org/data-structure/check-if-a-number-is-prime-or-not/
https://www.geeksforgeeks.org/problems/prime-number2314/1


Problem statement:
Given an integer N, check whether it is prime or not. A prime number is a number that is only divisible by 1 and itself and the total number of divisors is 2.

Examples:
                Example 1:
                Input:N = 2

                Output:True

                Explanation: 2 is a prime number because it has two divisors: 1 and 2 (the number itself).

                Example 2:
                Input:N =10

                Output: False

                Explanation: 10 is not prime, it is a composite number because it has 4 divisors: 1, 2, 5 and 10.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

2. Title: Find all Prime Numbers (Sieve of Eratosthenes)

Links:
https://takeuforward.org/data-structure/sieve-of-eratosthenes-find-all-prime-numbers
https://www.naukri.com/code360/problems/all-prime-numbers-less-than-or-equal-to-n_1214958?leftPanelTabValue=PROBLEM
https://leetcode.com/problems/count-primes/description/


Problem statement:
Given a number N, return all primes till N.

Examples
                Example 1:
                Input:N = 10

                Output:[2, 3, 5, 7]

                Explanation: All numbers before 10 are 1, 2, 3, 4, … 10 out of which 2, 3, 5 and 7 are prime.

                Example 2:
                Input:N =32

                Output: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]

                Explanation: All numbers before 32 are 1, 2, 3, 4, … 32 out of which 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 and 31 are prime.



INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Count Primes In Range (using Sieve)

Links:
https://takeuforward.org/maths/count-prime-in-a-range-l-r
https://www.geeksforgeeks.org/problems/count-primes-in-range1604/1


Problem statement:
Given a range L to R, calculate the number of prime numbers in it. Note: inclusive of L and R

Examples
                Example 1:
                Input:N=10

                Output:[2, 3, 5, 7]
                Explanation: All numbers before 10 are 1, 2, 3, 4, … 10 out of which 2, 3, 5 and 7 are prime.

                Example 2:
                Input:N=32

                Output: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
                Explanation:All numbers before 32 are 1, 2, 3, 4, … 32 out of which 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 and 31 are prime.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // 1. Title: Check prime or not

    // Optimal approach
    // Time: O(sqrt N)
    // Space: O(1)
    bool isPrime(int n)
    {
        for (int i = 2; i * i <= n; i++)
        { // O(sqrt N)

            // If n is divisible by i
            // without any remainder.
            if (n % i == 0)
            {

                return false;
            }
        }

        return true;
    }

    // --------------------------------------------------------
    // 2. Title: Find all Prime Numbers (Sieve of Eratosthenes)

    // Optimal approach: Sieve of Eratosthenes
    // Time:  O(N Log Log N + N):
    //        because outer loop's O(sqrtN) * inner loop iterates over multiples of primes
    //        Overall becomes: O(n/2 + n/3 + n/5 + ?.) = O(n log(log(N))
    // Space: O(N) for `primes` vector ignoring
    vector<int> findAllPrimes(int n)
    {
        if (n <= 1)
            return {};
        vector<int> ans;
        vector<int> primes(n + 1, 1); // O(N)

        // 0 and 1 are non-primes
        primes[0] = primes[1] = 0;

        for (int i = 2; i * i <= n; i++)
        { // Note: looping till sqrtN

            if (primes[i] == 0)
                continue; // Note: if non-primes no need to do
                          // as already covered by some previous primes

            for (int j = i; i * j <= n; j++)
            { // Note: starting from i
              // as j's all prev multiplications are already covered

                primes[i * j] = 0;
            }
        }

        // O(N)
        for (int i = 0; i <= n; i++)
        {
            if (primes[i] == 1)
                ans.push_back(i);
        }

        return ans;
    }

    // --------------------------------------------------------
    // 3. Title: Count Primes In Range (using Sieve)

    // Optimal approach: SiveofEroth + prefix sum as cumulative count of primes till R
    // Note: If Q such queries are given, simply make the sieve for the max range i.e 10^6
    // Time: O(R Log Log R)
    // Space: O(R)
    int countPrimes(int L, int R)
    {
        int ans = 0;
        vector<int> primes(R + 1, 1);

        primes[0] = primes[1] = 0;

        // create the Sieve of Eroth.. in O(R Log Log R)
        for (int i = 2; i * i <= R; i++)
        {

            if (primes[i] == 0)
                continue;

            for (int j = i; i * j <= R; j++)
            {

                primes[i * j] = 0;
            }
        }

        for (int i = 1; i <= R; i++)
        { // O(R)

            primes[i] = primes[i - 1] + primes[i];
        }

        // O(1)
        ans = primes[R] - primes[L - 1]; // inclusive of L and R

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
