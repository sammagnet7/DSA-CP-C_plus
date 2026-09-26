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
    // ==========================================
    // Approach 1: Standard Sliding Window (Valid Window Focus)
    // ==========================================
    // Logic:
    // 1. Expand the 'right' pointer to include a new fruit.
    // 2. If the map size exceeds 2 (invalid window), enter a WHILE loop.
    // 3. Shrink from the 'left' strictly until the window becomes valid again.
    // 4. Update the answer with the size of the valid window.
    //
    // Pros:
    // - Intuitive and easy to understand (Standard template).
    // - Guarantees that at every step, the window [l, r] is valid.
    //
    // Cons:
    // - Technically touches elements twice (once by 'r', once by 'l'), making it 2*N operations in worst case.
    //
    // Time Complexity: O(2N) -> O(N)
    // - Each element is added once and removed once.
    // Space Complexity: O(1)
    // - Map contains at most 3 elements.
    int totalFruit_Standard(vector<int> &fruits)
    {
        int ans = 0;
        int N = fruits.size();

        unordered_map<int, int> mp; // Stores frequency of fruits in current window

        int l = 0;
        int r = 0;

        while (r < N)
        {
            // Add current fruit to the map
            mp[fruits[r]]++;

            // If we have more than 2 distinct fruits, the window is invalid.
            // We MUST shrink until it becomes valid (size <= 2)
            while (mp.size() > 2)
            {
                mp[fruits[l]]--;
                if (mp[fruits[l]] == 0)
                {
                    mp.erase(fruits[l]);
                }
                l++; // Move left pointer
            }

            // At this point, the window [l, r] is guaranteed valid.
            int count = r - l + 1;
            ans = max(ans, count);

            r++;
        }

        return ans;
    }

    // ==========================================
    // Approach 2: Optimized "Non-Shrinking" Sliding Window
    // ==========================================
    // Logic:
    // 1. Similar to above, expand 'right'.
    // 2. If the map size exceeds 2, we do NOT loop to make it valid.
    // 3. Instead, we shift 'left' ONLY ONCE.
    //    - Why? We only care about finding the *longest* window.
    //    - If we had a valid window of size K, and now we have an invalid window of size K+1,
    //      shifting 'l' once keeps the window size at K.
    //    - We don't need to shrink to a smaller valid size (e.g., K-5) because we've already found a size K.
    //    - We essentially "drag" the max-sized window across the array until it can grow again.
    //
    // Pros:
    // - Slightly faster in practice as it avoids the inner while loop.
    //
    // Cons:
    // - Logic is less intuitive (at intermediate steps, the window might be invalid).
    //
    // Time Complexity: O(N)
    // - 'l' and 'r' only move forward, max N steps each.
    // Space Complexity: O(1)
    int totalFruit_Optimized(vector<int> &fruits)
    {
        int ans = 0;
        int N = fruits.size();

        unordered_map<int, int> mp;

        int l = 0;
        int r = 0;

        while (r < N)
        {
            mp[fruits[r]]++;

            // If invalid, just shift 'l' once.
            // We don't loop. This maintains the window size but shifts it right.
            if (mp.size() > 2)
            {
                mp[fruits[l]]--;
                if (mp[fruits[l]] == 0)
                {
                    mp.erase(fruits[l]);
                }
                l++;
            }

            // If the window became valid (or stayed valid), update answer.
            // Note: If mp.size() > 2 after the single shift, we basically
            // maintain the previous 'ans' without updating it.
            if (mp.size() <= 2)
            {
                int count = r - l + 1;
                ans = max(ans, count);
            }

            r++;
        }

        return ans;
    }

    // ==========================================
    // Approach 3: "Jump" Optimization (Last Occurrence Index)
    // ==========================================
    // Logic:
    // 1. Instead of storing Frequency, store the 'Last Index' where a fruit appeared.
    // 2. When we encounter a 3rd distinct fruit:
    //    - We need to remove one fruit type completely to make space.
    //    - Which one? The one that "ended" the earliest (Min Last Index).
    //    - Why? Removing the fruit that persists longest would require shrinking the window more.
    // 3. Set new 'start' to (Min Last Index + 1). This "Jumps" the left pointer over many elements at once.
    //
    // Pros:
    // - Skips redundant checks by jumping 'l' directly to the valid position.
    //
    // Cons:
    // - Requires iterating the map to find the minimum index (though map size is small constant here, 3).
    //
    // Time Complexity: O(N)
    // Space Complexity: O(1)
    int totalFruit_Jump(vector<int> &fruits)
    {
        int N = fruits.size();
        int winStartIdx = 0;
        int maxFruits = 0;

        // Map stores: <Fruit Type, Index of its most recent occurrence>
        unordered_map<int, int> mp;

        for (int i = 0; i < N; i++)
        {
            // Update the last seen position of current fruit
            mp[fruits[i]] = i;

            // If we have 3 types, we must evict one type completely
            if (mp.size() > 2)
            {
                int leastRecentIdx = N;
                int fruitToRemove = -1;

                // Iterate map (only size 3) to find the fruit type that ended earliest
                for (auto it = mp.begin(); it != mp.end(); it++)
                {
                    if (it->second < leastRecentIdx)
                    {
                        leastRecentIdx = it->second;
                        fruitToRemove = it->first;
                    }
                }

                // Remove that fruit type
                mp.erase(fruitToRemove);

                // JUMP the window start:
                // Everything before and including 'leastRecentIdx' is now cut off
                winStartIdx = leastRecentIdx + 1;
            }

            // Update max length
            maxFruits = max(maxFruits, (i - winStartIdx + 1));
        }

        return maxFruits;
    }
};

int main()
{
    return 0;
}
