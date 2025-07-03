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
#include <unordered_set>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

/*

1. Title: Minimum Window Substring

Links:
https://www.youtube.com/watch?v=WJaij9ffOIY&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=12
https://takeuforward.org/plus/dsa/problems/minimum-window-substring-?tab=editorial
https://leetcode.com/problems/minimum-window-substring/description/

Problem statement:
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

Examples:
    Example 1:
    Input: s = "ADOBECODEBANC", t = "ABC"
    Output: "BANC"
    Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

    Example 2:
    Input: s = "a", t = "a"
    Output: "a"
    Explanation: The entire string s is the minimum window.

    Example 3:
    Input: s = "a", t = "aa"
    Output: ""
    Explanation: Both 'a's from t must be included in the window.
    Since the largest window of s only has one 'a', return empty string.


Constraints:
    m == s.length
    n == t.length
    1 <= m, n <= 105
    s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //------------------------------------------------------------------------
    // 1. Minimum Window Substring
    //

    // Optimal approach: Two pointer approach
    // Uses hash where target strings chars' counts are stored prehand
    // While traversing the given string decrement the map's char  frequency
    // while expanding (i.e. r++) check for freq==0 indicates one char's all occurences are met
    // While shrinking (i.e. l++) check for freq>0 indicates one char's all occurences not met
    //
    //  Time: O(2M + N)
    //  Space: O(256)
    string minWindow(string s, string t)
    {

        int m = s.size();
        int n = t.size();

        vector<int> hash(256);
        int totUniqCount;

        for (int i = 0; i < n; i++)
        { // O(N)
            if (hash[t[i]] == 0)
                totUniqCount++;
            hash[t[i]]++;
        }

        int minLen = INT_MAX;
        int startIdx = -1;
        // int totUniqCount = mp.size();
        int curUniqCount = 0;
        int l = 0;
        int r = 0;

        while (r < m)
        { // O(M)
            hash[s[r]]--;

            if (hash[s[r]] == 0)
            { // cur char's all occurences found
                curUniqCount++;
            }

            while (curUniqCount == totUniqCount)
            { // O(M) : Shrinking to find minimum one
                int len = r - l + 1;
                if (len < minLen)
                {
                    minLen = len;
                    startIdx = l;
                }

                hash[s[l]]++;
                if (hash[s[l]] == 1)
                { // Current char's atleast one occurences is missing
                    curUniqCount--;
                }
                l++;
            }

            r++;
        }

        if (startIdx == -1) // edge case handle
            return "";
        return s.substr(startIdx, minLen);
    }
};

int main()
{
    return 0;
}
