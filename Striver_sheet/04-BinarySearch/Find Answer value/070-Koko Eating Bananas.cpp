#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Koko Eating Bananas

https://takeuforward.org/binary-search/koko-eating-bananas/
https://leetcode.com/problems/koko-eating-bananas/submissions/1623560881/

Problem statement:
A monkey is given ‘n’ piles of bananas, whereas the 'ith' pile has ‘a[i]’ bananas. An integer ‘h’ is also given, which denotes the time (in hours) for all the bananas to be eaten.
Each hour, the monkey chooses a non-empty pile of bananas and eats ‘k’ bananas. If the pile contains less than ‘k’ bananas, then the monkey consumes all the bananas and won’t eat any more bananas in that hour.
Find the minimum number of bananas ‘k’ to eat per hour so that the monkey can eat all the bananas within ‘h’ hours.

[   
    Similar kind of problem: Minimum days to make M bouquets
    https://takeuforward.org/arrays/minimum-days-to-make-m-bouquets/
    https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/
]

Examples:

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23


INPUT::::::
5
10
3 6 7 11
5
30 11 23 4 20
6
30 11 23 4 20
3
1000000000 1000000000
10
1 1 1 999999999



OUTPUT::::::
3
30
23
1000000000
142857143

 */
class Solution
{
public:
    // Optimal approach: Binary search
    // Time: O(N Log (max element))
    // Space: O(1)
    int minEatingSpeed(vector<int> &arr, int h)
    {

        int N = arr.size();
        int ans = INT_MAX;

        int maxE = *max_element(arr.begin(), arr.end());

        int l = 1;
        int r = maxE;

        while (l <= r)
        {

            int mid = l - (l - r) / 2;

            int hoursReq = 0;

            for (int i = 0; i < N; i++)
            {
                hoursReq += ceil((double)arr[i] / mid); // We must cast to double here,
                                                        // float also will not work also
                if (hoursReq > h)
                    break;
            }

            if (hoursReq <= h)
            { // here for case equals to also go left
                ans = min(ans, mid);
                r = mid - 1;
            }
            else if (hoursReq > h)
                l = mid + 1;
        }

        return ans;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        int n;
        cin >> n;
        cin.ignore();

        string input;
        getline(cin, input);

        vector<int> arr;
        stringstream ss(input);
        int num;

        while (ss >> num)
        {
            arr.push_back(num);
        }

        Solution ob;

        cout << ob.minEatingSpeed(arr, n);
        cout << endl;
    }
    return 0;
}