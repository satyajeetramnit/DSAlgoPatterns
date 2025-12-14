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
        
        if (userTweets.containsKey(userId)) {
            pq.offer(userTweets.get(userId));
        }
        
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
        if (followerId == followeeId) return;
        userFollows.putIfAbsent(followerId, new HashSet<>());
        userFollows.get(followerId).add(followeeId);
    }
    
    public void unfollow(int followerId, int followeeId) {
        if (userFollows.containsKey(followerId)) {
            userFollows.get(followerId).remove(followeeId);
        }
    }

    public static void main(String[] args) {
        Twitter twitter = new Twitter();
        twitter.postTweet(1, 5);
        System.out.println("Feed 1 (Expect [5]): " + twitter.getNewsFeed(1));
        
        twitter.follow(1, 2);
        twitter.postTweet(2, 6);
        System.out.println("Feed 1 (Expect [6, 5]): " + twitter.getNewsFeed(1));
        
        twitter.unfollow(1, 2);
        System.out.println("Feed 1 (Expect [5]): " + twitter.getNewsFeed(1));
    }
}
