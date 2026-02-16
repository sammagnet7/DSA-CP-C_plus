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

1. Title: 190. Reverse Bits

Links:
https://leetcode.com/problems/reverse-bits/description/


Problem statement:
Reverse bits of a given 32 bits signed integer.


Example 1:
Input: n = 43261596
Output: 964176192
Explanation:
Integer	Binary
43261596	00000010100101000001111010011100
964176192	00111001011110000010100101000000

Example 2:
Input: n = 2147483644
Output: 1073741822
Explanation:
Integer	Binary
2147483644	01111111111111111111111111111100
1073741822	00111111111111111111111111111110


Constraints:
0 <= n <= 231 - 2
n is even.


Follow up: If this function is called many times, how would you optimize it?

-----------------------------------------------------------------------

*/
class Solution
{
private:
    // Constants for the cache size (2^8 = 256 possible 8-bit values)
    static const int COUNT = 256;
    uint8_t cache[COUNT];

    // Helper to pre-compute the reverse of all numbers from 0 to 255
    void initCache()
    {
        for (int num = 0; num < COUNT; ++num)
        {
            int n = num;
            uint8_t res = 0;
            // Standard 8-bit reversal logic
            for (int i = 0; i < 8; i++)
            {
                res = (res << 1) | (n & 1);
                n >>= 1;
            }
            cache[num] = res;
        }
    }

public:
    // Constructor initializes the cache once when the object is created
    Solution()
    {
        initCache();
    }

    /*
     * METHOD: reverseBits
     * -------------------
     * APPROACH: Divide and Conquer with Memoization (Byte-Level Caching)
     * Instead of iterating through all 32 bits individually (which is slow for many calls),
     * we split the 32-bit integer into four 8-bit chunks (bytes).
     *
     * LOGIC:
     * 1. Extraction: We isolate each byte using bitwise shifting and masking (>> and & 0xFF).
     * - Byte 0 (LSB): n & 0xFF
     * - Byte 1: (n >> 8) & 0xFF
     * - Byte 2: (n >> 16) & 0xFF
     * - Byte 3 (MSB): (n >> 24) & 0xFF
     * 2. Reversal: We look up the reversed value of each byte in our pre-computed 'cache'.
     * - This turns an O(8) loop into an O(1) array access.
     * 3. Reassembly: We reconstruct the 32-bit integer by placing the reversed bytes in mirrored positions.
     * - Reversed Byte 0 moves to the MSB position (<< 24).
     * - Reversed Byte 1 moves to the upper-middle position (<< 16).
     * - Reversed Byte 2 moves to the lower-middle position (<< 8).
     * - Reversed Byte 3 moves to the LSB position (no shift).
     *
     * COMPLEXITY:
     * - Time: O(1). Specifically, 4 table lookups + bitwise ops. Much faster than 32 iterations.
     * - Space: O(1). The cache size is fixed at 256 bytes (very small).
     */
    uint32_t reverseBits(uint32_t n)
    {

        // 1. Extract bytes (masking with 0xff ensures we only get the lowest 8 bits)
        uint8_t byte0 = (n) & 0xff;
        uint8_t byte1 = (n >> 8) & 0xff;
        uint8_t byte2 = (n >> 16) & 0xff;
        uint8_t byte3 = (n >> 24) & 0xff;

        // 2. Reassemble in reverse order
        // Note: Explicit cast to (uint32_t) before shifting is crucial.
        // Without it, 'cache[byte0]' is promoted to a signed 'int'.
        // Shifting a signed int into the sign bit (<< 24) can cause undefined behavior or overflow errors.
        uint32_t res =
            ((uint32_t)cache[byte0] << 24) | ((uint32_t)cache[byte1] << 16) | ((uint32_t)cache[byte2] << 8) | ((uint32_t)cache[byte3]);

        return res;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
