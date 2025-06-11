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
Find intersection of Two Linked Lists:

https://takeuforward.org/data-structure/find-intersection-of-two-linked-lists/
https://leetcode.com/problems/intersection-of-two-linked-lists/submissions/1660696832/

Problem statement:
Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null.

Example:

Example 1:
List 1 = [1,3,1,2,4], List 2 = [3,2,4]
Output:
2
Explanation: Here, both lists intersecting nodes start from node 2.

Example 2:
Input:
 List1 = [1,2,7], List 2 = [2,8,1]
Output:
 Null
Explanation: Here, both lists do not intersect and thus no intersection node is present.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------


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
    // Find intersection of Two Linked Lists:
    
    // Optimal approach
    // Idea: First find the length difference between two linked lists
    // Then straverse the extra nodes from starting of the longer list
    // Then traverse both the list together until a same node is found
    // TIme: O(~3N)
    // Space: O(1)
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {

        ListNode *tmpA = headA;
        ListNode *tmpB = headB;

        int countA = 1;
        int countB = 1;

        // O(N)
        while (tmpA->next != NULL && tmpB->next != NULL)
        {
            tmpA = tmpA->next;
            tmpB = tmpB->next;
            countA++;
            countB++;
        }

        while (tmpA->next != NULL)
        {
            tmpA = tmpA->next;
            countA++;
        }

        while (tmpB->next != NULL)
        {
            tmpB = tmpB->next;
            countB++;
        }

        if (tmpA != tmpB)
            return NULL;

        int diff = 0;
        ListNode *dummy1, *dummy2;

        if (countA > countB)
        {
            diff = countA - countB;
            dummy1 = headA;
            dummy2 = headB;
        }
        else
        {
            diff = countB - countA;
            dummy1 = headB;
            dummy2 = headA;
        }

        // O(N)
        while (diff--)
        {
            dummy1 = dummy1->next;
        }

        // O(N)
        while (dummy2 != NULL)
        {
            if (dummy1 == dummy2)
                return dummy1;
            dummy1 = dummy1->next;
            dummy2 = dummy2->next;
        }

        return NULL;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}