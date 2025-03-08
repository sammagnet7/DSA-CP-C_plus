#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <climits>

using namespace std;

/*
https://takeuforward.org/arrays/find-the-highest-lowest-frequency-element/

Problem Statement:
Given an array of size N. Find the highest and lowest frequency element.

Examples:

Example 1:
Input: array[] = {10,5,10,15,10,5};
Output: 10 15
Explanation: The frequency of 10 is 3, i.e. the highest and the frequency of 15 is 1 i.e. the lowest.

Example 2:
Input: array[] = {2,2,3,4,4,2};
Output: 2 3
Explanation: The frequency of 2 is 3, i.e. the highest and the frequency of 3 is 1 i.e. the lowest.
*/
class Solution
{
public:
    // Time: O(N): if use unordered_map
    vector<int> calFreq(vector<int> &input)
    {
        unordered_map<int, int> freqCumulator;

        for (int i : input)
        {                       // O(N)
            freqCumulator[i]++; // If the element is not present
                                // in the map then insert it with frequency 1,
                                // otherwise increase the existing frequency by 1.
        }

        int maxFreqElem = -1;
        int maxFreq = INT_MIN;
        int minFreqElem = -1;
        int minFreq = INT_MAX;

        for (auto x : freqCumulator)
        { // O(N)
            if (x.second > maxFreq)
            {
                maxFreq = x.second;
                maxFreqElem = x.first;
            }
            if (x.second < minFreq)
            {
                minFreq = x.second;
                minFreqElem = x.first;
            }
        }

        return {minFreqElem, maxFreqElem};
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
        vector<int> resp;
        resp = ob.calFreq(input);

        cout << "Min:" << resp[0] << "; Max: " << resp[1] << endl;

        cout << "----" << endl;
    }

    return 0;
}
