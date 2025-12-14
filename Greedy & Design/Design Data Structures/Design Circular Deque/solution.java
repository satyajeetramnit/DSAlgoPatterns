class MyCircularDeque {
    private int[] buffer;
    private int k, front, rear, count;

    public MyCircularDeque(int k) {
        this.k = k;
        this.buffer = new int[k];
        this.front = 0;
        this.rear = k - 1;
        this.count = 0;
    }
    
    public boolean insertFront(int value) {
        if (isFull()) return false;
        front = (front - 1 + k) % k;
        buffer[front] = value;
        count++;
        return true;
    }
    
    public boolean insertLast(int value) {
        if (isFull()) return false;
        rear = (rear + 1) % k;
        buffer[rear] = value;
        count++;
        return true;
    }
    
    public boolean deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % k;
        count--;
        return true;
    }
    
    public boolean deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + k) % k;
        count--;
        return true;
    }
    
    public int getFront() {
        if (isEmpty()) return -1;
        return buffer[front];
    }
    
    public int getRear() {
        if (isEmpty()) return -1;
        return buffer[rear];
    }
    
    public boolean isEmpty() {
        return count == 0;
    }
    
    public boolean isFull() {
        return count == k;
    }

    public static void main(String[] args) {
        MyCircularDeque deque = new MyCircularDeque(3);
        System.out.println("Insert Last 1: " + deque.insertLast(1));
        System.out.println("Insert Last 2: " + deque.insertLast(2));
        System.out.println("Insert Front 3: " + deque.insertFront(3));
        System.out.println("Insert Front 4 (Full): " + deque.insertFront(4));
        System.out.println("Get Rear (2): " + deque.getRear());
        System.out.println("Is Full (true): " + deque.isFull());
        System.out.println("Delete Last: " + deque.deleteLast());
        System.out.println("Get Front (3): " + deque.getFront());
    }
}
