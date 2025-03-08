#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <climits>

using namespace std;

/*
https://leetcode.com/problems/frequency-of-the-most-frequent-element/description/
https://leetcode.com/problems/frequency-of-the-most-frequent-element/solutions/4173577/frequency-of-the-most-frequent-element

Problem Statement:
Maximum possible frequency of an element after performing at most k operations

The frequency of an element is the number of times it occurs in an array.
You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and **increment** the element at that index by 1.
Return the maximum possible frequency of an element after performing at most k operations.

Example 1:
Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.

Example 2:
Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.

Example 3:
Input: nums = [3,9,6], k = 2
Output: 1

Constraints:
1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 105
*/
class Solution
{
public:
    // Good approach: Sliding window
    int maxFrequency(vector<int>& nums, int k) {

    }

    // Good approach: Binary search
    int maxFrequency(vector<int>& nums, int k) {

    }

    // Brute force approach Time: O(N^2)
    int maxFrequency(vector<int>& nums, int k) {
        map<int,int> freq; // taking map as, map is sorted by key and here key is the numbers

        for(int i:nums){ // O(N Log N)
           freq[i]++;
        }
        
        for(auto itr=freq.rbegin(); itr!=freq.rend(); itr++){ // Reverse iterator
            int temp=k;
            auto left_itr=itr;   // Reverse iterator
            int left_freq=0;
            left_itr++;

            while(temp>0 && left_itr != freq.rend()){ // O((Unique elements)^2) ~ O(N^2)
                if(left_freq==0){   // that means left_itr has moved to new left element
                    left_freq=left_itr->second;
                }
                if((itr->first - left_itr->first)<=temp){
                    (itr->second)++;
                }
                temp -= (itr->first- left_itr->first); 

                left_freq--;
                if(left_freq==0){
                    left_itr++;
                }               
                                
            }
        }
        
        int maxi=0;
        int maxFreq=0;

        for(auto i:freq){
            if(i.second>maxFreq){
                maxFreq=i.second;
                maxi=i.first;
            }
        }

        return maxFreq;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore();

    cout << endl;
    while (t--)
    {
        int k;
        cin >> k;
        cin.ignore();

        string inStr;
        getline(cin, inStr);
        stringstream ss(inStr);

        vector<int> input;
        int inNum;
        while (ss >> inNum)
        {
            input.push_back(inNum);
        }

        Solution ob;
        cout << ob.maxFrequency(input, k) << endl;

        cout << "----" << endl;
    }

    return 0;
}
