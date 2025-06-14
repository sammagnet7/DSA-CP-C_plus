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
Flattening a Linked List:

https://takeuforward.org/data-structure/flattening-a-linked-list/
https://www.naukri.com/code360/problems/flatten-a-linked-list_1112655?leftPanelTabValue=SUBMISSION

Helper: Merge Two Sorted Linked Lists:
https://www.naukri.com/code360/problems/800332?leftPanelTabValue=SUBMISSION

Problem statement:
Given a linked list containing ‘N’ head nodes where every node in the linked list contains two pointers:
‘Next’ points to the next node in the list
‘Child’ pointer to a linked list where the current node is the head
Each of these child linked lists is in sorted order and connected by a 'child' pointer. Your task is to flatten this linked list such that all nodes appear in a single layer or level in a 'sorted order'.

Examples:

Sample Input 1 :
4
3
1 2 3
3
8 10 15
2
18 22
1
29
Sample Output 1 :
1 2 3 8 10 15 18 22 29

Sample Input 2 :
5
2
4 6
2
5 71
3
7 8 9
3
11 12 19
3
14 15 17
Sample Output 2 :
4 5 6 7 8 9 11 12 14 15 17 19 71

Expected Time Complexity:
Try solving this in O(n*n*k), where ‘n’ denotes the number of head nodes and ‘k’ is the average number of child nodes in all 'n' sub-lists.
Expected Space Complexity:
Try solving this without using any extra space.

*/

class Node
{
public:
    int data;
    Node *child;
    Node *next;

    Node()
    {
        this->data = 0;
        this->child = NULL;
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->child = NULL;
        this->next = NULL;
    }
    Node(int data, Node *next, Node *child)
    {
        this->data = data;
        this->child = child;
        this->next = next;
    }
};

class Solution
{
public:
    // ---------------------------------------------------------------------------
    // Optimal approach
    // Time: O(N+M)
    // Space: O(1)
    Node *sortAndMergeLists(Node *first, Node *second)
    {
        Node *tmp1 = first;
        Node *tmp2 = second;
        Node *nextN;
        Node *prevN = nullptr;

        Node *ans = first;
        if (tmp1->data > tmp2->data)
            ans = second;

        while (tmp1 != NULL && tmp2 != NULL)
        {

            if (tmp1->data <= tmp2->data)
            {
                prevN = tmp1;
                tmp1 = tmp1->child;
            }
            else
            {
                if (prevN == NULL)
                    first = tmp2;
                else
                    prevN->child = tmp2;
                prevN = tmp2;
                nextN = tmp2->child;
                tmp2->child = tmp1;
                tmp2 = nextN;
            }
        }

        if (tmp2 != NULL)
        {
            prevN->child = tmp2;
        }

        return first;
    }

    // Optimal approach: In each iteration merge two sorted LL
    // Time: O(N^2 * K)
    // SPace: O(1)
    Node *flattenLinkedList(Node *head)
    {
        if (head->next == NULL)
            return head;

        Node *tmpHorizon = head->next;

        while (tmpHorizon != NULL)
        {

            head = sortAndMergeLists(head, tmpHorizon);

            tmpHorizon = tmpHorizon->next;
        }

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}