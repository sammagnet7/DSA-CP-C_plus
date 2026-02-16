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
1. Given array of **distinct** integers.
2. same number may be chosen from candidates an **unlimited** number of times.
3. The solution set must not contain duplicate combinations

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
1. Given array may have **duplicates.**
2. Each number in candidates may only be used **once** in the combination.
3. The solution set must not contain duplicate combinations

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

-------------------------------------------------------------------------------

Combination Sum III:

1. Given array may have **duplicates.**
2. The solution set must not contain duplicate combinations
3. Solution must be of given length

https://leetcode.com/problems/combination-sum-iii/description/


Problem statement:
Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

Examples:

Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Explanation:
1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:
Input: k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
Explanation:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.

Example 3:
Input: k = 4, n = 1
Output: []
Explanation: There are no valid combinations.
Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.

Example 4:
Input: k = 9, n = 45
Output: [[1,2,3,4,5,6,7,8,9]]

INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    // ---------------------------------------------
    // Combination Sum - 1:
    // 1. Given array of **distinct** integers.
    // 2. same number may be chosen from candidates an **unlimited** number of times.
    // 3. The solution set must not contain duplicate combinations

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
    // Time: O(2^target * K): Because of the case when `1` is there and can be repeated `target` times
    // + vector of size `K` push_back time where `k` is avg combinations' length
    // Space: O(k*x) i.e `ans` space where `k` is avg combinations` length and `x` is #combinations found, ignoring recursion stack space
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> comb;
        recursiveCombSum(ans, candidates, comb, target, 0, 0);
        return ans;
    }

    // ---------------------------------------------
    // Combination Sum II:
    // 1. Given array may have **duplicates.**
    // 2. Each number in candidates may only be used **once** in the combination.
    // 3. The solution set must not contain duplicate combinations

    // O(2^N * K)
    void recursiveCombSum(vector<vector<int>> &ans, vector<int> &inputs, vector<int> &comb, int target, int prevSum, int idx)
    {

        if (prevSum > target)
            return;
        if (prevSum == target)
        {
            ans.push_back(comb);
            return;
        }
        if (idx == inputs.size())
            return;

        // 1. This loop one by one selects each element in the `input` array.
        // 2. Calls recursively with the next element of the array.
        // 3. As the normal recursion tree here always allows the `first entry`
        //    and all the `input` array elements get its chance once by default.
        // 4. Skipping the duplicate elements from the loop
        //      ignores duplication of the combinations by not allowing same element to be considered for the same index again
        for (int i = idx; i < inputs.size(); i++)
        {

            if (inputs[i] > target)
                break; // As sorted array, simply optimize time

            if (i > idx && inputs[i - 1] == inputs[i]) // allows  `first entry`, then further checks for duplicates
                continue;

            comb.push_back(inputs[i]);
            recursiveCombSum(ans, inputs, comb, target, (prevSum + inputs[i]), (i + 1)); // Note: here passing `i` not `idx`
            comb.pop_back();
        }
    }

    // Optimal approach: backtracking combination with Iteration: see comments in the method
    // Time: O(2^N * K) where `N` is size of input array and `k` is avg combination length
    // Space: O(k*x) where `x` is possible combinations in the `ans`
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> comb;

        sort(candidates.begin(), candidates.end()); // Needed so that we can eleminate duplicates later

        recursiveCombSum(ans, candidates, comb, target, 0, 0);
        return ans;
    }

    // ---------------------------------------------
    // Combination Sum III:
    // 1. Given array may have **duplicates.**
    // 2. The solution set must not contain duplicate combinations
    // 3. Solution must be of given length

    // O(2^N * 3)
    void recursiveCombSum(vector<vector<int>> &ans, vector<int> &inputs, vector<int> &comb, int target, int length, int prevSum, int idx)
    {
        // Check if `combinations` vector size reaches given length limit
        if (comb.size() == length && prevSum == target)
        {
            ans.push_back(comb);
            return;
        }

        // 1. This loop one by one selects each element in the `input` array.
        // 2. Calls recursively with the next element of the array.
        // 3. As the normal recursion tree here always allows the `first entry`
        //    and all the `input` array elements get its chance once by default.
        // 4. Skipping the duplicate elements from the loop
        //      ignores duplication of the combinations by not allowing same element to be considered for the same index again
        for (int i = idx; i < inputs.size(); i++)
        {

            if (inputs[i] > target)
                break; // For more optimization: As sorted array

            if (i > idx && inputs[i - 1] == inputs[i]) // allows  `first entry`, then further checks for duplicates
                continue;

            comb.push_back(inputs[i]);
            recursiveCombSum(ans, inputs, comb, target, length, (prevSum + inputs[i]), (i + 1)); // Note: here passing `i` not `idx`
            comb.pop_back();
        }
    }

    // Optimal approach: Recursion + Iteration
    // TIme: O(2^N * 3)
    // Space: O(3 * x) where x is the number of combinations in `ans`
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> ans;
        vector<int> comb;
        vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        recursiveCombSum(ans, candidates, comb, n, k, 0, 0);
        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
