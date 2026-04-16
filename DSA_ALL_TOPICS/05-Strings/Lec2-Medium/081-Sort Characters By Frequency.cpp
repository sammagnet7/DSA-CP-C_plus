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

Title: Sort Characters By Frequency

Linke:
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


Constraints:
    1 <= s.length <= 5 * 10^5
    s consists of uppercase and lowercase English letters and digits.


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

//-------------------------------------------------------------------------------
// 1. Title: Sort Characters By Frequency
//-------------------------------------------------------------------------------

// Type Aliasing: Clean, modern C++ practice for readability
using P = pair<int, int>;

class Solution
{
public:
    /**
     * @brief Sorts characters by their frequency in descending order.
     * * * 🧠 IDEA & INTUITION:
     * Sorting a string of 500,000 characters using standard sorting algorithms
     * takes O(N log N) time, which is too slow. Instead, we use a Frequency Map.
     * Because there are only 256 possible ASCII characters, we map them to a
     * fixed-size array. We then sort this tiny 256-element array based on
     * frequency. Finally, we reconstruct the string using the sorted counts.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N). Counting characters takes O(N). Sorting the fixed
     * 256-element array takes O(1) time (since 256 log 256 is a mathematical constant).
     * Rebuilding the string takes O(N). Total = O(N) linear time.
     * - Space Complexity: O(1) auxiliary space. We use exactly 256 pairs, which
     * never scales up regardless of how large the input string gets.
     * (Note: The O(N) space for the returned string is not counted against auxiliary space).
     */
    string frequencySort(string s)
    {

        // Allocate a fixed vector of 256 elements for all possible ASCII characters
        vector<P> freq(256);

        // 1. Initialize the pairs {character_ascii, count}
        for (int i = 0; i < 256; ++i)
        {
            freq[i] = {i, 0};
        }

        // 2. Count the frequencies in a single pass
        for (char c : s)
        {
            freq[c].second += 1;
        }

        // 3. Sort by frequency descending using a custom lambda comparator
        sort(freq.begin(), freq.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

        string ans = "";

        // ⚙️ OPTIMIZATION 1 (Memory): Pre-allocate exact memory needed to
        // prevent expensive dynamic array resizing under the hood.
        ans.reserve(s.length());

        // 4. Build the result using C++17 Structured Bindings
        for (auto [idx, fr] : freq)
        {

            // ⚙️ OPTIMIZATION 2 (Speed): If frequency is 0, we can stop entirely
            // because the rest of the array is sorted descending to 0.
            if (fr == 0)
                break;

            // ⚙️ OPTIMIZATION 3 (Speed): Write 'fr' number of characters directly
            // to memory in one operation instead of using a slow while-loop.
            ans.append(fr, (char)idx);
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