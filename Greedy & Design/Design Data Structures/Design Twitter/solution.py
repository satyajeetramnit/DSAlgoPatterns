import heapq
from collections import defaultdict

class Twitter:
    def __init__(self):
        self.time = 0
        self.tweets = defaultdict(list) # userId -> list of [time, tweetId]
        self.following = defaultdict(set) # userId -> set of followeeIds

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.time += 1
        self.tweets[userId].append((-self.time, tweetId))

    def getNewsFeed(self, userId: int) -> list[int]:
        min_heap = []
        
        # Add self (temporarily in logic)
        users = self.following[userId] | {userId}
        
        for u in users:
            if u in self.tweets and self.tweets[u]:
                idx = len(self.tweets[u]) - 1
                time, tweet_id = self.tweets[u][idx]
                heapq.heappush(min_heap, (time, tweet_id, u, idx - 1))
        
        result = []
        while min_heap and len(result) < 10:
            time, tweet_id, u, next_idx = heapq.heappop(min_heap)
            result.append(tweet_id)
            
            if next_idx >= 0:
                next_time, next_tweet_id = self.tweets[u][next_idx]
                heapq.heappush(min_heap, (next_time, next_tweet_id, u, next_idx - 1))
             
        return result

    def follow(self, followerId: int, followeeId: int) -> None:
        if followerId != followeeId:
            self.following[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followeeId in self.following[followerId]:
            self.following[followerId].remove(followeeId)

if __name__ == "__main__":
    twitter = Twitter()
    twitter.postTweet(1, 5)
    print(f"Feed 1 (Expect [5]): {twitter.getNewsFeed(1)}")
    
    twitter.follow(1, 2)
    twitter.postTweet(2, 6)
    print(f"Feed 1 (Expect [6, 5]): {twitter.getNewsFeed(1)}")
    
    twitter.unfollow(1, 2)
    print(f"Feed 1 (Expect [5]): {twitter.getNewsFeed(1)}")
