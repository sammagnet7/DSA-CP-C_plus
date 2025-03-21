#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Kadane's Algorithm : Maximum Subarray Sum in an Array

https://takeuforward.org/data-structure/stock-buy-and-sell/
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
https://www.naukri.com/code360/problems/893405?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: You are given an array of prices where prices[i] is the price of a given stock on an ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock. Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Examples:

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.


INPUT::::::
7
7 1 5 3 6 4
7 6 4 3 1
2 100 150 120
1 2 3 4
2 2 2 2
17 20 11 9 12 6
98 101 66 72

OUTPUT::::::

5
0
148
3
0
3
6
 */

class Solution
{
public:
    /*
        Brute force
        Time: O(N^2)
        Space: O(1)
     */
    // int maxProfit(vector<int> &prices)
    // {
    //     int maxP = 0;
    //     for (int i = 0; i < prices.size(); i++)
    //     {
    //         for (int j = i; j < prices.size(); j++)
    //         {
    //             if (prices[j] - prices[i] > maxP)
    //                 maxP = prices[j] - prices[i];
    //         }
    //     }

    //     return maxP;
    // }

    /*  Better Approach
        Intuition:
        Traverse the array from backwards. Compute and store a max elemement, which is the max from last until current index
        Then traverse array from starting to end and find the max profit by substratcing to the backward max of that index.
        Time complexity: O(N)
        Space Complexity: O(N)
     */
    // int maxProfit(vector<int> &prices)
    // {
    //     int N = prices.size();
    //     int maxP = 0;
    //     int maxE = INT_MIN;

    //     vector<int> maxArr(N);

    //     for (int i = N - 1; i > 0; i--)
    //     {
    //         maxE = prices[i] > maxE ? prices[i] : maxE;
    //         maxArr[i] = maxE;
    //     }

    //     for (int i = 0; i < N - 1; i++)
    //     {
    //         if (maxArr[i + 1] - prices[i] > maxP)
    //         {
    //             maxP = maxArr[i + 1] - prices[i];
    //         }
    //     }

    //     return maxP;
    // }

    /*  Optimal Approach
        Intuition: We will linearly travel the array.
        We can maintain a minimum from the start of the array and compare it with every element of the array,
        if it is greater than the minimum then take the difference and maintain it in max,
        otherwise update the minimum.

        Time complexity: O(N)
        Space Complexity: O(1)
     */
    int maxProfit(vector<int> &arr)
    {
        int maxPro = 0;
        int n = arr.size();
        int minPrice = INT_MAX;

        for (int i = 0; i < arr.size(); i++)
        {
            minPrice = min(minPrice, arr[i]);
            maxPro = max(maxPro, arr[i] - minPrice);
        }

        return maxPro;
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
        // int k;
        // cin >> k;
        // cin.ignore();

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

        cout << ob.maxProfit(arr);

        cout << endl;
    }
}