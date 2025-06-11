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
Add 1 to a number represented by LL:

https://www.youtube.com/watch?v=aXQWhbvT3w0&t=1s
https://www.naukri.com/code360/problems/add-one-to-a-number-represented-as-linked-list_920557?leftPanelTabValue=SUBMISSION

Problem statement:
You're given a positive integer represented in the form of a singly linked-list of digits. The length of the number is 'n'.
Add 1 to the number, i.e., increment the given number by one.

Note:
The expected time complexity is O('n').
There are no leading zeroes in the number.

Example:

Sample Input 1:
3
1 5 2
Sample Output 1:
1 5 3
Explanation For Sample Input 1:
Initially the number is 152. After incrementing it by 1, the number becomes 153.

Sample Input 2:
2
9 9
Sample Output 2:
1 0 0
Explanation For Sample Input 2:
Initially the number is 9. After incrementing it by 1, the number becomes 100. Please note that there were 2 nodes in the initial linked list, but there are three nodes in the sum linked list.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------


*/

class Node
{
public:
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int x) : data(x), next(nullptr) {}
    Node(int x, Node *next) : data(x), next(next) {}
};

class Solution
{
public:
    // ---------------------------------------------------------------------------
    // Add 1 to a number represented by LL:
    // Better approach: Reverse LL -> add 1 and ripple carry -> Reverse again
    // Time: O(3N)
    // Space: O(1)

    // // Reverse LL in O(N)
    // Node *revSingLL(Node *head)
    // {

    //     Node *tmp = head;
    //     Node *pre = NULL;

    //     while (tmp != NULL)
    //     {
    //         Node *next = tmp->next;
    //         tmp->next = pre;
    //         pre = tmp;
    //         tmp = next;
    //     }

    //     return pre;
    // }

    // // Time: O(3N)
    // // Space: O(1)
    // Node *addOne(Node *head)
    // {
    //     if (head == NULL)
    //         return head;

    //     head = revSingLL(head);
    //     Node *tmp = head;
    //     Node *pre = NULL;

    //     int dig, carry = 1;
    //     while (tmp != NULL)
    //     {

    //         dig = tmp->data;
    //         dig += carry;

    //         if (dig > 9)
    //         {
    //             tmp->data = 0;
    //             carry = 1;
    //         }
    //         else
    //         {
    //             tmp->data = dig;
    //             carry = 0;
    //             break;
    //         }

    //         pre = tmp;
    //         tmp = tmp->next;
    //     }

    //     if (carry == 1)
    //     {
    //         Node *newN = new Node(1);
    //         pre->next = newN;
    //     }

    //     head = revSingLL(head);

    //     return head;
    // }

    // ---------------------------------------------------------------------------
    // Optimal approach: Using Recursion
    // Time: O(N)
    // Space: O(N)

    // Time O(N)
    // Space O(N) for recursion tree
    int addOnetoNode(Node *cur)
    {

        if (cur == NULL)
            return 1;

        int carryRet = addOnetoNode(cur->next);

        int dig = cur->data;
        dig += carryRet;

        if (dig > 9)
        {
            cur->data = 0;
            return 1;
        }
        else
        {
            cur->data = dig;
            return 0;
        }
    }

    // O(N)
    Node *addOne(Node *head)
    {
        if (head == NULL)
            return head;

        int finalCarry = addOnetoNode(head);

        if (finalCarry == 0)
            return head;
        else
        {
            Node *newN = new Node(1);
            newN->next = head;

            return newN;
        }
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}