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

1. Title: Sliding Window Maximum

Links:
https://takeuforward.org/data-structure/sliding-window-maximum/
https://takeuforward.org/plus/dsa/problems/sliding-window-maximum?tab=editorial
https://www.youtube.com/watch?v=NwBvene4Imo&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=17
https://leetcode.com/problems/sliding-window-maximum/description/

Problem statement:
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the max sliding window.

Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

Example 2:
Input: nums = [1], k = 1
Output: [1]


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Sliding Window Maximum
//
class Solution
{
public:
    // Optimal approach: Uses Monotonic stack and deque
    // Here we maintain the stack in decreasing order so that once the max is popped we can find the next max
    // We use back of the deque to maintain decreasing order
    // And the front of the deque to get the max element in O(1)
    //
    // Time: O(2N): input traversal + stack pop loop
    // SPace: O(K+(N-k)): K for stack space + (N-k) for ans vector
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {

        int N = nums.size();
        vector<int> ans;

        deque<int> dq; // O(K) stores index in decreasing order of values from front to back

        for (int i = 0; i < N; i++)
        { // O(N)

            while (!dq.empty() && nums[dq.back()] < nums[i])
            { // O(N)
                dq.pop_back();
            }
            dq.push_back(i);

            if (i >= (k - 1))
            { // means reached the window size
                while (!dq.empty() && (i - dq.front()) >= k)
                { // pop elements which are out of window
                    dq.pop_front();
                }
                ans.push_back(nums[dq.front()]);
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}
