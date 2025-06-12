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
Delete all occurrences of a given key in a doubly linked list:
https://www.naukri.com/code360/problems/delete-all-occurrences-of-a-given-key-in-a-doubly-linked-list_8160461?leftPanelTabValue=SUBMISSION

Find pairs with given sum in Sorted doubly linked list:
https://www.naukri.com/code360/problems/find-pair-with-a-given-sum-in-a-doubly-linked-list_1164172?leftPanelTabValue=SUBMISSION

Remove duplicates from a sorted Doubly Linked List:
https://www.naukri.com/code360/problems/remove-duplicates-from-a-sorted-doubly-linked-list_2420283?leftPanelTabValue=DISCUSS

*/

class Node
{
public:
    int data;
    Node *prev;
    Node *next;
    Node()
    {
        this->data = 0;
        this->prev = NULL;
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
    Node(int data, Node *next, Node *prev)
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
    // Delete all occurrences of a given key in a doubly linked list:
    // Optimal approach
    // Time: O(N)
    // Space: O(1)
    Node *deleteAllOccurrences(Node *head, int k)
    {

        if (head == NULL)
            return head;
        if (head->next == NULL)
        {
            if (head->data == k)
                return NULL;
            else
                return head;
        }

        Node *tmp = head;

        while (tmp != NULL && tmp->next != NULL)
        {
            if (tmp->data == k)
            {
                if (tmp == head)
                {
                    head = tmp->next;
                    tmp->next->prev = NULL;
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }
            }

            tmp = tmp->next;
        }

        if (tmp->data == k)
        {
            if (tmp == head)
                return NULL; // Note this line
            if (tmp->prev != NULL)
                tmp->prev->next = NULL;
        }

        return head;
    }

    // ---------------------------------------------------------------------------
    // Find pairs with given sum in Sorted doubly linked list:

    // // Better Approach: Using Hash
    // // Time: O(N) as unordered_map and all values are distinct
    // // Space: O(N) for hashmap
    // vector<pair<int, int>> findPairs(Node *head, int k)
    // {
    //     unordered_map<int, int> mp;
    //     vector<pair<int, int>> ans;

    //     Node *tmp = head;
    //     int cur, req;

    //     while (tmp)
    //     {
    //         cur = tmp->data;
    //         req = (k - cur);

    //         if (mp[req] > 0)
    //         {
    //             ans.push_back({cur, req});
    //         }

    //         mp[cur]++;

    //         tmp = tmp->next;
    //     }

    //     return ans;
    // }

    // Optimal approach: As given DLL is sorted -> Use two pointers approach
    // Time: O(N)
    // Space: O(1)
    vector<pair<int, int>> findPairs(Node *head, int k)
    {
        vector<pair<int, int>> ans;

        if (head == NULL || head->next == NULL)
            return ans;

        Node *left = head;
        Node *right = head;

        while (right->next != NULL)
            right = right->next;

        // while(left!=right && left->prev!=right){
        while (left->data < right->data)
        {

            int sum = left->data + right->data;
            if (sum == k)
            {
                ans.push_back({left->data, right->data});
                left = left->next;
                right = right->prev;
            }
            else if (sum < k)
            {
                left = left->next;
            }
            else
            {
                right = right->prev;
            }
        }

        return ans;
    }
    // ---------------------------------------------------------------------------
    // Remove duplicates from a sorted Doubly Linked List:

    // Optimal approach
    // Time: O(N)
    // Space: O(1)
    Node *removeDuplicates(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node *tmp = head;
        int curV = 0;
        int preV = -1;

        while (tmp != NULL && tmp->next != NULL)
        {

            curV = tmp->data;

            if (curV == preV)
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }

            preV = curV;
            tmp = tmp->next;
        }

        // Handling tail node
        if (tmp != NULL)
        {
            if (tmp->data == preV)
            {
                tmp->prev->next = NULL;
            }
        }

        return head;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}