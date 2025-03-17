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
    // Approach: Hashing
    // Time: O(N) or O(N Log N)
    // In the worst case(which rarely happens), the unordered_map takes O(N) to find an element. In that case, the time complexity will be O(N2). If we use map instead of unordered_map, the time complexity will be O(N* logN) as the map data structure takes logN time to find an element.
    // Space: O(N) for Map
    vector<int> twoSum(vector<int> &arr, int target)
    {
        vector<int> resp(2, -1);
        unordered_map<int, int> elem_idx_mp;

        for (int i = 0; i < arr.size(); i++)
        {
            int req = target - arr[i];

            if (elem_idx_mp.find(req) != elem_idx_mp.end())
            {
                resp[0] = elem_idx_mp[req];
                resp[1] = i;
                return resp;
            }
            else
            {
                elem_idx_mp[arr[i]] = i;
            }
        }
        return resp;
    }

    // Approach: Two pointer
    // Time: O(N LogN): To sort array
    // Space: O(N): To keep another array for maintaining indexes
    // vector<int> twoSum(vector<int> &arr, int target)
    // {
    //     vector<int> resp(2, -1);
    //     sort(arr.begin(), arr.end());
    //     int left = 0, right = arr.size() - 1;

    //     for (int i = 0; i < arr.size(); i++)
    //     {
    //     }
    //     return resp;
    // }
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
        resp = ob.twoSum(arr, k);
        cout << resp[0] << "," << resp[1];

        cout << endl;
    }
}