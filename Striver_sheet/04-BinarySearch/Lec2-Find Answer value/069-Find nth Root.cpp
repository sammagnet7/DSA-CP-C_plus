#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*
Nth Root of a Number using Binary Search

https://takeuforward.org/data-structure/nth-root-of-a-number-using-binary-search/
https://www.naukri.com/code360/problems/nth-root-of-m_1062679?leftPanelTabValue=PROBLEM

Problem statement:
You are given two positive integers 'n' and 'm'. You have to return the 'nth' root of 'm', i.e. 'm(1/n)'. If the 'nth root is not an integer, return -1.

Expected Time Complexity:
Try to do this in O(log(n+m)).

Examples:
Sample Input 1:
3 27
Sample Output 1:
3
Explanation For Sample Input 1:
3rd Root of 27 is 3, as (3)^3 equals 27.

Sample Input 2:
4 69
Sample Output 2:
-1
Explanation For Sample Input 2:
4th Root of 69 is not an integer, hence -1.

INPUT::::::
3
3 27
4 69
9 1953125

OUTPUT::::::
3
-1
5


 */
class Solution
{
public:
    // long long XtoThePowerN(long long X, int N, int threshold){
    //     long long mulV= 1;
    //     while(N--){
    //         mulV *= X;
    //         if(mulV > threshold) return mulV;   // This is very imporatn step
    //                                         // where we check the multiplication bound
    //                                         // and return before overflow
    //     }
    //     return mulV;
    // }

    // Optimal approach for getting power of N
    // Time: T(Log N)
    // Space: O(1)
    long long XtoThePowerN(long long X, int N, long long threshold)
    {

        long long mulV = 1;
        long long baseV = X;

        while (N > 0)
        {
            if (N % 2 == 0)
            { // even
                N /= 2;
                baseV = (baseV * baseV);
            }
            else
            { // odd
                N--;
                mulV = baseV * mulV;
            }

            if (baseV > threshold || mulV > threshold) // This is very imporatn step
                                                       // where we check the multiplication bound
                                                       // and return before overflow
                return INT_MAX;
        }

        return mulV;
    }

    // Optimal approach: uses Binary search
    // time: O(Log N)
    // Space: O(1)
    int NthRoot(int N, int M)
    {
        // Write your code here.

        int l = 1, r = M;
        int ans = -1;

        while (l <= r)
        {
            int mid = l - (l - r) / 2;

            long long mulV = XtoThePowerN(mid, N, M);

            if (mulV == M)
                return mid;
            else if (mulV < M)
                l = mid + 1;
            else if (M < mulV)
                r = mid - 1;
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
        int n, m;
        cin >> n;
        cin.ignore();
        cin >> m;

        // string input;
        // getline(cin, input);

        // vector<int> arr;
        // stringstream ss(input);
        // int num;

        // while (ss >> num)
        // {
        //     arr.push_back(num);
        // }

        Solution ob;

        cout << ob.NthRoot(n, m);
        cout << endl;
    }
    return 0;
}