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

1. Title: Concatenation of Consecutive Binary Numbers

Links:
https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/description/


Problem statement:
Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.


Example 1:
Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1.

Example 2:
Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.

Example 3:
Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.


Constraints:
1 <= n <= 105


-----------------------------------------------------------------------

*/

//-------------
// Approach 1:
//-------------

class Solution
{
private:
    int MOD = 1e9 + 7;

public:
    /*
     * METHOD: concatenatedBinary
     * --------------------------
     * APPROACH: Bitwise Shift with Modular Arithmetic
     * We build the concatenated binary number step-by-step. For each number 'cur',
     * we shift our accumulated result to the left by the exact number of bits
     * 'cur' takes up, and then add 'cur' using bitwise OR.
     *
     * THE MATH:
     * 1. Left shifting by L bits is mathematically multiplying by 2^L.
     * 2. Bitwise ORing 'cur' (into empty zero bits) is exactly adding 'cur'.
     * 3. Because modulo distributes perfectly over addition and multiplication:
     * (A * B + C) % MOD == ((A % MOD) * B + C) % MOD
     * We can safely apply the modulo at every single step to prevent
     * 64-bit integer overflow without corrupting the final remainder.
     *
     * COMPLEXITY:
     * - Time: O(N). We do exactly N iterations with O(1) hardware-level math.
     * - Space: O(1). Only a few integer variables are allocated.
     */
    int concatenatedBinary(int n)
    {

        long long res = 0;

        for (int cur = 1; cur <= n; ++cur)
        {

            // O(1) Hardware Intrinsic:
            // __builtin_clz returns the number of leading zeros in a 32-bit int.
            // 32 - leading_zeros gives us the exact bit-length of 'cur'.
            int usefulBits = 32 - __builtin_clz(cur);

            // BITWISE TRANSLATION TO MATH:
            // 1. (res << usefulBits)   -> res_old * (2 ^ usefulBits)
            // 2. | cur                 -> + cur
            // 3. % MOD                 -> Applies distributive modulo to keep 'res' < 64-bit
            res = ((res << usefulBits) | cur) % MOD;
        }

        // The number is already safely modulo'd from the final loop iteration,
        // but returning res % MOD is a safe and standard guarantee.
        return res % MOD;
    }
};

//-------------
// Approach 2:
//-------------

class Solution
{
public:
    /*
     * METHOD: concatenatedBinary
     * --------------------------
     * APPROACH: Bitwise Shift and Modular Arithmetic
     * We simulate the concatenation by shifting the accumulated result to the
     * left by the number of bits the current number 'i' requires, then adding 'i'.
     *
     * PROS:
     * - Extremely fast. We completely avoid string manipulation.
     * - The (i & (i-1)) trick finds the bit length in O(1) time without math libraries.
     *
     * COMPLEXITY:
     * - Time: O(N). We iterate exactly N times, doing basic O(1) arithmetic.
     * - Space: O(1). Only a few scalar variables are used.
     */
    int concatenatedBinary(int n)
    {

        long long ans = 0; // Use long long to prevent overflow before modulo
        long long MOD = 1e9 + 7;
        int length = 0; // Tracks the current bit-length of 'i'

        for (int i = 1; i <= n; ++i)
        {

            // If 'i' is a power of 2, it requires one more bit than the previous numbers.
            // Example: i=4 (100) requires 3 bits, whereas i=3 (11) required 2 bits.
            if ((i & (i - 1)) == 0)
            {
                length++;
            }

            // 1. Shift 'ans' left by 'length' to make room.
            // 2. Bitwise OR with 'i' to insert 'i' into the empty bits.
            // 3. Modulo to keep the number strictly within bounds.
            ans = ((ans << length) | i) % MOD;
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
