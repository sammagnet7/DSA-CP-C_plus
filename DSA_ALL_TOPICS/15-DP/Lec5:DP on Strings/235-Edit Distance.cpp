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

1. Title: Edit Distance

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

//-------------------------------------------------------------------------------
// 1. Title: Edit Distance
//-------------------------------------------------------------------------------

class Solution
{
public:
    // ---------------------------------------------
    // Approach 1 [3D dp: TLE]
    // ---------------------------------------------
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

    // ---------------------------------
    // Approach 2 [Optimal] [Iterative]
    // ---------------------------------

    /**
     * @brief Computes the minimum number of operations to convert word1 to word2.
     *
     * * --- THE LCS BACKTRACKING PITFALL ---
     * [Where it works]: Finding the Longest Common Subsequence (LCS) and backtracking
     * works perfectly for problems that ONLY allow Insertions and Deletions (e.g.,
     * LeetCode 583: Delete Operation for Two Strings (DP 230.0)). In those cases, the minimum
     * edits are strictly derived from the formula: len(word1) + len(word2) - 2 * LCS.
     *
     * * [Why it fails here]: The moment the "Replace" operation is introduced, the
     * *distribution* of the un-matched characters (the gaps) matters. A single Replace
     * operation fixes one character from BOTH strings simultaneously. Because there can
     * be multiple valid LCS paths, a standard LCS backtracker will blindly pick the
     * first one it finds. This might force alignments that create terrible "gaps",
     * requiring more edits than an alternative LCS path would have needed.
     *
     * * --- THE CORRECT IDEA (Current Approach) ---
     * Instead of relying on a rigid LCS anchor, we use Dynamic Programming to evaluate
     * the cost of all 3 operations simultaneously at every single prefix combination.
     * * We define dp[i][j] as the minimum operations to convert the prefix word1[0...i-1]
     * to the prefix word2[0...j-1].
     * * If the current characters mismatch, we simulate all 3 allowed operations by
     * looking at previously computed states, and take the minimum:
     * 1. Insert:  We virtually inserted word2[j-1]. Cost = 1 + dp[i][j-1] (Left cell)
     * 2. Delete:  We virtually deleted word1[i-1]. Cost = 1 + dp[i-1][j] (Top cell)
     * 3. Replace: We virtually swapped them. Cost = 1 + dp[i-1][j-1] (Diagonal cell)
     *
     * * --- COMPLEXITY ---
     * Time Complexity:  O(N * M), where N and M are the lengths of the two strings.
     * We compute every cell in the 2D grid exactly once.
     * Space Complexity: O(N * M) to store the 2D DP matrix.
     */
    int minDistance(string word1, string word2)
    {

        int n = word1.length();
        int m = word2.length();

        // dp[i][j] will store the minimum edit distance between the
        // first 'i' characters of word1 and the first 'j' characters of word2.
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // --- BASE CASES ---

        // If word2 is empty (j = 0), the only way to match it is to
        // DELETE all 'i' characters from word1.
        for (int i = 0; i <= n; ++i)
        {
            dp[i][0] = i;
        }

        // If word1 is empty (i = 0), the only way to match word2 is to
        // INSERT all 'j' characters of word2 into word1.
        for (int j = 0; j <= m; ++j)
        {
            dp[0][j] = j;
        }

        // --- DP TRANSITIONS ---

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {

                // CASE A: Characters Match
                // No new operation is needed. The edit distance is exactly the same
                // as it was for the prefixes before these two characters.
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                // CASE B: Characters Do NOT Match
                // We must perform exactly 1 operation. We look at the 3 possible
                // moves, find the one that previously cost the least, and add 1.
                else
                {
                    int doInsert = dp[i][j - 1];      // Cost if we inserted word2's character
                    int doDelete = dp[i - 1][j];      // Cost if we deleted word1's character
                    int doReplace = dp[i - 1][j - 1]; // Cost if we replaced word1's char with word2's

                    // Take the best (minimum) of the 3 simulated choices, plus 1 for the operation
                    dp[i][j] = 1 + min({doInsert, doDelete, doReplace});
                }
            }
        }

        // The final cell contains the minimum operations for the full lengths of both strings
        return dp[n][m];
    }

    // ---------------------------------
    // Approach 3 [Optimal] [Recursive]
    // ---------------------------------
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
};

//-------------------------------------------------------------------------------
// 2. Title:
//-------------------------------------------------------------------------------

int main()
{
    return 0;
}
