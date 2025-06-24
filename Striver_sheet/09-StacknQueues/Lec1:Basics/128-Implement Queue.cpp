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
https://takeuforward.org/data-structure/implement-queue-using-linked-list/
https://www.naukri.com/code360/problems/implement-queue-using-linked-list_8161235?leftPanelTabValue=PROBLEM

Problem statement:
You are given ‘q’ queries, where each query can be of the following types:

push(x) -> this means to push the element ‘x’ in the queue.
pop() -> This means deleting the front element of the queue and returning it. If there’s no element in the queue, return -1.
Your task is to implement a queue that supports these two queries.

You must write an algorithm whose time complexity is O(1), and whose space complexity is O(1).

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Implement Queue using Stack

Links:
https://takeuforward.org/data-structure/implement-queue-using-stack/
https://leetcode.com/problems/implement-queue-using-stacks/description/


Problem statement:
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.

Notes:
You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.



INPUT::::::


OUTPUT::::::

*/

//-----------------------------------------------------------------------
// 1. Title: Implement Queue using Arrays
// Note: All ops in O(1)

// Time: O(1)
// Space: O(1) ignoring the actual queue space
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
// Note: All op must be done in O(1)

// Time: o(1)
// Space: O(1) ignoring the actual queue space
class Node
{
public:
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int x) : data(x), next(nullptr) {}
    Node(int x, Node *next) : data(x), next(next) {}
};

struct Queue
{
    Node *front;
    Node *rear;
    void push(int);
    int pop();

    Queue()
    {
        front = rear = NULL;
    }
};

void Queue::push(int x)
{ // O(1)
    // Write Your Code Here
    if (rear == NULL)
    {
        Node *newN = new Node(x);
        front = rear = newN;
    }
    else
    {
        Node *newN = new Node(x);
        rear->next = newN;
        rear = newN;
    }
}

int Queue::pop()
{ // O(1)
    // Write Your Code Here
    if (front == NULL)
    {
        return -1;
    }
    else if (front == rear)
    {
        int ret = front->data;
        front = rear = NULL;
        return ret;
    }

    else
    {
        int ret = front->data;
        Node *tmp = front;
        front = front->next;
        delete (tmp);
        return ret;
    }
}

//-----------------------------------------------------------------------
// 3. Title: Implement Queue using Stack
// All ops in O(1) time and can take O(2N) space

// Optimal approach: While  at time of pop() occasionally we perform `n` copy operations
// Time: O(1)
// Space: O(2N)
class MyQueue
{
public:
    stack<int> st1, st2;

    MyQueue()
    {
    }

    // O(1)
    void push(int x)
    {
        st1.push(x);
    }

    // O(N) ~ Avg(1)
    int pop()
    {
        if (!st2.empty())
        { // O(1)
            int top = st2.top();
            st2.pop();
            return top;
        }

        if (st1.empty())
        { // O(1)
            return -1;
        }

        while (!st1.empty())
        { // O(N)
            st2.push(st1.top());
            st1.pop();
        }

        int top = st2.top();
        st2.pop();
        return top;
    }

    int peek()
    {
        if (!st2.empty())
        { // O(1)
            int top = st2.top();
            return top;
        }

        if (st1.empty())
        { // O(1)
            return -1;
        }

        while (!st1.empty())
        { // O(N)
            st2.push(st1.top());
            st1.pop();
        }

        int top = st2.top();
        return top;
    }

    bool empty()
    {
        if (st1.empty() && st2.empty())
            return true;
        else
            return false;
    }
};

int main()
{
    return 0;
}
