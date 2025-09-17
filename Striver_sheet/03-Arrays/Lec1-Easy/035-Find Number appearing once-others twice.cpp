#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/arrays/find-the-number-that-appears-once-and-the-other-numbers-twice/
https://www.naukri.com/code360/problems/find-the-single-element_6680465?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/single-number/description/

Problem Statement:
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Examples:

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1


INPUT::::::
4
3 0 1
0 1
9 6 4 2 3 5 7 0 1
1

OUTPUT::::::

1
4
1
2
10
3

 */
class Solution
{
public:
    // Approach 1: XOR (best for unsorted input)
    // ----------------------------------------
    // Idea:
    //   XOR all numbers together. Because x ^ x = 0 and 0 ^ y = y, every number that
    //   appears twice cancels out, leaving the single (unpaired) number as the result.
    //   This assumes exactly one number appears once and all others appear exactly twice.
    //
    // Time: O(N)   -- single pass through array
    // Space: O(1)  -- constant extra space
    //
    // Notes:
    //   - Works on unsorted arrays.
    //   - No risk of overflow since it's bitwise, not arithmetic.
    //   - Extremely efficient and the usual preferred approach when constraints match.
    int singleNumber(vector<int> &nums)
    {
        int xori = 0; // accumulator for XOR of seen elements

        // XOR every element into the accumulator. Pairs cancel out.
        for (int e : nums)
        {
            xori ^= e;
        }

        // After the loop, xori holds the element that did not have a pair.
        return xori;
    }

    // Approach 2: Scan sorted array (use when input is sorted)
    // -------------------------------------------------------
    // Idea:
    //   If the array is sorted and exactly one element appears once while every other
    //   element appears twice, then the unique element will be the one that is not
    //   equal to its neighbor(s). We scan and check neighbors to find it.
    //   This avoids extra space and can short-circuit early once found.
    //
    // Time: O(N)   -- in the worst case we may scan whole array
    // Space: O(1)
    //
    // Notes / Edge-cases:
    //   - Requires the input array to be sorted. If not sorted, either sort first
    //     (cost O(N log N)) or use the XOR approach.
    //   - Careful at boundaries (i == 0 and i == n-1) — those are handled explicitly.
    //   - If pairs are large blocks, you can optimize by skipping pairs (i += 2 when
    //     arr[i] == arr[i+1]) to speed average performance, but correctness remains
    //     with the simple neighbor-check below.
    //   - Ensure `ans` is initialized or assigned before returning (this code assigns
    //     before break; defensive default could be used if needed).
    int singleNumber(vector<int> &arr)
    {
        int n = arr.size();
        int ans = 0; // will hold the unique element once found

        // Traverse the array and find the element which is not equal to its neighbors.
        for (int i = 0; i < n; ++i)
        {
            // Check left neighbor (or boundary) and right neighbor (or boundary).
            // If both comparisons hold (not equal to left and not equal to right),
            // arr[i] is the unique element.
            if ((i == 0 || arr[i] != arr[i - 1]) && (i == n - 1 || arr[i] != arr[i + 1]))
            {
                ans = arr[i];
                break; // we can stop once we find the unique element
            }
        }
        return ans;
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

        cout << ob.singleNumber(arr);
        cout << endl;
    }
}