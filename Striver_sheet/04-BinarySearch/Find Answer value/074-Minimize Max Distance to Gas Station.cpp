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

using namespace std;

/*
Minimise Maximum Distance between Gas Stations

https://takeuforward.org/arrays/minimise-maximum-distance-between-gas-stations/
https://www.naukri.com/code360/problems/minimise-max-distance_7541449?leftPanelTabValue=PROBLEM


Problem statement:
You are given a sorted array ‘arr’ of length ‘n’, which contains positive integer positions of ‘n’ gas stations on the X-axis. You are also given an integer ‘k’. You have to place 'k' new gas stations on the X-axis. You can place them anywhere on the non-negative side of the X-axis, even on non-integer positions. Let 'dist' be the maximum value of the distance between adjacent gas stations after adding k new gas stations.
Find the minimum value of ‘dist’.

Note: Answers within 10^-6 of the actual answer will be accepted. For example, if the actual answer is 0.65421678124, it is okay to return 0.654216. Our answer will be accepted if that is the same as the actual answer up to the 6th decimal place.


Examples:

Example 1:
Input Format: N = 5, arr[] = {1,2,3,4,5}, k = 4
Result: 0.5
Explanation: One of the possible ways to place 4 gas stations is {1,1.5,2,2.5,3,3.5,4,4.5,5}. Thus the maximum difference between adjacent gas stations is 0.5. Hence, the value of ‘dist’ is 0.5. It can be shown that there is no possible way to add 4 gas stations in such a way that the value of ‘dist’ is lower than this.
Example 2:
Input Format: N = 10, arr[] = {1,2,3,4,5,6,7,8,9,10}, k = 1
Result: 1
Explanation: One of the possible ways to place 1 gas station is {1,1.5,2,3,4,5,6,7,8,9,10}. Thus the maximum difference between adjacent gas stations is still 1. Hence, the value of ‘dist’ is 1. It can be shown that there is no possible way to add 1 gas station in such a way that the value of ‘dist’ is lower than this.



INPUT::::::
5
4
1 2 3 4 5
1
1 2 3 4 5 6 7 8 9 10
1
1 4 6 10 11
1
1 2 3 4 5 6 7 8 9 10
1
2 4 6 8 10 

OUTPUT::::::
0.5
1
3
1
2

 */
class Solution
{
public:
    // // Brute force: Array traversal
    // // Time: O(N*K) + O(k)
    // // Space: O(N)
    // double minimiseMaxDistance(vector<int> &arr, int k)
    // {
    //     int N = arr.size();

    //     vector<int> addedCount(N - 1, 0);

    //     for (int x = 0; x < k; x++)
    //     { // Number of new gas stations i.e. k times

    //         double maxDist = INT_MIN;
    //         int maxDistIdx = -1;

    //         for (int i = 0; i < N - 1; i++)
    //         { // existing N gas stations
    //             int sectionalDist = arr[i + 1] - arr[i];
    //             double minSectionalDist = (double)sectionalDist / (addedCount[i] + 1);

    //             if (minSectionalDist > maxDist)
    //             {
    //                 maxDist = minSectionalDist;
    //                 maxDistIdx = i;
    //             }
    //         }

    //         addedCount[maxDistIdx]++;
    //     }

    //     double ans = INT_MIN;
    //     for (int i = 0; i < N - 1; i++)
    //     {
    //         int sectionalDist = arr[i + 1] - arr[i];
    //         double minSectionalDist = (double)sectionalDist / (addedCount[i] + 1);

    //         ans = max(ans, minSectionalDist);
    //     }

    //     return ans;
    // }

    // // Better approach: Using Priority queue as Max heap
    // // Time: O(N Log N) + O(K Log N)
    // // Space: O(2N)
    // double minimiseMaxDistance(vector<int> &arr, int k)
    // {
    //     int N = arr.size();

    //     vector<int> addedPostCount(N - 1, 0);
    //     priority_queue<pair<double, int>> maxSecDistIdx; // Section wise max distance and index pair

    //     // Creating max heap
    //     for (int i = 0; i < N - 1; i++)
    //     {                                                   // O(N)
    //         maxSecDistIdx.push({(arr[i + 1] - arr[i]), i}); // O(Log N)
    //     }

    //     for (int p = 0; p < k; p++)
    //     { // Number of new gas stations i.e. k times

    //         auto distIdxPair = maxSecDistIdx.top(); // Get cuurent max dist in O(1)
    //         maxSecDistIdx.pop();

    //         int idx = distIdxPair.second;

    //         addedPostCount[idx]++;

    //         double currDist = (double)(arr[idx + 1] - arr[idx]) / (addedPostCount[idx] + 1);

    //         maxSecDistIdx.push({currDist, idx}); // O(Log N)
    //     }

    //     return maxSecDistIdx.top().first;
    // }


    // Optimal approach: Using Binary search
    // Go to the half side with minimum distance possible with available number of gas stations
    // Note: As dist is measured in 10^-6 range
    // do r=mid and l=mid instead of r-mid-1 and l=mid+1
    // Also check condition (l-r<1e-6)
    // Time: O(Log N)
    // Space: O(1)
    double minimiseMaxDistance(vector<int> &arr, int k)
    {

        int N = arr.size();

        double ans = -1; // Test cases are failing while maintaining ans var

        double maxDist = INT_MIN;

        // O(N)
        for (int i = 0; i < N - 1; i++)
        {
            maxDist = max(maxDist, (double)(arr[i + 1] - arr[i]));
        }

        double l = 0.0;
        double r = maxDist;

        double diff = 1e-6 ;

        // O(Log N)
        while (r - l > diff)
        { // within 10^-6

            double mid = (l + r) / 2.0;
            int availableStations = k;

            // O(N)
            for (int i = 0; i < N - 1; i++)
            {
                double sectionDist = arr[i + 1] - arr[i];

                int stationsNeeded = ceil(sectionDist / mid) - 1;
                availableStations -= stationsNeeded;
            }

            if (availableStations >= 0)
            { // i.e. less required than avaialbe
                ans = mid;
                r = mid;
            }
            else // i.e. more required than avaialbe
                l = mid;
                
        }

        //return r; // Must return r instead of answer to pass test cases 2 and 5 here
        return ans==-1?r:ans; // Or do this to handle the cases where given array's max dist is already the min dist
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

        cout << ob.minimiseMaxDistance(arr, n);
        cout << endl;
    }
    return 0;
}