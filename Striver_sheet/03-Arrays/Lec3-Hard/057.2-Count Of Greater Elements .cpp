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

using namespace std;

/*

1. Title: Count Of Greater Elements

Links:
https://www.geeksforgeeks.org/dsa/number-nges-right/
https://www.naukri.com/code360/library/number-of-nges-to-the-right
https://www.geeksforgeeks.org/problems/number-of-nges-to-the-right/1
https://www.naukri.com/code360/problems/count-of-greater-elements-to-the-right_8365436


Problem statement:
You are given an array 'arr' of length 'N'.
You are given 'Q' queries, and for each query, you are given an index(0-based indexing).
Answer to each query is the number of the strictly greater elements to the right of the given index element.
You must return an array 'answer' of length ’N’, where ‘answer[i]’ is the answer to the ‘ith’ query.

Examples:
    Input:
    arr = [5, 2, 10, 4], N=4, Q=2, query = [0, 1]
    Output:
    1 2
    Explanation: The element at index 0 is 5 for the first query. There is only one element greater than 5 towards the right, i.e., 10.
    For the second query, the element at index 1 is 2. There are two elements greater than 2 towards the right, i.e., 10 and 4.
    Hence we return [1, 2]

    Sample Input 1:
        8 3
        1 3 6 5 8 9 13 4
        0 1 5
    Sample Output 1:
        7 6 1
    Explanation Of Sample Input 1:
        For test case one:
        Input:
            arr = [1, 3, 6, 5, 8, 9, 13, 4], N=8, Q=3, query = [0, 1, 5]
        Output:
            7 6 1
        Explanation:
            The element at index 0 is 1 for the first query. There are seven elements greater than 1 towards the right, i.e., 3, 6, 5, 8, 9, 13, and 4.
            For the second query, the element at index 1 is 3. There are six elements greater than 3 towards the right, i.e., 6, 5, 8, 9, 13, and 4.
            For the third query, the element at index 5 is 9. There is only one element greater than 9 towards the right, i.e., 13.
            Hence we return [7, 6, 1].

    Sample Input 2:
        4 4
        1 2 3 4
        0 1 2 3
    Sample Output 2:
        3 2 1 0

Constraints:
    1 <= N <= 10^4
    1 <= Q <= 100
    1 <= arr[i] <= 10^5.
    0 <= query[i] <= ‘N’-1
    Time Limit: 1 sec


INPUT::::::


OUTPUT::::::

*/

/*
  Count of Greater Elements (for given query indices)
  --------------------------------------------------
  Problem:
    - Given an array `arr` and a list of query indices `query`, for each query index q
      we must return how many elements to the right of index q are strictly greater
      than arr[q].
    - More formally: for index i, count elements j > i such that arr[j] > arr[i].

  High-level approach (intuition):
    - This is very similar to the classic "count inversions" using merge-sort.
    - If we process the array with a divide-and-conquer merge-sort, the two halves
      become sorted. While merging, we can count how many elements in the right
      half are greater than a given element in the left half.
    - To preserve original positions (so we can answer queries about indices),
      we operate on pairs (value, original_index). The result for each original
      index is accumulated in geCount[index].
    - The key observation:
        When merging two sorted subarrays:
          left:  input[l..mid]  (sorted ascending by value)
          right: input[r..end]  (sorted ascending by value)
        If input[l].value < input[r].value, then input[l] is less than ALL elements
        in input[r..end] whose value > input[r].value. But since right is sorted,
        when input[l].value < input[r].value, **all** elements from r..end are > input[l].
        Thus we can add (end - r + 1) to geCount[ input[l].index ] in O(1).
    - After full merge-sort, geCount[i] contains the count of greater elements to
      the right of original index i. Answer queries by indexing geCount.

  Complexity:
    - customMerge: O(length of segment) per merge.
    - customMergeSort: O(n log n) overall.
    - Building input pairs: O(n).
    - Answering Q queries: O(Q).
    - Total: O(n log n + Q).
    - Space: O(n) auxiliary for pair vector + O(n) for tmp during merges → O(3n) in comments.

  Notes:
    - We use strictly greater (>) comparisons, matching the problem statement.
    - This method returns counts for every index; queries are then trivial lookups.
*/

/*
  Merge step that counts "greater elements on right" for left-side items.
  - ngeCount: vector<int> where ngeCount[idx] accumulates counts for original index idx.
  - input: vector<pair<value, original_index>> which is being sorted by value.
  - start, mid, end: current segment boundaries (inclusive).
*/
void customMerge(vector<int> &ngeCount, vector<pair<int, int>> &input, int start, int mid, int end)
{
    // tmp stores merged segment
    vector<pair<int, int>> tmp;

    int l = start;
    int r = mid + 1;

    // Merge while counting: when input[l].first < input[r].first,
    // then input[l] is less than ALL elements from r..end (because right is sorted).
    // Therefore, those (end - r + 1) elements are strictly greater than input[l].
    while (l <= mid && r <= end)
    {
        if (input[l].first < input[r].first)
        {
            tmp.push_back(input[l]);

            // Count how many elements in right half are strictly greater than input[l]
            ngeCount[input[l].second] += (end - r + 1);

            l++;
        }
        else
        {
            // input[l].first >= input[r].first: move the smaller (or equal) right item first
            tmp.push_back(input[r]);
            r++;
        }
    }

    // Copy remaining left items (they see no additional right items that weren't already counted)
    while (l <= mid)
    {
        tmp.push_back(input[l]);
        l++;
    }

    // Copy remaining right items
    while (r <= end)
    {
        tmp.push_back(input[r]);
        r++;
    }

    // Write merged segment back into input
    for (int i = start; i <= end; i++)
    {
        input[i] = tmp[i - start];
    }
}

/*
  Recursive merge-sort driver that sorts input[start..end] by value
  while updating ngeCount for elements in that segment.
*/
void customMergeSort(vector<int> &ngeCount, vector<pair<int, int>> &input, int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    // Recursively sort left and right halves
    customMergeSort(ngeCount, input, start, mid);
    customMergeSort(ngeCount, input, mid + 1, end);

    // Merge and count cross-segment greater elements
    customMerge(ngeCount, input, start, mid, end);
}

/*
  countGreater:
    - arr: original array of values
    - query: list of indices; for each index i in query we must return the number
             of elements to the right of i that are strictly greater than arr[i].
    - Returns: vector<int> of answers corresponding to query order.

  Steps:
    1) Build input vector of pairs (value, original_index).
    2) Run customMergeSort which fills geCount[index] for every index.
    3) For each query index, push geCount[idx] into the answer list.
*/
vector<int> countGreater(vector<int> &arr, vector<int> &query)
{
    int n = (int)arr.size();
    vector<int> ans;                 // O(Q)
    vector<pair<int, int>> input(n); // O(N): store {value, original_index}
    vector<int> geCount(n, 0);       // O(N): counts of greater elements to the right

    // Fill input pairs
    for (int i = 0; i < n; i++)
    {
        input[i] = {arr[i], i};
    }

    // Sort input by value while counting greater-right occurrences
    customMergeSort(geCount, input, 0, n - 1); // O(N log N)

    // Answer queries using precomputed counts
    for (int idx : query)
    {
        ans.push_back(geCount[idx]);
    }

    return ans;
}

int main()
{
    return 0;
}
