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
      for (int i = 1; i <= min(zeroleft, limit); ++i)
      {
        // After placing 'i' zeros, the previous block becomes '0'
        accVal = (accVal + recCount(zeroleft - i, oneleft, 0, limit)) % MOD;
      }
    }

    // If we are at the beginning OR we just placed a block of '0's,
    // we must now place a block of '1's.
    if (prev == -1 || prev == 0)
    {
      // Try placing a block of size `i` (from 1 up to the allowed limit)
      for (int i = 1; i <= min(oneleft, limit); ++i)
      {
        // After placing 'i' ones, the previous block becomes '1'
        accVal = (accVal + recCount(zeroleft, oneleft - i, 1, limit)) % MOD;
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

// ----------------------------------------------------------
// Approach 3: 2d DP [OPTIMAL]
// ----------------------------------------------------------



int main()
{
  return 0;
}
