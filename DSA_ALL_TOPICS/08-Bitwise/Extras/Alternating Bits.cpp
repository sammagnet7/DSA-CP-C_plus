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

1. Title: Binary Number with Alternating Bits

Links:
https://leetcode.com/problems/binary-number-with-alternating-bits/description/


Problem statement:
Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.



Example 1:
Input: n = 5
Output: true
Explanation: The binary representation of 5 is: 101

Example 2:
Input: n = 7
Output: false
Explanation: The binary representation of 7 is: 111.

Example 3:
Input: n = 11
Output: false
Explanation: The binary representation of 11 is: 1011.


Constraints:
1 <= n <= 231 - 1
-----------------------------------------------------------------------

*/

class Solution
{
public:
    /*
     * METHOD: hasAlternatingBits (Approach 1: XOR Trick)   [OPTIMAL]
     * ----------------------------------------------------------------
     * APPROACH: Pattern Matching with XOR
     * Instead of looping, we use the property that alternating bits (010101)
     * create a specific pattern when shifted and XORed.
     *
     * LOGIC:
     * 1. Shift: 'shiftedNum = n >> 1'.
     * If n is alternating (e.g., 1010), shifted is (0101).
     * 2. XOR: 'xOrVal = n ^ shiftedNum'.
     * - 1 ^ 0 = 1
     * - 0 ^ 1 = 1
     * If 'n' is truly alternating, every position will differ from its neighbor.
     * Result: A stream of ALL 1s (e.g., 1111).
     * 3. Check All 1s:
     * - A number with all 1s (like 7=111, 15=1111) has a special property:
     * (X & (X + 1)) == 0.
     * - Example (X=7, 111): X+1=8 (1000). 0111 & 1000 = 0000.
     *
     * CORNER CASE:
     * - Use 'long long' for 'xOrVal' to prevent overflow when doing (xOrVal + 1)
     * if the input 'n' is the maximum integer (INT_MAX).
     *
     * COMPLEXITY:
     * - Time: O(1) -> Constant number of operations.
     * - Space: O(1).
     */
    bool hasAlternatingBits(int n)
    {

        // Use long long to handle potential overflow during (xOrVal + 1) check
        long long num = n;
        long long shiftedNum = num >> 1;

        // Step 1 & 2: Generate a number that SHOULD be all 1s
        long long xOrVal = (num ^ shiftedNum);

        // Step 3: Verify if 'xOrVal' is actually all 1s (Power of 2 minus 1)
        // If xOrVal is 111...1, adding 1 makes it 100...0.
        // ANDing them together results in 0.
        if ((xOrVal & (xOrVal + 1)) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Solution
{
public:
    /*
     * METHOD: hasAlternatingBits (Approach 2: Simulation)  [Sub-optimal]
     * ------------------------------------------------------------------
     * APPROACH: Iterative State Machine
     * We simulate the process of reading bits from right to left (LSB to MSB).
     * We maintain an 'expectedBit' state that toggles between 0 and 1.
     *
     * LOGIC:
     * 1. Initialize: Get the very first bit (LSB) of 'n'. This is our first expectation.
     * 2. Loop: While 'n' has bits remaining (> 0):
     * - Check: Does the current LSB (n & 1) match 'expectedBit'?
     * - If mismatch: Return false immediately.
     * - Update: Toggle 'expectedBit' (0 -> 1, 1 -> 0) using logical NOT (!).
     * - Advance: Right shift 'n' to process the next bit.
     *
     * COMPLEXITY:
     * - Time: O(log N) -> Proportional to number of bits (max 32 iterations).
     * - Space: O(1) -> Uses only a few integer variables.
     */
    bool hasAlternatingBits(int n)
    {

        // Start by expecting the first bit we see (e.g., if n=...101, expect 1)
        int expectedBit = n & 1;

        while (n)
        {

            // Validation Step:
            // Compare the current actual bit (n & 1) with our expectation.
            if ((n & 1) != expectedBit)
            {
                return false;
            }

            // State Update:
            // Flip expectation for the next position.
            // !0 becomes 1, !1 becomes 0.
            expectedBit = (!expectedBit);

            // Move to the next bit (divide by 2)
            n >>= 1;
        }

        // If we finished the loop without returning false, all bits matched.
        return true;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
