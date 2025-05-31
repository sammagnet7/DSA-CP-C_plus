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
Sort Characters By Frequency
https://leetcode.com/problems/sort-characters-by-frequency/description/

Problem statement:
Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

Example 1:
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.


INPUT::::::
3
tree
cccaaa
Aabb

OUTPUT::::::
eetr 
cccaaa 
bbaA

-----------------------------------------------------------------------

 */
class Solution
{
public:
    //-----------------------------------------------------------------------
    // Optimal approach
    // Time: O(N)
    // Space: O(N)
    string frequencySort(string s)
    {

        int N = s.size();

        vector<pair<int, int>> freq(256, make_pair(0, 0)); // < char, <freq,char> >

        // O(N)
        for (int i = 0; i < N; i++)
        {
            int curChar = s[i];
            int count = freq[curChar].first;
            count++;
            freq[curChar] = {count, curChar};
        }

        // O(1) as freq arr is of size 256
        sort(freq.begin(), freq.end());

        string ans;

        for (int i = 255; i >= 0; i--)
        {
            int frequency = freq[i].first;
            char thisChar = freq[i].second;

            ans.append(frequency, thisChar); // DO NOT USE string concat here,
                                             // as it creates new strings every time
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
        cout << ob.frequencySort(input) << " ";
        // cout<< ob.reverseWords(input)<<" ";
        // cout<< ob.isIsomorphic(input1,input2);
        cout << endl;
    }
    return 0;
}