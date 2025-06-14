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

https://takeuforward.org/data-structure/reverse-linked-list-in-groups-of-size-k/
https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/1663052367/

Problem statement:
Given the head of a singly linked list of `n` nodes and an integer `k`, where k is less than or equal to `n`.
Your task is to reverse the order of each group of `k` consecutive nodes, if `n` is not divisible by `k`,
then the last group of remaining nodes should remain unchanged.


Examples:

Example 1:
Input Format:
LL: 1  2  3  4  5  6  7  8  9  10
K = 3
Output: 3  2  1  6  5  4  9  8  7  10
Explanation:
Group 1: Reverse nodes 1 -> 2 -> 3 to become 3 -> 2 -> 1.
Group 2: Reverse nodes 4 -> 5 -> 6 to become 6 -> 5 -> 4.
Group 3: Reverse nodes 7 -> 8 -> 9 to become 9 -> 8 -> 7.
Node 10 remains as is since there are no more groups of size K remaining.

Example 2:
Input Format:
LL: 5  4  3  7  9  2
K = 4
Output: 7 3 4 5 9 2
Explanation:
Group 1: Reversed nodes 5 -> 4 -> 3 -> 7 to become 7 -> 3 -> 4 -> 5.
Group 2: Nodes 9 -> 2 remain unchanged as they are not a complete group of size K.

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
    // Optimal approach
    // Note Striver's blog also where it is done in O(2N) but in easier way
    // Time: O(N)
    // Space: O(1)
    ListNode *reverseKGroup(ListNode *head, int k)
    {

        if (head == NULL || head->next == NULL)
            return head;

        ListNode *curHead = head;
        ListNode *lastHead = NULL;
        ListNode *tmp = head;
        ListNode *prevN = nullptr;
        ListNode *nextN;
        bool flag = false;

        while (tmp != NULL)
        {

            for (int i = 1; i <= k; i++)
            {

                if (tmp == NULL)
                {
                    tmp = prevN;
                    prevN = nullptr;
                    while (tmp != NULL)
                    {
                        nextN = tmp->next;
                        tmp->next = prevN;
                        prevN = tmp;
                        tmp = nextN;
                    }
                    lastHead->next = curHead;
                    return head;
                }
                else
                {
                    nextN = tmp->next;
                    tmp->next = prevN;
                    prevN = tmp;
                    tmp = nextN;
                }
            }

            if (!flag)
            { // One time only
                head = prevN;
                flag = true;
            }

            if (lastHead != NULL)
                lastHead->next = prevN;
            lastHead = curHead;

            curHead = tmp;
            prevN = nullptr; // reset
        }

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}