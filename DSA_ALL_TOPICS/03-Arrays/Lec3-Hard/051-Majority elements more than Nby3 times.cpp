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
    vector<int> majorityElement_MAP(vector<int> arr)
    {
        int n = arr.size();
        vector<int> res;

        unordered_map<int, int> mpp;

        // least occurrence of the majority element:
        int threshold = n / 3;

        for (int i = 0; i < n; i++)
        {
            if (res.size() > 0 && res[0] == arr[i])
                continue; // Skips if already selected as majority element

            mpp[arr[i]]++;

            // checking if arr[i] is the majority element:
            if (mpp[arr[i]] > threshold)
            {
                res.push_back(arr[i]);
            }
            if (res.size() == 2)
                break;
        }

        return res;
    }

    /*
        majorityElement
        ----------------
        Problem:
            - Find all elements in the array that appear more than ⌊n/3⌋ times.
            - Constraint: There can be at most 2 such elements (pigeonhole principle).

        Approach: Extended Moore’s Voting Algorithm
        --------------------------------------------
        Intuition:
            - For n/2 majority element problem, Moore’s Voting Algorithm maintains one candidate + counter.
            - For n/3 majority element problem, at most 2 numbers can qualify, so we track two candidates.
            - Cancellation process:
                * If current number matches one of the candidates, increment its counter.
                * If one candidate's counter is 0 and the current number is not the other candidate,
                  assign it as new candidate.
                * If it matches none and both counters > 0, decrement both counters.
              → This ensures that frequent numbers survive after the full pass, while less frequent ones cancel out.

        Verification:
            - After first pass, el1 and el2 are *candidates* only.
            - Must verify by counting actual occurrences in a second pass.

        Complexity:
            - Time: O(n)  (two passes over nums)
            - Space: O(1) (only counters and candidates)

    */
    vector<int> majorityElement(vector<int> &nums)
    {

        int n = nums.size();
        int threshold = n / 3; // frequency needed to qualify

        // Two potential candidates and their counts
        int count1 = 0, count2 = 0;
        int el1 = INT_MIN, el2 = INT_MIN;

        // --- First Pass: Find potential candidates ---
        for (int i = 0; i < n; i++)
        {
            int cur = nums[i];

            if (count1 == 0 && el2 != cur)
            {
                // Candidate 1 slot is free, and current is not candidate 2
                el1 = cur;
                count1 = 1;
            }
            else if (count2 == 0 && el1 != cur)
            {
                // Candidate 2 slot is free, and current is not candidate 1
                el2 = cur;
                count2 = 1;
            }
            else if (el1 == cur)
            {
                // Current matches candidate 1
                count1++;
            }
            else if (el2 == cur)
            {
                // Current matches candidate 2
                count2++;
            }
            else
            {
                // Current matches neither → cancel one from both
                count1--;
                count2--;
            }
        }

        // --- Second Pass: Verify candidates ---
        count1 = 0;
        count2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == el1)
                count1++;
            if (nums[i] == el2)
                count2++;
        }

        vector<int> ans;
        if (count1 > threshold)
            ans.push_back(el1);
        if (count2 > threshold)
            ans.push_back(el2);

        return ans;
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