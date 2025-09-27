#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Count reverse pairs

https://takeuforward.org/data-structure/count-reverse-pairs/
https://leetcode.com/problems/reverse-pairs/description/

Problem statement:
Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:
    0 <= i < j < nums.length and
    nums[i] > 2 * nums[j].

Examples:
    Example 1:
    Input: nums = [1,3,2,3,1]
    Output: 2
    Explanation: The reverse pairs are:
    (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
    (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

    Example 2:
    Input: nums = [2,4,3,5,1]
    Output: 3
    Explanation: The reverse pairs are:
    (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
    (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
    (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1



Constraints:
    1 <= nums.length <= 5 * 104
    -231 <= nums[i] <= 231 - 1



INPUT::::::
3
1 2 3 4 5
5 4 3 2 1
5 3 2 1 4

OUTPUT::::::
0
10
7

 */
class Solution
{
public:
    /*
        Problem: Count Reverse Pairs
        ----------------------------
        - A reverse pair is defined as a pair of indices (i, j) such that:
            i < j  and  arr[i] > 2*arr[j].
        - Example: arr = [1, 3, 2, 3, 1]
            Reverse pairs = (1,4), (3,4) → total = 2.

        Why merge sort helps:
        ---------------------
        - Brute force: check all pairs (i,j) → O(n^2).
        - We can do better with merge sort because:
            * Left half [start..mid] and right half [mid+1..end] are both sorted individually.
            * For each element arr[l] in left half, we want to count how many arr[r] in right half
            satisfy arr[l] > 2*arr[r].
            * Since right half is sorted, once arr[l] > 2*arr[r] holds for some r,
            it will hold for all subsequent r (up to end).
            * This allows linear scanning across the two halves.

        Why not count inside normal merge step (like inversion count)?
        -------------------------------------------------------------
        - In inversion count, condition is arr[l] > arr[r].
        When it holds, all remaining elements in left half also hold → easy to count.
        - For reverse pairs, condition is stricter: arr[l] > 2*arr[r].
        If arr[l] > 2*arr[r], we cannot just move one pointer and count linearly in the same way,
        because future arr[l+1] might also satisfy condition with the same arr[r].
        So we need an explicit two-pointer scan to count before merging.

        Function details:
        -----------------
        1. countReversePairs(arr, start, end, mid):
            - Given arr[start..mid] and arr[mid+1..end] (both sorted),
            count cross-half reverse pairs.
            - Use two pointers (l in left, r in right).
            - If arr[l] > 2*arr[r]:
                → all elements from arr[l..mid] satisfy this with arr[r].
                → increment inversions by (mid - l + 1).
                → increment r.
            Else:
                → increment l (move forward in left half).
            - Returns the count of cross reverse pairs.

        2. mergeSort(arr, start, end):
            - Recursively splits the array into halves.
            - Counts reverse pairs in left half + right half + cross pairs.
            - Unlike normal inversion counting, here merge() step only sorts arrays,
            while counting is done in countReversePairs().

        3. reversePairs(arr):
            - Wrapper function that copies arr (to avoid modifying original).
            - Calls mergeSort to return the count.

        Complexity:
            - Each mergeSort level costs O(n) for scanning (countReversePairs + merge).
            - Total = O(n log n).
            - Space: O(n) if we also implement merge; here only count uses O(1).

        Note:
            - Cast to long long is required because arr[i] and 2*arr[j] can overflow int.
    */

    int countReversePairs(vector<int> &arr, int start, int end, int mid)
    {
        int inversions = 0;
        int l = start, r = mid + 1;

        // Step 1: count cross reverse pairs
        while (l <= mid && r <= end)
        {
            if ((long long)arr[l] > (2LL * arr[r]))
            {
                inversions += (mid - l + 1); // all elements from l..mid satisfy condition with arr[r]
                r++;
            }
            else
            {
                l++;
            }
        }
        return inversions;
    }

    int mergeSort(vector<int> &arr, int start, int end)
    {
        if (start >= end)
            return 0;

        int inversionCount = 0;
        int mid = start + (end - start) / 2;

        // Count in left and right halves
        inversionCount += mergeSort(arr, start, mid);
        inversionCount += mergeSort(arr, mid + 1, end);

        // the extra step added here for: Count cross reverse pairs
        inversionCount += countReversePairs(arr, start, end, mid);

        // Merge step (needed to keep halves sorted for next levels)
        inplace_merge(arr.begin() + start, arr.begin() + mid + 1, arr.begin() + end + 1);

        return inversionCount;
    }

    // Wrapper to count reverse pairs in the array
    int reversePairs(vector<int> &arr)
    {
        int n = arr.size();
        vector<int> workArr(arr.begin(), arr.end()); // copy to avoid modifying original
        return mergeSort(workArr, 0, n - 1);
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        string input;
        getline(cin, input);

        vector<int> arr;
        stringstream ss(input);
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.reversePairs(arr);
        cout << endl;
    }
    return 0;
}