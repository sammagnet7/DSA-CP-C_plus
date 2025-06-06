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

using namespace std;

/*
Construct Doubly LinkedList:
https://www.naukri.com/code360/problems/introduction-to-doubly-linked-list_8160413?leftPanelTabValue=SUBMISSION

Insertion In Doubly Linked List:
https://www.naukri.com/code360/problems/insertion-in-doubly-linked-list_4609682?leftPanelTabValue=SUBMISSION

Insert at end of Doubly Linked List:
https://www.naukri.com/code360/problems/insert-at-end-of-doubly-linked-list_8160464?leftPanelTabValue=SUBMISSION

Deletion In Doubly Linked List:
https://www.naukri.com/code360/problems/deletion-in-doubly-linked-list_4609672?leftPanelTabValue=SUBMISSION


INPUT::::::


OUTPUT::::::

*/

class Node
{
public:
    int data;
    Node *next, *prev;
    Node() : data(0), next(nullptr), prev(nullptr) {}
    Node(int x) : data(x), next(nullptr), prev(nullptr) {}
    Node(int x, Node *next, Node *prev) : data(x), next(next), prev(prev) {}
};

class MyDoublyLinkedList
{
public:
    // Construct Doubly LinkedList
    Node *constructDLL(vector<int> &arr)
    {

        Node *head = new Node(arr[0]);
        Node *currN = head;

        for (int i = 1; i < arr.size(); i++)
        {
            int elm = arr[i];

            Node *newN = new Node(elm, nullptr, currN);
            currN->next = newN;
            currN = newN;
        }

        return head;
    }

    // Insert at end of Doubly Linked List
    Node *insertAtTail(Node *head, int k)
    {

        if (head == NULL)
        { // Handling case: N == 0
            Node *newN = new Node(k);
            return newN;
        }

        Node *curN = head;

        while (curN->next != nullptr)
        {
            curN = curN->next;
        }

        Node *newN = new Node(k, curN, nullptr);
        curN->next = newN;

        return head;
    }

    // Insertion In Doubly Linked List
    Node *insert(int k, int val, Node *head)
    {

        Node *curN = head;
        Node *preN = nullptr;

        for (int i = 0; i < k; i++)
        {
            preN = curN;
            curN = curN->next;
        }

        Node *newN = new Node(val);

        if (curN == NULL)
        { // When k is equal to size of the list
            newN->prev = preN;
            newN->next = nullptr;

            preN->next = newN;

            return head;
        }
        else
        { // Otherwise

            newN->prev = curN->prev;
            newN->next = curN;

            if (curN->prev != NULL) // some middle node
                curN->prev->next = newN;
            else
                head = newN; // Node at index 0

            curN->prev = newN;

            return head;
        }
    }

    // Deletion In Doubly Linked List
    void deleteNode(Node *(&head), int pos)
    {

        Node *curN = head;

        for (int i = 0; i < pos; i++)
        {
            curN = curN->next;
        }

        Node *preN = curN->prev;
        Node *nextN = curN->next;

        if (preN != NULL) // Other than index 0
            preN->next = nextN;
        else
            head = nextN; // Removing at index 0

        if (nextN != NULL) // other than tail index
            nextN->prev = preN;

        curN->prev = NULL;
        curN->next = NULL;
        delete (curN); // Before deleting Made the pointers to NULL
    }
};

int main()
{
    MyDoublyLinkedList *obj = new MyDoublyLinkedList();

    return 0;
}
