#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find the elements that appears more than N/3 times in the array

https://takeuforward.org/data-structure/majority-elementsn-3-times-find-the-elements-that-appears-more-than-n-3-times-in-the-array/
https://leetcode.com/problems/majority-element-ii/description/
https://www.naukri.com/code360/problems/majority-element_6915220?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem Statement: Given an array of N integers. Find the elements that appear more than N/3 times in the array. If no such element exists, return an empty vector.

Note: As greater than N/3, so there can be a maximum of 2 majority elements.

Examples:

Example 1:
Input array[] = {1,2,2,3,2}
Result
: 2
Explanation:
 Here we can see that the Count(1) = 1, Count(2) = 3 and Count(3) = 1.Therefore, the count of 2 is greater than N/3 times. Hence, 2 is the answer.

Example 2:
Input array[] = {11,33,33,11,33,11}
Result:
 11 33
Explanation:
 Here we can see that the Count(11) = 3 and Count(33) = 3. Therefore, the count of both 11 and 33 is greater than N/3 times. Hence, 11 and 33 is the answer.


INPUT::::::
2
1 2 2 3 2
11 33 33 11 33 11


OUTPUT::::::

2
33 11

 */
class Solution
{
public:
    // Better Approach : Using Frequency map
    // Time: O(N Log N)
    // Space: O(N)
    // vector<int> majorityElement(vector<int> arr)
    // {
    //     int n = arr.size();
    //     vector<int> res;

    //     unordered_map<int, int> mpp;

    //     // least occurrence of the majority element:
    //     int threshold = n / 3;

    //     for (int i = 0; i < n; i++)
    //     {
    //         if (res.size() > 0 && res[0] == arr[i])
    //             continue; // Skips if already selected as majority element

    //         mpp[arr[i]]++;

    //         // checking if arr[i] is the majority element:
    //         if (mpp[arr[i]] > threshold)
    //         {
    //             res.push_back(arr[i]);
    //         }
    //         if (res.size() == 2)
    //             break;
    //     }

    //     return res;
    // }

    // Approach: Moore’s Voting Algorithm : Using Counter
    // Time: O(N)
    // Space: O(1)
    vector<int> majorityElement(vector<int> &arr)
    {
        vector<int> res;
        int cnt1 = 0, cnt2 = 0;
        int el1 = INT_MIN, el2 = INT_MIN;

        int threshold = arr.size() / 3;

        for (int i = 0; i < arr.size(); i++)
        {
            if (el1 == arr[i])
                cnt1++;
            else if (el2 == arr[i])
                cnt2++;
            else if (cnt1 == 0)
            {
                el1 = arr[i];
                cnt1++;
            }
            else if (cnt2 == 0)
            {
                el2 = arr[i];
                cnt2++;
            }
            else
            { // matches none
                cnt1--;
                cnt2--;
            }
            if (cnt1 > threshold && (res.size() == 0 || res[0] != el1))
            {
                res.push_back(el1);
            }

            else if (cnt2 > threshold && (res.size() == 0 || res[0] != el2))
            {
                res.push_back(el2);
            }

            // If already 2 majors found, then return
            if (res.size() == 2)
                return res;
        }

        // Now have to check whole array with the el1 and el2 for possible answers
        vector<int> res1;
        cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == el1)
                cnt1++;
            else if (arr[i] == el2)
                cnt2++;
        }
        if (cnt1 > threshold)
            res1.push_back(el1);
        if (cnt2 > threshold)
            res1.push_back(el2);

        return res1;
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

        vector<int> res = ob.majorityElement(arr);

        if (res.size() == 0)
            cout << "NONE";
        else
        {
            for (int e : res)
            {
                cout << e << " ";
            }
        }

        cout << endl;
    }
}