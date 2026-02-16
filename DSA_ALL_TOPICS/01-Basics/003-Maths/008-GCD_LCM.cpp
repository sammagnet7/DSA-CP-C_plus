#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
https://takeuforward.org/data-structure/find-gcd-of-two-numbers/
https://www.geeksforgeeks.org/problems/lcm-and-gcd4516/1

Problem Statement:
Given two integers a and b, write a function lcmAndGcd() to compute their LCM and GCD. The function inputs two integers a and b and returns a list containing their LCM and GCD.

Examples:

Input: a = 5 , b = 10
Output: [10, 5]
Explanation: LCM of 5 and 10 is 10, while their GCD is 5.
Input: a = 14 , b = 8
Output: [56, 2]
Explanation: LCM of 14 and 8 is 56, while their GCD is 2.
Input: a = 1 , b = 1
Output: [1, 1]
Explanation: LCM of 1 and 1 is 1, while their GCD is 1.
Expected Time Complexity: O(log(min(a, b))
Expected Auxiliary Space: O(1)

Constraints:
1 <= a, b <= 109
*/

class Solution
{
public:
    // Brute force Time: O( MIN(a,b) )
    int findGCD_BRUTE(int a, int b)
    {

        for (int divisor = min(a, b); divisor > 1; divisor--)
        {
            if (a % divisor == 0 && b % divisor == 0)
                return divisor;
        }
        return 1;
    }

    // Euclidean approach; Time:  O( MIN(a,b) )
    /*
    The Euclidean Algorithm is a method for finding the greatest common divisor of two numbers. It operates on the principle that the GCD of two numbers remains the same even if the smaller number is subtracted from the larger number.
    To find the GCD of n1 and n2 where n1 > n2:
    Repeatedly subtract the smaller number from the larger number until one of them becomes 0.
    Once one of them becomes 0, the other number is the GCD of the original numbers.
    */
    int findGCD_Euclidean_BETTER(int a, int b)
    {

        if (a == 0)
            return b;
        else if (b == 0)
            return a;

        else
        {
            int mini = min(a, b);
            int maxi = max(a, b);

            return findGCD_Euclidean_BETTER((maxi - mini), mini);
        }
    }

    // Euclidean Optimal approach: Time: O( Log [base ] MIN(a,b) )
    /* Instead of subtracting repeatedly, here we use remainder operator.
        This brings down the time complexity to logarithmic order.
    */
    int findGCD_Euclidean_OPTIMAL(int a, int b)
    {

        if (a == 0)
            return b;
        else if (b == 0)
            return a;

        else
        {
            int mini = min(a, b);
            int maxi = max(a, b);

            return findGCD_Euclidean_OPTIMAL((maxi % mini), mini);
        }
    }

    void lcmAndGcd(int a, int b)
    {
        // The GCD of two numbers is the largest number that divides both of them without leaving a remainder.

        // int gcd=findGCD(a,b);
        // int gcd=findGCD_Euclidean_BETTER(a,b);
        int gcd = findGCD_Euclidean_OPTIMAL(a, b);

        int lcm = (a * b) / gcd;

        cout<<"GCD: "<<gcd<<endl;
        cout<<"LCM: "<<lcm<<endl;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        Solution ob;

        ob.lcmAndGcd(a,b);
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends