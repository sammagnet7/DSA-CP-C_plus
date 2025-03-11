#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/arrays/find-the-missing-number-in-an-array/
https://leetcode.com/problems/missing-number/
https://www.naukri.com/code360/problems/missing-number_6680467?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse&leftPanelTabValue=SUBMISSION


Problem Statement:
Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Examples:

Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation:
n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation:
n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation:
n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.


Constraints:
n == nums.length
1 <= n <= 104
0 <= nums[i] <= n
All the numbers of nums are unique.

Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?

INPUT::::::
4
3 0 1
0 1
9 6 4 2 3 5 7 0 1
1

OUTPUT::::::

2
2
8
0


 */
class Solution
{
public:
    // Time: O(N log N)
    // Space: O(1)
    // Approach: Using Sorting
    // int missingNumber(vector<int>& nums) {
    //     sort(nums.begin(), nums.end());
    //     if(nums[0]!=0) return 0; // edge case
    //     for(int i=0; i<nums.size()-1; i++){
    //         if(nums[i+1]-nums[i] != 1) return nums[i]+1;
    //     }
    //     return nums[nums.size()-1]+1; // edge case
    // }

    // Time: O(N)
    // Space: O(N)
    // Approach: Using extra array space
    // int missingNumber(vector<int>& nums) {
    //     int len=nums.size();
    //     vector<int> range(len+1, -1);

    //     for(int e:nums){
    //         range[e]=1;
    //     }
    //     for(int i=0; i<(len+1); i++){
    //         if(range[i]==-1) return i;
    //     }
    //     return 0;
    // }

    // Time: O(N)
    // Space: O(1)
    // Approach: Using formula
    // int missingNumber(vector<int>& nums) {
    //     int len=nums.size();

    //     int expectedSum = (len * (len+1))/2;

    //     int actualSum=0;
    //     for(int e:nums){
    //         actualSum+=e;
    //     }

    //     return expectedSum-actualSum;
    // }

    // Time: O(N)
    // Space: O(1)
    // Approach: Using XOR
    int missingNumber(vector<int> &nums)
    {
        int len = nums.size();
        int xor1 = 0, xor2 = len;
        for (int i = 0; i < len; i++)
        {
            xor1 ^= nums[i];
            xor2 ^= i;
        }

        return (xor1 ^ xor2);
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

        cout << ob.missingNumber(arr);
        cout << endl;
    }
}