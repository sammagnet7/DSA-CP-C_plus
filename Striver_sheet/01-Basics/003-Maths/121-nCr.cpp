#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*
Calculating the value of nCr:

Naive Approach:

We can separately calculate n!, r!, (n-r)! and using their values we can calculate nCr. This is an extremely naive way to calculate. The time complexity will be O(n)+O(r)+O(n-r).

Optimal Approach
Algorithm / Intuition
We can optimize this calculation by the following observation.
Assume, given r = 7, c = 4.
Now, n = r-1 = 7-1 = 6 and r = c-1 = 4-1 = 3
Let’s calculate 6C3 = 6! / (3! *(6-3)!) = (6*5*4*3*2*1) / ((3*2*1)*(3*2*1))
This will boil down to (6*5*4) / (3*2*1)
So, nCr = (n*(n-1)*(n-2)*.....*(n-r+1)) / (r*(r-1)*(r-2)*....1)

Now, we will use this optimized formula to calculate the value of nCr. But while implementing this into code we will take the denominator in the forward direction like:

(n / 1)*((n-1) / 2)*.....*((n-r+1) / r).

INPUT::::::
2
5 3
10 4

OUTPUT::::::

10
210

 */

class Solution
{

public:
    // Approach:
    // nCr= [ n!/ ((n-r)!*r!) ] = [ (n*(n-1)*(n-2)*.....*(n-r+1)) / (r*(r-1)*(r-2)*....1) ]
    //    = (n / 1)*((n-1) / 2)*.....*((n-r+1) / r)
    // time: O(r)
    // Space: O(1)
    int calnCr(int n, int r)
    {
        int m = min(r, (n - r));
        r = m;

        long long result = 1;

        for (int i = 1; i <= r; i++)
        {
            result *= (n - i + 1); // This 2 step split is necessary
                                   // so that numerators gets divided properly
                                   // in both the cases of n being even or odd
            result /= i;
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
        int n, r;
        cin >> n >> r;

        Solution ob;

        cout << ob.calnCr(n, r);

        cout << endl; // Print a blank line between test cases
    }
    return 0;
}