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

Title: Find Kth Bit in Nth Binary String

Link:
https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/description/


Problem statement:
Given two positive integers n and k, the binary string Sn is formed as follows:

S1 = "0"
Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first four strings in the above sequence are:

S1 = "0"
S2 = "011"
S3 = "0111001"
S4 = "011100110110001"
Return the kth bit in Sn. It is guaranteed that k is valid for the given n.


Example 1:
Input: n = 3, k = 1
Output: "0"
Explanation: S3 is "0111001".
The 1st bit is "0".

Example 2:
Input: n = 4, k = 11
Output: "1"
Explanation: S4 is "011100110110001".
The 11th bit is "1".


Constraints:
1 <= n <= 20
1 <= k <= 2n - 1

INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: K-th Symbol in Grammar

Links:
https://leetcode.com/problems/k-th-symbol-in-grammar/description/

Problem statement:
We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.


Example 1:
Input: n = 1, k = 1
Output: 0
Explanation: row 1: 0

Example 2:
Input: n = 2, k = 1
Output: 0
Explanation:
row 1: 0
row 2: 01

Example 3:
Input: n = 2, k = 2
Output: 1
Explanation:
row 1: 0
row 2: 01


Constraints:
1 <= n <= 30
1 <= k <= 2n - 1



INPUT::::::


OUTPUT::::::

*/

//-------------------------------------------------------------------------------
// 1. Title: Find Kth Bit in Nth Binary String
//-------------------------------------------------------------------------------
class Solution
{
public:
    /*
     * METHOD: findKthBit
     * ------------------
     * APPROACH: Divide and Conquer / Recursion
     * We avoid generating the string by navigating the mathematical properties
     * of its symmetrical construction. At each step, we cut the search space
     * in half, just like Binary Search.
     *
     * COMPLEXITY:
     * - Time: O(N). The recursion goes at most N levels deep. Since N <= 20,
     * this executes in a fraction of a millisecond.
     * - Space: O(N) for the recursive call stack. No strings are allocated.
     */
    char findKthBit(int n, int k)
    {

        // Base case: The first string is just "0"
        if (n == 1)
        {
            return '0';
        }

        // Calculate the total length of S_n which is (2^n) - 1
        int length = (1 << n) - 1;

        // Calculate the 1-indexed middle position
        int mid = length / 2 + 1;

        // Case 1: k is exactly the middle bit
        if (k == mid)
        {
            return '1';
        }

        // Case 2: k is in the left half
        if (k < mid)
        {
            // The left half is identical to S_{n-1}
            return findKthBit(n - 1, k);
        }

        // Case 3: k is in the right half
        else
        {
            // Find the mirrored position in S_{n-1}
            int mirroredIndex = length - k + 1;

            // Recursively fetch the bit from S_{n-1}
            char bit = findKthBit(n - 1, mirroredIndex);

            // Because the right half is inverted, we MUST flip the result
            return bit == '0' ? '1' : '0';
        }
    }
};

//-------------------------------------------------------------------------------
// 2. Title: K-th Symbol in Grammar
//-------------------------------------------------------------------------------
/*
0:01
1:10

n      k:123456789.......
1: # 1   0
2: # 2   01
3: # 4   0110
4: # 8   01101001
5: #16   0110100110010110
*/
class Solution
{
public:
    /*
     * METHOD: kthGrammar
     * ------------------
     * APPROACH: Binary Tree Parent-Child Mapping
     * We view the grammar generation as a binary tree. Each bit in row (n-1)
     * spawns two bits in row n. By mapping the current index 'k' to its parent
     * index (k + 1) / 2, we can recursively fetch the parent's value. Then, we
     * determine the current bit based on whether 'k' is an odd (left) or
     * even (right) child.
     *
     * COMPLEXITY:
     * - Time: O(N). We make exactly N recursive calls to traverse up the tree.
     * - Space: O(N) strictly for the recursive call stack.
     */
    int kthGrammar(int n, int k)
    {

        // Base case: The root of the tree is always 0
        if (n == 1)
        {
            return 0;
        }

        // Recursively fetch the parent bit from the previous row.
        // (k + 1) / 2 flawlessly maps both left (odd) and right (even) children
        // to their shared parent index.
        int prev = kthGrammar(n - 1, (k + 1) / 2);

        // If the parent is 0:
        // - Left child (k is odd) becomes 0
        // - Right child (k is even) becomes 1
        if (prev == 0)
        {
            return (k % 2 != 0) ? 0 : 1;
        }
        // If the parent is 1:
        // - Left child (k is odd) becomes 1
        // - Right child (k is even) becomes 0
        else
        {
            return (k % 2 != 0) ? 1 : 0;
        }
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
