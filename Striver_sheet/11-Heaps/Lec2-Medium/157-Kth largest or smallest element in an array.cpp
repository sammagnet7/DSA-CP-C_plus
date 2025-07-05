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

2. Title: Kth Smallest element in an array

Links:
https://takeuforward.org/data-structure/kth-largest-smallest-element-in-an-array/
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/k-th-largest-element-in-an-array
https://www.naukri.com/code360/problems/kth-smallest-element_893056?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array of integers 'ARR' of size 'N' and another integer 'K'.
Your task is to find and return 'K'th smallest value present in the array.

Note: All the elements in the array are distinct.

Example
If 'N' is 5 and 'K' is 3 and the array is 7, 2, 6, 1, 9
Sorting the array we get 1, 2, 6, 7, 9
Hence the 3rd smallest number is 6.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Kth largest element in an array
  //-------------------------------------------------------------------------------

  // Approach1:
  //
  // Sub-optimal approach: using sorting
  // Time: O(N Log N)
  // Space: O(1)
  // int findKthLargest(vector<int> &nums, int k)
  // {

  //   int N = nums.size();

  //   sort(nums.begin(), nums.end());

  //   return nums[N - k];
  // }

  // ----------------------------
  // Approach2:

  // Sub-optimal approach: using PQ as MAX heap
  // Time: O(N Log N + K log N)
  // Space: O(N)
  // int findKthLargest(vector<int> &nums, int k)
  // {

  //   priority_queue<int> pq; // O(N)

  //   for (int i = 0; i < nums.size(); i++)
  //   { // O(N)
  //     pq.push(nums[i]); // O(Log N)
  //   }

  //   for (int i = 0; i < k - 1; i++)
  //   { // O(k)
  //     pq.pop(); // O(Log N)
  //   }

  //   return pq.top();
  // }

  // ----------------------------
  // Approach3:
  //
  // Better approach: Using PQ as MIN heap
  //
  // Time: O(K Log K + (N-K)*LogK ) ~ O(N Log K)
  // Space: O(K)
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

  // ----------------------------
  // Approach4:
  //

  //
  // O(1)
  int getRandomIdx(int l, int r)
  {
    int len = r - l + 1;

    int randx = rand() % len;

    return (l + randx);
  }

  //
  // O(n)
  int partition(vector<int> &arr, int start, int end, int pivotIdx)
  {

    swap(arr[start], arr[pivotIdx]);

    pivotIdx = start;
    int pivot = arr[pivotIdx];

    int rightToPivotx = start + 1; // index representing just the next index to the sorted place of pivot

    for (int i = start + 1; i <= end; i++)
    { // O(N): traverse the whole array

      if (arr[i] < pivot)
      { // where ever element smaller than pivot is found, swap with the rightToPivotx and increment rightToPivotx so that rightToPivotx still points to the just next element of pivot's sorted place
        swap(arr[i], arr[rightToPivotx]);
        rightToPivotx++;
      }
    }

    swap(arr[pivotIdx], arr[rightToPivotx - 1]);

    return (rightToPivotx - 1);
  }

  //
  //
  // Optimal approach: Using Quickselect Algorithm
  //
  // Time: Avg(N) but O(N^2)
  // Space: O(1)
  int findKthLargest(vector<int> &nums, int k)
  {
    int N = nums.size();

    int l = 0;
    int r = N - 1;

    while (l <= r)
    { // O(N + N/2 + N/4 + N/8 + ...) ~~ O(N)
      // becasue each time partitions into half (tense to) of the prev array.
      // But in worst case if the random pivot always partitions the array in (N-1) and 1, then ~~ O(N^2)

      int randx = getRandomIdx(l, r);

      int pivotSortedIdx = partition(nums, l, r, randx); // O(n)

      if (pivotSortedIdx == (N - k))
        return nums[pivotSortedIdx];

      else if (pivotSortedIdx > (N - k))
      {
        r = pivotSortedIdx - 1;
      }
      else
      {
        l = pivotSortedIdx + 1;
      }
    }

    return -1;
  }

  //-------------------------------------------------------------------------------
  // 2. Title: Kth Smallest element in an array
  //-------------------------------------------------------------------------------

  // // Approach1:
  // //

  // // Sub-optimal approach: using sorting
  // // Time: O(N Log N)
  // // Space: O(1)
  // int kthSmallest(int n,int k,vector<int> &nums)
  // {

  //   int N = nums.size();

  //   sort(nums.begin(), nums.end(), greater<int>());

  //   return nums[N - k];
  // }

  // // ----------------------------
  // // Approach2:
  // //

  // // Sub-optimal approach: using PQ as MIN heap
  // // Time: O(N Log N + K log N)
  // // Space: O(N)
  // int kthSmallest(int n,int k,vector<int> &nums)
  // {

  //   priority_queue<int, vector<int>, greater<int>> pq; // O(N)

  //   for (int i = 0; i < nums.size(); i++)
  //   { // O(N)
  //     pq.push(nums[i]); // O(Log N)
  //   }

  //   for (int i = 0; i < k - 1; i++)
  //   { // O(k)
  //     pq.pop(); // O(Log N)
  //   }

  //   return pq.top();
  // }

  // // ----------------------------
  // // Approach3:
  // //

  // // Better approach: Using PQ as MAX heap
  // //
  // // Time: O(K Log K + (N-K)*LogK ) ~ O(N Log K)
  // // Space: O(K)
  // int kthSmallest(int n,int k,vector<int> &nums)
  // {

  //   priority_queue<int> pq; // default max heap
  //   int N = nums.size();

  //   for (int i = 0; i < k; i++)
  //   {                       // O(K)
  //     pq.push(nums[i]); // O(Log K)
  //   }

  //   for (int i = k; i < N; i++)
  //   { // O(N-K)

  //     if (nums[i] < pq.top())
  //     {
  //       pq.pop(); // O(Log K)
  //       pq.push(nums[i]);
  //     }
  //   }

  //   return pq.top();
  // }

  // ----------------------------
  // Approach4:
  //

  //
  // O(1)
  int getRandomIdx(int l, int r)
  {
    int len = r - l + 1;

    int randx = rand() % len;

    return (l + randx);
  }

  //
  // O(n)
  int partition(vector<int> &arr, int start, int end, int pivotIdx)
  {

    swap(arr[start], arr[pivotIdx]);

    pivotIdx = start;
    int pivot = arr[pivotIdx];

    int rightToPivotx = start + 1; // index representing just the next index to the sorted place of pivot

    for (int i = start + 1; i <= end; i++)
    { // O(N): traverse the whole array

      if (arr[i] < pivot)
      { // where ever element smaller than pivot is found, swap with the rightToPivotx and increment rightToPivotx so that rightToPivotx still points to the just next element of pivot's sorted place
        swap(arr[i], arr[rightToPivotx]);
        rightToPivotx++;
      }
    }

    swap(arr[pivotIdx], arr[rightToPivotx - 1]);

    return (rightToPivotx - 1);
  }

  //
  //
  // Optimal approach: Using Quickselect Algorithm
  //
  // Time: Avg(N) but O(N^2)
  // Space: O(1)
  int kthSmallest(int n, int k, vector<int> &nums)
  {
    int N = nums.size();

    int l = 0;
    int r = N - 1;

    while (l <= r)
    { // O(N + N/2 + N/4 + N/8 + ...) ~~ O(N)
      // becasue each time partitions into half (tense to) of the prev array.
      // But in worst case if the random pivot always partitions the array in (N-1) and 1, then ~~ O(N^2)

      int randx = getRandomIdx(l, r);

      int pivotSortedIdx = partition(nums, l, r, randx); // O(n)

      if (pivotSortedIdx == (k - 1))
        return nums[pivotSortedIdx];

      else if (pivotSortedIdx > (k - 1))
      {
        r = pivotSortedIdx - 1;
      }
      else
      {
        l = pivotSortedIdx + 1;
      }
    }

    return -1;
  }
};

int main()
{
  return 0;
}
