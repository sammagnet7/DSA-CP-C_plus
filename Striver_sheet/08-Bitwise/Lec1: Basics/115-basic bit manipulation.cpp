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

1. Title: Check whether K-th bit is set or not (i.e. extract i-th bit)

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/check-whether-k-th-bit-is-set-or-not_5026446?leftPanelTabValue=SUBMISSION


Problem statement:
Given a number ‘N’ and a number ‘K’. Return true if ‘K’th bit of number is set, else return false.

Example:
Input: ‘N’ = 5, ‘K’ = 1
Output: YES
5 in binary can be written as 101 and as we can see a first bit from the right of 5 is set so the answer is 'YES'.
Detailed explanation ( Input/output format, Notes, Images )

Sample Input 1 :
3 2
Sample Output 1 :
YES
Explanation Of Sample Input 1 :
3 in binary can be represented as 11 and 2 bit from right is set there, So answer is 'YES'.

Sample Input 2 :
128 7
Sample Output 2 :
NO


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

2. Title: Even or Odd

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.geeksforgeeks.org/problems/odd-or-even3618/1

Problem statement:
Given a positive integer n, determine whether it is odd or even. Return true if the number is even and false if the number is odd.

Examples:

Input: n = 15
Output: false
Explanation: The number is not divisible by 2, Odd number.

Input: n = 44
Output: true
Explanation: The number is divisible by 2, Even number.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

3. Title: Power of Two

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/power-of-two_893061?leftPanelTabValue=SUBMISSION


Problem statement:
You have been given an integer 'N'.
Your task is to return true if it is a power of two. Otherwise, return false.
An integer 'N' is a power of two, if it can be expressed as 2 ^ 'K' where 'K' is an integer.

Example:
'N' = 4,
4 can be represented as 2^2. So, 4 is the power of two, and hence true is our answer.

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

4. Title: Set/Unset the rightmost unset/set bit

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/set-the-rightmost-unset-bit_8160456?leftPanelTabValue=PROBLEM


Problem statement:
The problem is to find the rightmost bit of a non-negative number 'N' that is currently unset (i.e., has a value of 0) in its binary representation and set it to 1.
Return the number after setting the rightmost unset bit of 'N'. If there are no unset bits in N's binary representation, then the number should remain unchanged.

Examples:

N = 5
Output: 7
Explanation: The binary representation of 5 is 101. After setting the rightmost unset bit it becomes 111 which is 7.
Detailed explanation ( Input/output format, Notes, Images )

Sample Input 1:
10
Sample Output 1:
11
Explanation Of Sample Input 1:
N=10
The binary representation of 10 is 1010. After setting the rightmost unset bit it becomes 1011 which is 11.

Sample Input 2:
7
Sample Output 2:
7
Explanation Of Sample Input 2:
N=7
The binary representation of 7 is 111. As there is no unset bit it remains the same.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

5. Title: Swap Two Numbers w/o third variable

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/swap-two-numbers_1112577?leftPanelTabValue=PROBLEM


Problem statement:
You are given two numbers 'a' and 'b' as input.
You must swap the values of 'a' and 'b'.

For Example:
Input:
'a' = 8, 'b' = 5
Output:
5 8
Explanation:
Initially, the value of 'a' and 'b' is 8 and 5, respectively.

After swapping, the value of 'a' is 5, and the value of 'b' is 8.

Note: Do it with out 3rd variable

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
6. Title: Set i-th bit

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/bit-manipulation_8142533?leftPanelTabValue=PROBLEM

Problem statement:
You have a 32-bit unsigned integer called 'num' and another integer called 'i'.
You need to perform the following operations on the 'num' integer based on the value of 'i':
1. Get the bit value at the "i"th position of "num".
2. Set the bit at the "i"th position of "num".
3. Clear the bit at the "i"th position of "num".

We are starting bits from 1 instead of 0. (1-based)

For Example:
N=25  i=3
Output : 0 29 25
Bit at the 3rd position from LSB is 0. (1 1 0 0 1)
The value of the given number after setting the 3rd bit is 29. (1 1 1 0 1)
The value of the given number after clearing the 3rd bit is 25. (1 1 0 0 1)

INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
7. Title: Toggle i-th bit

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/toggle-k-bits_973006?leftPanelTabValue=PROBLEM

Problem statement:
You are given a 32-bit integer ‘N’. Your task is to toggle the rightmost ‘K’ bits in the given integer and return the new integer.

For Example :
If ‘N’ = 12 and ‘K’ = 2:
The binary representation of 12 is ‘1100’, after toggling rightmost 2 bits, it becomes ‘1111’ i.e. 15. Hence, the answer is 15.


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------
8. Title: Count the set bits

Links:
https://www.youtube.com/watch?v=qQd-ViW7bfk
https://www.naukri.com/code360/problems/count-set-bits_1112627?leftPanelTabValue=PROBLEM

Problem statement
You are given a positive integer ‘N’. Your task is to find the total number of ‘1’ in the binary representation of all the numbers from 1 to N.
Since the count of ‘1’ can be huge, you are required to return it modulo 1e9+7.

Sample Input 1:
2
5
3
Sample Output 1:
7
4
Explanation For Sample Input 1 :

In the first test case,
DECIMAL    BINARY      SET BIT COUNT
1            01                  1
2            10                  1
3            11                  2
4            100                 1
5            101                 2
1 + 1 + 2 + 1 + 2 = 7
Answer = 7 % 1000000007 = 7


In the second test case,
DECIMAL    BINARY      SET BIT COUNT
1            01                  1
2            10                  1
3            11                  2
1 + 1 + 2 = 4
Answer = 4 % 1000000007 = 4
Sample Input 2:
2
6
10
Sample Output 2:
9
17


INPUT::::::


OUTPUT::::::

-----------------------------------------------------------------------

*/

class Solution
{
public:
    //-----------------------------------------------------------------------
    // 1. Title: Check whether K-th bit is set or not

    // O(1)
    bool isKthBitSet(int N, int k)
    {

        bool ans = N & (1 << (k - 1)); // taking (k-1) as 1 based index is used in the question

        return ans;
    }

    //-----------------------------------------------------------------------
    // 2. Title: Even or Odd

    // O(1)
    bool isEven(int N)
    {

        bool ans = N & 1; // Bitwise AND with the LSB bit of N -> if 1 then Odd

        return (!ans);
    }

    //-----------------------------------------------------------------------
    // 3. Title: Power of Two

    // O(1)
    bool isPowerOfTwo(int N)
    {
        int removedRightMostSetBit = N & (N - 1);
        bool isSingleSetBit = removedRightMostSetBit == 0 ? true : false;

        return isSingleSetBit;
    }

    //-----------------------------------------------------------------------
    // 4. Title: Set/Unset the rightmost unset/set bit

    // Set the rightmost unset bit
    // O(N)
    int setBits(int N)
    {

        bool ifAllOnes = N & (N + 1);          // check if no zeros exists
        int setRightMostzeroBit = N | (N + 1); // sets rightmost unset bit

        if (ifAllOnes)
            return setRightMostzeroBit;
        else
            return N; // if no zeros then no need to set
    }

    // Unset the rightmost set bit
    // O(N)
    int unsetBits(int N)
    {

        bool ifAllzeros = (N == 0) ? true : false; // check if no ones exists
        int unsetRightMostOneBit = N & (N - 1);    // un-sets rightmost set bit

        if (!ifAllzeros)
            return N;
        else
            return unsetRightMostOneBit;
    }

    //-----------------------------------------------------------------------
    // 5. Title: Swap Two Numbers w/o third variable

    // O(3)
    void swapNumber(int &a, int &b)
    {
        a = a ^ b; // a xor b
        b = b ^ a; // b ^ (a^b) -> a
        a = a ^ b; // (a^b) ^ a -> b
    }

    //-----------------------------------------------------------------------
    // 6. Title: Set i-th bit

    // O(1)
    vector<int> bitManipulation(int num, int i)
    {

        int bitManipulator = (1 << (i - 1)); // as 1-based index

        int curBit;

        if ((num & bitManipulator) > 0)
            curBit = 1;
        else
            curBit = 0;

        int setIthBit = num | bitManipulator; // set i-th bit

        int unsetIthBit = num & (~bitManipulator);

        return {curBit, setIthBit, unsetIthBit};
    }

    //-----------------------------------------------------------------------
    // 7. Title: Toggle i-th bit

    // use XOR with `1` to toggle a bit
    // O(1)
    int toggleKBits(int N, int k)
    {

        int op = 1 << k; // for k=2 make op = 100

        op = op - 1; // then make op = 11

        N = N ^ op; // 1100 xor 11 -> 1111

        return N;
    }

    //-----------------------------------------------------------------------
    // 8. Title: Count the set bits

    // O(N * Log N)
    int countSetBits(int n)
    {

        long long count = 0;
        long long mod = (1e9 + 7);

        // O(Log N)
        while (n)
        {

            int tmp = n;

            while (tmp)
            {

                if (tmp & 1)
                { // odd
                    count++;
                    count = (count % mod);
                }

                tmp = tmp / 2;
            }

            n--;
        }

        return count;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
