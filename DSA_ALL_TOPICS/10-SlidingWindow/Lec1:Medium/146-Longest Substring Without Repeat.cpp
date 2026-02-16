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

1. Title: Longest Substring Without Repeating Characters

Links:
https://www.youtube.com/watch?v=-zSxTJkcdAo&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=3
https://takeuforward.org/data-structure/length-of-longest-substring-without-any-repeating-character/
https://takeuforward.org/plus/dsa/problems/longest-substring-without-repeating-characters?tab=editorial
https://leetcode.com/problems/longest-substring-without-repeating-characters/description/


Problem statement:
Given a string s, find the length of the longest substring without duplicate characters.

Examplse:
    Example 1:
    Input: s = "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.

    Example 2:
    Input: s = "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

    Example 3:
    Input: s = "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
    Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints:
    0 <= s.length <= 5 * 104
    s consists of English letters, digits, symbols and spaces.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1.
//

// Optimal approach: Sliding window
// Time: O(2N)
// Space: O(256)
int lengthOfLongestSubstring(string s)
{

    int N = s.size();
    int ans = 0;
    vector<int> track(256, -1); // O(256)

    int l = 0;
    int r = 0;
    int len = 0;

    while (l < N && r < N)
    {
        int curAscii = s[r];

        while (track[curAscii] != -1 && l < r)
        {
            track[s[l]] = -1;
            l++;
            len--;
        }

        track[curAscii] = 1;
        len++;
        ans = max(ans, len);
        r++;
    }

    return ans;
}
int main()
{
    return 0;
}
