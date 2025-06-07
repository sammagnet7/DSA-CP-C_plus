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

Find middle element in a Linked List:
https://takeuforward.org/data-structure/find-middle-element-in-a-linked-list/
https://leetcode.com/problems/middle-of-the-linked-list/submissions/1656289794/

--------------------------------------------------------

Reverse a Linked List:
https://takeuforward.org/data-structure/reverse-a-linked-list/
https://leetcode.com/problems/reverse-linked-list/submissions/1656346430/

--------------------------------------------------------



INPUT::::::


OUTPUT::::::

*/

class ListNode
{
public:
    int data;
    ListNode *next;
    ListNode() : data(0), next(nullptr) {}
    ListNode(int x) : data(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : data(x), next(next) {}
};

class Solution
{
public:
    // --------------------------------------------------------
    // Optimal approach: 'Tortoise-Hare' method
    // Approach:
    // The Tortoise and Hare algorithm leverages two pointers, 'slow' and 'fast', initiated at the beginning of the linked list.
    // The 'slow' pointer advances one node at a time, while the 'fast' pointer moves two nodes at a time.
    // The fast-moving hare reaches the end of the list in exactly the same time it takes for the slow-moving tortoise to reach the middle.
    // Time: O(N/2) ~ O(N)
    // Space: O(1)
    ListNode *middleNode(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return head;

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }

    // --------------------------------------------------------
    // Optimal approach: iterative
    // Time: O(N)
    // Space: O(1)
    ListNode* reverseListIter(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;

        ListNode* cur = head;
        ListNode* curNext = NULL;
        ListNode* tobeNext = NULL;

        while(cur != NULL){
            curNext = cur->next;
            cur->next = tobeNext;
            tobeNext = cur;
            cur = curNext;
        }

        return tobeNext;
    }

    // Optimal approach: Recursive
    // Time: O(N)
    // Space: O(1)
    ListNode *reverseListRec(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)   // Note the base cases here
        {
            return head;
        }

        ListNode *newHead = reverseListRec(head->next);

        head->next->next = head; // Updating the next pointer in the reverse order
        head->next = NULL;       // This makes sure that the tail element's next points to NULL

        return newHead;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}