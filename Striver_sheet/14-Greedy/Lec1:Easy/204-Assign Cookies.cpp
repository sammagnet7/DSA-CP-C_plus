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

1. Title: Assign Cookies

Links:
https://takeuforward.org/Greedy/assign-cookies
https://takeuforward.org/plus/dsa/problems/assign-cookies?tab=editorial
https://leetcode.com/problems/assign-cookies/description/
https://leetcode.com/problems/maximum-matching-of-players-with-trainers/description/


Problem statement:
Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Examples:
  Example 1:
  Input: g = [1,2,3], s = [1,1]
  Output: 1
  Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
  And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
  You need to output 1.

  Example 2:
  Input: g = [1,2], s = [1,2,3]
  Output: 2
  Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
  You have 3 cookies and their sizes are big enough to gratify all of the children,
  You need to output 2.


Constraints:
  1 <= g.length <= 3 * 104
  0 <= s.length <= 3 * 104
  1 <= g[i], s[j] <= 231 - 1


Note: This question is the same as 2410: Maximum Matching of Players With Trainers.


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
  // 1. Title: Assign Cookies
  //-------------------------------------------------------------------------------

  /**
   * Approach:
   * The goal is to assign cookies to children such that the number of content (satisfied) children is maximized.
   * Each child has a greed factor (`g[i]`), and each cookie has a size (`s[j]`).
   * A child `i` will be content if there exists a cookie `j` such that `s[j] >= g[i]`.
   *
   * Strategy:
   * - Sort both the greed array and the cookie sizes.
   * - Use two pointers to iterate through both arrays and greedily assign the smallest suitable cookie to each child.
   * - If a cookie satisfies the current child, move both pointers.
   * - Otherwise, try the next larger cookie (move only cookie pointer).
   *
   * Time Complexity: O(N log N + M log M) where N = g.size(), M = s.size() (due to sorting)
   * Space Complexity: O(1) extra space (in-place sorting and constant space used)
   */

  int findContentChildren(vector<int> &g, vector<int> &s)
  {
    // Sort greed factors and cookie sizes to apply greedy approach
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int gS = g.size(); // Number of children
    int sS = s.size(); // Number of cookies

    int i = 0; // Pointer for children
    int j = 0; // Pointer for cookies

    // Try to satisfy each child with the smallest possible cookie
    while (i < gS && j < sS)
    {
      if (g[i] <= s[j])
      {
        // Cookie `s[j]` satisfies child `g[i]`
        i++; // Move to next child
        j++; // Move to next cookie
      }
      else
      {
        // Cookie too small, try next larger cookie
        j++;
      }
    }

    // `i` represents the number of satisfied children
    return i;
  }
};

int main()
{
  return 0;
}
