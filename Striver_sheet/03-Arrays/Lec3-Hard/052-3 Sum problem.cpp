#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

/*
3 Sum : Find triplets that add up to a zero

https://takeuforward.org/data-structure/3-sum-find-triplets-that-add-up-to-a-zero/
https://leetcode.com/problems/3sum/description/
https://www.naukri.com/code360/problems/three-sum_6922132?utm_source=striver&utm_medium=website&utm_campaign=codestudio_a_zcourse

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Note:Solution set must not contain duplicate triplets.

Examples:

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0


INPUT::::::
3
-1 0 1 2 -1 -4
0 1 1
0 0 0

OUTPUT::::::

[[-1 -1 2 ][-1 0 1 ]]
[]
[[0 0 0 ]]

 */
class Solution
{
public:
    /*
        Approach: Brute Force + Deduplication
        -------------------------------------
        Intuition:
            - Check every possible triplet using 3 nested loops.
            - If their sum is zero, store the triplet as a candidate answer.
            - To avoid duplicate triplets:
                * Sort the triplet (since order of elements doesn’t matter).
                * Insert into a `set<vector<int>>`, which maintains uniqueness.

        Steps:
            1) Initialize a set `uniqResp` to collect unique triplets.
            2) Use 3 nested loops:
                - i from 0 to N-3
                - j from i+1 to N-2
                - k from j+1 to N-1
            → this enumerates every distinct triplet (i,j,k).
            3) For each triplet:
                - Check if arr[i] + arr[j] + arr[k] == 0.
                - If yes, create a vector {arr[i], arr[j], arr[k]}.
                - Sort the triplet (O(3) ≈ O(1)).
                - Insert into `uniqResp` (deduplication).
            4) Convert the set into a vector<vector<int>> and return.

        Complexity:
            - Time: O(N^3) for the 3 nested loops.
            * Each loop runs ~N times, so total ~N^3 checks.
            * Sorting each triplet is O(3 log 3) ≈ O(1).
            * Insertion into set is O(log M), where M = number of unique triplets (≤ N^3).
            * Overall: O(N^3).
            - Space: O(M) for the set of unique triplets (M ≤ N^3 in worst case).

        Limitations:
            - This brute-force solution is too slow for large N (e.g., N > 300).
            - Optimized approaches exist:
                * Sorting + two-pointer method: O(N^2).
                * Hashing-based approaches: O(N^2) expected.
            - But this version is simple, correct, and demonstrates the basic idea.

    */
    vector<vector<int>> threeSum(vector<int> &arr)
    {
        int N = arr.size();
        set<vector<int>> uniqResp; // stores unique sorted triplets

        // Enumerate all triplets
        for (int i = 0; i < N - 2; i++)
        {
            for (int j = i + 1; j < N - 1; j++)
            {
                for (int k = j + 1; k < N; k++)
                {
                    if (arr[i] + arr[j] + arr[k] == 0)
                    {
                        // Found a triplet that sums to 0
                        vector<int> temp = {arr[i], arr[j], arr[k]};
                        sort(temp.begin(), temp.end()); // normalize order
                        uniqResp.insert(temp);          // deduplicate
                    }
                }
            }
        }

        // Convert set to vector of triplets
        return vector<vector<int>>(uniqResp.begin(), uniqResp.end());
    }

    /*
    threeSum
    --------
        Approach: Hashing-based 2-Sum Extension
        ---------------------------------------
        Intuition:
            - The 3-Sum problem can be reduced to repeated 2-Sum problems:
                * Fix one element nums[i].
                * Then find two other elements nums[j], nums[k] such that
                        nums[j] + nums[k] == -(nums[i]).
                * This is exactly the 2-Sum problem with target = -nums[i].
            - To solve 2-Sum efficiently:
                * Use a hash set to store elements seen so far (in_between_vals).
                * For each nums[j], compute the required complement:
                        req = restTargetSum - nums[j].
                * If complement already exists in the set, we found a triplet.

        Handling duplicates:
            - Sort each triplet {nums[i], req, nums[j]} before inserting,
                so that {2, -1, -1} and {-1, 2, -1} normalize to {-1, -1, 2}.
            - Store triplets in a set<vector<int>> uniq_triplets,
                which ensures uniqueness across all triplets.

        Steps in code:
            1. Initialize an empty set `uniq_triplets`.
            2. Loop over i = 0..n-2 (fix nums[i]).
            3. For each i:
                - Initialize empty hash set in_between_vals.
                - Set restTargetSum = -nums[i].
                - Inner loop j = i+1..n-1:
                    * Compute req = restTargetSum - nums[j].
                    * If req is in in_between_vals → found a triplet.
                    * Normalize triplet by sorting, then insert into uniq_triplets.
                    * Insert nums[j] into in_between_vals.
            4. At the end, convert uniq_triplets (set) to vector for output.

        Complexity:
            - Outer loop: O(n).
            - Inner loop: O(n).
            - Hash set lookup/insert: O(1) average.
            - For each valid triplet, sorting 3 elements = O(1).
            - Inserting into set: O(log M), where M = number of unique triplets.
            - Total time: O(n^2 log M).
            - Space: O(n) for hash set + O(M) for storing unique triplets.

        Limitations:
            - More efficient than brute force O(n^3).
            - But slower than the optimal O(n^2) two-pointer method because:
                * Using set incurs O(log M) insertion.
                * Still does not avoid all redundant checks.
            - Can cause TLE on large inputs (e.g., n ~ 10^4).

        Summary:
            - Good improvement over naive solution.
            - Demonstrates connection between 3-Sum and 2-Sum hashing.
            - For optimal performance, prefer sorted + two-pointer O(n^2) approach.
        */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        int targetSum = 0;

        set<vector<int>> uniq_triplets; // ensure no duplicate triplets

        // Fix one number nums[i]
        for (int i = 0; i < n - 1; i++)
        {
            unordered_set<int> in_between_vals;      // seen elements for 2-sum
            int restTargetSum = targetSum - nums[i]; // pair sum needed

            // Two-sum logic on the remaining subarray
            for (int j = i + 1; j < n; j++)
            {
                int req = restTargetSum - nums[j];

                // Check if required complement is already seen
                if (in_between_vals.find(req) != in_between_vals.end())
                {
                    vector<int> triplet = {nums[i], req, nums[j]};
                    sort(triplet.begin(), triplet.end()); // normalize triplet order
                    uniq_triplets.insert(triplet);        // insert into set
                }

                // Add nums[j] to hash set for future checks
                in_between_vals.insert(nums[j]);
            }
        }

        // Convert set to vector
        return vector<vector<int>>(uniq_triplets.begin(), uniq_triplets.end());
    }

    /*
        Approach: Sorting + Two Pointers (Optimal O(n^2))
        -------------------------------------------------
        Intuition:
            - After sorting the array:
                * Fix the first element nums[i].
                * Now the problem reduces to finding pairs (nums[l], nums[r]) such that:
                    nums[l] + nums[r] == -nums[i].
                * This is a classic 2-Sum problem on a sorted array, solvable with two pointers.

        Key Ideas:
            1. Sort array → ensures duplicates are grouped and allows two-pointer logic.
            2. For each index i:
                - Skip duplicate nums[i] to avoid duplicate triplets.
                - Use two pointers:
                    l = i+1 (start of subarray)
                    r = n-1 (end of subarray)
                - While l < r:
                    * If nums[l] + nums[r] < -nums[i], need larger sum → l++.
                    * If nums[l] + nums[r] > -nums[i], need smaller sum → r--.
                    * If equal, found a valid triplet:
                        store {nums[i], nums[l], nums[r]}.
                        then move l++, r-- while skipping duplicates.
            3. Continue until all i processed.

        Why it works:
            - Sorting + two-pointer ensures O(n^2) time complexity.
            - Skipping duplicates ensures no repeated triplets are added.
            - Each triplet is generated exactly once in sorted order.

        Complexity:
            - Sorting: O(n log n).
            - Outer loop over i: O(n).
            - Inner two-pointer scan: O(n) per i in worst case.
            - Total: O(n^2).
            - Space: O(1) extra (excluding output).

        Optimality:
            - This is the standard optimal solution for 3-Sum.
            - Brute force O(n^3) and hashing-based O(n^2 log n) approaches are slower.

    */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        int targetSum = 0;

        // Step 1: Sort the array
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        // Step 2: Fix first element nums[i]
        for (int i = 0; i < n - 2; i++)
        {

            // Skip duplicate values for the first element
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int l = i + 1;                           // left pointer
            int r = n - 1;                           // right pointer
            int restTargetSum = targetSum - nums[i]; // pair sum needed

            // Two-sum logic on the remaining subarray:
            // Step 3: Two-pointer scan
            while (l < r)
            {
                int curSum = nums[l] + nums[r];

                if (curSum < restTargetSum)
                {
                    l++; // need a bigger sum
                }
                else if (curSum > restTargetSum)
                {
                    r--; // need a smaller sum
                }
                else
                {
                    // Found a valid triplet
                    ans.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;

                    // Skip duplicates for nums[l]
                    while (l < r && nums[l - 1] == nums[l])
                        l++;
                    // Skip duplicates for nums[r]
                    while (l < r && nums[r + 1] == nums[r])
                        r--;
                }
            }

        }

        return ans;
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

        vector<vector<int>> res = ob.threeSum(arr);

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