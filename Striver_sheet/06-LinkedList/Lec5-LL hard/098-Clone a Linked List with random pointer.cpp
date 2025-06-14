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
Clone Linked List with Random and Next Pointer:

https://takeuforward.org/data-structure/clone-linked-list-with-random-and-next-pointer/
https://leetcode.com/problems/copy-list-with-random-pointer/submissions/1663815606/


Problem statement:
Given a linked list where every node in the linked list contains two pointers:
‘next’ which points to the next node in the list.
‘random’ which points to a random node in the list or ‘null’.
Create a ‘deep copy’ of the given linked list and return it.

Examples:

Example 1:
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Example 2:
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Example 3:
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

*/

class Node
{
public:
    int val;
    Node *random;
    Node *next;

    Node()
    {
        this->val = 0;
        this->random = NULL;
        this->next = NULL;
    }
    Node(int data)
    {
        this->val = data;
        this->random = NULL;
        this->next = NULL;
    }
    Node(int val, Node *next, Node *random)
    {
        this->val = val;
        this->random = random;
        this->next = next;
    }
};

class Solution
{
public:
    // ---------------------------------------------------------------------------

    // // Better approach: Using map data structure
    // // Time: O(N) or O(N^2) because of unordered_map
    // // Space: O(N) extra space because of map data structure
    // Node *copyRandomList(Node *head)
    // {

    //     unordered_map<Node *, Node *> mpR;
    //     Node *newHead = new Node(-1);

    //     Node *aN = head;
    //     Node *bN = newHead;

    //     while (aN != NULL)
    //     {

    //         Node *newN;
    //         Node *newR;

    //         // creating `next` node
    //         if (mpR.find(aN) != mpR.end())
    //         {
    //             newN = mpR[aN];
    //         }
    //         else
    //         {
    //             newN = new Node(aN->val);
    //         }
    //         mpR[aN] = newN; // Storing new Node pointer w.r.t old node pointer

    //         // creating `random` node
    //         if (mpR.find(aN->random) != mpR.end())
    //         {
    //             newR = mpR[aN->random];
    //         }
    //         else
    //         {
    //             if (aN->random == NULL)
    //                 newR = nullptr;
    //             else
    //                 newR = new Node(aN->random->val);
    //         }
    //         mpR[aN->random] = newR; // Storing new Random pointer w.r.t old Random pointer

    //         newN->random = newR;
    //         bN->next = newN;

    //         aN = aN->next;
    //         bN = bN->next;
    //     }

    //     return newHead->next;
    // }

    // Optimal approach: avoids extra space
    // Idea: Instead of keeping original-duplicate mapping in a map,
    //       attach the duplicate nodes to the next of the original nodes
    // Time: O(3N)
    // Space: O(1)
    Node *copyRandomList(Node *head)
    {

        Node *tmp = head;
        Node *next, *preN;
        Node *ans;

        // O(N)
        // creates duplicate nodes and places next to the original nodes
        while (tmp != NULL)
        {
            next = tmp->next;
            Node *newN = new Node(tmp->val);
            tmp->next = newN;
            newN->next = next;
            tmp = next;
        }

        tmp = head;
        // O(N)
        // populate the random pointers of all the nodes with the duplicate nodes' pointers
        while (tmp != NULL)
        {
            if (tmp->random != NULL)
            {
                tmp->next->random = tmp->random->next;
            }
            tmp = tmp->next->next;
        }

        ans = new Node(0);
        preN = ans;
        tmp = head;
        // O(N)
        // From one LL making two seperate LL
        while (tmp != NULL && tmp->next != NULL)
        {
            next = tmp->next->next; // Get the next node of Original LL

            preN->next = tmp->next; // Linking the Duplicate LL prev node
            preN = tmp->next;       // Moving forward the duplicate LL pointer to the nextDuplicate node

            tmp->next = next; // restoring Original LL by skipping the duplicate node in between two originals
            tmp = next;       // Moving forward the Original LL pointer to the next original node
        }

        return ans->next;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}