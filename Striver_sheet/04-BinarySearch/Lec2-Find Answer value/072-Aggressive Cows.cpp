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
Aggressive Cows

https://takeuforward.org/data-structure/aggressive-cows-detailed-solution/
https://www.naukri.com/code360/problems/aggressive-cows_1082559?leftPanelTabValue=PROBLEM


Problem statement:
You are given an array 'arr' of size 'n' which denotes the position of stalls.
You are also given an integer 'target' which denotes the number of aggressive cows.
You are given the task of assigning stalls to 'target' cows such that the minimum distance between any two of them is the maximum possible.
Find the maximum possible minimum distance.


Examples:

Example 1:
Input Format: N = 6, target = 4, arr[] = {0,3,4,7,10,9}
Result: 3
Explanation: The maximum possible minimum distance between any two cows will be 3 when 4 cows are placed at positions {0, 3, 7, 10}. Here the distances between cows are 3, 4, and 3 respectively. We cannot make the minimum distance greater than 3 in any ways.

Example 2:
Input Format: N = 5, target = 2, arr[] = {4,2,1,3,6}
Result: 5
Explanation: The maximum possible minimum distance between any two cows will be 5 when 2 cows are placed at positions {1, 6}.


INPUT::::::
5
4
0 3 4 7 10 9
2
4 2 1 3 6
4
18 27 44 77 69 19 35 83 9 64
2
1 2 3
4
87 93 51 81 68 99 59


OUTPUT::::::
3
5
19
2
13


 */
class Solution
{
public:
    // Optimal approach: Binary search
    // First sort the given array
    // Then min distance possible: 1
    // Max distance possible: (arr[N-1]-arr[0])
    // So, ans can lie between min to max distance with which target cows can be placed
    // For this we use Binary search
    // Time: O(N Log N) + O(N Log(MaxOfArr-MinOfArr))
    // Space: O(1)
    int aggressiveCows(vector<int> &arr, int target)
    {
        int N = arr.size();
        int ans = INT_MIN; // Max possible minimum distance
        sort(arr.begin(), arr.end());

        int l = 1;                   // Min distance possible
        int r = arr[N - 1] - arr[0]; // Max distance possible

        while (l <= r)
        {

            int mid_dis = l - (l - r) / 2;

            int prevPos = arr[0]; // First cow always be placed at the starting stall
            int cow_count = 1;    // First cow always be counted

            for (int i = 1; i < N; i++)
            {
                int curPos = arr[i];

                if (curPos - prevPos >= mid_dis)
                { // Only place a cow when dist is satisfied
                    cow_count++;
                    prevPos = curPos;
                }

                if (cow_count > target)
                    break;
            }

            if (cow_count >= target)
            { // when more cows have been place than target try to
              // increase the distance by going right
              // And also note the distance as a possible ans
                ans = max(ans, mid_dis);
                l = mid_dis + 1;
            }
            else if (cow_count < target)
            { // else go left to see with lesser distance
              // can it be possible to place all the cows
                r = mid_dis - 1;
            }
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

        cout << ob.aggressiveCows(arr, n);
        cout << endl;
    }
    return 0;
}