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

1. Title: Handle n queries of prime factorization

Links:
https://takeuforward.org/plus/dsa/problems/prime-factorisation-of-a-number
https://youtu.be/glKWkmKFlMw?si=z6eZJa3o6ccXcve2


Problem statement:
You are given an integer array queries of length n.
Return the prime factorization of each number in array queries in sorted order.
Note: Need to return duplicate factors as well.


Examples:
    Input : queries = [2, 3, 4, 5, 6]
    Output : [ [2], [3], [2, 2], [5], [2, 3] ]
    Explanation : The values 2, 3, 5 are itself prime numbers.
    The prime factorization of 4 will be --> 2 * 2.
    The prime factorization of 6 will be --> 2 * 3.

    Input : queries = [7, 12, 18]
    Output : [ [7], [2, 2, 3], [2, 3, 3] ]
    Explanation : The value 7 itself is a prime number.
    The prime factorization of 12 will be --> 2 * 2 * 3.
    The prime factorization of 18 will be --> 2 * 3 * 3.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // Title: Handle n queries of prime factorization
    // Sub-optimal approach:

    // // Time: O(sqrt(N)) in worst case i.e. N is a prime
    // // Space: O(1)
    // vector<int> AllPrimeFactors(int N)
    // {
    //     vector<int> ans;

    //     // This approach automatically eleminates non-prime factors to acting as
    //     // divisor because non-primes' previous prime will already eliminate the
    //     // factors from the dividend So the non-prime ahead can not divide the
    //     // divisor
    //     for (int i = 2; i * i <= N;
    //          i++)
    //     { // O(sqrt(N)) in worst case i.e. N is a prime so N won't be
    //       // reduced by division In other cases N will be reduced in
    //       // each step by a factor So at max sqrtN iteration will be
    //       // there

    //         if (N % i == 0)
    //         {
    //             while (N % i == 0)
    //             { //

    //                 ans.push_back(i);
    //                 N /= i; // Log (base i) N
    //             }
    //         }
    //     }

    //     if (N != 1)
    //         ans.push_back(N); // **Note when left remainder is not 1**

    //     sort(ans.begin(), ans.end());

    //     return ans;
    // }

    // // Sub-optimal approach: Using division method
    // // Time: O(Q*sqrtN) where Q is number of queries and N is avg number
    // // Space: O(1)
    // vector<vector<int>> primeFactors(vector<int> &queries)
    // {
    //     // your code goes here
    //     vector<vector<int>> ans;

    //     for (int i = 0; i < queries.size(); i++) // O(Q)
    //     {
    //         ans.push_back(AllPrimeFactors(queries[i]));
    //     }

    //     return ans;
    // }

    // ---------------------------------------------------------------
    // optimal approach:

    // Time: O(sqrt(N)) in worst case i.e. N is a prime
    // Space: O(1)
    vector<int> AllPrimeFactors(int N, vector<int> &sieve)
    {
        vector<int> ans;

        while (N > 1)
        {                                // until N becomes `1`
            int minFactorOfN = sieve[N]; // This step lowering the complexity to logN

            ans.push_back(minFactorOfN);
            N /= minFactorOfN; // Log N
        }

        sort(ans.begin(), ans.end());

        return ans;
    }

    // O(n Log log n)
    vector<int> getSieve(int n)
    {
        vector<int> leastPrimes(n + 1, -1); // O(N)

        for (int i = 0; i <= n; i++)
        { // setting default values
            leastPrimes[i] = i;
        }

        leastPrimes[0] = 0;
        leastPrimes[1] = 1;

        for (int i = 2; i * i <= n; i++)
        { // O(N Log log N)

            if (leastPrimes[i] != i)
                continue;

            for (int j = i; i * j <= n; j++)
            {
                int prob = i * j;
                if (leastPrimes[prob] != prob)
                    continue;

                leastPrimes[prob] = i;
            }
        }

        return leastPrimes;
    }

    // optimal approach: Using Sieve of Erothns for storing least factor of each
    // numbers Time: O(Q * Log m)
    // where Q is the number of queries and m is the maximum number in queries.
    // Space: O(m)
    vector<vector<int>> primeFactors(vector<int> &queries)
    {
        int m = *max_element(queries.begin(), queries.end()); // O(Q)

        vector<int> sieveOfLeast = getSieve(m); // O(m Log log m)

        vector<vector<int>> ans;

        for (int i = 0; i < queries.size(); i++) // O(Q)
        {
            // O(log m)
            vector<int> primeFactors =
                AllPrimeFactors(queries[i], sieveOfLeast);
            ans.push_back(primeFactors);
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
