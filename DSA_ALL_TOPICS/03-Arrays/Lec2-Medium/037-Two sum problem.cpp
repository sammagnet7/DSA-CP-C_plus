#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Two Sum : Check if a pair with given sum exists in Array

https://takeuforward.org/data-structure/two-sum-check-if-a-pair-with-given-sum-exists-in-array/
https://leetcode.com/problems/two-sum/description/

Problem Statement: Given an array of integers arr[] and an integer target.
1st variant: Return YES if there exist two numbers such that their sum is equal to the target. Otherwise, return NO
2nd variant: Return indices of the two numbers such that their sum is equal to the target. Otherwise, we will return {-1, -1}.
Note:
You may assume that each input would have exactly one solution.
You are not allowed to use the same element twice. Example: If the target is equal to 6 and num[1] = 3, then nums[1] + nums[1] = target is not a solution.


Examples:

Example 1:
Input Format: N = 5, arr[] = {2,6,5,8,11}, target = 14
Result: YES (for 1st variant)
        [1, 3] (for 2nd variant)
Explanation: arr[1] + arr[3] = 14. So, the answer is “YES” for the first variant and [1, 3] for 2nd variant.

Example 2:
Input Format: N = 5, arr[] = {2,6,5,8,11}, target = 15
Result: NO (for 1st variant)
        [-1, -1] (for 2nd variant)
Explanation: There exist no such two numbers whose sum is equal to the target.

INPUT::::::
5
14
2 6 5 8 11
15
2 6 5 8 11
9
2 7 11 15
6
3 2 4
6
3 3

OUTPUT::::::

1,3
-1,-1
0,1
1,2
0,1
 */
class Solution
{
public:
    /**
     * Approach 1: Hash Map (Unordered Map)
     * ------------------------------------
     * Idea:
     *  - For each element arr[i], compute the complement = target - arr[i].
     *  - If complement exists in hash map, return its index along with i.
     *  - Otherwise, store arr[i] in the hash map with its index.
     *
     * Time Complexity:
     *  - O(N) on average (each lookup and insert in unordered_map is O(1) average case).
     *  - O(N^2) in the worst case(which rarely happens), the unordered_map takes O(N) to find an element.
     *
     * Space Complexity:
     *  - O(N) for storing elements in the hash map.
     *
     * Notes:
     *  - Fastest practical solution.
     *  - Order of indices returned depends on the order of discovery.
     */
    vector<int> twoSum_hash(vector<int> &arr, int target)
    {
        vector<int> resp(2, -1);             // default return if no solution exists
        unordered_map<int, int> elem_idx_mp; // maps element value -> index

        for (int i = 0; i < arr.size(); i++)
        {
            int req = target - arr[i]; // complement needed to reach target

            // If complement already exists, solution found
            if (elem_idx_mp.find(req) != elem_idx_mp.end())
            {
                resp[0] = elem_idx_mp[req]; // index of complement
                resp[1] = i;                // current index
                return resp;
            }
            else
            {
                // Store current element with its index
                elem_idx_mp[arr[i]] = i;
            }
        }
        // If no valid pair found, return {-1,-1}
        return resp;
    }

    /**
     * Approach 2: Sorting + Two Pointers
     * ----------------------------------
     * Idea:
     *  - Pair each element with its index, then sort by value.
     *  - Use two pointers (l, r):
     *      * If sum == target → solution found.
     *      * If sum < target → move l forward to increase sum.
     *      * If sum > target → move r backward to decrease sum.
     *  - Return indices of the two elements.
     *
     * Time Complexity:
     *  - O(N log N) due to sorting.
     *
     * Space Complexity:
     *  - O(N) for storing value-index pairs.
     *
     * Notes:
     *  - Useful if you want indices but also sorted processing.
     *  - Slower than hash map approach but still efficient.
     */
    vector<int> twoSum_sort(vector<int> &arr, int target)
    {
        int n = arr.size();

        // Store elements with their original indices
        vector<pair<int, int>> val_id(n);
        for (int i = 0; i < n; i++)
        {
            val_id[i].first = arr[i]; // value
            val_id[i].second = i;     // index
        }

        // Sort pairs by value
        sort(val_id.begin(), val_id.end());

        int l = 0;
        int r = n - 1;

        // Two-pointer search
        while (l < r)
        {
            int sum = val_id[l].first + val_id[r].first;

            if (sum == target)
            {
                // Return original indices
                return {val_id[l].second, val_id[r].second};
            }
            else if (sum < target)
            {
                l++; // need bigger sum → move left pointer right
            }
            else
            {
                r--; // need smaller sum → move right pointer left
            }
        }

        // If no valid pair found
        return {-1, -1};
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
        int k;
        cin >> k;
        cin.ignore();

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

        vector<int> resp;
        resp = ob.twoSum_hash(arr, k);
        // resp = ob.twoSum_sort(arr, k);

        cout << resp[0] << "," << resp[1];

        cout << endl;
    }
}