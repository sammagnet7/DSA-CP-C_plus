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

1. Title: Valid Paranthesis Checker

Links:
https://takeuforward.org/plus/dsa/problems/valid-paranthesis-checker?tab=editorial
https://leetcode.com/problems/valid-parenthesis-string/description/


Problem statement:
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:
Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

Examples:
  Example 1:
  Input: s = "()"
  Output: true

  Example 2:
  Input: s = "(*)"
  Output: true

  Example 3:
  Input: s = "(*))"
  Output: true


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
  // 1. Title: Valid Paranthesis Checker
  //-------------------------------------------------------------------------------
  // Note: The brute force approach: For each asterik try 3 possible solutions: '(' or ')' or '*' recursively.
  // Time: O(3^N)

  /**
   * Optimal approach:
   *
   * Function: checkValidString
   * Purpose: To check if a string containing '(', ')', and '*' is valid.
   *
   * A string is valid if:
   * - Every '(' has a matching ')'.
   * - '*' can be treated as '(', ')' or an empty string.
   *
   * Approach (Greedy with Range Tracking):
   * - Use two counters:
   *      openCmin → minimum number of unmatched '('
   *      openCmax → maximum number of unmatched '('
   * - Iterate the string and update openCmin and openCmax based on current character:
   *      '(' → both min and max increase
   *      ')' → both min and max decrease
   *      '*' → min decreases (treat as ')'), max increases (treat as '(')
   * - If at any point openCmax < 0 → too many ')' → invalid
   * - After full traversal, if openCmin == 0 → valid
   *
   * Time Complexity: O(N) — one pass over the string
   * Space Complexity: O(1) — constant space
   */

  bool checkValidString(string s)
  {
    int openCmin = 0; // Minimum number of open brackets
    int openCmax = 0; // Maximum number of open brackets

    for (char c : s)
    {
      if (c == '(')
      {
        openCmin++;
        openCmax++;
      }
      else if (c == ')')
      {
        openCmin--;
        openCmax--;
      }
      else if (c == '*')
      {
        openCmin--; // Treat * as ')'
        openCmax++; // Treat * as '('
      }

      // If max open count goes negative, too many ')'
      if (openCmax < 0)
        return false;

      // Clamp min open to 0 (can't go negative)
      openCmin = max(0, openCmin);
    }

    // If min open is 0 → all opened are closed
    return openCmin == 0;
  }
};

int main()
{
  return 0;
}
