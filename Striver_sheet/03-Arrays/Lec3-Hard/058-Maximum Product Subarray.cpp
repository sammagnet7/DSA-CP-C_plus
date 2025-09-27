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


Examples:

Example 1:
Input:  Nums = [1,2,3,4,5,0]
Output: 120
Explanation:    In the given array, we can see 1×2×3×4×5 gives maximum product value.

Example 2:
Input:  Nums = [1,2,-3,0,-4,-5]
Output: 20
Explanation:    In the given array, we can see
Note: What is an inversion of an array? Definition: for all i & j < size of array, if i < j then you have to find pair (A[i],A[j]) such that A[j] < A[i]. (-4)×(-5) gives maximum product value.

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
    /*
        [NOT INTUITIVE: DON'T GO WITH THIS APPROACH  ❌]
        Approach 1: Dynamic Kadane-like method for Maximum Product Subarray
        ------------------------------------------------------------------
        Intuition / idea:
            - For sum-subarray problems Kadane's algorithm keeps one running max.
            For product we must track two values at each step:
                * max_prod: the maximum product of a subarray ending at current element
                * min_prod: the minimum product of a subarray ending at current element
            Why two values?
                - A negative number flips signs: a very small (large negative) product
                multiplied by a negative current element can become the new maximum.
                - So we keep both the best positive product and the most negative product
                (which could become large positive later).
            - At each element e we consider three possibilities for new subarray ending here:
                1) start fresh at e
                2) extend previous max_prod by e
                3) extend previous min_prod by e
            The new max_prod is the maximum of those; the new min_prod is the minimum.
            - Track the global maximum `ans` over all positions.

        Correctness sketch:
            - The recurrence considers every subarray that ends at the current index:
            either it is only `e` or it extends a prior subarray (tracked via max_prod/min_prod).
            - By keeping both extremes we correctly handle sign flips caused by negatives.

        Edge cases handled:
            - Zero resets influence: multiplying by zero yields zero, and later starting a new subarray
            at the next element is considered since we include `e` as a candidate.
            - Single-element arrays and all-negative arrays are handled naturally.

        Complexity:
            - Time: O(N) — one pass through the array.
            - Space: O(1) — just a few variables.

        Note:
            - Uses int arithmetic; if products may overflow 32-bit, use 64-bit types.
        */
    // int maxProduct(vector<int> &arr)
    // {
    //     int max_prod = 1;  // maximum product ending at previous index
    //     int min_prod = 1;  // minimum product (most negative) ending at previous index
    //     int ans = INT_MIN; // global maximum product seen so far

    //     for (int e : arr)
    //     {
    //         // compute possible candidates using previous max/min and current element
    //         int temp1 = max({e, (max_prod * e), (min_prod * e)}); // new max ending here
    //         int temp2 = min({e, (max_prod * e), (min_prod * e)}); // new min ending here

    //         max_prod = temp1;
    //         min_prod = temp2;

    //         // update global answer
    //         ans = max(ans, max_prod);
    //     }

    //     return ans;
    // }


    /*
      [INTUITIVE : GO WITH THIS APPROACH ✅]
      Approach 2: Prefix & Postfix product scan (another intuitive O(N) method)
      -------------------------------------------------------------------------
      Intuition / idea:
        - Consider the product of every prefix (from left) and every prefix from the right
          (postfix when viewed from left to right). The maximum subarray product will be
          one of these prefix or postfix cumulative products after handling zeros.
        - More concretely:
            * If there are an even number of negatives in the subarray, the product is positive;
              including the whole span gives the max.
            * If odd number of negatives, we can drop either the prefix up to the first negative
              or the suffix after the last negative to make it even — effectively this corresponds
              to checking prefix products and suffix products.
        - By scanning forward and backward simultaneously, and resetting product to 1 when encountering 0,
          we capture candidates for maximum product subarrays without explicitly enumerating endpoints.

      How it works step-by-step:
        - pre_prod accumulates product from left to right.
        - post_prod accumulates product from right to left (by accessing arr[N-1-i]).
        - On encountering zero, reset the corresponding product to 1 because subarrays crossing the zero
          cannot have product larger than zero (and we can start a new subarray after the zero).
        - At each step update max_prod with pre_prod and post_prod. This covers subarrays that end at i
          and start at i respectively and effectively considers trimming first/last negatives when necessary.

      Edge cases handled:
        - Zeros: reset product and continue; a single zero may itself be the maximum if all other products are negative.
        - All-negative arrays: the best will be captured by prefix/postfix behavior (keeping appropriate trims).
        - Single-element arrays naturally handled.

      Complexity:
        - Time: O(N) — a single scan with two accumulators.
        - Space: O(1) — constant extra memory.

      Notes:
        - This method is very concise and often easier to implement. It is especially elegant
          when combined with the trick of resetting to 1 on zero.
        - Both approaches are valid; Kadane-like method is more standard and explicitly maintains
          the necessary state (max/min). Prefix/postfix is a neat alternative that relies on symmetry.
        - Again, use 64-bit if intermediate products can overflow int.
    */
    int maxProduct(vector<int> &arr)
    {
        int N = (int)arr.size();
        int pre_prod = 1, post_prod = 1;
        int max_prod = INT_MIN;

        for (int i = 0; i < N; i++)
        {
            // Reset on zero because product of any subarray containing zero is zero,
            // and future subarrays should start fresh after zero.
            if (pre_prod == 0)
                pre_prod = 1;
            if (post_prod == 0)
                post_prod = 1;

            pre_prod *= arr[i];
            post_prod *= arr[N - 1 - i];

            max_prod = max({max_prod, pre_prod, post_prod});
        }

        return max_prod;
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

        cout << ob.maxProduct(arr);
        cout << endl;
    }
    return 0;
}