#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
next_permutation : find next lexicographically greater permutation

https://takeuforward.org/data-structure/next_permutation-find-next-lexicographically-greater-permutation/
https://leetcode.com/problems/next-permutation/description/
https://www.naukri.com/code360/problems/893046?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website

Problem Statement: Given an array Arr[] of integers, rearrange the numbers of the given array into the lexicographically next greater permutation of numbers.
If such an arrangement is not possible, it must rearrange to the lowest possible order (i.e., sorted in ascending order).

Note:A sequence of ‘N’ integers is called a permutation if it contains all integers from 1 to ‘N’ exactly once.

Examples:

Example 1 :
Input format:
 Arr[] = {1,3,2}
Output
: Arr[] = {2,1,3}
Explanation:
All permutations of {1,2,3} are {{1,2,3} , {1,3,2}, {2,13} , {2,3,1} , {3,1,2} , {3,2,1}}. So, the next permutation just after {1,3,2} is {2,1,3}.

Example 2:
Input format:
 Arr[] = {3,2,1}
Output:
Arr[] = {1,2,3}
Explanation:
As we see all permutations of {1,2,3}, we find {3,2,1} at the last position. So, we have to return the topmost permutation


INPUT::::::
7
1 2 3
2 3 1 4 5
1 2
3 1 2
1 3 2
3 2 1
1 1 5

OUTPUT::::::

1 3 2
2 3 1 5 4
2 1
3 2 1
2 1 3
1 2 3
1 5 1
 */

class Solution
{
public:
    /*
        Time: O(N)
        Space: O(1)
        using in-built function of C++
     */
    // void nextPermutation(vector<int> &arr)
    // {
    //     int N = arr.size();
    //     next_permutation(arr.begin(), arr.end());
    // }

    /*
        Algo:
        Observations:
            In case of next permutation there are some pattern to observe.
            1. Traverse digits from end to start. You will see digits increasing in order from end to upto an index.
            2. Save the index(take as pivotIdx) where this order is breaking.
            3. If pivotIdx does not not exists, that means next permuatation is the reverse of the whole digits
            3. Else the next permutation can be created by two steps:
                3.1. Find a digit in the right part of the pivot, which is just the next greater element than pivot
                3.2. Swap the pivot with that element
                3.3. Then Reverse the right part of the array

        Time: O(N)
        Space: O(1)

     */
    void nextPermutation(vector<int> &arr)
    {
        int N = arr.size();
        int pivotIdx = -1;

        for (int i = N - 1; i > 0; i--)
        {
            if (arr[i - 1] < arr[i])
            {
                pivotIdx = i - 1;
                break;
            }
        }
        if (pivotIdx == -1)
        {
            reverse(arr.begin(), arr.end());
            return;
        }
        else
        {
            for (int i = N - 1; i > pivotIdx; i--)
            {
                if (arr[i] > arr[pivotIdx])
                {
                    swap(arr[i], arr[pivotIdx]);
                    reverse(arr.begin() + pivotIdx + 1, arr.end());
                    return;
                }
            }
        }
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
        // int k;
        // cin >> k;
        // cin.ignore();

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

        ob.nextPermutation(arr);

        for (int e : arr)
        {
            cout << e << " ";
        }

        cout << endl;
    }
}