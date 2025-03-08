#include <iostream>
#include <cmath>

using namespace std;

/*
https://takeuforward.org/data-structure/check-if-a-number-is-prime-or-not/

https://www.naukri.com/code360/problems/check-prime_624934?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf&leftPanelTabValue=SUBMISSION

Problem statement
A prime number is a positive integer that is divisible by exactly 2 integers, 1 and the number itself.
Numbers having more than two factors are known as composite numbers.

You are given a number 'n'.
Find out whether 'n' is prime or not.

Example :
Sample Input 1:
5
Sample Output 1:
YES
Explanation of sample input 1 :
5 is only divisible by 1 and 5. 2, 3 and 4 do not divide 5.


Sample Input 2:
6
Sample Output 2:
NO
Explanation of sample input 2 :
6 is divisible by 1, 2, 3, and 6. Therefore it is not a prime number.


Sample Input 3:
1
Sample Output 3:
NO
Explanation of sample input 3 :
1 is divisible only by 1, having only one factor. Therefore it is not a prime number.

Expected time complexity :
The expected time complexity is O(sqrt('n')).
Constraints :
1 <= 'n' <= 10 ^ 9
Time limit: 1 second
*/

class Solution
{
public:
    // Optimal approach; Time: O(sqrt(N))
    bool isPrime_OPTIMAL(int N)
    {
        if (N <= 1)
            return false;

        for (int i = 2; i <= sqrt(N); i++)
        {
            if (N % i == 0)
                return false;
        }
        return true;
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

        cout<<boolalpha;
        cout << ob.isPrime_OPTIMAL(N) << endl;
        cout << "--" << endl;
        cout<<noboolalpha;
    }
    return 0;
}
// } Driver Code Ends