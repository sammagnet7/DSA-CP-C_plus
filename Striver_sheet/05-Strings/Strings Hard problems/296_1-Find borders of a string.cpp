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
    abcababcab Output:
    2 5

    Sample Input 0
    aaaaaaaaaa
    Sample Output 0
    1 2 3 4 5 6 7 8 9

    Sample Input 1
    ababababab
    Sample Output 1
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

2. Title:


Links:


Problem statement:





INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Finding Borders (Using LPS array of KMP algo)
//-------------------------------------------------------------------------------
//

/*
  buildLPS(LPS, pat)
  ------------------
  Purpose / intuition:
    - Build the prefix-function (also called LPS = "Longest Proper Prefix
      which is also Suffix") for the string `pat`.
    - LPS[i] will store the length of the longest proper prefix of pat[0..i]
      that is also a suffix of pat[0..i].
    - We compute LPS in linear time by reusing previously computed values:
        * `len` holds the length of the current candidate border (the longest
          prefix-suffix for the prefix ending at index i-1).
        * `i` is the index we are computing LPS for.
      When pat[i] matches pat[len] we can extend the current border by one.
      On mismatch we fall back to a shorter border using LPS[len-1] and retry.
    - Key invariant:
        Before processing index i, `len` is the length of the longest border
        for pat[0..i-1]. Using that, we either extend it (on match) or reduce it
        (on mismatch) — but we only move i forward when we have determined LPS[i].
    - This avoids re-comparing characters from scratch and gives O(n) time.

  Inputs:
    - LPS : vector<int> of size at least pat.size(); will be filled in-place.
    - pat : the pattern / string for which we compute the prefix-function.

  Complexity:
    - Time: O(n) where n = pat.size().
    - Space: O(1) extra (besides LPS which is O(n)).
*/
void buildLPS(vector<int> &LPS, const string &pat)
{
    int n = (int)pat.size();
    if (n == 0)
        return; // nothing to do for empty string

    // Base case: single character has no proper prefix equal to suffix.
    LPS[0] = 0;

    int len = 0; // length of the current longest border for prefix ending before i
    int i = 1;   // we compute LPS[i] for i = 1..n-1

    while (i < n)
    {
        if (pat[i] == pat[len])
        {
            /*
              Characters match: we can extend the current border by 1.
              So the longest prefix-suffix for pat[0..i] is len+1.
              Move both pointers forward: i and len.
            */
            len++;
            LPS[i] = len;
            i++;
        }
        else
        {
            /*
              Characters do not match:
                - If len != 0, we have a non-empty candidate border. We try
                  a shorter border that might match: set len = LPS[len-1].
                  We do NOT increment i here because we want to attempt to
                  extend this shorter border at the same i.
                - If len == 0, there is no border to fall back to; then LPS[i]
                  is 0 and we can advance i.
              This fallback step is the core trick that avoids repeated work.
            */
            if (len != 0)
            {
                len = LPS[len - 1]; // fallback to next smaller border
                // note: no i++ here
            }
            else
            {
                // no border possible, record 0 and advance
                LPS[i] = 0;
                i++;
            }
        }
    }
}

/*
  findBorders(s)
  --------------
  Purpose / intuition:
    - Return a vector<int> containing all border lengths of the input string s,
      i.e., all L such that 0 < L < n and s[0..L-1] == s[n-L..n-1].
    - The longest proper border of the whole string is LPS[n-1].
    - Any border of that border is also a border of the full string; therefore
      iterating k = LPS[n-1], k = LPS[k-1], ... yields all borders in descending order.
    - We reverse the collected list to return borders in increasing order as requested.

  Steps:
    1) Edge-case: empty string -> no borders (return empty vector).
    2) Build LPS for the full string (O(n)).
    3) Walk the chain starting from LPS[n-1], repeatedly replacing k with LPS[k-1],
       collecting each k until 0.
    4) Reverse collected values to get them in increasing order.

  Complexity:
    - Time: O(n) building LPS + O(b) walking chain, overall O(n) where b is number of borders.
    - Space: O(n) for LPS and O(b) for returned borders.
*/
vector<int> findBorders(const string &s)
{
    int n = (int)s.size();
    if (n == 0)
        return {}; // no borders in empty string

    // Step 1: compute LPS array for the whole string
    vector<int> LPS(n, 0);
    buildLPS(LPS, s);

    // Start at the longest border of the whole string
     // Step 2: Collect all borders using the LPS chain
    /*
      Intuition:
        - The last value LPS[n-1] gives the length of the longest border
          of the full string (longest prefix == suffix).
        - That border itself may contain a smaller border,
          found by LPS[LPS[n-1]-1].
        - We keep walking this chain until 0.
    */
    vector<int> borders;
    int k = LPS[n - 1]; // length of longest proper border
    while (k > 0)
    {
        // k is a valid border length: prefix[0..k-1] == suffix[n-k..n-1]
        borders.push_back(k);
        // move to the next smaller border of that prefix
        k = LPS[k - 1];
    }

    // Step 3: borders collected in descending order (largest to smallest).
    // Reverse to return in increasing order as required by the problem statement.
    reverse(borders.begin(), borders.end());
    return borders;
}

int main()
{
    /*
      main:
        - Read input string
        - Call findBorders() to compute borders
        - Print them in a single line separated by spaces
    */
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    if (!(cin >> str))
        return 0; // read input; exit if nothing to read

    // Delegate the work to findBorders (keeps main concise and testable)
    vector<int> ans = findBorders(str);

    // Print results in one line; prints a blank line if no borders exist
    for (size_t i = 0; i < ans.size(); ++i)
    {
        if (i)
            cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
