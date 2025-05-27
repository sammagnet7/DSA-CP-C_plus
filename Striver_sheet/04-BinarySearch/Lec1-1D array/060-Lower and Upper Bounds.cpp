#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Implement Lower Bound

https://takeuforward.org/arrays/implement-lower-bound-bs-2/
https://www.naukri.com/code360/problems/lower-bound_8165382?utm_source=youtube&utm_medium=affiliate&utm_campaign=codestudio_Striver_BinarySeries&leftPanelTabValue=PROBLEM

https://takeuforward.org/arrays/implement-upper-bound/
https://www.naukri.com/code360/problems/implement-upper-bound_8165383?utm_source=youtube&utm_medium=affiliate&utm_campaign=codestudio_Striver_BinarySeries&leftPanelTabValue=PROBLEM

Problem statement:
Given a sorted array of N integers and an integer target, write a program to find the lower bound and upper bound of target.

Note:
What is Lower Bound?
The lower bound is the smallest index, ind, where arr[ind] >= target. But if any such index is not found, the lower bound algorithm returns n i.e. size of the given array.

What is Upper Bound?
The upper bound is the smallest index, ind, where arr[ind] > target.
But if any such index is not found, the upper bound algorithm returns n i.e. size of the given array.

The main difference between the lower and upper bound is in the condition. For the lower bound the condition was arr[ind] >= target and here, in the case of the upper bound, it is arr[ind] > target.


Examples:

Example 1:
Input Format: N = 4, arr[] = {1,2,2,3}, target = 2
Result:
    Lower bound 1
        Explanation: Index 1 is the smallest index such that arr[1] >= target.
    Upper bound 3
        Explanation: Index 3 is the smallest index such that arr[3] > target.

Example 2:
Input Format: N = 5, arr[] = {3,5,8,15,19}, target = 9
Result:
    Lower bound 3
        Explanation: Index 3 is the smallest index such that arr[3] >= target.
    Upper bound 4
        Explanation: Index 4 is the smallest index such that arr[4] > target.


INPUT::::::
6
2
1 2 2 3
9
3 5 8 9 15 19
4
1 2 2 3
7
1 4 7 8 10
10
1 2 5 6 10
5
1 5 5 7 7 9 10

OUTPUT::::::
Lower bound: 1 Upper bound: 3
Lower bound: 3 Upper bound: 4
Lower bound: 4 Upper bound: 4
Lower bound: 2 Upper bound: 3
Lower bound: 4 Upper bound: 5
Lower bound: 1 Upper bound: 3

 */
class Solution
{
public:
    // Approach: Optimal:: Binary search
    // Always focus on the condition in which the index can be a possible answer. here it will be (arr[i]>=target)
    // Time: O(Log N)
    // Space: P(1)
    int lowerBound(vector<int> arr, int N, int target)
    {

        int l = 0, r = N - 1;
        int ans = N; // in case target is greater than any elements in the array

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if(arr[mid] == target){
                ans = mid; // smallest i where arr[i]>=target
                r = mid - 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
            else if (target < arr[mid])
            {
                ans = mid; // smallest i where arr[i]>=target
                r = mid - 1;
            }
        }

        return ans;
    }

    // Approach: Optimal:: Binary search
    // Always focus on the condition in which the index can be a possible answer. here it will be (arr[i]>target)
    // Time: O(Log N)
    // Space: P(1)
    int upperBound(vector<int> &arr, int N, int target)
    {

        int l = 0, r = N;

        int ans = N; // in case target is greater than any elements in the array

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            if(arr[mid] == target){
                l = mid + 1;
            }
            else if (arr[mid] < target)
            {
                l = mid + 1;
            }
            else if (target < arr[mid])
            {
                ans = mid; // smallest i where arr[i]>target
                r = mid - 1;
            }
        }

        return ans;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int target;
        cin >> target;
        cin.ignore();

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

        cout << "Lower bound: "<< ob.lowerBound(arr, arr.size(), target) <<" Upper bound: "<<ob.upperBound(arr, arr.size(), target);
        cout << endl;
    }
    return 0;
}