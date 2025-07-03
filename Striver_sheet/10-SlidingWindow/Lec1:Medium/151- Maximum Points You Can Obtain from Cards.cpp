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

1. Title: Maximum Points You Can Obtain from Cards

Links:
https://www.youtube.com/watch?v=pBWCOCS636U&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=2
https://takeuforward.org/plus/dsa/problems/maximum-points-you-can-obtain-from-cards-?tab=editorial
https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/


Problem statement:
There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.
In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
Your score is the sum of the points of the cards you have taken.
Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

Examples:
    Example 1:
    Input: cardPoints = [1,2,3,4,5,6,1], k = 3
    Output: 12
    Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

    Example 2:
    Input: cardPoints = [2,2,2], k = 2
    Output: 4
    Explanation: Regardless of which two cards you take, your score will always be 4.

    Example 3:
    Input: cardPoints = [9,7,7,9,7,7,9], k = 7
    Output: 55
    Explanation: You have to take all the cards. Your score is the sum of points of all cards.



INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
    //------------------------------------------------------------------------
    //  1. Title: Maximum Points You Can Obtain from Cards
    //
    //  Approach1:

    // // Sub-optimal solution: Using prefix-sum
    // //
    // // Time: O(2N)
    // // Space: O(1)
    // int maxScore(vector<int>& cardPoints, int k) {

    //     int N = cardPoints.size();
    //     int remSubArrSize = N-k;
    //     long long total = 0;

    //     for(int i:cardPoints){  // O(N)
    //         total += i;
    //     }

    //     int l = 0;
    //     int r = 0;

    //     long long windowTot = 0;

    //     while(r<=(l+remSubArrSize-1)){ //O(K)
    //         windowTot += cardPoints[r];
    //         r++;
    //     }

    //     long long score = total-windowTot;
    //     long long maxScore = score;

    //     while(r<N){ // O(N-k)
    //         windowTot -= cardPoints[l];
    //         windowTot += cardPoints[r];

    //         score = total-windowTot;
    //         maxScore = max(maxScore,score);

    //         l++;
    //         r++;
    //     }

    //     return maxScore;
    // }

    // ----------------------------------------
    // Approach2:
    //

    // optimal solution
    //
    // Time: O(2K)
    // Space: O(1)
    int maxScore(vector<int> &cardPoints, int k)
    {

        int N = cardPoints.size();

        int score = 0;
        int maxScore = 0;

        for (int i = 0; i < k; i++)
        { // O(k)
            score += cardPoints[i];
        }

        maxScore = score;

        for (int i = k - 1, j = N - 1; i >= 0; i--, j--)
        { // O(k)
            score -= cardPoints[i];
            score += cardPoints[j];

            maxScore = max(maxScore, score);
        }

        return maxScore;
    }
};

int main()
{
    return 0;
}
