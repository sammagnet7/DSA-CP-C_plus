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
Sort a Linked List:

https://takeuforward.org/linked-list/sort-a-linked-list
https://leetcode.com/problems/sort-list/submissions/1660509599/


Problem statement:
Given the head of a linked list, return the list after sorting it in ascending order.
Note: Do it in O(N Log N) time and O(1) space

Example:

Example 1:
Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:
Input: head = []
Output: []


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------

Sort a LL of 0's 1's and 2's:
https://www.naukri.com/code360/problems/sort-linked-list-of-0s-1s-2s_1071937?leftPanelTabValue=PROBLEM

Problem statement
Given a linked list of 'N' nodes, where each node has an integer value that can be 0, 1, or 2. You need to sort the linked list in non-decreasing order and the return the head of the sorted list.

Example:
Given linked list is 1 -> 0 -> 2 -> 1 -> 2. 
The sorted list for the given linked list will be 0 -> 1 -> 1 -> 2 -> 2.


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

// ---------------------------------------------------------------------------
    // Sort a Linked List:

    // Brute force: Convert LL to Array and sort
    // Time: O(N Log N)
    // Space: O(N)
    // ListNode* sortList(ListNode* head) {

    //     ListNode* tmp = head;
    //     vector<int> arr;

    //     // o(N)
    //     while(tmp!=NULL){
    //         arr.push_back(tmp->val);
    //         tmp = tmp->next;
    //     }

    //     sort(arr.begin(), arr.end()); // O(N Log N)

    //     tmp = head;
    //     for(int i: arr){
    //         tmp->val = i;
    //         tmp = tmp->next;
    //     }

    //     return head;
    // }

    // Helper method: O(N)
    ListNode *merge(ListNode *headL, ListNode *headR)
    {

        ListNode *head = new ListNode();
        ListNode *tmp = head;

        while (headL != NULL && headR != NULL)
        {
            if (headL->val <= headR->val)
            {
                tmp->next = headL;
                tmp = tmp->next;
                headL = headL->next;
            }
            else
            {
                tmp->next = headR;
                tmp = tmp->next;
                headR = headR->next;
            }
        }

        if (headL != NULL)
        {
            tmp->next = headL;
        }

        if (headR != NULL)
        {
            tmp->next = headR;
        }

        tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete (tmp);

        return head;
    }

    ListNode *mergeSort(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return head;

        ListNode *slow = head;
        ListNode *fast = head->next->next;

        // at the end of this loop `slow` pointer will point to the node just before the middle node
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode *midN = slow->next;
        slow->next = nullptr;

        ListNode *leftLL = mergeSort(head);
        ListNode *rightLL = mergeSort(midN);

        return merge(leftLL, rightLL);
    }

    // Optimal approach: Using Merged sort on LL : in-place
    // Time: O(N Log N)
    // Space: O(1)
    ListNode *sortList(ListNode *head)
    {
        return mergeSort(head);
    }

//  -------------------------------------------------------------------------
    // Sort a LL of 0's 1's and 2's:

    // Optimal approach: create 3 LL each for 0s, 1s and 2s
    // Time: O(N)
    // Space: O(1)
    ListNode *sortList(ListNode *head)
    {
        ListNode *headZero = new ListNode();
        ListNode *headOne = new ListNode();
        ListNode *headtwo = new ListNode();

        ListNode *tempZero = headZero;
        ListNode *tempOne = headOne;
        ListNode *temptwo = headtwo;

        while (head != NULL)
        {

            if (head->val == 0)
            {
                tempZero->next = head;
                tempZero = tempZero->next;
            }
            else if (head->val == 1)
            {
                tempOne->next = head;
                tempOne = tempOne->next;
            }
            else if (head->val == 2)
            {
                temptwo->next = head;
                temptwo = temptwo->next;
            }

            head = head->next;
        }

        tempZero->next = headOne->next;
        tempOne->next = headtwo->next;
        temptwo->next = nullptr;

        return headZero->next;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}