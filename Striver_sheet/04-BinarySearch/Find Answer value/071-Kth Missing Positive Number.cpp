#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Kth Missing Positive Number

https://takeuforward.org/arrays/kth-missing-positive-number/
https://leetcode.com/problems/kth-missing-positive-number/description/

Problem statement:
You are given a strictly increasing array ‘vec’ and a positive integer 'k'. Find the 'kth' positive integer missing from 'vec'.

Examples:

Example 1:
Input Format: vec[]={4,7,9,10}, k = 1
Result: 1
Explanation: The missing numbers are 1, 2, 3, 5, 6, 8, 11, 12, ……, and so on. Since 'k' is 1, the first missing element is 1.

Example 2:
Input Format: vec[]={4,7,9,10}, k = 4
Result: 5
Explanation: The missing numbers are 1, 2, 3, 5, 6, 8, 11, 12, ……, and so on. Since 'k' is 4, the fourth missing element is 5.


INPUT::::::
4
1
4 7 9 10
4
4 7 9 10
5
2 3 4 7 11
2
1 2 3 4


OUTPUT::::::
1
5
9
6

 */
class Solution
{
public:
    // Optimal approach: inary search
    // Time: O(Log N)
    // Space: O(1)
    int findKthPositive(vector<int> &arr, int k)
    {
        int N = arr.size();
        int num = 0;  // this will store the largest number seen which is less than the missing number
        int diff = 0; // This stores the count of missing numbers for that 'num'

        int l = 1;
        int r = N;

        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            int lcNum = arr[mid - 1]; // Use [mid-1] instead of [mid] to convert to 0th based indexing
            int lcDiff = lcNum - mid;

            if (lcDiff < k)
            {
                diff = lcDiff;
                num = lcNum;
                l = mid + 1;
            }
            else if (lcDiff >= k)
            {
                r = mid - 1;
            }
        }

        return num + (k - diff);
    }

    // Approach: Linear search
    // Time: O(N)
    // Space: O(1)
    // int missingK(vector<int> vec, int n, int k)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         if (vec[i] <= k)
    //             k++; // shifting k
    //         else
    //             break;
    //     }
    //     return k;
    // }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int n;
        cin >> n;
        cin.ignore();

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

        cout << ob.findKthPositive(arr, n);
        cout << endl;
    }
    return 0;
}