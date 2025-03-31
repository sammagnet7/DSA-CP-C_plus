#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
3 Sum : Find triplets that add up to a zero

https://takeuforward.org/data-structure/3-sum-find-triplets-that-add-up-to-a-zero/
https://leetcode.com/problems/3sum/description/
https://www.naukri.com/code360/problems/three-sum_6922132?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Note:Solution set must not contain duplicate triplets.

Examples:

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0


INPUT::::::
3
-1 0 1 2 -1 -4
0 1 1
0 0 0

OUTPUT::::::

[[-1 -1 2 ][-1 0 1 ]]
[]
[[0 0 0 ]]

 */
class Solution
{
public:
    // // Approach: Brute
    // // Three pointer for each of the 3 elements
    // // Time: O(N^3 Log N)
    // // Space: O(N)
    // vector<vector<int>> threeSum(vector<int>& arr) {
    //     int N= arr.size();
    //     set<vector<int>> uniqResp;

    //     for(int i=0; i<N-2; i++){
    //         for(int j=i+1; j<N-1; j++){
    //             for(int k=j+1; k<N; k++){
    //                 if(arr[i]+arr[j]+arr[k] == 0){
    //                     vector<int> temp={arr[i],arr[j],arr[k]};
    //                     sort(temp.begin(), temp.end()); // O(3) ~ O(1)
    //                     uniqResp.insert(temp);
    //                 }
    //             }
    //         }
    //     }
    //     return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    // }

    // // Approach: Better
    // // Instead of 3 pointers (i,j,k) use 2 pointers (i,k). Use a hashset for achieving the functionality of the 3rd pointer
    // // Time: O(N^2 Log N)
    // // Space: O(N)
    // vector<vector<int>> threeSum(vector<int>& arr) {
    //     int N= arr.size();
    //     set<vector<int>> uniqResp;

    //     for(int i=0; i<N-1; i++){
    //         set<int> hash; // hashset holding elements between i and k
    //         for(int k=i+1;  k<N; k++){
    //             int req = 0-(arr[i]+arr[k]);
    //             if(hash.find(req) != hash.end()){
    //                 vector<int> temp={arr[i], arr[k], req};
    //                 sort(temp.begin(), temp.end());
    //                 uniqResp.insert(temp);
    //             }
    //             hash.insert(arr[k]);
    //         }
    //     }
    //     return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    // }

    // Approach: Optimal
    // Here we sort the array then use 3 pointers, where i traverse from min to max elements
    // and pointers j and k traversing from 2 opposit sides cover the rest of the array once
    // As array is already sorted so removing duplicates done on the fly omiting the need of uniqSet
    // Time: O(N LogN + N^2)
    // Space: O(1)
    vector<vector<int>> threeSum(vector<int> &arr)
    {
        vector<vector<int>> resp;
        int N = arr.size();

        sort(arr.begin(), arr.end());

        for (int i = 0; i < N - 2; i++)
        {

            if (i != 0 && arr[i] == arr[i - 1])
                continue; // Ignoring the duplicates

            int j = i + 1, k = N - 1; // initialising

            while (j < k)
            {

                // Ignoring the duplicates
                if (j != i + 1 && arr[j - 1] == arr[j])
                {
                    j++;
                    continue;
                }
                else if (k != N - 1 && arr[k] == arr[k + 1])
                {
                    k--;
                    continue;
                }

                if (arr[i] + arr[j] + arr[k] == 0)
                { // bingo
                    resp.push_back({arr[i], arr[j], arr[k]});
                    j++;
                    k--;
                }
                else if (arr[i] + arr[j] + arr[k] > 0)
                { // move right pointer to left
                    k--;
                }
                else if (arr[i] + arr[j] + arr[k] < 0)
                { // move left pointer to right
                    j++;
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

        vector<vector<int>> res = ob.threeSum(arr);

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