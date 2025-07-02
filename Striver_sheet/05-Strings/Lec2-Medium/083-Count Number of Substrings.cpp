#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

/*
Number of Substrings Containing All Three Characters

https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
https://www.naukri.com/code360/problems/count-substring-with-abc_8160465

Problem statement:
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.



Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb".
Example 3:

Input: s = "abc"
Output: 1


INPUT::::::


OUTPUT::::::


-----------------------------------------------------------------------

 */
class Solution
{
public:
    //-----------------------------------------------------------------------
    // Optimal approach: Two pointer approach
    // Time: O(N)
    // Space: O(1)
    int numberOfSubstrings(string s)
    {
        int N = s.size();
        int ans = 0;

        int l = 0;
        int r = 0;

        int countA = 0, countB = 0, countC = 0;

        while (r <= N)
        { // Using equal sign to handle r's increment by 1 in prev iteration
            if (countA >= 1 && countB >= 1 && countC >= 1)
            {
                ans += (N - r + 1); // +1 because r is getting incremented by 1 in prev iteration
                if (s[l] == 'a')
                    countA--;
                else if (s[l] == 'b')
                    countB--;
                else if (s[l] == 'c')
                    countC--;
                l++;
            }
            else
            {
                if (s[r] == 'a')
                    countA++;
                else if (s[r] == 'b')
                    countB++;
                else if (s[r] == 'c')
                    countC++;
                r++;
            }
        }

        return ans;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        string input;
        getline(cin, input);

        // int m, n;
        /// cin >> m >> n;

        // vector<vector<int>> matrix(m, vector<int>(n));

        // Read the matrix
        // for (int i = 0; i < m; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cin >> matrix[i][j];
        //     }
        // }

        Solution ob;
        cout << ob.numberOfSubstrings(input) << " ";
        // cout<< ob.reverseWords(input)<<" ";
        // cout<< ob.isIsomorphic(input1,input2);
        cout << endl;
    }
    return 0;
}