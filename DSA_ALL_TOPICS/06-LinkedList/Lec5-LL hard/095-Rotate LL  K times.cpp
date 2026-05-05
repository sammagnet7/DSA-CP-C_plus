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
https://leetcode.com/problems/rotate-list/description/


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

//--------------
// Approach : 1
//--------------
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

/**
 * ============================================================================
 * Approach 2: Circular Linked List + Modulo Math   [RECOMMENDED]
 * ============================================================================
 * Logic:
 * 1. Find the length of the list and locate the tail node.
 * 2. Connect the tail to the head to form a circular ring.
 * 3. Find the actual number of rotations needed using k % N.
 * 4. Traverse to the (N - k % N)th node, which will become our new tail.
 * 5. Break the circle and return the new head.
 * ============================================================================
 * Complexity:
 * - Time: O(N). We traverse the list once to find the length, and partially
 *   traverse it again to find the cut point. Total steps <= 2N.
 * - Space: O(1). We only allocate a few pointers, modifying the list in-place.
 * ============================================================================
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        // Defensive Engineering: Handle edge cases instantly
        if (!head || !head->next || k == 0)
        {
            return head;
        }

        // Step 1: Find the length (N) and the original tail node
        int len = 1;
        ListNode *tail = head;
        while (tail->next)
        {
            len++;
            tail = tail->next;
        }

        // Step 2: Calculate effective rotations to bypass the 2 * 10^9 constraint
        int effective_k = k % len;
        if (effective_k == 0)
        {
            return head; // List returns to original state
        }

        // Step 3: Connect tail to head to form a circular ring
        tail->next = head;

        // Step 4: Find the new tail
        // If we rotate right by effective_k, the new tail is at index (len - effective_k - 1)
        ListNode *new_tail = head;
        int steps_to_new_tail = len - effective_k - 1;

        for (int i = 0; i < steps_to_new_tail; ++i)
        {
            new_tail = new_tail->next;
        }

        // Step 5: Define the new head and sever the ring
        ListNode *new_head = new_tail->next;
        new_tail->next = nullptr;

        return new_head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}