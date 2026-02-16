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

1. Title: Build max heap

Links:
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/build-heap-from-a-given-array
https://www.naukri.com/code360/problems/build-heap_975375?leftPanelTabValue=PROBLEM


Problem statement:
You are given an integer array with N elements. Your task is to build a max binary heap from the array.

A max-heap is a complete binary tree in which the value of each internal node is greater than or equal to the values of the children of that node.

Note :
You do not need to print anything, just return the vector representation of the heap such that the input array follows 0 - based indexing and :

The left child of the ith node is at (2 * i + 1)th index.

The right child of the ith node is at (2 * i + 2)th index.

Parent of the node present at ith index is at (i - 1) / 2 indexes.


INPUT::::::


OUTPUT::::::
-------------------------------------------------------------------------------------------------------
2. Title: Convert Min Heap To Max Heap

Links:
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/convert-min-heap-to-max-heap?tab=editorial
https://www.naukri.com/code360/problems/convert-min-heap-to-max-heap_1381084?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array of size ‘N’ which is an array representation of min-heap.
You need to convert this min-heap array representation to a max-heap array representation. Return the max-heap array representation.

For Example
Corresponding to given min heap : [1,2,3,6,7,8]

It can be converted to the following max heap: [8,7,3,6,2,1]


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:

    //-------------------------------------------------------------------------------
    // 1. Title: Build max heap
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

    // Optimal approach: From 2nd-last layer to top layer incrementally builds the heap.
    // Overall the amortized time taken becomes O(N)
    //
    // Time: O(N)
    // Space: O(1)
    vector<int> buildMaxHeap(vector<int> &arr, int n)
    {
        // Write your code here
        int INendx = n / 2 - 1; // Internal-nodes end index

        for (int i = INendx; i >= 0; i--)   
        {
            max_heapify_DOWN(arr, i, n);
        }

        return arr;
    }

    //-------------------------------------------------------------------------------
    // 2. Title: Convert Min Heap To Max Heap
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

    // Exactly same method of `Building heap` from scratch
    // Optimal approach: From 2nd-last layer to top layer incrementally builds the heap.
    // Overall the amortized time taken becomes O(N)
    //
    // Time: O(N)
    // Space: O(1)
    vector<int> MinToMaxHeap(int n, vector<int> &arr)
    {
        // Write your code here.
        // Write your code here
        int INendx = n / 2 - 1; // Internal-nodes end index

        for (int i = INendx; i >= 0; i--)
        {
            max_heapify_DOWN(arr, i, n);
        }

        return arr;
    }
};

int main()
{
    return 0;
}
