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

1. Title: Rotated Digits

Links:
https://leetcode.com/problems/rotated-digits/description/


Problem statement:
An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

0, 1, and 8 rotate to themselves,
2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
6 and 9 rotate to each other, and
the rest of the numbers do not rotate to any other number and become invalid.
Given an integer n, return the number of good integers in the range [1, n].



Example 1:
  Input: n = 10
  Output: 4
  Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
  Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.

Example 2:
  Input: n = 1
  Output: 0

Example 3:
  Input: n = 2
  Output: 1


Constraints:
  1 <= n <= 10^4



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

/**
 * ============================================================================
 * Approach 1: Digit Extraction Simulation
 * ============================================================================
 * Logic:
 * We iterate through every number from 1 to N. For each number, we extract
 * its digits one by one from right to left using modulo 10 arithmetic.
 * - If we find a "poisoned" digit (3, 4, 7), the whole number is invalid,
 *   so we break early (fail-fast) to save CPU cycles.
 * - If we find a "good" digit (2, 5, 6, 9), we flag it, but keep checking
 *   to ensure no poisoned digits appear later.
 * ============================================================================
 * Complexity:
 * - Time: O(N log_10 N). For each of the N numbers, we do a while loop for
 *   each of its digits. The number of digits in N is log_10(N).
 * - Space: O(1). Only a few primitive integer variables are used.
 * ============================================================================
 */
class Solution1
{
public:
  int rotatedDigits(int n)
  {

    int count = 0;

    for (int x = 1; x <= n; ++x)
    {

      int tmp = x;
      bool isGood = false;

      // Extract digits one by one until the number is reduced to 0
      while (tmp)
      {
        int dig = tmp % 10; // Get the rightmost digit

        // Fail-fast condition: If it contains 3, 4, or 7, it's permanently invalid.
        if (dig == 3 || dig == 4 || dig == 7)
        {
          isGood = false;
          break; // Stop checking further digits to save time
        }

        // If it contains a rotating digit, flag it as good.
        // We do NOT break here, because a 3, 4, or 7 might be further left!
        if (dig == 2 || dig == 5 || dig == 6 || dig == 9)
        {
          isGood = true;
        }

        tmp /= 10; // Remove the rightmost digit to process the next one
      }

      // If the number survived the loop without hitting a 3, 4, or 7,
      // AND it had at least one good rotating digit, we count it.
      if (isGood)
      {
        ++count;
      }
    }

    return count;
  }
};

/**
 * ============================================================================
 * Approach 2: 1D Dynamic Programming (State Machine)
 * ============================================================================
 * Logic:
 * We categorize every number into a strict state hierarchy:
 * - State 0 (Neutral): Valid, but doesn't make the number "good" (0, 1, 8).
 * - State 1 (Good): Valid and rotates to a different number (2, 5, 6, 9).
 * - State 2 (Poisoned): Invalidates the entire number (3, 4, 7).
 *
 * The state of any multi-digit number is simply the maximum state between
 * its prefix (e.g., 12 in 125) and its last digit (e.g., 5 in 125).
 * Because Poisoned(2) > Good(1) > Neutral(0), the max() function perfectly
 * simulates the overriding rules.
 * ============================================================================
 * Complexity:
 * - Time: O(N). We evaluate every number exactly once in O(1) time by
 *   looking up previously computed states. No inner while-loops!
 * - Space: O(N). We allocate a vector of size N+1 to remember the states.
 * ============================================================================
 */

class Solution
{
public:
  int rotatedDigits(int n)
  {

    // dp[i] stores the state (0, 1, or 2) of the number i
    vector<int> dp(n + 1, 0);
    int count = 0;

    for (int i = 0; i <= n; ++i)
    {

      // Base cases: Manually define states for single-digit numbers
      if (i < 10)
      {
        if (i == 0 || i == 1 || i == 8)
        {
          dp[i] = 0; // Neutral
        }
        else if (i == 2 || i == 5 || i == 6 || i == 9)
        {
          dp[i] = 1; // Good
          count++;
        }
        else
        {
          dp[i] = 2; // Poisoned
        }
      }

      // DP Transition: For multi-digit numbers (10 and above)
      else
      {
        // i / 10 drops the last digit, leaving the prefix we already solved
        int prefix_state = dp[i / 10];

        // i % 10 isolates the last digit, which we also already solved
        int last_digit_state = dp[i % 10];

        // Combine the states: Invalid(2) overrides Good(1) overrides Neutral(0)
        dp[i] = max(prefix_state, last_digit_state);

        // If the combined state is exactly 1, the number is Good!
        if (dp[i] == 1)
        {
          count++;
        }
      }
    }

    return count;
  }
};

int main()
{
  return 0;
}
