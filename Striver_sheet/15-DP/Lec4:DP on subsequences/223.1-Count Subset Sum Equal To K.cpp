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

1. Title: Count Subset Sum Equal To K

Links:
https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1


Problem statement:
Given an array arr of non-negative integers and an integer target, the task is to count all subsets of the array whose sum is equal to the given target.

Examples:
  Input: arr[] = [5, 2, 3, 10, 6, 8], target = 10
  Output: 3
  Explanation: The subsets {5, 2, 3}, {2, 8}, and {10} sum up to the target 10.
  Input: arr[] = [2, 5, 1, 4, 3], target = 10
  Output: 3
  Explanation: The subsets {2, 1, 4, 3}, {5, 1, 4}, and {2, 5, 3} sum up to the target 10.
  Input: arr[] = [5, 7, 8], target = 3
  Output: 0
  Explanation: There are no subsets of the array that sum up to the target 3.
  Input: arr[] = [35, 2, 8, 22], target = 0
  Output: 1
  Explanation: The empty subset is the only subset with a sum of 0.
  Constraints:
  1 ≤ arr.size() ≤ 10^3
  0 ≤ arr[i] ≤ 10^3
  0 ≤ target ≤ 10^3



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


*/

/*
 * Method: countSubsetSum
 * ------------------
 * Counts the number of subsets in 'arr' that sum up to 'targetSum'.
 *
 * Logic: Dynamic Programming (0/1 Knapsack variation)
 * We build a table DP[i][s] representing the number of subsets using elements
 * from index 0 to i that sum up to 's'.
 *
 * State Definition:
 * DP[i][sum] = Number of subsets using first 'i+1' elements (indices 0..i)
 * that sum up to 'sum'.
 *
 * Recurrence:
 * For each element arr[i], we have two choices:
 * 1. Not Take: Count remains same as valid subsets using 0..i-1 for the same sum.
 * 2. Take: Add counts of subsets using 0..i-1 that sum to (sum - arr[i]).
 * DP[i][sum] = (Not Take) + (Take)
 *
 * Important Handling of Zeros:
 * The initialization specifically handles cases where arr[0] == 0.
 * If arr[0] is 0, there are TWO ways to make sum 0: {} (empty) and {0}.
 */
int countSubsetSum(vector<int> &arr, int targetSum)
{

  int n = arr.size();

  // DP Table initialization
  // Rows: indices of array elements (0 to n-1)
  // Cols: possible sum values (0 to targetSum)
  vector<vector<int>> DP(n, vector<int>(targetSum + 1, 0));

  // ---------------------------------------------------------
  // 1. Base Case Initialization (Index 0)
  // ---------------------------------------------------------

  // Case A: Not Taking the 0th element
  // There is always 1 way to make sum 0 (by taking an empty subset)
  DP[0][0] = 1;

  // Case B: Taking the 0th element
  // Important Check: Only possible if the element itself is <= targetSum
  if (arr[0] <= targetSum)
  {
    // CRITICAL LOGIC POINT: += 1 instead of = 1
    // Why? If arr[0] is 0, we have already set DP[0][0] = 1 (empty set).
    // Now, taking the element '0' is a second valid way to reach sum 0.
    // So DP[0][0] becomes 1 + 1 = 2.
    // If arr[0] is 5, DP[0][0] stays 1, and DP[0][5] becomes 1.
    DP[0][arr[0]] += 1;
  }

  // ---------------------------------------------------------
  // 2. Build the DP Table
  // ---------------------------------------------------------
  for (int i = 1; i < n; i++)
  {

    // Loop from sum = 0 to targetSum
    // Important: Must start from 0 to correctly update cases where arr[i] == 0
    for (int sum = 0; sum <= targetSum; sum++)
    {

      int take = 0;
      int notTake = 0;

      // Option 1: Take current element arr[i]
      // Valid only if current sum is large enough to include arr[i]
      if (sum - arr[i] >= 0)
      {
        take = DP[i - 1][sum - arr[i]];
      }

      // Option 2: Do not take current element
      // Inherit the count from the previous state directly
      notTake = DP[i - 1][sum];

      // Total ways = ways(Take) + ways(Not Take)
      // Note: For large inputs, perform modulo arithmetic here: (take + notTake) % 1e9+7
      DP[i][sum] = take + notTake;
    }
  }

  // The answer is the number of subsets using elements 0..n-1 to get targetSum
  return DP[n - 1][targetSum];
}

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n, targetSum;

  cin >> n;
  cin >> targetSum;

  vector<int> nums;

  int count = n;
  while (count--)
  {
    int temp;
    cin >> temp;
    nums.push_back(temp);
  }

  cout << countSubsetSum(nums, targetSum);

  return 0;
}
