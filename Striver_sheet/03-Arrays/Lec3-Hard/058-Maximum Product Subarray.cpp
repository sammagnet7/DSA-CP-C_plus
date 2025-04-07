#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Maximum Product Subarray in an Array

https://takeuforward.org/data-structure/maximum-product-subarray-in-an-array/
https://leetcode.com/problems/maximum-product-subarray/
https://www.naukri.com/code360/problems/subarray-with-maximum-product_6890008?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem statement:
Given an array that contains both negative and positive integers, find the maximum product subarray.

Note: What is an inversion of an array? Definition: for all i & j < size of array, if i < j then you have to find pair (A[i],A[j]) such that A[j] < A[i].

Examples:

Example 1:
Input:  Nums = [1,2,3,4,5,0]
Output: 120
Explanation:    In the given array, we can see 1×2×3×4×5 gives maximum product value.

Example 2:
Input:  Nums = [1,2,-3,0,-4,-5]
Output: 20
Explanation:    In the given array, we can see (-4)×(-5) gives maximum product value.

Example 3:
Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 4:
Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.


INPUT::::::
3
1 2 3 4 5
5 4 3 2 1
5 3 2 1 4

OUTPUT::::::
120
20
6
0
24

 */
class Solution
{
public:
    // Approach: Optimal :: kadane's algo
    // Intuition: Maintain min_prod for largest -ve product till now. maintain max_prod for largest +ve product till now. Take Max of these.
    // Time: O(N)
    // Spae: O(1)
    int maxProduct(vector<int> &arr)
    {
        int max_prod = 1, min_prod = 1;
        int ans = INT_MIN;

        for (int e : arr)
        {
            int temp1 = max({e, (max_prod * e), (min_prod * e)});
            int temp2 = min({e, (max_prod * e), (min_prod * e)});

            max_prod = temp1;
            min_prod = temp2;

            ans = max(ans, max_prod);
        }

        return ans;
    }

    // // Approach: Optimal :: Prefix and postfix product
    // // Max product will be product of an array having no -ve or an array with even -ve elements.
    // // So in odd -ve elements' case either remove the 1st -ve or last -ve element.
    // // Time: O(N)
    // // Spae: O(1)
    // int maxProduct(vector<int>& arr) {
    //     int N= arr.size();
    //     int pre_prod=1, post_prod=1;
    //     int max_prod=INT_MIN;

    //     for(int i=0; i<N; i++){
    //         if(pre_prod == 0) pre_prod=1;    // Handling zero values
    //         if(post_prod == 0) post_prod=1;  // Handling zero values

    //         pre_prod *= arr[i];
    //         post_prod *= arr[N-1-i];

    //         max_prod = max({max_prod, pre_prod, post_prod});
    //     }

    //     return max_prod;
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

        cout << ob.maxProduct(arr);
        cout << endl;
    }
    return 0;
}