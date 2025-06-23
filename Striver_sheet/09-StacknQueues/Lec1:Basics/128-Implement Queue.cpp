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

using namespace std;

/*

1. Title: Implement Queue using Arrays

Links:
https://takeuforward.org/data-structure/implement-queue-using-array/
https://www.naukri.com/code360/problems/implement-queue-using-arrays_8390825?leftPanelTabValue=PROBLEM


Problem statement:
Queue is a linear data structure that follows the idea of First In First Out. That means insertion and retrieval operations happen at opposite ends.
Implement a simple queue using arrays.

You are given 'query' queries which are either of the 2 types:

1 'e': Enqueue (add) element ‘e’ at the end of the queue.

2: Dequeue (retrieve) the element from the front of the queue. If the queue is empty, return -1.




INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
2. Title: Implement Queue using Linked list

Links:


Problem statement:



INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Implement Queue using Stack

Links:


Problem statement:



INPUT::::::


OUTPUT::::::

*/

//-----------------------------------------------------------------------
// 1. Title: Implement Queue using Arrays

class Queue
{

private:
    int front, rear;
    vector<int> arr;

public:
    Queue()
    {
        front = 0;
        rear = 0;
        arr.resize(100001);
    }

    // O(1)
    // Enqueue (add) element 'e' at the end of the queue.
    void enqueue(int e)
    {
        // Write your code here.
        int next = (rear + 1) % 100001;
        if (next != front)
        {
            arr[rear] = e;
            rear = (rear + 1) % 100001;
        }
    }

    // O(1)
    // Dequeue (retrieve) the element from the front of the queue.
    int dequeue()
    {
        // Write your code here.
        if (front == rear)
            return -1;
        else
        {
            int ret = arr[front];
            front = (front + 1) % 100001;
            return ret;
        }
    }
};

//-----------------------------------------------------------------------
// 2. Title: Implement Queue using Linked list



//-----------------------------------------------------------------------
// 3. Title: Implement Queue using Stack


int main()
{
    return 0;
}
