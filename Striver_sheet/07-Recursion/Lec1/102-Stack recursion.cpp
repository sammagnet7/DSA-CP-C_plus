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
Sorting the stack recursively:
https://www.naukri.com/code360/problems/sorting-the-stack-recursively_1868989?leftPanelTabValue=PROBLEM

Problem statement:
sort the stack recursively.
1. Looping through the stack is not allowed.
2. You need to return a stack that is sorted in descending order.


Examples:

Sample Input 1 :
2
4
8 5 9 7
5
33 2 5 1 4
Sample Output 1 :
9 7 8 5
33 5 4 2 1

Explanation of the Sample Input 1:
For the first test case:
For the given stack, the resultant sorted stack would be 5 8 7 9.

For the second test case:
For the given stack, the resulting sorted stack would be 1 2 4 5 33.

Sample Input 2 :
2
4
1 2 3 4
3
5 1 2
Sample Output 2 :
4 3 2 1
5 2 1


---------------------------------------------------------------------------------------------------

Reverse Stack Using Recursion:
https://www.naukri.com/code360/problems/reverse-stack-using-recursion_631875?leftPanelTabValue=PROBLEM

Problem statement:
Reverse a given stack of 'N' integers using recursion. You are required to make changes in the input parameter itself.
Note: You are not allowed to use any extra space other than the internal stack space used due to recursion.

Examples:

Sample Input 1 :
3
2 1 3
Sample Output 1 :
3 1 2

Explanation to Sample Input 1 :
Reverse of a give stack is 3 1 2 where first element becomes last and last becomes first.

Sample Input 2 :
2
3 2
Sample Output 2 :
2 3


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------

    int recurseStack(stack<int> &s, int prev)
    {

        int cur, next, ret;

        cur = s.top();
        s.pop();

        if (prev >= cur)
        {
            next = cur;
            prev = prev;
        }
        else if (prev < cur)
        {
            next = prev;
            prev = cur;
        }

        if (!s.empty())
            ret = recurseStack(s, next);
        else
            ret = next;

        s.push(ret);

        return prev;
    }

    void helperStack(stack<int> &s, int count)
    {

        if (count == 0)
            return;

        recurseStack(s, INT_MAX);

        helperStack(s, --count);
    }

    // Approach: Bubble sort using recursion
    // Time: O(N^2)
    // Space: O(N) i.e. stack space
    stack<int> sortStack(stack<int> &s)
    {
        helperStack(s, s.size());

        return s;
    }

    // ----------------------------------------------------------------------------------

    // helper function for extracting the stack bottom element to the top
    int extractBottom(stack<int> &stack, int prev)
    {

        int ret;
        int cur = stack.top();
        stack.pop();

        if (stack.empty())
        {
            stack.push(prev);
            return cur;
        }

        ret = extractBottom(stack, cur);

        stack.push(prev);

        return ret;
    }

    // Optimal approach: Bubble up the bottom ellement to the top
    // Time : O(N^2)
    // Space: O(N) i.e. for recursion stack length
    void reverseStack(stack<int> &stack)
    {

        int topV = stack.top();
        stack.pop();

        if (stack.empty())
        {
            stack.push(topV);
            return;
        }

        int topRet = extractBottom(stack, topV);

        reverseStack(stack);

        stack.push(topRet);
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
