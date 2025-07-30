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
1. Title: Minimum Number of Platforms

Links:
https://takeuforward.org/data-structure/minimum-number-of-platforms-required-for-a-railway/
https://takeuforward.org/plus/dsa/problems/minimum-number-of-platforms-required-for-a-railway?tab=editorial
https://www.naukri.com/code360/problems/minimum-number-of-platforms_799400?leftPanelTabValue=PROBLEM


Problem statement:
You have been given two arrays, 'AT' and 'DT', representing the arrival and departure times of all trains that reach a railway station.
Your task is to find the minimum number of platforms required for the railway station so that no train needs to wait.
Note :
  1. Every train will depart on the same day and the departure time will always be greater than the arrival time. For example, A train with arrival time 2240 and departure time 1930 is not possible.
  2. Time will be given in 24H format and colons will be omitted for convenience. For example, 9:05AM will be given as "905", or 9:10PM will be given as "2110".
  3. Also, there will be no leading zeroes in the given times. For example, 12:10AM will be given as “10” and not as “0010”.

Examples:
  Sample Input 1:
  2
  6
  900 940 950 1100 1500 1800
  910 1200 1120 1130 1900 2000
  4
  100 200 300 400
  200 300 400 500
  Sample Output 1:
  3
  2
  Explanation of the Sample Output 1:
  In test case 1, For the given input, the following will be the schedule of the trains:

  Train 1 arrived at 900 on platform 1.
  Train 1 departed at 910 from platform 1.
  Train 2 arrived at 940 on platform 1.
  Train 3 arrived at 950 on platform 2 (since platform 1 was already occupied by train 1).
  Train 4 arrived at 1100 on platform 3 (since both platforms 1 and 2 were occupied by trains 2 and 3 respectively).
  Train 3 departed at 1120 from platform 2 (platform 2 becomes vacant).
  Train 4 departed at 1130 from platform 3 (platform 3 also becomes vacant).
  Train 2 departed at 1200 from platform 1 (platform 1 also becomes vacant).
  Train 5 arrived at 1500 on platform 1.
  Train 6 arrived at 1800 on platform 2.
  Train 5 departed at 1900 from platform 1.
  Train 6 departed at 2000 from platform 2.

  Thus, minimum 3 platforms are needed for the given input.

  In test case 2, For the given input, the following will be the schedule of the trains:

  Train 1 arrived at 100 on platform 1.
  Train 2 arrived at 200 from platform 2 (as platform 1 is occupied by train 1).
  Train 1 departed at 200 from platform 1.
  Train 3 arrived at 300 on platform 1.
  Train 2 departed at 300 from platform 2.
  Train 4 arrived at 400 on platform 2.
  Train 3 departed at 400 from platform 1.
  Train 4 departed at 500 from platform 2.

  Thus, 2 platforms are needed for the given input.
  Sample Input 2:
  2
  2
  900 1000
  999 1100
  3
  1200 1300 1450
  1310 1440 1600
  Sample Output 2:
  1
  2
  Explanation of the Sample Output 2:
  In test case 1, For the given input, the following will be the schedule of the trains:

  Train 1 arrived at 900 on platform 1.
  Train 1 departed at 999 from platform 1.
  Train 2 arrived at 1000 on platform 1.
  Train 2 arrived at 1100 on platform 1.

  Thus, only 1 platform is needed for the given input.

  In test case 2, For the given input, the following will be the schedule of the trains:

  Train 1 arrived at 1200 on platform 1.
  Train 2 arrived at 1300 on platform 2. (since platform 1 was already occupied by train 1).
  Train 1 departed at 1310 from platform 1.
  Train 2 departed at 1440 from platform 2.
  Train 3 arrived at 1450 on platform 1.
  Train 3 departed at 1600 on platform 1.

  Thus, minimum 2 platforms are needed for the given input.


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title:

Links:

Problem statement:


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Minimum Number of Platforms
  //-------------------------------------------------------------------------------

  /*
    Approach: Event Timeline Sorting

    Intuition:
    - Treat arrival and departure times as events.
    - Mark each event with a label: 'a' for arrival, 'd' for departure.
    - Sort all events based on time (arrivals before departures if time is equal).
    - Traverse the timeline:
        - Increment count on 'a' (arrival).
        - Decrement count on 'd' (departure).
        - Keep track of the maximum count encountered ? this is the number of platforms needed.

    Time Complexity: O(n log n) for sorting the 2n events.
    Space Complexity: O(n) for storing the combined event list.
*/

  // int calculateMinPatforms(int at[], int dt[], int n) {
  //     vector<pair<int, char>> at_dt;

  //     // Push both arrival and departure events with markers
  //     for (int i = 0; i < n; i++) {
  //         at_dt.push_back({at[i], 'a'});
  //         at_dt.push_back({dt[i], 'd'});
  //     }

  //     // Sort all events: time ascending, with 'a' before 'd' on ties
  //     sort(at_dt.begin(), at_dt.end());

  //     int aCount = 0;  // Number of trains currently at the station
  //     int ans = 0;     // Max platforms needed at any time

  //     // Traverse the sorted event list
  //     for (auto el : at_dt) {
  //         char type = el.second;

  //         if (type == 'a') {
  //             aCount++;  // One more train has arrived
  //         } else {
  //             aCount--;  // One train has departed
  //         }

  //         ans = max(ans, aCount);  // Update max platforms required
  //     }

  //     return ans;
  // }

  //
  // Approach 2
  //

  /*
      Approach: Two Pointer (Greedy)

      Intuition:
      - Sort both arrival and departure times.
      - Use two pointers:
          - `aI` for arrival index
          - `dI` for departure index
      - Traverse arrival times:
          - If next train arrives before or at the same time as the current one departs,
            increment platform count.
          - Else, train has departed, decrement platform count.
      - Keep track of max platforms required during traversal.

      Time Complexity: O(n log n) ? sorting the arrival and departure arrays.
      Space Complexity: O(1) ? constant space used, no extra structures.
  */

  int calculateMinPatforms(int at[], int dt[], int n)
  {
    sort(at, at + n); // Sort arrival times
    sort(dt, dt + n); // Sort departure times

    int aI = 0;       // Pointer for arrival
    int dI = 0;       // Pointer for departure
    int arrCount = 0; // Current number of platforms occupied
    int ans = 0;      // Max platforms needed

    while (aI < n)
    {
      if (at[aI] <= dt[dI])
      {
        arrCount++; // New train arrived before earliest departure
        aI++;
      }
      else
      {
        arrCount--; // A train departed
        dI++;
      }

      ans = max(ans, arrCount); // Update max platforms if needed
    }

    return ans;
  }
};

int main()
{
  return 0;
}
