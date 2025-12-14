import java.util.PriorityQueue;
import java.util.Collections;

class MedianFinder {
    private PriorityQueue<Integer> small; // Max heap
    private PriorityQueue<Integer> large; // Min heap

    public MedianFinder() {
        small = new PriorityQueue<>(Collections.reverseOrder());
        large = new PriorityQueue<>();
    }
    
    public void addNum(int num) {
        small.offer(num);
        large.offer(small.poll());
        
        if (small.size() < large.size()) {
            small.offer(large.poll());
        }
    }
    
    public double findMedian() {
        if (small.size() > large.size()) {
            return (double)small.peek();
        } else {
            return (double)(small.peek() + large.peek()) / 2.0;
        }
    }

    public static void main(String[] args) {
        MedianFinder obj = new MedianFinder();
        obj.addNum(1);
        obj.addNum(2);
        System.out.println("Median (1,2): " + obj.findMedian()); // 1.5
        obj.addNum(3);
        System.out.println("Median (1,2,3): " + obj.findMedian()); // 2.0
    }
}
