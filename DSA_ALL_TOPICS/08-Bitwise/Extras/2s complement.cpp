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
#include <bitset>

using namespace std;

/*

1. Title: Complement of Base 10 Integer

Links:
https://leetcode.com/problems/number-complement/
https://leetcode.com/problems/complement-of-base-10-integer/description/

Problem statement:
The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer n, return its complement.



Example 1:
Input: n = 5
Output: 2
Explanation: 5 is "101" in binary, with complement "010" in binary, which is 2 in base-10.

Example 2:
Input: n = 7
Output: 0
Explanation: 7 is "111" in binary, with complement "000" in binary, which is 0 in base-10.

Example 3:
Input: n = 10
Output: 5
Explanation: 10 is "1010" in binary, with complement "0101" in binary, which is 5 in base-10.


Constraints:
1 <= n < 2^31

-----------------------------------------------------------------------

*/

//-------------------------------
// Complement of Base 10 Integer
// ------------------------------

class Solution
{
public:
    /**
     * Approach 1: String Manipulation & Built-in CPU Instructions
     * * Concept:
     * Convert the integer into a 32-character binary string, locate where the
     * actual value starts (skipping the unused leading zeros), manually flip
     * the characters, and parse it back to a base-10 integer.
     * * Complexity:
     * - Time: O(1). The loop always runs at most 32 times, but string allocation
     * and parsing add heavy constant-time overhead.
     * - Space: O(1). A 32-character string takes a small, constant amount of memory.
     */
    int findComplement1(int n)
    {

        // Convert the integer into a complete 32-bit string (e.g., 5 becomes "000...000101")
        string bitstream = bitset<32>(n).to_string();

        // Calculate the number of leading zeros to find where the "useful" bits start.
        // __builtin_clz maps to a lightning-fast hardware instruction.
        // Edge case: __builtin_clz(0) is undefined on some architectures, so we explicitly
        // set it to 31 for n=0, ensuring we only flip the very last bit.
        int leadingZs = n == 0 ? 31 : __builtin_clz(n);

        // Iterate through the string starting exactly where the actual binary value begins
        for (int i = leadingZs; i < 32; ++i)
        {
            // Flip the characters: '1' becomes '0', and '0' becomes '1'
            bitstream[i] = bitstream[i] == '1' ? '0' : '1';
        }

        // Parse the modified base-2 string back into a standard base-10 integer
        int res = stoi(bitstream, nullptr, 2);

        return res;
    }

    /**
     * Approach 2: Pure Bitwise Math (Optimal)
     * * Concept:
     * We can flip all the bits of a number by XORing it with a "mask" of all 1s.
     * The goal is to generate a mask of 1s that is the exact same length as `n`.
     * For example, if n = 5 (101), we want a mask of 7 (111). 101 ^ 111 = 010 (2).
     * * Complexity:
     * - Time: O(1). Executes purely via math and bitwise operations with zero loops.
     * - Space: O(1). Uses only a few integer variables.
     */
    int findComplement(int n)
    {

        // Find how many bits are required to represent `n`.
        // log2(n) gives the highest power of 2, so log2(n) + 1 gives the exact bit length.
        // Edge case: log2(0) is mathematically undefined, so we manually assign 1 useful bit.
        int usefulBits = n == 0 ? 1 : log2(n) + 1;

        // Generate the XOR mask.
        // 1. We shift '1' to the left by `usefulBits` (e.g., 1 << 3 becomes 1000 binary, or 8).
        // 2. We subtract 1 to turn it into a sequence of 1s (e.g., 8 - 1 = 7, which is 111 binary).
        // Note: Casting 1 to (long long) is a great defensive practice to prevent
        // undefined behavior or overflow if usefulBits ever pushed past 31.
        int mask = (((long long)1) << usefulBits) - 1;

        // XOR the original number with our all-1s mask to flip the bits
        int res = n ^ mask;

        return res;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
