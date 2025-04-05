#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Merge Overlapping Sub-intervals

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
    // // Approach: Better: Hashing
    // // Time: O(N)
    // // Space: O(N)
    // vector<int> findTwoElement(vector<int> &arr)
    // {

    //     int N = arr.size();
    //     vector<int> res(2);

    //     vector<int> hash(N + 1, 0);

    //     for (int e : arr)
    //     {
    //         hash[e]++;
    //     }

    //     int count = 0;
    //     for (int i = 1; i <= N; i++)
    //     {

    //         if (hash[i] == 2)
    //         {
    //             res[0] = i;
    //             count++;
    //         }

    //         else if (hash[i] == 0)
    //         {
    //             res[1] = i;
    //             count++;
    //         }

    //         if (count == 2)
    //             break;
    //     }

    //     return res;
    // }

    // Approach: Optimal 1: Math based
    // find 2 equations: x + y and x - y.. To find these use 2 AP formulas: sum of first N numbers and sum of first N^2s
    // Time: O(N)
    // Space: O(1)
    vector<int> findTwoElement(vector<int> &arr)
    {

        long long N = arr.size(); // make it long

        long long sumOfNs = N * (N + 1) / 2; // Apply formula to find sum of first N natural numbers

        long long sumOfNSquares = N * (N + 1) * (2 * N + 1) / 6; // Apply formula to find sum of first N natural numbers' squares

        long long actualSum = 0;
        long long actualSquareSum = 0;
        for (int e : arr)
        {
            actualSum += e;
            actualSquareSum += (e * e);
        }

        int xMinusY = sumOfNs - actualSum;
        int x2MinusY2 = sumOfNSquares - actualSquareSum;

        int xPlusY = x2MinusY2 / xMinusY;

        int val1 = (xPlusY + xMinusY) / 2;
        int val2 = (xPlusY - xMinusY) / 2;

        int c = 0;
        for (int e : arr)
        {
            if (e == val1)
            {
                c++;
            }
        }

        if (c == 2)
        {
            return {val1, val2};
        }
        else
            return {val2, val1};
    }

    // // Approach: Optimal 2: XOR based
    // // See the TakeUForward blog
    // // Time: O(3 N)
    // // Space: O(1)
    // vector<int> findTwoElement(vector<int> &arr)
    // {

    //     long long N = arr.size(); // make it long

    //     int actualXor = 0;
    //     int xorOfNs = 0;

    //     for (int i = 0; i < N; i++)
    //     { // xor of all array elements and all elements from 1 to N
    //         actualXor ^= arr[i];
    //         xorOfNs ^= i + 1;
    //     }

    //     int XxorY = actualXor ^ xorOfNs;

    //     int bitPos = -1;

    //     for (int i = 0; i < 32; i++)
    //     { // Find the bit index from right where x and y differs. To get that find first bit value 1 from right in xored product
    //         if ((XxorY >> i) & 1)
    //         {
    //             bitPos = i;
    //             break;
    //         }
    //     }

    //     int buck1 = 0, buck2 = 0; // 2 buckets: Bucket1 will consists of the xor of elements having 1 at index 'bitPos'
    //                               // Bucket2 will consists of the xor of elements having 0 at index 'bitPos'

    //     for (int i = 0; i < N; i++)
    //     { // Segregating elements having one vs zero at the bit index

    //         if ((arr[i] >> bitPos) & 1)
    //             buck1 ^= arr[i];
    //         else
    //             buck2 ^= arr[i];

    //         if (((i + 1) >> bitPos) & 1)
    //             buck1 ^= i + 1;
    //         else
    //             buck2 ^= i + 1;
    //     }

    //     int c = 0; // counter
    //     for (int e : arr)
    //     { // Checking which one of the variable is missing vs repeating
    //         if (e == buck1)
    //         {
    //             c++;
    //         }
    //     }

    //     if (c == 2)
    //     {
    //         return {buck1, buck2};
    //     }
    //     else
    //         return {buck2, buck1};
    // }
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