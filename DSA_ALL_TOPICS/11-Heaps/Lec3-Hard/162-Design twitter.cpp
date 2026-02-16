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

1. Title: Design Twitter

Links:
https://leetcode.com/problems/design-twitter/description/
https://www.naukri.com/code360/library/design-twitter-2236  (But not optimal)


Problem statement:
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.

Implement the Twitter class:
Twitter() Initializes your twitter object.
void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId. Each call to this function will be made with a unique tweetId.
List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId.


Example:
  Input
  ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
  [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
  Output
  [null, null, [5], null, null, [6, 5], null, [5]]

  Explanation
  Twitter twitter = new Twitter();
  twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
  twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
  twitter.follow(1, 2);    // User 1 follows user 2.
  twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
  twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
  twitter.unfollow(1, 2);  // User 1 unfollows user 2.
  twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.


Constraints:
  1 <= userId, followerId, followeeId <= 500
  0 <= tweetId <= 104
  All the tweets have unique IDs.
  At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
  A user cannot follow himself.


INPUT::::::


OUTPUT::::::


*/

class Solution
{
public:
  //-------------------------------------------------------------------------------
  // 1. Title: Design twitter :: OOPs approach
  //-------------------------------------------------------------------------------

  // -------------------------------------------------------------
  // Approach1: Getting erong answer for some test cases as previously posted tweets before following I am not fetching but fully OOPs followed
  //

  // template <typename T>
  // class FixedSizedDQ
  // {
  // private:
  //   deque<T> dq;
  //   int maxSize;

  // public:
  //   FixedSizedDQ(int size)
  //   {
  //     maxSize = size;
  //   }

  //   void push_back(T val)
  //   { // O(1)
  //     if (dq.size() == maxSize)
  //     {
  //       dq.pop_front();
  //     }
  //     dq.push_back(val);
  //   }

  //   bool empty()
  //   { // O(1)
  //     return dq.empty();
  //   }

  //   int size()
  //   { // O(1)
  //     return dq.size();
  //   }

  //   deque<T> &getAll()
  //   {
  //     return dq;
  //   }
  // };

  // class User
  // {
  // private:
  //   int userId;
  //   FixedSizedDQ<pair<int, int>> top10; // pair{followeeId, tweetId}
  //   set<int> followers;                 // <followers-ids>

  //   vector<int> getTop10Tweets()
  //   { // O(10)
  //     deque<pair<int, int>> &dq = top10.getAll();
  //     vector<int> v;
  //     for (auto it = dq.rbegin(); it != dq.rend(); it++)
  //     {
  //       v.push_back(it->second);
  //     }
  //     return v;
  //   }

  //   void removeFromTop10(int followeeId)
  //   { // O(10)
  //     deque<pair<int, int>> &dq = top10.getAll();
  //     for (auto it = dq.begin(); it != dq.end();)
  //     {
  //       if (it->first == followeeId)
  //       {
  //         it = dq.erase(it);
  //       }
  //       else
  //       {
  //         it++;
  //       }
  //     }
  //   }

  // public:
  //   User(int uId) : top10(10)
  //   {
  //     userId = uId;
  //   }

  //   FixedSizedDQ<pair<int, int>> &getTop10Ref()
  //   {
  //     return top10;
  //   }

  //   void postMyTweet(int tweetId, unordered_map<int, User *> userDB)
  //   { // O(#followers)

  //     this->top10.push_back({userId, tweetId}); // Add tweet to own top10

  //     for (auto it = followers.begin(); it != followers.end(); ++it)
  //     {                                 // O(#followers): add tweet to all followers' top10
  //       User *follower = userDB[(*it)]; // Check
  //       follower->getTop10Ref().push_back({userId, tweetId});
  //     }
  //   }

  //   vector<int> getMyNewsFeed()
  //   { // O(10)
  //     return getTop10Tweets();
  //   }

  //   void followMe(int followerId)
  //   { // O(1)
  //     followers.insert(followerId);
  //   }

  //   void unfollowMe(int followerId)
  //   { // O(#followers)
  //     followers.erase(followerId);
  //   }

  //   void removeTweetsFromMe(int followeeId)
  //   { // O(10)
  //     removeFromTop10(followeeId);
  //   }
  // };

  // //------------------------------------------------------

  // class Twitter
  // {
  // private:
  //   unordered_map<int, User *> userDB; // Note: userId, using object pointer in map

  // public:
  //   Twitter()
  //   {
  //   }

  //   void postTweet(int userId, int tweetId)
  //   {

  //     if (userDB.find(userId) == userDB.end())
  //     { // when not found
  //       User *newU = new User(userId);
  //       userDB[userId] = newU; // Note: assigning ref
  //     }

  //     userDB[userId]->postMyTweet(tweetId, userDB);
  //   }

  //   vector<int> getNewsFeed(int userId)
  //   {
  //     if (userDB.find(userId) == userDB.end())
  //     { // when not found
  //       return vector<int>();
  //     }
  //     else
  //     {
  //       return userDB[userId]->getMyNewsFeed();
  //     }
  //   }

  //   void follow(int followerId, int followeeId)
  //   {
  //     // Create follower if not exists
  //     if (userDB.find(followerId) == userDB.end())
  //     {
  //       userDB[followerId] = new User(followerId);
  //     }

  //     // Create followee if not exists
  //     if (userDB.find(followeeId) == userDB.end())
  //     {
  //       userDB[followeeId] = new User(followeeId);
  //     }

  //     userDB[followeeId]->followMe(followerId);
  //   }

  //   void unfollow(int followerId, int followeeId)
  //   {
  //     if ((userDB.find(followerId) == userDB.end()) || (userDB.find(followeeId) == userDB.end()))
  //       return;
  //     else
  //     {
  //       userDB[followeeId]->unfollowMe(followerId);
  //       userDB[followerId]->removeTweetsFromMe(followeeId);
  //     }
  //   }
  // };

  //-------------------------------------------------------------------------------
  // 2. Title: Design twitter :: Solution for DSA
  //-------------------------------------------------------------------------------

  // -------------------------------------------------------------
  // Approach2: Using simple logic but still getting TLE
  //

  // class Twitter
  // {
  // public:
  //   vector<pair<int, int>> tweets;                    // <userid-tweetid> list
  //   unordered_map<int, unordered_set<int>> following; // <follower, <list-of-followees>>

  //   Twitter()
  //   {
  //     tweets.clear();
  //     following.clear();
  //   }

  //   void postTweet(int userId, int tweetId)
  //   {
  //     tweets.push_back({userId, tweetId});
  //   }

  //   vector<int> getNewsFeed(int userId)
  //   {
  //     vector<int> top10;

  //     for (auto it = tweets.rbegin(); it != tweets.rend() && top10.size() < 10; it++)
  //     {

  //       int tweetUId = it->first;
  //       int tweetId = it->second;

  //       if (tweetUId == userId)
  //       {
  //         top10.push_back(tweetId);
  //       }
  //       else if (following[userId].find(tweetUId) != following[userId].end())
  //       {
  //         top10.push_back(tweetId);
  //       }
  //     }

  //     return top10;
  //   }

  //   void follow(int followerId, int followeeId)
  //   {
  //     if (followerId == followeeId)
  //       return;
  //     if (following.find(followeeId) == following.end())
  //       return;
  //     // if(following.find(followerId) == following.end()){
  //     //     following[followerId] = unordered_set<int>();
  //     // }
  //     following[followerId].insert(followeeId);
  //   }

  //   void unfollow(int followerId, int followeeId)
  //   {
  //     following[followerId].erase(followeeId);
  //   }
  // };

  // -------------------------------------------------------------
  // Approach3: Using Heap, passing all test cases
  //

  // This approach works more efficiently
  // because while getting the news feed for a user, instead of searching all the posts created till now
  // this approach searches through only the followee's posts and gets top10 creating a Max heap based on post time.
  class Twitter
  {
  public:
    long long time;
    unordered_map<int, unordered_set<int>> following;  // <follower, <list-of-followees>>
    unordered_map<int, vector<pair<int, int>>> tweets; // < userid, list<time,tweetid> >

    Twitter()
    {
      time = 0;
      tweets.clear();
      following.clear();
    }

    void postTweet(int userId, int tweetId)
    {                                              // O(1)
      tweets[userId].push_back({time++, tweetId}); // while adding increase time each time
    }

    vector<int> getNewsFeed(int userId)
    { // O()

      priority_queue<pair<int, int>> pq; // Max heap we will use to get recent 10 posts with highest time

      vector<pair<int, int>> ownnFeed = tweets[userId]; // Add user's own tweets to PQ
      for (auto tweet : ownnFeed)
      {
        pq.push(tweet);
      }

      for (auto fId : following[userId])
      { // get user's followee list
        vector<pair<int, int>> followeeFeed = tweets[fId];

        for (auto fTweet : followeeFeed)
        { // Add User's followee tweets to PQ
          pq.push(fTweet);
        }
      }

      vector<int> top10;

      for (int i = 0; i < 10 && !pq.empty(); i++)
      { // Now extract top 10 posts from Max heap
        top10.push_back(pq.top().second);
        pq.pop();
      }

      return top10;
    }

    void follow(int followerId, int followeeId)
    { // O(1)
      if (followerId == followeeId)
        return;

      following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    { // O(1)
      following[followerId].erase(followeeId);
    }
  };

  /**
   * Your Twitter object will be instantiated and called as such:
   * Twitter* obj = new Twitter();
   * obj->postTweet(userId,tweetId);
   * vector<int> param_2 = obj->getNewsFeed(userId);
   * obj->follow(followerId,followeeId);
   * obj->unfollow(followerId,followeeId);
   */
};

int main()
{
  return 0;
}
