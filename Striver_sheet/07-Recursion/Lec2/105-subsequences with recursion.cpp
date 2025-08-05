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

Subset Sum Equal To K exists?

https://www.naukri.com/code360/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM

Problem statement:
You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.

Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

For Example :
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.

Follow-up:
Can you use dynamic programming and use the previously calculated result to calculate the new result?

INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------

Count Subsets with Sum K:

https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532?leftPanelTabValue=PROBLEM

Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.


Problem statement
You are given an array 'arr' of size 'n' containing positive integers and a target sum 'k'.
Find the number of ways of selecting the elements from the array such that the sum of chosen elements is equal to the target 'k'.
Since the number of ways can be very large, print it modulo 10 ^ 9 + 7.

Example:
Input: 'arr' = [1, 1, 4, 5]
Output: 3
Explanation: The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.

Follow-up:
The expected time complexity is O('n' * 'k').
Optimize it with DP.

INPUT::::::


OUTPUT::::::

-------------------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------
    // Subset Sum Equal To K exists?

    // O(2^N) : w/o DP, so non-optimal
    bool recFindExists(vector<int> &arr, int index, int target, int prevSum)
    {

        if (index == arr.size() || prevSum > target)
            return false;

        int cur = arr[index];

        bool ret = false;
        if ((prevSum + cur) == target)
            return true;

        ret = recFindExists(arr, (index + 1), target, (prevSum + cur));
        if (ret)
            return true;

        ret = recFindExists(arr, (index + 1), target, prevSum);
        if (ret)
            return true;

        return false;
    }

    // NON-optimal approach: Recursion  w/o DP
    // Time: O(2^N) due to binary stack tree
    // Space: O(N) due to stack space
    bool subsetSumToK(int n, int k, vector<int> &arr)
    {
        return recFindExists(arr, 0, k, 0);
    }

    // ---------------------------------------------
    // Count Subsets with Sum K:

    int static const moduler = (1e9 + 7);

    // O(2^N) : w/o DP, so non-optimal
    int recCountSum(vector<int> &arr, int index, int target, int prevSum)
    {

        if (index == arr.size() || prevSum > target)
            return 0;

        int cur = arr[index];

        int ret = 0;
        if ((prevSum + cur) == target)
            ret = 1;

        ret += recCountSum(arr, (index + 1), target, (prevSum + cur));
        ret += recCountSum(arr, (index + 1), target, prevSum);

        return (ret % moduler);
    }

    // NON-optimal approach: Recursion  w/o DP
    // Time: O(2^N) due to binary stack tree
    // Space: O(N) due to stack space
    // For DP Refer: 223-subsequences with recursion.cpp
    int findWays(vector<int> &arr, int k)
    {
        return recCountSum(arr, 0, k, 0);
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
