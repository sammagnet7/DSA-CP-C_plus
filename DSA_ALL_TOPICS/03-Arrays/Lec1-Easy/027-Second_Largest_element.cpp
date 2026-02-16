#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/find-second-smallest-and-second-largest-element-in-an-array/
https://www.geeksforgeeks.org/problems/second-largest3735/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=second-largest
https://www.naukri.com/code360/problems/ninja-and-the-second-order-elements_6581960?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem Statement: Given an array, find the second smallest and second largest element in the array. Print ‘-1’ in the event that either of them doesn’t exist.

Example 1:
Input:
[1,2,4,7,7,5]
Output:
Second Smallest : 2
Second Largest : 5
Explanation:
The elements are as follows 1,2,3,5,7,7 and hence second largest of these is 5 and second smallest is 2

Example 2:
Input:
[1]
Output:
Second Smallest : -1
Second Largest : -1
Explanation:
Since there is only one element in the array, it is the largest and smallest element present in the array. There is no second largest or second smallest element present.


Approach:
We would require four variables: small,second_small, large, and second_large. Variable small and second_small are initialized to INT_MAX while large and second_large are initialized to INT_MIN.

Second Smallest Algo:
If the current element is smaller than ‘small’, then we update second_small and small variables
Else if the current element is smaller than ‘second_small’ then we update the variable ‘second_small’
Once we traverse the entire array, we would find the second smallest element in the variable second_small.
Here’s a quick demonstration of the same.

Second Largest Algo:
If the current element is larger than ‘large’ then update second_large and large variables
Else if the current element is larger than ‘second_large’ then we update the variable second_large.
Once we traverse the entire array, we would find the second largest element in the variable second_large.
Here’s a quick demonstration of the same.

INPUT::::::
5
4 1 3 9 7
10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10
38 31 20 14 34
1

OUTPUT::::::

2nd Largest: 7; 2nd Smallest: 3
2nd Largest: 9; 2nd Smallest: 2
2nd Largest: 9; 2nd Smallest: 2
2nd Largest: 34; 2nd Smallest: 20
2nd Largest: -1; 2nd Smallest: -1
 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    vector<int> getSecondOrderElements(vector<int> &arr)
    {
        vector<int> res(2, 0);
        res[0] = INT_MIN;
        int max = INT_MIN;

        res[1] = INT_MAX;
        int min = INT_MAX;

        for (int e : arr)
        {

            // Find Max and push prev max to 2nd Largest
            if (e > max)
            {
                res[0] = max;
                max = e;
            }
            // Consider elements which are not greater than Max but can be 2nd Largest
            if (e > res[0] && e != max)
                res[0] = e;

            // Find Min and push prev Min to 2nd Minimum
            if (e < min)
            {
                res[1] = min;
                min = e;
            }
            // Consider elements which are not lesser than Min but can be 2nd Minimum
            if (e < res[1] && e != min)
                res[1] = e;
        }

        if (res[0] == INT_MIN)
            res[0] = -1;
        if (res[1] == INT_MAX)
            res[1] = -1;
        return res;
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

        vector<int> res = ob.getSecondOrderElements(arr);
        cout << "2nd Largest: " << res[0] << "; 2nd Smallest: " << res[1];

        cout << endl;
    }
}