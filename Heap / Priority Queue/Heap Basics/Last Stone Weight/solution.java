import java.util.PriorityQueue;
import java.util.Collections;

class Solution {
    public int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int s : stones) maxHeap.offer(s);
        
        while (maxHeap.size() > 1) {
            int y = maxHeap.poll();
            int x = maxHeap.poll();
            if (x != y) {
                maxHeap.offer(y - x);
            }
        }
        
        return maxHeap.isEmpty() ? 0 : maxHeap.peek();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] stones = {2, 7, 4, 1, 8, 1};
        System.out.println("Test Case 1: " + sol.lastStoneWeight(stones)); // Expect 1
    }
}
