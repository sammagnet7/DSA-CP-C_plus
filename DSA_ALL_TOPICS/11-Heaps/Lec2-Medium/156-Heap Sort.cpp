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

1. Title: Heap Sort

Links:
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/heap-sort
https://www.geeksforgeeks.org/problems/heap-sort/1


Problem statement:
Given an array arr[]. The task is to sort the array elements by Heap Sort.

Examples:

Input: arr[] = [4, 1, 3, 9, 7]
Output: [1, 3, 4, 7, 9]
Explanation: After sorting elements using heap sort, elements will be in order as 1, 3, 4, 7, 9.
Input: arr[] = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Explanation: After sorting elements using heap sort, elements will be in order as 1, 2, 3, 4, 5, 6, 7, 8, 9, 10.
Input: arr[] = [2, 1, 5]
Output: [1, 2, 5]
Explanation: After sorting elements using heap sort, elements will be in order as 1, 2, 5.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Heap sort
  //-------------------------------------------------------------------------------

  // O(Log N)
  void max_heapify_DOWN(vector<int> &heap, int idx, int N)
  {

    int lc_idx = 2 * idx + 1;
    int rc_idx = 2 * idx + 2;

    int greatestIdx = idx;
    if ((lc_idx < N) && heap[lc_idx] > heap[greatestIdx])
      greatestIdx = lc_idx;
    if ((rc_idx < N) && heap[rc_idx] > heap[greatestIdx])
      greatestIdx = rc_idx;

    if (greatestIdx != idx)
    {
      swap(heap[idx], heap[greatestIdx]);
      max_heapify_DOWN(heap, greatestIdx, N);
    }
  }

  // Time: O(N)
  // Space: O(1)
  void buildMaxHeap(vector<int> &arr, int n)
  {
    // Write your code here
    int INendx = n / 2 - 1; // Internal-nodes end index

    for (int i = INendx; i >= 0; i--)
    {
      max_heapify_DOWN(arr, i, n);
    }
  }

  // Optimal approach: Using Build_Heap
  // Note: For sorting ASC, use max heap. So that can put the next max onto the last index
  // Note: For sorting DESC, use min heap. So that can put the next min onto the last index
  //
  // Time: O(N Log N)
  // Space: O(1)
  void heapSort(vector<int> &arr)
  {
    // code here
    int N = arr.size();

    buildMaxHeap(arr, N);

    int curSize = N;

    while (curSize > 1) // O(N)
    {

      swap(arr[0], arr[curSize - 1]);
      curSize--;
      max_heapify_DOWN(arr, 0, curSize); // O(Log N)
    }
  }
};

int main()
{
  return 0;
}
