import java.util.*;

class Solution {
    public int leastInterval(char[] tasks, int n) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char t : tasks) counts.put(t, counts.getOrDefault(t, 0) + 1);
        
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        maxHeap.addAll(counts.values());
        
        int time = 0;
        Queue<int[]> q = new LinkedList<>(); // {freq, active_time}
        
        while (!maxHeap.isEmpty() || !q.isEmpty()) {
            time++;
            
            if (!maxHeap.isEmpty()) {
                int freq = maxHeap.poll();
                freq--;
                if (freq > 0) {
                    q.offer(new int[]{freq, time + n});
                }
            }
            
            if (!q.isEmpty() && q.peek()[1] == time) {
                maxHeap.offer(q.poll()[0]);
            }
        }
        
        return time;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        char[] tasks = {'A','A','A','B','B','B'};
        int n = 2;
        System.out.println("Test Case 1: " + sol.leastInterval(tasks, n)); // Expect 8
    }
}
