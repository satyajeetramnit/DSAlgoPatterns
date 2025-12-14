#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Twitter {
  struct Tweet {
    int id;
    int time;
    Tweet *next;
    Tweet(int i, int t) : id(i), time(t), next(nullptr) {}
  };

  int time;
  unordered_map<int, Tweet *> userTweets; // User -> Head of Tweet List
  unordered_map<int, unordered_set<int>>
      followers; // Follower -> Set of Followees

public:
  Twitter() : time(0) {}

  void postTweet(int userId, int tweetId) {
    Tweet *newTweet = new Tweet(tweetId, ++time);
    newTweet->next = userTweets[userId];
    userTweets[userId] = newTweet;
  }

  vector<int> getNewsFeed(int userId) {
    auto cmp = [](Tweet *a, Tweet *b) { return a->time < b->time; };
    priority_queue<Tweet *, vector<Tweet *>, decltype(cmp)> pq(cmp);

    if (userTweets.count(userId) && userTweets[userId])
      pq.push(userTweets[userId]);

    for (int followeeId : followers[userId]) {
      if (userTweets.count(followeeId) && userTweets[followeeId]) {
        pq.push(userTweets[followeeId]);
      }
    }

    vector<int> feed;
    while (!pq.empty() && feed.size() < 10) {
      Tweet *top = pq.top();
      pq.pop();
      feed.push_back(top->id);
      if (top->next)
        pq.push(top->next);
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

int main() {
  Twitter twitter;
  twitter.postTweet(1, 5); // User 1 posts tweet 5
  vector<int> feed = twitter.getNewsFeed(1);
  cout << "Feed 1 (Expect 5): ";
  for (int id : feed)
    cout << id << " ";
  cout << endl;

  twitter.follow(1, 2);    // User 1 follows User 2
  twitter.postTweet(2, 6); // User 2 posts tweet 6
  feed = twitter.getNewsFeed(1);
  cout << "Feed 1 (Expect 6, 5): ";
  for (int id : feed)
    cout << id << " ";
  cout << endl;

  twitter.unfollow(1, 2); // User 1 unfollows User 2
  feed = twitter.getNewsFeed(1);
  cout << "Feed 1 (Expect 5): ";
  for (int id : feed)
    cout << id << " ";
  cout << endl;

  return 0;
}
