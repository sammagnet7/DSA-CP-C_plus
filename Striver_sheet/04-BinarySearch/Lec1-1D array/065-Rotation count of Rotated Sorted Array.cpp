#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Find out how many times the array has been rotated

https://takeuforward.org/arrays/find-out-how-many-times-the-array-has-been-rotated/
https://www.naukri.com/code360/problems/rotation_7449070?leftPanelTabValue=PROBLEM

Problem statement
You are given an array 'arr' having 'n' distinct integers sorted in ascending order. The array is right rotated 'r' times
Find the minimum value of 'r'.
Right rotating an array means shifting the element at 'ith' index to (‘i+1') mod 'n' index, for all 'i' from 0 to ‘n-1'.

Examples:

Sample Input 1:
4
2 3 4 1
Sample Output 1:
3   
Explanation of sample output 1:
If we right rotate the array {1, 2, 3, 4} by '3' times then we will get {2, 3, 4, 1}. Thus 'r' = 3.


Sample Input 2:
3
1 2 3
Sample Output 2:
0
Explanation of sample output 2:
If we right rotate the array {1, 2, 3} by '0' time then we will get {1, 2, 3}. Thus 'r' = 0.

INPUT::::::
5
2 3 4 1
1 2 3
35 43 45 1 2 9 12 13 19 20 26 28 29 32 
2
6 7 10 1 4 

OUTPUT::::::
3
0
3
0
3

 */
class Solution
{
public:
    // Alternate minimal approach would be to find the minimum element in this array.
    // That gives the starting element of rotated array


    // Optimal approach: Check which indexes are having elements lesser than start element of the array.
    // That is breaking the sorted order. And take the left most index from those.
    // Time: O(logN)
    // Space: O(1)
    int findKRotation(vector<int> &arr)
    {
        // Write your code here.

        int N = arr.size();

        int l = 0, r = N - 1;
        int startI = arr[0];
        int k = 0;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if (startI <= arr[mid])
            {
                l = mid + 1;
            }
            else if (startI > arr[mid])
            {
                k = mid;
                r = mid - 1;
            }
        }
        return k;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        //int target;
        //cin >> target;
        //cin.ignore();

        string input;
        getline(cin, input);

        vector<int> arr;
        stringstream ss(input);
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.findKRotation(arr);
        cout << endl;
    }
    return 0;
}