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
Remove N-th node from the end of a Linked List:

https://takeuforward.org/data-structure/remove-n-th-node-from-the-end-of-a-linked-list/
https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1658970211/


Problem statement:
Given a linked list and an integer N, the task is to delete the Nth node from the end of the linked list and print the updated linked list.
Note: Do it in O(N)

Example:

Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------

Delete the Middle Node of the Linked List:
https://takeuforward.org/linked-list/delete-the-middle-node-of-the-linked-list
https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/submissions/1659382079/

Problem statement:
You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.
The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.
For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.

Examples:

Example 1:
Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]
Explanation:
The above figure represents the given linked list. The indices of the nodes are written below.
Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
We return the new list after removing this node.

Example 2:
Input: head = [1,2,3,4]
Output: [1,2,4]
Explanation:
The above figure represents the given linked list.
For n = 4, node 2 with value 3 is the middle node, which is marked in red.

Example 3:
Input: head = [2,1]
Output: [2]
Explanation:
The above figure represents the given linked list.
For n = 2, node 1 with value 1 is the middle node, which is marked in red.
Node 0 with value 2 is the only node remaining after removing node 1.

Example 4:
Input: head = [1]
Output: []

INPUT::::::


OUTPUT::::::

*/

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    // Optimal solution
    // Here first we increment fast than slow by `n` nodes
    // Then we increment both together until fast reaches the end.
    // At that moment `slow->next` points to the node to be deleted
    // Also special handle is needed for deleting `head` node
    // Time: O(N)
    // Space: O(1)
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *slow = head;
        ListNode *fast = head;

        int count = n; //

        // O(n)
        while (count--)
        {
            fast = fast->next;
        } // Now `fast` pointer is ahead of `slow` pointer by n nodes

        if (fast == NULL)
        { // Handling when the `head` needs to be deleted
            ListNode *newhead = head->next;

            head->next = nullptr;
            delete (head);

            return newhead;
        }

        // O(N-n)   where N is the length of LL
        while (fast->next != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        } // now `slow` points to the node which is of distance `n` from the end node

        // But as count starts from end and the end node itself counts as 1st from end
        ListNode *delN = slow->next;

        slow->next = slow->next->next;

        delN->next = nullptr;
        delete (delN);

        return head;
    }

    //-------------------------------------------------------------------------
    // Optimal approach: Tortoise-Hare approach
    // Time: O(N/2)
    // Space: O(1)
    ListNode *deleteMiddle(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return NULL;

        ListNode *slow = head;
        ListNode *fast = head->next->next;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        // Below commented part is needed if we start as (fast = head)
        // if(slow == head->next && slow->next==NULL){
        //     head->next = NULL;
        //     delete(slow);
        //     return head;
        // }
        // ListNode* tmp = slow->next;
        // slow->val = slow->next->val;
        // slow->next = slow->next->next;
        // tmp->next = nullptr;
        // delete(tmp);

        ListNode *tmp = slow->next;
        slow->next = slow->next->next;
        tmp->next = nullptr;
        delete (tmp);

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}