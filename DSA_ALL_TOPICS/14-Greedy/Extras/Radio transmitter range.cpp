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

1. Title: Hackerland Radio Transmitters

Links:
https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem




Problem statement:



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:


Problem statement:
In Hackerland, houses are built in a straight line, each at a specific location (an integer coordinate).
You need to place radio transmitters to cover all houses.

A transmitter placed at location x covers all houses whose positions are within the range:
    [x - k, x + k]
where k is the transmitter’s range.

Your task: Find the minimum number of transmitters needed to cover all houses.

Input
-----
- The first line: two integers
    n -> number of houses
    k -> range of each transmitter
- The second line: n space-separated integers, the house positions.

Output
------
- A single integer: the minimum number of transmitters needed.

Example
-------
Input:
5 1
1 2 3 4 5

Output:
2

Explanation:
- Place a transmitter at position 2 -> covers houses at 1, 2, 3.
- Place another at position 4 -> covers houses at 3, 4, 5.
- Minimum = 2 transmitters.



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title: Hackerland Radio Transmitters
    //-------------------------------------------------------------------------------

    /*
     * Approach:
     * ----------
     * Greedy placement of transmitters:
     * 1. Sort the house positions.
     * 2. Start from the leftmost uncovered house (index i).
     * 3. Move right (j) until the farthest house within distance k of x[i] →
     *    transmitter should be placed at house x[j-1].
     * 4. From x[j-1], move right (l) until all houses within k are covered.
     * 5. Next uncovered house becomes new i = l.
     * 6. Repeat until all houses are covered.
     *
     * Time Complexity: O(n log n)   (sorting + single scan)
     * Space Complexity: O(1)        (in-place, ignoring sort)
     */

    int hackerlandRadioTransmitters(vector<int> x, int k)
    {
        // Step 1: sort house positions
        sort(x.begin(), x.end());
        int n = x.size();
        int count = 0; // number of transmitters placed

        int i = 0; // current index of leftmost uncovered house

        while (i < n)
        {
            // Step 2: move j right until house j is out of range k from x[i]
            int j = i + 1;
            while (j < n && x[j] - x[i] <= k)
            {
                j++;
            }

            // Step 3: place a transmitter at the farthest valid house (x[j-1])
            count++;

            // Step 4: now move l right to cover all houses within k from x[j-1]
            int l = j;
            while (l < n && x[l] - x[j - 1] <= k)
            {
                l++;
            }

            // Step 5: all houses up to index l-1 are covered; continue from l
            i = l;
        }

        // Return the total number of transmitters placed
        return count;
    }

    //-------------------------------------------------------------------------------
    // 2. Title:
    //-------------------------------------------------------------------------------
};
 
int main()
{

    return 0;
}
