#include <iostream>
#include <cmath>
#include<string> // to_string()

using namespace std;

/*
https://takeuforward.org/maths/check-if-a-number-is-armstrong-number-or-not/

Problem Statement:
You are given an integer 'n'. Return 'true' if 'n' is an Armstrong number, and 'false' otherwise.

An Armstrong number is a number (with 'k' digits) such that the sum of its digits raised to 'kth' power is equal to the number itself. For example, 371 is an Armstrong number because 3^3 + 7^3 + 1^3 = 371.

Sample Input 1 :
1
Sample Output 1 :
true
Explanation of Sample Input 1 :
1 is an Armstrong number as, 1^1 = 1.

Sample Input 2 :
103
Sample Output 2 :
false

Sample Input 3 :
1634
Sample Output 3 :
true
Explanation of Sample Input 3 :
1634 is an Armstrong number, as 1^4 + 6^4 + 3^4 + 4^4 = 1634
*/

class Solution
{
public:
    // Time complexity: O(N)
    bool checkArmstrong(int N){
        //int len= to_string(N).size(); // O(Log [base10] N)
        int len= log10(N) +1;   // O(1)

        int temp=N;
        int sum=0;
        while(temp){
            sum+= pow((temp%10), len);
            temp/=10;
        }
        return N==sum?true:false;
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
        cout << ob.checkArmstrong(N) << endl;
        cout<<noboolalpha;

        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends