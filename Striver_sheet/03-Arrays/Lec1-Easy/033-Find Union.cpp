#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

/*
https://takeuforward.org/data-structure/union-of-two-sorted-arrays/
https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=union-of-two-sorted-arrays
https://www.naukri.com/code360/problems/sorted-array_6613259?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem Statement:
Given two sorted arrays a[] and b[], where each array may contain duplicate elements , the task is to return the elements in the union of the two arrays in sorted order.
Union of two arrays can be defined as the set containing distinct common elements that are present in either of the arrays.

Examples:
Input: a[] = [1, 2, 3, 4, 5], b[] = [1, 2, 3, 6, 7]
Output: 1 2 3 4 5 6 7
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5 6 7.

Input: a[] = [2, 2, 3, 4, 5], b[] = [1, 1, 2, 3, 4]
Output: 1 2 3 4 5
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5.

Input: a[] = [1, 1, 1, 1, 1], b[] = [2, 2, 2, 2, 2]
Output: 1 2
Explanation: Distinct elements including both the arrays are: 1 2.


Constraints:
1  <=  a.size(), b.size()  <=  105
-109  <=  a[i] , b[i]  <=  109

Approach folloed: 2 pointer approach is best in case of given arrays are already sorted
Other approach: Using Set. But inserting m+n th element takes log(m+n) time. Upon approximation across inserting all elements in worst, it would take O((m+n)log(m+n) time.
Another approach: Using Map. i.e. using a Frequency map. But  inserting m+n th element takes log(m+n) time. Upon approximation across insertion of all elements in worst it would take O((m+n)log(m+n) time.


INPUT::::::
3
1 2 3 4 5
1 2 3 6 7

2 2 3 4 5
1 1 2 3 4

1 1 1 1 1
2 2 2 2 2

OUTPUT::::::

1 2 3 4 5 6 7
1 2 3 4 5
1 2

 */
class Solution
{
public:
    // Time: O(m+n)
    // Space: O(1) {If Space of union ArrayList is not considered}
    vector<int> findUnion(vector<int> &a, vector<int> &b)
    {
        vector<int> res;

        int idx_a = 0, idx_b = 0;

        while (idx_a < a.size() && idx_b < b.size())
        {
            if (res.size() != 0 && a[idx_a] == res.back())
                idx_a++;

            else if (res.size() != 0 && b[idx_b] == res.back())
                idx_b++;

            else if (a[idx_a] < b[idx_b])
                res.push_back(a[idx_a++]);

            else if (a[idx_a] > b[idx_b])
                res.push_back(b[idx_b++]);

            else if (a[idx_a] == b[idx_b])
            {
                res.push_back(a[idx_a]);
                idx_a++;
                idx_b++;
            }
        }

        while (idx_a < a.size())
        {
            if (a[idx_a] == res.back())
            {
                idx_a++;
                continue;
            }
            res.push_back(a[idx_a++]);
        }
        while (idx_b < b.size())
        {
            if (b[idx_b] == res.back())
            {
                idx_b++;
                continue;
            }
            res.push_back(b[idx_b++]);
        }

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
        string input1, input2;

        getline(cin, input1);
        getline(cin, input2);
        cin.ignore();

        stringstream ss1(input1);
        stringstream ss2(input2);

        vector<int> arr1, arr2;
        int num;

        while (ss1 >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr1.push_back(num);
        }
        while (ss2 >> num) // `ss` gives space seperated characters as output which gets converted into int
        {
            arr2.push_back(num);
        }

        Solution ob;

        vector<int> res = ob.findUnion(arr1, arr2);

        for (int i : res)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}