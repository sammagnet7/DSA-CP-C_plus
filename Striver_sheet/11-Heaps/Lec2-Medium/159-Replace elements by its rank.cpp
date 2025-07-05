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
#include <string.h>
#include <list>

using namespace std;

/*

1. Title: Replace elements by its rank in the array

Links:
https://takeuforward.org/data-structure/replace-elements-by-its-rank-in-the-array/
https://www.naukri.com/code360/problems/replace-each-element-of-array-with-its-corresponding-rank_975384?leftPanelTabValue=PROBLEM


Problem statement:
Given an array of integers 'ARR’ of size ‘N’. Replace each element of this array with its corresponding rank and return the array.

The rank of an element is an integer between 1 to ‘N’ inclusive that represents how large the element is in comparison to other elements of the array. The following rules can also define the rank of an element:

1. It is an integer starting from 1.
2. The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
3. It should be as small as possible.


For Example:
'ARR' = [4, 7, 2, 90]
Here, 2 is the smallest element, followed by 4, 7, and 90.
Hence rank of element 2 is 1, element 4 is 2, element 7 is 3, and element 90 is 4.
Hence we return [2, 3, 1, 4].


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Replace elements by its rank in the array
  //-------------------------------------------------------------------------------

  // -------------------------------
  // Approach1: Sub-optimal
  //

  // // Sub-optimal approach
  // // time: O(N^2) ~ o(N^3)
  // // Space: O(2N) including `ans` space
  // vector<int> replaceWithRank(vector<int> &arr, int n) {

  //     int N = arr.size();
  //     vector<int> ans(N); // space: O(N)

  //     for(int i=0; i<N; i++){ // O(N)

  //         unordered_set<int> lessEls; // space: O(N)

  //         for(int j=0; j<N; j++){ // O(N)

  //             if(arr[j] < arr[i])
  //                 lessEls.insert(arr[j]);  // Avg(1) ~ O(N)
  //         }

  //         ans[i] = lessEls.size()+1;
  //     }

  //     return ans;
  // }

  // -------------------------------
  // Approach2: Optimal
  //

  // Optimal approach
  // Time: O(N Log N + 3N)
  // Space: O(3N)
  vector<int> replaceWithRank(vector<int> &arr, int n)
  {
    // Write your code here.

    unordered_set<int> st(arr.begin(), arr.end()); // space: O(N)

    vector<int> rank(st.begin(), st.end()); // space: O(N)
    sort(rank.begin(), rank.end());         // O(n log n)

    unordered_map<int, int> mp; // space: O(uniqs)

    for (int i = 0; i < rank.size(); i++)
    { // O(uniqs)
      mp[rank[i]] = i + 1;
    }

    for (int i = 0; i < arr.size(); i++)
    { // O(N)
      arr[i] = mp[arr[i]];
    }

    return arr;
  }
};

int main()
{
  return 0;
}
