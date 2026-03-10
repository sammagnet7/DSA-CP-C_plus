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

1. Title: Find All Possible Stable Binary Arrays I and II

Links:
https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/description/
https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/description/


Problem statement:
You are given 3 positive integers zero, one, and limit.

A binary array arr is called stable if:

The number of occurrences of 0 in arr is exactly zero.
The number of occurrences of 1 in arr is exactly one.
Each subarray of arr with a size greater than limit must contain both 0 and 1.
Return the total number of stable binary arrays.

Since the answer may be very large, return it modulo 109 + 7.


Example 1:
Input: zero = 1, one = 1, limit = 2
Output: 2
Explanation:
The two possible stable binary arrays are [1,0] and [0,1].

Example 2:
Input: zero = 1, one = 2, limit = 1
Output: 1
Explanation:
The only possible stable binary array is [1,0,1].

Example 3:
Input: zero = 3, one = 3, limit = 2
Output: 14
Explanation:
All the possible stable binary arrays are [0,0,1,0,1,1], [0,0,1,1,0,1], [0,1,0,0,1,1], [0,1,0,1,0,1], [0,1,0,1,1,0], [0,1,1,0,0,1], [0,1,1,0,1,0], [1,0,0,1,0,1], [1,0,0,1,1,0], [1,0,1,0,0,1], [1,0,1,0,1,0], [1,0,1,1,0,0], [1,1,0,0,1,0], and [1,1,0,1,0,0].


Constraints: [for I]
1 <= zero, one, limit <= 200

Constraints:[for II]
1 <= zero, one, limit <= 1000



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Find All Possible Stable Binary Arrays
//-------------------------------------------------------------------------------

// -------------------------------------------------
// Approach 1: Top-Down DP (Character-by-Character)
// -------------------------------------------------

/**
 * Approach 1: 4D State Top-Down DP
 * * Idea:
 * We build the array one element at a time. At each step, we decide whether to
 * place a '0' or a '1'. To ensure the array remains stable, we must track the
 * last character placed and how much of our consecutive allowance (limit) remains.
 * * State Definition:
 * dp[zeroleft][oneleft][prev][limitleft]
 * - zeroleft: Number of '0's remaining to be placed.
 * - oneleft: Number of '1's remaining to be placed.
 * - prev: The character we placed in the previous step (0 or 1).
 * - limitleft: The remaining consecutive times we can place the 'prev' character.
 * * Time Complexity: O(zero * one * limit)
 * We have zero * one * 2 * limit possible states. Computing each state takes
 * O(1) constant time.
 * * Space Complexity: O(zero * one * limit)
 * We allocate a 4D vector of size (zero+1) * (one+1) * 2 * (limit+1).
 * There is also O(zero + one) auxiliary space used by the recursion stack.
 */
class Solution
{
private:
  int MOD = 1e9 + 7;
  vector<vector<vector<vector<int>>>> dp;

  int recCount(int zeroleft, int oneleft, int prev, int limitleft, int limit)
  {

    // Base Case 1: All zeros and ones have been successfully placed
    if (zeroleft == 0 && oneleft == 0)
    {
      return 1;
    }
    // Base Case 2: Invalid path (tried to place more elements than available)
    else if (zeroleft < 0 || oneleft < 0)
    {
      return 0;
    }

    // Memoization check (skip if prev is -1, which is our starting dummy state)
    if (prev != -1 && dp[zeroleft][oneleft][prev][limitleft] != -1)
    {
      return dp[zeroleft][oneleft][prev][limitleft];
    }

    int retVal = 0;

    // Condition A: We have exhausted the consecutive limit for the 'prev' character.
    // We are FORCED to switch characters.
    if (limitleft == 0)
    {
      if (prev == 0)
      {
        if (oneleft > 0)
        {
          // Switch to placing '1'. The limit resets to (limit - 1) because we just placed one.
          retVal = recCount(zeroleft, oneleft - 1, 1, limit - 1, limit);
        }
      }
      else if (prev == 1)
      {
        if (zeroleft > 0)
        {
          // Switch to placing '0'.
          retVal = recCount(zeroleft - 1, oneleft, 0, limit - 1, limit);
        }
      }
    }
    // Condition B: We still have allowance to place identical consecutive characters.
    else
    {
      int place0 = 0;
      int place1 = 0;

      // Option 1: Try placing a '0'
      if (zeroleft > 0)
      {
        // If we previously placed '0', decrement limitleft. If we switched, reset it.
        place0 = recCount(zeroleft - 1, oneleft, 0, prev == 0 ? limitleft - 1 : limit - 1, limit);
      }

      // Option 2: Try placing a '1'
      if (oneleft > 0)
      {
        place1 = recCount(zeroleft, oneleft - 1, 1, prev == 1 ? limitleft - 1 : limit - 1, limit);
      }

      retVal = (place0 + place1) % MOD;
    }

    // Do not cache the dummy starting state
    if (prev == -1)
    {
      return retVal;
    }

    return dp[zeroleft][oneleft][prev][limitleft] = retVal;
  }

public:
  int numberOfStableArrays(int zero, int one, int limit)
  {

    // Initialize the 4D memoization table with -1
    dp = vector<vector<vector<vector<int>>>>(
        zero + 1, vector<vector<vector<int>>>(
                      one + 1, vector<vector<int>>(
                                   2, vector<int>(limit + 1, -1))));

    // Start recursion with -1 indicating no previous character placed
    return recCount(zero, one, -1, limit, limit);
  }
};

// ----------------------------------------------------------
// Approach 2: Top-Down DP (Block-by-Block / Space Optimized)
// ----------------------------------------------------------

/**
 * Approach 2: 3D State Top-Down DP (Space Optimized)
 * * Idea:
 * Instead of adding characters one by one, we add blocks of identical characters.
 * If we just finished placing a block of '0's, our next move MUST be placing a
 * block of '1's. The size of this block can be anywhere from 1 to `limit`.
 * Because we always alternate blocks, we never need to explicitly track `limitleft`.
 * * State Definition:
 * dp[zeroleft][oneleft][prev]
 * - zeroleft: Number of '0's remaining to be placed.
 * - oneleft: Number of '1's remaining to be placed.
 * - prev: The character of the block we just finished placing (0 or 1).
 * * Time Complexity: O(zero * one * limit)
 * We have zero * one * 2 possible states. Inside each state, we run a loop of
 * size up to `limit` to calculate the transitions.
 * * Space Complexity: O(zero * one)
 * We allocate a 3D vector of size (zero+1) * (one+1) * 2. This is a massive
 * memory reduction compared to the 4D approach. The recursion stack takes
 * O(zero + one) auxiliary space.
 */
class Solution
{
private:
  int MOD = 1e9 + 7;
  vector<vector<vector<int>>> dp;

  int recCount(int zeroleft, int oneleft, int prev, int limit)
  {

    // Base Case: All elements successfully placed
    if (zeroleft == 0 && oneleft == 0)
    {
      return 1;
    }
    // Base Case: Invalid path
    else if (zeroleft < 0 || oneleft < 0)
    {
      return 0;
    }

    // Memoization check
    if (prev != -1 && dp[zeroleft][oneleft][prev] != -1)
    {
      return dp[zeroleft][oneleft][prev];
    }

    int accVal = 0;

    // If we are at the beginning OR we just placed a block of '1's,
    // we must now place a block of '0's.
    if (prev == -1 || prev == 1)
    {
      // Try placing a block of size `i` (from 1 up to the allowed limit)
      for (int bs = 1; bs <= min(zeroleft, limit); ++bs)
      {
        // After placing 'i' zeros, the previous block becomes '0'
        accVal = (accVal + recCount(zeroleft - bs, oneleft, 0, limit)) % MOD;
      }
    }

    // If we are at the beginning OR we just placed a block of '0's,
    // we must now place a block of '1's.
    if (prev == -1 || prev == 0)
    {
      // Try placing a block of size `i` (from 1 up to the allowed limit)
      for (int bs = 1; bs <= min(oneleft, limit); ++bs)
      {
        // After placing 'i' ones, the previous block becomes '1'
        accVal = (accVal + recCount(zeroleft, oneleft - bs, 1, limit)) % MOD;
      }
    }

    // Do not cache the dummy starting state
    if (prev == -1)
    {
      return accVal;
    }

    return dp[zeroleft][oneleft][prev] = accVal;
  }

public:
  int numberOfStableArrays(int zero, int one, int limit)
  {

    // Initialize the 3D memoization table with -1
    dp = vector<vector<vector<int>>>(
        zero + 1, vector<vector<int>>(
                      one + 1, vector<int>(
                                   2, -1)));

    return recCount(zero, one, -1, limit);
  }
};

// ----------------------------------------------------------------------------
// Approach 3: Bottom-Up DP (Block-by-Block / Space Optimized)  [RECOMMENDED 1]
// ----------------------------------------------------------------------------
/**
 * Idea: Bottom-Up Dynamic Programming (Block-Building Approach)
 * * * Concept:
 * Instead of generating the array character-by-character, we build it by appending
 * "blocks" of identical characters. We alternate between adding a block of '0's and
 * a block of '1's. By enforcing that the size of any block is between 1 and `limit`,
 * we guarantee the resulting array is always "stable".
 * * * DP State Definition:
 * dp[zerosUsed][onesUsed][endsWith]
 * - `zerosUsed`: The exact number of '0's used to build the current prefix.
 * - `onesUsed`: The exact number of '1's used to build the current prefix.
 * - `endsWith`: A boolean-like integer (0 or 1) representing the character
 * that the current prefix ends with.
 * - 0: The prefix ends with a block of '0's.
 * - 1: The prefix ends with a block of '1's.
 * * * Contrast: Bottom-Up (Prefixes) vs. Top-Down (Suffixes)
 * This is a classic "State-Machine" DP, which causes a shift in perspective:
 * - Top-Down (Recursive): You start with the full amount of zeros/ones and ask,
 * "How do I finish the REST of this array?" The state tracks what is LEFT to
 * place. The third parameter (`prev`) acts as a RESTRICTION from the past,
 * dictating what you are allowed to place next.
 * - Bottom-Up (Iterative): You start with empty arrays and ask, "How did I build
 * what I CURRENTLY have?" The state tracks what has ALREADY BEEN PLACED. The
 * third parameter (`endsWith`) acts as a DESCRIPTION of the present, telling
 * the future loops what they are allowed to append to this prefix.
 * * * Time Complexity: O(zero * one * limit)
 * We have two outer loops iterating `zero` and `one` times. Inside, we have
 * two loops iterating up to `limit` times.
 * * * Space Complexity: O(zero * one)
 * We allocate a 3D vector of size (`zero`+1) x (`one`+1) x 2.
 */
class Solution
{
  // A large prime number used to modulo the results to prevent integer
  // overflow and satisfy the problem's requirement for large answers.
  int MOD = 1e9 + 7;

public:
  int numberOfStableArrays(int zero, int one, int limit)
  {

    // Initialize the 3D DP table with 0s.
    // Dimensions are +1 to allow indexing from 0 up to exactly `zero` and `one`.
    vector<vector<vector<int>>> dp(zero + 1, vector<vector<int>>(one + 1, vector<int>(2, 0)));

    // ==========================================
    // BASE CASES: Seeding the initial states
    // ==========================================

    // Base Case 1: Prefixes made ENTIRELY of '0's.
    // We can place anywhere from 1 up to `limit` zeros in a row.
    // The `min(zero, limit)` bound ensures we don't try to place more zeros
    // than we globally possess.
    for (int zerosUsed = 1; zerosUsed <= min(zero, limit); ++zerosUsed)
    {
      dp[zerosUsed][0][0] = 1; // Exactly 1 way to make a pure string of `zerosUsed` zeros.
    }

    // Base Case 2: Prefixes made ENTIRELY of '1's.
    // We can place anywhere from 1 up to `limit` ones in a row.
    for (int onesUsed = 1; onesUsed <= min(one, limit); ++onesUsed)
    {
      dp[0][onesUsed][1] = 1; // Exactly 1 way to make a pure string of `onesUsed` ones.
    }

    // ==========================================
    // DP TRANSITIONS: Building the prefixes
    // ==========================================

    // Outer loops: Iterate through all possible quantities of '0's and '1's used so far.
    // We start at 1 because the 0-cases (pure 0s or pure 1s) are seeded above.
    for (int zerosUsed = 1; zerosUsed <= zero; ++zerosUsed)
    {
      for (int onesUsed = 1; onesUsed <= one; ++onesUsed)
      {

        // Accumulators to hold the sum of valid configurations for the current state.
        int waysEndingInZero = 0;
        int waysEndingInOne = 0;

        // ---------------------------------------------------------
        // TRANSITION A: Calculating arrays that end in '0'
        // ---------------------------------------------------------
        // To end in '0', we must have just appended a block of '0's to a prefix that ended in '1'.
        // 'blockSize' represents the size of the '0' block we are currently appending.
        // It must be at least 1, and at most `limit` OR the total '0's we are using (`zerosUsed`).
        for (int blockSize = 1; blockSize <= min(zerosUsed, limit); ++blockSize)
        {
          // If we just appended `blockSize` zeros, the previous state must have had
          // `zerosUsed - blockSize` zeros, the exact same number of ones (`onesUsed`),
          // and it MUST have ended in '1' (index 1).
          waysEndingInZero = (waysEndingInZero + dp[zerosUsed - blockSize][onesUsed][1]) % MOD;
        }

        // Store the calculated sum into the DP table.
        dp[zerosUsed][onesUsed][0] = waysEndingInZero;

        // ---------------------------------------------------------
        // TRANSITION B: Calculating arrays that end in '1'
        // ---------------------------------------------------------
        // To end in '1', we must have just appended a block of '1's to a prefix that ended in '0'.
        // 'blockSize' represents the size of the '1' block we are currently appending.
        // It must be at least 1, and at most `limit` OR the total '1's we are using (`onesUsed`).
        for (int blockSize = 1; blockSize <= min(onesUsed, limit); ++blockSize)
        {
          // If we just appended `blockSize` ones, the previous state must have had
          // `onesUsed - blockSize` ones, the exact same number of zeros (`zerosUsed`),
          // and it MUST have ended in '0' (index 0).
          waysEndingInOne = (waysEndingInOne + dp[zerosUsed][onesUsed - blockSize][0]) % MOD;
        }

        // Store the calculated sum into the DP table.
        dp[zerosUsed][onesUsed][1] = waysEndingInOne;
      }
    }

    // ==========================================
    // FINAL RESULT
    // ==========================================
    // The total number of valid stable arrays using EXACTLY `zero` 0s and `one` 1s
    // is the sum of those configurations that end in '0' and those that end in '1'.
    return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
  }
};

// ----------------------------------------------------------------------------
// Approach 4: Bottom-Up DP (Time-Space optimized)  [OPTIMAL]  [RECOMMENDED 2]
// ----------------------------------------------------------------------------

/**
 * Idea: Bottom-Up Dynamic Programming with Inclusion-Exclusion
 * * * Concept:
 * To achieve O(1) time complexity per state, we stop building the array using
 * "blocks" of characters. Instead, we build it one character at a time.
 * We naively assume we can append a '0' to ANY valid array from the previous
 * step. Then, we use the Inclusion-Exclusion principle to mathematically subtract
 * the exact number of configurations that became invalid (i.e., those that formed
 * exactly `limit + 1` consecutive characters).
 * * * DP State Definition:
 * dp[zerosUsed][onesUsed][endsWith]
 * - `zerosUsed`: The exact number of '0's used to build the current prefix.
 * - `onesUsed`: The exact number of '1's used to build the current prefix.
 * - `endsWith`: The character (0 or 1) that sits at the very end of the prefix.
 * * * Time Complexity: O(zero * one)
 * We fill a 2D grid. Every cell calculates its value using O(1) math operations,
 * completely eliminating the inner `limit` loop. This allows it to pass the
 * N = 1000 constraints of Version II.
 * * * Space Complexity: O(zero * one)
 * The 3D vector allocates space proportional to (zero * one * 2).
 */
class Solution
{
  int MOD = 1e9 + 7;

public:
  int numberOfStableArrays(int zero, int one, int limit)
  {

    // Initialize the DP table. We use standard 'int' to save memory, as our
    // modulo operations will keep the values well within the 32-bit limit.
    vector<vector<vector<int>>> dp(zero + 1, vector<vector<int>>(one + 1, vector<int>(2, 0)));

    // ==========================================
    // BASE CASES
    // ==========================================

    // Base Case 1: Prefixes made entirely of '0's.
    // Valid only up to the `limit`.
    for (int zerosUsed = 1; zerosUsed <= min(zero, limit); ++zerosUsed)
    {
      dp[zerosUsed][0][0] = 1;
    }

    // Base Case 2: Prefixes made entirely of '1's.
    // Valid only up to the `limit`.
    for (int onesUsed = 1; onesUsed <= min(one, limit); ++onesUsed)
    {
      dp[0][onesUsed][1] = 1;
    }

    // ==========================================
    // DP TRANSITIONS
    // ==========================================

    for (int zerosUsed = 1; zerosUsed <= zero; ++zerosUsed)
    {
      for (int onesUsed = 1; onesUsed <= one; ++onesUsed)
      {

        // ---------------------------------------------------------
        // CALCULATING ARRAYS ENDING IN '0'
        // ---------------------------------------------------------

        // 1. Naive Addition:
        // Assume we can safely append a '0' to ANY valid array that has 1 less zero.
        // It doesn't matter if the previous array ended in '0' or '1'.
        dp[zerosUsed][onesUsed][0] = (dp[zerosUsed - 1][onesUsed][0] + dp[zerosUsed - 1][onesUsed][1]) % MOD;

        // 2. Inclusion-Exclusion (Subtracting Invalid States):
        // If we have used enough zeros that a sequence of `limit + 1` zeros is possible:
        if (zerosUsed - 1 - limit >= 0)
        {

          // The invalid states are those that just formed exactly `limit + 1` zeros.
          // This happens ONLY IF the array was previously formed by a valid prefix
          // ending in '1', followed by exactly `limit + 1` zeros.
          // We look back `limit + 1` steps to find how many such prefixes exist:
          // dp[zerosUsed - 1 - limit][onesUsed][1]

          // Note: We use 1LL * MOD to temporarily cast MOD to a 64-bit integer.
          // This prevents integer overflow when adding MOD to a potentially negative subtraction result.
          dp[zerosUsed][onesUsed][0] = (dp[zerosUsed][onesUsed][0] - dp[zerosUsed - 1 - limit][onesUsed][1] + 1LL * MOD) % MOD;
        }

        // ---------------------------------------------------------
        // CALCULATING ARRAYS ENDING IN '1'
        // ---------------------------------------------------------

        // 1. Naive Addition:
        // Append a '1' to ANY valid array that has 1 less one.
        dp[zerosUsed][onesUsed][1] = (dp[zerosUsed][onesUsed - 1][0] + dp[zerosUsed][onesUsed - 1][1]) % MOD;

        // 2. Inclusion-Exclusion (Subtracting Invalid States):
        // If we have used enough ones that a sequence of `limit + 1` ones is possible:
        if (onesUsed - 1 - limit >= 0)
        {

          // Subtract configurations that formed exactly `limit + 1` ones.
          // We look back `limit + 1` steps to find prefixes ending in '0'.
          dp[zerosUsed][onesUsed][1] = (dp[zerosUsed][onesUsed][1] - dp[zerosUsed][onesUsed - 1 - limit][0] + 1LL * MOD) % MOD;
        }
      }
    }

    // ==========================================
    // FINAL RESULT
    // ==========================================

    // Sum the valid combinations ending in '0' and ending in '1'.
    return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
  }
};

int main()
{
  return 0;
}
