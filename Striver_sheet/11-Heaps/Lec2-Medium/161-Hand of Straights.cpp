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

1. Title: Hand of Straights
or Divide Array in Sets of K Consecutive Numbers

Links:
https://leetcode.com/problems/hand-of-straights/description/


Problem statement:
Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize, and consists of groupSize consecutive cards.

Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize, return true if she can rearrange the cards, or false otherwise.

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
Example 2:

Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.


Linke:
https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/description/


Problem statement:
Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.

Return true if it is possible. Otherwise, return false.

Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].
Example 3:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.

INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Hand of Straights or Divide Array in Sets of K Consecutive Numbers
  //-------------------------------------------------------------------------------

  // -------------------------------
  // Approach1: Optimal
  //

  /**
   * Checks if the array `nums` can be divided into sets of `k` consecutive numbers.
   *
   * Process:
   * - Count the frequency of each number using a map.
   * - Repeatedly take the smallest available number and try to form a group of size `k`
   *   with consecutive elements [start, start+1, ..., start+k-1].
   * - Reduce the count of each element used. If any required number is missing, return false.
   *
   * Time Complexity: O(N log N)
   *   - N is the number of elements in nums.
   *   - log N factor comes from map operations (insert/find/erase).
   *
   * Space Complexity: O(N)
   *   - To store the frequency map.
   */
  bool isNStraightHand(vector<int> &nums, int k)
  {

    // If the total number of elements is not divisible by k, it's impossible
    if (nums.size() % k != 0)
      return false;

    // Frequency map to count each number
    map<int, int> mp;
    for (int num : nums)
    {
      mp[num]++;
    }

    // Try to divide the array into sets of size k with consecutive numbers
    while (!mp.empty())
    {

      // Start from the smallest available number
      int start = mp.begin()->first;

      // Use one occurrence of the starting number
      mp[start]--;
      if (mp[start] == 0)
        mp.erase(start);

      // Check for the next k - 1 consecutive numbers
      for (int i = start + 1; i <= start + k - 1; i++)
      {

        // If the next number is not found, return false
        if (mp.find(i) == mp.end())
          return false;

        // Use one occurrence of the number
        mp[i]--;
        // If frequency becomes 0, remove it from the map
        if (mp[i] == 0)
          mp.erase(i);
      }
    }

    // Successfully divided all elements into required sets
    return true;
  }
};

int main()
{
  return 0;
}
