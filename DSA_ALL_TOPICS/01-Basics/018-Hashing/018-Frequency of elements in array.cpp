#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>

using namespace std;

/*
https://takeuforward.org/hashing/hashing-maps-time-complexity-collisions-division-rule-of-hashing-strivers-a2z-dsa-course/
https://takeuforward.org/data-structure/count-frequency-of-each-element-in-the-array/

Problem Statement: 
Given an array, we have found the number of occurrences of each element in the array.

Examples:

Example 1:
Input: arr[] = {10,5,10,15,10,5};
Output: 10  3
        5  2
        15  1
Explanation:    10 occurs 3 times in the array
                5 occurs 2 times in the array
                15 occurs 1 time in the array

Example2:
Input: arr[] = {2,2,3,4,4,2};
Output: 2  3
        3  1
        4  2
Explanation: 2 occurs 3 times in the array
             3 occurs 1 time in the array
             4 occurs 2 time in the array
*/
class Solution
{
public:
    // Time: O(N*Log N): if use map
    //       O(N): if use unordered_map
    map<int, int> calFreq(vector<int> &input)
    {
        map<int, int> res;

        for (int i : input)
        {
            res[i]++; // If the element is not present
                      // in the map then insert it with frequency 1,
                      // otherwise increase the existing frequency by 1.
        }

        return res;
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
        map<int, int> resp;
        resp = ob.calFreq(input);

        for (auto x : resp)
        {
            cout << x.first << " " << x.second << endl;
        }

        cout << "----" << endl;
    }

    return 0;
}
