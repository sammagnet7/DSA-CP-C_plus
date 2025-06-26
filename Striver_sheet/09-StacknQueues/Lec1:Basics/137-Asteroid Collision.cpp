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

using namespace std;

/*

1. Title: Asteroid Collision

Links:
https://www.youtube.com/watch?v=_eYGqw_VDR4&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=11
https://takeuforward.org/plus/dsa/problems/asteroid-collision?tab=editorial
https://leetcode.com/problems/asteroid-collision/


Problem statement:
We are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod in the array represent their relative position in space.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

Examples:
    Example 1:
    Input: asteroids = [5,10,-5]
    Output: [5,10]
    Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

    Example 2:
    Input: asteroids = [8,-8]
    Output: []
    Explanation: The 8 and -8 collide exploding each other.

    Example 3:
    Input: asteroids = [10,2,-5]
    Output: [10]
    Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

    Example 4: **
    Input: asteroids = [-2,-1,1,2]
    Output: [-2,-1,1,2]


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. Asteroid Collision

// O(1)
bool doCollide(int i, int j)
{
    if (i < 0)
        return false; // This is needed beacuse if left one is going left, then no chance of collison
    if (i > 0 && j > 0)
        return false;
    else if (i < 0 && j < 0)
        return false;
    else
        return true;
}

// Optimal approach: Uses stack
// Time: O(N)
// O(N)
vector<int> asteroidCollision(vector<int> &asteroids)
{

    int N = asteroids.size();
    vector<int> st; // O(N)

    for (int i = 0; i < N; i++)
    {

        if (asteroids[i] == 0)
            continue; // Just ignore 0s

        if (st.empty())
        { // if no prior left in stack, just push current
            st.push_back(asteroids[i]);
            continue;
        }

        else if (!doCollide(st.back(), asteroids[i]))
        { // if not opposit just push
            st.push_back(asteroids[i]);
            continue;
        }

        bool curExploded = false;

        while (!st.empty() && doCollide(st.back(), asteroids[i]))
        { // decide which asteroid stays

            if (abs(st.back()) < abs(asteroids[i]))
            {
                st.pop_back();
            }
            else if (abs(st.back()) == abs(asteroids[i]))
            {
                st.pop_back();
                curExploded = true;
                break;
            }
            else if (abs(st.back()) > abs(asteroids[i]))
            {
                curExploded = true;
                break;
            }
        }

        if (!curExploded)
        {
            st.push_back(asteroids[i]);
        }
    }

    return st;
}

int main()
{
    return 0;
}
