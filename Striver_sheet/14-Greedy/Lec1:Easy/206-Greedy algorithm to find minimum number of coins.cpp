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
  int minimumCoins(int amount)
  {
    // Write your code here.

    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 500, 1000};

    int i = coins.size() - 1;
    int count = 0;

    while (amount > 0 && i >= 0)
    {
      if (coins[i] > amount)
      {
        i--;
        continue;
      }
      if (amount % coins[i] == 0)
      {
        int q = amount / coins[i];
        amount = amount - (q * coins[i]);
        count += q;
      }
      else
      {
        count++;
        amount -= coins[i];
      }
    }

    if (amount == 0)
      return count;
    else
      return -1;
  }
};

int main()
{
  return 0;
}
