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

1. Title: Edit Distance | (DP-33)

Links:
https://takeuforward.org/data-structure/edit-distance-dp-33/
https://www.youtube.com/watch?v=fJaKO8FbDdo
https://takeuforward.org/plus/dsa/problems/edit-distance?tab=editorial
https://leetcode.com/problems/edit-distance/


Problem statement:
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character

Examples:
    Example 1:
    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation:
    horse -> rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')

    Example 2:
    Input: word1 = "intention", word2 = "execution"
    Output: 5
    Explanation:
    intention -> inention (remove 't')
    inention -> enention (replace 'i' with 'e')
    enention -> exention (replace 'n' with 'x')
    exention -> exection (replace 'n' with 'c')
    exection -> execution (insert 'u')


Constraints:
    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters.


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
    // 1. Title: Edit Distance | (DP-33)
    //-------------------------------------------------------------------------------

    // ---------------------------------
    // Approach 1 (Inefficient, TLE on large cases)
    // ---------------------------------
    //
    // Idea:
    //  - Carry an "opCount" parameter down the recursion to accumulate operations.
    //  - Memoize results in a 3D dp: [id1][id2][opCount].
    //
    // Problems:
    //  - The dp state includes `opCount`, which can be as large as (n1+n2).
    //  - That makes the state space O(n1 * n2 * (n1+n2)).
    //  - Extremely memory-heavy and slow → leads to TLE/MLE.
    //
    // Time Complexity: O(n1 * n2 * (n1+n2))
    // Space Complexity: O(n1 * n2 * (n1+n2))
    // → Not practical for strings of length ~500 or larger.
    //
    int recOpCount(int id1, int id2, int opCount,
                   string &word1, string &word2,
                   vector<vector<vector<int>>> &dp)
    {

        if (id1 == -1 && id2 == -1)
            return opCount;
        else if (id1 == -1)
            return opCount + id2 + 1; // need to insert all remaining chars from word2
        else if (id2 == -1)
            return opCount + id1 + 1; // need to delete all remaining chars from word1

        if (dp[id1][id2][opCount] != -1)
            return dp[id1][id2][opCount];

        if (word1[id1] == word2[id2])
        {
            return dp[id1][id2][opCount] =
                       recOpCount(id1 - 1, id2 - 1, opCount, word1, word2, dp);
        }
        else
        {
            int op1 = recOpCount(id1, id2 - 1, opCount + 1, word1, word2, dp);     // insert
            int op2 = recOpCount(id1 - 1, id2, opCount + 1, word1, word2, dp);     // delete
            int op3 = recOpCount(id1 - 1, id2 - 1, opCount + 1, word1, word2, dp); // replace

            return dp[id1][id2][opCount] = min({op1, op2, op3});
        }
    }

    int minDistance(string word1, string word2)
    {
        int n1 = word1.size();
        int n2 = word2.size();
        int maxOps = n1 + n2; // worst case

        vector<vector<vector<int>>> dp(n1,
                                       vector<vector<int>>(n2, vector<int>(maxOps, -1)));

        return recOpCount(n1 - 1, n2 - 1, 0, word1, word2, dp);
    }

    // -----------------------
    // Approach 2 (Optimal, Accepted)
    // -----------------------
    //
    // Idea:
    //  - State defined only by indices (id1,id2).
    //  - Recurrence:
    //      if word1[id1]==word2[id2] → no cost, move diagonally
    //      else → 1 + min(insert, delete, replace)
    //  - Base cases:
    //      if one string is empty, need to insert/delete the other length.
    //
    // Time Complexity: O(n1 * n2)
    // Space Complexity: O(n1 * n2)
    // → Works efficiently up to word lengths ~1000.
    //
    // Note: opCount is NOT carried in the recursion here.
    //       Each dp[id1][id2] stores the minimum operations
    //       needed to convert word1[0..id1] → word2[0..id2].
    //
    int recOpCount(int id1, int id2,
                   string &word1, string &word2,
                   vector<vector<int>> &dp)
    {

        if (id1 == -1 && id2 == -1)
            return 0;
        else if (id1 == -1)
            return id2 + 1; // insert remaining chars of word2
        else if (id2 == -1)
            return id1 + 1; // delete remaining chars of word1

        if (dp[id1][id2] != -1)
            return dp[id1][id2];

        if (word1[id1] == word2[id2])
        {
            return dp[id1][id2] =
                       recOpCount(id1 - 1, id2 - 1, word1, word2, dp);
        }
        else
        {
            int op1 = 1 + recOpCount(id1, id2 - 1, word1, word2, dp);     // insert
            int op2 = 1 + recOpCount(id1 - 1, id2, word1, word2, dp);     // delete
            int op3 = 1 + recOpCount(id1 - 1, id2 - 1, word1, word2, dp); // replace

            return dp[id1][id2] = min({op1, op2, op3});
        }
    }

    int minDistance(string word1, string word2)
    {
        int n1 = word1.size();
        int n2 = word2.size();
        vector<vector<int>> dp(n1, vector<int>(n2, -1));
        return recOpCount(n1 - 1, n2 - 1, word1, word2, dp);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
