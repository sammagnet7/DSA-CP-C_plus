#include <iostream>
#include <cmath>

using namespace std;

/*
https://takeuforward.org/data-structure/print-all-divisors-of-a-given-number/
https://www.naukri.com/code360/problems/sum-of-all-divisors_8360720?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf


Problem statement
You are given an integer ‘n’.
Function ‘sumOfDivisors(n)’ is defined as the sum of all divisors of ‘n’.
Find the SUM of ‘sumOfDivisors(i)’ for all ‘i’ from 1 to ‘n’.

Example:
Input: ‘n’  = 5
Output: 21
Explanation:
We need to find the sum of ‘sumOfDivisors(i)’ for all ‘i’ from 1 to 5.
‘sumOfDivisors(1)’ = 1
‘sumOfDivisors(2)’ = 2 + 1 = 3
‘sumOfDivisors(3)’ = 3 + 1 = 4
‘sumOfDivisors(4)’ = 4 + 2 +1 = 7
‘sumOfDivisors(5)’ = 5 + 1 = 6
Therefore our answer is sumOfDivisors(1) + sumOfDivisors(2) + sumOfDivisors(3) + sumOfDivisors(4) + sumOfDivisors(5) = 1 + 3 + 4 + 7 + 6 = 21.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
3

Sample Output 1:
8
Explanation of sample output 1:
We need to find sumOfDivisors(1) + sumOfDivisors(2) +sumOfDivisors(3).
sumOfDivisors(1) = 1
sumOfDivisors(2) = 2 + 1 = 3
sumOfDivisors(3) = 3 + 1 = 4
Therefore, the answer is sumOfDivisors(1) + sumOfDivisors(2) + sumOfDivisors(3) = 1 + 3 + 4 = 8.

Sample Input 2:
10
Sample Output 2:
87


Expected Time Complexity:
Try to solve this in O(sqrt(‘n’)).

Constraints:
1 <= ‘n’ <= 3*10^4

Time Limit: 1 sec
*/

class Solution
{
public:
    // Brute force approach; Time: O(N^2)
    int sumOfAllDivisors_BRUTE(int N)
    {
        int sum = 0;
        for (int k = 1; k <= N; k++)
        {
            for (int i = 1; i <= k; i++)
            {
                if ((k % i) == 0)
                    sum += i;
            }
        }
        return sum;
    }

    // Better approach; Time: O(N*rootN)
    int sumOfAllDivisors_BETTER(int N)
    {
        int sum = 0;
        for (int num = 1; num <= N; num++)
        {
            for (int i = 1; i <= sqrt(num); i++)
            {
                if ((num % i) == 0)
                {
                    sum += i;
                    if (i != (num / i))
                        sum += (num / i);
                }
            }
        }
        return sum;
    }

    // Optimal approach; Time: O(N);
    int sumOfAllDivisors_OPTIMAL(int N)
    {
        int sum = 0;

        for (int num = 1; num <= N; num++)
        {
            sum = sum + (N / num) * num; // (how many times a divisor can be present from 1 to N) * (divisor's value)
        }

        return sum;
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

        cout << ob.sumOfAllDivisors_BRUTE(N) << endl;
        cout << ob.sumOfAllDivisors_BETTER(N) << endl;
        cout << ob.sumOfAllDivisors_OPTIMAL(N) << endl;
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends