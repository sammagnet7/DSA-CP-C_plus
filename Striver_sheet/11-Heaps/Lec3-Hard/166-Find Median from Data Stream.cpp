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

1. Title: Find Median from Data Stream

Links:
https://takeuforward.org/plus/dsa/problems/find-median-from-data-stream
https://leetcode.com/problems/find-median-from-data-stream/description/


Problem statement:
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.


Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0


Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.


Follow up:

Q1. If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
Q2. If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?

Ans1:
  🧠 Optimized Plan
  🔧 Data Structures:
  vector<int> freq(101, 0) → frequency of each number in [0, 100]

  int count → total number of elements added so far

  📌 Operations
  addNum(int num)
  Just increment freq[num]

  Increment count

  🕒 Time: O(1)
  🧠 Space: O(1) (since 101 fixed entries)

  findMedian()
  For odd count: find the middle element

  For even count: find the two middle elements and average them

  Use a simple pass over the frequency array to find the k-th elements.

  🕒 Time: O(100) (technically O(1) because 100 is a constant)

-----------------------------------------------------------


Ans2:
  ⚒️ Strategy
  🔹 Data Structures
  vector<int> freq(101, 0) → frequency for range [0, 100]

  Two heaps for outliers:

  maxHeap (left side): elements < 0

  minHeap (right side): elements > 100

  int totalCount → total numbers added


INPUT::::::


OUTPUT::::::


*/

//-------------------------------------------------------------------------------
// 1. Title: Find Median from Data Stream
//-------------------------------------------------------------------------------

// Optimal approach: Using 2 heaps
class MedianFinder
{
public:
  priority_queue<int> pqmx_left;                             // max heap
  priority_queue<int, vector<int>, greater<int>> pqmn_right; // min heap
  // long long size;

  MedianFinder()
  {
    // size = 0;
  }

  void addNum(int num)
  { // O(Log N)
    // size++;

    if (!pqmx_left.empty() && num < pqmx_left.top())
    {
      pqmx_left.push(num);
    }
    else
    {
      pqmn_right.push(num);
    }

    // int medPQLen = size/2 +1;

    // while(pqmx_left.size() < medPQLen){
    //     pqmx_left.push(pqmn_right.top());
    //     pqmn_right.pop();
    // }

    // while(pqmx_left.size() > medPQLen){
    //     pqmn_right.push(pqmx_left.top());
    //     pqmx_left.pop();
    // }

    if (pqmx_left.size() > pqmn_right.size())
    {
      pqmn_right.push(pqmx_left.top());
      pqmx_left.pop();
    }

    else if (pqmx_left.size() < pqmn_right.size())
    {
      pqmx_left.push(pqmn_right.top());
      pqmn_right.pop();
    }
  }

  // another approach
  // double findMedian() {

  //     if(size%2 == 0){    // even
  //         int mdL = pqmx_left.top();
  //         pqmx_left.pop();
  //         int mdR = pqmx_left.top();
  //         pqmx_left.push(mdL);

  //         return ((double)mdL+ (double)mdR) /2;
  //     }
  //     else{   // odd
  //         return pqmx_left.top();
  //     }
  // }

  double findMedian()
  { // O(1)

    if (pqmx_left.size() == pqmn_right.size())
    {
      return ((double)(pqmx_left.top() + pqmn_right.top()) / 2.0);
    }
    else
    {
      return (pqmx_left.size() > pqmn_right.size()) ? pqmx_left.top() : pqmn_right.top();
    }
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
  return 0;
}
