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
    // Another approach : Using Frequency map
    // Time: O(N Log N)
    // SPace: O(N)
    // int majorityElement(vector<int> &arr)
    // {
    // }

    // Approach: Using Counter
    // Time: O(N)
    // Space: O(1)
    int majorityElement(vector<int> &arr)
    {
        int elem = 0;
        int count = 0;

        for (int i = 0; i < arr.size(); i++)
        {
            if (count == 0)
            {
                elem = arr[i];
                count++;
            }
            else if (arr[i] == elem)
            {
                count++;
            }
            else if (arr[i] != elem)
            {
                count--;
            }
        }

        // checking if the stored element is the majority element
        // This check is needed if it not guaranteed that such an element always exists in the array
        count = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == elem)
                count++;
        }

        if (count > (arr.size() / 2))
            return elem;
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

        cout << ob.majorityElement(arr);

        cout << endl;
    }
}