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
Rotate List:

https://takeuforward.org/data-structure/rotate-a-linked-list/
https://leetcode.com/problems/rotate-list/submissions/1662639369/


Problem statement:
Given the head of a linked list, rotate the list to the right by k places.

Examples:

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:
Input: head = [0,1,2], k = 4
Output: [2,0,1]

Example 3:
Input: head = [], k = 0
Output: []

Example 4:
Input: head = [1,2,3], k = 2000000000
Output: [2,3,1]

*/

class ListNode
{
public:
    int data;
    ListNode *prev;
    ListNode *next;
    ListNode()
    {
        this->data = 0;
        this->prev = NULL;
        this->next = NULL;
    }
    ListNode(int data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
    ListNode(int data, ListNode *next, ListNode *prev)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
};

class Solution
{
public:
    // ---------------------------------------------------------------------------
    // optimal approach: Use LL length and modulus operator
    // Time: O(2N)
    // Space: O(1)
    ListNode *rotateRight(ListNode *head, int k)
    {

        if (head == NULL || head->next == NULL)
            return head;

        ListNode *front = head;
        ListNode *back = head;

        for (int i = 1; i <= k; i++)
        {
            front = front->next;
            if (front == NULL)
            {
                int llLen = i;
                front = head;
                i = 0;         // here resetting for loop counter to the start
                k = k % llLen; // for k greater than the length of the list
                               // rotate the list for k%length of the list
            }
        }

        while (front->next != NULL)
        {
            back = back->next;
            front = front->next;
        }

        front->next = head;
        head = back->next;
        back->next = nullptr;

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}