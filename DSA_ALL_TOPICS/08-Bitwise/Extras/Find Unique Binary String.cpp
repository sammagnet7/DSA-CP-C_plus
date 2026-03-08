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
#include<bitset>

using namespace std;

/*

1. Title: Find Unique Binary String

Links:
https://leetcode.com/problems/find-unique-binary-string/description/


Problem statement:
Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.


Example 1:
Input: nums = ["01","10"]
Output: "11"
Explanation: "11" does not appear in nums. "00" would also be correct.

Example 2:
Input: nums = ["00","01"]
Output: "11"
Explanation: "11" does not appear in nums. "10" would also be correct.

Example 3:
Input: nums = ["111","011","001"]
Output: "101"
Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.


Constraints:
n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] is either '0' or '1'.
All the strings of nums are unique.



-----------------------------------------------------------------------

*/

#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    // -----------------------
    // Approach 1: sub-OPTIMAL
    // -----------------------
    /**
     * Idea: Integer Conversion & The Pigeonhole Principle
     * Instead of dealing with strings directly, we can treat each binary string as a
     * base-2 integer.
     * Since there are exactly 'n' strings, by the Pigeonhole Principle, if we look
     * at the integer range [0, n] (which contains n + 1 numbers), at least one
     * number in this range MUST be missing from our input array.
     * * Step-by-Step Approach & Logic:
     * 1. Tracking Array: We create a boolean array `dp` of size `n + 1` to track
     * which integers from 0 to 'n' are present in the input.
     * 2. String to Integer: Iterate through the given strings, convert each from base-2
     * to a decimal integer using `stoi(..., 2)`.
     * 3. Mark Presence: If the converted integer falls within our target range [0, n],
     * we mark it as `true` in our `dp` array. We can safely ignore numbers > n.
     * 4. Find the Missing Number: Iterate from 0 to n. The first index where `dp[num]`
     * is `false` is our missing number.
     * 5. Integer to String: Convert that missing number back into a binary string using
     * `std::bitset<16>` (since constraints state n <= 16).
     * 6. Format Output: `bitset` generates a full 16-bit string (e.g., "0000000000000011").
     * We calculate the number of leading zeros to trim (`16 - nobs`) and use `substr`
     * to return exactly the `nobs` bits required.
     * * Time Complexity: O(n)
     * We iterate through the 'n' strings once. String-to-integer and bitset conversions
     * take constant time bounded by the maximum string length (16).
     * * Space Complexity: O(n)
     * We use a boolean vector of size `n + 1` to track the occurrences.
     */
    string findDifferentBinaryString(vector<string> &nums)
    {

        int n = nums.size();
        int nobs = nums[0].size(); // Number of bits required for the output

        // dp array to track presence of numbers in the range [0, n]
        vector<bool> dp(n + 1, false);

        for (int i = 0; i < n; ++i)
        {
            // Convert binary string to decimal integer
            int curNum = stoi(nums[i], nullptr, 2);

            // Only track numbers that fall within our [0, n] pigeonhole range
            if (curNum < n + 1)
            {
                dp[curNum] = true;
            }
        }

        // Find the first missing number in the range [0, n]
        for (int num = 0; num < n + 1; ++num)
        {
            if (!dp[num])
            {
                // Convert the missing integer back to a 16-bit binary string
                string val = bitset<16>(num).to_string();

                // Calculate starting index to strip leading zeros based on required length
                int clz = 16 - nobs;

                // Return the exact rightmost 'nobs' bits
                return val.substr(clz, nobs);
            }
        }

        return "";
    }

    // -----------------------
    // Approach 2: OPTIMAL
    // -----------------------
    /**
     * Idea:
     * This solution uses Cantor's Diagonalization Argument.
     * Since we are given 'n' strings, each of length 'n', we can construct a new
     * string of length 'n' that is guaranteed to not be in the array.
     * We do this by ensuring our new string differs from the i-th string at the
     * i-th position.
     * * Approach:
     * 1. Initialize an empty string `ans`.
     * 2. Iterate through the array of strings from index `i = 0` to `n - 1`.
     * 3. At each step, look at `nums[i][i]` (the character on the diagonal).
     * 4. If `nums[i][i]` is '0', append '1' to `ans`. If it is '1', append '0'.
     * 5. Return the constructed string `ans`.
     * * Time Complexity: O(n)
     * We iterate through the given array of 'n' strings exactly once, doing a
     * constant time O(1) character flip and append at each step.
     * * Space Complexity: O(1)
     * We only use extra space for the output string `ans` of length 'n'. Excluding
     * the space required for the output, the auxiliary space is strictly O(1).
     */
    string findDifferentBinaryString(vector<string> &nums)
    {

        int n = nums.size();
        string ans = "";

        for (int i = 0; i < n; ++i)
        {
            // Flip the i-th character of the i-th string
            if (nums[i][i] == '0')
            {
                ans += '1';
            }
            else
            {
                ans += '0';
            }
        }

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
