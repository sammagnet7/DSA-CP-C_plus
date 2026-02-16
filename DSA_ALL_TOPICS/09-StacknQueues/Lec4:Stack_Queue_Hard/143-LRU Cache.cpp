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

1. Title: LRU Cache

Links:
https://takeuforward.org/data-structure/implement-lru-cache/
https://takeuforward.org/plus/dsa/problems/lru-cache?tab=editorial
https://leetcode.com/problems/lru-cache/description/


Problem statement:
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:
LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.


Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. LRU Cache
//
// O(1) ~ O(Log N) depends upon unordered_map's performance
// Time: O(1)
// Space: O(4N) where N=capacity
class LRUCache
{
public:
    list<pair<int, int>> lru;                              // stores key-value pair
                                                           // where back is recently used and front is least-recently-used
    unordered_map<int, list<pair<int, int>>::iterator> mp; // stores iterator at list w.r.t key
    int cap = 0;

    LRUCache(int capacity) : lru(list<pair<int, int>>()), mp(unordered_map<int, list<pair<int, int>>::iterator>())
    {
        cap = capacity;
    }

    // O(1)
    int get(int key)
    {
        if (mp.find(key) == mp.end())
        { // Key not exists in cache
            return -1;
        }
        else
        { // key exists
            auto it = mp[key];
            int val = it->second;

            // lru.erase(it);
            // lru.push_back({key,val});
            // mp[key] = --lru.end();
            lru.splice(lru.end(), lru, it); // Note: better approach
                                            // Re-places the node without deleting and creating new node

            return val;
        }
    }

    // O(1)
    void put(int key, int value)
    {

        if (mp.find(key) == mp.end())
        { // key not exists in cache

            if (mp.size() == cap)
            { // cache is full, delete least-recently-used
                int key = lru.front().first;
                lru.pop_front();
                mp.erase(key);
            }

            lru.push_back({key, value}); // push new entry
            mp[key] = --lru.end();       // save the iterator pointing to that entry in list
        }
        else
        { // key already exists
            auto it = mp[key];
            lru.erase(it); // remove current

            lru.push_back({key, value}); // update value
            mp[key] = --lru.end();       // update map with new iterator
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    return 0;
}
