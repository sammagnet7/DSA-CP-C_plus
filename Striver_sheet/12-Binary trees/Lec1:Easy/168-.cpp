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

1. Title: Top K Frequent Elements

Links:
https://takeuforward.org/plus/dsa/problems/top-k-frequent-elements?tab=editorial
https://leetcode.com/problems/top-k-frequent-elements/description/


Problem statement:
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.



Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]


Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.


Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Top K Frequent Elements
  //-------------------------------------------------------------------------------

  // Optimal approach: Using map and heap
  // Time: O(N)
  // Space: O(#uniqs+K)
  vector<int> topKFrequent(vector<int> &nums, int k)
  {

    unordered_map<int, int> mp;                                                         // O(#uniqs): <number, freq >
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // O(k) min heap of <freq,num>

    for (int i : nums)
    { // O(N)
      mp[i]++;
    }

    for (auto it = mp.begin(); it != mp.end(); it++)
    { // O(#uniqs)

      int curNum = it->first;
      int curFrq = it->second;

      if (pq.size() == k)
      {

        if (pq.top().first < curFrq)
        {
          pq.pop();
        }
        else
        {
          continue;
        }
      }

      pq.push({curFrq, curNum}); // O(Log (#uniqs))
    }

    vector<int> ans;

    while (!pq.empty())
    { // O(k)
      ans.push_back(pq.top().second);
      pq.pop();
    }

    return ans;
  }
};

int main()
{
  return 0;
}
