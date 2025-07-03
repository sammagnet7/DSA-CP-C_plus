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
Title: Number of Substrings Containing All Three Characters

Links:
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
https://www.youtube.com/watch?v=xtqN4qlgr8s&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=9
https://takeuforward.org/plus/dsa/problems/number-of-substrings-containing-all-three-characters?tab=editorial
https://www.naukri.com/code360/problems/count-substring-with-abc_8160465

Problem statement:
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.


Eaxamples:
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

    Example 4:
    Input: s = "acbbcac"
    Output: 11


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // -------------------------------------------------------------------------------------------
    // Number of Substrings Containing All Three Characters
    // Approach1:
    //

    // // Optimal approach: Two pointer approach: 2 pass
    // // Time: O(2N)
    // // Space: O(3)
    // int numberOfSubstrings(string s)
    // {

    //     int N = s.size();
    //     int ans = 0;

    //     int l = 0;
    //     int r = 0;

    //     vector<int> lastSeen(3, 0); // O(3)

    //     while (r < N)
    //     { // O(N)

    //         lastSeen[s[r] - 'a']++;

    //         while (lastSeen['a' - 'a'] >= 1 && lastSeen['b' - 'a'] >= 1 && lastSeen['c' - 'a'] >= 1)
    //         { // O(N)
    //             ans += (N - r);
    //             lastSeen[s[l] - 'a']--;
    //             l++;
    //         }

    //         r++;
    //     }

    //     return ans;
    // }

    // ------------------------------------------------------
    // Approach2:
    //

    // // Optimal approach: Two pointer approach: single pass
    // Step1: For every char find minimum window left of it, having all the three chars ending at that char
    //
    // Time: O(N)
    // Space: O(1)
    int numberOfSubstrings(string s)
    {

        int N = s.size();
        int ans = 0;

        vector<int> lastSeen(3, -1); // O(3): stores last seen indexes of char

        int r = 0;

        while (r < N)
        { // O(N)

            lastSeen[s[r] - 'a'] = r; // storing last seen index for char s[r]

            if (lastSeen['a' - 'a'] >= 0 && lastSeen['b' - 'a'] >= 0 && lastSeen['c' - 'a'] >= 0)
            {

                int windowMinIdx = min(lastSeen[0], min(lastSeen[1], lastSeen[2]));

                int countEndingHere = windowMinIdx - 0 + 1;

                ans += countEndingHere;
            }

            r++;
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