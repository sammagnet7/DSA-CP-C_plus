#include <iostream>
#include <vector>
#include <climits>
#include <sstream>
#include <set>

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

Approach followed: 2 pointer approach is best in case of given arrays are already sorted
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
    // Approach:
    // ---------
    // We are given two sorted arrays `a` and `b`. We need to compute their UNION
    // (all unique elements from both arrays, sorted).
    //
    // Since both arrays are sorted, we can efficiently use the "two pointers" technique:
    //   1. Maintain two indices `idx_a` and `idx_b`, starting at 0.
    //   2. Compare a[idx_a] and b[idx_b]:
    //        - If one is smaller, push it to the result and advance that pointer.
    //        - If both are equal, push it once and advance both pointers.
    //   3. To handle duplicates within arrays, always check the last element of result
    //      (`res.back()`) before inserting a new one. If it's the same, skip.
    //   4. After one array is fully traversed, process the remaining elements of the other
    //      (again skipping duplicates).
    //
    // This guarantees that:
    //   - All elements are inserted in sorted order (because inputs are sorted).
    //   - No duplicates appear in the final union.
    //
    // Time Complexity: O(m + n)
    //   - Each pointer moves at most once across its array.
    // Space Complexity: O(1) {excluding result vector}
    //   - We only use the result vector as output storage.
    //
    vector<int> findUnion(vector<int> &a, vector<int> &b)
    {
        vector<int> res; // Final result storing unique elements in sorted order

        int idx_a = 0, idx_b = 0; // Two pointers for arrays `a` and `b`

        // Traverse both arrays until one is exhausted
        while (idx_a < a.size() && idx_b < b.size())
        {
            // Case 1: Skip duplicate in `a`
            if (!res.empty() && a[idx_a] == res.back())
                idx_a++;

            // Case 2: Skip duplicate in `b`
            else if (!res.empty() && b[idx_b] == res.back())
                idx_b++;

            // Case 3: Smaller element is added to result
            else if (a[idx_a] < b[idx_b])
                res.push_back(a[idx_a++]);

            else if (a[idx_a] > b[idx_b])
                res.push_back(b[idx_b++]);

            // Case 4: Equal elements -> add once, move both pointers
            else if (a[idx_a] == b[idx_b])
            {
                res.push_back(a[idx_a]);
                idx_a++;
                idx_b++;
            }
        }

        // Add remaining elements of `a` (if any), skipping duplicates
        while (idx_a < a.size())
        {
            if (a[idx_a] == res.back())
            {
                idx_a++; // Skip duplicate
                continue;
            }
            res.push_back(a[idx_a++]);
        }

        // Add remaining elements of `b` (if any), skipping duplicates
        while (idx_b < b.size())
        {
            if (b[idx_b] == res.back())
            {
                idx_b++; // Skip duplicate
                continue;
            }
            res.push_back(b[idx_b++]);
        }

        return res; // Final union array
    }

    // Approach:
    // ---------
    // We want the union of two arrays `a` and `b` (all unique elements, sorted).
    // Using a `set` makes this straightforward:
    //   1. Insert all elements of array `a` into the set.
    //   2. Insert all elements of array `b` into the set.
    //   3. Since `set` stores elements in sorted order and automatically removes duplicates,
    //      the final set already represents the union.
    //   4. Convert the set back to a vector for the result.
    //
    // Time Complexity: O((m+n) * log(m+n))
    //   - Each insertion into a set takes O(log(size)).
    //   - Total insertions = m+n.
    //   - So complexity = O((m+n) log(m+n)).
    //
    // Space Complexity: O(m+n)
    //   - The set may store all elements from both arrays in the worst case.
    //   - The output vector also uses O(m+n).
    //
    // Note:
    //   - Simpler to implement than two-pointer approach.
    //   - But slightly less efficient in time (due to log factor) and space (extra set).
    //
    vector<int> findUnion(vector<int> &a, vector<int> &b)
    {
        // Step 1: Create a set initialized with elements of `a`
        set<int> st(a.begin(), a.end());

        // Step 2: Insert all elements of `b` into the set
        // (duplicates are automatically ignored)
        for (int j : b)
        {
            st.insert(j);
        }

        // Step 3: Convert set back into a vector (sorted + unique)
        return vector<int>(st.begin(), st.end());
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