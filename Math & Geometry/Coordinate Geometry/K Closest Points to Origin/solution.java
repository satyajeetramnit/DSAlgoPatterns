import java.util.PriorityQueue;

class Solution {
    public int[][] kClosest(int[][] points, int k) {
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> 
            Integer.compare(b[0]*b[0] + b[1]*b[1], a[0]*a[0] + a[1]*a[1])
        );
        
        for (int[] p : points) {
            maxHeap.offer(p);
            if (maxHeap.size() > k) {
                maxHeap.poll();
            }
        }
        
        int[][] res = new int[k][2];
        for (int i = 0; i < k; i++) {
            res[i] = maxHeap.poll();
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] points = {{1,3}, {-2,2}};
        int[][] res = sol.kClosest(points, 1);
        
        System.out.println("Test Case 1 Output:");
        for (int[] p : res) {
            System.out.print("[" + p[0] + "," + p[1] + "] ");
        }
        System.out.println(); // Expect [-2, 2]
    }
}
