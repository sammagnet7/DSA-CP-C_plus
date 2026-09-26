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

1. Title: Minimum cost to cut the stick

Links:
https://takeuforward.org/data-structure/minimum-cost-to-cut-the-stick-dp-50/
https://www.youtube.com/watch?v=xwomavsC86c
https://takeuforward.org/plus/dsa/problems/minimum-cost-to-cut-the-stick?tab=editorial
https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/



Problem statement:
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:

    |   |   |   |   |   |   |
    0   1   2   3   4   5   6

Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.

Return the minimum total cost of the cuts.

Examples:
    Example 1:
    Input: n = 7, cuts = [1,3,4,5]
    Output: 16
    Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:

    The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
    Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).

            Stage 1: Initial Rod (Length 7)
            |---------------------------|
            0   1   2   3   4   5   6   7

            Stage 2: Cut at 1 (Cost: 7)
            |---|   |-----------------------|
            0   1   1   2   3   4   5   6   7

            Stage 3: Cut at 3 (Cost: 6)
            |---|   |-------|   |---------------|
            0   1   1   2   3   3   4   5   6   7

            Stage 4: Cut at 4 (Cost: 4)
            |---|   |-------|   |---|   |-----------|
            0   1   1   2   3   3   4   4   5   6   7

            Stage 5: Cut at 5 (Cost: 3)
            |---|   |-------|   |---|   |---|   |-------|
            0   1   1   2   3   3   4   4   5   5   6   7

    Example 2:
    Input: n = 9, cuts = [5,6,1,4,2]
    Output: 22
    Explanation: If you try the given cuts ordering the cost will be 25.
    There are much ordering with total cost <= 25, for example, the order [4, 6, 5, 2, 1] has total cost = 22 which is the minimum possible.


Constraints:
    2 <= n <= 10^6
    1 <= cuts.length <= min(n - 1, 100)
    1 <= cuts[i] <= n - 1
    All the integers in cuts array are distinct.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:



Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------


*/

//-------------------------------------------------------------------------------
// 1. Title: Minimum cost to cut the stick
//-------------------------------------------------------------------------------

// ===================================================
// Approach 1: Top-Down DP (Memoization) [TLE]
// ===================================================

/**
 * Approach: Top-Down DP (Memoization).
 * * Logic:
 * We treat the rod as a segment defined by physical boundaries [leftBound, rightBound].
 * For any given segment, we iterate through all possible cut positions provided.
 * If a cut falls within the current segment, we split the rod into two sub-segments
 * and recursively find the minimum cost to cut those pieces.
 *
 * State: dp[leftBound][rightBound] = Minimum cost to cut the segment from leftBound to rightBound.
 * * Complexity:
 * - Time: O(N^2 * M), where N is the length of the rod and M is the number of cuts.
 * There are O(N^2) possible states for (left, right) and for each state, we loop over M cuts.
 * - Space: O(N^2) to store the memoization table.
 *
 * * Note: This approach is suboptimal because N can be very large (up to 10^9),
 * leading to Memory Limit Exceeded (MLE).
 */
class Solution
{
    const int INF = 1e9 + 7;

private:
    int findMinCost(int leftBound, int rightBound, vector<vector<int>> &memo, const vector<int> &cuts)
    {

        // Base Case: If the segment length is 1 or less, no integer cuts are possible.
        if (leftBound + 1 >= rightBound)
        {
            return 0;
        }

        // Check if the result for this specific segment [leftBound, rightBound] is already cached.
        if (memo[leftBound][rightBound] != -1)
        {
            return memo[leftBound][rightBound];
        }

        int currentSegmentLength = rightBound - leftBound;
        int minCostOfSplits = INF;
        bool hasValidCut = false;

        // Try every cut in the list to see if it can split the current segment.
        for (int cutPos : cuts)
        {
            if (cutPos > leftBound && cutPos < rightBound)
            {
                hasValidCut = true;

                // Recursive relation: cost = (left segment cost) + (right segment cost)
                int cost = findMinCost(leftBound, cutPos, memo, cuts) +
                           findMinCost(cutPos, rightBound, memo, cuts);

                minCostOfSplits = min(minCostOfSplits, cost);
            }
        }

        // If no cuts were valid inside this segment, the cost is 0.
        // Otherwise, cost = length of current rod + minimum cost of further splits.
        int result = (hasValidCut) ? (currentSegmentLength + minCostOfSplits) : 0;

        // Memoize and return.
        return memo[leftBound][rightBound] = result;
    }

public:
    int minCost(int n, vector<int> &cuts)
    {
        // Warning: This allocation will fail for large values of n.
        // For n = 10^5, this requires ~40GB of memory.
        vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));

        return findMinCost(0, n, memo, cuts);
    }
};

// =========================================================
// Approach 2: Top-Down DP (Memoization + map) [Sub-optimal]
// =========================================================

class Solution
{
    const int INF = 1e9 + 7;

private:
    /**
     * Approach: Top-Down DP with Sparse Memoization (using std::map).
     *
     * Idea:
     * ------
     * - As the DP table is too sparsed, instead of using vector we us map here.
     * - We recursively partition the stick between `start` and `end` based on cuts.
     * - For each cut inside (start, end), we try making that cut and then recursively
     * compute the cost of cutting the left and right parts.
     * - Store the results in a map `dp[{start,end}]` to avoid recomputation.
     *
     * Implementation details:
     * ------------------------
     * - Base case: If no cut lies between `start` and `end`, cost = 0.
     * - Otherwise: cost = (end - start) + min cost of partitioning left and right.
     *
     * Time Complexity:
     * -----------------
     * - There are O(m²) subproblems (`m = number of cuts`).
     * - Each subproblem loops over O(m) possible cuts.
     * - Each dp lookup/insertion in `std::map` costs O(log m).
     * - Total = O(m² * m * log m) = **O(m³ log m)**.
     *
     * Space Complexity:
     * ------------------
     * - DP map stores at most O(m²) entries.
     * - Recursion depth = O(m).
     * - So space = O(m² + m)
     *
     * * WHY THIS IS PASSING:
     * 1. Space Efficiency: Even though N can be 10^9, you only make cuts at specific
     * points defined in the `cuts` array (which usually has a max length M of ~100).
     * By using a `map<pair<int, int>, int>`, you only allocate memory for the
     * segments you actually visit. The maximum number of unique segments is bounded
     * by the number of pairs of cut points, which is O(M^2), not O(N^2).
     * 2. Acceptable Time Complexity: For each of the O(M^2) states, you iterate through
     * all M cuts. Map lookups take O(log(M^2)). This results in an overall time
     * complexity of roughly O(M^3 * log M). If M is 100, M^3 is 1,000,000, which
     * easily runs within the typical 1-second time limit on platforms like LeetCode.
     *
     * * WHY FURTHER OPTIMIZATION IS NEEDED:
     * 1. High Overhead: `std::map` is a Red-Black Tree. Every lookup and insertion takes
     * O(log K) time and involves pointer chasing in memory, which is much slower
     * than O(1) array access.
     * 2. Redundant Iterations: Because the `cuts` array isn't sorted, you are forced
     * to loop through the entire array for every recursive call, even if the current
     * segment [leftBound, rightBound] is very small and only contains 1 or 2 valid cuts.
     * 3. The "Gold Standard": By sorting the cuts and redefining the DP state to track
     * cut indices rather than rod coordinates, we can use a fast, contiguous 2D
     * array/vector and drop the time complexity to a pure O(M^3).
     */
    int findMinCost(int leftBound, int rightBound, map<pair<int, int>, int> &memo, const vector<int> &cuts)
    {

        // Base Case: If the segment length is 1 or less, no integer cuts are possible.
        if (leftBound + 1 >= rightBound)
        {
            return 0;
        }

        // Check if the result for this specific segment [leftBound, rightBound] is already cached.
        // Map lookups take O(log(Number of States)).
        if (memo.find({leftBound, rightBound}) != memo.end())
        {
            return memo[{leftBound, rightBound}];
        }

        int currentSegmentLength = rightBound - leftBound;
        int minCostOfSplits = INF;
        bool hasValidCut = false;

        // Try every cut in the list to see if it can split the current segment.
        // Bottleneck: This loop always runs M times, regardless of the segment size.
        for (int cutPos : cuts)
        {
            if (cutPos > leftBound && cutPos < rightBound)
            {
                hasValidCut = true;

                // Recursive relation: cost = (left segment cost) + (right segment cost)
                int cost = findMinCost(leftBound, cutPos, memo, cuts) +
                           findMinCost(cutPos, rightBound, memo, cuts);

                minCostOfSplits = min(minCostOfSplits, cost);
            }
        }

        // If no cuts were valid inside this segment, the cost is 0.
        // Otherwise, cost = length of current rod + minimum cost of further splits.
        int result = (hasValidCut) ? (currentSegmentLength + minCostOfSplits) : 0;

        // Memoize and return.
        return memo[{leftBound, rightBound}] = result;
    }

public:
    int minCost(int n, vector<int> &cuts)
    {
        // Using a map prevents the Memory Limit Exceeded (MLE) error that would
        // occur with an N x N 2D array.
        map<pair<int, int>, int> memo;

        return findMinCost(0, n, memo, cuts);
    }
};

// ======================================================================
// Approach 3: Top-Down DP with Preprocessed Cuts (Interval DP) [OPTIMAL]
// ======================================================================

/*
Idea:
- Preprocess cuts:
    - Insert 0 (left boundary) and n (right boundary).
    - Sort cuts for ordered positions.
- Now the problem becomes interval DP:
    dp[i][j] = minimum cost to cut between cuts[i] and cuts[j].
- Transition:
    For every possible cut k between i and j:
        dp[i][j] = min( dp[i][j], (cuts[j]-cuts[i]) + dp[i][k] + dp[k][j] )
- Base Case:
    If j - i <= 1 → no space for cuts in between → cost = 0.

Key Improvements over Approach 1:
- Sorting + boundary padding ensures structured intervals.
- Instead of looping over all cuts, we only loop between i+1 … j-1.
- Faster since we restrict unnecessary checks.

Time Complexity:
- O(m^3), where m = cuts.size() + 2 (after adding boundaries).
- Each interval (i,j) is solved once, looping over possible k in between.

Space Complexity:
- O(m^2) for dp array.
- O(m) recursion stack depth.

This is the standard Interval DP solution for this problem and is more efficient and clean than the map-based approach.

*/
class Solution
{
    // A large enough value to represent infinity when looking for minimums.
    // 1e9 + 7 is commonly used to prevent integer overflow when adding costs.
    const int INF = 1e9 + 7;

private:
    /**
     * @param leftBound The INDEX in the 'cuts' array representing the left end of the current rod segment.
     * @param rightBound The INDEX in the 'cuts' array representing the right end of the current rod segment.
     * @param memo 2D DP table storing the minimum cost to cut the segment between leftBound and rightBound.
     * @param cuts The modified and sorted array of cut points (including 0 and n).
     */
    int findMinCost(int leftBound, int rightBound, vector<vector<int>> &memo, const vector<int> &cuts)
    {

        // BASE CASE: If the left and right indices are adjacent (e.g., index 1 and index 2),
        // there are absolutely no valid cut points between them. Therefore, the cost to cut is 0.
        if (leftBound + 1 >= rightBound)
        {
            return 0;
        }

        // MEMOIZATION CHECK: If we have already calculated the minimum cost for this specific
        // pair of boundary indices, return it immediately to save time in O(1).
        if (memo[leftBound][rightBound] != -1)
        {
            return memo[leftBound][rightBound];
        }

        // The physical cost of making ANY cut in this segment is exactly the physical length
        // of the segment. We calculate this by looking up the actual physical coordinates
        // at our current boundary indices.
        int currentSegmentLength = cuts[rightBound] - cuts[leftBound];

        int minCostOfSplits = INF;

        // Iterate through all possible indices strictly strictly INSIDE our current boundaries.
        // Because the array is sorted, every index 'cutPos' here is guaranteed to be a valid cut.
        for (int cutPos = leftBound + 1; cutPos < rightBound; ++cutPos)
        {

            // DIVIDE AND CONQUER: Simulate making a cut at 'cutPos'.
            // This splits our rod into a left piece [leftBound to cutPos]
            // and a right piece [cutPos to rightBound].
            int leftPartCost = findMinCost(leftBound, cutPos, memo, cuts);
            int rightPartCost = findMinCost(cutPos, rightBound, memo, cuts);

            // Keep track of the cheapest way we've found to split this current segment.
            minCostOfSplits = min(minCostOfSplits, (leftPartCost + rightPartCost));
        }

        // Add the cost of making the cut (currentSegmentLength) to the cost of the sub-problems.
        // (Note: Since your loop is guaranteed to run at least once due to the base case,
        // minCostOfSplits will never actually be INF here, but this ternary is a safe guardrail).
        int result = (minCostOfSplits == INF) ? 0 : (currentSegmentLength + minCostOfSplits);

        // Store the calculated minimum cost in our DP table before returning it.
        return memo[leftBound][rightBound] = result;
    }

public:
    int minCost(int n, vector<int> &cuts)
    {

        // PRE-PROCESSING: Treat the start (0) and end (n) of the original rod as "cuts".
        // This standardizes our logic so every segment is bounded by elements in this array.
        cuts.push_back(0);
        cuts.push_back(n);

        // Sorting is crucial! It ensures that indices map perfectly to physical left-to-right order.
        sort(cuts.begin(), cuts.end());

        // 'm' is the total number of points we care about (original cuts + 2 boundaries).
        int m = cuts.size();

        // Initialize the DP table. Size (m+1) x (m+1) is completely safe and covers all indices.
        // Filled with -1 to indicate uncalculated states.
        vector<vector<int>> memo(m + 1, vector<int>(m + 1, -1));

        // Start the top-down recursion.
        // The entire original rod spans from the very first index (0) to the very last index (m-1).
        return findMinCost(0, m - 1, memo, cuts);
    }
};

// ====================================================================================
// Approach 4: Bottom-Up DP with Preprocessed Cuts (Interval DP) [OPTIMAL][RECOMMENDED]
// ====================================================================================
class Solution
{
    const int INF = 1e9 + 7;

public:
    /**
     * Approach: Bottom-Up Dynamic Programming (Interval DP)
     * * Algorithm:
     * 1. We redefine the problem from "cutting a rod of length N" to "choosing a sequence
     * of cut indices". To do this, we add the rod boundaries (0 and n) to our `cuts`
     * array and sort it.
     * 2. State Definition: Let `dp[i][j]` be the minimum cost to perform all possible
     * cuts on the rod segment between `cuts[i]` and `cuts[j]`.
     * 3. Base Case: If there are no cut points between i and j (i.e., j == i + 1),
     * the cost is 0. Our table is initialized to 0, handling this naturally.
     * 4. Transition: For any segment [i, j], we try making a first cut at every possible
     * index `k` (where i < k < j). The cost will be:
     * Cost(i, j) = (cuts[j] - cuts[i]) + dp[i][k] + dp[k][j]
     * We take the minimum of these costs across all possible `k`.
     * 5. Traversal Order: In Interval DP, we must solve smaller intervals before larger
     * ones. We achieve this by iterating the left bound `i` backwards, and the right
     * bound `j` forwards.
     * * Complexity:
     * - Time Complexity: O(M^3), where M is the number of elements in the modified `cuts`
     * array (original cuts + 2). There are O(M^2) states, and for each state, we do
     * at most O(M) work in the `k` loop.
     * - Space Complexity: O(M^2) to store the 2D `dp` table. Since M <= 102, this is
     * extremely minimal and easily avoids the Memory Limit Exceeded issues of an N x N table.
     */
    int minCost(int n, vector<int> &cuts)
    {

        // Step 1: Pre-process the cuts array to include physical boundaries
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        int m = cuts.size();

        // Step 2: Initialize the DP table with 0s.
        // Size is m x m because indices go from 0 to m-1.
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // Step 3: Build the table bottom-up.
        // `i` represents the left boundary index. We move backwards to ensure
        // smaller sub-segments are processed first.
        for (int i = m - 1; i >= 0; --i)
        {

            // `j` represents the right boundary index.
            // We start at i + 2 because segments of length 1 (j == i + 1) have no cuts
            // inside them and cost 0 (which is already set by the initialization).
            for (int j = i + 2; j < m; ++j)
            {

                // The physical length of the segment we are currently trying to cut
                int currentSegmentLength = cuts[j] - cuts[i];
                int minCostOfSplits = INF;

                // `k` represents the index of the cut we are making between i and j
                for (int k = i + 1; k < j; ++k)
                {

                    // Since i goes backwards and j goes forwards, dp[i][k] and dp[k][j]
                    // are guaranteed to have already been calculated.
                    int leftPartCost = dp[i][k];
                    int rightPartCost = dp[k][j];

                    minCostOfSplits = min(minCostOfSplits, (leftPartCost + rightPartCost));
                }

                // The total cost for dp[i][j] is the cost of the cut itself (currentSegmentLength)
                // plus the best way we found to cut the resulting sub-segments.
                dp[i][j] = currentSegmentLength + minCostOfSplits;
            }
        }

        // The final answer is the cost to cut the entire rod, from index 0 to index m-1.
        return dp[0][m - 1];
    }
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------
int main()
{
    return 0;
}
