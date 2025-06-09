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
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}