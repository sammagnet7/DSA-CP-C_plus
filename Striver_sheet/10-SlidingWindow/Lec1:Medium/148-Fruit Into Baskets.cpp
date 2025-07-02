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

1. Title: Fruit Into Baskets

Links:
https://www.youtube.com/watch?v=e3bs0uA1NhQ&list=PLgUwDviBIf0q7vrFA_HEWcqRqMpCXzYAL&index=6
https://takeuforward.org/plus/dsa/problems/fruit-into-baskets?tab=editorial
https://leetcode.com/problems/fruit-into-baskets/description/

Problem statement:
You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
Given the integer array fruits, return the maximum number of fruits you can pick.

 
Examples:
    Example 1:
    Input: fruits = [1,2,1]
    Output: 3
    Explanation: We can pick from all 3 trees.

    Example 2:
    Input: fruits = [0,1,2,2]
    Output: 3
    Explanation: We can pick from trees [1,2,2].
    If we had started at the first tree, we would only pick from trees [0,1].

    Example 3:
    Input: fruits = [1,2,3,2,2]
    Output: 4
    Explanation: We can pick from trees [2,3,2,2].
    If we had started at the first tree, we would only pick from trees [1,2].


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1.
//

class Solution
{
public:
    // 1. Title: Fruit Into Baskets
    //Approach1:


    // // SuboOptimal approach: two passes sliding window
    // // Time: O(2N)
    // // Space: O(1)
    // int totalFruit(vector<int> &fruits)
    // {

    //     int ans = 0;
    //     int N = fruits.size();

    //     unordered_map<int, int> mp; // O(2)

    //     int l = 0;
    //     int r = 0;

    //     while (r < N)
    //     {

    //         if (mp.find(fruits[r]) != mp.end())
    //         {
    //             mp[fruits[r]]++;
    //         }
    //         else
    //         {
    //             if (mp.size() < 2)
    //             {
    //                 mp[fruits[r]]++;
    //             }
    //             else
    //             {
    //                 while (mp.size() >= 2)
    //                 {
    //                     mp[fruits[l]]--;
    //                     if (mp[fruits[l]] == 0)
    //                     {
    //                         mp.erase(fruits[l]);
    //                     }
    //                     l++;
    //                 }
    //                 mp[fruits[r]]++;
    //             }
    //         }

    //         int count = r - l + 1;
    //         ans = max(ans, count);

    //         r++;
    //     }

    //     return ans;
    // }

    // Approach2:
    //

    // Optimal approach: One pass sliding window
    // Time: O(N)
    // Space: O(1)
    int totalFruit(vector<int> &fruits)
    {

        int ans = 0;
        int N = fruits.size();

        unordered_map<int, int> mp; // O(2)

        int l = 0;
        int r = 0;

        while (r < N)
        { // O(N)

            mp[fruits[r]]++;

            if (mp.size() > 2)
            {
                mp[fruits[l]]--;
                if (mp[fruits[l]] == 0)
                {
                    mp.erase(fruits[l]);
                }
                l++;
            }

            if (mp.size() <= 2)
            {
                int count = r - l + 1;
                ans = max(ans, count);
            }

            r++;
        }

        return ans;
    }
};

int main()
{
    return 0;
}
