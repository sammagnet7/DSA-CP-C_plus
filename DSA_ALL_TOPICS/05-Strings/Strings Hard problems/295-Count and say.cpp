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

1. Title: Count and say

Links:
https://takeuforward.org/plus/dsa/problems/count-and-say?tab=editorial
https://leetcode.com/problems/count-and-say/


Problem statement:
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

    countAndSay(1) = "1"
    countAndSay(n) is the run-length encoding of countAndSay(n - 1).

Run-length encoding (RLE) is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "3322251" we replace "33" with "23", replace "222" with "32", replace "5" with "15" and replace "1" with "11". Thus the compressed string becomes "23321511".

Given a positive integer n, return the nth element of the count-and-say sequence.


Example 1:
    Input: n = 4
    Output: "1211"
    Explanation:
    countAndSay(1) = "1"
    countAndSay(2) = RLE of "1" = "11"
    countAndSay(3) = RLE of "11" = "21"
    countAndSay(4) = RLE of "21" = "1211"

Example 2:
    Input: n = 1
    Output: "1"
    Explanation:
    This is the base case.


Constraints:
1 <= n <= 30

Follow up: Could you solve it iteratively?


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Count and say
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ---------------------------------
    // Approach 1 - Recursive (Top-down)
    // ---------------------------------
    /**
     * @brief Generates the nth element of the Count-and-Say sequence recursively.
     * * * 🧠 INTUITION & APPROACH:
     * The problem is inherently recursive: f(n) depends entirely on f(n-1).
     * 1. Base Case: If n == 1, return the mathematical starting point "1".
     * 2. Recursive Step: Ask the function to compute the string for `n - 1`.
     * 3. Run-Length Encoding (RLE): Iterate through the returned string, counting
     * consecutive identical characters.
     * 4. When a streak breaks, append the string representation of the count,
     * followed by the character itself.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(L_1 + L_2 + ... + L_n) where L_i is the string length.
     * - Space Complexity: O(n) for the recursive call stack.
     */
    string countAndSay(int n)
    {

        // 1. Base case
        if (n == 1)
        {
            return "1";
        }

        // 2. Recursive leap of faith
        string ret = countAndSay(n - 1);

        string rle = "";

        // Pre-allocate memory to prevent dynamic resizing overhead
        rle.reserve(ret.length() * 2);

        char prevChar = ret[0];
        int count = 1;

        // 3. Process the returned string
        for (int i = 1; i < ret.length(); ++i)
        {

            if (ret[i] == prevChar)
            {
                ++count;
            }
            else
            {
                // GENERAL APPROACH:
                // Use to_string() to safely handle counts of any size (10, 100, etc.)
                // ⚙️ C++ PRO-TIP OPTIMIZATION:
                // Due to Conway's constant, the count in this specific sequence
                // will never exceed 3. Therefore, you can bypass the overhead of
                // `to_string` and use fast ASCII math: `rle.push_back(count + '0');`
                rle.append(to_string(count));
                rle.push_back(prevChar);

                // Reset trackers for the new character
                prevChar = ret[i];
                count = 1;
            }
        }

        // 4. Append the final streak after the loop ends
        rle.append(to_string(count));
        rle.push_back(prevChar);

        return rle;
    }

    // ---------------------------------------
    // Approach 2 - Iterative (Bottom-up)
    // ---------------------------------------

    /**
     * @brief Generates the nth element of the Count-and-Say sequence iteratively.
     * * * 🧠 INTUITION & APPROACH:
     * Starting with the base case "1", we iteratively generate the next sequence
     * `n - 1` times. In each iteration, we read the previous string (`rle`),
     * count consecutive identical characters, and build the `next_seq` using
     * standard Run-Length Encoding.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(L_1 + L_2 + ... + L_n) where L_i is the length of the
     * string at step i.
     * - Space Complexity: O(L_n) to store the final generated string.
     */
    string countAndSay(int n)
    {

        // Base case
        string rle = "1";

        // Generate the sequence n-1 times
        for (int itr = 2; itr <= n; ++itr)
        {

            string next_seq = "";

            // OPTIMIZATION 1: Pre-allocate memory to prevent dynamic resizing overhead
            next_seq.reserve(2 * rle.length());

            char prevChar = rle[0];
            int count = 1;

            // Iterate through the PREVIOUS string to build the NEXT string
            for (int i = 1; i < rle.length(); ++i)
            {

                char curChar = rle[i];

                if (curChar == prevChar)
                {
                    ++count;
                }
                else
                {
                    // GENERAL APPROACH: safely handle counts of any size
                    // ⚙️ CONWAY OPTIMIZATION:
                    // Because of Conway's constant, count never exceeds 3 in this specific
                    // sequence. You could bypass to_string() with: `next_seq.push_back(count + '0');`
                    next_seq.append(to_string(count));
                    next_seq.push_back(prevChar);

                    prevChar = curChar;
                    count = 1;
                }
            }

            // Don't forget the final streak!
            next_seq.append(to_string(count));
            next_seq.push_back(prevChar);

            // OPTIMIZATION 2: O(1) Pointer Swap
            // Instead of deep-copying strings, std::move safely transfers memory
            // ownership from `next_seq` into `rle`, dropping the old `rle` memory.
            rle = std::move(next_seq);
        }

        return rle;
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------
//

int main()
{
    return 0;
}