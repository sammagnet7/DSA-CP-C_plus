#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
https://www.rookieslab.com/posts/fastest-way-to-check-if-a-number-is-prime-or-not

Problem statement

Sieve of Eratosthenes:

The idea behind Sieve of Eratosthenes is to cross out all the composites in the given range. Once we are sure that all composites are crossed out, we are left with all the primes in the given range. How do we cross out all the composites?

Let’s create a process to find all primes in the range 1 to N.

Iterate from 2 to sqrt(N), call it i
For each i, we cross out all the multiples of i, i.e. 2*i, 3*i .. and so on
If i is already crossed out, we don’t do anything, because if i is already crossed out, we are ensured that all multiples of i are already crossed out in our previous iterations
In the end, we print out all the numbers that are not crossed out
Example: Let’s take a range [2, 25] and find all the primes in this list.

[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]

A beautiful visualization of the above process was found on wikipedia2:
https://www.rookieslab.com/assets/documentation/Sieve-of-Eratosthenes-animation.gif
*/

class Solution
{
public:
    // Optimal approach; Time: O(N* Log Log N);
    void listPrimes_OPTIMAL(int N, vector<int> &list)
    {
        vector<bool> is_prime(N + 1, true); // default: all are prime
        is_prime[0] = is_prime[1] = false;  // we know 0 and 1 is by default considered non_prime

        // Sieve of Eratosthenes
        for (int i = 2; i <= sqrt(N); i++)
        { //  O(N* Log Log N)
            if (!is_prime[i])
                continue;

            for (int j = i + i; j <= N; j = j + i)
            {
                is_prime[j] = false;
            }
        }

        for (int i = 0; i < is_prime.size(); i++)
        { // O(N)
            if (is_prime[i])
                list.push_back(i);
        }
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin >> N;
        Solution ob;

        vector<int> list_prime; // Not initialized. So blank array.

        ob.listPrimes_OPTIMAL(N, list_prime);

        for (auto i : list_prime)
            cout << i << " ";

        cout << endl;
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends