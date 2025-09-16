#include <iostream>
#include <climits> //Needed for MAX, MIN limits

using namespace std;

/*
https://leetcode.com/problems/reverse-integer/solutions/138782/reverse-integer/

Problem Statement: 
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, (2^31-1)], then return 0.
Assume the environment does not allow you to store 64-bit integers (signed or unsigned).


Examples:
    Input: x = 123
    Output: 321
    Example 2:

    Input: x = -123
    Output: -321
    Example 3:

    Input: x = 120
    Output: 21
 
Constraints:
    -231 <= x <= 231 - 1
*/


class Solution {
public:
    // Time complexity: O(log [base10] N)
    int reverse(int N) {
        int temp=N;
        int rev=0;

        while(temp){
            int digit=temp%10;
            if(rev > (INT_MAX/10) || (rev==INT_MAX/10 && digit>7)) return 0;   
            else if(rev < (INT_MIN/10) || (rev==INT_MIN/10 && digit< -8)) return 0;         
            rev=10*rev+digit;
            temp /= 10;
        }

        return rev;
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
        cout << ob.reverse(N) << endl;
        //cout<<"--"<<endl;
    }
    return 0;
}
// } Driver Code Ends