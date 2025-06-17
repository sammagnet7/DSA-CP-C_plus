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

-----------------------------------------------------------------------

Generate all possible UNIQUE subsets:
1. Given input array may contain duplicates
2. Power set must contain all possible unique subsets

https://takeuforward.org/data-structure/subset-ii-print-all-the-unique-subsets/
https://leetcode.com/problems/subsets-ii/description/

Problem Statement:
Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Examples:

Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

Subset Sum : Sum of all Subsets:

https://takeuforward.org/data-structure/subset-sum-sum-of-all-subsets/
https://www.naukri.com/code360/problems/subset-sum_3843086?leftPanelTabValue=PROBLEM

Problem Statement: Given an array print all the sum of the subset generated from it, in the increasing order.

Examples:

Example 1:
Input: N = 3, arr[] = {5,2,1}
Output: 0,1,2,3,5,6,7,8
Explanation: We have to find all the subset’s sum and print them.in this case the generated subsets are [ [], [1], [2], [2,1], [5], [5,1], [5,2]. [5,2,1],so the sums we get will be  0,1,2,3,5,6,7,8

Example 2:
Input: N=3,arr[]= {3,1,2}
Output: 0,1,2,3,3,4,5,6
Explanation: We have to find all the subset’s sum and print them.in this case the generated subsets are [ [], [1], [2], [2,1], [3], [3,1], [3,2]. [3,2,1],so the sums we get will be  0,1,2,3,3,4,5,6


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

    //--------------------------------------------------------------------------
    // Generate all possible UNIQUE subsets:

    // O(2^N * N)
    void recurseUniquePowerSet(vector<vector<int>> &ans, vector<int> &inp, vector<int> &subset, int idx)
    {

        ans.push_back(subset);

        for (int i = idx; i < inp.size(); i++)
        {
            if (i != idx and inp[i] == inp[i - 1])
                continue;

            subset.push_back(inp[i]);
            recurseUniquePowerSet(ans, inp, subset, (i + 1));
            subset.pop_back();
        }
    }

    // Optimal approach: Recursion + Iteration
    // Time:  O(2^N * N) Beacuse 2^Nelements in power set and N is the max length of subset
    // Space: O(2^N * N) for `ans` vector + Auxiliary space is O(n)  if n is the depth of the recursion tree
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        vector<int> subset;

        recurseUniquePowerSet(ans, nums, subset, 0);

        return ans;
    }

    // ---------------------------------------------
    // Sum of all Subsets:

    // O(2^N * 2^N Log (2^N))
    void recurseSubsetSum(vector<int> &ans, vector<int> &input, int idx, int sum)
    {

        if (idx == input.size())
        {
            ans.push_back(sum);
            return;
        }

        recurseSubsetSum(ans, input, (idx + 1), (sum + input[idx]));
        recurseSubsetSum(ans, input, (idx + 1), (sum));
    }

    // Optimal approach: Backtracking
    // Time: O(2^N * 2^N Log (2^N))	because size of the power set is 2^N and sorting is needed
    // Space: O(2^N) where 2^N is the minimum number of subset sums in the `ans`
    vector<int> subsetSum(vector<int> &num)
    {
        vector<int> ans;

        recurseSubsetSum(ans, num, 0, 0);

        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
