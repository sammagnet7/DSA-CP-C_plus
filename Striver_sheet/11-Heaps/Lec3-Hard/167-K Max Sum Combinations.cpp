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

1. Title: K Max Sum Combinations

Links:
https://www.naukri.com/code360/problems/k-max-sum-combinations_975322?leftPanelTabValue=PROBLEM
https://placewit.medium.com/k-max-sum-combinations-2c6d67a3acb


Problem statement:
You are given two arrays/lists ‘A’ and ‘B’ of size ‘N’ each. You are also given an integer ‘K’. You must return ‘K’ distinct maximum and valid sum combinations from all the possible sum combinations of the arrays/lists ‘A’ and ‘B’.
Sum combination adds one element from array ‘A’ and another from array ‘B’.

For example :
  A : [1, 3]
  B : [4, 2]
  K: 2

  The possible sum combinations can be 5(3 + 2), 7(3 + 4), 3(1 + 2), 5(1 + 4).
  The 2 maximum sum combinations are 7 and 5.

  Sample Input 1 :
  3 2
  1 3 5
  6 4 2
  Sample Output 1 :
  11 9
  Explanation of Sample Output 1 :
  For the given arrays/lists, all the possible sum combinations are:
  7(1 + 6), 5(1 + 4), 3(1 + 2), 9(3 + 6), 7(3 + 4), 5(3 + 2), 11(6 + 5), 9(5 + 4), 7(5 + 2).
  The two maximum sum combinations from the above combinations are 11 and 9.

  Sample Input 2 :
  2 1
  1 1
  1 1
  Sample Output 2 :
  2
  Explanation of sample input 2 :
  For the given arrays/lists, two possible sum combinations are 2(1 + 1), and 2(1 + 1).

Constraints :
1 <= N <= 100
1 <= K <= N
-10^5 <= A[i], B[i] <= 10^5

'A[i]' and 'B[i]' denote the ith element in the given arrays/lists.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: K Max Sum Combinations
  //-------------------------------------------------------------------------------

  // Approach1:
  // Sub-optimal approach

  // //Brute force
  // // Time: O(N^2*Log k)
  // // Space: O(K)
  // vector<int> kMaxSumCombination(vector<int> &a, vector<int> &b, int n, int k){

  // 	priority_queue<int, vector<int>, greater<int>> pq;

  // 	for(int i: a){
  // 		for(int j: b){
  // 			pq.push((i+j));

  // 			if(pq.size()>k){
  // 				pq.pop();
  // 			}
  // 		}
  // 	}

  // 	vector<int> ans(k);

  // 	for(int i=k-1; i>=0; i--){
  // 		ans[i] = pq.top();
  // 		pq.pop();
  // 	}

  // 	return ans;
  // }

  //------------------------------------
  // Approach2:
  // Optima solution:

  /*
   * Function to find K maximum sum combinations from two arrays.
   *
   * Time Complexity:
   * - Sorting: O(N log N)
   * - Each heap operation: O(log K)
   * - We perform up to K operations ? Total: O(N log N + K log K)
   *
   * Space Complexity:
   * - Heap: O(K)
   * - Visited set: O(K)
   * - Result array: O(K)
   */
  vector<int> kMaxSumCombination(vector<int> &a, vector<int> &b, int n, int k)
  {
    // Write your code here.

    // Step 1: Sort both arrays in descending order
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    // Step 3: Visited set to avoid pushing same pair again ? O(1) init
    set<pair<int, int>> uniqIdxPair;

    // To store final top-K sums ? O(K) space
    vector<int> ans;

    // Step 2: Initialize a max-heap to store {sum, indexA, indexB} ? O(1)
    priority_queue<tuple<int, int, int>> pq;

    // Step 4: Push the first (maximum) pair sum ? O(log 1) = O(1)
    pq.push(make_tuple(a[0] + b[0], 0, 0));
    uniqIdxPair.insert({0, 0});

    // Step 5: Extract top K combinations from heap ? O(K log K)
    while (ans.size() < k)
    {

      tuple<int, int, int> t = pq.top();

      int curMaxSum = get<0>(t);
      int i = get<1>(t);
      int j = get<2>(t);

      pq.pop(); // O(log K)

      ans.push_back(curMaxSum);

      // Push next combination from A (i+1, j) if not visited
      if (i + 1 < a.size() && (uniqIdxPair.find({(i + 1), j})) == uniqIdxPair.end())
      {
        pq.push(make_tuple((a[i + 1] + b[j]), (i + 1), j)); // O(log K)
        uniqIdxPair.insert({(i + 1), j});                   // O(log K)
      }

      // Push next combination from B (i, j+1) if not visited
      if (j + 1 < b.size() && (uniqIdxPair.find({i, (j + 1)})) == uniqIdxPair.end())
      {
        pq.push(make_tuple((a[i] + b[j + 1]), i, (j + 1))); // O(log K)
        uniqIdxPair.insert({i, (j + 1)});                   // O(log K)
      }
    }

    return ans;
  }
};

int main()
{
  return 0;
}
