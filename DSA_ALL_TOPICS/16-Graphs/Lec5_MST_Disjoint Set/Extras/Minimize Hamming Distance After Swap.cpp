#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_set>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

/*

1. Title: Minimize Hamming Distance After Swap Operations

Links:
https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/description/


Problem statement:
You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.


Example 1:
    Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
    Output: 1
    Explanation: source can be transformed the following way:
    - Swap indices 0 and 1: source = [2,1,3,4]
    - Swap indices 2 and 3: source = [2,1,4,3]
    The Hamming distance of source and target is 1 as they differ in 1 position: index 3.

Example 2:
    Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
    Output: 2
    Explanation: There are no allowed swaps.
    The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.

Example 3:
    Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
    Output: 0


Constraints:
    n == source.length == target.length
    1 <= n <= 10^5
    1 <= source[i], target[i] <= 10^5
    0 <= allowedSwaps.length <= 10^5
    allowedSwaps[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Minimize Hamming Distance After Swap Operations
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * Approach: DSU + Frequency Mapping (Refactored)
 * ============================================================================
 * Logic:
 * We use DSU to link all swappable indices. Then, for each DSU component, we
 * count the frequencies of the available `source` numbers. Finally, we iterate
 * through the `target` array and check if the required number is available in
 * that index's component pool.
 * ============================================================================
 * Complexity:
 * - Time: O(N). DSU operations take near O(1) time. Hash map insertions and
 * lookups take O(1) average time.
 * - Space: O(N) for the DSU arrays and the frequency maps.
 * ============================================================================
 */

class DSU
{
private:
    vector<int> par, size;

public:
    DSU(int n)
    {
        par.assign(n, 0);
        size.assign(n, 1); // Start sizes at 1

        for (int i = 0; i < n; ++i)
        {
            par[i] = i;
        }
    }

    int getPar(int a)
    {
        if (par[a] == a)
        {
            return a;
        }
        // Path compression
        return par[a] = getPar(par[a]);
    }

    void duni(int a, int b)
    {
        int pa = getPar(a);
        int pb = getPar(b);

        if (pa == pb)
            return;

        int sa = size[pa];
        int sb = size[pb];

        // Union by Size (Fixed the addition bug)
        if (sa <= sb)
        {
            par[pa] = pb;
            size[pb] += sa;
        }
        else
        {
            par[pb] = pa;
            size[pa] += sb;
        }
    }
};

class Solution
{
public:
    int minimumHammingDistance(vector<int> &source, vector<int> &target, vector<vector<int>> &allowedSwaps)
    {

        int n = source.size();
        DSU dsu(n);

        for (auto &e : allowedSwaps)
        {
            dsu.duni(e[0], e[1]);
        }

        // Map: Component Root -> (Number -> Frequency)
        // This completely replaces the slow `multiset` with O(1) lookups
        unordered_map<int, unordered_map<int, int>> mp;

        // Populate the pools of available numbers
        for (int i = 0; i < n; ++i)
        {
            int pIdx = dsu.getPar(i);
            mp[pIdx][source[i]]++;
        }

        int hammingDist = 0;

        // Verify against the target
        for (int i = 0; i < n; ++i)
        {
            int pIdx = dsu.getPar(i);
            int required_num = target[i];

            if (mp[pIdx][required_num] > 0)
            {
                // Number exists in the pool, consume one
                mp[pIdx][required_num]--;
            }
            else
            {
                // Number does not exist or ran out, mandatory mismatch
                hammingDist++;
            }
        }

        return hammingDist;
    }
};

int main()
{

    return 0;
}