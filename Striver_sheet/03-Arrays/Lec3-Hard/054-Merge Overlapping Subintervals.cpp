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

    // Approach: Optimal
    // Note: Using for-each loop slows down. So use index based loop
    // Time: O(N Log N)
    // Space: O(1)
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int N = intervals.size();
        vector<vector<int>> resp;
        int idx = -1;

        sort(intervals.begin(), intervals.end());

        for (int i = 0; i < N; i++)
        {
            int start = intervals[i][0];
            int end = intervals[i][1];

            if (resp.size() == 0)
            { // 1st element
                resp.push_back({start, end});
            }
            else if (start <= resp.back()[1])
            { // If in previous range then merge
                if (end > resp.back()[1])
                    resp.back()[1] = end;
            }
            else
            { // add new entry
                resp.push_back({start, end});
            }
        }

        return resp;
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