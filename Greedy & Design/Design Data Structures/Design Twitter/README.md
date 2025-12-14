# Design Twitter

## 🧩 Problem Statement
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the `10` most recent tweets in the user's news feed.

Implement the `Twitter` class:
- `Twitter()` Initializes your twitter object.
- `void postTweet(int userId, int tweetId)` Composes a new tweet with ID `tweetId` by the user `userId`. Each call to this function will be distinct and unique.
- `List<Integer> getNewsFeed(int userId)` Retrieves the `10` most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
- `void follow(int followerId, int followeeId)` The user with ID `followerId` started following the user with ID `followeeId`.
- `void unfollow(int followerId, int followeeId)` The user with ID `followerId` started unfollowing the user with ID `followeeId`.

## 🔍 Approaches

### 1. Hash Map + Priority Queue (K-way Merge)
- **Concept:** Getting a news feed is essentially merging $K$ sorted lists (where $K$ is the number of people you follow + yourself).
- **Structure:**
  - `Global Timer`: To strictly order tweets.
  - `Topic Map (User -> List<Tweet>)`: Each user has a linked list of their own tweets.
  - `Follow Map (User -> Set<User>)`: Adjacency list for the follower graph.
- **Algorithm:**
  - `postTweet`: Add tweet (with strict global timestamp) to the head of the user's tweet list.
  - `follow`/`unfollow`: Add/Remove from `followerId`'s set.
  - `getNewsFeed`:
    1. Gather the `head` of the tweet list for the user and everyone they follow.
    2. Put these `heads` into a Max-Heap (based on timestamp).
    3. Pop the max tweet, add to result, and push the `next` tweet from that same list into the Heap.
    4. Repeat until we have 10 tweets.

### 🏛️ Design Diagram
```mermaid
graph TD
    subgraph Users
    u1[User 1]
    u2[User 2]
    u3[User 3]
    end

    subgraph Follow Graph
    u1 -->|Follows| u2
    u1 -->|Follows| u3
    end

    subgraph Tweet Lists
    l1[U1 Tweets: T5 -> T2]
    l2[U2 Tweets: T4 -> T1]
    l3[U3 Tweets: T6 -> T3]
    end
    
    u1 -.-> l1
    u2 -.-> l2
    u3 -.-> l3

    subgraph "Feed Generation (Merge K Lists)"
    h[Max Heap]
    h <--Push--> T5[T5 (U1)]
    h <--Push--> T4[T4 (U2)]
    h <--Push--> T6[T6 (U3)]
    
    res[Result: T6, T5, T4, T3...]
    h -->|Pop Max| res
    end
    
    style h fill:#ff9800,stroke:#333
    style res fill:#4caf50,stroke:#333
```

## ⏳ Time & Space Complexity
- **Time Complexity:**
  - `postTweet`: $O(1)$.
  - `follow/unfollow`: $O(1)$.
  - `getNewsFeed`: $O(K)$ to build heap + $O(10 \log K)$ to extract. $K$ is number of followees.
- **Space Complexity:** $O(U + T)$ where $U$ is users and $T$ is tweets.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

class Twitter {
    struct Tweet {
        int id;
        int time;
        Tweet* next;
        Tweet(int i, int t) : id(i), time(t), next(nullptr) {}
    };

    int time;
    unordered_map<int, Tweet*> userTweets; // User -> Head of Tweet List
    unordered_map<int, unordered_set<int>> followers; // Follower -> Set of Followees

public:
    Twitter() : time(0) {}

    void postTweet(int userId, int tweetId) {
        Tweet* newTweet = new Tweet(tweetId, ++time);
        newTweet->next = userTweets[userId];
        userTweets[userId] = newTweet;
    }

    vector<int> getNewsFeed(int userId) {
        // Min-Heap (but we store timestamp, so logically Max-Heap)
        // Pair: <Tweet*, OriginUserId> ? No, just Tweet* is enough.
        auto cmp = [](Tweet* a, Tweet* b) { return a->time < b->time; };
        priority_queue<Tweet*, vector<Tweet*>, decltype(cmp)> pq(cmp);

        // Add self
        if (userTweets.count(userId) && userTweets[userId]) 
            pq.push(userTweets[userId]);

        // Add followees
        for (int followeeId : followers[userId]) {
            if (userTweets.count(followeeId) && userTweets[followeeId]) {
                pq.push(userTweets[followeeId]);
            }
        }

        vector<int> feed;
        while (!pq.empty() && feed.size() < 10) {
            Tweet* top = pq.top();
            pq.pop();
            feed.push_back(top->id);
            if (top->next) pq.push(top->next);
        }
        return feed;
    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId)
            followers[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followers.count(followerId))
            followers[followerId].erase(followeeId);
    }
};
```

### Python
```python
import heapq
from collections import defaultdict

class Twitter:
    def __init__(self):
        self.time = 0
        self.tweets = defaultdict(list) # userId -> list of [time, tweetId]
        self.following = defaultdict(set) # userId -> set of followeeIds

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.time += 1
        # Push recent tweets to front? Or just append and act like it's sorted?
        # List append is to end. End is NEWEST.
        # So we iterate backwards or utilize index.
        self.tweets[userId].append((-self.time, tweetId))

    def getNewsFeed(self, userId: int) -> list[int]:
        min_heap = []
        
        # Add self
        self.following[userId].add(userId)
        
        for followeeId in self.following[userId]:
            if followeeId in self.tweets:
                # Get the last (newest) tweet
                idx = len(self.tweets[followeeId]) - 1
                time, tweetId = self.tweets[followeeId][idx]
                heapq.heappush(min_heap, (time, tweetId, followeeId, idx - 1))
        
        result = []
        while min_heap and len(result) < 10:
            time, tweetId, followeeId, nextIdx = heapq.heappop(min_heap)
            result.append(tweetId)
            
            if nextIdx >= 0:
                nextTime, nextTweetId = self.tweets[followeeId][nextIdx]
                heapq.heappush(min_heap, (nextTime, nextTweetId, followeeId, nextIdx - 1))
        
        # Don't forget to remove self if only added for query logic?
        # Actually follow logic allows following self or handled implicitly.
        # Problem statement usually implies separate logic.
        # Removing self from set to be safe/clean.
        if userId in self.following[userId]:
             self.following[userId].remove(userId)
             
        return result

    def follow(self, followerId: int, followeeId: int) -> None:
        self.following[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followeeId in self.following[followerId]:
            self.following[followerId].remove(followeeId)
```

### Java
```java
import java.util.*;

class Twitter {
    private static int globalTime = 0;
    
    private class Tweet {
        int id;
        int time;
        Tweet next;
        public Tweet(int id) {
            this.id = id;
            this.time = globalTime++;
            this.next = null;
        }
    }
    
    private Map<Integer, Tweet> userTweets;
    private Map<Integer, Set<Integer>> userFollows;

    public Twitter() {
        userTweets = new HashMap<>();
        userFollows = new HashMap<>();
    }
    
    public void postTweet(int userId, int tweetId) {
        Tweet newTweet = new Tweet(tweetId);
        newTweet.next = userTweets.get(userId);
        userTweets.put(userId, newTweet);
    }
    
    public List<Integer> getNewsFeed(int userId) {
        PriorityQueue<Tweet> pq = new PriorityQueue<>((a, b) -> b.time - a.time);
        
        // Add self
        if (userTweets.containsKey(userId)) {
            pq.offer(userTweets.get(userId));
        }
        
        // Add followees
        if (userFollows.containsKey(userId)) {
            for (int followeeId : userFollows.get(userId)) {
                if (userTweets.containsKey(followeeId)) {
                    pq.offer(userTweets.get(followeeId));
                }
            }
        }
        
        List<Integer> res = new ArrayList<>();
        while (!pq.isEmpty() && res.size() < 10) {
            Tweet t = pq.poll();
            res.add(t.id);
            if (t.next != null) {
                pq.offer(t.next);
            }
        }
        return res;
    }
    
    public void follow(int followerId, int followeeId) {
        userFollows.putIfAbsent(followerId, new HashSet<>());
        userFollows.get(followerId).add(followeeId);
    }
    
    public void unfollow(int followerId, int followeeId) {
        if (userFollows.containsKey(followerId)) {
            userFollows.get(followerId).remove(followeeId);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Newspaper Aggregation:**
You subscribe to 10 newspapers (Users). Every morning (getNewsFeed), you want the latest headlines. You stack the newest issue of each newspaper on a table. You pick the one with the most recent date (Priority Queue). After reading it, you look at the *previous* issue of that same newspaper and put it back in the valid pile. You repeat this until you have 10 headlines.

## 🎯 Summary
✅ **Merge K Sorted Lists:** By storing tweets as time-ordered linked lists per user, fetching the feed becomes an efficient K-Way Merge problem.
