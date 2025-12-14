import java.util.PriorityQueue;

class KthLargest {
    private PriorityQueue<Integer> minHeap;
    private int k;

    public KthLargest(int k, int[] nums) {
        this.k = k;
        minHeap = new PriorityQueue<>();
        for (int num : nums) {
            add(num);
        }
    }
    
    public int add(int val) {
        minHeap.offer(val);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        return minHeap.peek();
    }

    public static void main(String[] args) {
        int[] nums = {4, 5, 8, 2};
        KthLargest obj = new KthLargest(3, nums);
        System.out.println("Test Case 1:");
        System.out.println("Add 3: " + obj.add(3));   // 4
        System.out.println("Add 5: " + obj.add(5));   // 5
        System.out.println("Add 10: " + obj.add(10)); // 5
        System.out.println("Add 9: " + obj.add(9));   // 8
        System.out.println("Add 4: " + obj.add(4));   // 8
    }
}
