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

1. Title: XOR of Numbers in a Range

Links:
https://takeuforward.org/bit-manipulation/xor-of-numbers-in-a-given-range

https://takeuforward.org/bit-manipulation/xor-of-numbers-in-a-range-l-to-r
https://www.naukri.com/code360/problems/l-to-r-xor_8160412?leftPanelTabValue=PROBLEM


Problem statement:
You are given two numbers 'L' and 'R'.
Find the XOR of the elements in the range [L, R].

Example:
    For 'L' = 1 and ‘R’ = 5.
    The answer is 1.
    Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
    3 5
Sample Output 1:
    2
Explanation of sample output 1:
'L' = 3 and ‘R’ = 5
Answer is 2. Value of 3^4^5 is 2.

Sample Input 2:
    1 3
Sample Output 2:
    0

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    // ---------------------------------------------------------------
    // Title: XOR of Numbers in a Range

    // O(1)
    int findXorOfRangeFromOne(int N)
    {

        int rem = N % 4;

        switch (rem)
        {
        case 1:
            return 1;
        case 2:
            return (N + 1);
        case 3:
            return 0;
        case 0:
            return N;
        default:
            return -1;
        }
    }

    // Optimal approach: Use predefined modulo table
    // Time: o(1)
    // Space: O(1)
    int findXOR(int L, int R)
    {

        int preL = L - 1;

        int xorOneTopreL = findXorOfRangeFromOne(preL);
        int xorOneToR = findXorOfRangeFromOne(R);

        return xorOneTopreL ^ xorOneToR;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
