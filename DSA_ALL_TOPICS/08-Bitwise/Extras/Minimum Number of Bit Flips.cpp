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
#include <cstdint>

using namespace std;

/*

1. Title: Minimum Number of Flips to Make the Binary String Alternating

Links:
https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating


Problem statement:
You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:

Type-1: Remove the character at the start of the string s and append it to the end of the string.
Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
Return the minimum number of type-2 operations you need to perform such that s becomes alternating.

The string is called alternating if no two adjacent characters are equal.

For example, the strings "010" and "1010" are alternating, while the string "0100" is not.


Example 1:
Input: s = "111000"
Output: 2
Explanation: Use the first operation two times to make s = "100011".
Then, use the second operation on the third and sixth elements to make s = "101010".

Example 2:
Input: s = "010"
Output: 0
Explanation: The string is already alternating.

Example 3:
Input: s = "1110"
Output: 1
Explanation: Use the second operation on the second element to make s = "1010".


Constraints:
1 <= s.length <= 10^5
s[i] is either '0' or '1'.


-----------------------------------------------------------------------

*/

//-------------
// Approach 1:
//-------------

/**
 * Idea:
 * 1. Type-1 Operation (Cyclic Shift): Removing the first character and appending it
 * to the end is essentially rotating the string. We can easily simulate ALL possible
 * rotations by concatenating the string to itself: `s = s + s`.
 *
 * A sliding window of size N over this doubled string represents every possible
 * string configuration after applying any number of Type-1 operations.
 *
 * 2. Type-2 Operation (Bit Flip): An alternating binary string can only take two forms:
 * - Pattern A: "101010..." (starts with '1')
 * - Pattern B: "010101..." (starts with '0')
 *
 * * Approach:
 * 1. Store the original length `n` and double the string `s += s`.
 * 2. Use a sliding window of size `n` across the doubled string.
 * 3. As the window expands to the right (index `i`), compare the current character
 * against what it *should* be for Pattern A and Pattern B. If it doesn't match,
 * increment the respective flip counters (`ans1`, `ans2`).
 * 4. Once the window size exceeds `n` (when `i >= n`), we must slide the left side
 * of the window forward. We look at the character that is leaving the window
 * `s[i - n]`. If it was recorded as a mismatch, we decrement the respective counter
 * because it is no longer part of our current rotation.
 * 5. Whenever the window has reached exactly size `n` (when `i >= n - 1`), record
 * the minimum of our counters.
 *
 * * Time Complexity: O(N)
 * We iterate through the doubled string of size 2N exactly once. All window updates
 * (checking expected chars, incrementing/decrementing) take O(1) time.
 *
 * * Space Complexity: O(N)
 * We allocate extra space to double the string.
 * Note: This can technically be optimized to O(1) space by not physically doubling
 * the string and instead using modulo arithmetic `s[i % n]`, but doubling the string
 * often results in cleaner, more readable code with negligible overhead.
 *
 */
class Solution
{
public:
    int minFlips(string s)
    {
        int n = s.length();

        // Double the string to simulate all Type-1 cyclic shifts
        s += s;

        int ans1 = 0; // Flips required to match Pattern A: "1010..."
        int ans2 = 0; // Flips required to match Pattern B: "0101..."
        int minFlips = INT_MAX;

        for (int i = 0; i < s.length(); ++i)
        {

            // Expected characters at index i for both patterns
            char expectedA = (i % 2 == 0) ? '1' : '0';
            char expectedB = (i % 2 == 0) ? '0' : '1';

            // Expand window: Add the new character's mismatches
            if (s[i] != expectedA)
                ++ans1;
            if (s[i] != expectedB)
                ++ans2;

            // Shrink window: Remove the outgoing character's mismatches if window > n
            if (i >= n)
            {
                // The character that just left the window is at index (i - n)
                char old_expectedA = ((i - n) % 2 == 0) ? '1' : '0';
                char old_expectedB = ((i - n) % 2 == 0) ? '0' : '1';

                if (s[i - n] != old_expectedA)
                    --ans1;
                if (s[i - n] != old_expectedB)
                    --ans2;
            }

            // Once the window reaches the required size 'n', evaluate the minimum
            if (i >= n - 1)
            {
                minFlips = min({minFlips, ans1, ans2});
            }
        }

        return minFlips;
    }
};
int main()
{
    Solution *obj = new Solution();

    return 0;
}
