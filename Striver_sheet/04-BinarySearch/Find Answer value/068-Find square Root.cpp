#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Finding Sqrt of a number using Binary Search

https://takeuforward.org/binary-search/finding-sqrt-of-a-number-using-binary-search/
https://leetcode.com/problems/sqrtx/description/
https://www.naukri.com/code360/problems/square-root-integral_893351?leftPanelTabValue=PROBLEM

Problem statement:
Given a non-negative integer x, return the square root of x rounded down to the nearest integer.


Examples:

Example 1:
Input: x = 4
Output: 2
Explanation: The square root of 4 is 2, so we return 2.

Example 2:
Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.


INPUT::::::
4
4
8
0
2147395599

OUTPUT::::::
2
2
0
46339

 */
class Solution
{
public:
    // Optimal approach: Using Binary search
    // Time: O(Log N)
    // SPacE: O(1)
    int mySqrt(int x)
    {

        int l = 1, r = x;
        int ans = 0;

        while (l <= r)
        {
            long mid = l - (l - r) / 2;

            long mulV = mid * mid;

            if (mulV == x)
                return mid;
            else if (mulV < x)
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }

        return ans;
    }

    // // optimal approach: using built-in func
    // // Time: O(Log N)
    // // Space: O(1)
    // int mySqrt(int x) {
    //     return sqrt(x);
    // }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int x;
        cin >> x;
        // cin.ignore();

        // string input;
        // getline(cin, input);

        // vector<int> arr;
        // stringstream ss(input);
        // int num;

        // while (ss >> num)
        // {
        //     arr.push_back(num);
        // }

        Solution ob;

        cout << ob.mySqrt(x);
        cout << endl;
    }
    return 0;
}