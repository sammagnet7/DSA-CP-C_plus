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

1. Title: Minimum Distance to Type a Word Using Two Fingers


Links:
https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/description/


Problem statement:

A	B	C	D	E	F
G	H	I	J	K	L
M	N	O	P	Q	R
S	T	U	V	W	X
Y	Z

You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.

For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
Given the string word, return the minimum total distance to type such string using only two fingers.

The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.

Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.



Example 1:
  Input: word = "CAKE"
  Output: 3
  Explanation: Using two fingers, one optimal way to type "CAKE" is:
  Finger 1 on letter 'C' -> cost = 0
  Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2
  Finger 2 on letter 'K' -> cost = 0
  Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1
  Total distance = 3

Example 2:
  Input: word = "HAPPY"
  Output: 6
  Explanation: Using two fingers, one optimal way to type "HAPPY" is:
  Finger 1 on letter 'H' -> cost = 0
  Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
  Finger 2 on letter 'P' -> cost = 0
  Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
  Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
  Total distance = 6


Constraints:
  2 <= word.length <= 300
  word consists of uppercase English letters.



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
// 1. Title: Minimum Distance to Type a Word Using Two Fingers
//-------------------------------------------------------------------------------

//============================================================
// Approach 1: DP on left hand right hand indexes [Slow] [MLE]
//============================================================
class Solution
{
private:
  int getKeyDist(int key1_idx, int key2_idx, string &word)
  {

    if (key1_idx == -1 || key2_idx == -1)
    {
      return 0;
    }

    int key_1 = word[key1_idx] - 'A';
    int key_2 = word[key2_idx] - 'A';

    int key1_x = key_1 / 6;
    int key1_y = key_1 % 6;
    int key2_x = key_2 / 6;
    int key2_y = key_2 % 6;

    return abs(key1_x - key2_x) + abs(key1_y - key2_y);
  }

  /**
   * ============================================================================
   * CAUSE OF MEMORY LIMIT EXCEEDED (MLE): O(N^3) State Definition
   * ============================================================================
   * The Bug:
   * You defined the positions of Finger 1 and Finger 2 by the `index` of the
   * string they last typed. Because the string length (N) can be up to 300,
   * your DP table dimensions are [301] x [301] x [300].
   * * The Math:
   * 301 * 301 * 300 = 27,180,300 elements.
   * At 4 bytes per integer, that is ~108 Megabytes of raw data.
   * Furthermore, `vector<vector<vector<int>>>` creates over 90,000 separate
   * heap allocations for the inner arrays. The metadata, pointers, and memory
   * fragmentation overhead of nested vectors pushes this well past LeetCode's
   * memory limits (and makes allocation incredibly slow, often risking TLE).
   * ============================================================================
   */
  int minDist(int fing1Pos, int fing2Pos, int pos, string &word, vector<vector<vector<int>>> &dp)
  {

    if (pos == word.size())
    {
      return 0;
    }

    if (dp[fing1Pos + 1][fing2Pos + 1][pos] != -1)
    {
      return dp[fing1Pos + 1][fing2Pos + 1][pos];
    }

    int moveFing1 = getKeyDist(fing1Pos, pos, word) + minDist(pos, fing2Pos, pos + 1, word, dp);

    int moveFing2 = getKeyDist(fing2Pos, pos, word) + minDist(fing1Pos, pos, pos + 1, word, dp);

    return dp[fing1Pos + 1][fing2Pos + 1][pos] = min(moveFing1, moveFing2);
  }

public:
  int minimumDistance(string word)
  {

    int n = word.size();

    // Allocating a massive N^3 DP table using nested vectors causes massive
    // heap fragmentation and memory overhead.
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n, -1)));

    return minDist(-1, -1, 0, word, dp);
  }
};

//============================================================
// Approach 2: DP on left hand right hand characters [Fast]
//============================================================
/**
 * ============================================================================
 * Approach: Top-Down DP with State Compression & Raw Arrays
 * ============================================================================
 * OPTIMIZATION 1: State Definition Compression (Fixes Memory Limit Exceeded)
 * Earlier Approach:
 * We tracked the fingers by the `index` of the string they last typed.
 * This resulted in a massive O(N^3) DP table (300 x 300 x 300 ≈ 27M elements).
 * Current Approach:
 * We track the fingers by their physical `character` value (0 to 25, plus an
 * "unplaced" state). The keyboard only cares *where* the finger is, not *when* it got there. This violently reduces the state to O(27 * 27 * N), dropping
 * memory usage by over 99% (down to ~218K elements).
 * * OPTIMIZATION 2: Heap Allocation Removal (Fixes Speed Bottlenecks)
 * Earlier Approach:
 * Using `vector<vector<vector<int>>>` forced the compiler to make thousands
 * of scattered, dynamic memory allocations on the heap, causing memory
 * fragmentation and cache misses.
 * Current Approach:
 * Using a raw C-array (`int dp[27][27][300]`) allocates a single, contiguous
 * block of memory. Combined with `memset`, this initializes almost instantly
 * and fits perfectly into the CPU cache for maximum read/write speeds.
 * ============================================================================
 * Complexity:
 * - Time: O(N * 27^2). The DP table tracks exactly 27 possible states for
 * Finger 1, 27 states for Finger 2, and N states for the string index.
 * Since evaluating each state takes O(1) time, the absolute maximum number of
 * operations is 729 * N. For N = 300, this is ~218,000 operations, running in 0ms.
 * - Space: O(N * 27^2). The raw 3D array allocates exactly 27 * 27 * 300
 * integers, which consumes less than 1 Megabyte of memory total. The recursive
 * call stack adds an additional O(N) space constraint.
 * ============================================================================
 */
class Solution
{
private:
  // Fixed-size raw array.
  // +1 for the 26 letters to handle the "-1" (unplaced) state safely.
  int dp[26 + 1][26 + 1][300];

  int getKeyDist(int key_1, int key_2)
  {

    // If the finger hasn't been placed on the keyboard yet, moving it is free
    if (key_1 == -1 || key_2 == -1)
    {
      return 0;
    }

    // Convert 1D character index (0-25) into 2D keyboard coordinates (x, y)
    int key1_x = key_1 / 6;
    int key1_y = key_1 % 6;
    int key2_x = key_2 / 6;
    int key2_y = key_2 % 6;

    // Return the Manhattan distance
    return abs(key1_x - key2_x) + abs(key1_y - key2_y);
  }

  // Notice we no longer pass the heavy DP reference around. It is a class member.
  int minDist(int fing1Char, int fing2Char, int pos, string &word)
  {

    // Base Case: We have successfully typed every character in the word
    if (pos == word.size())
    {
      return 0;
    }

    // Return memoized result if this specific universe has already been calculated.
    // We add +1 to the finger states to safely map the -1 state to index 0.
    if (dp[fing1Char + 1][fing2Char + 1][pos] != -1)
    {
      return dp[fing1Char + 1][fing2Char + 1][pos];
    }

    // Option 1: Move Finger 1 to the current target letter.
    // Cost = (Distance for Finger 1) + (Min cost to finish the rest of the string)
    int moveFing1 = getKeyDist(fing1Char, word[pos] - 'A') +
                    minDist(word[pos] - 'A', fing2Char, pos + 1, word);

    // Option 2: Move Finger 2 to the current target letter.
    // Cost = (Distance for Finger 2) + (Min cost to finish the rest of the string)
    int moveFing2 = getKeyDist(fing2Char, word[pos] - 'A') +
                    minDist(fing1Char, word[pos] - 'A', pos + 1, word);

    // Cache the absolute best choice and return it
    return dp[fing1Char + 1][fing2Char + 1][pos] = min(moveFing1, moveFing2);
  }

public:
  int minimumDistance(string word)
  {

    int n = word.size();

    // DEPRECATED: vector<vector<vector<int>>> dp(26+1, vector<vector<int>>(26+1, vector<int>(n, -1)));

    // Instantly wipe the raw memory block with -1s
    memset(dp, -1, sizeof(dp));

    // Both fingers start entirely unplaced (-1)
    return minDist(-1, -1, 0, word);
  }
};

int main()
{
  return 0;
}
