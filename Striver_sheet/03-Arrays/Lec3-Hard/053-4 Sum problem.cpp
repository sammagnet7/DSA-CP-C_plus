#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
4 Sum | Find Quads that add up to a target value

https://takeuforward.org/data-structure/4-sum-find-quads-that-add-up-to-a-target-value/
https://leetcode.com/problems/4sum/description/
https://www.naukri.com/code360/problems/4sum_5713771?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem statement:
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Examples:

Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]


INPUT::::::
7
0
1 0 -1 0 -2 2
9
4 3 3 4 4 2 1 2 1 1
8
2 2 2 2 2
5
1 2 1 0 1
8
2 2 2 2 1 3
4
1 1 1 0
0
1000000000 1000000000 1000000000 1000000000

OUTPUT::::::

[[-2 -1 1 2 ][-2 0 0 2 ][-1 0 0 1 ]]
[[1 1 3 4 ][1 2 2 4 ][1 2 3 3 ]]
[[2 2 2 2 ]]
[[1 1 1 2 ]]
[[1 2 2 3 ][2 2 2 2 ]]
[]
[]

 */
class Solution
{
public:
    // // Approach: Brute
    // // Time: O(N^4 Log N)
    // // Space: O(N)
    // vector<vector<int>> fourSum(vector<int> &arr, int target)
    // {
    //     int N = arr.size();
    //     set<vector<int>> uniqResp;

    //     for (int i = 0; i < N - 3; i++)
    //     {
    //         for (int j = i + 1; j < N - 2; j++)
    //         {
    //             for (int k = j + 1; k < N - 1; k++)
    //             {
    //                 for (int l = k + 1; l < N; l++)
    //                 {
    //                     if (arr[i] + arr[j] + arr[k] + arr[l] == target)
    //                     {
    //                         vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
    //                         sort(temp.begin(), temp.end()); // O(4)
    //                         uniqResp.insert(temp);
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    // }

    // // Approach: Replacing the 3 rd loop using hash set which stores element between pointer j and l
    // // Time: O(N^3 Log N)
    // // Space: O(N)
    // vector<vector<int>> fourSum(vector<int> &arr, int target)
    // {
    //     int N = arr.size();
    //     set<vector<int>> uniqResp;

    //     for (int i = 0; i < N - 3; i++)
    //     {
    //         for (int j = i + 1; j < N - 2; j++)
    //         {
    //             set<int> tempHash; // replacement of loop k

    //             for (int l = j + 1; l < N; l++)
    //             {
    //                 int req = target - (arr[i] + arr[j] + arr[l]);
    //                 if (tempHash.find(req) != tempHash.end())
    //                 {
    //                     vector<int> temp = {arr[i], arr[j], req, arr[l]};
    //                     sort(temp.begin(), temp.end()); // O(4)
    //                     uniqResp.insert(temp);
    //                 }
    //                 tempHash.insert(arr[l]);
    //             }
    //         }
    //     }

    //     return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    // }

    // Approach: Optimal: Sorts the given array first to mitigate using sets.
    // So that time and space reduces
    // Time: O(N^3)
    // Space: O(1)
    vector<vector<int>> fourSum(vector<int> &arr, int target)
    {
        int N = arr.size();
        vector<vector<int>> resp;

        sort(arr.begin(), arr.end());

        for (int i = 0; i < N - 3; i++)
        {
            if (i != 0 && arr[i] == arr[i - 1])
            { // needed to skip duplicate entries
                continue;
            }
            for (int j = i + 1; j < N - 2; j++)
            {
                if (j != i + 1 && arr[j] == arr[j - 1])
                { // needed to skip duplicate entries
                    continue;
                }
                int left = j + 1;
                int right = N - 1;

                while (left < right)
                {
                    if (left != j + 1 && arr[left] == arr[left - 1])
                    { // needed to skip duplicate entries
                        left++;
                        continue;
                    }
                    else if (right != N - 1 && arr[right] == arr[right + 1])
                    { // needed to skip duplicate entries
                        right--;
                        continue;
                    }

                    long long sum = (long long)arr[i] + (long long)arr[j] + (long long)arr[left] + (long long)arr[right];

                    if (sum == target)
                    {
                        resp.push_back({arr[i], arr[j], arr[left], arr[right]});
                        left++;
                        right--;
                    }
                    else if (sum < target)
                        left++;

                    else if (sum > target)
                        right--;
                }
            }
        }

        return resp;
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

        vector<vector<int>> res = ob.fourSum(arr, k);

        cout << "[";
        for (auto e : res)
        {
            cout << "[";
            for (auto ee : e)
            {
                cout << ee << " ";
            }
            cout << "]";
        }
        cout << "]";

        cout << endl;
    }
}