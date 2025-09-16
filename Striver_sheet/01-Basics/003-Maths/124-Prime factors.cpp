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

1. Title: Find all Prime Factors of the given number

Links:
https://takeuforward.org/data-structure/print-all-prime-factors-of-the-given-number/
https://www.geeksforgeeks.org/problems/prime-factors5052/1



Problem statement:
Given an integer N, print all of its prime factors.

Examples
                Example 1:
                Input: N=60
                Output: 2, 3, 5
                Explanation: All factors/divisors of 60 include: 1, 2, 3, 4, 5, 6, 10, 12, 18, 20, 30, 60. Out of these only 2, 3 and 5 are prime.

                Example 2:
                Input: N=35
                Output: 5, 7
                Explanation: All factors/divisors of 35 include: 1, 5, 7, 35. Out of these, only 5 and 7 are prime.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

2. Title: Prime Factorization using Sieve

Links:
https://www.geeksforgeeks.org/problems/prime-factorization-using-sieve/1

Problem statement:
You are given a positive number N. Using the concept of Sieve, compute its prime factorisation.

Example:
    Input:
    N = 12246
    Output:
    2 3 13 157
    Explanation:
    2*3*13*157 = 12246 = N.

Your Task:
Comple the function findPrimeFactors(), which takes a positive number N as input and returns a vector consisting of prime factors. You should implement Sieve algorithm to solve this problem.

Expected Time Complexity: O(Nlog(log(N)).
Expected Auxiliary Space: O(N).

Constraints:
2<=N<=2*105

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Smallest Prime Factor (SPF)

Links:
https://youtu.be/glKWkmKFlMw?si=mosnrLAU8JoUvHlA
https://www.geeksforgeeks.org/problems/least-prime-factor5216/1

Problem statement:
Given a number N, find the least prime factors for all numbers from 1 to N.  The least prime factor of an integer X is the smallest prime number that divides it.
Note :

1 needs to be printed for 1.
You need to return an array/vector/list of size N+1 and need to use 1-based indexing to store the answer for each number.

Example 1:
    Input: N = 6
    Output: [0, 1, 2, 3, 2, 5, 2]
    Explanation: least prime factor of 1 = 1,
    least prime factor of 2 = 2,
    least prime factor of 3 = 3,
    least prime factor of 4 = 2,
    least prime factor of 5 = 5,
    least prime factor of 6 = 2.
    So answer is[1, 2, 3, 2, 5, 2].

Example 2:
    Input: N = 4
    Output: [0, 1, 2, 3, 2]
    Explanation: least prime factor of 1 = 1,
    least prime factor of 2 = 2,
    least prime factor of 3 = 3,
    least prime factor of 4 = 2.
    So answer is[1, 2, 3, 2].

Expected Time Complexity: O(NlogN)
Expected Auxiliary Space: O(N)

Constraints:
2<= n <=105

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // 1. Title: Find all Prime Factors of the given number

    //
    // Note: One suboptimal approach would be
    // to loop from 2 to sqrtN, find both the factors at each go
    // and for each number checkPrime()
    //
    // Time: O(sqrtN * (2 * sqrtN)) == O(2 N)
    // SPace: O(1)
    //
    // vector<int> AllPrimeFactors(int N)
    // {
    // }

    // ---------------------------------------------------------------

    //  Optimal Approach: continuously divide the number by its smallest prime factor until it becomes 1 or a prime number itself
    //  60/2=30, 30/2=15, 15/3=5, 5/4=!, 5/5=1, ... N/root(N)
    //
    // Time: O(sqrt(N)) in worst case i.e. N is a prime
    // Space: O(1)
    vector<int> AllPrimeFactors(int N)
    {

        vector<int> ans;

        // This approach automatically eleminates non-prime factors to acting as divisor
        // because non-primes' previous prime will already eliminate the factors from the dividend
        // So the non-prime ahead can not divide the divisor
        for (int i = 2; i * i <= N; i++)
        { // O(sqrt(N)) in worst case i.e. N is a prime so N won't be reduced by division
          // In other cases N will be reduced in each step by a factor
          // So at max sqrtN iteration will be there

            if (N % i == 0)
            {
                ans.push_back(i);

                while (N % i == 0)
                { //

                    N /= i; // Log (base i) N
                }
            }
        }

        if (N != 1)
            ans.push_back(N); // **Note when left remainder is not 1**

        return ans;
    }

    // --------------------------------------------------------
    // 2. Title: Prime Factorization using Sieve

    // One sub-optimal approach using **Sieve of Erothns**.
    // Time: O(N Log log N)
    // SPace: O(N)
    vector<int> findPrimeFactors(int N)
    {
        if (N <= 1)
            return {};

        int rootOfN = sqrt(N);

        vector<int> primes(N + 1, 1);
        vector<int> ans;

        primes[0] = primes[1] = 0;

        // O(N Log log N)
        for (int i = 0; i <= rootOfN; i++)
        { // Optimization 1 by rootOfN

            if (primes[i] == 0)
                continue; // // Optimization 2 by continue

            for (int j = i; (i * j) <= N; j++)
            { // Optimization 3 by j=i

                primes[i * j] = 0;
            }
        }

        for (int i = 0; i <= N; i++)
        { // O(N)

            if (primes[i] == 1 && N % i == 0)
            { // if prime and factor of N

                for (int k = i; N % k == 0; N /= k)
                    ans.push_back(k);
            }
        }

        return ans;
    }

    // --------------------------------------------------------
    // 3. Title: Smallest Prime Factor (SPF)

    // optimal approach: Uses **Sieve of Erothns**
    // In the sieve store all the MIN factors of each numbers
    // Time: O(N Log log N)
    // Space: O(N)
    vector<int> leastPrimeFactor(int n)
    {
        vector<int> ans;
        vector<int> leastPrimes(n + 1, -1); // O(N)

        leastPrimes[0] = 0;
        leastPrimes[1] = 1;
        // create the sieve
        for (int i = 2; i * i <= n; i++)
        { // O(N Log log N)

            if (leastPrimes[i] != -1)
                continue;

            leastPrimes[i] = i; // if prime, put the number itself

            for (int j = i; i * j <= n; j++)
            {

                if (leastPrimes[i * j] != -1)
                    continue;

                leastPrimes[i * j] = i; // if not prime, then put the smallest prime factor
            }
        }

        for (int i = 0; i <= n; i++)
        { // O(N)

            if (leastPrimes[i] == -1)
                ans.push_back(i);
            else
                ans.push_back(leastPrimes[i]);
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
