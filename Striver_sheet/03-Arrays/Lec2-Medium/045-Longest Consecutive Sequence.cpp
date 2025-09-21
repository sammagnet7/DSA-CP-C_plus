#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Longest Consecutive Sequence in an Array

https://takeuforward.org/data-structure/longest-consecutive-sequence-in-an-array/
https://leetcode.com/problems/longest-consecutive-sequence/description/
https://www.naukri.com/code360/problems/longest-successive-elements_6811740?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem statement:
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

Note:
You must write an algorithm that runs in O(n) time.
You can reorder the array to form a sequence.

Examples:
Input:
A = [5, 8, 3, 2, 1, 4], N = 6
Output:
5
Explanation:
The resultant sequence can be 1, 2, 3, 4, 5.
The length of the sequence is 5.

Input:
 [100, 200, 1, 3, 2, 4]
Output:
 4
Explanation:
 The longest consecutive subsequence is 1, 2, 3, and 4.

Input:
 [3, 8, 5, 7, 6]
Output:
 4
Explanation:
 The longest consecutive subsequence is 5, 6, 7, and 8.

INPUT::::::
7
1 2 3
2 3 1 4 5
1 2
3 1 2
1 3 2
3 2 1
1 1 5

OUTPUT::::::

5
4
9
3
4
4
 */

class Solution
{
public:
    /**
     * Longest Consecutive Sequence — Sorting Approach
     * ----------------------------------------------
     * Idea:
     *   - Sort the array.
     *   - Traverse sorted array and count lengths of consecutive increasing runs.
     *   - Handle duplicates: skip when arr[i] == arr[i-1].
     *   - Track maximum consecutive length.
     *
     * Time Complexity:  O(N log N) [due to sorting]
     * Space Complexity: O(1) extra (ignoring sorting cost)
     *
     * Notes:
     *   - Simpler but slower than set-based approach.
     */

    int longestConsecutive_sort(vector<int> &arr)
    {
        if (arr.empty())
            return 0;

        sort(arr.begin(), arr.end());

        int count = 1; // current consecutive streak
        int maxC = 1;  // maximum streak found

        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] == arr[i - 1] + 1)
            {
                // Extend consecutive streak
                count++;
                maxC = max(maxC, count);
            }
            else if (arr[i] == arr[i - 1])
            {
                // Duplicate element → ignore
                continue;
            }
            else
            {
                // Break in sequence → reset streak
                count = 1;
            }
        }

        return maxC;
    }

    /*  Optimal approach: Using Set
        Intuition:
            1. remove duplicates by storing into Set
            2. For each element check if it can be starting element of a sequence of not by checking if one lesser than this element is present in the Set or not
            3. If not starting element then skip.
            4. If it is a starting element then keeping it as the initial element try finding the sequence by searching inside the set.
        Time: O(2N) As to create unordered set it takes O(N) and after that the set is getting traversed only Once.
                    (If not starting, then skip. If startng then find rest in sequence)
        Space: O(N)
    */

    /**
     * Longest Consecutive Sequence — Optimal Approach (Set)
     * -----------------------------------------------------
     * Intuition:
     *   1. Insert all numbers into an unordered_set to remove duplicates
     *      and allow O(1) lookups.
     *   2. For each element, check if it is the **start of a sequence**:
     *        - A number is a start if (num - 1) is not in the set.
     *   3. If it’s a start, count how long the consecutive run continues
     *      by repeatedly checking (num + 1), (num + 2), ...
     *   4. Track the longest run.
     *
     * Time Complexity:
     *   - O(N) average
     *   - Building set = O(N), checking sequences = O(N) total
     *   - Each element is processed at most twice (once as potential start,
     *     once in a sequence).
     *
     * Space Complexity: O(N) for the set
     *
     * Notes:
     *   - More efficient than sorting-based approach for large arrays.
     */
    int longestConsecutive(vector<int> &arr)
    {
        // creating set from the given array
        unordered_set<int> eset(arr.begin(), arr.end());
        int maxC = 0;

        for (auto curr : eset)
        {
            int pre = curr - 1;

            if (eset.find(pre) != eset.end())
            {
                // curr element is not starting of the sequence
                continue;
            }
            else
            { // this element is starting of a possible sequence. So start checking
                int count = 1;
                int next = curr + 1;
                while (eset.find(next) != eset.end())
                {
                    count++;
                    next++;
                }
                maxC = max(count, maxC);
            }
        }

        return maxC;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the tailing newline char
    cout << endl;

    while (t--)
    {
        // int k;
        // cin >> k;
        // cin.ignore();

        string input;
        getline(cin, input);
        stringstream ss(input);

        vector<int> arr;
        int num;
        while (ss >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr.push_back(num);
        }

        Solution ob;
        // vector<int> res;
        // res = ob.leaders(arr);

        // for (int e : res)
        // {
        //     cout << e << " ";
        // }
        cout << ob.longestConsecutive(arr);

        cout << endl;
    }
}