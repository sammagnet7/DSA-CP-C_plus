#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
https://www.naukri.com/code360/problems/reverse-bits_2181102?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf

Problem Statement:

There is a song concert going to happen in the city. The price of each ticket is equal to the number obtained after reversing the bits of a given 32 bits unsigned integer ‘n’.

Sample Input 1 :
12
Sample Output 1:
805306368
Explanation For Sample Input 1 :
Since the given number N = 12 is represented as 00000000000000000000000000001100 in its binary representation. So after reversing the bits, it will become 0110000000000000000000000000000, which is equal to 805306368 only. So the output is 805306368.
*/

class Solution
{
public:
    // Time complexity: O(log [base10] N)
    long reverseBits_using_ShiftOps(long N)
    {

        long rev = 0;

        for (int i = 0; i < 32; i++)
        {
            // Use of Bitwise AND operator;
            if ((N & ((long)1 << i)) > 0)
            { // check if ith bit from right is set
                rev += ((long)1 << (32 - i - 1));
            }
        }
        return rev;
    }

    long reverseBits_using_Array(long N)
    {
        unsigned int num = N;
        unsigned int rev = 0;

        vector<int> arr(32, 0);
        int idx = 0;
        while (num)
        {
            int digit = num % 2;
            arr[idx++] = digit;
            num /= 2;
        }

        for (int idx = 0; idx <= 31; idx++)
            rev = rev + (pow(2, (32 - idx - 1)) * arr[idx]);

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
        cout << ob.reverseBits_using_ShiftOps(N) << endl;
        cout << ob.reverseBits_using_Array(N) << endl;

        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends