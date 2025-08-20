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

1. Title: Evaluate Boolean Expression to True | Partition DP: DP 52

Links:
https://takeuforward.org/data-structure/evaluate-boolean-expression-to-true-partition-dp-dp-52/
https://www.youtube.com/watch?v=MM7fXopgyjw
https://www.naukri.com/code360/problems/problem-name-boolean-evaluation_1214650?leftPanelTabValue=PROBLEM


Problem statement:
You are given an expression 'exp' in the form of a string where operands will be : (TRUE or FALSE), and operators will be : (AND, OR or XOR).
Now you have to find the number of ways we can parenthesize the expression such that it will evaluate to TRUE.
As the answer can be very large, return the output modulo 1000000007.

Note :
‘T’ will represent the operand TRUE.
‘F’ will represent the operand FALSE.
‘|’ will represent the operator OR.
‘&’ will represent the operator AND.
‘^’ will represent the operator XOR.

Example :
    Input: 'exp’ = "T|T & F".
    Output: 1
    Explanation:
    There are total 2  ways to parenthesize this expression:
        (i) (T | T) & (F) = F
        (ii) (T) | (T & F) = T
    Out of 2 ways, one will result in True, so we will return 1.


    Sample Input 1 :
    T^T^F
    Sample Output 1 :
    0
    Explanation For Sample Input 1:
    There are total 2  ways to parenthesize this expression:
    (i) (T^T)^(F) = F
    (ii) (T)^(T^F) = F
    Both ways will result in False, so we will return 0.

    Sample Input 2 :
    F|T^F
    Sample Output 2 :
    2
    Explanation For Sample Input 2:
    For the first test case:
    There are total 2  ways to parenthesize this expression:
    (i) (F|T)^(F) = T
    (ii) (F)|(T^F) = T
    Both ways will result in True, so we will return 2.

Expected time complexity
The expected time complexity is O(n ^ 3), where 'n' denotes the length of 'exp'.

Constraints:
    3 <= |‘exp’| <= 200
    Where |'exp'| denotes the length of 'exp'.
    Time Limit: 1 sec



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
    // 1. Title: Evaluate Boolean Expression to True | Partition DP: DP 52
    //-------------------------------------------------------------------------------

    int modulo = 1000000007;

    /*
        Function: noOfPossibleWays
        --------------------------------
        Calculates the number of ways to evaluate a given operator ('&', '|', '^')
        to a desired boolean value (true/false), based on the counts of ways
        the left and right sub-expressions can evaluate to True or False.

        Parameters:
            leftT  - Number of ways left sub-expression evaluates to True
            leftF  - Number of ways left sub-expression evaluates to False
            rightT - Number of ways right sub-expression evaluates to True
            rightF - Number of ways right sub-expression evaluates to False
            op     - The operator (&, |, ^)
            isTrue - Boolean flag: are we computing ways for True (1) or False (0)?

        Approach:
            - For each operator, apply boolean logic:
                '&': True ? both true, False ? any other combo
                '|': True ? any one true, False ? both false
                '^': True ? different values, False ? same values
            - Apply modulo after every addition and multiplication to prevent overflow.

        Time: O(1) for each call
        Space: O(1)
    */
    long long noOfPossibleWays(int leftT, int leftF, int rightT, int rightF, char op, bool isTrue)
    {
        if (op == '&')
        {
            if (isTrue)
                return (1LL * leftT * rightT) % modulo;
            else
                return ((1LL * leftF * rightF) % modulo + (1LL * leftT * rightF) % modulo + (1LL * leftF * rightT) % modulo) % modulo;
        }
        else if (op == '|')
        {
            if (isTrue)
                return ((1LL * leftT * rightT) % modulo + (1LL * leftT * rightF) % modulo + (1LL * leftF * rightT) % modulo) % modulo;
            else
                return (1LL * leftF * rightF) % modulo;
        }
        else if (op == '^')
        {
            if (isTrue)
                return ((1LL * leftT * rightF) % modulo + (1LL * leftF * rightT) % modulo) % modulo;
            else
                return ((1LL * leftT * rightT) % modulo + (1LL * leftF * rightF) % modulo) % modulo;
        }
        return 0;
    }

    /*
        Function: recOpCoun
        --------------------------------
        Recursively calculates the number of ways to parenthesize the expression
        such that it evaluates to True or False.

        Parameters:
            i, j   - Start and end indices of the current substring
            isTrue - Boolean: true if we want the expression to evaluate to True, false otherwise
            exp    - The input expression (string of T/F and operators)
            dp     - 3D DP table for memoization: dp[i][j][isTrue]

        Approach:
            - Base cases:
                If i > j ? no valid expression ? 0
                If i == j ? check if exp[i] matches the desired truth value
            - For each operator between i and j:
                Split into left and right sub-expressions
                Recursively calculate all combinations for left and right
                Aggregate results using noOfPossibleWays()
            - Store in dp to avoid recomputation

        Time Complexity: O(n^3)
            - n = length of expression
            - O(n^2) subproblems (pairs of i, j), and for each, O(n) possible partitions
        Space Complexity: O(n^2)
            - DP table of size n x n x 2
    */
    long long recOpCoun(int i, int j, int isTrue, string &exp, vector<vector<vector<long long>>> &dp)
    {
        if (i > j)
            return 0;
        if (i == j)
        {
            if (isTrue)
                return exp[i] == 'T';
            else
                return exp[i] == 'F';
        }

        if (dp[i][j][isTrue] != -1)
            return dp[i][j][isTrue];

        long long totalWays = 0;

        // Iterate over operators (which are always at odd positions)
        for (int op = i + 1; op <= j - 1; op += 2)
        {
            // Recursively compute counts for left and right
            long long lTcount = recOpCoun(i, op - 1, true, exp, dp) % modulo;
            long long lFcount = recOpCoun(i, op - 1, false, exp, dp) % modulo;
            long long rTcount = recOpCoun(op + 1, j, true, exp, dp) % modulo;
            long long rFcount = recOpCoun(op + 1, j, false, exp, dp) % modulo;

            // Combine results using operator
            long long ways = noOfPossibleWays(lTcount, lFcount, rTcount, rFcount, exp[op], isTrue);

            // Add to total and apply modulo
            totalWays = (totalWays + ways) % modulo;
        }

        return dp[i][j][isTrue] = totalWays;
    }

    /*
        Function: evaluateExp
        --------------------------------
        Wrapper function to initialize DP and call recursive solver.

        Approach:
            - Create a 3D DP table initialized with -1
            - Call recOpCoun for the entire expression with isTrue = true
            - Return result modulo 1e9+7

        Time: O(n^3)
        Space: O(n^2)
    */
    int evaluateExp(string &exp)
    {
        int n = exp.size();
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));
        return recOpCoun(0, n - 1, true, exp, dp);
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};

int main()
{
    return 0;
}
