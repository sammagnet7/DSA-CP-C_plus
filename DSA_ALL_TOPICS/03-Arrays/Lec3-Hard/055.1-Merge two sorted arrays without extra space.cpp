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
    /*
    mergeTwoSortedArraysWithoutExtraSpace
    -------------------------------------
    Problem:
        - Given two sorted arrays arr1 and arr2.
        - Merge them in-place (without using extra space) such that:
              * After merging, arr1 contains the smaller elements,
              * arr2 contains the larger elements,
              * Both arr1 and arr2 remain sorted individually.

    Approach: Optimal1 (Swap + Re-sort)
    -----------------------------------
    Intuition:
        - The largest elements of arr1 (at the end) might be greater than
          the smallest elements of arr2 (at the beginning).
        - If so, those elements are "out of place" across the two arrays.
        - To fix:
            1. Traverse arr1 from the back (largest elements) and arr2 from the front (smallest elements).
            2. If arr1[i] > arr2[j], swap them.
               → This moves the smaller element into arr1 and the larger into arr2.
            3. Keep doing this until the arrays are "partitioned correctly".
        - At this point, arr1 may not be fully sorted internally, and same for arr2,
          but we know all elements in arr1 ≤ all elements in arr2.
        - Finally, sort arr1 and arr2 individually to restore sorted order.

    Example:
        arr1 = [1, 4, 7, 8, 10]
        arr2 = [2, 3, 9]
        - Compare arr1[4]=10 with arr2[0]=2 → swap → arr1=[1,4,7,8,2], arr2=[10,3,9]
        - Compare arr1[3]=8 with arr2[1]=3 → swap → arr1=[1,4,7,3,2], arr2=[10,8,9]
        - Compare arr1[2]=7 with arr2[2]=9 → no swap (arrays partitioned).
        - Sort both:
            arr1 = [1,2,3,4,7]
            arr2 = [8,9,10]

    Complexity:
        - Swap pass: O(min(m, n)) comparisons/swaps.
        - Sorting arr1: O(m log m).
        - Sorting arr2: O(n log n).
        - Total time: O(min(m, n) + m log m + n log n).
        - Space: O(1) extra (in-place).

    Limitations:
        - Requires final sorting of both arrays → adds log factors.
        - There exists a more optimal "Gap method" (Shell sort style) that avoids full sorting.

*/
    void mergeTwoSortedArraysWithoutExtraSpace(vector<long long> &arr1, vector<long long> &arr2)
    {
        int m = arr1.size();
        int n = arr2.size();

        int i = m - 1; // pointer starting at end of arr1
        int j = 0;     // pointer starting at beginning of arr2

        // Step 1: Swap misplaced elements between arr1 and arr2
        while (i >= 0 && j < n)
        {
            if (arr2[j] < arr1[i])
            {
                swap(arr1[i--], arr2[j++]); // move smaller into arr1, larger into arr2
            }
            else
            {
                break; // arrays are partitioned correctly
            }
        }

        // Step 2: Sort each array individually
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
    }

    /*
        Aproach: Optimal2

        Follows `SHELL SORT` inplace sorting algorithm based upon `GAP = [ceil of {(m+n)/2}] -> then [ceil of{GAP/2}]`

        Time: O((M+N)* Log (M+N))
        Space: O(1)
        ..
    */
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