#include <iostream>
#include <vector>

using namespace std;

/*
https://takeuforward.org/data-structure/factorial-of-a-number-iterative-and-recursive/

https://www.geeksforgeeks.org/problems/find-all-factorial-numbers-less-than-or-equal-to-n3548/0?problemType=functional&difficulty%255B%255D=-1&page=1&query=problemTypefunctionaldifficulty%255B%255D-1page1

Problem statement:
A number n is called a factorial number if it is the factorial of a positive integer. For example, the first few factorial numbers are 1, 2, 6, 24, 120,
Given a number n, the task is to return the list/vector of the factorial numbers smaller than or equal to n.

Examples:
Input: n = 3
Output: 1 2
Explanation: The first factorial number is 1 which is less than equal to n. The second number is 2 which is less than equal to n,but the third factorial number is 6 which is greater than n. So we print only 1 and 2.

Input: n = 6
Output: 1 2 6
Explanation: The first three factorial numbers are less than equal to n but the fourth factorial number 24 is greater than n. So we print only first three factorial numbers.
Constraints:
1<=n<=1018
*/

class Solution
{
public:
    vector<long long> factorialNumbers(long long N)
    {

        int dig = 1;
        vector<long long> res;
        long long factorial = 1;

        while (factorial <= N)
        {
            res.push_back(factorial);

            dig++;
            factorial = res[dig - 2] * dig;
        }
        return res;
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

        vector<long long> ans = ob.factorialNumbers(N);
        for (auto num : ans)
        {
            cout << num << " ";
        }
        cout << endl;
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends