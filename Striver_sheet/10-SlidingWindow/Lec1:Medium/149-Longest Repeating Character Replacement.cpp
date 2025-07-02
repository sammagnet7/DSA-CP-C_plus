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

1. Title: Longest Repeating Character Replacement

Links:
https://www.youtube.com/watch?v=_eNhaDCr6P0&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=8
https://takeuforward.org/plus/dsa/problems/longest-repeating-character-replacement?tab=editorial
https://leetcode.com/problems/longest-repeating-character-replacement/description/

Problem statement:
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.

Examples:
    Example 1:
    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.

    Example 2:
    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.
    There may exists other ways to achieve this answer too.

Note: s consists of only uppercase English letters.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Title: Longest Repeating Character Replacement
// Approach1:
//

// // Sub-optimal approach: 2 pointer using frequency array
// // Time: O(N + (N*26))
// // Space: O(26)
// int characterReplacement(string s, int k)
// {

//     int ans = 0;
//     int N = s.size();

//     int l = 0;
//     int r = 0;
//     vector<int> frq(26, 0); // O(26): stores frequency of each char
//     int maxFrq = 0;

//     while (r < N)
//     { // O(N)
//         int cur = s[r] - 'A';
//         frq[cur]++;
//         maxFrq = max(maxFrq, frq[cur]);

//         int alterCount = (r - l + 1) - maxFrq;

//         while (alterCount > k)
//         { // O(N)
//             int curLeft = s[l] - 'A';
//             frq[curLeft]--;

//             maxFrq = 0;
//             for (int f : frq)
//             { // O(26)
//                 maxFrq = max(maxFrq, f);
//             }

//             l++;
//             alterCount = (r - l + 1) - maxFrq;
//         }

//         ans = max(ans, (r - l + 1));
//         r++;
//     }

//     return ans;
// }

// Approach2:
//

// Optimal approach: 2 pointer using frequency array, single pass
// Time: O(N)
// Space: O(26)
int characterReplacement(string s, int k)
{

    int ans = 0;
    int N = s.size();

    int l = 0;
    int r = 0;
    vector<int> frq(26, 0); // O(26): stores frequency of each char
    int maxFrq = 0;

    while (r < N)
    { // O(N)

        int cur = s[r] - 'A';
        frq[cur]++;
        maxFrq = max(maxFrq, frq[cur]);

        int alterCount = (r - l + 1) - maxFrq;

        if (alterCount > k)
        { // O(1): Not using while loop as no meaning of shrinking already found max size
            int curLeft = s[l] - 'A';
            frq[curLeft]--;

            // Removing extra loop for updating maxFrq to 2nd largest one

            l++;
            alterCount = (r - l + 1) - maxFrq;
        }

        if (alterCount <= k)
        {
            ans = max(ans, (r - l + 1));
        }
        r++;
    }

    return ans;
}

int main()
{
    return 0;
}
