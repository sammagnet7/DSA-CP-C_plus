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

Power Set: generate all the possible subsequences of the input vector:

https://takeuforward.org/data-structure/power-set-print-all-the-possible-subsequences-of-the-string/
https://leetcode.com/problems/subsets/description/?roomId=klgJbk

Problem statement:
Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Examples:

Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Generate Power Set:

    // O(2^N)
    void recursePowerSet(vector<vector<int>> &ans, vector<int> &input, vector<int> &subset, int inputIdx)
    {

        if (inputIdx == input.size())
        {
            ans.push_back(subset);
            return;
        }

        recursePowerSet(ans, input, subset, (inputIdx + 1));

        subset.push_back(input[inputIdx]);
        recursePowerSet(ans, input, subset, (inputIdx + 1));
        subset.pop_back();
    }

    // optimal approach: recursion/ backtracking
    // Here we are keeping an index of input vector
    // in each recursion step we are calling recursion 2 ways: One with the indexed element and other without
    // And then moving the index forward to the next element in the input vector
    // And finally saving the generated string when index is going outof bounds of the input vector
    // This way all the possible sets are getting generated
    // Time: O(2^N) because each element has two option: either present or not
    // Space: O(N) for recursion stack
    vector<vector<int>> subsets(vector<int> &nums)
    {

        vector<vector<int>> ans;
        vector<int> subset;

        recursePowerSet(ans, nums, subset, 0);

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
