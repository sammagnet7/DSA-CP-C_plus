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

using namespace std;

/*
Linked List Cycle:
https://takeuforward.org/data-structure/detect-a-cycle-in-a-linked-list/
https://leetcode.com/problems/linked-list-cycle/submissions/1656523475/

--------------------------------------------------------

Linked list find starting Node of the cycle:
https://takeuforward.org/data-structure/starting-point-of-loop-in-a-linked-list/
https://leetcode.com/problems/linked-list-cycle-ii/submissions/1656859563/

--------------------------------------------------------

Length of Loop in Linked List:
https://takeuforward.org/linked-list/length-of-loop-in-linked-list
https://www.naukri.com/code360/problems/find-length-of-loop_8160455?leftPanelTabValue=SUBMISSION


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
    // -------------------------------------------------------
    // Brute force approach: Using Map
    // Time: O(N Log N)
    // Space: O(N)
    // bool hasCycle(ListNode *head) {

    //     if(head==NULL || head->next==NULL) return false;

    //     unordered_set<ListNode*> st;
    //     bool isUnique = true;

    //     while(head != NULL){
    //         isUnique = st.insert(head).second;  // returns false if duplicate found

    //         if(!isUnique) return true;

    //         head = head->next;
    //     }

    //     return false;
    // }

    // Optimal approach: Tortoise-Hare approach
    // Time: O(N)
    // Space: O(1)
    bool hasCycle(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return false;

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow)
                return true;
        }

        return false;
    }

    // -------------------------------------------------------
    // Brute force
    // Time: O(N) ~ O(N^2)
    // Space: O(N)
    // ListNode *detectCycle(ListNode *head)
    // {
    //     if (head == NULL || head->next == NULL)
    //         return NULL;

    //     unordered_set<ListNode *> st;
    //     bool isUnique = true;

    //     while (head != NULL && head->next != NULL)
    //     {

    //         isUnique = st.insert(head).second;

    //         if (!isUnique)
    //             return head;

    //         head = head->next;
    //     }

    //     return NULL;
    // }

    // Optimal approach: Tortoise-Hare method
    // `slow` will advance one step at a time, while `fast` will advance two steps at a time.
    // If slow and fast meets->indicates cycle exists
    // If cycle exists, Reset the `slow` pointer to the head
    // Move `fast` and `slow` one step at a time until they meet again.
    // The point where they meet again is the starting point.
    // Time: O(N)
    // Space: O(1)
    ListNode *detectCycle(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return NULL;

        ListNode *slow = head;
        ListNode *fast = head;

        bool isCyclic = false;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow)
            {
                slow = head;
                isCyclic = true;
                break;
            }
        }

        if (isCyclic)
        {
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }

            return slow;
        }

        return NULL;
    }

    // -------------------------------------------------------
    // Optimal approach: Tortoise-Hare method
    // Time: O(N)
    // Space: O(1)
    int lengthOfLoop(ListNode *head)
    {

        if (head == NULL || head->next == NULL)
            return 0;

        bool isCyclic = false;
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (slow == fast)
            {
                isCyclic = true;
                break;
            }
        }

        if (isCyclic)
        {
            slow = slow->next;
            int dist = 1;

            // Count the length of the loop
            while (fast != slow)
            {
                slow = slow->next;
                dist++;
            }

            return dist;
        }
        else
            return 0;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}