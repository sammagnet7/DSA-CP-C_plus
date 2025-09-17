#include <iostream>
#include <vector>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
https://takeuforward.org/arrays/find-the-missing-number-in-an-array/
https://leetcode.com/problems/missing-number/
https://www.naukri.com/code360/problems/missing-number_6680467?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse&leftPanelTabValue=SUBMISSION


Problem Statement:
Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Examples:

Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation:
n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation:
n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation:
n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.


Constraints:
n == nums.length
1 <= n <= 104
0 <= nums[i] <= n
All the numbers of nums are unique.

Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?

INPUT::::::
4
3 0 1
0 1
9 6 4 2 3 5 7 0 1
1

OUTPUT::::::

2
2
8
0


 */
class Solution
{
public:
    // Approach 1: Sorting
    // -------------------
    // Idea:
    //   Sort the array, then scan adjacent elements to find the gap (difference != 1).
    //   If the first element isn't 0 then 0 is missing. If no gap found, the missing number
    //   must be n (one greater than the last element).
    //
    // Time: O(N log N)   (dominant cost: sort)
    // Space: O(1)       (in-place sort; ignoring sort's stack or allocator details)
    //
    // Note:
    //   - Sorting changes the input order (destructive).
    //   - Works well if N is small or when an in-place solution isn't required.
    int missingNumber(vector<int> &nums)
    {
        // Sort the array so missing gap becomes visible as a non-consecutive pair.
        sort(nums.begin(), nums.end());

        // Edge case: smallest number should be 0 for a full 0..n range.
        if (nums[0] != 0)
            return 0; // 0 is missing

        // Walk adjacent pairs and look for a break in consecutiveness.
        for (int i = 0; i < (int)nums.size() - 1; i++)
        {
            // If next element is not exactly one greater, the missing number is nums[i]+1.
            if (nums[i + 1] - nums[i] != 1)
                return nums[i] + 1;
        }

        // If we never found a gap, the missing number must be n (i.e., last element + 1).
        return nums[nums.size() - 1] + 1;
    }

    // Approach 2: Extra array / boolean marker
    // ----------------------------------------
    // Idea:
    //   Create an auxiliary array of length n+1 initialized to a sentinel (e.g., -1).
    //   Mark positions present in `nums`. Then scan the marker array to find the index
    //   that was never marked — that index is the missing number.
    //
    // Time: O(N)     (single pass to mark + single pass to scan markers)
    // Space: O(N)    (auxiliary array of size n+1)
    //
    // Note:
    //   - Straightforward and easy to reason about.
    //   - Uses O(n) extra memory; not ideal when memory is constrained.
    int missingNumber(vector<int> &nums)
    {
        int len = nums.size();

        // Marker array for all numbers in range [0..len]. Initialize with -1 (absent).
        vector<int> range(len + 1, -1);

        // Mark each seen number.
        for (int e : nums)
        {
            // e is guaranteed to be in [0..len] by problem constraints.
            range[e] = 1;
        }

        // The first index not marked is the missing number.
        for (int i = 0; i < (len + 1); i++)
        {
            if (range[i] == -1)
                return i;
        }

        // Defensive: but algorithm should always return inside loop.
        return 0;
    }

    // Approach 3: Sum formula (expected sum - actual sum)
    // --------------------------------------------------
    // Idea:
    //   The sum of numbers from 0..n is n*(n+1)/2. Compute expected sum and subtract
    //   actual sum of array elements; the difference is the missing number.
    //
    // Time: O(N)    (one pass to compute actual sum)
    // Space: O(1)
    //
    // Notes / Caveats:
    //   - Watch integer overflow for large n; prefer 64-bit (long long) for production.
    //   - Simple and intuitive, but can overflow with large inputs in 32-bit int.
    int missingNumber(vector<int> &nums)
    {
        int len = nums.size();

        // expectedSum is sum of 0..len, because one number in 0..len is missing and nums has size len
        long long expectedSum = (long long)len * (len + 1) / 2; // use long long to avoid overflow
        long long actualSum = 0;

        // Compute actual sum of provided numbers
        for (int e : nums)
        {
            actualSum += e;
        }

        // The difference yields the missing number
        return (int)(expectedSum - actualSum);
    }

    // Approach 4: XOR trick
    // ---------------------
    // Idea:
    //   XOR has the property that x ^ x = 0 and x ^ 0 = x. If we XOR all numbers in
    //   nums and XOR with all numbers from 0..n, all paired numbers cancel out and
    //   the result is the missing number.
    //
    // Time: O(N)   (single pass)
    // Space: O(1)
    //
    // Advantages:
    //   - No risk of arithmetic overflow.
    //   - Very memory efficient and fast.
    //   - Works cleanly with bitwise operations.
    int missingNumber(vector<int> &nums)
    {
        int len = nums.size();

        // xor1 = XOR of all elements in nums
        int xor1 = 0;
        // xor2 = XOR of all numbers from 0..len
        int xor2 = len; // start with len so after XOR-ing 0..len-1 we get XOR(0..len)

        // Build xor1 and xor2
        for (int i = 0; i < len; i++)
        {
            xor1 ^= nums[i]; // XOR with array element
            xor2 ^= i;       // XOR with index i (0..len-1)
        }

        // XOR of xor1 and xor2 cancels all present numbers, leaving the missing one.
        return (xor1 ^ xor2);
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
        string input;

        getline(cin, input);

        stringstream ss(input);

        vector<int> arr;
        int num;

        while (ss >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.missingNumber(arr);
        cout << endl;
    }
}