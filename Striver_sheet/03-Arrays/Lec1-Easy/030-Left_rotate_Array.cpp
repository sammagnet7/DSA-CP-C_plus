#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/left-rotate-the-array-by-one/
https://www.naukri.com/code360/problems/left-rotate-an-array-by-one_5026278?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse
https://leetcode.com/problems/rotate-array/description/

Problem Statement: Given an array of N integers, left rotate the array by one place.

Example 1:
Input:
 N = 5, array[] = {1,2,3,4,5}
Output:
 2,3,4,5,1
Explanation:
Since all the elements in array will be shifted  toward left by one so ‘2’ will now become the  first index and and ‘1’ which was present at
first index will be shifted at last.

Example 2:
Input:
 N = 1, array[] = {3}
Output:
 3
Explanation:
 Here only element is present and so
the element at first index will be shifted to
last index which is also by the way the first index.

INPUT::::::
5
1 1 2 2 2 3 3
1 1 1 2 2 3 3 3 3 4 4
1 1 2
0 0 1 1 1 2 2 3 3 4
1 2 2 2 3

OUTPUT::::::

1 2 3
1 2 3 4
1 2
0 1 2 3 4
1 2 3

 */
class Solution
{
public:
    // Time: O(N)
    // Space: O(1)
    void rotate(vector<int> &nums, int k)
    {
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

        ob.rotate(arr, 1);
        cout << "Rotated by 1 position: ";
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;

        ob.rotate(arr, 2);
        cout << "Rotated by 2 position: ";
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;

        ob.rotate(arr, 3);
        cout << "Rotated by 3 position: ";
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "----------------" << endl;
    }
}