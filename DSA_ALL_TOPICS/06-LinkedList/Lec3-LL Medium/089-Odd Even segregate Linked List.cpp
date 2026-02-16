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
Segregate even and odd nodes in LinkedList:
https://takeuforward.org/data-structure/segregate-even-and-odd-nodes-in-linkedlist
https://leetcode.com/problems/odd-even-linked-list/submissions/1658542974/

Problem statement:
Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.
The first node is considered odd, and the second node is even, and so on.
Note that the relative order inside both the even and odd groups should remain as it was in the input.
You must solve the problem in O(1) extra space complexity and O(n) time complexity.

Example:

Example 1:
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]

Example 2:
Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]

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
    // -------------------------------------------------------
    // Optimal approach: Maintain 2 seperate LL for odd and even only using different pointers
    // TIme: O(N)
    // Space: O(1)
    ListNode *oddEvenList(ListNode *head)
    {

        if (head == NULL || head->next == NULL || head->next->next == NULL)
            return head;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *evenHead = even;

        ListNode *temp = head->next->next;

        int count = 3;
        while (temp != NULL)
        {

            if (count % 2 == 0)
            { // even
                even->next = temp;
                even = even->next;
            }
            else
            { // odd
                odd->next = temp;
                odd = odd->next;
            }

            temp = temp->next;
            count++;
        }

        even->next = nullptr;
        odd->next = evenHead;

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}