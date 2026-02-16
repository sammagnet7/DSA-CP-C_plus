#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find the repeating and missing number

https://takeuforward.org/data-structure/find-the-repeating-and-missing-numbers/
https://www.geeksforgeeks.org/problems/find-missing-and-repeating2512/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=find-missing-and-repeating
https://www.naukri.com/code360/problems/missing-and-repeating-numbers_6828164?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem statement:
You are given a read-only array of N integers with values also in the range [1, N] both inclusive. Each integer appears exactly once except A which appears twice and B which is missing. The task is to find the repeating and missing numbers A and B where A repeats twice and B is missing.


Examples:

Example 1:
    Input Format:  array[] = {3,1,2,5,3}
    Result: {3,4)
    Explanation: A = 3 , B = 4
    Since 3 is appearing twice and 4 is missing

Example 2:
    Input Format: array[] = {3,1,2,5,4,6,7,5}
    Result: {5,8)
    Explanation: A = 5 , B = 8
    Since 5 is appearing twice and 8 is missing


INPUT::::::
5
3 1 2 5 3
3 1 2 5 4 6 7 5
2 2
1 3 3
4 3 6 2 1 1

OUTPUT::::::
3 4
5 8
2 1
3 2
1 5

 */
class Solution
{
public:
    // Approach: Hashing
    // - Use a frequency array (hash) of size N+1 to track counts of each number.
    // - Traverse arr, incrementing counts.
    // - The number with count==2 → duplicate.
    // - The number with count==0 → missing.
    // Time: O(N)   Space: O(N)
    vector<int> findTwoElement(vector<int> &arr)
    {
        int N = arr.size();
        vector<int> res(2);
        vector<int> hash(N + 1, 0);

        // Count occurrences
        for (int e : arr)
        {
            hash[e]++;
        }

        // Identify duplicate and missing
        for (int i = 1; i <= N; i++)
        {
            if (hash[i] == 2)
                res[0] = i; // duplicate
            if (hash[i] == 0)
                res[1] = i; // missing
        }
        return res;
    }

    /*
    findTwoElement
    ---------------
    Problem:
        - You are given an array of size N containing numbers from 1..N.
        - Exactly one number is missing and one number is duplicated.
        - Find both numbers.

    Approach: Optimal 1 (Math-based using sum formulas)
    ---------------------------------------------------
    Intuition:
        - Let:
            x = missing number
            y = repeating number
        - Two facts:
            1) Difference in total sums:
                (1 + 2 + ... + N) - (sum of array)
                = (x + rest) - (y + rest)
                = x - y
                => x - y = sumOfNs - actualSum
            2) Difference in sum of squares:
                (1^2 + 2^2 + ... + N^2) - (sum of squares of array)
                = (x^2 + rest) - (y^2 + rest)
                = x^2 - y^2
                => (x - y)(x + y) = x2MinusY2
                => x + y = (x2MinusY2 / (x - y))
        - Now we have two equations:
            x - y  (from sums)
            x + y  (from squares)
        - Solve them to get x and y:
            x = ( (x+y) + (x-y) ) / 2
            y = ( (x+y) - (x-y) ) / 2
        - Finally, confirm which one is repeating by counting.

    Complexity:
        - Time: O(N) (one pass for sums, one pass to verify duplicate).
        - Space: O(1) (only variables, no extra arrays).

    Example:
        arr = [1, 3, 3]
        N=3
        sumOfNs = 6, actualSum = 7 → x-y = -1
        sumOfSquares = 14, actualSquares=19 → x^2-y^2 = -5
        x+y = (x^2-y^2)/(x-y) = (-5)/(-1) = 5
        Solve: x=2, y=3
*/
    vector<int> findTwoElement(vector<int> &arr)
    {
        long long N = arr.size();

        // Expected sums
        long long sumOfNs = N * (N + 1) / 2;                     // formula: N(N+1)/2
        long long sumOfNSquares = N * (N + 1) * (2 * N + 1) / 6; // formula: N(N+1)(2N+1)/6

        // Actual sums from array
        long long actualSum = 0, actualSquareSum = 0;
        for (int e : arr)
        {
            actualSum += e;
            actualSquareSum += (1LL * e * e);
        }

        // Step 1: find x-y
        int xMinusY = sumOfNs - actualSum;

        // Step 2: find x^2-y^2
        int x2MinusY2 = sumOfNSquares - actualSquareSum;

        // Step 3: derive x+y
        int xPlusY = x2MinusY2 / xMinusY;

        // Step 4: solve equations
        int val1 = (xPlusY + xMinusY) / 2; // candidate for x
        int val2 = (xPlusY - xMinusY) / 2; // candidate for y

        // Step 5: verify which is repeating
        int count = 0;
        for (int e : arr)
        {
            if (e == val1)
                count++;
        }

        if (count == 2)
        {
            // val1 is repeating, val2 is missing
            return {val1, val2};
        }
        else
        {
            // val2 is repeating, val1 is missing
            return {val2, val1};
        }
    }

    /*
        findTwoElement
        ---------------
        Problem:
            - Given an array of size N containing numbers from 1..N.
            - Exactly one number is missing and one number is duplicated.
            - Find both numbers.

        Approach: Optimal 2 (XOR-based)
        --------------------------------
        Intuition:
            - Let:
                x = missing number
                y = repeating number
            - XOR trick:
                1. XOR of all elements in the array (actualXor).
                2. XOR of all numbers from 1..N (xorOfNs).
                3. Their XOR (actualXor ^ xorOfNs) cancels out all common numbers,
                leaving: XxorY = x ^ y.
            - Now we must separate x and y.
            - Idea: In binary, if x ≠ y, then XxorY has at least one set bit (1).
                    → That bit indicates a position where x and y differ.
            - Use this bit (bitPos) to partition all numbers into two buckets:
                Bucket1: numbers with bitPos set
                Bucket2: numbers with bitPos unset
            - XOR numbers in each bucket (both arr[i] and i+1).
            Because every number except x and y occurs once in both array and range,
            everything cancels out, leaving either x or y in each bucket.
            - At the end, buck1 and buck2 hold x and y (order unknown).
            - Verify by counting which one is repeating in arr.

        Complexity:
            - Time: O(3N)
                * O(N) for first XOR pass
                * O(N) for bucket partition
                * O(N) for verification
            - Space: O(1) extra.

        Example:
            arr = [1, 3, 3]
            N=3
            actualXor = 1 ^ 3 ^ 3 = 1
            xorOfNs   = 1 ^ 2 ^ 3 = 0
            XxorY = 1 ^ 0 = 1 (binary: 001) → lowest set bit at pos 0
            Partition:
                Bucket1: numbers with bit0=1 → {1,3,3} and {1,3}
                Bucket2: numbers with bit0=0 → { } and {2}
            After XOR:
                buck1 = 3, buck2 = 2
            Check: 3 occurs twice → repeating=3, missing=2

    */
    vector<int> findTwoElement(vector<int> &arr)
    {
        long long N = arr.size();

        // Step 1: XOR of all elements and XOR of 1..N
        int actualXor = 0;
        int xorOfNs = 0;
        for (int i = 0; i < N; i++)
        {
            actualXor ^= arr[i];
            xorOfNs ^= (i + 1);
        }

        // Step 2: XOR of missing and repeating numbers
        int XxorY = actualXor ^ xorOfNs;

        // Step 3: find a set bit position (where x and y differ)
        int bitPos = -1;
        for (int i = 0; i < 32; i++)
        {
            if ((XxorY >> i) & 1)
            {
                bitPos = i;
                break;
            }
        }

        // Step 4: partition numbers into two buckets based on bitPos
        int buck1 = 0, buck2 = 0;
        for (int i = 0; i < N; i++)
        {
            if ((arr[i] >> bitPos) & 1)
                buck1 ^= arr[i];
            else
                buck2 ^= arr[i];

            if (((i + 1) >> bitPos) & 1)
                buck1 ^= (i + 1);
            else
                buck2 ^= (i + 1);
        }

        // Step 5: verify which bucket is repeating
        int count = 0;
        for (int e : arr)
        {
            if (e == buck1)
                count++;
        }

        if (count == 2)
        {
            // buck1 is repeating, buck2 is missing
            return {buck1, buck2};
        }
        else
        {
            // buck2 is repeating, buck1 is missing
            return {buck2, buck1};
        }
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
        vector<int> res = ob.findTwoElement(arr);

        cout << res[0] << " " << res[1];
        cout << endl;
    }
    return 0;
}