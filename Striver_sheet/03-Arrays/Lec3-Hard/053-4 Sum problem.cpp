#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
4 Sum | Find Quads that add up to a target value

https://takeuforward.org/data-structure/4-sum-find-quads-that-add-up-to-a-target-value/
https://leetcode.com/problems/4sum/description/
https://www.naukri.com/code360/problems/4sum_5713771?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse


Problem statement:
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Examples:

Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]


INPUT::::::
7
0
1 0 -1 0 -2 2
9
4 3 3 4 4 2 1 2 1 1
8
2 2 2 2 2
5
1 2 1 0 1
8
2 2 2 2 1 3
4
1 1 1 0
0
1000000000 1000000000 1000000000 1000000000

OUTPUT::::::

[[-2 -1 1 2 ][-2 0 0 2 ][-1 0 0 1 ]]
[[1 1 3 4 ][1 2 2 4 ][1 2 3 3 ]]
[[2 2 2 2 ]]
[[1 1 1 2 ]]
[[1 2 2 3 ][2 2 2 2 ]]
[]
[]

 */
class Solution
{
public:
    // // Approach: Brute
    // // Time: O(N^4 Log N)
    // // Space: O(N)
    vector<vector<int>> fourSum(vector<int> &arr, int target)
    {
        int N = arr.size();
        set<vector<int>> uniqResp;

        for (int i = 0; i < N - 3; i++)
        {
            for (int j = i + 1; j < N - 2; j++)
            {
                for (int k = j + 1; k < N - 1; k++)
                {
                    for (int l = k + 1; l < N; l++)
                    {
                        if (arr[i] + arr[j] + arr[k] + arr[l] == target)
                        {
                            vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                            sort(temp.begin(), temp.end()); // O(4)
                            uniqResp.insert(temp);
                        }
                    }
                }
            }
        }

        return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    }

    /*
        fourSum (hashing-based extension of 2-Sum / 3-Sum idea)
        -------------------------------------------------------
        Problem:
        - Find all unique quadruplets (a,b,c,d) from array `arr` such that
            a + b + c + d == target.
        - Return unique quadruplets (no duplicates). Order of numbers inside a
            quadruplet does not matter (we normalize each quadruplet by sorting).

        Approach (in the same "style" as the 3-Sum hashing-based method):
        - Reduce 4-Sum to repeated 2-Sum checks by fixing two elements.
        - Fix two indices i and j (i < j). For the remaining subarray arr[j+1..n-1],
            we search for pairs (p,q) with p < q such that arr[p] + arr[q] == target - (arr[i] + arr[j]).
        - We solve this inner 2-Sum using a hash set `seen` that stores values encountered
            so far when scanning from left to right inside the j+1..n-1 range:
            * For each k from j+1 to n-1:
                req = neededSum - arr[k]
                if req exists in `seen`, then there is at least one index p (j < p < k)
                with arr[p] == req, so (arr[i], arr[j], req, arr[k]) forms a valid quadruplet.
                Normalize (sort) the quadruplet and insert into a set< vector<int> >
                to ensure uniqueness across all found quadruplets.
                Then insert arr[k] into `seen` so future k's can pair with it.
        - This enumerates all index-ordered quadruplets with i < j < p < k (p is where `req` appeared),
            hence every distinct index combination is considered exactly once in terms of existence.

        Why it works:
        - Outer loops fix two elements. For each fixed pair we look for complementary pairs
            among later elements. Using a hash set gives O(1) average-time membership tests,
            so the inner scan is linear in the length of the remaining suffix.
        - Sorting each quadruplet before insertion into the `uniq_quadruplets` set
            ensures value-based uniqueness (triples/quads with same values but different indices
            map to the same canonical vector).

        Complexity:
        - Time: O(n^3) in the worst case (two loops for i,j and an inner linear scan over k).
            * For each i (O(n)) and each j (O(n)), the inner loop is O(n) on average,
            so O(n^3) total.
        - Space: O(M + n) where M is the number of unique quadruplets stored and
            O(n) for the temporary hash set `seen`.
        - This is better than brute-force O(n^4) but not optimal for very large n.
            For very large arrays consider sorting + two-pointer + hashing combination to get better constants.

        Notes / Limitations:
        - This method does not assume the input is sorted; it normalizes quadruplets by sorting them
            before insertion into the uniqueness set.
        - Because we use value-based `seen` (unordered_set<int>), if an element value repeats at multiple
            earlier positions, membership detection still works (we just need existence of at least one).
        - Duplicate quadruplets (same values but different index sets) are removed by the `set<vector<int>>`.
        - If `arr` elements and `target` can be large (e.g., up to 1e9), use 64-bit arithmetic for intermediate sums.
    */

    vector<vector<int>> fourSum(vector<int> &arr, int target)
    {
        int n = (int)arr.size();
        set<vector<int>> uniq_quadruplets; // store unique, sorted quadruplets

        // Fix first element i and second element j (i < j)
        for (int i = 0; i < n - 3; ++i)
        {
            for (int j = i + 1; j < n - 2; ++j)
            {

                // needed sum for the remaining pair (p, k): arr[p] + arr[k] == needed
                long long needed = (long long)target - (long long)arr[i] - (long long)arr[j];

                // Hash set stores values seen so far in the scan over indices (j+1 .. n-1)
                unordered_set<int> seen;

                // Scan the suffix and check if any previously seen value complements arr[k]
                for (int k = j + 1; k < n; ++k)
                {
                    long long req = needed - (long long)arr[k];

                    // If a complement value was seen earlier (between j+1 and k-1),
                    // we found a quadruplet (arr[i], arr[j], req, arr[k]).
                    if (req >= INT_MIN && req <= INT_MAX)
                    { // safe cast check (optional)
                        if (seen.find((int)req) != seen.end())
                        {
                            vector<int> quad = {arr[i], arr[j], (int)req, arr[k]};
                            sort(quad.begin(), quad.end()); // normalize by value order
                            uniq_quadruplets.insert(quad);
                        }
                    }

                    // Mark current value arr[k] as seen for future iterations
                    seen.insert(arr[k]);
                }
            }
        }

        // Convert set to vector for return
        return vector<vector<int>>(uniq_quadruplets.begin(), uniq_quadruplets.end());
    }

    /*
        fourSum
        -------
        Problem:
            - Find all unique quadruplets (a, b, c, d) in the array such that:
                a + b + c + d == target
            - Return all unique quadruplets without duplicates.

        Approach: Sorting + Two-Pointer Technique (Optimal O(n^3))
        -----------------------------------------------------------
        Intuition:
            - A naive brute force solution checks all 4-element combinations → O(n^4).
            - We can optimize by fixing the first two numbers (arr[i], arr[j]).
            - Then the problem reduces to finding two numbers (arr[left], arr[right])
            such that their sum == target - (arr[i] + arr[j]).
            - Because the array is sorted:
                * If current sum < required sum → move left++ (to increase sum).
                * If current sum > required sum → move right-- (to decrease sum).
                * If equal → found a quadruplet, then move both pointers while skipping duplicates.
            - Sorting also makes it easy to skip duplicates at every stage.

        Key Steps:
            1. Sort the array.
            2. Loop i = 0..n-4 → fix first element.
            * Skip duplicates for arr[i].
            3. Loop j = i+1..n-3 → fix second element.
            * Skip duplicates for arr[j].
            4. Two-pointer search in subarray [j+1..n-1] for pairs that complete the quadruplet.
            5. Skip duplicates for left and right pointers to avoid duplicate quadruplets.
            6. Store results directly in `result`.

        Complexity:
            - Sorting: O(n log n).
            - Outer loop (i): O(n).
            - Inner loop (j): O(n).
            - Two-pointer scan: O(n).
            - Total: O(n^3).
            - Space: O(1) extra (excluding result).

        Why it works:
            - Sorting enables the two-pointer method.
            - Skipping duplicates ensures only unique quadruplets are included.
            - Using long long for intermediate sums prevents overflow when target/arr[i]/arr[j] are large.

        Limitations:
            - Still cubic time O(n^3). Works fine for n up to a few thousand,
            but too slow for very large arrays (n ~ 10^5).
    */
    vector<vector<int>> fourSum(vector<int> &arr, int target)
    {
        vector<vector<int>> result;
        int n = (int)arr.size();
        if (n < 4)
            return result;

        sort(arr.begin(), arr.end()); // sort to use two-pointer and skip duplicates

        // Fix first element
        for (int i = 0; i < n - 3; ++i)
        {
            // Skip duplicate values for the first element
            if (i > 0 && arr[i] == arr[i - 1])
                continue;

            // Fix second element
            for (int j = i + 1; j < n - 2; ++j)
            {
                // Skip duplicate values for the second element
                if (j > i + 1 && arr[j] == arr[j - 1])
                    continue;

                int left = j + 1;
                int right = n - 1;
                long long twoSumTarget = (long long)target - ((long long)arr[i] + (long long)arr[j]);

                // Two-pointer search for a pair in arr[left..right] summing to twoSumTarget
                while (left < right)
                {
                    long long curSum = (long long)arr[left] + (long long)arr[right];
                    if (curSum < twoSumTarget)
                    {
                        ++left; // need a larger sum
                    }
                    else if (curSum > twoSumTarget)
                    {
                        --right; // need a smaller sum
                    }
                    else
                    {
                        // Found a quadruplet
                        result.push_back({arr[i], arr[j], arr[left], arr[right]});

                        // Advance both pointers and skip duplicates for left and right
                        ++left;
                        --right;
                        while (left < right && arr[left] == arr[left - 1])
                            ++left;
                        while (left < right && arr[right] == arr[right + 1])
                            --right;
                    }
                }
            }
        }

        return result;
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
        int k;
        cin >> k;
        cin.ignore();

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

        vector<vector<int>> res = ob.fourSum(arr, k);

        cout << "[";
        for (auto e : res)
        {
            cout << "[";
            for (auto ee : e)
            {
                cout << ee << " ";
            }
            cout << "]";
        }
        cout << "]";

        cout << endl;
    }
}