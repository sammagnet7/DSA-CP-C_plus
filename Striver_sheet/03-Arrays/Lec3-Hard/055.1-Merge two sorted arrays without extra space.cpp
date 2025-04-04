#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Merge two Sorted Arrays Without Extra Space

https://takeuforward.org/data-structure/merge-two-sorted-arrays-without-extra-space/
https://www.naukri.com/code360/problems/merge-two-sorted-arrays-without-extra-space_6898839?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse&leftPanelTabValue=PROBLEM

Problem statement:
Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order. Merge them in sorted order. Modify arr1 so that it contains the first N elements and modify arr2 so that it contains the last M elements.

Examples:

Example 1:
Input:
    n = 4, arr1[] = [1 4 8 10]
    m = 5, arr2[] = [2 3 9]
Output:
    arr1[] = [1 2 3 4]
    arr2[] = [8 9 10]
Explanation:
    After merging the two non-decreasing arrays, we get, 1,2,3,4,8,9,10.

Example2:
Input:
    n = 4, arr1[] = [1 3 5 7]
    m = 5, arr2[] = [0 2 6 8 9]
Output:
    arr1[] = [0 1 2 3]
    arr2[] = [5 6 7 8 9]
Explanation:
    After merging the two non-decreasing arrays, we get, 0 1 2 3 5 6 7 8 9.

INPUT::::::
6
4 3
1 4 8 10
2 3 9
4 5
1 3 5 7
0 2 6 8 9

OUTPUT::::::
[ 1 2 3 4 : 8 9 10 ]
[ 0 1 2 3 : 5 6 7 8 9 ]

 */
class Solution
{
public:
    // Aproach: Optimal1
    // Make arr1 containing all the smaller elements than arr2.
    // Then sort arr1 and arr2 individually
    // Time: O( min(M,N)+ LogM LogN+)
    // Space: O(1)
    void mergeTwoSortedArraysWithoutExtraSpace(vector<long long> &arr1, vector<long long> &arr2)
    {
        int m = arr1.size();
        int n = arr2.size();

        int i = m - 1;
        int j = 0;

        // Traverese arr1 in reverse and arr2 forward
        while (i >= 0 && j < n)
        {
            if (arr2[j] < arr1[i])
            {
                swap(arr1[i--], arr2[j++]);
            }
            else
            {
                break;
            }
        }

        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
    }

    // Aproach: Optimal2
    // Follows `SHELL SORT` inplace sorting algorithm based upon `GAP = [ceil of {(m+n)/2}] -> then [ceil of{GAP/2}]`
    // Time: O((M+N)* Log (M+N))
    // Space: O(1)
    // ..
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cin.ignore();

        string line1, line2;
        getline(cin, line1);
        getline(cin, line2);

        vector<long long> arr1, arr2;

        stringstream ss1(line1);
        stringstream ss2(line2);

        long long num;

        while (ss1 >> num)
        {
            arr1.push_back(num);
        }
        while (ss2 >> num)
        {
            arr2.push_back(num);
        }

        Solution ob;
        ob.mergeTwoSortedArraysWithoutExtraSpace(arr1, arr2);

        cout << "[ ";
        for (long long i = 0; i < n; i++)
        {
            cout << arr1[i] << " ";
        }
        cout << ": ";
        for (long long j = 0; j < m; j++)
        {
            cout << arr2[j] << " ";
        }
        cout << "]";
        cout << endl;
    }
    return 0;
}