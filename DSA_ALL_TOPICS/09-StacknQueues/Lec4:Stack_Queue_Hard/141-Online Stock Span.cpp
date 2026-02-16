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
#include <string.h>

using namespace std;

/*

1. Title: Online Stock Span

Links:
https://takeuforward.org/plus/dsa/problems/stock-span-problem?tab=editorial
https://leetcode.com/problems/online-stock-span/description/

Problem statement:
Design an algorithm that collects daily price quotes for some stock and returns the span of that stock's price for the current day.
The span of the stock's price in one day is the maximum number of consecutive days (starting from that day and going backward) for which the stock price was less than or equal to the price of that day.
For example, if the prices of the stock in the last four days is [7,2,1,2] and the price of the stock today is 2, then the span of today is 4 because starting from today, the price of the stock was less than or equal 2 for 4 consecutive days.
Also, if the prices of the stock in the last four days is [7,34,1,2] and the price of the stock today is 8, then the span of today is 3 because starting from today, the price of the stock was less than or equal 8 for 3 consecutive days.
Implement the StockSpanner class:

StockSpanner() Initializes the object of the class.
int next(int price) Returns the span of the stock's price given that today's price is price.
 

Example 1:
Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]
Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
stockSpanner.next(85);  // return 6


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Online Stock Span
//

class StockSpanner
{
public:
    vector<int> prices;
    stack<int> st;

    StockSpanner() : prices(vector<int>()), st(stack<int>())
    {
    }

    // Optimal approach: Using Monotonic stack and finding pse (prev-smaller elem)
    // Time: O(2N): after N calls made : N times calls made + max N times pop up
    // Space: O(2N): N vector + N stack space
    int next(int price)
    {

        prices.push_back(price);

        while (!st.empty() && prices[st.top()] <= price)
        { // Overall O(N) after N calls because max N elements can be popped up.
            st.pop();
        }

        int cur_idx = prices.size() - 1;
        int pge_idx = st.empty() ? -1 : st.top();

        st.push(cur_idx);

        return (cur_idx - pge_idx);
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

int main()
{
    return 0;
}
