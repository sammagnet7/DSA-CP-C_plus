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
    // 1. Generate Power Set:
    // ---------------------------------------------

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
    // 2. Generate all possible UNIQUE subsets:
    //--------------------------------------------------------------------------

    // ===================================================================================
    // Approach 1: Brute Force Backtracking with std::set for Deduplication [sub-optimal]
    // ===================================================================================
    /*
     * IDEA:
     * This method relies on the data structure (`std::set`) to do the heavy
     * lifting. We sort the array to guarantee that identical subsets are generated
     * in the exact same order (e.g., always `[1, 2, 2]`, never `[2, 1, 2]`).
     * Then, we generate EVERY possible subset blindly and insert them into a set.
     * The set automatically discards the duplicates.
     *
     * STEP-BY-STEP APPROACH:
     * 1. Sort the input array `nums`.
     * 2. Start recursion at index 0.
     * 3. Base Case: If `idx` reaches the end, insert `subset` into the `set` `ans`.
     * 4. Branch 1 (Do Not Pick): Recurse to `idx + 1` without adding to `subset`.
     * 5. Branch 2 (Pick): Add `nums[idx]`, recurse to `idx + 1`, and backtrack.
     * 6. In the main function, construct the final `vector<vector<int>>` using
     * the iterators from the `set`.
     *
     * TIME COMPLEXITY:
     * O(N * 2^N * log(2^N)), which simplifies to O(N^2 * 2^N).
     * We blindly generate exactly $2^N$ subsets. For each subset, inserting it
     * into the set takes logarithmic time relative to the set's size, and comparing
     * subsets during insertion takes $O(N)$ time.
     *
     * SPACE COMPLEXITY:
     * O(N * 2^N) to store the subsets in the `std::set`. A set in C++ is
     * typically implemented as a Red-Black Tree, meaning every subset is wrapped
     * in a node with extra pointers (left, right, parent) and a color flag,
     * causing significant memory overhead compared to a flat vector.
     *
     * COMPARISON TO METHOD 1 (Optimized Method):
     * + PROS: The recursive logic is incredibly simple and standard. You don't
     * have to think about duplicate-skipping logic at all; the `set` acts as
     * a safety net.
     * - CONS: Much slower execution time and significantly higher memory footprint.
     * Generating identical branches just to throw them away later is highly
     * inefficient, especially as the input size grows.
     */

    void rec(int idx, vector<int> &nums, vector<int> &subset, set<vector<int>> &ans)
    {

        if (idx == nums.size())
        {
            ans.insert(subset);
            return;
        }

        // Branch 1: DO NOT PICK
        rec(idx + 1, nums, subset, ans);

        // Branch 2: PICK
        subset.push_back(nums[idx]);
        rec(idx + 1, nums, subset, ans);
        subset.pop_back(); // backtrack
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {

        set<vector<int>> ans;
        vector<int> subset;

        // Sorting guarantees subsets are generated with elements in identical order
        sort(nums.begin(), nums.end());
        rec(0, nums, subset, ans);

        // Convert the set back to the required vector format
        return vector<vector<int>>(ans.begin(), ans.end());
    }

    // ============================================================================
    // Approach 2: Optimized Backtracking with Duplicate Pruning [OPTIMAL]
    // ============================================================================
    /*
     * IDEA:
     * This method uses standard backtracking (Pick / Do Not Pick) but actively
     * prunes the recursion tree to avoid generating duplicate subsets in the
     * first place. By sorting the array first, all duplicates become adjacent.
     * If we choose NOT to pick an element, we must also skip all identical
     * elements immediately following it to prevent generating identical subsets.
     *
     * STEP-BY-STEP APPROACH:
     * 1. Sort the input array `nums` so duplicates are adjacent.
     * 2. Start the recursion at index 0 with an empty `subset`.
     * 3. Base Case: If `idx` reaches the end of `nums`, add `subset` to `ans`.
     * 4. Branch 1 (Pick): Add `nums[idx]` to `subset`, recurse for `idx + 1`,
     * and then backtrack by popping the element.
     * 5. Branch 2 (Do Not Pick): Since we decided NOT to include the current
     * element at this specific position, we use a while loop to skip any
     * subsequent identical elements.
     * 6. Recurse for the next unique element's index.
     *
     * TIME COMPLEXITY:
     * O(N * 2^N) in the worst case (where all elements are unique).
     * We generate at most 2^N subsets, and copying each subset to the result
     * takes O(N) time. However, if there are many duplicates, the actual
     * time is much faster because we prune large portions of the recursion tree.
     * * SPACE COMPLEXITY:
     * O(N) auxiliary space for the recursion stack and the `subset` vector.
     * (Excluding the space required for the output array `ans`).
     *
     * COMPARISON TO METHOD 2 (Set Method):
     * + PROS: Much faster and more memory-efficient. It avoids generating
     * dead-end branches in the recursion tree entirely. It also avoids the
     * heavy structural memory overhead and O(log M) insertion time of a
     * `std::set` (Red-Black tree).
     * - CONS: The logic is slightly more complex. You have to be careful
     * about exactly where and how you skip duplicates.
     */

    void rec(int idx, vector<int> &nums, vector<int> &subset, vector<vector<int>> &ans)
    {
        // Base case: we've considered all elements
        if (idx == nums.size())
        {
            ans.push_back(subset);
            return;
        }

        // Branch 1: PICK the current element
        subset.push_back(nums[idx]);
        rec(idx + 1, nums, subset, ans);
        subset.pop_back(); // backtrack

        // Branch 2: DO NOT PICK the current element
        // Since we are not picking nums[idx], we must skip all future duplicates of it.
        // Otherwise, picking the duplicate later would create a subset we already generated.
        while (idx + 1 < nums.size() && nums[idx] == nums[idx + 1])
        {
            idx++;
        }

        // Move to the next unique element
        rec(idx + 1, nums, subset, ans);
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        vector<vector<int>> ans;
        vector<int> subset;

        // Sorting is strictly required so duplicates are adjacent
        sort(nums.begin(), nums.end());

        rec(0, nums, subset, ans);

        return ans;
    }

    // ---------------------------------------------
    // 3. Sum of all Subsets:
    // ---------------------------------------------

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
