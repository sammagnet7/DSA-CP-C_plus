#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Merge Overlapping Sub-intervals

https://takeuforward.org/data-structure/merge-overlapping-sub-intervals/
https://leetcode.com/problems/merge-intervals/submissions/1594108434/
https://www.naukri.com/code360/problems/merge-all-overlapping-intervals_6783452?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem statement:
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

Constraints:
1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104

Examples:

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


INPUT::::::
6
[1 3] [2 6] [8 10] [15 18]
[1 4] [4 5]
[1 4] [0 4]
[1 4] [2 3]
[2 3] [4 5] [6 7] [8 9] [1 10]
[1 4] [5 6]

OUTPUT::::::
[1 6] [8 10] [15 18]
[1 5]
[0 4]
[1 4]
[1 10]
[1 4] [5 6]


 */
class Solution
{
public:
    // // Approach: Better
    // // Little slower because every time storing the range array
    // // Time: O(N Log N)
    // // Space: O(2)
    // vector<vector<int>> merge(vector<vector<int>> &intervals)
    // {

    //     vector<vector<int>> resp;
    //     int idx = -1;

    //     sort(intervals.begin(), intervals.end());

    //     vector<int> prevRange(2, INT_MIN);

    //     for (auto range : intervals)
    //     {

    //         int l = range[0];
    //         int r = range[1];

    //         if (l <= prevRange[1])
    //         {
    //             if (r > prevRange[1])
    //                 resp[idx][1] = r;
    //         }
    //         else
    //         {
    //             resp.push_back({l, r});
    //             idx++;
    //         }
    //         prevRange = resp[idx];
    //     }

    //     return resp;
    // }

    /*
        merge
        -----
        Problem:
            - Given a list of intervals [start, end], merge all overlapping intervals.
            - Return the resulting list of non-overlapping intervals covering the same ranges.

        Approach:
            1. Sort intervals by their start time (and implicitly by end if starts equal).
            - Sorting ensures that when we scan intervals in order, any overlapping
                intervals must be adjacent in this sorted list.
            2. Maintain a result vector `ans` to store merged intervals.
            3. For each interval:
                - If `ans` is empty → push current interval.
                - Else compare current interval [lr_cur, rr_cur] with the last interval in ans [lr_back, rr_back]:
                    * Case 1: No overlap (rr_back < lr_cur):
                        → Push current interval as a new entry.
                    * Case 2: Overlap and current interval extends beyond rr_back (rr_back < rr_cur):
                        → Merge by extending ans.back()[1] to rr_cur.
                    * Case 3: Overlap but current interval is fully contained (rr_cur ≤ rr_back):
                        → Do nothing (last interval already covers current).
            4. Return ans.

        Intuition:
            - Sorting by start ensures intervals either overlap with the last merged interval or start after it.
            - So we only ever need to check against the last interval in `ans`.
            - This greedy approach guarantees merging correctness.

        Complexity:
            - Sorting: O(n log n).
            - Single pass scan: O(n).
            - Total: O(n log n).
            - Space: O(n) for storing merged intervals.

        Example walkthrough:
            intervals = [[1,3], [2,6], [8,10], [15,18]]
            After sorting: [[1,3], [2,6], [8,10], [15,18]]
            ans = []
            - Take [1,3] → ans = [[1,3]]
            - Take [2,6], overlaps with [1,3] → merge → ans = [[1,6]]
            - Take [8,10], no overlap → ans = [[1,6],[8,10]]
            - Take [15,18], no overlap → ans = [[1,6],[8,10],[15,18]]

        Correctness:
            - Works because sorting ensures any overlap must be adjacent.
            - Greedy merge keeps intervals compact without missing any.
    */
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int n = intervals.size();

        // Step 1: sort by start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;

        // Step 2: iterate through intervals
        for (int i = 0; i < n; i++)
        {
            int lr_cur = intervals[i][0]; // current interval left
            int rr_cur = intervals[i][1]; // current interval right

            int lr_back = ans.empty() ? -1 : ans.back()[0]; // last merged interval left
            int rr_back = ans.empty() ? -1 : ans.back()[1]; // last merged interval right

            if (ans.empty())
            {
                // Case: first interval
                ans.push_back({lr_cur, rr_cur});
            }
            else if (rr_back < lr_cur)
            {
                // Case 1: no overlap
                ans.push_back({lr_cur, rr_cur});
            }
            else if (rr_back < rr_cur)
            {
                // Case 2: overlap and extend
                ans.back()[1] = rr_cur;
            }
            // Case 3: overlap but contained → do nothing
        }

        return ans;
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

        vector<vector<int>> intervals;
        stringstream ss(input);
        char ch;
        int num1, num2;

        while (ss >> ch >> num1 >> num2 >> ch)
        { // Parsing "[x y]"
            intervals.push_back({num1, num2});
        }

        Solution ob;
        vector<vector<int>> res = ob.merge(intervals);

        for (size_t i = 0; i < res.size(); i++)
        {
            cout << "[" << res[i][0] << " " << res[i][1] << "]";
            if (i != res.size() - 1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}