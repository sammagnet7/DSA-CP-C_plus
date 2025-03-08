#include <iostream>
#include<vector>

using namespace std;

/*
https://takeuforward.org/arrays/print-fibonacci-series-up-to-nth-term/
https://leetcode.com/problems/fibonacci-number/description/

Problem statement:
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
Given n, calculate F(n).

Example 1:
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Example 2:
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Example 3:
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
 

Constraints:
0 <= n <= 30
*/

class Solution
{
public:
    //Recurseive approach. TIme: O(2^N)
    int fib_Rec(int N) {
        if(N==0 || N==1) return N;

        return fib_Rec(N-1)+fib_Rec(N-2);
    }

    int fib_OPTIMAL(int N) {
        if(N<2) return N;       // Handling edge cases
        vector<int> fibs(N+1,-1);
        fibs[0]=0;
        fibs[1]=1;

        for(int i=2; i<=N; i++){
            fibs[i]=fibs[i-1]+fibs[i-2];
        }
        return fibs[N];
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    cout<<endl;
    while (t--)
    {
        int N;
        cin >> N;
        Solution ob;

        cout << ob.fib_Rec(N) << endl;
        cout << ob.fib_OPTIMAL(N) << endl;
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends