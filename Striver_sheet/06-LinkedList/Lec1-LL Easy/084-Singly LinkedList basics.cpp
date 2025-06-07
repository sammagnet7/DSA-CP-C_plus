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
Design Singly LinkedList:

https://takeuforward.org/linked-list/linked-list-introduction
https://leetcode.com/problems/design-linked-list/submissions/1655479399/

Delete a LinkedList node with out the HEAD provided:
https://leetcode.com/problems/delete-node-in-a-linked-list/editorial/

Approach:
    void deleteNode(ListNode* node) {

        ListNode* temp_next = node->next;
        
        node->val = temp_next->val;
        node->next = temp_next->next;

        delete(temp_next);
    }


INPUT::::::


OUTPUT::::::
-----------------------------------------------------------------------
*/
class MyLinkedList
{
public:
    //-----------------------------------------------------------------------
    // Struct for each Node
    struct Node
    {
        int val;
        Node *next;

        // Constructor for struct Node
        Node(int newVal)
        {
            val = newVal;
            next = nullptr;
        }

        // Constructor for struct Node
        Node(int newVal, Node *ptr)
        {
            val = newVal;
            next = ptr;
        }
    };

    // Attributes to the LinkedList class
    Node *head;
    Node *tail;
    int listLen;

    // Constructor for the LinkedList class' objects
    MyLinkedList()
    {
        head = nullptr;
        tail = head;
        listLen = 0;
    }

    //-----------------------------------------------------------------------
    //  Get the value of the indexth node in the linked list. If the index is invalid, return -1
    // Time: O(N)
    // Space: O(1)
    int get(int index)
    {
        if (index < 0 || index > (listLen - 1))
            return -1;

        Node *currN = head;
        int idx = 0;

        while (currN != nullptr)
        {
            if (idx == index)
                return currN->val;
            currN = currN->next;
            idx++;
        }
        return -1;
    }

    //-----------------------------------------------------------------------
    // Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
    // Time: O(1)
    // Space: O(1)
    void addAtHead(int val)
    {
        Node *newN = new Node(val, head); // Creates new node and set the next pointer with the HEAD pointed node
        head = newN;
        if (listLen == 0)
            tail = newN; // For the 1st node

        listLen++;
    }

    //-----------------------------------------------------------------------
    // Append a node of value val as the last element of the linked list.
    // Time: O(1)
    // Space: O(1)
    void addAtTail(int val)
    {
        Node *newN = new Node(val);
        if (listLen > 0)
            tail->next = newN;

        tail = newN;
        if (listLen == 0)
        {
            head = newN;
        }

        listLen++;
    }

    //-----------------------------------------------------------------------
    // Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
    // Time: O(N)
    // Space: O(1)
    void addAtIndex(int index, int val)
    {
        if (index < 0 || index > listLen)
            return;

        if (index == listLen)
            addAtTail(val);
        else if (index == 0)
            addAtHead(val);
        else
        {
            Node *ptr = head;
            Node *indexedNode = nullptr;
            Node *indexedPrevNode = nullptr;

            int countIdx = 0;
            while (ptr != nullptr)
            {
                indexedPrevNode = indexedNode;
                indexedNode = ptr;

                if (countIdx == index)
                    break;

                ptr = ptr->next;
                countIdx++;
            }

            Node *newN = new Node(val, indexedNode);
            indexedPrevNode->next = newN;

            listLen++;
        }
    }

    //-----------------------------------------------------------------------
    // Delete the indexth node in the linked list, if the index is valid.
    // Time: O(N)
    // Space: O(1)
    void deleteAtIndex(int index)
    {
        if (index < 0 || index > (listLen - 1))
            return;

        if (index == 0)
        {
            Node *curr = head;
            head = head->next;

            delete (curr);
            listLen--;
            return;
        }

        Node *ptr = head;
        Node *indexedNode = nullptr;
        Node *indexedPrevNode = nullptr;

        int countIdx = 0;
        while (ptr != nullptr)
        {
            indexedPrevNode = indexedNode;
            indexedNode = ptr;

            if (countIdx == index)
                break;

            ptr = ptr->next;
            countIdx++;
        }

        indexedPrevNode->next = indexedNode->next;

        if (index == (listLen - 1))
            tail = indexedPrevNode;

        delete (indexedNode);
        listLen--;
    }
};

int main()
{
    MyLinkedList *obj = new MyLinkedList();
    obj->addAtHead(0);

    obj->addAtIndex(1, 4);

    obj->addAtTail(8);

    obj->addAtHead(5);

    obj->addAtIndex(4, 3);

    obj->addAtTail(0);

    obj->addAtTail(5);

    obj->addAtIndex(6, 3);

    obj->deleteAtIndex(7);

    obj->deleteAtIndex(5);

    obj->addAtTail(4);

    while (obj->head != nullptr)
    {
        cout << (obj->head->val) << " ";
        obj->head = obj->head->next;
    }

    cout << endl;

    return 0;
}
