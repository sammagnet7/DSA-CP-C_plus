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
https://www.hackerrank.com/contests/mock-test-2-1758395674/challenges/meet-in-the-middle-3-1


Problem statement:
You are given an array of n numbers. In how many ways can you choose a subset of the numbers with sum x?

Example
    Input:
    4 5 1 2 3 2
    Output:
    3

Input Format
The first input line has two numbers n and x: the array size and the required sum. The second line has n integers t1,t2,...,tn: the numbers in the array.

Constraints
    1<=n<=40
    1<=x<=10^9
    1<=ti<=10^9

Output Format
    Print the number of ways you can create the sum x.

Sample Input 0
    10 17
    5 8 5 6 9 1 2 5 8 6
    Sample Output 0
    22

    Sample Input 1
    40 1
    1 2 2 1 1 1 2 2 2 2 1 1 2 1 1 2 2 1 1 2 2 1 2 2 2 2 2 2 1 2 1 2 1 2 1 2 2 1 2 1
    Sample Output 1
    17



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
// 1. Title: Count Subset Sum Equal To K
//    Approach1: recursive with memoization
//-------------------------------------------------------------------------------

/*
countSubsetSum (recursive with memoization)
-------------------------------------------
Purpose:
  - Counts the number of subsets of `nums[0..idx]` that sum exactly to `sum`.
  - Uses recursion with memoization (top-down DP).

Parameters:
  - idx : current index in array (0-based)
  - sum : remaining target sum
  - nums: input array
  - dp  : memoization table; dp[i][s] stores the count of subsets using nums[0..i]
          that sum to `s`. Initialized with -1 (unvisited).

Recurrence:
  - Either include nums[idx] (reduce sum) or exclude it.
  - Base cases:
      * If idx < 0 and sum == 0 → found one valid subset (the empty subset).
      * If idx < 0 and sum != 0 → no valid subset.
      * If sum < 0 → invalid path.

Time Complexity:
  - O(n * sum)
    Each state (idx, sum) is computed once and memoized.
  - Each state takes O(1) time after recursion + memoization.

Space Complexity:
  - O(n * sum) for the DP table.
  - O(n) recursion stack depth (since idx decreases down to -1).

Limitations:
  - `sum` can be as large as 1e9 in some problems (e.g., "Meet in the Middle" subset-sum variant).
    → This approach becomes infeasible for large sums because:
        * DP table size = n * (sum+1) → memory blowup.
        * Time also scales linearly with `sum`.
  - Practically only feasible when `n * sum ≤ ~10^7` (depending on memory/time limits).
  - For large sums, alternative techniques (e.g., Meet in the Middle, bitset-based DP)
    must be used.

*/
int countSubsetSum(int idx, int sum, vector<int> &nums, vector<vector<int>> &dp)
{

    // Base case: no elements left and target achieved
    if (idx < 0 && sum == 0)
        return 1;

    // Base case: no elements left but target not achieved
    else if (idx < 0 && sum != 0)
        return 0;

    // Base case: overshoot target sum (invalid path)
    else if (sum < 0)
    {
        return 0;
    }

    // Optimization: if target already zero, any remaining elements excluded
    if (idx >= 0 && sum == 0)
        return dp[idx][sum] = 1;

    // Return cached result if available
    if (dp[idx][sum] != -1)
    {
        return dp[idx][sum];
    }

    // Recurrence: include or exclude nums[idx]
    return dp[idx][sum] =
               countSubsetSum(idx - 1, sum - nums[idx], nums, dp) + // include current
               countSubsetSum(idx - 1, sum, nums, dp);              // exclude current
}

/*
    Wrapper to set up the DP table and call recursive function.

    - Initializes a 2D DP array of size n x (sum+1), filled with -1.
    - Starts recursion from the last index with the full target sum.
    - Returns the total count of subsets that sum to `sum`.

    Limitations:
      - Memory usage = O(n * sum). For large `sum`, this can exceed limits.
      - Works only for moderate values of `sum` (e.g., ≤ 1e5–1e6 depending on `n`).
*/
int countSubsetSumWrapper(int n, int sum, vector<int> &nums)
{
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    countSubsetSum(n - 1, sum, nums, dp);

    return dp[n - 1][sum];
}

//-------------------------------------------------------------------------------
// Approach2: Iterative (bottom-up tabulation DP)
//-------------------------------------------------------------------------------

/*
    countSubsetSumWrapper:
    ----------------------
    Approach2: bottom-up tabulation DP
      - Bottom-up Dynamic Programming (tabulation).
      - We build a DP table iteratively where each cell dp[i][s] stores
        the number of subsets from nums[0..i] that sum exactly to s.
      - Transition is based on including or excluding the current element.

    Purpose:
      - Count the number of subsets in `nums` whose sum equals `totSum`.

    Parameters:
      - n       : number of elements in the array
      - totSum  : target sum
      - nums    : input array (positive integers assumed)

    DP State Definition:
      - dp[i][s] = number of subsets using elements from nums[0..i]
                   that sum exactly to s.

    Base Cases:
      1) dp[i][0] = 1 for all i
         - Intuition: the empty subset always achieves sum = 0.
      2) dp[0][nums[0]] = 1 (if nums[0] ≤ totSum)
         - With only the first element, the only non-zero sum achievable is nums[0].

    Transition (recurrence):
      For each index idx and sum s:
        - If we include nums[idx], we must form (s - nums[idx]) using previous elements.
        - If we exclude nums[idx], we must form s using previous elements.
      Hence:
        dp[idx][s] = dp[idx-1][s - nums[idx]] + dp[idx-1][s]   if s >= nums[idx]
                   = dp[idx-1][s]                              otherwise.

    Answer:
      - dp[n-1][totSum] gives the number of subsets of the full array that sum to totSum.

    Complexity:
      - Time:  O(n * totSum) → filling an n x (totSum+1) table.
      - Space: O(n * totSum) for the table.

    Limitations:
      - This approach is infeasible if totSum is very large (e.g., up to 1e9).
      - Practical limit: n * totSum ≤ ~10^7 for typical memory/time constraints.
      - For larger sums and small n (e.g., n ≤ 40), use alternative methods like
        Meet in the Middle.
*/
int countSubsetSumWrapper(int n, int totSum, vector<int> &nums)
{

    // DP table: rows = elements, columns = sums
    vector<vector<int>> dp(n, vector<int>(totSum + 1, 0));

    // Base Case 1: sum = 0 is always achievable (empty subset)
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
    }

    // Base Case 2: with only the first element, we can form sum = nums[0]
    if (nums[0] <= totSum)
    {
        dp[0][nums[0]] = 1;
    }

    // Fill DP table bottom-up
    for (int idx = 1; idx < n; idx++)
    {
        for (int sum = 1; sum <= totSum; sum++)
        {
            if (sum - nums[idx] >= 0)
            {
                // Option 1: include nums[idx], Option 2: exclude it
                dp[idx][sum] = dp[idx - 1][sum - nums[idx]] + dp[idx - 1][sum];
            }
            else
            {
                // Can't include nums[idx], only option: exclude it
                dp[idx][sum] = dp[idx - 1][sum];
            }
        }
    }

    // Final answer
    return dp[n - 1][totSum];
}

//-------------------------------------------
// Approach3: Iterative (Meet-in-the-Middle)
//-------------------------------------------

/*
  generateAllSubsetsums (iterative bitmask version)
  ------------------------------------------------
  Purpose:
    - Enumerate all subset sums for the contiguous subarray nums[startIdx..endIdx]
      and append them to allSubsetsums.
    - This version uses the standard bitmask technique: treat each integer from
      0..(2^m - 1) as a selection mask for the m elements in the subarray.

  Approach & intuition:
    - A subarray of length m has exactly 2^m subsets. Each subset can be
      represented by an m-bit integer (bit i = 1 means include element i).
    - Iterate every possible bitmask. For each bitmask, loop the subarray
      positions and add the element if the corresponding mask bit is set.
    - Collect the sum for that mask into the result vector.
    - This approach is straightforward, explicit, and avoids recursion; it is
      a good fit when m is small (<= ~25 in practice, and here m <= 20 for n<=40).

  Complexity:
    - Time: O(m * 2^m) where m = endIdx - startIdx + 1.
    - Space: O(2^m) additional space to store all subset sums in allSubsetsums.
    - Use-case: in meet-in-the-middle, m is roughly n/2, so when n<=40 this is feasible.

  Notes / pitfalls:
    - Be careful with integer types and bit-shifts. (The code below intentionally
      uses 1 << (i-startIdx) for clarity — on platforms where left-shift of
      signed 1 may be risky for large shifts you can use (1u << ...) or 1ULL.)
    - For large m this becomes expensive quickly (exponential blow-up).
*/

// void generateAllSubsetsums(int startIdx, int initSum, int endIdx, vector<int> &nums, vector<int> &allSubsetsums)
// {

//     int array_size = endIdx - startIdx + 1; // number of elements in this subarray (m)
//     int subset_size = (1 << array_size);    // total number of masks = 2^m

//     for (int bitmask = 0; bitmask < subset_size; bitmask++)
//     { // for each 2^array_size possibilities a bitmask to be used

//         int curSum = 0;

//         for (int i = startIdx; i <= endIdx; i++)
//         {
//             if ((bitmask & 1 << (i - startIdx)))
//             {
//                 curSum += nums[i];
//             }
//         }

//         allSubsetsums.push_back(curSum); // record the sum for this particular subset (mask)
//     }
// }

/*
  generateAllSubsetsums (recursive version)
  ----------------------------------------
  Purpose:
    - Another way to enumerate all subset sums for nums[curIdx..endIdx], appending to allSubsetsums.
    - This recursive form is often considered more "intuitive" because it mirrors the include/exclude
      decision tree: at each index either include the element or skip it.

  Approach & intuition:
    - At each element (curIdx) we have two choices:
        1) include nums[curIdx] in the running sum (curSum + nums[curIdx])
        2) exclude nums[curIdx] (curSum)
    - Recursively explore both branches until we pass the end index; when the traversal completes
      push the accumulated curSum into allSubsetsums.
    - The recursion naturally enumerates all 2^m possibilities.
    - This is functionally equivalent to the bitmask method but uses recursion rather than integer masks.

  Complexity:
    - Time: O(2^m) recursive calls, each doing O(1) work (plus push_back).
    - Space: O(2^m) for storing results + O(m) recursion depth (stack).

  Notes:
    - Recursive approach is clearer for many readers, but has a small recursion overhead.
    - Use this when m is small (<= ~25). For very large m recursion may risk stack overflow.
*/
void generateAllSubsetsums(int curIdx, int curSum, int endIdx, vector<int> &nums, vector<int> &allSubsetsums)
{

    // base case: whenever traversing the array completes, saves the current sum
    if (curIdx == endIdx + 1)
    {
        allSubsetsums.push_back(curSum);
        return;
    }

    // Include current element and recurse
    generateAllSubsetsums(curIdx + 1, curSum + nums[curIdx], endIdx, nums, allSubsetsums);
    // Exclude current element and recurse
    generateAllSubsetsums(curIdx + 1, curSum, endIdx, nums, allSubsetsums);
}

/*
  countSubsetSumWrapper (Meet-in-the-Middle)
  ------------------------------------------
  Purpose:
    - Count how many subsets of the entire array nums[0..n-1] have sum equal to targetSum.
    - Uses the meet-in-the-middle technique: split the array into two halves, enumerate all subset
      sums of each half, and then pair sums from the left half with complementary sums from the right
      half so that leftSum + rightSum == targetSum.

  High-level approach:
    1) Split array into left segment [0 .. leftSize-1] and right segment [leftSize .. n-1].
    2) Generate all subset sums for the left segment (leftSubsetsums).
       - There will be 2^leftSize sums.
    3) Generate all subset sums for the right segment (rightSubsetsums).
       - There will be 2^rightSize sums.
    4) Sort the rightSubsetsums vector so we can use binary search to count complements fast.
    5) For each leftSum in leftSubsetsums compute complement = targetSum - leftSum,
       then count how many times complement occurs in rightSubsetsums via equal_range.
    6) Sum these counts to get the total number of subsets whose sum == targetSum.

  Why this works (intuition):
    - Every subset of the full array can be split into elements chosen from the left half
      and elements chosen from the right half. If the left part sums to L and the right to R,
      then the full subset sum is L+R. By enumerating all possible L and R values and counting
      complementary pairs you count all full-array subsets exactly once.

  Complexity:
    - Time:
        * Generating left sums: O(leftSize * 2^leftSize) (bitmask) or O(2^leftSize) (recursion).
        * Generating right sums: similar with rightSize.
        * Sorting rightSubsetsums: O(2^rightSize * log 2^rightSize).
        * For each left sum (2^leftSize) perform binary search in right sums: O(2^leftSize * log 2^rightSize).
        Overall roughly O(2^(n/2) log 2^(n/2)) for n up to ~40.
    - Space: O(2^leftSize + 2^rightSize) to store subset sums.

  Practical limits / notes:
    - This approach is ideal when n <= ~40 (each half <= 20, so 2^20 ≈ 1e6).
    - Use 64-bit integers (long long) if elements and sums can be large; here the code uses int.
      If nums elements or targetSum are large (>= 1e9) switch sums and counters to long long.
    - Reserving vector capacity (reserve(1<<leftSize)) avoids repeated reallocations.
    - The code below uses the bitmask or recursive generators interchangeably — pick one consistent style.

  Implementation details (mapping to code below):
    - leftSize = mid, rightSize = n - mid
    - leftSubsetsums.reserve(1<<leftSize) and rightSubsetsums.reserve(1<<rightSize)
    - generators called for the two halves
    - sort(rightSubsetsums) and for each left sum use equal_range to count matches

  Correctness caveats:
    - If using ints and input values are large, sums may overflow int. Consider using long long types.
    - If leftSize or rightSize become large (> 25), the enumeration may become too slow / memory heavy.
*/
int countSubsetSumWrapper(int n, int targetSum, vector<int> &nums)
{

    int mid = n / 2;
    int leftSize = mid;
    int rightSize = n - mid;

    vector<int> leftSubsetsums;
    leftSubsetsums.reserve(1 << leftSize); // 2^leftSize

    vector<int> rightSubsetsums;
    rightSubsetsums.reserve(1 << rightSize); // 2^rightSize

    // generate subset sums for left half [0 .. leftSize-1]
    generateAllSubsetsums(0, 0, leftSize - 1, nums, leftSubsetsums);
    // generate subset sums for right half [leftSize .. leftSize+rightSize-1] i.e. [leftSize .. n-1]
    generateAllSubsetsums(leftSize + 0, 0, leftSize + rightSize - 1, nums, rightSubsetsums);

    // sort right sums for binary-search counting of complements
    sort(rightSubsetsums.begin(), rightSubsetsums.end());

    int ans = 0;

    // iterate every left subset sum and count complementary right sums
    for (int i = 0; i < (1 << leftSize); i++)
    {
        int leftSum = leftSubsetsums[i];
        int restTargetSum = targetSum - leftSum;

        auto matchRange = equal_range(rightSubsetsums.begin(), rightSubsetsums.end(), restTargetSum);

        ans += distance(matchRange.first, matchRange.second);
    }

    return ans;
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, sum;

    cin >> n;
    cin >> sum;

    vector<int> nums;

    int count = n;
    while (count--)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    cout << countSubsetSumWrapper(n, sum, nums);

    return 0;
}
