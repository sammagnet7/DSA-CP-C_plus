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

1. Title:  Fractional Knapsack

Links:
https://takeuforward.org/data-structure/fractional-knapsack-problem-greedy-approach/
https://www.naukri.com/code360/problems/fractional-knapsack_975286?leftPanelTabValue=PROBLEM

Problem statement:
You have been given weights and values of ‘N’ items. You are also given a knapsack of size ‘W’.
Your task is to put the items in the knapsack such that the total value of items in the knapsack is maximum.

Note:
You are allowed to break the items.

Example:
If 'N = 4' and 'W = 10'. The weights and values of items are weights = [6, 1, 5, 3] and values = [3, 6, 1, 4].
Then the best way to fill the knapsack is to choose items with weight 6, 1 and  3. The total value of knapsack = 3 + 6 + 4 = 13.00
1
6 200
50 40 90 120 10 200
40 50 25 100 30 45

Sample output 1:
204.00
Explanation of Sample output 1:
The most optimal way to fill the knapsack is to choose full items with weight 10 and value 30, weight 40 and value 50, weight 120 and value 100. Then take weight 30 from the item with weight 50 and value 40.
The total value =  30 + 50 + 100 + (30/50)*(40) = 204.00

Sample Input 2:
1
5 100
20 24 36 40 42
12 35 41 25 32
Sample output 2:
106.48


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
  // 1. Title:  Fractional Knapsack
  //-------------------------------------------------------------------------------

  /**
   * Function: maximumValue
   * Purpose: Solves the fractional knapsack problem using a greedy approach
   *
   * Approach:
   * 1. Calculate value per unit weight for each item.
   * 2. Sort items by this ratio in descending order.
   * 3. Take whole items until the capacity is full.
   * 4. If partial item can be taken, take the fractional part.
   *
   * Time Complexity: O(N log N) for sorting
   * Space Complexity: O(N) for storing value per weight info
   */

  double maximumValue(vector<pair<int, int>> &items, int n, int w)
  {
    // Vector to store {value/weight, weight, value}
    vector<pair<double, pair<int, int>>> store;

    for (auto e : items)
    {
      double frac = (double)e.second / e.first; // value per unit weight
      store.push_back({frac, {e.first, e.second}});
    }

    // Sort by value per weight in descending order
    sort(store.begin(), store.end(), greater<>());

    // sort(store.begin(), store.end(), [](const pair<double, pair<int,int>>& a, const pair<double, pair<int,int>>& b){
    //     return a.first > b.first;
    // });

    double totalValue = 0.0;
    int i = 0;

    // Greedily take items until knapsack is full
    while (w > 0 && i < n)
    {
      double e_frac = store[i].first;
      int e_wt = store[i].second.first;
      int e_val = store[i].second.second;

      if (e_wt <= w)
      {
        // Take full item
        w -= e_wt;
        totalValue += e_val;
      }
      else
      {
        // Take fractional part
        totalValue += (e_frac * w);
        w = 0;
      }

      i++;
    }

    return totalValue;
  }
};

int main()
{
  return 0;
}
