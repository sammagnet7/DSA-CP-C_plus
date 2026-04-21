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

1. Title: Find the String with LCP

Links:
https://leetcode.com/problems/find-the-string-with-lcp/description/


Problem statement:
We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:

lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.



Example 1:
    Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
    Output: "abab"
    Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".

Example 2:
    Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
    Output: "aaaa"
    Explanation: lcp corresponds to any 4 letter string with a single distinct letter. The lexicographically smallest of them is "aaaa".

Example 3:
    Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
    Output: ""
    Explanation: lcp[3][3] cannot be equal to 3 since word[3,...,3] consists of only a single letter; Thus, no answer exists.


Constraints:
    1 <= n == lcp.length == lcp[i].length <= 1000
    0 <= lcp[i][j] <= n


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

*/

// ============================================================================
// Approach: Greedy "Lock-In" Assignment + DP Validation
// ============================================================================

class Solution
{
public:
    /**
     * Finds the lexicographically smallest string that matches the given LCP matrix.
     * 1. The "Lock-In" Strategy:
     * If lcp[i][j] > 0, it is a mathematical guarantee that word[i] and word[j]
     * are the exact same character. We sweep through the array, and whenever we
     * find an empty spot, we assign it the lowest available letter (starting at
     * 'a'). We then instantly lock in that same letter for every index j that
     * shares a prefix with i. We never change a letter once it is locked.
     * * 2. The O(N^2) DP Validator:
     * Instead of simulating string matches forward (which causes O(N^3)), we
     * validate the matrix backwards. If word[i] matches word[j], the LCP at
     * that spot is simply 1 + lcp[i+1][j+1]. Because we are going backwards,
     * lcp[i+1][j+1] is already guaranteed to be validated! This drops the
     * validation time to pure O(1) per cell.
     * ============================================================================
     * Complexity:
     * - Time: O(N^2). Phase 1 loops through the N x N grid once to group and
     * assign characters. Phase 2 loops backwards through the N x N grid to
     * validate.
     * - Space: O(N). We only allocate a single string of length N. No extra
     * matrices or vectors are required.
     * ============================================================================
     */
    string findTheString(vector<vector<int>> &lcp)
    {

        int n = lcp.size();

        // Initialize an empty string with spaces
        string ans(n, ' ');
        char curr_char = 'a';

        // --------------------------------------------------------
        // Phase 1: Greedy "Lock-In" Assignment
        // --------------------------------------------------------
        for (int i = 0; i < n; ++i)
        {

            // If this index hasn't been assigned a character yet
            if (ans[i] == ' ')
            {

                // If we run out of lowercase English letters, the matrix
                // is mathematically impossible. Do not wrap around.
                if (curr_char > 'z')
                {
                    return "";
                }

                // Lock in the current character for `i` and ANY index `j`
                // that shares a prefix with `i`.
                for (int j = i; j < n; ++j)
                {
                    if (lcp[i][j] > 0)
                    {
                        ans[j] = curr_char;
                    }
                }

                // Move to the next available character in the alphabet
                curr_char++;
            }
        }

        // --------------------------------------------------------
        // Phase 2: O(N^2) DP Matrix Validation
        // --------------------------------------------------------
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {

                int expected_lcp = 0;

                if (ans[i] == ans[j])
                {
                    expected_lcp = 1;
                    // Safely look diagonally down-right
                    if (i + 1 < n && j + 1 < n)
                    {
                        expected_lcp += lcp[i + 1][j + 1];
                    }
                }

                // Reject the matrix if it contradicts our locked-in string.
                if (lcp[i][j] != expected_lcp)
                {
                    return "";
                }
            }
        }

        return ans;
    }
};

int main()
{

    return 0;
}
