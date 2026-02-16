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

1. Title: Greedy algorithm to find minimum number of coins

Links:
https://takeuforward.org/data-structure/find-minimum-number-of-coins/
https://www.youtube.com/watch?v=mVg9CfJvayM
https://www.naukri.com/code360/problems/greedy-algorithm-for-ninja-and-the-coins_3191489?leftPanelTabValue=PROBLEM


Problem statement:
Ninja went to the toffee shop, and he purchased some toffies worth 'V' cents. Ninja has an unlimited supply of coins of 1, 2, 5, 10, 20, 50, 100, 500, and 1000 cents. Now Ninja wants to know the minimum number of coins he needs to pay to the shopkeeper.
Your task is to find the minimum number of coins Ninja needs to pay to the shopkeeper so as to pay 'V' cents to him.
Note: You have to solve this problem using the greedy approach.

Example:
  Input: 'V' = 60
  Output: 2
  Ninja need to pay two coins only 50 + 10 = 60

  Sample Input 1 :
  2
  70
  50
  Sample Output 1 :
  2
  1
  Explanation Of Sample Input 1 :
  For the first test case, Ninja need to pay two coins, only 50 + 20 = 70

  For the second test case, Ninja needs to pay only one coin of 50 cents.
  Sample Input 2 :
  2
  121
  100
  Sample Output 2 :
  3
  1


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
  // 1. Title: Greedy algorithm to find minimum number of coins
  //-------------------------------------------------------------------------------

  /*
   * Function: minimumCoins
   * ----------------------
   * Calculates the minimum number of coins/notes required to reach a specific
   * target value 'v' using Indian currency denominations.
   *
   * Strategy:
   * Uses a Greedy Algorithm. We sort denominations in descending order
   * (via a Max-Heap) and maximize the usage of the largest possible
   * denomination at every step.
   *
   * Complexity Analysis:
   * Time Complexity: O(K log K)
   * - Where K is the number of denominations (9 in this case).
   * - Initializing the priority_queue takes O(K).
   * - In the worst case, we iterate through all K coins. The heap pop
   * operation takes O(log K).
   * - Since K is fixed and small, this runs in effectively O(1) constant time.
   *
   * Space Complexity: O(K)
   * - We use O(K) auxiliary space to store the denominations in the
   * vector and the priority_queue.
   */
  int minimumCoins(int v)
  {
    // 1. Define the available currency denominations (Standard Indian Currency)
    // Note: This logic relies on the "canonical" property of this specific set
    // where a greedy approach always yields the optimal solution.
    std::vector<int> c = {1, 2, 5, 10, 20, 50, 100, 500, 1000};

    // 2. Create a Max-Heap (Priority Queue)
    // This organizes the coins so that the largest denomination is always at the top (.top()).
    // Logic: We want to process the largest coins first.
    std::priority_queue<int> coins(c.begin(), c.end());

    int ans = 0; // Initialize the counter for the total number of coins/notes

    // 3. Process until the target value 'v' is reduced to 0
    while (v && !coins.empty())
    {

      // Check if the current largest coin fits into the remaining value
      if (coins.top() <= v)
      {

        // Calculate how many notes of this specific denomination fit
        // Example: if v = 45 and top = 20, t = 2 (20 * 2 = 40)
        int t = v / coins.top();

        // Reduce the remaining value by the total value of these notes
        // Example: v becomes 45 - 40 = 5
        v -= (t * coins.top());

        // Add the count of these notes to the final answer
        ans += t;
      }

      // 4. Move to the next largest denomination
      // Regardless of whether we used the coin or not, we remove the current
      // top to check the next smaller denomination in the next iteration.
      coins.pop();
    }

    return ans;
  }
};

int main()
{
  return 0;
}
