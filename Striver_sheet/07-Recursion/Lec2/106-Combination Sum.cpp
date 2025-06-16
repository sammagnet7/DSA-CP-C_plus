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

Combination Sum - 1:
(Given array of distinct integers and same number may be chosen from candidates an unlimited number of times):

https://takeuforward.org/data-structure/combination-sum-1/
https://leetcode.com/problems/combination-sum/description/


Problem statement:
Given an array of distinct integers and a target, you have to return the list of all unique combinations where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from the given array an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.


Examples:

Example 1:
Input: array = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation: 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
             7 is a candidate, and 7 = 7.
             These are the only two combinations.


Example 2:
Input: array = [2], target = 1
Output: []
Explaination: No combination is possible.


INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------
Combination Sum II:
(Given array may have duplicates and Each number in candidates may only be used once in the combination)

https://takeuforward.org/data-structure/combination-sum-ii-find-all-unique-combinations/
https://leetcode.com/problems/combination-sum-ii/description/


Problem statement:
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
Each number in candidates may only be used once in the combination.
Note: The solution set must not contain duplicate combinations.


Examples:

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output:
[
[1,2,2],
[5]
]


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Combination Sum - 1:

    // O(2^target * N)
    void recursiveCombSum(vector<vector<int>> &ans, vector<int> &inputs, vector<int> &comb, int target, int prevSum, int idx)
    {

        if (prevSum > target) // Base case used when recursing with same index
            return;

        if (idx == inputs.size())
        {
            if (prevSum == target)
                ans.push_back(comb);
            return;
        }

        int cur = inputs[idx];

        comb.push_back(cur);
        recursiveCombSum(ans, inputs, comb, target, (prevSum + cur), (idx)); // Recurse with same index
        comb.pop_back();

        recursiveCombSum(ans, inputs, comb, target, (prevSum), (idx + 1)); // Recurse not picking cur elem
    }

    // Optimal approach: Using Backtracking
    // At each index either can be picked up or not
    // As duplicates allowed so try with same index iteratively until vector size reaches
    // Time: O(2^target * N): Because of the case when `1` is there and can be repeated `target` times
    // + vector of size N push_back time
    // Space: O(k*x) where `k` is avg combination length and `x` is #combinations found, ignoring stack space
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> comb;
        recursiveCombSum(ans, candidates, comb, target, 0, 0);
        return ans;
    }

    // ---------------------------------------------
    // Combination Sum - 2:
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
