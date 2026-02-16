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

1. Title: LFU Cache

Links:
https://www.youtube.com/watch?v=0PSB9y8ehbk&t=1s
https://takeuforward.org/plus/dsa/problems/lfu-cache?tab=editorial
https://leetcode.com/problems/lfu-cache/description/


Problem statement:
Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:
LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.
The functions get and put must each run in O(1) average time complexity.

Example 1:
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. LFU Cache
//

//
//
// Note: Here we can maintain least frequency with a varibale `leastFreq` in O(1) as if least freq changes, it will change max by 1 unit. if there is `delete` op, then it could take O(N) for searching the next lower freq, so this approach would not work then.
// Also note: for lru_list most-recenet is pushed at back and least-recent is at front.
//
//
class LFUCache
{
public:
    unordered_map<int, list<pair<int, int>>> lfu;                     // < frq_lv, lru_list <(key,val)> >
    unordered_map<int, pair<int, list<pair<int, int>>::iterator>> mp; // < key, (frq_lv, list-iterator pointing to val) >

    int cap;
    int leastFreq;

    LFUCache(int capacity)
    {
        cap = capacity;
        leastFreq = capacity;
    }

    int get(int key)
    {

        if (mp.find(key) == mp.end())
        { // key does not exists
            return -1;
        }
        else
        { // key exists

            int frq_lv = mp[key].first;
            auto it = mp[key].second;
            int val = it->second;

            lfu[frq_lv].erase(it); // remove old entry

            if ((leastFreq == frq_lv) && (lfu[frq_lv].empty()))
            { // if cur one is of least frequency and after removal none are present in that least frequency, that means least frequency need to be updated
                leastFreq = (frq_lv + 1);
            }

            frq_lv++;
            lfu[frq_lv].push_back({key, val});
            it = --(lfu[frq_lv].end());
            mp[key] = {frq_lv, it};

            return val;
        }
    }

    void put(int key, int value)
    {

        if (mp.find(key) == mp.end())
        { // key does not exists

            if (mp.size() == cap)
            { // cache full. Evict LFU
                int old_key = lfu[leastFreq].front().first;
                lfu[leastFreq].pop_front();
                mp.erase(old_key);
            }

            lfu[1].push_back({key, value});
            auto it = --(lfu[1].end());
            mp[key] = {1, it};
            leastFreq = 1;
        }
        else
        { // key exists

            int frq_lv = mp[key].first;
            auto it = mp[key].second;

            lfu[frq_lv].erase(it); // remove old entry

            if ((leastFreq == frq_lv) && (lfu[frq_lv].empty()))
            { // if cur one is of least frequency and after removal none are present in that least frequency, that means least frequency need to be updated
                leastFreq = (frq_lv + 1);
            }

            frq_lv++;
            lfu[frq_lv].push_back({key, value});
            it = --(lfu[frq_lv].end());
            mp[key] = {frq_lv, it};
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    return 0;
}
