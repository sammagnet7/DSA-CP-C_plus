#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/remove-duplicates-in-place-from-sorted-array/
https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
https://www.naukri.com/code360/problems/remove-duplicates-from-sorted-array_1102307?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Problem Statement: Given an integer array sorted in non-decreasing order, remove the duplicates in place such that each unique element appears only once. The relative order of the elements should be kept the same.
If there are k elements after removing the duplicates, then the first k elements of the array should hold the final result. It does not matter what you leave beyond the first k elements.
Note: Return k after placing the final result in the first k slots of the array.ote: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.
Do not allocate extra space for another array. You need to do this by modifying the given input array in place with O(1) extra memory.

Example 1:
Input:
 arr[1,1,2,2,2,3,3]
Output:
 arr[1,2,3,_,_,_,_]
Explanation:
 Total number of unique elements are 3, i.e[1,2,3] and Therefore return 3 after assigning [1,2,3] in the beginning of the array.

Example 2:
Input:
 arr[1,1,1,2,2,3,3,3,3,4,4]
Output:
 arr[1,2,3,4,_,_,_,_,_,_,_]
Explanation:
 Total number of unique elements are 4, i.e[1,2,3,4] and Therefore return 4 after assigning [1,2,3,4] in the beginning of the array.


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
    int removeDuplicates(vector<int> &nums)
    {
        int valididx = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            // On finding each new element increment the counter index and save the new element with the counter index
            if (nums[i - 1] != nums[i])
            {
                valididx++;
                nums[valididx] = nums[i];
            }
        }

        return valididx + 1;
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

        int n = ob.removeDuplicates(arr);
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
}