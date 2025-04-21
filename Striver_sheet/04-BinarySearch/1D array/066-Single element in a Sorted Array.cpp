#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Search Single Element in a sorted array

https://takeuforward.org/data-structure/search-single-element-in-a-sorted-array/
https://leetcode.com/problems/single-element-in-a-sorted-array/

Problem statement:
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
Return the single element that appears only once.

Examples:

Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10

INPUT::::::
6
2 3 4 1
1 2 3
35 43 45 1 2 9 12 13 19 20 26 28 29 32
2
6 7 10 1 4
1 1 2

OUTPUT::::::
2
10
1
1
9
2

 */
class Solution
{
public:
    // Optimal approach
    // Time: O(Log N)
    // Space: O(1)
    int singleNonDuplicate(vector<int> &arr)
    {
        int N = arr.size();

        // Pre handle edge cases
        if (N == 1)
            return arr[0];
            
        // if (arr[0] != arr[1])
        //     return arr[0];
        // if (arr[N - 1] != arr[N - 2])
        //     return arr[N - 1];
        // int l=1, r=N-2;

        int l = 0, r = N-1;

        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            if(mid==0 && arr[mid]!= arr[mid+1])  // Handle edge
                return arr[mid];
            else if(mid==(N-1) && arr[mid]!= arr[mid-1])   // handle edge
                return arr[mid];
            else if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1])  // Bingo
            { 
                return arr[mid];
            }
            else if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) || (mid % 2 != 0 && arr[mid] == arr[mid - 1]))
            { // We are at the left. Go find in right
                l = mid + 1;
            }
            else if ((mid % 2 == 0 && arr[mid] == arr[mid - 1]) || (mid % 2 != 0 && arr[mid] == arr[mid + 1]))
            { // We are at the right. Go find in left
                r = mid - 1;
            }
        }
        return -1;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        // int target;
        // cin >> target;
        // cin.ignore();

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

        cout << ob.singleNonDuplicate(arr);
        cout << endl;
    }
    return 0;
}