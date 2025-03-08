#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
https://leetcode.com/problems/palindrome-number/

Problem Statement:
Given an integer x, return true if x is a palindrome, and false otherwise.

Example 1:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 

Constraints: -231 <= x <= 231 - 1
 

Follow up: Could you solve it without converting the integer to a string?
*/

class Solution
{
public:
    //Better approach: Time complexity: O(log [base10] N)
    bool isPalindrome_woString(int N) {

        if(N<0) return false;

        int num=N;
        unsigned int rev=0; // we need bigger data type than int. That's why using 'unsigned'
        while(num){
            int digit=num%10;
            rev = rev*10 + digit;
            num /=10;
        }
        if(N==rev) return true;
        else return false;
    }

    // Time complexity: O(log [base10] N)
    bool isPalindrome_withString(int N) {
        string num_str=to_string(N);
        int len=num_str.size();

        for(int i=0; i<len/2; i++){
            if(num_str[i] != num_str[len-1-i])
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

        cout << std::boolalpha; 
        cout << ob.isPalindrome_woString(N) << endl;
        cout << ob.isPalindrome_withString(N) << endl;
        cout << std::noboolalpha;

        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends