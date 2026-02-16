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

1. Title: Minimum cost to cut the stick| (DP-50)

Links:
https://takeuforward.org/data-structure/minimum-cost-to-cut-the-stick-dp-50/
https://www.youtube.com/watch?v=xwomavsC86c
https://takeuforward.org/plus/dsa/problems/minimum-cost-to-cut-the-stick?tab=editorial
https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/



Problem statement:
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:
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

    Example 2:
    Input: n = 9, cuts = [5,6,1,4,2]
    Output: 22
    Explanation: If you try the given cuts ordering the cost will be 25.
    There are much ordering with total cost <= 25, for example, the order [4, 6, 5, 2, 1] has total cost = 22 which is the minimum possible.


Constraints:
    2 <= n <= 106
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

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Minimum cost to cut the stick| (DP-50)
    //-------------------------------------------------------------------------------

    /*
    ============================================
    Approach 1: Recursion + Memoization with map
    ============================================

    Idea:
    ------
    - We recursively partition the stick between `start` and `end` based on cuts.
    - For each cut inside (start, end), we try making that cut and then recursively
    compute the cost of cutting the left and right parts.
    - Store the results in a map `dp[{start,end}]` to avoid recomputation.

    Implementation details:
    ------------------------
    - Base case: If no cut lies between `start` and `end`, cost = 0.
    - Otherwise: cost = (end - start) + min cost of partitioning left and right.

    Time Complexity:
    -----------------
    - There are O(m²) subproblems (`m = number of cuts`).
    - Each subproblem loops over O(m) possible cuts.
    - Each dp lookup/insertion in `std::map` costs O(log m).
    - Total = O(m² * m * log m) = **O(m³ log m)**.

    Space Complexity:
    ------------------
    - DP map stores at most O(m²) entries.
    - Recursion depth = O(m).
    - So space = **O(m² + m)**.

    */

    // int recPart(int start, int end, vector<int>& cuts, map<pair<int,int>, int> &dp){
    //     if(dp.find({start,end}) != dp.end()){
    //         return dp[{start,end}];
    //     }

    //     int curCost = end - start;
    //     int minRecPartCost = INT_MAX;

    //     for(int i=0; i<cuts.size(); i++){
    //         if(start < cuts[i] && cuts[i] < end){
    //             int leftpart = recPart(start, cuts[i], cuts, dp);
    //             int rightPart = recPart(cuts[i], end, cuts, dp);
    //             minRecPartCost = min(minRecPartCost, (leftpart+rightPart));
    //         }
    //     }

    //     if(minRecPartCost == INT_MAX){
    //         return dp[{start,end}] = 0;   // no cut possible
    //     } else {
    //         return dp[{start,end}] = curCost + minRecPartCost;
    //     }
    // }

    // int minCost(int n, vector<int>& cuts) {
    //     map<pair<int,int>, int> dp;
    //     return recPart(0, n, cuts, dp);
    // }

    /*
    Approach 2: Top-Down DP with Preprocessed Cuts (Interval DP)
    ------------------------------------------------------------
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

    int recPart(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
    {
        if (j - i <= 1)
            return 0; // no cut possible

        if (dp[i][j] != -1)
            return dp[i][j];

        int curCost = cuts[j] - cuts[i];
        int minRecPartCost = INT_MAX;

        for (int k = i + 1; k < j; k++)
        {
            int leftpart = recPart(i, k, cuts, dp);
            int rightPart = recPart(k, j, cuts, dp);
            minRecPartCost = min(minRecPartCost, (leftpart + rightPart));
        }

        return dp[i][j] = (minRecPartCost == INT_MAX ? 0 : curCost + minRecPartCost);
    }

    int minCost(int n, vector<int> &cuts)
    {
        cuts.insert(cuts.begin(), 0); // left boundary
        cuts.push_back(n);            // right boundary
        sort(cuts.begin(), cuts.end());

        int c = cuts.size();
        vector<vector<int>> dp(c, vector<int>(c, -1));

        return recPart(0, c - 1, cuts, dp);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
