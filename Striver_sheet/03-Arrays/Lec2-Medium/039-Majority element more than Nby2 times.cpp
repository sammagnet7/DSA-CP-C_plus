#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find the Majority Element that occurs more than N/2 times

https://takeuforward.org/data-structure/find-the-majority-element-that-occurs-more-than-n-2-times/
https://leetcode.com/problems/majority-element/description/
https://www.naukri.com/code360/problems/majority-element_6783241?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem Statement: Given an array of N integers, write a program to return an element that occurs more than N/2 times in the given array. You may consider that such an element always exists in the array.

Examples:

Example 1:
Input Format: N = 3, nums[] = {3,2,3}
Result: 3
Explanation: When we just count the occurrences of each number and compare with half of the size of the array, you will get 3 for the above solution.

Example 2:
Input Format:N = 7, nums[] = {2,2,1,1,1,2,2}
Result: 2
Explanation: After counting the number of times each element appears and comparing it with half of array size, we get 2 as result.

Example 3:
Input Format:N = 10, nums[] = {4,4,2,4,3,4,4,3,2,4}
Result: 4


INPUT::::::
5
3 2 3
2 2 1 1 1 2 2
4 4 2 4 3 4 4 3 2 4
2 2 1 3 1 1 3 1 1
-53 75 56 56 56


OUTPUT::::::

3
2
4
1
56

 */
class Solution
{
public:
    /**
     * Majority Element — Frequency Map Approach
     * -----------------------------------------
     * Problem:
     *   - Find the element that appears more than ⌊n/2⌋ times in the array.
     *   - If no such element exists, return -1.
     *
     * Approach:
     *   - Use a hash map (unordered_map) or map to count the frequency of each element.
     *   - Traverse the array, increment count for each element.
     *   - After counting, check which element (if any) has frequency > n/2.
     *
     * Time Complexity:
     *   - O(N) average with unordered_map (hash table).
     *   - O(N log N) if using ordered map (balanced BST).
     *
     * Space Complexity:
     *   - O(N) for storing frequencies.
     *
     * Notes:
     *   - Straightforward approach, easy to implement.
     *   - Less space-efficient than Boyer–Moore (which uses O(1)).
     */
    int majorityElement_Map(vector<int> &arr)
    {
        int n = arr.size();
        unordered_map<int, int> freq; // value -> count

        // Count frequencies
        for (int x : arr)
        {
            freq[x]++;
        }

        // Find element with frequency > n/2
        for (auto &p : freq)
        {
            if (p.second > n / 2)
                return p.first;
        }

        return -1; // no majority element
    }

    /**
     * Majority Element (Boyer–Moore Voting Algorithm)
     * -----------------------------------------------
     * Problem:
     *   - Find the element that appears more than ⌊n/2⌋ times in the array.
     *   - If no such element exists, return -1.
     *
     * Approach:
     *   - Use the Boyer–Moore Majority Vote Algorithm.
     *   - Maintain a candidate element `elem` and a counter `count`.
     *   - Iterate through the array:
     *       * If count == 0 → take current element as new candidate.
     *       * If current element == candidate → increment count.
     *       * If current element != candidate → decrement count.
     *   - At the end, candidate may be the majority element.
     *   - Do a final pass to confirm if candidate is indeed majority.
     *
     * Time Complexity:
     *   - O(N) [single pass to find candidate + optional second pass to verify].
     *
     * Space Complexity:
     *   - O(1) [constant space for counters].
     *
     * Notes:
     *   - If the problem guarantees a majority element exists (like LeetCode 169),
     *     the second verification loop can be skipped.
     *   - This algorithm works because if we pair each occurrence of the candidate
     *     with a different element, majority element will remain unpaired.
     */
    int majorityElement(vector<int> &arr)
    {
        int elem = 0;  // candidate for majority
        int count = 0; // vote counter

        // Phase 1: Find potential candidate
        for (int i = 0; i < arr.size(); i++)
        {
            if (count == 0)
            {
                // If no candidate, take current element as new candidate
                elem = arr[i];
                count = 1;
            }
            else if (arr[i] == elem)
            {
                // If same as candidate, increment vote
                count++;
            }
            else
            {
                // Different element → cancel out one vote
                count--;
            }
        }

        // Phase 2: Verify candidate (only needed if majority not guaranteed)
        count = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == elem)
                count++;
        }

        // Check if candidate occurs more than n/2 times
        if (count > arr.size() / 2)
            return elem;

        return -1; // no majority element
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

        cout << ob.majorityElement(arr);

        cout << endl;
    }
}