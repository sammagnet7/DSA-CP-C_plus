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
Check if the given Linked List is Palindrome:
https://takeuforward.org/data-structure/check-if-given-linked-list-is-plaindrome/
https://leetcode.com/problems/palindrome-linked-list/submissions/1657461060/

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
    // Brute force
    // Time: O(2N)
    // Space: O(N)
    // bool isPalindrome(ListNode *head)
    // {
    //     if (head == NULL || head->next == NULL)
    //         return true;

    //     stack<int> st;
    //     ListNode *temp = head;

    //     while (temp != NULL)
    //     {
    //         st.push(temp->val);
    //         temp = temp->next;
    //     }

    //     temp = head;

    //     while (temp != NULL)
    //     {
    //         if (temp->val != st.top())
    //             return false;
    //         st.pop();
    //         temp = temp->next;
    //     }

    //     return true;
    // }

    // Optimal approach: Reverse the 2nd half of LL and compare
    // Time: O(2N)
    // Space: O(1)
    bool isPalindrome(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return true;

        bool isPal = true;

        ListNode *slow = head;
        ListNode *fast = head;

        // Setting the slow pointer onto the mid element in O(N/2)
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode *rightHead = slow;

        // reversing the right half of LL in O(N/2)
        ListNode *tempN = rightHead;
        ListNode *preN = NULL;
        ListNode *NextN = NULL;
        while (tempN != NULL)
        {
            NextN = tempN->next;

            tempN->next = preN;
            preN = tempN;

            tempN = NextN;
        }
        rightHead = preN;

        // Compare and check if non-palindrome in O(N/2)
        ListNode *tempN_L = head;
        ListNode *tempN_R = rightHead;
        while (tempN_R != NULL)
        {

            if (tempN_L->val != tempN_R->val)
            {
                isPal = false;
                break;
            }
            tempN_L = tempN_L->next;
            tempN_R = tempN_R->next;
        }

        // reversing the right half of LL in O(N/2)
        tempN = rightHead;
        preN = NULL;
        NextN = NULL;
        while (tempN != NULL)
        {
            NextN = tempN->next;

            tempN->next = preN;
            preN = tempN;

            tempN = NextN;
        }

        return isPal;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}