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

1. Title: Contiguous Array [Binary variant]

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

2. Title: Longest Balanced Substring I

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
// 1. Title: Contiguous Array [Binary variant]
//-------------------------------------------------------------------------------
class Solution
{
public:
    /*
     * Method: findMaxLength
     * ---------------------
     * Approach: Prefix Sum + Hash Map (The "Elevation" Method)
     * * Core Idea:
     * 1. Transform the data: Treat 0 as -1 and 1 as +1.
     * 2. Calculate Running Sum (Prefix Sum).
     * 3. If the Running Sum at index 'i' is the same as the Running Sum at index 'j' (where j < i),
     * it means the net change between j and i is 0.
     * Therefore, the subarray nums[j+1...i] has an equal number of 0s and 1s.
     *
     * Time Complexity: O(N)
     * - We traverse the array once. Map operations are O(1) on average.
     * * Space Complexity: O(N)
     * - In the worst case (e.g., all 1s), the map stores N distinct sums.
     */
    int findMaxLength(vector<int> &nums)
    {

        int N = nums.size();

        // Hash Map to store the FIRST occurrence of a specific cumulative sum.
        // Key: Cumulative Sum
        // Value: Index where this sum was FIRST seen
        unordered_map<int, int> firstSeen;

        // Note: This vector is technically redundant for the logic.
        // We only use 'curSum' in the calculation, but storing it here
        // helps visualize the prefix sum history.
        vector<int> prefSum(N + 1, 0);

        // Base Case Initialization:
        // A sum of 0 is conceptually seen at index -1 (before the array starts).
        // This handles the edge case where the balanced subarray starts at index 0.
        // Example: nums=[0, 1]. At i=1, sum is 0. Length = 1 - (-1) = 2.
        firstSeen[0] = -1;

        int maxLen = 0;
        int curSum = 0; // The running balance

        for (int i = 0; i < N; i++)
        {

            // Step 1: Update Running Sum
            // If 1 -> Add 1
            // If 0 -> Subtract 1
            curSum += (nums[i] == 1 ? 1 : -1);

            // Store in vector (Optional step for logic, good for debugging)
            prefSum[i] = curSum;

            // Step 2: Check History
            // Have we seen this 'curSum' before?
            if (firstSeen.find(curSum) != firstSeen.end())
            {

                // FOUND A BALANCED SUBARRAY!
                // If we were at "Altitude X" at index 'prev_idx', and we are back at
                // "Altitude X" at index 'i', then the path between them has net 0 change.

                int prevIdx = firstSeen[curSum];
                int currentLen = i - prevIdx;

                maxLen = max(maxLen, currentLen);

                // CRITICAL: Do NOT update firstSeen[curSum] here.
                // We want the *longest* subarray, so we want to keep the
                // *leftmost* (earliest) index where this sum appeared.
            }
            else
            {
                // First time seeing this specific sum.
                // Record the index.
                firstSeen[curSum] = i;
            }
        }

        return maxLen;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Longest Balanced Substring I
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
// 3. Title: Longest Balanced Substring II
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
 * Time Complexity: O(N)
 * - We iterate through the string a fixed number of times (3 passes for single,
 * 3 passes for pairs, 1 pass for triple). 7 * N = O(N).
 *
 * Space Complexity: O(N)
 * - Hash Maps store at most N states.
 */

class Solution
{
private:
    /*
     * Method: solveSingleChar
     * -----------------------
     * Handles the case where the balanced substring contains only 1 distinct character.
     * Logic: Simply finds the longest consecutive sequence of 'target' character.
     * Example: "aaabbba" -> target 'a' gives 3.
     */
    int solveSingleChar(const string &s, char target)
    {
        int maxLen = 0;
        int currentRun = 0;

        for (char c : s)
        {
            if (c == target)
            {
                currentRun++;
                maxLen = max(maxLen, currentRun);
            }
            else
            {
                currentRun = 0;
            }
        }
        return maxLen;
    }

    /*
     * Method: solveTwoChars
     * ---------------------
     * Handles the case where the balanced substring contains exactly 2 distinct characters (u, v).
     * The third character ('wall') MUST NOT appear in the substring.
     *
     * Logic:
     * 1. Iterate through string.
     * 2. If we see 'wall', the current substring breaks. Reset the map and counter.
     * 3. Else, update balance 'diff = count(u) - count(v)'.
     * 4. Use HashMap to find the longest subarray with the same 'diff' value.
     */
    int solveTwoChars(const string &s, char u, char v)
    {
        int maxLen = 0;
        int n = s.length();

        // Find the 3rd character which acts as the delimiter/wall
        char wall = ' ';
        if (u != 'a' && v != 'a')
            wall = 'a';
        else if (u != 'b' && v != 'b')
            wall = 'b';
        else
            wall = 'c';

        // Map stores <Difference, First Index seen>
        // Difference = count(u) - count(v)
        unordered_map<int, int> diffMap;

        // Base case: Difference 0 is seen at index -1
        // (conceptually before the string starts)
        diffMap[0] = -1;

        int diff = 0;

        for (int i = 0; i < n; i++)
        {
            if (s[i] == wall)
            {
                // RESET: We hit a wall. Valid substring cannot cross this.
                // Clear history, reset diff to 0.
                // Treat current index 'i' as the new "virtual start" (-1 equivalent)
                diffMap.clear();
                diffMap[0] = i;
                diff = 0;
            }
            else
            {
                // Update difference based on character
                if (s[i] == u)
                    diff++;
                else if (s[i] == v)
                    diff--;

                // Check if this difference state has been seen before
                if (diffMap.count(diff))
                {
                    // Current length is (Current Index - First Index of this diff)
                    maxLen = max(maxLen, i - diffMap[diff]);
                }
                else
                {
                    // First time seeing this difference in current segment
                    diffMap[diff] = i;
                }
            }
        }
        return maxLen;
    }

    /*
     * Method: solveThreeChars
     * -----------------------
     * Handles the case where substring contains all 3 distinct characters (a, b, c) equally.
     * Condition: count(a) == count(b) AND count(b) == count(c).
     *
     * Logic:
     * 1. Track two differences: d1 = a - b, d2 = b - c.
     * 2. Store pair {d1, d2} in a map.
     * 3. If the pair {d1, d2} repeats, the substring between occurrences is balanced.
     */
    int solveThreeChars(const string &s)
    {
        int maxLen = 0;
        int n = s.length();

        // Map stores <{diff1, diff2}, First Index>
        // Use std::map or a custom hash for pair. Here map is O(N log N),
        // but since N=10^5 and map is small, it's acceptable.
        // Can use custom hash for unordered_map to keep O(N).
        map<pair<int, int>, int> stateMap;

        // Base case: State {0, 0} seen at index -1
        stateMap[{0, 0}] = -1;

        int a = 0, b = 0, c = 0;

        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'a')
                a++;
            else if (s[i] == 'b')
                b++;
            else if (s[i] == 'c')
                c++;

            // Calculate relative differences
            int diff1 = a - b;
            int diff2 = b - c;

            if (stateMap.count({diff1, diff2}))
            {
                maxLen = max(maxLen, i - stateMap[{diff1, diff2}]);
            }
            else
            {
                stateMap[{diff1, diff2}] = i;
            }
        }
        return maxLen;
    }

public:
    int longestBalancedSubstring(string s)
    {
        int ans = 0;

        // 1. Check for single character balanced substrings
        ans = max(ans, solveSingleChar(s, 'a'));
        ans = max(ans, solveSingleChar(s, 'b'));
        ans = max(ans, solveSingleChar(s, 'c'));

        // 2. Check for two-character balanced substrings (pairs)
        // Note: These methods handle the logic where the 3rd char is excluded.
        ans = max(ans, solveTwoChars(s, 'a', 'b'));
        ans = max(ans, solveTwoChars(s, 'a', 'c'));
        ans = max(ans, solveTwoChars(s, 'b', 'c'));

        // 3. Check for three-character balanced substrings
        ans = max(ans, solveThreeChars(s));

        return ans;
    }
};

int main()
{
    return 0;
}
