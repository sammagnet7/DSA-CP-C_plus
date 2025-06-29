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

1. Title: Number of NGEs to the right

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
    Explanation: The element at index 0 is 1 for the first query. There are seven elements greater than 1 towards the right, i.e., 3, 6, 5, 8, 9, 13, and 4.
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

//-----------------------------------------------------------------------
// 1. Title: Number of NGEs to the right
// Uses Merge sort approach similar to `Counting inverses`

// O(N)
void customMerge(vector<int> &ngeCount, vector<pair<int, int>> &input, int start, int mid, int end)
{

    vector<pair<int, int>> tmp;

    int l = start;
    int r = mid + 1;

    while (l <= mid && r <= end)
    {

        if (input[l].first < input[r].first)
        {
            tmp.push_back(input[l]);

            ngeCount[input[l].second] += (end - r + 1); // Most important step which takes the count of nges

            l++;
        }
        else if (input[l].first >= input[r].first)
        {
            tmp.push_back(input[r]);
            r++;
        }
    }

    while (l <= mid)
    {
        tmp.push_back(input[l]);
        l++;
    }
    while (r <= end)
    {
        tmp.push_back(input[r]);
        r++;
    }

    for (int i = start; i <= end; i++)
    {
        input[i] = tmp[i - start];
    }
}

// O(N Log N)
void customMergeSort(vector<int> &ngeCount, vector<pair<int, int>> &input, int start, int end)
{

    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    customMergeSort(ngeCount, input, start, mid);
    customMergeSort(ngeCount, input, mid + 1, end);

    customMerge(ngeCount, input, start, mid, end);
}

// Optimal approach: using merge sort to divide the problem into subproblem
// Similar approach of `counting inversions`
//
// Time: O(N+ Q + N Log N)
// Space: O(3 N)
vector<int> countGreater(vector<int> &arr, vector<int> &query)
{
    // Write your code here.
    vector<int> ans; // O(Q)

    vector<pair<int, int>> input(arr.size()); // O(N): creating a duplicate `input` array to store pair of {value, index}
    vector<int> ngeCount(arr.size(), 0);      // O(N)

    for (int i = 0; i < arr.size(); i++)
    { // O(N)
        input[i] = {arr[i], i};
    }

    customMergeSort(ngeCount, input, 0, (input.size() - 1)); // O(N Log N)

    for (int idx : query)
    { // O(Q)
        ans.push_back(ngeCount[idx]);
    }

    return ans;
}

int main()
{
    return 0;
}
