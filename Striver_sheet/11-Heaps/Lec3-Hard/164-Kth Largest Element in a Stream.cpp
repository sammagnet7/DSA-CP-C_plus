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

1. Title: Kth Largest Element in a Stream

Links:
https://takeuforward.org/plus/dsa/problems/kth-largest-element-in-a-stream-of-running-integers?tab=editorial
https://leetcode.com/problems/kth-largest-element-in-a-stream/


Problem statement:
You are part of a university admissions office and need to keep track of the kth highest test score from applicants in real-time. This helps to determine cut-off marks for interviews and admissions dynamically as new applicants submit their scores.

You are tasked to implement a class which, for a given integer k, maintains a stream of test scores and continuously returns the kth highest test score after a new score has been submitted. More specifically, we are looking for the kth highest score in the sorted list of all scores.

Implement the KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of test scores nums.
int add(int val) Adds a new test score val to the stream and returns the element representing the kth largest element in the pool of test scores so far.


Example 1:
  Input:
  ["KthLargest", "add", "add", "add", "add", "add"]
  [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]

  Output: [null, 4, 5, 5, 8, 8]

  Explanation:

  KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
  kthLargest.add(3); // return 4
  kthLargest.add(5); // return 5
  kthLargest.add(10); // return 5
  kthLargest.add(9); // return 8
  kthLargest.add(4); // return 8

Example 2:
  Input:
  ["KthLargest", "add", "add", "add", "add"]
  [[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]

  Output: [null, 7, 7, 7, 8]

  Explanation:

  KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
  kthLargest.add(2); // return 7
  kthLargest.add(10); // return 7
  kthLargest.add(9); // return 7
  kthLargest.add(9); // return 8


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Kth Largest Element in a Stream
  //-------------------------------------------------------------------------------

  // Optimal solution: Using MIN heap to store only k largest elements into the heap
  // Time: O(log N)
  // Space: O(K)
  class KthLargest
  {
  public:
    priority_queue<int, vector<int>, greater<int>> pq; // MIN heap
    int maxSize;

    KthLargest(int k, vector<int> &nums)
    {
      maxSize = k;

      for (int i : nums)
      {
        pq.push(i);
        if (pq.size() > maxSize)
        {
          pq.pop();
        }
      }
    }

    int add(int val)
    {
      pq.push(val); // O(Log N)

      if (pq.size() > maxSize)
        pq.pop();

      return pq.top();
    }
  };

  /**
   * Your KthLargest object will be instantiated and called as such:
   * KthLargest* obj = new KthLargest(k, nums);
   * int param_1 = obj->add(val);
   */
};

int main()
{
  return 0;
}
