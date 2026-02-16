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
#include <cstring> // For memset

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

  //-------------------------------------------------------------------------------
  // Approach: 1 [TLE] [Without DP]
  //-------------------------------------------------------------------------------
  /*
   * Function: rec
   * -------------
   * Recursively checks if the string 's' is valid starting from index 'idx'.
   * Uses a standard backtracking approach to explore all possibilities for '*'.
   *
   * Parameters:
   * idx - Current index in the string 's' we are processing.
   * st  - Reference to the stack maintaining open parentheses '('.
   * s   - The input string containing '(', ')', and '*'.
   * N   - Total length of the string.
   *
   * Complexity Analysis:
   * Time Complexity: O(3^N)
   * - In the worst case (e.g., a string of all '*'), every character branches
   * into 3 recursive calls. This exponential growth makes it very slow
   * for large inputs.
   *
   * Space Complexity: O(N)
   * - O(N) for the recursion stack depth.
   * - O(N) for the 'st' stack storing open brackets.
   */
  bool rec(int idx, stack<char> &st, string &s, int N)
  {

    // Base Case: If we have processed the entire string
    if (idx == N)
    {
      // The string is valid only if the stack is completely empty
      // (all open brackets have been matched)
      if (st.empty())
      {
        return true;
      }
      return false;
    }

    bool result = false;

    // Case 1: Current char is '('
    // We must push it onto the stack and move forward.
    if (s[idx] == '(')
    {
      st.push('(');                    // Action: Add to stack
      result = rec(idx + 1, st, s, N); // Recurse
      st.pop();                        // Backtrack: Remove it to restore state for caller
    }
    // Case 2: Current char is ')'
    // We must match it with an open bracket from the stack.
    else if (s[idx] == ')')
    {
      if (!st.empty() && st.top() == '(')
      {
        st.pop();                        // Action: Consume an open bracket
        result = rec(idx + 1, st, s, N); // Recurse
        st.push('(');                    // Backtrack: Put the '(' back so previous calls aren't affected
      }
      else
      {
        // Found closing bracket but stack is empty -> Invalid path
        return false;
      }
    }
    // Case 3: Current char is '*'
    // This is the branching point. We try all 3 possibilities.
    else if (s[idx] == '*')
    {

      // Option A: Treat '*' as Empty String ""
      // No stack change needed, just move index forward.
      result = rec(idx + 1, st, s, N);
      if (result)
      {
        return true; // Pruning: If valid, stop exploring other options
      }

      // Option B: Treat '*' as '('
      st.push('(');                    // Action: Add '('
      result = rec(idx + 1, st, s, N); // Recurse
      st.pop();                        // Backtrack: Undo addition
      if (result)
      {
        return true;
      }

      // Option C: Treat '*' as ')'
      // Only valid if we have something to pop
      if (!st.empty() && st.top() == '(')
      {
        st.pop();                        // Action: Match with existing '('
        result = rec(idx + 1, st, s, N); // Recurse
        st.push('(');                    // Backtrack: Restore the popped '('
        if (result)
        {
          return true;
        }
      }
    }

    return result;
  }

  bool checkValidString(string s)
  {
    int N = s.size();
    stack<char> st;
    return rec(0, st, s, N);
  }

  /*
    Why can't we implement DP with this stack approach?
    You cannot simply add a DP table to this specific code because you cannot use a std::stack object as an array index.

    Solution:
      The stack only contains the character (. Therefore, the "Stack Object" can be simplified to just an Integer (the count of items in the stack) -> `int openCount`.

  */

  //-------------------------------------------------------------------------------
  // Approach: 2 [OPTIMAL] [Using DP]
  //-------------------------------------------------------------------------------

  // DP Table for Memoization
  // Dimensions: [index][open_bracket_count]
  // Values: -1 (Unvisited), 0 (False), 1 (True)
  // Note: Size 101 assumes string length constraint N <= 100
  int memo[101][101];

  /*
   * Function: solve
   * ---------------
   * Recursively checks validity using DFS + Memoization.
   * * Parameters:
   * i         - Current index in the string
   * openCount - The number of currently open '(' brackets (acts as a virtual stack)
   * s         - The input string
   *
   * Complexity Analysis:
   * Time Complexity: O(N^2)
   * - There are N indices and at most N possible open counts.
   * - Total unique states = N * N. Each state is computed only once.
   *
   * Space Complexity: O(N^2)
   * - O(N^2) for the memoization table.
   * - O(N) for recursion stack depth.
   */
  bool solve(int i, int openCount, string &s)
  {

    // Base Case: Reached end of string
    if (i == s.size())
    {
      // Valid only if all open brackets have been closed (count is 0)
      return openCount == 0;
    }

    // Pruning: Invalid State
    // We cannot have negative open brackets (e.g., trying to close ')' when empty)
    if (openCount < 0)
      return false;

    // Memoization Lookup
    // If we have already solved this state (index + specific count), return the stored result.
    // This prevents re-calculating the same path, fixing the TLE issue.
    if (memo[i][openCount] != -1)
    {
      return memo[i][openCount];
    }

    bool res = false;

    // Case 1: '(' -> Increment count (Simulates push to stack)
    if (s[i] == '(')
    {
      res = solve(i + 1, openCount + 1, s);
    }
    // Case 2: ')' -> Decrement count (Simulates pop from stack)
    else if (s[i] == ')')
    {
      // Check bounds before decrementing to avoid negative indexing or invalid logic
      if (openCount > 0)
        res = solve(i + 1, openCount - 1, s);
    }
    // Case 3: '*' -> Branch into 3 possibilities
    else if (s[i] == '*')
    {
      // Option A: Treat as empty string "" (Skip, count stays same)
      bool emptyChoice = solve(i + 1, openCount, s);

      // Option B: Treat as '(' (Increment count)
      bool openChoice = solve(i + 1, openCount + 1, s);

      // Option C: Treat as ')' (Decrement count)
      bool closeChoice = false;
      if (openCount > 0)
      {
        closeChoice = solve(i + 1, openCount - 1, s);
      }

      // If ANY path leads to a valid solution, this state is valid.
      res = emptyChoice || openChoice || closeChoice;
    }

    // Store result in DP table and return
    return memo[i][openCount] = res;
  }

  bool checkValidString(string s)
  {
    // Initialize DP table with -1 (representing "not calculated yet")
    memset(memo, -1, sizeof(memo));

    return solve(0, 0, s);
  }

  //-------------------------------------------------------------------------------
  // Approach: 3 [OPTIMAL]  [2 Stacks][Greedy]
  //-------------------------------------------------------------------------------

  /*
   * Method: checkValidString
   * ------------------------
   * Validates a string containing '(', ')', and '*' using a Greedy Two-Stack approach.
   * * Strategy:
   * 1. Left-to-Right Scan: Handle all ')' immediately.
   * - Prioritize matching ')' with a previous '('.
   * - If no '(', use a '*' as a substitute.
   * 2. Cleanup Phase: Handle remaining '('.
   * - Match leftover '(' with remaining '*' that appear AFTER the '('.
   * * Complexity Analysis:
   * Time Complexity: O(N)
   * - We traverse the string once (O(N)).
   * - The cleanup while-loop runs at most N/2 times.
   * * Space Complexity: O(N)
   * - We use two stacks which, in the worst case (e.g., "((((*"),
   * store up to N indices.
   */
  bool checkValidString(string s)
  {

    // We store INDICES, not characters.
    // We need indices to ensure that when matching a '(' with a '*',
    // the '(' comes BEFORE the '*' (i.e., index_open < index_star).
    stack<int> openSt; // Indices of strictly open brackets '('
    stack<int> starSt; // Indices of flexible wildcards '*'

    // Pass 1: Handle all ')' characters
    for (int i = 0; i < s.size(); i++)
    {

      if (s[i] == '(')
      {
        openSt.push(i); // Save index for later matching
      }
      else if (s[i] == '*')
      {
        starSt.push(i); // Save index, might be used as '(', ')', or ""
      }
      else
      { // Current char is ')'

        // Priority 1: Match with a real '('
        // We prefer to use '(' because it has no other use.
        // We save '*' for later because it is more flexible.
        if (!openSt.empty())
        {
          openSt.pop();
        }
        // Priority 2: Match with a '*' (treating '*' as '(')
        else if (!starSt.empty())
        {
          starSt.pop();
        }
        // Failure: No '(' or '*' available to balance this ')'
        else
        {
          return false;
        }
      }
    }

    // Pass 2: Cleanup - Match remaining '(' with available '*'
    // At this point, we have processed all ')'.
    // The stacks only contain unmatched '(' and unmatched '*'.
    while (!openSt.empty() && !starSt.empty())
    {

      // CRITICAL LOGIC: Position matters.
      // A '*' can only close a '(' if the '*' appears AFTER the '('.
      // Case 1: "(*" -> open index < star index. Valid. '*' becomes ')'.
      // Case 2: "*(" -> open index > star index. Invalid. '*' cannot act as ')'.
      if (openSt.top() > starSt.top())
      {
        return false;
      }

      // Match found, remove both
      openSt.pop();
      starSt.pop();
    }

    // Final Check:
    // We don't care if starSt is not empty (remaining '*' become empty strings "").
    // We ONLY fail if we still have unmatched '(' left.
    return openSt.empty();
  }

  //-------------------------------------------------------------------------------
  // Approach: 4 [OPTIMAL] [Mathematical]
  //-------------------------------------------------------------------------------

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
