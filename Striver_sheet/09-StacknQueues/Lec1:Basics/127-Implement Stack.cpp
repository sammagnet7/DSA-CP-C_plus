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

1. Title: Implement Stack using Arrays

Links:
https://takeuforward.org/data-structure/implement-stack-using-array/
https://www.naukri.com/code360/problems/stack-implementation-using-array_3210209?leftPanelTabValue=PROBLEM


Problem statement:
Stack is a data structure that follows the LIFO (Last in First out) principle. Design and implement a stack to implement the following functions:

1. Push(num): Push the given number in the stack if the stack is not full.

2. Pop: Remove and print the top element from the stack if present, else print -1.

3. Top: Print the top element of the stack if present, else print -1.

4. isEmpty: Print 1 if the stack is empty, else print 0.

5. isFull: Print 1 if the stack is full, else print 0.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
2. Title: Implement Stack using Linked list

Links:
https://takeuforward.org/data-structure/implement-stack-using-linked-list/
https://www.naukri.com/code360/problems/implement-stack-with-linked-list_630475?leftPanelTabValue=PROBLEM


Problem statement:
You must implement the Stack data structure using a Singly Linked List.

Create a class named 'Stack' which supports the following operations(** all in O(1) time **):


getSize: Returns an integer. Gets the current size of the stack

isEmpty: Returns a boolean. Gets whether the stack is empty

push: Returns nothing. Accepts an integer. Puts that integer at the top of the stack

pop: Returns nothing. Removes the top element of the stack. It does nothing if the stack is empty.

getTop: Returns an integer. Gets the top element of the stack. Returns -1 if the stack is empty


INPUT::::::


OUTPUT::::::


-----------------------------------------------------------------------

3. Title: Implement Stack using Queue:

Links:
https://takeuforward.org/data-structure/implement-stack-using-single-queue/
https://leetcode.com/problems/implement-stack-using-queues/description/


Problem statement:
Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.
Notes:

You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.



INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Implement Stack using Arrays
// Note: All op must be in O(1)
class Stack
{

private:
    vector<int> arr; // No memory allocated yet
    int cap = 0;

public:
    Stack(int capacity) { cap = capacity; }

    // O(1)
    void push(int num)
    {
        // Write your code here.
        if (arr.size() < cap)
            arr.push_back(num);
    }

    // O(1)
    int pop()
    {
        // Write your code here.
        if (arr.size() == 0)
            return -1;

        int ret = arr.back();
        arr.pop_back();
        return ret;
    }

    // O(1)
    int top()
    {
        // Write your code here.
        if (arr.size() == 0)
            return -1;
        return arr.back();
    }

    // O(1)
    int isEmpty()
    {
        // Write your code here.
        return arr.size() == 0 ? 1 : 0;
    }

    // O(1)
    int isFull()
    {
        // Write your code here.
        if (arr.size() == cap)
            return 1;
        else
            return 0;
    }
};

//-----------------------------------------------------------------------
// 2. Title: Implement Stack using Linked list
// Note: All op must be done in O(1)

class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        this->data = 0;
        next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

class Stack
{
    // Write your code here
    Node *head;
    int size;

public:
    Stack()
    {
        // Write your code here
        Node *dummyN = new Node();
        head = dummyN;

        size = 0;
    }

    int getSize() // O(1)
    {
        // Write your code here
        return this->size;
    }

    bool isEmpty() // O(1)
    {
        // Write your code here
        if (this->size == 0)
            return true;
        else
            return false;
    }

    void push(int data) // O(1)
    {
        // Write your code here
        Node *newN = new Node(data, head); // newN --> head
        head = newN;
        this->size++;
    }

    void pop() // O(1)
    {
        // Write your code here
        if (size != 0)
        {
            Node *tmp = head;
            head = head->next;
            tmp->next = NULL;
            delete (tmp);
            this->size--;
        }
    }

    int getTop() // O(1)
    {
        // Write your code here
        if (size == 0)
            return -1;
        else
            return head->data;
    }
};

//-----------------------------------------------------------------------
// 3. Title: Implement Stack using Queue:
// Some ops takes O(N)

// Approach1: Sub-optimal approach beacuse of higher space taken
// Implementing Stack using double queue
// Space: O(2N)
// class MyStack {
//     queue<int> q1, q2;
//     queue<int> *cur, *other, *tmp;
// public:
//     MyStack() {
//         cur = &q1;
//         other = &q2;
//     }

//     void push(int x) {
//         cur->push(x);
//     }

//     int pop() {

//         int top = -1;

//         if(cur->empty()) return top;

//         while(cur->size()>1){
//             int el = cur->front();
//             cur->pop();
//             other->push(el);
//         }

//         top = cur->front();
//         cur->pop();

//         tmp = cur;
//         cur = other;
//         other = tmp;

//         return top;
//     }

//     int top() {

//         int top = -1;
//         if(cur->empty()) return top;

//         while(!cur->empty()){
//             top = cur->front();
//             cur->pop();
//             other->push(top);
//         }

//         tmp = cur;
//         cur = other;
//         other = tmp;

//         return top;
//     }

//     bool empty() {
//         return cur->empty();
//     }
// };

// Approach2: Implementing Stack using single queue i.e. taking lower space
// Note: Here we are reversing at the time of push()
//       But in general implementations reverse at time of pop() or top()
// Space: O(N)
class MyStack
{
    queue<int> q1;

public:
    MyStack()
    {
    }

    // O(1)
    void push(int x)
    {
        q1.push(x);
    }

    // O(N)
    int pop()
    {

        int top = -1;
        int curSize = q1.size();

        if (curSize == 0)
            return top;

        while (--curSize)
        {
            top = q1.front();
            q1.pop();
            q1.push(top);
        }
        top = q1.front();
        q1.pop();

        return top;
    }

    // O(N)
    int top()
    {

        int top = -1;
        int curSize = q1.size();

        if (curSize == 0)
            return top;

        while (curSize--)
        {
            top = q1.front();
            q1.pop();
            q1.push(top);
        }

        return top;
    }

    // O(1)
    bool empty()
    {
        return q1.empty();
    }
};

int main()
{

    return 0;
}
