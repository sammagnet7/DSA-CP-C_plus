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

1. Title: Finding Borders

Links:
https://www.hackerrank.com/contests/mock-test-2-1758395674/challenges/finding-borders


Problem statement:
A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.

Example
    Input:
    abcababcab
    Output:
    2 5

    Sample Input
    aaaaaaaaaa
    Sample Output
    1 2 3 4 5 6 7 8 9

    Sample Input
    ababababab
    Sample Output
    2 4 6 8

Input Format
The only input line has a string of length n consisting of characters a–z.

Constraints
1  n  106

Output Format
Print all border lengths of the string in increasing order.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Finding Borders (Using LPS array of KMP algo)
//-------------------------------------------------------------------------------

/**
 * @brief Finds all border lengths of a string in increasing order.
 * * A "border" is a prefix of the string that is also a suffix, excluding the
 * full string itself.
 * * * * * 🧠 INTUITION (The LPS Traceback):
 * The definition of a KMP LPS (Longest Prefix Suffix) array perfectly matches
 * the definition of a border.
 * 1. The longest border of the entire string is simply `LPS[m - 1]`.
 * 2. To find the next largest border, we treat our current border length as a
 * mismatch state and use the LPS array to safely fall back: `len = LPS[len - 1]`.
 * 3. We repeat this traceback until the length hits 0.
 * * * * * ⏱️ COMPLEXITY:
 * - Time Complexity: O(M) to build the LPS array + O(K) to trace back the borders
 * (where K is the number of borders). Reversing takes O(K). Overall Time: O(M).
 * - Space Complexity: O(M) auxiliary space to store the LPS array.
 * * @param pattern The input string to analyze.
 * @param ans A reference to a vector where the border lengths will be stored.
 */
void findBorders(string &pattern, vector<int> &ans)
{

  int m = pattern.length();

  // Edge case: Empty string has no borders
  if (m == 0)
  {
    return;
  }

  // =========================================================
  // PHASE 1: PRE-COMPUTE THE LPS ARRAY
  // =========================================================
  vector<int> LPS(m, 0);

  int len = 0; // Left Pointer: Tracks the length of the currently matched prefix
  int i = 1;   // Right Pointer: Scans the suffix of the string

  while (i < m)
  {

    // Match found: Expand the known prefix length
    if (pattern[len] == pattern[i])
    {
      ++len;
      LPS[i] = len;
      ++i;
    }
    else
    {
      // Mismatch: Slide the Left Pointer back to the previous longest prefix
      if (len != 0)
      {
        len = LPS[len - 1];
        // Note: 'i' is NOT incremented, so we re-evaluate pattern[i]
      }
      // Left Pointer is 0, no prefix match is possible. Advance 'i'.
      else
      {
        ++i;
      }
    }
  }

  // =========================================================
  // PHASE 2: THE BORDER TRACEBACK
  // =========================================================

  // Start with the length of the longest possible border of the full string
  len = LPS[m - 1];

  // Trace back through the LPS array to find all smaller overlapping borders
  while (len > 0)
  {

    // Record the exact length of the valid border
    ans.push_back(len);

    // Fall back to find the next longest valid border
    len = LPS[len - 1];
  }

  // The problem requires the output in increasing order.
  // Since our traceback goes from longest to shortest, we reverse the final result.
  reverse(ans.begin(), ans.end());
}

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  string pattern;

  cin >> pattern;

  vector<int> ans;

  findBorders(pattern, ans);

  for (int i : ans)
  {
    cout << i << " ";
  }

  return 0;
}
