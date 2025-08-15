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

1. Title: Chocolate Pickup

Links:
https://takeuforward.org/data-structure/3-d-dp-ninja-and-his-friends-dp-13/
https://www.youtube.com/watch?v=QGfn7JeXK54
https://www.naukri.com/code360/problems/ninja-and-his-friends_3125885?leftPanelTabValue=PROBLEM


Problem statement:
Ninja has a 'GRID' of size 'R' X 'C'. Each cell of the grid contains some chocolates. Ninja has two friends Alice and Bob, and he wants to collect as many chocolates as possible with the help of his friends.
Initially, Alice is in the top-left position i.e. (0, 0), and Bob is in the top-right place i.e. (0, ‘C’ - 1) in the grid. Each of them can move from their current cell to the cells just below them. When anyone passes from any cell, he will pick all chocolates in it, and then the number of chocolates in that cell will become zero. If both stay in the same cell, only one of them will pick the chocolates in it.
If Alice or Bob is at (i, j) then they can move to (i + 1, j), (i + 1, j - 1) or (i + 1, j + 1). They will always stay inside the ‘GRID’.
Your task is to find the maximum number of chocolates Ninja can collect with the help of his friends by following the above rules.

Example:
Input: ‘R’ = 3, ‘C’ = 4
       ‘GRID’ = [[2, 3, 1, 2], [3, 4, 2, 2], [5, 6, 3, 5]]
Output: 21

Initially Alice is at the position (0,0) he can follow the path (0,0) -> (1,1) -> (2,1) and will collect 2 + 4 + 6 = 12 chocolates.
Initially Bob is at the position (0, 3) and he can follow the path (0, 3) -> (1,3) -> (2, 3) and will colllect 2 + 2 + 5 = 9 chocolates.
Hence the total number of chocolates collected will be 12 + 9 = 21. there is no other possible way to collect a greater number of chocolates than 21.



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Chocolate Pickup
  //-------------------------------------------------------------------------------

  /**
   * Function to calculate the maximum chocolates that two players (Alice and Bob)
   * can collect while traversing a grid from the top row to the bottom.
   *
   * Rules:
   * - Both start at the first row: Alice at column 0, Bob at column c-1.
   * - In each move, both can go to the same column, left, or right in the next row.
   * - If both land on the same cell, chocolates are counted only once.
   * - They continue moving until the last row.
   *
   * Approach:
   * - Recursive DP (Top-down) with memoization.
   * - A 3D DP table is used to store the state: dp[row][aliceCol][bobCol].
   * - At each level, explore 9 combinations of moves (3 for Alice × 3 for Bob).
   *
   * Time Complexity:  O(r * c * c * 9) ≈ O(r * c^2)
   * - r levels (rows)
   * - c options for Alice, c options for Bob
   * - 9 movement combinations per state
   *
   * Space Complexity: O(r * c^2)
   * - For the 3D dp array
   */

  int maxChoco(vector<vector<int>> &grid, vector<vector<vector<int>>> &dp, int r, int c, int lv, int aliceCol, int bobCol)
  {
    // If either Alice or Bob goes out of grid bounds, return very small value to ignore path
    if (aliceCol < 0 || aliceCol >= c || bobCol < 0 || bobCol >= c)
    {
      return INT_MIN;
    }

    // Base case: last row reached
    if (lv == r - 1)
    {
      // If both are in the same column, count once
      if (aliceCol == bobCol)
        return grid[lv][aliceCol];
      else
        return grid[lv][aliceCol] + grid[lv][bobCol];
    }

    // Return memoized result if already computed
    if (dp[lv][aliceCol][bobCol] != -1)
      return dp[lv][aliceCol][bobCol];

    int maxChocos = INT_MIN;

    // Try all 3×3 = 9 combinations of moves for Alice and Bob
    for (int k1 = -1; k1 <= 1; k1++)
    {
      for (int k2 = -1; k2 <= 1; k2++)
      {
        int aliceIdx = aliceCol + k1;
        int bobIdx = bobCol + k2;

        // Recursive call for the next level
        int result = maxChoco(grid, dp, r, c, lv + 1, aliceIdx, bobIdx);

        maxChocos = max(maxChocos, result);
      }
    }

    // Compute the total chocolates collected in the current cell(s)
    if (aliceCol == bobCol)
    {
      return dp[lv][aliceCol][bobCol] = grid[lv][aliceCol] + maxChocos;
    }
    else
    {
      return dp[lv][aliceCol][bobCol] = grid[lv][aliceCol] + grid[lv][bobCol] + maxChocos;
    }
  }

  // Wrapper function that initializes the DP array and triggers the recursive computation
  int maximumChocolates(int r, int c, vector<vector<int>> &grid)
  {
    // Initialize a 3D DP table with -1 for memoization
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));

    // Start from row 0, Alice at column 0, Bob at column c-1
    return maxChoco(grid, dp, r, c, 0, 0, c - 1);
  }

  //-------------------------------------------------------------------------------
  // 2. Title:
  //-------------------------------------------------------------------------------
};

int main()
{
  return 0;
}
