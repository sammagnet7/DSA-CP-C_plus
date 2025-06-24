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

1. Title: Implement Min Stack

Links:
https://takeuforward.org/data-structure/implement-min-stack-o2n-and-on-space-complexity/
https://leetcode.com/problems/min-stack/

Problem statement:
Implement Min Stack | O(2N) and O(N) Space Complexity. Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Examples:

Input Format:["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"]
[
[ ], [-2], [0], [-3], [ ], [ ], [ ], [ ]
]

Result: [null, null, null, null, -3, null, 0, -2]
Explanation:
stack < long long > st
st.push(-2); Push element in stack
st.push(0); Push element in stack
st.push(-3); Push element in stack
st.getMin(); Get minimum element fromstack
st.pop(); Pop the topmost element
st.top(); Top element is 0
st.getMin(); Minimum element is -2




INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Implement Min Stack

// Another sub-optimal approach: In stack with value save `till now min value` as well in O(2N)

// Optimal approach: 
// Time: O(1) 
// Space: O(N); stack space
class MinStack
{
public:
    stack<long long> st;
    long long minV;

    MinStack()
    {
    }

    // O(1)
    void push(int val)
    {

        if (this->st.empty())
        { // If stack is empty push cur val and update min
            this->st.push(val);
            minV = val;
        }
        else
        {
            if (val >= minV)
                st.push(val);
            else
            { // when cur val is less than minV
                long long modV = 2 * (long long)val - minV;
                st.push(modV); // push modified value into stack
                minV = val;    // update min value var
            }
        }
    }

    // O(1)
    void pop()
    {

        if (st.top() > minV)
            st.pop();
        else
        {
            long long modVal = st.top();
            st.pop();
            minV = (2 * minV) - modVal;
        }
    }

    // O(1)
    int top()
    {
        if (st.top() >= minV) // when stack top is greater than min value
            return st.top();  // stack top has original value
        else                  // when stack top is lesser than min value
            return minV;      // stack top having modified value, min var is holding the actual value
    }

    // O(1)
    int getMin()
    {
        return minV;
    }
};

int main()
{
    return 0;
}
