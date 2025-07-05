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

1. Title: Merge k Sorted Lists

Links:
https://takeuforward.org/data-structure/merge-k-sorted-arrays/
https://leetcode.com/problems/merge-k-sorted-lists/description/


Problem statement:
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Examples:
  Example 1:
  Input: lists = [[1,4,5],[1,3,4],[2,6]]
  Output: [1,1,2,3,4,4,5,6]
  Explanation: The linked-lists are:
  [
    1->4->5,
    1->3->4,
    2->6
  ]
  merging them into one sorted list:
  1->1->2->3->4->4->5->6

  Example 2:
  Input: lists = []
  Output: []

  Example 3:
  Input: lists = [[]]
  Output: []



INPUT::::::


OUTPUT::::::

--------------------------------------------------------------------------------------------------------

2. Title: Merge K Sorted Arrays

Links:
https://takeuforward.org/linked-list/merge-k-sorted-linked-lists
https://www.naukri.com/code360/problems/merge-k-sorted-arrays_975379?leftPanelTabValue=PROBLEM


Problem statement:
You have been given ‘K’ different arrays/lists, which are sorted individually (in ascending order). You need to merge all the given arrays/list such that the output array/list should be sorted in ascending order.


Examples:
  Sample Input 1:
  1
  2
  3
  3 5 9
  4
  1 2 3 8
  Sample Output 1:
  1 2 3 3 5 8 9
  Explanation of Sample Input 1:
  After merging the two given arrays/lists [3, 5, 9] and [ 1, 2, 3, 8], the output sorted array will be [1, 2, 3, 3, 5, 8, 9].

  Sample Input 2:
  1
  4
  3
  1 5 9
  2
  45 90
  5
  2 6 78 100 234
  1
  0
  Sample Output 2:
  0 1 2 5 6 9 45 78 90 100 234
  Explanation of Sample Input 2 :
  After merging the given arrays/lists [1, 5, 9], [45, 90], [2, 6, 78, 100, 234] and [0], the output sorted array will be [0, 1, 2, 5, 6, 9, 45, 78, 90, 100, 234].


INPUT::::::


OUTPUT::::::


*/

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Merge k Sorted Lists
  //-------------------------------------------------------------------------------

  //-----------------------------------
  // Approach1: Sub-optimal
  //

  // // Sub-optimal approach: Each time we compare `k` lists' head to find out the minimum one, add that to ans, repeat for all nodes
  // //
  // // Time: O(K*N) where K is #lists and N is #total nodes in all the lists
  // // SPace: O(1)
  // ListNode *mergeKLists(vector<ListNode *> &lists)
  // {

  //   ListNode *ans;
  //   ListNode *head = new ListNode();
  //   ans = head;

  //   int k = lists.size();

  //   while (true)
  //   { // O(N) where `N` is number of total nodes in all the lists

  //     int smallestIdx = -1;

  //     for (int i = 0; i < k; i++)
  //     { // O(K)

  //       if (lists[i] == NULL)
  //         continue;

  //       if (head->next == NULL)
  //       { // for first non-null `i` this will happen
  //         head->next = lists[i];
  //         smallestIdx = i;
  //       }
  //       else
  //       {
  //         if (lists[i]->val < head->next->val)
  //         {
  //           head->next = lists[i];
  //           smallestIdx = i;
  //         }
  //       }
  //     }

  //     if (smallestIdx == -1)
  //       break;
  //     lists[smallestIdx] = lists[smallestIdx]->next;
  //     head->next->next = NULL;
  //     head = head->next;
  //   }

  //   return ans->next;
  // }

  //-----------------------------------
  // Approach2: Optimal
  //

  //
  // O(n) where `n` is the total number of nodes including list1 and list2
  ListNode *merge(ListNode *list1, ListNode *list2)
  {

    ListNode *head = new ListNode();
    ListNode *tail = head;

    while (list1 != NULL && list2 != NULL)
    {

      if (list2->val < list1->val)
      {
        tail->next = list2;
        list2 = list2->next;
      }
      else
      {
        tail->next = list1;
        list1 = list1->next;
      }

      tail = tail->next;
    }

    tail->next = NULL;

    if (list1 != NULL)
    {
      tail->next = list1;
    }
    if (list2 != NULL)
    {
      tail->next = list2;
    }

    return head->next;
  }

  //
  // O(Log K)
  ListNode *divideAndMerge(vector<ListNode *> &lists, int start, int end)
  {

    if (start == end)
      return lists[start];

    if (start > end)
      return NULL;

    int mid = start + (end - start) / 2;

    ListNode *headL = divideAndMerge(lists, start, mid);
    ListNode *headR = divideAndMerge(lists, mid + 1, end);

    return merge(headL, headR);
  }

  //  Here we first divide the list into its smallest possible parts i.e. single list, then we merges back 2 lists each time
  //
  // Optimal appraoch: Divide and conqure paradigm
  // Time : O(N Log k)
  // Spcae: O(1)
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {

    return divideAndMerge(lists, 0, (lists.size() - 1));
  }

  // Note:
  // Another approach can be done using Heap data structure. Follow below links' optimal solution for that:
  // https://takeuforward.org/linked-list/merge-k-sorted-linked-lists
  // Time for this is also: O(N Log k) where N is total nuber of nodes including all the lists.
  //

  //-------------------------------------------------------------------------------
  // 2. Title: Merge K Sorted Arrays
  //-------------------------------------------------------------------------------

  //-----------------------------------
  // Approach1: Optimal
  //

  // Optimal approach: Using max heap
  //
  //
  // Time: O(N Log K) where N is total number of nodes available and k is #lists
  // Space: O(K + N), considering `ans` size
  vector<int> mergeKSortedArrays(vector<vector<int>> &arrays, int k)
  {
    int N = 0;
    priority_queue<pair<int, int>> mxHeap; // <val, vector index>   // O(k)

    for (int i = 0; i < arrays.size(); i++)
    { // O(k)
      int n = arrays[i].size();
      N += n;
      mxHeap.push({arrays[i][n - 1], i});
    }

    vector<int> ans(N); // O(N)

    while (!mxHeap.empty())
    { // O(N)

      ans[N - 1] = mxHeap.top().first;
      int vec_idx = mxHeap.top().second;

      N--;
      mxHeap.pop(); // O(Log K)

      arrays[vec_idx].pop_back();

      if (!arrays[vec_idx].empty())
      {
        mxHeap.push({arrays[vec_idx].back(), vec_idx}); // O(Log K)
      }
    }

    return ans;
  }
  
};

int main()
{
  return 0;
}
