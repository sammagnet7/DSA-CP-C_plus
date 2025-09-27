#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Merge two Sorted Arrays Without Extra Space -> into arr1 only

https://takeuforward.org/data-structure/merge-two-sorted-arrays-without-extra-space/
https://leetcode.com/problems/merge-sorted-array/description/

Problem statement:
You are given two integer arrays arr1 and arr2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in arr1 and arr2 respectively.
Merge arr1 and arr2 into a single array sorted in non-decreasing order.
The final sorted array should not be returned by the function, but instead be stored inside the array arr1. To accommodate this, arr1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. arr2 has a length of n.


Examples:

Example 1:
    Input: arr1 = [1,2,3,0,0,0], m = 3, arr2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]
    Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
    The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from arr1.

Example 2:
    Input: arr1 = [1], m = 1, arr2 = [], n = 0
    Output: [1]
    Explanation: The arrays we are merging are [1] and [].
    The result of the merge is [1].

Example 3:
    Input: arr1 = [0], m = 0, arr2 = [1], n = 1
    Output: [1]
    Explanation: The arrays we are merging are [] and [1].
    The result of the merge is [1].
    Note that because m = 0, there are no elements in arr1. The 0 is only there to ensure the merge result can fit in arr1.

INPUT::::::
6
4 3
1 4 8 10 0 0 0
2 3 9
4 5
1 3 5 7 0 0 0
0 2 6 8 9

OUTPUT::::::
[ 1 2 3 4 8 9 10 ]
[ 0 1 2 3 5 6 7 8 9 ]


 */
class Solution
{
public:
    /*
        merge
        -----
        Problem:
            - You are given two sorted arrays:
                nums1: size m + n, with the first m elements valid and sorted,
                    and the last n elements empty (placeholders for merge).
                nums2: size n, fully sorted.
            - Merge nums2 into nums1 so that nums1 contains all elements sorted.

        Approach:
            - Instead of using extra space, we rearrange values directly between nums1 and nums2.

        Steps:
            1. Compare elements from the end of nums1’s valid part with the beginning of nums2.
                - i points to the last valid element of nums1 (index m-1).
                - j points to the start of nums2 (index 0).
                - If nums1[i] > nums2[j], swap them:
                    * Bigger element moves into nums2,
                    * Smaller element comes into nums1.
                - Decrement i and increment j.
                - If nums1[i] <= nums2[j], just increment j (nums2[j] already bigger).
            2. After this loop, all elements in nums1 are ≤ all elements in nums2,
            but internal order may be disturbed.
            3. Sort both halves again:
                - nums1[0..m-1]
                - nums2[0..n-1]
            4. Copy all nums2’s sorted elements back into nums1[m..m+n-1].

        Intuition:
            - Step 1 ensures partition: smaller values gravitate to nums1, larger to nums2.
            - Step 2 restores order inside each array.
            - Step 3 finalizes the in-place merge.

        Complexity:
            - Partition loop: O(min(m, n))
            - Sorting nums1’s first m elements: O(m log m)
            - Sorting nums2: O(n log n)
            - Copying nums2 into nums1: O(n)
            - Total Time: O(min(m,n) + m log m + n log n)
            - Space: O(1) extra (in-place swap and sort).

        Limitation:
            - Works, but not the most optimal.
            - An even better solution uses the "Gap Method" (like Shell Sort) to avoid
            sorting each array separately, reducing unnecessary work.

        Example:
            nums1 = [1,4,7,0,0,0], m=3
            nums2 = [2,5,6], n=3

            Step1 swapping:
                nums1 = [1,4,2,0,0,0], nums2 = [7,5,6]
                nums1 = [1,4,2,0,0,0], nums2 = [7,5,6] → no swap, done.

            Step2 sorting:
                nums1[0..2] = [1,2,4], nums2 = [5,6,7]

            Step3 copy back:
                nums1 = [1,2,4,5,6,7]
    */
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int i = m - 1; // last valid index in nums1
        int j = 0;     // first index in nums2

        // Step 1: swap misplaced elements
        while (i >= 0 && j < n)
        {
            if (nums1[i] > nums2[j])
            {
                swap(nums1[i--], nums2[j++]);
            }
            else
            {
                j++;
            }
        }

        // Step 2: sort both parts independently
        sort(nums1.begin(), nums1.begin() + m);
        sort(nums2.begin(), nums2.begin() + n);

        // Step 3: append sorted nums2 into nums1
        for (int j = 0; j < n; j++)
        {
            nums1[m + j] = nums2[j];
        }
    }

    /*
    merge
    -----
    Problem:
        - Given two sorted arrays:
            arr1: of size m + n, first m elements valid and sorted, last n slots empty.
            arr2: of size n, fully sorted.
        - Merge arr2 into arr1 so that arr1 contains all elements sorted.

    Approach: Optimal In-place Merge by Right Shifting
    ---------------------------------------------------
    Intuition:
        - Normally, merging two sorted arrays requires O(m + n) extra space.
        - To do it in-place:
            1. Right shift the m valid elements of arr1 to the end.
               - This makes the first n slots of arr1 empty.
               - Now arr1 can be filled from the beginning by merging.
            2. Perform a classic merge of two sorted arrays:
               - i pointer traverses shifted arr1 elements.
               - j pointer traverses arr2.
               - k pointer fills arr1 from the start.
            3. Copy the remaining elements from whichever array still has leftovers.

    Steps in code:
        - Right shift arr1’s first m elements to positions [n .. m+n-1].
        - Initialize:
            i = n (start of shifted arr1 part),
            j = 0 (start of arr2),
            k = 0 (position to fill in arr1).
        - While both halves have elements:
            * Compare arr1[i] and arr2[j].
            * Place smaller at arr1[k], then advance the respective pointer.
        - Copy leftovers from arr1’s shifted part (if any).
        - Copy leftovers from arr2 (if any).

    Why it works:
        - By shifting arr1’s valid part to the back, we free up space at the front.
        - This lets us merge in-place without overwriting unprocessed elements.
        - Classic merge logic guarantees sorted order.

    Complexity:
        - Time: O(m + n) → each element processed once.
        - Space: O(1) → only uses pointers, no extra arrays.

    Example:
        arr1 = [1,3,5,0,0,0], m=3
        arr2 = [2,4,6], n=3
        After shifting arr1: arr1 = [1,3,5,1,3,5] (conceptually [_,_,_,1,3,5])
        Merge step fills arr1 as [1,2,3,4,5,6].

*/
    void merge(vector<long long> &arr1, int m, vector<long long> &arr2, int n)
    {
        int t = m + n;

        // Step 1: Right shift arr1’s first m elements to the back
        // e.g., arr1 = [1,3,5,0,0,0] → shift → [_,_,_,1,3,5]
        for (int i = m - 1, j = 0; i >= 0; i--, j++)
        {
            arr1[t - 1 - j] = arr1[i];
        }

        // Step 2: Merge shifted arr1 and arr2 into arr1
        int i = n; // pointer to shifted arr1’s valid start
        int j = 0; // pointer to arr2
        int k = 0; // pointer to write merged values in arr1

        while (i < t && j < n)
        {
            if (arr1[i] <= arr2[j])
            {
                arr1[k] = arr1[i];
                k++;
                i++;
            }
            else
            {
                arr1[k] = arr2[j];
                k++;
                j++;
            }
        }

        // Step 3: Copy remaining elements from shifted arr1
        while (i < t)
        {
            arr1[k] = arr1[i];
            k++;
            i++;
        }

        // Step 4: Copy remaining elements from arr2
        while (j < n)
        {
            arr1[k] = arr2[j];
            k++;
            j++;
        }
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int m, n;
        cin >> m >> n;
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
        ob.merge(arr1, m, arr2, n);

        cout << "[ ";
        for (long long i = 0; i < m + n; i++)
        {
            cout << arr1[i] << " ";
        }
        cout << "]";
        cout << endl;
    }
    return 0;
}