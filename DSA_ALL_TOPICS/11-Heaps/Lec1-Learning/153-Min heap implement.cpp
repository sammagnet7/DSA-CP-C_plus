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
#include <utility>  // needed for std::swap()

using namespace std;

/*

1. Title: Min Heap Implementation

Links:
Theory: https://takeuforward.org/plus/dsa/problems/heaps-theory
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/implement-min-heap?tab=editorial
https://www.naukri.com/code360/problems/min-heap-implementation_5480527?leftPanelTabValue=PROBLEM


Problem statement:
Implement the Min Heap data structure.

Min heap is a tree data structure where the root element is the smallest of all the elements in the heap. Also, the children of every node are smaller than or equal to the root node.

The insertion and removal of elements from the heap take log('N'), where 'N' is the number of nodes in the tree.
Implement the “minHeap” class. You will be given the following types of queries:-

0 extractMinElement(): Remove the minimum element present in the heap, and return it.

1 deleteElement( i ): Delete the element present at the 'i' th index.

2 insert( key ): Insert the value 'key' in the heap.

For queries of types 0 and 1, at least one element should be in the heap.


INPUT::::::


OUTPUT::::::


*/

class minHeap
{

private:
    vector<int> heap;
    int cap;
    int curSize = 0;

    // O(Log N)
    void heapify_DOWN(int idx)
    {

        int lc_idx = 2 * idx + 1;
        int rc_idx = 2 * idx + 2;

        int lowestIdx = idx;
        if ((lc_idx < curSize) && heap[lc_idx] < heap[lowestIdx])
            lowestIdx = lc_idx;
        if ((rc_idx < curSize) && heap[rc_idx] < heap[lowestIdx])
            lowestIdx = rc_idx;

        if (lowestIdx != idx)
        {
            swap(heap[idx], heap[lowestIdx]);
            heapify_DOWN(lowestIdx);
        }
    }

    // O(Log N)
    void heapify_UP(int idx)
    {
        int p_idx = (idx - 1) / 2;
        if (p_idx < 0)
            return;

        if (heap[p_idx] <= heap[idx])
            return;
        else
        {
            swap(heap[p_idx], heap[idx]);
            heapify_UP(p_idx);
        }
    }

public:
    // Constructor for the class.
    // minHeap(): heap(vector<int>()) {
    //     // Write your code here.
    //     curSize = 0;
    // }

    minHeap(int capacity) : heap(vector<int>(capacity))
    {
        cap = capacity;
        curSize = 0;
    }

    // Implement the function to remove minimum element.
    // O(Log N)
    int extractMinElement()
    {
        // Write you code here.
        if (curSize == 0)
            return -1;

        int ret = heap[0];

        swap(heap[0], heap[curSize - 1]);
        curSize--;

        heapify_DOWN(0);

        return ret;
    }

    // Implement the function to delete an element.
    // O(Log N)
    void deleteElement(int ind)
    {
        // Write you code here.

        if (curSize <= 0 || ind >= curSize)
        { // Note: **important to handle**
            return;
        }

        swap(heap[ind], heap[curSize - 1]); // O(N)

        curSize--;

        heapify_UP(ind);
        heapify_DOWN(ind);
    }

    // Implement the function to insert 'val' in the heap.
    // O(Log N)
    void insert(int val)
    {
        // Write you code here.

        if (curSize >= cap)
        {
            return;
        }

        heap[curSize] = val;
        curSize++;
        heapify_UP((curSize - 1)); // O(Log N)
    }
};

int main()
{
    return 0;
}
