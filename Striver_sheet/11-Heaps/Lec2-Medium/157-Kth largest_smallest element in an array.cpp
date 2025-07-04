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

1. Title: Kth largest element in an array

Links:
https://takeuforward.org/data-structure/kth-largest-smallest-element-in-an-array/
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/k-th-largest-element-in-an-array
https://leetcode.com/problems/kth-largest-element-in-an-array/description/

Problem statement:
Given an integer array nums and an integer k, return the kth largest element in the array.
Note:
  Note that it is the kth largest element in the sorted order, not the kth distinct element.
  Can you solve it without sorting?

Examples:
  Example 1:
  Input: nums = [3,2,1,5,6,4], k = 2
  Output: 5

  Example 2:
  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
  Output: 4

Constraints:
  1 <= k <= nums.length <= 105
  -104 <= nums[i] <= 104


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Kth largest element in an array
  //-------------------------------------------------------------------------------

  // Approach1:
  //
  // // Sub-optimal approach: using sorting
  // // Time: O(N+K)
  // // Space: O(N)
  // int findKthLargest(vector<int> &nums, int k)
  // {

  //   int N = nums.size();

  //   sort(nums.begin(), nums.end());

  //   return nums[N - k];
  // }

  // Approach2:
  //
  // // Sub-optimal approach: using PQ as MAX heap
  // // Time: O(N+K)
  // // Space: O(N)
  // int findKthLargest(vector<int> &nums, int k)
  // {

  //   priority_queue<int> pq; // O(N)

  //   for (int i = 0; i < nums.size(); i++)
  //   { // O(N)
  //     pq.push(nums[i]);
  //   }

  //   for (int i = 0; i < k - 1; i++)
  //   { // O(k)
  //     pq.pop();
  //   }

  //   return pq.top();
  // }

  // Approach3:
  //
  // // Better approach: Using PQ as MIN heap
  // //
  // // Time: O(K Log K + (N-K)*LogK) ~ O(N Log K)
  // // Space: O(K)
  // int findKthLargest(vector<int> &nums, int k)
  // {

  //   priority_queue<int, vector<int>, greater<int>> pq_min;
  //   int N = nums.size();

  //   for (int i = 0; i < k; i++)
  //   {                       // O(K)
  //     pq_min.push(nums[i]); // O(Log K)
  //   }

  //   for (int i = k; i < N; i++)
  //   { // O(N-K)

  //     if (nums[i] > pq_min.top())
  //     {
  //       pq_min.pop(); // O(Log K)
  //       pq_min.push(nums[i]);
  //     }
  //   }

  //   return pq_min.top();
  // }

  // Approach4:
  //
  // Optimal approach:
  //
  // Time:
  // Space:
  int findKthLargest(vector<int> &nums, int k)
  {
  }
};

int main()
{
  return 0;
}
