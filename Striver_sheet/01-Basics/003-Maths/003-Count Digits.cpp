#include <iostream>
#include <cmath> // needed for Log operation
using namespace std;

/*
https://takeuforward.org/data-structure/count-digits-in-a-number/

Problem Statement: Given an integer N, return the number of digits in N.
*/


class Solution
{
public:

    // Brute force: Time complexity: O(log [base10] N)
    int countDigits_BRUTE(int N)
    {
        // code here
        int temp = N;
        int count = 0;

        while (temp)
        {
            count++;
            temp /= 10;
        }
        return count;
    }

    // Optimal approach: Time complexity: O(1)
    /*
    The logarithmic base 10 of a positive integers gives the number of digits in n. 
    */
    int countDigits_OPTIMAL(int N){
        return (int)log10(N)+1;
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
        cout << ob.countDigits_BRUTE(N) << endl;
        cout << ob.countDigits_OPTIMAL(N) << endl;
        cout<<"--"<<endl;
    }
    return 0;
}
// } Driver Code Ends