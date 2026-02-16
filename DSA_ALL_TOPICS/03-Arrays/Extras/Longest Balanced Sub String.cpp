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

1. Title: Longest Balanced Substring I

Links:
https://leetcode.com/problems/longest-balanced-substring-i/description/


Problem statement:
You are given a string s consisting of lowercase English letters.

A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

Return the length of the longest balanced substring of s.


Example 1:
Input: s = "abbac"
Output: 4
Explanation:
The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

Example 2:
Input: s = "zzabccy"
Output: 4
Explanation:
The longest balanced substring is "zabc" because the distinct characters 'z', 'a', 'b', and 'c' each appear exactly 1 time.​​​​​​​

Example 3:
Input: s = "aba"
Output: 2
Explanation:
​​​​​​​One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".



Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.

----------------------------------------------------------------------------------------------------


2. Title: Contiguous Array [Binary variant]

Links:
https://leetcode.com/problems/contiguous-array/description/

Problem statement:
Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.


Example 1:
Input: nums = [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

Example 2:
Input: nums = [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Example 3:
Input: nums = [0,1,1,1,1,1,0,0,0]
Output: 6
Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.


Constraints:
1 <= nums.length <= 105
nums[i] is either 0 or 1.


----------------------------------------------------------------------------------------------------

3. Title: Longest Balanced Substring II

Links:
https://leetcode.com/problems/longest-balanced-substring-ii/description/


Problem statement:
You are given a string s consisting only of the characters 'a', 'b', and 'c'.

A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

Return the length of the longest balanced substring of s.


Example 1:
Input: s = "abbac"
Output: 4
Explanation:
The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

Example 2:
Input: s = "aabcc"
Output: 3
Explanation:
The longest balanced substring is "abc" because all distinct characters 'a', 'b' and 'c' each appear exactly 1 time.

Example 3:
Input: s = "aba"
Output: 2
Explanation:
One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".



Constraints:
1 <= s.length <= 105
s contains only the characters 'a', 'b', and 'c'.

*/

//-------------------------------------------------------------------------------
// 1. Title: Longest Balanced Substring I [26 chars] O(N^2) [OPTIMAL]
//-------------------------------------------------------------------------------

class Solution
{
public:
    /*
     * METHOD: longestBalanced
     * --------------------------------
     * APPROACH: Optimized Brute Force (O(N^2))
     * We iterate through all possible start positions 'i'.
     * For each start, we expand the end position 'j' to the right.
     * * OPTIMIZATION:
     * Instead of rescanning the frequency array to check for equality,
     * we track:
     * 1. distinctCount: How many unique chars are in s[i...j].
     * 2. maxFreq: The highest frequency among those chars.
     * * Condition:
     * If all present characters have the same frequency, they must all equal 'maxFreq'.
     * Therefore, the total length (j - i + 1) MUST equal (maxFreq * distinctCount).
     * * COMPLEXITY:
     * - Time: O(N^2). Two nested loops, internal updates are O(1).
     * - Space: O(1). Frequency array is fixed size 26.
     */
    int longestBalanced(string s)
    {
        int n = s.length();
        int maxLen = 0;

        // Outer loop: Start of the substring
        for (int i = 0; i < n; ++i)
        {

            // State for the current window s[i...j]
            vector<int> freq(26, 0);
            int maxFreq = 0;
            int distinctCount = 0;

            // Inner loop: End of the substring
            for (int j = i; j < n; ++j)
            {
                int charIdx = s[j] - 'a';

                // If this is the first time we see this char in this window
                if (freq[charIdx] == 0)
                {
                    distinctCount++;
                }

                freq[charIdx]++;
                maxFreq = max(maxFreq, freq[charIdx]);

                // Current substring length
                int currentLen = j - i + 1;

                // Check if balanced using the math trick
                if (maxFreq * distinctCount == currentLen)
                {
                    maxLen = max(maxLen, currentLen);
                }
            }
        }

        return maxLen;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Contiguous Array [Binary variant: 0-1] O(N) [OPTIMAL]
//-------------------------------------------------------------------------------
/*
 * Problem: 525. Contiguous Array
 * ------------------------------
 * Goal: Find the maximum length of a contiguous subarray with an equal number of 0s and 1s.
 *
 * Approach: Prefix Difference + Hash Map
 * --------------------------------------
 * Core Logic:
 * 1. Transformation:
 * - Treat 1 as +1
 * - Treat 0 as -1
 * This transforms the problem into finding the longest subarray with a SUM of 0.
 *
 * 2. The "Difference" Concept:
 * - We maintain a running variable 'diff'.
 * - diff = (Total 1s so far) - (Total 0s so far).
 * - If 'diff' at index 'i' is exactly the same as 'diff' at index 'j' (where j < i),
 * it implies that between index j and i, the number of 1s added equaled the number
 * of 0s added (net change is 0).
 *
 * 3. Hash Map Strategy:
 * - We store the FIRST index where a specific 'diff' value is seen.
 * - Why first? Because we want the longest subarray. To maximize (i - j),
 * we need 'j' to be as small (leftmost) as possible.
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N)
 * - We iterate through the array once.
 * - Hash Map insertions and lookups take O(1) on average.
 *
 * Space Complexity: O(N)
 * - In the worst case (e.g., 0,0,0,0...), the 'diff' keeps changing, so we store
 * N unique entries in the map.
 */

class Solution
{
public:
    int findMaxLength(vector<int> &nums)
    {

        int N = nums.size();

        // Map stores <Difference Value, First Index Seen>
        unordered_map<int, int> firstSeenDiffMap;

        // Base Case Initialization:
        // A difference of 0 is conceptually present at index -1 (before the array starts).
        // This handles cases where the balanced subarray starts from index 0.
        // Example: nums=[0, 1]. At i=0 (val 0), diff=-1. At i=1 (val 1), diff=0.
        // Length = 1 - (-1) = 2.
        firstSeenDiffMap[0] = -1;

        int maxLen = 0;
        int diff = 0; // Represents Count(1) - Count(0)

        for (int i = 0; i < N; i++)
        {

            // Step 1: Update Running Difference
            // If 1 -> Add 1 to balance
            // If 0 -> Subtract 1 from balance
            diff += (nums[i] == 1 ? 1 : -1);

            // Step 2: Check History
            // Have we seen this specific 'diff' state before?
            if (firstSeenDiffMap.find(diff) != firstSeenDiffMap.end())
            {

                // Found a valid subarray!
                // The subarray between 'prevSeenDiffIdx' and 'i' has equal 0s and 1s.
                // Because the net change in 'diff' between these two points is 0.

                int prevSeenDiffIdx = firstSeenDiffMap[diff];

                // Calculate length
                int currentLen = i - prevSeenDiffIdx;

                maxLen = max(maxLen, currentLen);

                // Note: We DO NOT update the map entry here.
                // We want to keep the 'prevSeenDiffIdx' as far left as possible
                // to maximize future lengths.
            }
            else
            {
                // First time encountering this specific 'diff'.
                // Store the index so we can calculate lengths relative to this point later.
                firstSeenDiffMap[diff] = i;
            }
        }

        return maxLen;
    }
};

//-------------------------------------------------------------------------------
// 3. Title: Longest Balanced Substring II [3 chars: a/b/c] O(N) [OPTIMAL]
//-------------------------------------------------------------------------------
/*
 * Problem: Longest Balanced Substring II
 * --------------------------------------
 * Goal: Find the length of the longest substring where ALL distinct characters
 * present in the substring appear the SAME number of times.
 *
 * The string contains only 'a', 'b', and 'c'.
 *
 * Approach: Divide and Conquer by "Distinct Character Count"
 * ----------------------------------------------------------
 * Since there are only 3 possible characters, a valid balanced substring can
 * only have 1, 2, or 3 distinct characters. We solve for each case separately.
 *
 * 1. Case 1 (1 Distinct Char): 'a' only, 'b' only, 'c' only.
 * -> Solved by finding the longest consecutive run of a single char.
 *
 * 2. Case 2 (2 Distinct Chars): pairs (a,b), (b,c), (a,c).
 * -> Solved using Prefix Sum Difference map.
 * -> The 3rd character acts as a "Wall" or "Reset". The substring cannot contain it.
 * -> We track diff = count(char1) - count(char2).
 *
 * 3. Case 3 (3 Distinct Chars): (a,b,c).
 * -> Solved using Multi-variable Prefix Sum Difference map.
 * -> We track state = {count(a)-count(b), count(b)-count(c)}.
 *
 * Complexity Analysis:
 * --------------------
 * Time Complexity: O(N log N)
 * - Step 1 & 2 are O(N).
 * - Step 3 uses std::map which adds a log factor. Total O(N log N).
 * (Can be optimized to O(N) using a custom hash for pair in unordered_map).
 *
 * Space Complexity: O(N)
 * - Hash Maps store at most N states.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int longestBalanced(string s)
    {

        int N = s.length();
        int maxLen = 0;

        // ====================================================
        // Step 1: Substrings with exactly 1 distinct character
        // ====================================================
        // Logic: A substring with only 1 distinct char is always balanced.
        // We just need the longest run of "aaaa...", "bbbb...", or "cccc..."
        // Time: O(3 * N) -> O(N)
        for (char c : {'a', 'b', 'c'})
        {
            int len = 0;
            for (int i = 0; i < N; i++)
            {
                if (s[i] != c)
                {
                    len = 0; // Break the run if char doesn't match
                }
                else
                {
                    len++;
                    maxLen = max(maxLen, len);
                }
            }
        }

        // ====================================================
        // Step 2: Substrings with exactly 2 distinct characters
        // ====================================================
        // Logic: We iterate over every pair combination: (a,b), (b,c), (c,a).
        // For a pair (x, y), the 3rd character acts as a "Wall".
        // If we hit the wall, the current balanced substring breaks, and we must reset.
        // Time: O(3 * N) -> O(N)
        for (auto [x, y] : {pair{'a', 'b'}, pair{'b', 'c'}, pair{'c', 'a'}})
        {

            unordered_map<int, int> firstSeenDiff;
            int diff;
            int i = 0;

            // Use a while loop to handle segment resets efficiently
            while (i < N)
            {

                // RESET LOGIC:
                // We are starting a new segment (either at 0 or after a 'wall').
                firstSeenDiff.clear();

                // Base Case: A difference of 0 is conceptually at index (start - 1).
                // If segment starts at 'i', previous index is 'i-1'.
                firstSeenDiff[0] = i - 1;
                diff = 0;

                // Inner loop traverses the valid segment containing only x and y
                for (; i < N; ++i)
                {

                    // Check for "Wall" (The 3rd distinct character)
                    if (s[i] != x && s[i] != y)
                    {
                        ++i;   // Move past the wall
                        break; // Break inner loop to trigger reset in outer while loop
                    }

                    // Calculate Running Difference (Prefix Sum trick)
                    // If x: +1, If y: -1.
                    // If diff becomes same as before, sum is 0 (balanced).
                    diff += (s[i] == x) ? 1 : -1;

                    if (firstSeenDiff.find(diff) != firstSeenDiff.end())
                    {
                        // Found a balanced portion within this segment
                        maxLen = max(maxLen, (i - firstSeenDiff[diff]));
                    }
                    else
                    {
                        // Store first occurrence of this difference
                        firstSeenDiff[diff] = i;
                    }
                }
            }
        }

        // ====================================================
        // Step 3: Substrings with exactly 3 distinct characters
        // ====================================================
        // Logic: We need count(a) == count(b) == count(c).
        // This mathematically implies:
        // 1. (count(a) - count(b)) == 0
        // 2. (count(b) - count(c)) == 0
        // We track this "State" pair {a-b, b-c}.
        // Time: O(N log N) due to std::map

        int countA = 0;
        int countB = 0;
        int countC = 0;

        // Map key: {diff1, diff2}, Value: First Index
        map<pair<int, int>, int> firstSeenState;

        // Base Case: State {0,0} is present at index -1 (before string starts).
        // This is crucial for substrings starting at index 0.
        firstSeenState[{0, 0}] = -1;

        for (int i = 0; i < N; ++i)
        {

            if (s[i] == 'a')
                countA++;
            else if (s[i] == 'b')
                countB++;
            else if (s[i] == 'c')
                countC++;

            int diff1 = countA - countB;
            int diff2 = countB - countC;

            // Check if this specific balance state {d1, d2} has been seen before.
            // If yes, the substring between the first occurrence and now
            // has maintained the relative balance of a, b, and c.
            if (firstSeenState.find({diff1, diff2}) != firstSeenState.end())
            {
                maxLen = max(maxLen, i - firstSeenState[{diff1, diff2}]);
            }
            else
            {
                firstSeenState[{diff1, diff2}] = i;
            }
        }

        return maxLen;
    }
};

int main()
{
    return 0;
}
