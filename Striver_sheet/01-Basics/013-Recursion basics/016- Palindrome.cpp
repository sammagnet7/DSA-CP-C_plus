#include <iostream>
#include <string>

using namespace std;

/*
https://takeuforward.org/data-structure/check-if-the-given-string-is-palindrome-or-not/
https://leetcode.com/problems/valid-palindrome/description/

Problem statement:
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.
Given a string s, return true if it is a palindrome, or false otherwise.

Example 1:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

Constraints:
1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.
*/

class Solution
{
public:
    // Time: O(Length of S)
    bool isPalindrome(string s)
    {
        int l = 0, r = s.size() - 1;

        while (l <= r)
        {
            if (!isalnum(s[l]))
                l++;
            else if (!isalnum(s[r]))
                r--;
            else
            {
                if (tolower(s[l]) != tolower(s[r]))
                    return false;
                else
                {
                    l++;
                    r--;
                }
            }
        }
        return true;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    cin.ignore();
    cout << endl;

    while (t--)
    {
        string s;
        getline(cin, s);
        cout << s << endl;
        Solution ob;

        cout << boolalpha;
        cout << ob.isPalindrome(s) << endl;
        cout << "--" << endl;
        cout << noboolalpha;
    }
    return 0;
}
// } Driver Code Ends