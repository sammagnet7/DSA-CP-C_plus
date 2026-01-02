#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
N-Repeated Element in Size 2N Array

https://leetcode.com/problems/n-repeated-element-in-size-2n-array/description/?envType=daily-question&envId=2026-01-02



Problem Statement:
You are given an integer array nums with the following properties:

nums.length == 2 * n.
nums contains n + 1 unique elements.
Exactly one element of nums is repeated n times.
Return the element that is repeated n times.

Examples:
    Example 1:
    Input: nums = [1,2,3,3]
    Output: 3

    Example 2:
    Input: nums = [2,1,2,5,3,2]
    Output: 2

    Example 3:
    Input: nums = [5,1,5,2,5,3,5,4]
    Output: 5


Constraints:
    2 <= n <= 5000
    nums.length == 2 * n
    0 <= nums[i] <= 104
    nums contains n + 1 unique elements and one of them is repeated exactly n times.


INPUT::::::



OUTPUT::::::


 */
class Solution
{
public:
    // Approach 1: Using Moore's voting algorithm with slight additonal chaeck
    // As oting algo works when element repeats more N/2 times
    // SO here handle Repeating N/2 times only by checking the last element as well
    //  Time: O(N)
    //  Space: O(1)
    //
    // int repeatedNTimes(vector<int>& nums) {

    //     int N = nums.size();
    //     int ans = -1;
    //     int count = 0;

    //     for(int i=0; i<N; i++){
    //         if(count == 0){
    //             ans = nums[i];
    //             count++;
    //         }
    //         else if(ans == nums[i]){
    //             count++;
    //         }
    //         else{
    //             count--;
    //         }
    //     }

    //     count =0;
    //     for(int i=0; i<N; i++){
    //         if(nums[i]==ans){
    //             count++;
    //         }
    //     }

    //     if(count==(N/2)){
    //         return ans;
    //     }
    //     else{
    //         return nums[N-1];
    //     }
    // }

    // int repeatedNTimes(vector<int>& nums) {
    //     // Check neighbors (Gap 1) and neighbors' neighbors (Gap 2)
    //     // This catches 99% of cases including [x, y, x]
    //     for (int i = 0; i < nums.size() - 2; i++) {
    //         if (nums[i] == nums[i+1] || nums[i] == nums[i+2]) {
    //             return nums[i];
    //         }
    //     }

    //     // If the loop finishes, the answer is in one of the two "blind spots":
    //     // 1. The very last pair [..., x, x]
    //     // 2. The N=2 edge case [x, y, z, x]
    //     // In both cases, the last element is the answer.
    //     return nums[nums.size() - 1];
    // }

    /*
        Approach 2: Probability / Gap Check (O(1) Space)

        Since the target element occupies 50% of the array (N out of 2N), it is statistically extremely dense. It is guaranteed that the repeated element will be found either next to itself (nums[i] == nums[i+1]) or separated by just one or two numbers.

        We can simply check if nums[i] equals nums[i+1] or nums[i+2] or nums[i+3].

        Time: O(N)
        Space: O(1)
    */
    int repeatedNTimes(vector<int> &nums)
    {
        // Iterate and check neighbors at distance 1, 2, and 3
        for (int i = 0; i < nums.size(); ++i)
        {
            // Check neighbor (Distance 1)
            if (i + 1 < nums.size() && nums[i] == nums[i + 1])
                return nums[i];

            // Check neighbor's neighbor (Distance 2)
            if (i + 2 < nums.size() && nums[i] == nums[i + 2])
                return nums[i];

            // Check edge case for N=2 [x, a, b, x] (Distance 3)
            if (i + 3 < nums.size() && nums[i] == nums[i + 3])
                return nums[i];
        }
        return -1;
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

        cout << ob.repeatedNTimes(arr);

        cout << endl;
    }
}