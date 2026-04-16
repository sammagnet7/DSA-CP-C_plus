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
https://www.youtube.com/watch?v=xtqN4qlgr8s&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=9
https://takeuforward.org/plus/dsa/problems/number-of-substrings-containing-all-three-characters?tab=editorial

https://www.naukri.com/code360/problems/count-substring-with-abc_8160465
https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/


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


Constraints:
    3 <= s.length <= 5 x 10^4
    s only consists of a, b or c characters.


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    //-----------------------------------
    // Approach 1: Sliding window 2 pass [Sub-optimal]
    //-----------------------------------

    /**
     * @brief Calculates valid substrings using a traditional Sliding Window.
     * * * 🧠 INTUITION & APPROACH:
     * We use a two-pointer approach (left 'l' and right 'r') to create a "window".
     * 1. Expand the window by moving 'r' to the right and adding characters to our frequency map.
     * 2. The moment our window becomes VALID (contains at least one 'a', 'b', and 'c'):
     * - Every substring starting at 'l' and ending anywhere from 'r' to the end of
     * the string (n-1) is mathematically guaranteed to be valid.
     * - Therefore, we can instantly add `n - r` to our answer.
     * 3. Shrink the window by removing the character at 'l' and moving 'l' forward
     * to see if we can find a smaller valid window.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the string length. Both 'l' and 'r' only
     * move forward, meaning we process each character at most twice.
     * - Space Complexity: O(1) auxiliary space. The vector is fixed at size 3.
     */
    int numberOfSubstrings(string s)
    {

        int n = s.length();

        // Fixed frequency map for 'a', 'b', and 'c'
        vector<int> freq(3, 0);

        int ans = 0;
        int l = 0, r = 0;

        // Iterate through the string with the right pointer
        while (r < n)
        {

            // 1. EXPAND: Add the current character to our window
            ++freq[s[r] - 'a'];

            // 2. EVALUATE: While the window is valid, mathematically calculate the permutations
            while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0)
            {

                // If the substring from l to r is valid, then extending it further
                // right up to the end of the string 'n' will also be valid.
                ans += (n - r);

                // 3. SHRINK: Remove the leftmost character and move the left pointer
                --freq[s[l] - 'a'];
                ++l;
            }

            // Move right pointer to evaluate the next character
            ++r;
        }

        return ans;
    }

    //----------------------------------------------------
    // Approach 2: Track last seen index: 1 Pass [OPTIMAL]
    //----------------------------------------------------

    /**
     * @brief Calculates substrings containing at least one 'a', 'b', and 'c'.
     * * * 🧠 INTUITION & APPROACH:
     * Instead of a shrinking sliding window, we track the most recent index where
     * we saw each character. At any given index `i`, if we have seen all three
     * characters, the "bottleneck" (the furthest we have to look back to secure
     * all three) is the minimum of their last seen indices.
     * Any string starting at `0, 1, 2... min_idx` and ending at `i` contains
     * all three characters. Thus, we add `min_idx + 1` to our total count.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string. We iterate
     * through the string exactly once.
     * - Space Complexity: O(1) auxiliary space. We use a fixed array of size 3.
     */
    int numberOfSubstrings(string s)
    {

        // Fixed array to track the last seen index of 'a', 'b', and 'c'.
        // We initialize with -1 to safely indicate "this character hasn't appeared yet".
        int lastSeen[3] = {-1, -1, -1};
        int count = 0;

        for (int i = 0; i < s.length(); ++i)
        {

            // 1. UPDATE STATE: Record the current index for this specific character.
            // s[i] - 'a' maps 'a'->0, 'b'->1, 'c'->2.
            lastSeen[s[i] - 'a'] = i;

            // 2. CHECK VALIDITY: Have all three characters appeared at least once?
            if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1)
            {

                // 3. FIND THE BOTTLENECK:
                // The minimum of these three indices tells us the closest we can get
                // to the start of the string while STILL capturing an 'a', 'b', and 'c'.
                int minIdx = min({lastSeen[0], lastSeen[1], lastSeen[2]});

                // 4. THE MATHEMATICAL TRICK:
                // If a valid substring ending at 'i' can start as late as 'minIdx',
                // then it is mathematically guaranteed that starting at any index BEFORE
                // 'minIdx' (like minIdx-1, minIdx-2... all the way to 0) will also be valid!
                // Because arrays are 0-indexed, there are exactly `minIdx + 1` valid
                // starting positions.
                count += (minIdx + 1);
            }
        }

        return count;
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