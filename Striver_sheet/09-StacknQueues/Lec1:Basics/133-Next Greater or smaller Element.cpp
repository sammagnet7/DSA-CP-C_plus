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

1. Title: Next Greater Element I

Links:
https://www.youtube.com/watch?v=7PrncD7v9YQ
https://leetcode.com/problems/next-greater-element-i/description/


Problem statement:
The next greater element of some element x in an array is the first greater element that is to the right of x in the same array.
You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of nums2.
For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for this query is -1.
Return an array ans of length nums1.length such that ans[i] is the next greater element as described above.



Example 1:
    Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
    Output: [-1,3,-1]
    Explanation: The next greater element for each value of nums1 is as follows:
    - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
    - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
    - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.

Example 2:
    Input: nums1 = [2,4], nums2 = [1,2,3,4]
    Output: [3,-1]
    Explanation: The next greater element for each value of nums1 is as follows:
    - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
    - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.


Constraints:
    1 <= nums1.length <= nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 104
    All integers in nums1 and nums2 are unique.
    All the integers of nums1 also appear in nums2.



INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
2. Title: Next Greater Element II

Links:
https://takeuforward.org/data-structure/next-greater-element-using-stack/
https://leetcode.com/problems/next-greater-element-ii/description/


Problem statement:
Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

Example 1:
    Input: nums = [1,2,1]
    Output: [2,-1,2]
    Explanation: The first 1's next greater number is 2;
    The number 2 can't find next greater number.
    The second 1's next greater number needs to search circularly, which is also 2.

Example 2:
    Input: nums = [1,2,3,4,3]
    Output: [2,3,4,-1,4]



INPUT::::::


OUTPUT::::::


-----------------------------------------------------------------------
3. Title: Next Smaller Element

Links:
https://www.naukri.com/code360/problems/next-greater-element_1112581?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array 'ARR' of integers of length N. Your task is to find the next smaller element for each of the array elements.
Next Smaller Element for an array element is the first element to the right of that element which has a value strictly smaller than that element.
If for any array element the next smaller element does not exist, you should print -1 for that array element.

For Example:
If the given array is [ 2, 3, 1], we need to return [1, 1, -1]. Because for  2, 1 is the Next Smaller element. For 3, 1 is the Next Smaller element and for 1, there is no next smaller element hence the answer for this element is -1.


INPUT::::::


OUTPUT::::::


*/

//-----------------------------------------------------------------------
// 1. Title: Next Greater Element I
//

// Optimal approach: Using Monotonic stack
// Time:  O(2N)
// Space: O(2N)
vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
{

    int N = nums2.size();
    unordered_map<int, int> ngeMP; // O(N) space
    vector<int> ans;

    stack<int> st; // O(N) space

    for (int i = N - 1; i >= 0; i--)
    { // O(N) time

        int cur = nums2[i];
        bool ngeExists = false;

        while (!st.empty())
        { // Amortized time for N loops: O(N)

            if (st.top() > cur)
            {
                ngeMP[cur] = st.top();
                st.push(cur);
                ngeExists = true;
                break;
            }
            else
            {
                st.pop();
            }
        }

        if (ngeExists)
        {
            continue;
        }
        else
        {
            ngeMP[cur] = -1;
            st.push(cur);
        }
    }

    for (int num : nums1)
    { // O(N)
        ans.push_back(ngeMP[num]);
    }

    return ans;
}

//-----------------------------------------------------------------------
// 2. Title: Next Greater Element II
//

// Approach: Using monotonic stack + copying the array physically
// Time: O(4N)
// SPace: O(4N)
// vector<int> nextGreaterElements(vector<int>& nums) {

//     int N = nums.size();

//     vector<int> ans(nums);
//     ans.insert(ans.end(), nums.begin(), nums.end());    // Space: O(2N)

//     stack<int> st; // Space: O(2N)

//     // O(2N)
//     for(int i=2*N-1; i>=0; i--){

//         int cur = ans[i];
//         ans[i] = -1;

//         while(!st.empty() && cur>=st.top()){
//             st.pop();
//         }

//         if(!st.empty()){
//             ans[i] = st.top();
//         }

//         st.push(cur);
//     }

//     ans.resize(N);

//     return ans;
// }

// Optimal approach: Using monotonic stack + looping the array twice
// Time: O(4N)
// Space: O(2N)
vector<int> nextGreaterElements(vector<int> &nums)
{
    int N = nums.size();

    vector<int> ans(N); // O(N) space
    stack<int> st;      // O(N) space

    // time: O(2N)
    for (int i = 2 * N - 1; i >= 0; i--)
    {

        int curIdx = i % N;
        int cur = nums[curIdx];
        ans[curIdx] = -1;

        while (!st.empty() && cur >= st.top())
        { // Amortized time for 2N loops: O(2N)
            st.pop();
        }

        if (!st.empty())
        {
            ans[curIdx] = st.top();
        }

        st.push(cur);
    }

    return ans;
}

//-----------------------------------------------------------------------
// 3. Title: Next Smaller Element
//

// Optimal approach : Using monotonic stack
// Time: O(2N)
// Space: O(N + N) : stack ds space + `ans` space
vector<int> nextSmallerElement(vector<int> &arr, int n)
{
    // Write your code here.

    vector<int> ans(n); // O(N)
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    { // O(N)

        int cur = arr[i];
        ans[i] = -1;

        while (!st.empty() && cur <= st.top())
        { // Amortized to O(N) after N times looping
            st.pop();
        }

        if (!st.empty())
        {
            ans[i] = st.top();
        }

        st.push(cur);
    }

    return ans;
}

int main()
{
    return 0;
}
